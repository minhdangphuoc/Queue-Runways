# Queue-Runways 🛫🛬
- This is a repository for airport simulation using Queues data structure.
- The source code was made for 5G00DM61-3003 Programming Languages 3.

## Concept
 
## Requirements

## Manual
This project using meson to build, so you have to download and install it to your computer.
[Meson Build](https://mesonbuild.com/)

### Build
``` cli
meson build //  Initialize the build
cd build // Move to build dirrectory
ninja && ./main // Run built
///Fast build and run
meson build && ninja -C build && ./build/main
```


### Change name of built
Change this code in meson.build for changing the name.
```
// meson.build
...
executable('main', './/src//main.cpp', link_with : lib) // change main to another name
...
```
## Issues
