# GuideAlignment
GuideAlignment is, as the name suggests, a multiple sequence alignment tool for proteins based on a guide tree.
It uses the blosum62 matrix, but the matrices that can be used will be expanded in the future.


# Build the program 
Dependencies: cmake and [Boost](https://www.boost.org)
To build the project and obtain an executable simply do

``` bash 
mkdir build
cd build 
cmake ..
cmake --build .
```
An executable named "GuideAlignment" will be present in the build folder.