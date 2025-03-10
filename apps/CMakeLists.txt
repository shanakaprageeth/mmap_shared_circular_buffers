include_directories(${CMAKE_SOURCE_DIR}/include)

# dependant libraries
set(libraries ${src_libs})

# setup CPPs to create the executable
# Add the executable for the master application
add_executable(master_app master.c)

# Add the executable for the slave application
add_executable(slave_app slave.c)

# Add required linker libraries
target_link_libraries(master_app
  ${libraries}
)
target_link_libraries(slave_app
  ${libraries}
)

# set the build output directory
set_target_properties(master_app
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/apps"
)

set_target_properties(slave_app
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/apps"
)
