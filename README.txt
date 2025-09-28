
# Prizoop CG-100 patch for the GitHub repo (last commit ~5y ago)

Use this if you're cloning https://github.com/tswilliamson/prizoop at that commit.

## Steps
1) Clone the repo: `git clone https://github.com/tswilliamson/prizoop`
2) Drop these files at the **repo root** (this adds a CMake/fxSDK build alongside the original Makefile).
3) Build:
```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=$FXSDK/cmake/toolchain.cmake -DFXSDK_PLATFORM=fxcg ..
make -j
```
Output: `build/prizoop_cg100.g3a`

## Notes
- The CMake config automatically includes `src/*.c*` and excludes Windows simulator files.
- Memory policy aims to keep usage under ~2 MB; adjust in `cmake/mem_cfg.h` if needed.
