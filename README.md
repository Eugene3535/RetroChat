Simple server-client retro-style application

In order to compile this project you will need to:

have CMake installed(https://cmake.org);
have any generator(like MSVS or MinGW);

mkdir external
cd external
git clone --branch 2.5.1 https://github.com/SFML/SFML.git
git clone --branch release-1.3.8 https://github.com/fltk/fltk.git
cd ..
mkdir build
cd build
cmake ..
cmake --build . --config Release
 
