
set(target symenglib)
message(STATUS "Lib ${target}")


# External libraries

# e.g., find_package(THIRDPARTY REQUIRED)


# Includes

#include_directories(
    # e.g., ${TRDP_INCLUDE_DIR}
#)

include_directories(
    BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/symenglib
)


# Libraries

set(libs
    # e.g., ${THIRDPARTY_LIBRARY}
)


# Compiler definitions

if (OPTION_BUILD_STATIC)
    add_definitions("-D${META_PROJECT_NAME_UPPER}_STATIC")
else()
    add_definitions("-DSYMENGLIB_EXPORTS")
endif()


# Sources

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(api_includes
     ${include_path}/err.h
     ${include_path}/gsi.h
     ${include_path}/misc.h
     ${include_path}/msf.h
     ${include_path}/pdb.h
     ${include_path}/pdb_info.h
     ${include_path}/sym.h
     ${include_path}/tpi.h
     ${include_path}/symenglib_api.h
)

set(sources
    ${source_path}/err.cpp
    ${source_path}/gsi.cpp
    ${source_path}/misc.cpp
    ${source_path}/msf.cpp
    ${source_path}/pdb.cpp
    ${source_path}/sym.cpp
    ${source_path}/tpi.cpp
    
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${api_includes})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})


# Build library

add_library(${target} ${api_includes} ${sources})

target_link_libraries(${target} ${libs} ${Boost_LIBRARIES})
target_compile_options(${target} PRIVATE ${DEFAULT_COMPILE_FLAGS})

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH	            ${include_path})


# Deployment

# Library
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)

if (WIN32)
  install(TARGETS Medusa RUNTIME DESTINATION .)
  file(GLOB boost_system_dll     "${Boost_LIBRARY_DIRS}/boost_system-*-mt-1*.dll")
  file(GLOB boost_filesystem_dll "${Boost_LIBRARY_DIRS}/boost_filesystem-*-mt-1*.dll")
  install(FILES "${boost_system_dll}" "${boost_filesystem_dll}" DESTINATION .)
endif ()

# Header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})
