# Create a library called "Octo" which includes the source file "Octo.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (Octo Application.cpp)


INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(Octo ${SDL2_LIBRARIES})


# Make sure the compiler can find include files for our Octo library
# when other libraries or executables link to Octo
target_include_directories (Octo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
