cmake_minimum_required(VERSION 3.20)

project(skifri_sln CXX)

add_subdirectory("external/rusty_audio")
add_subdirectory("external/nothofagus")

file(GLOB_RECURSE HEADERS "source/*.h" "include/*.h")
# file(GLOB_RECURSE RESOURCES "resources/data/*")

add_executable(skifri
    "source/piano.cpp"
    "source/main.cpp"
    "source/game.cpp"
    "source/entity/entity.cpp"
    "source/entity/animated_entity.cpp"
    "source/entity/static_entity.cpp"
    "source/entity/ramp.cpp"
    "source/entity/tree.cpp"
    "source/entity/player.cpp"
    
    ${HEADERS}
)

set_property(TARGET skifri PROPERTY CXX_STANDARD 20)
target_include_directories(skifri PRIVATE 
    "include"
    ${RUSTY_AUDIO_INCLUDE}
    ${NOTHOFAGUS_INCLUDE}
)

# foreach(resource ${RESOURCES})
#     get_filename_component(resource_name ${resource} NAME)
#     configure_file(${resource} ${CMAKE_CURRENT_BINARY_DIR}/resources/${resource_name} COPYONLY)
# endforeach(resource ${RESOURCES})


target_link_libraries(skifri PRIVATE rusty_audio nothofagus)