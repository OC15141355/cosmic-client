# Client Build — Windows

Status: **Not yet tested.** The codebase is cross-platform (GLFW/OpenGL/ASIO) and should build on Windows with MinGW or MSVC, but this has not been verified.

## Expected Steps

1. Install dependencies (vcpkg or manual):
   - GLFW3, FreeType, LZ4, ASIO

2. Build with CMake:
   ```cmd
   mkdir build && cd build
   cmake -G "Visual Studio 17 2022" ..
   cmake --build . --config Release
   ```

3. Copy NX files and fonts/ into the build directory.

## TODO

- [ ] Test MSVC compilation
- [ ] Test MinGW compilation
- [ ] Document any Windows-specific fixes needed
- [ ] Create GitHub Actions CI for Windows builds
