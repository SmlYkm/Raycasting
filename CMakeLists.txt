cmake_minimum_required(VERSION 3.10)
project(Raycasting)

###############################################################################
## source files ###############################################################
###############################################################################

# Manually list your engine files
set(sources_engine
    engine/src/math/utils.cpp
    engine/src/math/Trig.cpp
    engine/src/math/FixedPointInt.cpp
)

# Manually list your game/app files
set(sources
    src/main.cpp
)

###############################################################################
## target definitions #########################################################
###############################################################################

add_executable(Raycasting ${sources} ${sources_engine})

target_compile_features(Raycasting PUBLIC cxx_std_14)
target_compile_options(Raycasting PRIVATE -Wall -Wextra -Wfloat-conversion)
add_compile_options(-fdiagnostics-color=always)

target_include_directories(Raycasting PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/include
)