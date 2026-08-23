# gbdk-basic-text
GBDK Basic Text

## Requirements
- Windows 11 or Ubuntu 24.04
- GBDK-2020 >= 4.5.0
- CMake >= 4.2.1
- GNU Make >= 4.4.1

**TIPS:**
- **Windows:** Use [Chocolatey](https://community.chocolatey.org/) to install dependencies: `choco install cmake make`
- **Ubuntu:** Use apt to install dependencies: `sudo apt install cmake make`

## Build Instructions

### Prerequisites
Edit `CMakeLists.txt` and set `GBDK_HOME` to point to your extracted GBDK path.

Examples:
- **Windows:** Extract GBDK-2020 to `C:\gbdk` and set `set(GBDK_HOME "C:/gbdk")`
- **Ubuntu:** Extract GBDK-2020 to `~/gbdk` and set `set(GBDK_HOME "~/gbdk")`

### Quick Build

**Windows (PowerShell):**
```powershell
.\build.ps1
```

Optional flags:
- `-clean` - Clean build artifacts before building
- `-debug` - Build in debug mode

Example:
```powershell
.\build.ps1 -clean -debug
```

**Ubuntu (Bash):**
```bash
./build.sh
```

Optional flags:
- `--clean` - Clean build artifacts before building
- `--debug` - Build in debug mode

Example:
```bash
./build.sh --clean --debug
```

This will generate `rom.gb` in the `build` directory, which can be loaded into an emulator or flashcart.

### Manual Build
To build manually using CMake (works on both Windows and Ubuntu):

```bash
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
make
cd ..
```

Use `-DCMAKE_BUILD_TYPE=Debug` for debug build.

## Generate Graphics Assets

To generate assets file from png we use png2asset, here are the commands we use:

```
C:\gbdk\bin\png2asset.exe Font.png -keep_palette_order -tiles_only -spr8x8 -sprite_no_optimize -keep_duplicate_tiles
```

## Resources
- GBDK: https://github.com/gbdk-2020/gbdk-2020
- png2asset docs: https://gbdk.org/docs/api/docs_toolchain_settings.html#png2asset-settings
- Basic Text Tutorial: https://laroldsretrogameyard.com/tutorials/gb/drawing-text-in-game-boy-games/
- Font graphics assets: https://github.com/LaroldsJubilantJunkyard/drawing-basic-text
