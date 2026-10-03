import base64
import re
from pathlib import Path

FRONT = "iVBORw0KGgoAAAANSUhEUgAAAEAAAABABAMAAABYR2ztAAAAMFBMVEX/AP+Hd8KXidaypexpWaK8sPHQyvvf2PxMOoFcUm4+LXpRSmE+OEguKTgTEBoDAwfm3lE9AAAAAXRSTlMAQObYZgAABGFJREFUeJzV1V1sFFUUwPH/fPSDgXZ3izaCINMWJBaFoYVojGnrUkg0wRCMDbQQxxQxMamWPqBgYioPagwJ9SOAYs2U1gcbkpaoMcFS1oYsIRZYC6kG6zK0oAmE7uyCU9rOzvqw221XGn3ywfMyd+79zbnnnklm4H8cSmdqIM++3nHxX55/fC9mciiCx7oHjKmgpsGtezMkAvFS0oCue0Ujy6eBUDq9hyd5yd2PaaRBARfS4LIF0PlptaMCBiBDlCHLm1y/eXwNKDnnWNQ70oUSStVQ755P1dZdHoGcDQz1mvsRGrTUMSV+NQE8J4qizyGIqmOaEZ3CET2V4bZOBPB8YHp1EUqAOQDhVJGRTetIAENIOd4oRhzcCaClwpcECUFQEyaeMNrrq4DhgOyPG1Av6EZyCznmTXhxLUm6qoLuuMj+wwZ2SEz1IXfZfMFjRaBEAuYQHupZWvmhwQ9Trb77jCp+9hXiak0AbNze4iHW7yKRpYMAvPLJ6csgJ57u+2WrBkoOUFzd0/DHAh1ksLKFfMApX7Rlt0b7oSBPEh+gqtFKbTGv0N8PMNB+QUC4hGH3BCUxIJdOvSzf1/ngGEz6jSY6nKAOdsBxmUBJAnGii01iFYyMe9kuApBNGGhN9iG6rm3Dt64KkmGRO6wC2JoIRn0IRMhrjT+wXabk5awvVMbMhdBWiy64gAIi3K7HKNfKl49eel45erQSlHfPGBS5Jq1msg95py6aG3nro741gwM97hWr7dIK3bfzhDS44JaFCMTKFjYjPdG3ZvU+p2GP9c4+gTbRuRa337OSGcA9grR9cLF88OYBlDlVS09E1/dXt/8+9S5Q9m3Kjg9ulm8ckHBO5/eZG9Z6/T02adCq3rdtR35UO7ZZejQ0uScvbKrOyTesNFB+VFYNm3eWlR3vd4iHxiJOL2JhjWKkM/x5NmbhX7msQo4FoFkdcXrcLeT9NAXsimvlHssfc5sqJ8wBrbmYcVP+pqO2AFLfh7ov+wOa6f9uy5ujliDlBtQGoWnHxbNn0kDpXqSO+am+s7I7rnHXlRsnDjUWhRPpGj4vll/6OBzOqtmJRByRUvvF8demT4Eg9dUsGTpp1j4L0Fz81KBSa+tMAz3YhUt/YB4+HxKi22IsgBlgUpsrB26Oogv4Fm9sJmuv3WLMBG7LXKMywAuC77GaOqfFEbbuzcnIAN5gVoGqU0D8vOS1AnLdQT0TSKfqDvxGdIldLzwcKnNN8TAoM0E0PrnLggA7XTux1n2orQyOzARoieEqJsAev9K5+2fx/SCdoUyASkgEbPdV7EB3o3Lu+wxQYFGIWASQDY0Ldbs8MwOCN0rCC4pow7ZcqMk4BVYBbMSCM14Lcq5P9SkNAoAXkJseBOxQ999AXCiC+US4aokAb9+YAskfihxs6YA7RHjkgqQC7mRmhtixaOo+VqICynm/kQHu1+q9gOZayVkpPqozSzgrKlIjd3S2dcTrlbPOp8OTsP4Z/DfxF8Q/qmFU0vl8AAAAAElFTkSuQmCC"
BACK = "iVBORw0KGgoAAAANSUhEUgAAAEAAAABABAMAAABYR2ztAAAAMFBMVEX/AP+Hd8KXidaypexpWaK8sPHQyvvf2PxMOoFcUm4+LXpRSmE+OEguKTgTEBoDAwfm3lE9AAAAAXRSTlMAQObYZgAAA/ZJREFUeJztk11sFFUYhp8zu4WhwuyZ8iM3bU7bxEiwsG0x1gCyCCgmEIx4gYmaRhJNiCaNiVoM4gBVCTeudyTeFC4MGk0IcuEFwtafBGNLp/wkqHSdghhU2j1dqw6wM+PF7g5tUQz3vlcn5zzzfu/3nTPwv+5MtR/9B2A+su0f943qwj9euj2Ag3NboOdiqQxYXnzoTQaOM6Oyyle3rPxkIOMGZYdivTedBEA0Lth6rwPw2/GKwfuxgwPM3Do7sWg/gBGcAmBYGV4ZMH3AL3Xm5s9ygDA96gGWK7DKwPWTAM7uQK8GCFeTB4apQ5UB4x4HIGnAIQBTRR64RpJiGSipEYBrlbhNS+wQLKQdD6oXwLSlRAGIVjTDkK4CIjMTemrtxiAHkEjYsgEtRHMV2BV2cODd5jVy0PABsrIOC3sidnBKnbteXtM62l9QGaCoVSr4hNRiqoBpcrBZjo6kmpMOQL0ccRHFoRuqAvzZkNTpwR9l4unPeGsL3KUbQKOCuIvdwRpCzdpOiK7B6bQH45F8Ls7g44GR7AZ2fO1gdWqIIr2kAszI4UBEB0CtzKIGANBzKkBvBgJQDmDOWtlFsQ2QQj7gVUpcAdxWzwGYKxzwJIIC6ypdPBtm9niRkcqZTzh+veGwd3UdEtvrqjiU6r9Phvnx9gm/7yf63Et7g2JKQkN4udrFG8/7ry0dcNvam42O0oYz3404jTbqYluTAkTljs0Vg5u5evahp9Ljey7/IBbvrCvMU/Gg9oH/1RI3cEunX/g42Dewzr78eV5gxndxVWF2f6mRkbdWe0MXb7Tf/2FWqJKsOsxbxuv7d2YGNaXRHNGx5c9Ey77RJLdUAP/VL9Z+uvzomBR66YgnmXOoNhAbs2yPM/BSU+vclmMPaza3aJtAvHnGrRm8cu4mEA64wZDuUeaRU46WHDjXEvDor6nzQBKAdx48fWNT//ahBRt/T2Awtq7fS9x39MzJ2ME/8comh766xxO5QEbqF9c4EeGtv1kCuvdudgRH0k8i0aJ34WxvovzG49/fqnFWBdf4qx0kGrqGvQxxBqjdWM/bDWF34jGB5m4pV15S3ZMdwgTmfr1KuAgloCtKnu9mMuAfvuK/pxBSFCG05XjUyxSAsevOUDqipqgENnXRQlXer2agdLZhhmtcn5AWyELC1kxx6NnCi45ff4GtirwWwDRgxybnZ2rCrOFQbEohlSp4TJb5gYT565NtDlhX8xazv/WmOJSyaVjRkZzIQlHoIobNVO0Ccxkc3AZY/cAFl+lKSKAZsIY9GD08bQ4QKTD/iD9suQUwTDAWZaAoQ2gs5KaXqG0FxjxgtN+DQnhLiFjWmPfvh3esvwHD9neyxjwIggAAAABJRU5ErkJggg=="
ICON = "iVBORw0KGgoAAAANSUhEUgAAACAAAABABAMAAACJoGidAAAAMFBMVEVinIN7e3u9vbT///9zc82krPa0g1ruxYvFrCn29in2YlKUe83FpM29KZxiYlpBQUHpRLRfAAAAAXRSTlMAQObYZgAAATpJREFUeJztkiFPw1AUhb/30i1hJK9vlhBShQBNsCCGQVBELSz8Asj+CBqFHoIi0HMoEgjhB1S0E5CsbyNjybb0IkqHIigUHHXuyTX3uwd+lv9lE0CDq+KMMhDATwBOAc3cB3ILrHqA5kU5CjUEkyoAxr3Ez2egouhGJcBYROTW0YpCMtCsII6uRTAEMRpwD7ShwSSZXQKFDI5meJi0FRnQqH5TeShGG8ITgC/HY2HNQhqFZVC85bUIE3qRfUUzbDJv77zKNrs8dvDgWdXq9aks1ew8AI054xBiN7njGtCM4j3b6GJli6w8P7HyDn11Hm8m4EHgpuuADSgCUIDvnD2YYK+SALySpkrvly8GJxXcQhz7RHwyBbAL8roynfILpXLBhJiwmkUKgGyxIT0fYPDdb39F/4X5M4X5AMPa38+zc2FAAAAAAElFTkSuQmCC"
NORMAL_PAL = """JASC-PAL\n0100\n16\n255 0 255\n135 119 194\n151 137 214\n178 165 236\n105 89 162\n188 176 241\n208 202 251\n223 216 252\n76 58 129\n92 82 110\n62 45 122\n81 74 97\n62 56 72\n46 41 56\n19 16 26\n3 3 7\n"""
SHINY_PAL = """JASC-PAL\n0100\n16\n255 0 255\n100 185 185\n122 193 189\n148 216 206\n79 146 158\n159 216 207\n204 238 229\n192 234 226\n43 105 117\n60 82 133\n68 139 142\n56 75 128\n41 57 98\n34 51 83\n27 38 60\n31 39 53\n"""

root = Path('.')
asset = root / 'graphics/pokemon/ectoceon'
asset.mkdir(parents=True, exist_ok=True)
(asset/'front.png').write_bytes(base64.b64decode(FRONT))
(asset/'back.png').write_bytes(base64.b64decode(BACK))
(asset/'icon.png').write_bytes(base64.b64decode(ICON))
(asset/'normal.pal').write_text(NORMAL_PAL)
(asset/'shiny.pal').write_text(SHINY_PAL)
(asset/'NOTICE.txt').write_text('ROM-ready assets were derived from the approved Ectoceon implementation references archived in the Sam Edition Google Drive.\n')
(asset/'README.txt').write_text('''Ectoceon ROM asset source package for Pokemon: Sam Edition.\n\nfront.png / back.png are indexed 64x64 Gen III battle sources derived from the approved Ectoceon front/back implementation references.\nnormal.pal is the normal runtime palette; shiny.pal is derived from the approved shiny Ectoceon references while preserving the normal tile indices.\nicon.png is a 32x64 two-frame party/menu icon using existing icon palette 2.\nNo dedicated Ectoceon footprint artwork exists in the current asset authority, so Ectoceon conservatively reuses Eevee's family footprint rather than inventing new art.\nNo Ectoceon overworld sprite is required by current canon.\n''')
(root/'src/sam_ectoceon_graphics.c').write_text('''#include "global.h"\n\nconst u32 gMonFrontPic_Ectoceon[] = INCBIN_U32("graphics/pokemon/ectoceon/front.4bpp.lz");\nconst u32 gMonPalette_Ectoceon[] = INCBIN_U32("graphics/pokemon/ectoceon/normal.gbapal.lz");\nconst u32 gMonBackPic_Ectoceon[] = INCBIN_U32("graphics/pokemon/ectoceon/back.4bpp.lz");\nconst u32 gMonShinyPalette_Ectoceon[] = INCBIN_U32("graphics/pokemon/ectoceon/shiny.gbapal.lz");\nconst u8 gMonIcon_Ectoceon[] = INCBIN_U8("graphics/pokemon/ectoceon/icon.4bpp");\n''')

def replace_once(path, old, new):
    p = root/path
    s = p.read_text()
    n = s.count(old)
    if n != 1:
        raise RuntimeError(f'{path}: expected one match, found {n}: {old!r}')
    p.write_text(s.replace(old, new, 1))

replace_once('src/data/pokemon_graphics/front_pic_table.h', 'SPECIES_SPRITE(ECTOCEON, gMonFrontPic_CircledQuestionMark)', 'SPECIES_SPRITE(ECTOCEON, gMonFrontPic_Ectoceon)')
replace_once('src/data/pokemon_graphics/back_pic_table.h', 'SPECIES_SPRITE(ECTOCEON, gMonBackPic_CircledQuestionMark)', 'SPECIES_SPRITE(ECTOCEON, gMonBackPic_Ectoceon)')
replace_once('src/data/pokemon_graphics/palette_table.h', 'SPECIES_PAL(ECTOCEON, gMonPalette_CircledQuestionMark)', 'SPECIES_PAL(ECTOCEON, gMonPalette_Ectoceon)')
replace_once('src/data/pokemon_graphics/shiny_palette_table.h', 'SPECIES_SHINY_PAL(ECTOCEON, gMonPalette_CircledQuestionMark)', 'SPECIES_SHINY_PAL(ECTOCEON, gMonShinyPalette_Ectoceon)')
replace_once('src/data/pokemon_graphics/footprint_table.h', '[SPECIES_ECTOCEON] = gMonFootprint_Bulbasaur', '[SPECIES_ECTOCEON] = gMonFootprint_Eevee')
replace_once('src/pokemon_icon.c', '[SPECIES_ECTOCEON]    = gMonIcon_QuestionMark', '[SPECIES_ECTOCEON]    = gMonIcon_Ectoceon')
replace_once('src/pokemon_icon.c', '[SPECIES_ECTOCEON]    = 0,', '[SPECIES_ECTOCEON]    = 2,')

for path, y in [('src/data/pokemon_graphics/front_pic_coordinates.h', 3), ('src/data/pokemon_graphics/back_pic_coordinates.h', 2)]:
    p = root/path
    s = p.read_text()
    pattern = r'(\[SPECIES_ECTOCEON\] =\s*\{\s*)\.size = MON_COORDS_SIZE\(64, 64\),\s*\.y_offset = 0,(\s*\},)'
    repl = rf'\1.size = MON_COORDS_SIZE(56, 56),\n        .y_offset = {y},\2'
    out, n = re.subn(pattern, repl, s, count=1)
    if n != 1:
        raise RuntimeError(f'{path}: coordinate placeholder match count {n}')
    p.write_text(out)

p = root/'include/graphics.h'
s = p.read_text()
needle = 'extern const u8 gMonFootprint_Leafeon[];\n\nextern const u32 gMonFrontPic_Egg[];'
insert = '''extern const u8 gMonFootprint_Leafeon[];\nextern const u32 gMonFrontPic_Ectoceon[];\nextern const u32 gMonPalette_Ectoceon[];\nextern const u32 gMonBackPic_Ectoceon[];\nextern const u32 gMonShinyPalette_Ectoceon[];\nextern const u8 gMonIcon_Ectoceon[];\n\nextern const u32 gMonFrontPic_Egg[];'''
if s.count(needle) != 1:
    raise RuntimeError('graphics.h insertion anchor mismatch')
p.write_text(s.replace(needle, insert, 1))

# Remove temporary automation files so the final production commit contains only the implementation.
Path('.github/workflows/zz-apply-ectoceon-assets.yml').unlink(missing_ok=True)
Path('tools/apply_ectoceon_assets.py').unlink(missing_ok=True)
