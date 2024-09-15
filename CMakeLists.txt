cmake_minimum_required(VERSION 3.20)

project(skifri_sln CXX)

add_subdirectory("external/rusty_audio")
add_subdirectory("external/nothofagus")

file(GLOB_RECURSE HEADERS "source/*.h" "include/*.h")

add_executable(skifri
    "source/piano.cpp"
    "source/main.cpp"

    ${HEADERS}
)

set_property(TARGET skifri PROPERTY CXX_STANDARD 20)
target_include_directories(skifri PRIVATE 
    "include"
    ${RUSTY_AUDIO_INCLUDE}
    ${NOTHOFAGUS_INCLUDE}
)
target_link_libraries(skifri PRIVATE rusty_audio nothofagus)