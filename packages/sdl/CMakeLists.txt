set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH};${EXTERNALS_DIR}")

set(SDL2_ROOT "" CACHE PATH
  "The location of the SDL2 install prefix (only used if SDL2 is not yet found)")
if(SDL2_ROOT)
  message(SDL ROOT FOUND)
  set(CMAKE_PREFIX_PATH ${SDL2_ROOT} ${CMAKE_PREFIX_PATH})
elseif(MSVC)
  set(CMAKE_PREFIX_PATH externals/msvc ${CMAKE_PREFIX_PATH})
elseif(MINGW)
  message(MINGW?)
  set(CMAKE_PREFIX_PATH externals/mingw ${CMAKE_PREFIX_PATH})
endif()

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

message(SDL2_INCLUDE_DIR ${SDL2_INCLUDE_DIR})

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

set(THREE_PACKAGE_SDL_LIBS ${THREE_LIB} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${SDLMAIN_LIBRARY})

# Copy SDL runtime on Windows
if (MSVC OR MINGW)
  get_filename_component(SDL2_PATH ${SDL2MAIN_LIBRARY} PATH)
  set(SDL2_RUNTIME_LIBRARY "${SDL2_PATH}/SDL2.dll" CACHE INTERNAL "" FORCE)
  message (STATUS "Copying ${SDL2_RUNTIME_LIBRARY} to ${THREE_BINARY_PATH} \n")
  set(THREE_DEPENDS three_depends)
  if (MSVC)
    #add_custom_command(
    add_custom_target(
      ${THREE_DEPENDS}
      COMMAND ${CMAKE_COMMAND} -E make_directory "${THREE_BINARY_PATH}/$<CONFIGURATION>"
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_RUNTIME_LIBRARY} "${THREE_BINARY_PATH}/$<CONFIGURATION>"
      COMMENT "Copying ${SDL2_RUNTIME_LIBRARY}")
  else()
    add_custom_target(
      ${THREE_DEPENDS}
      COMMAND ${CMAKE_COMMAND} -E make_directory ${THREE_BINARY_PATH}
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDL2_RUNTIME_LIBRARY} "${THREE_BINARY_PATH}"
      COMMENT "Copying ${SDL2_RUNTIME_LIBRARY}")
  endif()
endif()

file(GLOB THREE_PACKAGE_SDL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/impl/*.cpp)
file(GLOB THREE_PACKAGE_SDL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

set(THREE_PACKAGE_SDL_SOURCE_FILES ${THREE_PACKAGE_SDL_SOURCES} ${THREE_PACKAGE_SDL_HEADERS})

add_library(three_package_sdl ${THREE_PACKAGE_SDL_SOURCE_FILES})
target_link_libraries(three_package_sdl ${THREE_PACKAGE_SDL_LIBS})

set_target_properties(three_package_sdl PROPERTIES COMPILE_FLAGS "${THREE_CXX_FLAGS}")

set(THREE_PACKAGE_SDL_LIBS ${THREE_PACKAGE_SDL_LIBS} three_package_sdl)

link_if_needed(three_package_sdl)

if(WIN32 AND MSVC)
  set_target_properties(three_package_sdl PROPERTIES DEBUG_OUTPUT_NAME ${three_package_sdl}${CMAKE_DEBUG_POSTFIX}
                                            RELEASE_OUTPUT_NAME ${three_package_sdl}${CMAKE_RELEASE_POSTFIX})
endif(WIN32 AND MSVC)

if(THREE_DEPENDS)
  add_dependencies(three_package_sdl ${THREE_DEPENDS})
endif()
