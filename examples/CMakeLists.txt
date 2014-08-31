# Locate necessary headers/libraries

set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};${EXTERNALS_DIR}")
set(CMAKE_PREFIX_PATH ${EXTERNALS_DIR}/rapidjson ${CMAKE_PREFIX_PATH})

set(SDL2_ROOT "" CACHE PATH
  "The location of the SDL2 install prefix (only used if SDL2 is not yet found)")
if(SDL2_ROOT)
  set(CMAKE_PREFIX_PATH ${SDL2_ROOT} ${CMAKE_PREFIX_PATH})
elseif(MSVC)
  set(CMAKE_PREFIX_PATH ${EXTERNALS_DIR}/sdl2-2.0.3/msvc ${CMAKE_PREFIX_PATH})
elseif(MINGW)
  set(CMAKE_PREFIX_PATH ${EXTERNALS_DIR}/sdl2-2.0.3/mingw ${CMAKE_PREFIX_PATH})
endif()

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(RapidJSON REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${RAPID_JSON_INCLUDE_DIR})

set(THREE_EXAMPLE_DEP_LIBS three three_package_sdl)

## TODO: Remove hard-wired data directory path
set(THREE_RELEASE_BUILD FALSE CACHE BOOL
  "Whether to compile examples for installation (changes data dir from absolute to relative reference")
set(DATA_DIR ${CMAKE_HOME_DIRECTORY}/data)
if (THREE_RELEASE_BUILD)
  add_definitions(-DTHREE_DATA_DIR=".")
else()
  add_definitions(-DTHREE_DATA_DIR="${DATA_DIR}")
endif()

#############

file(GLOB_RECURSE THREE_EXAMPLES_LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/extras/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/controls/*.cpp)
file(GLOB_RECURSE THREE_EXAMPLES_LIB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/extras/*.h ${CMAKE_CURRENT_SOURCE_DIR}/controls/*.h)
set(THREE_EXAMPLES_LIB_SOURCE_FILES ${THREE_EXAMPLES_LIB_SOURCES} ${THREE_EXAMPLES_LIB_HEADERS})
three_add_static_library(three_examples ${THREE_EXAMPLES_LIB_SOURCE_FILES})
set_target_properties(three_examples PROPERTIES COMPILE_FLAGS "${THREE_CXX_FLAGS}")
target_link_libraries(three_examples ${THREE_EXAMPLE_DEP_LIBS})

set(THREE_EXAMPLE_LIBS ${THREE_EXAMPLE_DEP_LIBS} three_examples)

file(GLOB examples "*.cpp")

foreach(example ${examples})
  get_filename_component(example_name ${example} NAME_WE)
  three_add_example(${example_name} ${example})
  set_target_properties(${example_name} PROPERTIES COMPILE_FLAGS "${THREE_CXX_FLAGS}")
endforeach()

