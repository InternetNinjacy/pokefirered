#!/usr/bin/env python3
"""Decode an actual GBA gPlayerParty RAM snapshot without modifying gameplay.

Input is raw, contiguous 6 * sizeof(struct Pokemon) bytes captured from mGBA
at the symbol's address, not an encrypted save-file blob. This is an oracle
for future emulator-RAM acquisition, NOT a substitute for an actual capture.
"""
import argparse
import json
import struct
from pathlib import Path

ORDER = [
    (0,1,2,3),(0,1,3,2),(0,2,1,3),(0,3,1,2),(0,2,3,1),(0,3,2,1),
    (1,0,2,3),(1,0,3,2),(2,0,1,3),(3,0,1,2),(2,0,3,1),(3,0,2,1),
    (1,2,0,3),(1,3,0,2),(2,1,0,3),(3,1,0,2),(2,3,0,1),(3,2,0,1),
    (1,2,3,0),(1,3,2,0),(2,1,3,0),(3,1,2,0),(2,3,1,0),(3,2,1,0),
]
POKEMON_SIZE = 100
SECURE_OFFSET = 32
SECURE_SIZE = 48
STARTERS = {133:"Eevee",172:"Pichu",132:"Ditto"}

def decode_mon(raw):
    if len(raw) != POKEMON_SIZE:
        raise ValueError("Expected exactly 100 bytes per struct Pokemon")
    personality, otid = struct.unpack_from("<II",raw,0)
    stored_checksum = struct.unpack_from("<H",raw,28)[0]  # offset audited below by self-test
    # FRLG BoxPokemon: checksum is at 28, unknown at 30, secure at 32.
    key = personality ^ otid
    plain = bytearray(raw[SECURE_OFFSET:SECURE_OFFSET+SECURE_SIZE])
    for off in range(0,SECURE_SIZE,4):
        value = struct.unpack_from("<I",plain,off)[0] ^ key
        struct.pack_into("<I",plain,off,value)
    calculated = sum(struct.unpack_from("<24H",plain)) & 0xffff
    order = ORDER[personality%24]
    sub0_pos=order.index(0)
    species = struct.unpack_from("<H",plain,sub0_pos*12)[0]
    return {"personality":personality,"otid":otid,"species":species,
            "species_name":STARTERS.get(species,str(species)),
            "level":raw[84], "checksum_expected":stored_checksum,
            "checksum_calculated":calculated, "checksum_valid":stored_checksum==calculated}

def decode_party(data):
    if len(data)!=6*POKEMON_SIZE:
        raise ValueError("Require exact six-member 600-byte party RAM snapshot")
    return [decode_mon(data[i*POKEMON_SIZE:(i+1)*POKEMON_SIZE]) for i in range(6)]

def validate_starter(party,expected):
    if expected not in STARTERS:
        raise ValueError("Unsupported expected starter species")
    found=[mon for mon in party if mon["species"] and mon["checksum_valid"]]
    if len(found)!=1 or found[0]["species"]!=expected or found[0]["level"]!=5:
        raise AssertionError(f"Expected exactly one Lv.5 {STARTERS[expected]}: {found}")
    return True

def synthetic_mon(species,personality,otid=0x11223344,level=5):
    raw=bytearray(POKEMON_SIZE)
    struct.pack_into("<II",raw,0,personality,otid)
    raw[84]=level
    plain=bytearray(SECURE_SIZE)
    struct.pack_into("<H",plain,ORDER[personality%24].index(0)*12,species)
    checksum=sum(struct.unpack_from("<24H",plain)) & 0xffff
    struct.pack_into("<H",raw,28,checksum)
    for off in range(0,SECURE_SIZE,4):
        word=struct.unpack_from("<I",plain,off)[0]^(personality^otid)
        struct.pack_into("<I",raw,SECURE_OFFSET+off,word)
    return bytes(raw)

def self_test():
    for i in range(24):
        for species in STARTERS:
            r=decode_mon(synthetic_mon(species,i))
            assert r["checksum_valid"] and r["species"]==species and r["level"]==5, (i,species,r)
    empty=bytes(POKEMON_SIZE)
    for species in STARTERS:
        party=decode_party(synthetic_mon(species,19)+empty*5)
        assert validate_starter(party,species)
    try:
        validate_starter(decode_party(empty*6),133)
    except AssertionError:
        pass
    else:
        raise AssertionError("Empty party must fail")
    print("PASS: 72 starter/ordering fixtures, checksum and empty-party rejection")

if __name__=="__main__":
    ap=argparse.ArgumentParser()
    ap.add_argument("--self-test",action="store_true")
    ap.add_argument("--party-ram",type=Path)
    ap.add_argument("--expect",choices=["eevee","pichu","ditto"])
    args=ap.parse_args()
    if args.self_test:
        self_test()
    else:
        if not args.party_ram or not args.expect:
            ap.error("Provide --party-ram FILE and --expect SPECIES")
        party=decode_party(args.party_ram.read_bytes())
        target={"eevee":133,"pichu":172,"ditto":132}[args.expect]
        validate_starter(party,target)
        print(json.dumps({"result":"PASS","starter":args.expect,"party":party},indent=2))
