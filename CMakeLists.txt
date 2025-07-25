cmake_minimum_required(VERSION 3.22)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(fvec LANGUAGES CXX)

set(LICENCES
	LICENSE
)

add_executable(fvectest
	frentest.cpp
	fren.hpp
	frenmath.hpp
)

if(WIN32)
	find_library(SDL2MAIN_LIBRARY NAMES SDL2main PATHS "$ENV{VULKAN_SDK}/Lib")
	find_library(SDL2_LIBRARY NAMES SDL2 PATHS "$ENV{VULKAN_SDK}/Lib" )

endif()

if(UNIX)
	find_library(SDL2MAIN_LIBRARY SDL2main)
	find_library(SDL2_LIBRARY SDL2)
endif()



target_compile_features(fvectest PUBLIC cxx_std_20)
set_target_properties(fvectest PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(fvectest ${SDL2MAIN_LIBRARY} ${SDL2_LIBRARY})
