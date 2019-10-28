  
project(Sieve_of_Atkin)


set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

set(CMAKE_CXX_STANDARD 11)

add_executable(Sieve_of_Atkin main.cpp sieveOfAtkin.cpp sieveOfAtkin.h)