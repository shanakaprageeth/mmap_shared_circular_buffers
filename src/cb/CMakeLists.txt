# include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Output library name
set(lib_name cb)

# set any additional libraries needed
set(libraries
)

# search for CPP files to build
file(GLOB cpp_files RELATIVE
     "${CMAKE_CURRENT_SOURCE_DIR}"
     "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp"
)

# setup a static library as build output
add_library(${lib_name} ${cpp_files})

# set dependant libraries for linker
target_link_libraries(${lib_name}
  ${libraries}
)

# add Library to the project libraries list
set(src_libs ${src_libs} ${lib_name})
set(src_libs ${src_libs} PARENT_SCOPE)
