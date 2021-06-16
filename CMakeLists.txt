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


# Set target properties for various platforms
set_target_properties(oto-aliaser PROPERTIES
  MACOSX_BUNDLE TRUE
  MACOSX_BUNDLE_ICON_FILE "icon.icns"
  MACOSX_BUNDLE_SHORT_VERSION_STRING "${oto-aliaser_VERSION_MAJOR}.${oto-aliaser_VERSION_MINOR}"
  MACOSX_BUNDLE_LONG_VERSION_STRING "${oto-aliaser_VERSION_MAJOR}.${oto-aliaser_VERSION_MINOR}.${oto-aliaser_VERSION_PATCH}"
  MACOSX_BUNDLE_BUNDLE_VERSION "${oto-aliaser_VERSION_MAJOR}.${oto-aliaser_VERSION_MINOR}.${oto-aliaser_VERSION_PATCH}"
  MACOSX_BUNDLE_COPYRIGHT "Copyright (c) 2021 Corwin Hansen"
  MACOSX_BUNDLE_INFO_STRING "${oto-aliaser_VERSION_MAJOR}.${oto-aliaser_VERSION_MINOR}.${oto-aliaser_VERSION_PATCH}, Copyright 2021 Corwin Hansen"
  WIN32_EXECUTABLE TRUE
  C_STANDARD 99)


  # Add install targets
  install (TARGETS oto-aliaser DESTINATION bin)
  install (FILES ${HeaderFiles} DESTINATION include)


# Packaging
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VENDOR "Corwin Hansen")
include (CPack)
