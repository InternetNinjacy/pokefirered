#!/usr/bin/env python3
from pathlib import Path
import base64, io, shutil, struct, zlib, zipfile, binascii

ROOT = Path(__file__).resolve().parents[2]
HERE = Path(__file__).resolve().parent
ROOMS = {
    'lorelei': ('PokemonLeague_LoreleisRoom', 'pokemon_league_lorelei'),
    'blue': ('PokemonLeague_BrunosRoom', 'pokemon_league_blue'),
    'agatha': ('PokemonLeague_AgathasRoom', 'pokemon_league_agatha'),
    'lance': ('PokemonLeague_LancesRoom', 'pokemon_league_lance'),
    'green': ('PokemonLeague_ChampionsRoom', 'pokemon_league_green'),
}


def unpack_payload():
    parts = sorted(HERE.glob('payload.part*'))
    if not parts:
        raise SystemExit('League Phase 5 payload parts are missing.')
    encoded = ''.join(p.read_text().strip() for p in parts)
    data = base64.b64decode(encoded)
    with zipfile.ZipFile(io.BytesIO(data)) as z:
        z.extractall(HERE)
    return HERE / 'payload'


def read_png_indexed(path):
    data = path.read_bytes()
    if data[:8] != b'\x89PNG\r\n\x1a\n':
        raise ValueError(f'{path}: not PNG')
    pos = 8; chunks = []
    width = height = bit_depth = color_type = None
    palette = None; idat = bytearray()
    while pos < len(data):
        n = struct.unpack('>I', data[pos:pos+4])[0]; typ = data[pos+4:pos+8]; body = data[pos+8:pos+8+n]
        pos += 12 + n
        if typ == b'IHDR':
            width, height, bit_depth, color_type, comp, filt, interlace = struct.unpack('>IIBBBBB', body)
            if color_type != 3 or interlace != 0 or bit_depth not in (4, 8):
                raise ValueError(f'{path}: expected non-interlaced indexed PNG (4/8 bpp), got type={color_type}, depth={bit_depth}, interlace={interlace}')
        elif typ == b'PLTE': palette = bytes(body)
        elif typ == b'IDAT': idat.extend(body)
        elif typ == b'IEND': break
    if width is None or palette is None: raise ValueError(f'{path}: incomplete PNG')
    raw = zlib.decompress(bytes(idat))
    rowbytes = (width * bit_depth + 7) // 8
    bpp = 1
    rows=[]; prev=bytearray(rowbytes); p=0
    for _ in range(height):
        ft=raw[p]; p+=1; cur=bytearray(raw[p:p+rowbytes]); p+=rowbytes
        for i in range(rowbytes):
            a=cur[i-bpp] if i>=bpp else 0; b=prev[i]; c=prev[i-bpp] if i>=bpp else 0
            if ft==1: cur[i]=(cur[i]+a)&255
            elif ft==2: cur[i]=(cur[i]+b)&255
            elif ft==3: cur[i]=(cur[i]+((a+b)//2))&255
            elif ft==4:
                pp=a+b-c; pa=abs(pp-a); pb=abs(pp-b); pc=abs(pp-c); pr=a if pa<=pb and pa<=pc else (b if pb<=pc else c)
                cur[i]=(cur[i]+pr)&255
            elif ft!=0: raise ValueError(f'{path}: unsupported PNG filter {ft}')
        rows.append(cur); prev=cur
    pixels=[]
    if bit_depth==8:
        for r in rows: pixels.extend(r[:width])
    else:
        for r in rows:
            for x in range(width):
                v=r[x//2]; pixels.append((v>>4)&15 if x%2==0 else v&15)
    return width,height,bit_depth,palette,pixels


def png_chunk(typ, body):
    return struct.pack('>I',len(body))+typ+body+struct.pack('>I',binascii.crc32(typ+body)&0xffffffff)


def write_png_indexed(path,w,h,depth,palette,pixels):
    if depth==8:
        rows=[bytes(pixels[y*w:(y+1)*w]) for y in range(h)]
    else:
        rows=[]
        for y in range(h):
            src=pixels[y*w:(y+1)*w]; row=bytearray((w+1)//2)
            for x,v in enumerate(src):
                if x%2==0: row[x//2]=(v&15)<<4
                else: row[x//2]|=v&15
            rows.append(bytes(row))
    raw=b''.join(b'\x00'+r for r in rows)
    ihdr=struct.pack('>IIBBBBB',w,h,depth,3,0,0,0)
    out=b'\x89PNG\r\n\x1a\n'+png_chunk(b'IHDR',ihdr)+png_chunk(b'PLTE',palette)+png_chunk(b'IDAT',zlib.compress(raw,9))+png_chunk(b'IEND',b'')
    path.parent.mkdir(parents=True,exist_ok=True); path.write_bytes(out)


def tile_pixels(tile32):
    out=[]
    for b in tile32: out += [b & 0x0F, (b >> 4) & 0x0F]
    return out


def main():
    payload=unpack_payload()
    base=ROOT/'data/tilesets/secondary/pokemon_league'
    basepng=base/'tiles.png'
    if not basepng.exists(): raise SystemExit('Expected live Sam/pokefirered source root; pokemon_league tiles.png missing.')
    w,h,depth,palette,basepixels=read_png_indexed(basepng)
    if w != 128 or h > 192 or h % 8:
        raise ValueError(f'Unexpected Pokemon League tiles.png dimensions: {w}x{h}')
    if depth not in (4,8): raise ValueError('Unsupported indexed PNG depth')
    # Vanilla FireRed's source PNG is 128x176 (352 explicit tiles), while the
    # engine reserves 384 secondary tile slots. Pad the source canvas to the
    # full 128x192 slot space before applying locked Sam tile IDs 640-1023.
    if h < 192:
        basepixels.extend([0] * (w * (192 - h)))
        h = 192

    for room,(layout_dir,tsdir) in ROOMS.items():
        src=payload/'tilesets'/tsdir; dest=ROOT/'data/tilesets/secondary'/tsdir
        (dest/'palettes').mkdir(parents=True,exist_ok=True)
        for p in (base/'palettes').glob('*.pal'): shutil.copy2(p,dest/'palettes'/p.name)
        shutil.copy2(src/'palettes/05.pal',dest/'palettes/05.pal')
        shutil.copy2(src/'metatiles.bin',dest/'metatiles.bin')
        shutil.copy2(src/'metatile_attributes.bin',dest/'metatile_attributes.bin')
        pix=list(basepixels); data=(src/'custom_tiles_payload.bin').read_bytes()
        if len(data)%34: raise ValueError(f'{room}: malformed custom tile payload')
        for off in range(0,len(data),34):
            gid=struct.unpack_from('<H',data,off)[0]; local=gid-640
            if not 0<=local<384: raise ValueError(f'{room}: tile {gid} outside secondary range')
            tx=(local%16)*8; ty=(local//16)*8; tp=tile_pixels(data[off+2:off+34])
            for yy in range(8):
                start=(ty+yy)*w+tx; pix[start:start+8]=tp[yy*8:(yy+1)*8]
        write_png_indexed(dest/'tiles.png',w,h,depth,palette,pix)
        mapdst=ROOT/'data/layouts'/layout_dir/'map.bin'; mapdst.parent.mkdir(parents=True,exist_ok=True)
        shutil.copy2(payload/'maps'/layout_dir/'map.bin',mapdst)
        border=payload/'maps'/layout_dir/'border.bin'
        if border.exists(): shutil.copy2(border,ROOT/'data/layouts'/layout_dir/'border.bin')

    required_symbols = ['gTileset_PokemonLeagueLorelei','gTileset_PokemonLeagueBlue','gTileset_PokemonLeagueAgatha','gTileset_PokemonLeagueLance','gTileset_PokemonLeagueGreen']
    combined='\n'.join((ROOT/p).read_text() for p in ['src/data/tilesets/graphics.h','src/data/tilesets/metatiles.h','src/data/tilesets/headers.h','data/layouts/layouts.json'])
    missing=[s for s in required_symbols if s not in combined]
    if missing: raise SystemExit('Missing League source bindings: '+', '.join(missing))
    print('Installed all five Sam Edition League Phase 4 room payloads for this checkout.')

if __name__=='__main__': main()
