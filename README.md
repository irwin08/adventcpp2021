# adventcpp2021
Advent of Code 2021 Attempt in C++

To build do the following:

````
cd adventcpp2021
mkdir build
cd build
cmake .. -G "Generator of Choice"
make
````
Last command only applies if you're using make as the underlying build system.

To add a day, create a "dayX" folder, add

````
add_subdirectory("dayX")
````
to the top-level CMakeLists.txt file
and in the "dayX" folder create a CMakeLists.txt that is similar to the CMakeLists.txt files in other existing sub-directories.
