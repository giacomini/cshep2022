cmake_minimum_required(VERSION 3.16)
project(examples VERSION 0.1.0)

find_package(TBB REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

string(APPEND CMAKE_CXX_FLAGS_DEBUG
       " -fsanitize=address -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG
       " -fsanitize=address -fno-omit-frame-pointer")

#find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if(CMAKE_CXX_CPPCHECK)
  list(APPEND CMAKE_CXX_CPPCHECK "--enable=warning" "--inconclusive" "--force"
       "--inline-suppr")
endif()

#find_program(CMAKE_CXX_CLANG_TIDY NAMES clang-tidy)
if(CMAKE_CXX_CLANG_TIDY)
  list(
    APPEND
    CMAKE_CXX_CLANG_TIDY
    -checks=-*,cppcoreguidelines-*,-cppcoreguidelines-avoid-magic-numbers,-cppcoreguidelines-narrowing-conversions,modernize-*,-modernize-use-trailing-return-type
  )
endif()

add_executable(algo algo.cpp)
add_executable(algo_solution algo_solution.cpp)

add_executable(algo_functions algo_functions.cpp)
add_executable(algo_functions_solution algo_functions_solution.cpp)

add_executable(race race.cpp)
add_executable(race_solution race_solution.cpp)

add_executable(false_sharing false_sharing.cpp)
add_executable(false_sharing_solution false_sharing_solution.cpp)

add_executable(privatization privatization.cpp)
add_executable(privatization_solution privatization_solution.cpp)

add_executable(parallel_for parallel_for.cpp)
target_link_libraries(parallel_for TBB::tbb)

add_executable(parallel_reduce parallel_reduce.cpp)
target_link_libraries(parallel_reduce TBB::tbb)

add_executable(parallel_reduce_explicit parallel_reduce_explicit.cpp)
target_link_libraries(parallel_reduce_explicit TBB::tbb)

# add_executable(mandelbrot_sfml_par main_par.cpp)
# target_link_libraries(mandelbrot_sfml_par PRIVATE TBB::tbb sfml-graphics)
