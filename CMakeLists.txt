cmake_minimum_required(VERSION 3.0.0)
project(myrt)

# INCLUDES
# project-specific includes
include_directories(src)
# myrt-math as a submodule
include_directories(submodules/myrt-math/include)

# SOURCES
# for now add everything
file(GLOB SOURCES "src/*.cpp")

# COMPILER OPTIONS
set(CXXFLAGS -std=c++1z -O3 -Weffc++)

# MAIN EXECUTABLE
add_executable(myrt ${SOURCES})
target_compile_options(myrt PUBLIC ${CXXFLAGS})
