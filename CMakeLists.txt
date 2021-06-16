cmake_minimum_required (VERSION 3.0.2)

# Basic project setup
cmake_policy(SET CMP0048 NEW)
project (oto-aliaser VERSION 0.1.1)


if(CMAKE_COMPILER_IS_GNUCXX) # add debug warnings for gcc
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)


# Find source files
FILE(GLOB_RECURSE SourceFiles src/*.c)
FILE(GLOB_RECURSE HeaderFiles src/*.h)



# Create the executable
include_directories ("${PROJECT_SOURCE_DIR}/src")
add_executable (oto-aliaser ${SourceFiles})





# Add install targets
install (TARGETS oto-aliaser DESTINATION bin)
install (FILES ${HeaderFiles} DESTINATION include)
