# Sam Edition Local Build Procedure (ENV-002)

This document defines the reproducible local build/toolchain procedure for Pokémon: Sam Edition.

## 1. Supported reference environment

The verified project environment is:

- Windows host
- WSL2
- Ubuntu 24.04 LTS, x86_64
- Git
- GNU Make
- GCC/G++
- `binutils-arm-none-eabi`
- `libpng-dev`
- pret/agbcc
- Sam Edition repository: `InternetNinjacy/pokefirered`

The original successful local setup used a Linux-side working directory under `~/pokemon-sam`. Keeping the repository inside the WSL/Linux filesystem is the reference layout for this procedure.

## 2. Install prerequisites

Open WSL and run:

```bash
sudo apt update
sudo apt install -y build-essential binutils-arm-none-eabi git libpng-dev
```

Confirm the important tools are available:

```bash
git --version
make --version | head -n 1
gcc --version | head -n 1
arm-none-eabi-as --version | head -n 1
arm-none-eabi-ar --version | head -n 1
```

Known failure mode: building agbcc without `binutils-arm-none-eabi` causes failures such as `arm-none-eabi-as: not found` and `arm-none-eabi-ar: not found`.

## 3. Create the working directory

```bash
cd ~
mkdir -p pokemon-sam
cd pokemon-sam
```

Reference layout after setup:

```text
~/pokemon-sam/
├── pokefirered/
└── agbcc/
```

## 4. Clone the Sam Edition repository

```bash
git clone https://github.com/InternetNinjacy/pokefirered.git
cd pokefirered
git fetch origin
git checkout sam-edition-dev
git pull --ff-only origin sam-edition-dev
```

Verify the checkout before doing any implementation work:

```bash
git rev-parse HEAD
git status --short --branch
```

At the ENV-002 documentation checkpoint, `sam-edition-dev` was observed at:

```text
1ac7382fd5ecb34cb2de6bdf5bba8e7fcf08e869
```

The branch name is the continuing integration target. The recorded SHA is a checkpoint for diagnosing environment drift, not an instruction to permanently pin all future work to that commit.

Do not use an obsolete or quarantined implementation branch as the ancestor for new Sam Edition work.

## 5. Build and install agbcc

Return to the parent directory:

```bash
cd ~/pokemon-sam
git clone https://github.com/pret/agbcc.git
cd agbcc
./build.sh
./install.sh ../pokefirered
```

If `agbcc` already exists and was built successfully in the same environment:

```bash
cd ~/pokemon-sam/agbcc
./install.sh ../pokefirered
```

If the compiler was built in a different terminal/environment, clean and rebuild it first:

```bash
cd ~/pokemon-sam/agbcc
git clean -fX
./build.sh
./install.sh ../pokefirered
```

## 6. Build Sam Edition

```bash
cd ~/pokemon-sam/pokefirered
git status --short --branch
make
```

A successful build produces:

```text
pokefirered.gba
```

For a clean rebuild:

```bash
make clean
make
```

Parallel builds are optional:

```bash
make -j"$(nproc)"
```

## 7. Record the build identity

For any build used for QA, record:

```bash
git rev-parse HEAD
git status --short --branch
sha1sum pokefirered.gba
```

The QA record should contain:

- branch name;
- commit SHA;
- whether the working tree was clean;
- ROM SHA-1;
- date of the build;
- host/WSL distribution used.

This makes a reported runtime result traceable to the exact source state that produced it.

## 8. Sam Edition compare warning

Do not use vanilla byte-for-byte comparison as the sole success criterion for a modified Sam Edition build.

The project has intentional data and engine changes, so a CI or local `COMPARE=1` / `make compare` failure can be expected solely because the generated ROM no longer matches vanilla FireRed.

A build is considered a compiler/build success when the normal build completes and produces `pokefirered.gba` without a genuine compiler, assembler, linker, or source-generation error.

Comparison failures still need inspection: do not dismiss unrelated compiler or source errors just because vanilla comparison is expected to differ.

## 9. Runtime handoff

ENV-002 establishes the reproducible build/toolchain path. Runtime behavior is a separate QA gate.

Before beginning runtime QA:

1. build from the intended Sam Edition branch;
2. record the branch, commit, working-tree state, and ROM SHA-1;
3. launch that exact ROM in the chosen GBA test emulator;
4. preserve the resulting save file with the QA record when testing persistent-state architecture.

The project records reviewed for ENV-002 do not establish a single mandatory emulator, so this document does not invent one. The emulator used for a QA run should be recorded alongside the ROM identity.

## 10. Minimum ENV-002 completion check

ENV-002 is reproducible when a fresh WSL2 Ubuntu environment can:

1. install the documented prerequisites;
2. clone the Sam Edition repository;
3. check out `sam-edition-dev`;
4. build and install `agbcc`;
5. run `make` successfully;
6. produce `pokefirered.gba`;
7. record the exact source and ROM identity used for QA.

Once this procedure has been reproduced successfully, ARCH-002 can use the resulting ROM for the compensated `SaveBlock1` / `SamEditionSaveData` runtime validation.

## 11. Reproduction record

ENV-002 was independently reproduced on October 1, 2026 using a fresh GitHub-hosted `ubuntu-24.04` runner.

Reproduction source:

- Documentation branch: `env-002-reproducible-build-docs`
- Source commit tested: `073b0d94febca2bb0f17600f50c609c56522d9a0`
- Clean-reproduction workflow run: `36853460035`

Every acceptance step completed successfully:

1. clean Ubuntu 24.04 host started;
2. documented prerequisites installed successfully;
3. Sam Edition repository cloned fresh;
4. documentation branch checked out successfully;
5. `pret/agbcc` cloned, built, and installed successfully;
6. project `make` completed successfully;
7. `pokefirered.gba` existed after the build;
8. the ROM and source-identity records were uploaded as the `env-002-clean-reproduction` workflow artifact.

Result: **ENV-002 reproducibility gate PASSED.**
