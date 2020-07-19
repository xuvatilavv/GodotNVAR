GodotNVAR is a wrapper for the [NVIDIA VRWorks Audio](https://developer.nvidia.com/vrworks/vrworks-audio) library for raytraced 3D audio.

### To use:

A starter project that shows the basic structure for how to set up a Godot project with this library can be found in the `example` directory. The files included are built for 64-bit Godot 3.2.2 on Windows.

### To compile this library:

Instructions for setting up your build environment can be found in the [godot compilation guide](https://docs.godotengine.org/en/stable/development/compiling/index.html), and a thorough guide on how to compile a GDNative library can be found in the [godot-cpp](https://github.com/godotengine/godot-cpp) readme. Here's some quick simplified instructions for x64 Windows:

1. From a terminal, download the repo with git. Use the `--recursive` flag to also download the necessary submodules.

        git clone --recursive [repo_link]

2. Compile the Godot C++ bindings library.

        cd GodotNVAR/godot-cpp
        scons platform=<target-platform> generate_bindings=yes -j6

The resulting library will be created in `godot-cpp/bin/`, and will differ according to your selected platform.

3. Compile the GodotNVAR GDNative library. These commands need to be run from `x64 Native Tools Command Prompt for VS 2019`, or the similar environment for your platform and installation.

        cd GodotNVAR
        cl /Fosrc/GodotNVAR.obj /c src/GodotNVAR.cpp /nologo -EHsc -DNDEBUG /MDd /Igodot-cpp\include /Igodot-cpp\include\core /Igodot-cpp\include\gen /Igodot-cpp\godot_headers /Iinclude
        link /nologo /dll /out:bin\GodotNVAR.dll /implib:bin\GodotNVAR.lib src\GodotNVAR.obj lib\nvar.lib godot-cpp\bin\<godot-cpp-bindings>

You'll need to replace `<godot-cpp-bindings>` with the name of the file that was created in the previous step. For your release build, replace /MDd with /MD to create a binary without debug symbols which will run faster and be smaller.

This creates the file `GodotNVAR.dll` in your GodotNVAR/bin directory, which can then be added into Godot as a GDNative library.