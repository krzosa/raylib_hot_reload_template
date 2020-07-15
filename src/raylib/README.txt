---------------------------------------------------------------------------------------
Welcome to raylib 3.0
---------------------------------------------------------------------------------------

raylib is a simple and easy-to-use library to enjoy videogames programming.

raylib is highly inspired by Borland BGI graphics lib and by XNA framework and it's specially well suited for prototyping, tooling, graphical applications, embedded systems and education.

NOTE for ADVENTURERS: raylib is a programming library to enjoy videogames programming; 
no fancy interface, no visual helpers, no auto-debugging... just coding in the most pure spartan-programmers way.

Ready to learn? Jump to code examples!

---------------------------------------------------------------------------------------
features
---------------------------------------------------------------------------------------

  - NO external dependencies, all required libraries are bundled into raylib
  - Multiple platforms supported: Windows, Linux, MacOS, Android, HTML5... and more!
  - Written in plain C code (C99) in PascalCase/camelCase notation
  - Hardware accelerated with OpenGL (1.1, 2.1, 3.3 or ES 2.0)
  - Unique OpenGL abstraction layer (usable as standalone module): rlgl
  - Multiple Fonts formats supported (TTF, XNA fonts, AngelCode fonts)
  - Outstanding texture formats support, including compressed formats (DXT, ETC, ASTC)
  - Full 3D support, including 3D Shapes, Models, Billboards, Heightmaps and more!
  - Flexible Materials system, supporting classic maps and PBR maps
  - Animated 3D models supported (skeletal bones animation)
  - Shaders support, including model and postprocessing shaders.
  - Powerful math module for Vector, Matrix and Quaternion operations: raymath
  - Audio loading and playing with streaming support (WAV, OGG, MP3, FLAC, XM, MOD)
  - VR stereo rendering support with configurable HMD device parameters
  - Huge examples collection with +115 code examples!
  - Bindings to +40 programming languages!
  
 > Notes on specific platform libraries:
  
raylib uses on its core module the outstanding GLFW3 library, embedded in the form of rglfw module, to avoid external dependencies.

raylib uses on its raudio module, the amazing miniaudio library to support multiple platforms and multiple audio backends.

raylib uses internally several single-file header-only libraries to support different fileformats loading and saving, 
all those libraries are embedded with raylib and available in src/external directory. Check raylib Wiki for a detailed list.

On Android platform, native_app_glue module (provided by Android NDK) and native Android libraries are used to manage window/context, inputs and activity life cycle.

On Raspberry Pi platform (native mode), Videocore API and EGL libraries are used for window/context management. 
Inputs are processed using evdev Linux libraries

On Web platform, raylib uses emscripten provided libraries for several input events management, specially noticeable the touch events support.

---------------------------------------------------------------------------------------
build and installation
---------------------------------------------------------------------------------------

raylib binary releases for Windows, Linux and macOS are available at the Github Releases page.

raylib is also available via multiple package managers on multiple OS distributions.

 > Installing and building raylib via vcpkg
You can download and install raylib using the vcpkg dependency manager:

  git clone https://github.com/Microsoft/vcpkg.git
  cd vcpkg
  ./bootstrap-vcpkg.sh
  ./vcpkg integrate install
  vcpkg install raylib
  
The raylib port in vcpkg is kept up to date by Microsoft team members and community contributors. 
If the version is out of date, please create an issue or pull request on the vcpkg repository.

 > Building raylib on multiple platforms

raylib Wiki (https://github.com/raysan5/raylib/wiki) contains detailed instructions on building and usage on multiple platforms.

Note that Wiki is open for edit, if you find some issue while building raylib for your target platform, feel free to edit the Wiki or open and issue related to it.

 > Using raylib with multiple IDEs
 
raylib has been developed on Windows platform using Notepad++ and MinGW GCC compiler but it can be used with other IDEs on multiple platforms.

GitHub projects directory (https://github.com/raysan5/raylib/tree/master/projects) contains several ready-to-use project templates to build raylib and code examples with multiple IDEs.

Note that there are lots of IDEs supported, some of the provided templates could require some review, please, if you find some issue with some template or you think they could be improved, feel free to send a PR or open a related issue.

---------------------------------------------------------------------------------------
contact
---------------------------------------------------------------------------------------

  - Webpage: http://www.raylib.com
  - Discord: https://discord.gg/raylib
  - Twitter: http://www.twitter.com/raysan5
  - Twitch: http://www.twitch.tv/raysan5
  - Reddit: https://www.reddit.com/r/raylib
  - Patreon: https://www.patreon.com/raylib
  - YouTube: https://www.youtube.com/channel/raylib

If you are using raylib and enjoying it, please, join our Discord server and let us know! :)

---------------------------------------------------------------------------------------
license
---------------------------------------------------------------------------------------

raylib is licensed under an unmodified zlib/libpng license, which is an OSI-certified, 
BSD-like license that allows static linking with closed source software. 
Check LICENSE.txt for further details.
