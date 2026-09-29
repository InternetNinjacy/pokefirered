#!/usr/bin/env python3
from pathlib import Path
import base64, io, zipfile

ROOT = Path(__file__).resolve().parents[2]
HERE = Path(__file__).resolve().parent
parts = sorted(HERE.glob("payload.part*"))
if not parts:
    raise SystemExit("League Phase 5 payload parts are missing.")
encoded = "".join(p.read_text().strip() for p in parts)
data = base64.b64decode(encoded)
with zipfile.ZipFile(io.BytesIO(data)) as z:
    z.extractall(ROOT)
print(f"Installed League Phase 5 binary payload from {len(parts)} parts.")
