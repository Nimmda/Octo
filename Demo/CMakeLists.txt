# Add executable called "demo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (demo main.cpp)

# Link the executable to the Octo library. Since the Octo library has
# public include directories we will use those link directories when building
# demo
target_link_libraries (demo LINK_PUBLIC Octo)