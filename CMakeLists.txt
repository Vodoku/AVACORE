# ################################################################################
#                              Top-Level Settings 
# ################################################################################

# CMake version must be greater than 2.8.11 
# --------------------------------------------------------------------------------
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11 FATAL_ERROR) 

# CMake project name 
# --------------------------------------------------------------------------------
PROJECT(AVACORE)

# CMake Project version
# --------------------------------------------------------------------------------
SET(AVACORE_VERSION_MAJOR 1)
SET(AVACORE_VERSION_MINOR 0)
SET(AVACORE_VERSION_PATCH 0) 
STRING(CONCAT AVACORE_VERSION "${AVACORE_VERSION_MAJOR}."
                    "${AVACORE_VERSION_MINOR}."
                    "${AVACORE_VERSION_PATCH} ")

# CMake Default Variables 
# --------------------------------------------------------------------------------
SET(CMAKE_INCLUDE_CURRENT_DIR ON) 
SET(CMAKE_AUTOMOC ON) 

# CMake Build Formatting 
# --------------------------------------------------------------------------------
SET(AVACORE_STAGES 6) 
# @TODO: Set this function up 
# Format Line 
# FUNCTION(PRINT_LINE_BREAK ADD_LENGTH) 
#     STRING(LENGTH "" LINE_LENGTH) 
#    IF(NOT ${ADD_LENGTH} MATCHES ${LINE_LENGTH}) 
#        FOREACH(NEW_LENGTH RANGE ${ADD_LENGTH}) 
#           STRING(APPEND LINE_BREAK"-") 
#       ENDFOREACH(NEW_LENGTH) 
#   ENDIF() 
#   MESSAGE(STATUS "${LINE_BREAK}") 
# ENDFUNCTION(PRINT_LINE_BREAK) 

# Command Line Options 
# --------------------------------------------------------------------------------
OPTION(AVACORE_PRINT_MESSAGES "Print Messages" ON)

# ################################################################################
#                    Stage 1 of 6 - Set Target Information 
# ################################################################################

# Operating System Definitions 
# --------------------------------------------------------------------------------
IF(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    ADD_DEFINITIONS(-DSYSTEM_LINUX)
ENDIF() 
IF(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    ADD_DEFINITIONS(-DSYSTEM_WINDOWS)
ENDIF() 

# Compiler Flags 
# --------------------------------------------------------------------------------
IF(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_INIT} 
        -D_DEBUG -D_DRAWGI /Zi /W4 /FS")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} 
        -D_SECURE_SCL=0 /W4 /FS")
ELSE()
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG_INIT} 
        -D_DEBUG -D_DRAWGI -Wno-deprecated-declarations")
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE_INIT} 
        -D_SECURE_SCL=0 -Wno-deprecated-declarations")
ENDIF() 

# Print System Information 
# --------------------------------------------------------------------------------
IF(AVACORE_PRINT_MESSAGES) 
    MESSAGE("-------------------------------------------------------------------")
    MESSAGE(STATUS "[STAGE: 0/${AVACORE_STAGES}] - Fetching Target Information") 
    MESSAGE("-------------------------------------------------------------------")
    # System Information 
    MESSAGE(STATUS "Operating System   =   ${CMAKE_SYSTEM_NAME}") 
    MESSAGE(STATUS "C/C++ Compiler     =   ${CMAKE_CXX_COMPILER_ID}") 
    MESSAGE(STATUS "CMake Version      =   ${CMAKE_VERSION}") 
    MESSAGE(STATUS "CMake Generator    =   ${CMAKE_GENERATOR}") 
    MESSAGE(STATUS "CMake Build Type   =   ${CMAKE_BUILD_TYPE_INIT}")
    MESSAGE(STATUS "System Processor   =   ${CMAKE_SYSTEM_PROCESSOR}")
    # Project Information 
    MESSAGE(STATUS "Project Name       =   ${CMAKE_PROJECT_NAME}")
    MESSAGE(STATUS "Binary Directory   =   ${CMAKE_BINARY_DIR}") 
    MESSAGE(STATUS "Source Directory   =   ${CMAKE_SOURCE_DIR}")
    MESSAGE(STATUS "Project Version    =   ${AVACORE_VERSION}")
    MESSAGE(STATUS "Major Version      =   ${AVACORE_VERSION_MAJOR}")
    MESSAGE(STATUS "Minor Version      =   ${AVACORE_VERSION_MINOR}")
    MESSAGE(STATUS "Patch Version      =   ${AVACORE_VERSION_PATCH}")
ENDIF(AVACORE_PRINT_MESSAGES)

# ################################################################################
#                    Stage 2 of 6 - Searching for Dependencies 
# ################################################################################

# QT Libraries / Dependencies 
# --------------------------------------------------------------------------------
IF(AVACORE_PRINT_MESSAGES) 
    MESSAGE("-------------------------------------------------------------------")
    MESSAGE(STATUS "[STAGE: 2/${AVACORE_STAGES}] - Loading QT Dependencies") 
    MESSAGE("-------------------------------------------------------------------")
ENDIF(AVACORE_PRINT_MESSAGES)

IF(WIN32 OR UNIX) 
    # Find these Qt5 Packages
    SET(QT5_PACKAGES Qt5Core Qt5Gui Qt5Widgets) 
    IF(AVACORE_PRINT_MESSAGES) 
        MESSAGE(STATUS "Searching for QT Packages ...") 
    ENDIF(AVACORE_PRINT_MESSAGES) 

    # Uncomment the following line IF executable fails to build :
    # set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
    FOREACH(package ${QT5_PACKAGES}) 
        IF(AVACORE_PRINT_MESSAGES) 
            MESSAGE(STATUS "Searching for package ${package}") 
        ENDIF(AVACORE_PRINT_MESSAGES) 
        FIND_PACKAGE(${package}) 
        IF(${package}_FOUND) 
            SET(QT5_PACKAGES_FOUND TRUE) 
            INCLUDE_DIRECTORIES(${package_INCLUDES})
            ADD_DEFINITIONS(${package_DEFINITIONS})
            IF(AVACORE_PRINT_MESSAGES) 
                MESSAGE(STATUS "[FOUND] - Package ${package}") 
            ENDIF(AVACORE_PRINT_MESSAGES) 
        ELSE()
            IF(AVACORE_PRINT_MESSAGES) 
                MESSAGE(WARNING "WARNING: [NOT FOUND] - Package ${package}") 
            ENDIF(AVACORE_PRINT_MESSAGES) 
        ENDIF() 
    ENDFOREACH()
ENDIF() 

# Local Source Files 
# --------------------------------------------------------------------------------
SET(AVACORE_SOURCES 
    src/main.cpp 
    src/window.cpp 
)
# Header Files 
# --------------------------------------------------------------------------------
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include 
    ${PROJECT_BINARY_DIR}
    ${PROJECT_BINARY_DIR}/include
)


# ################################################################################
#                   Stage 6 of 6 - Finalizing Build Properties 
# ################################################################################

IF(AVACORE_PRINT_MESSAGES) 
    MESSAGE("-------------------------------------------------------------------")
    MESSAGE(STATUS "[STAGE: ${AVACORE_STAGES}/${AVACORE_STAGES}] - Finishing Up") 
    MESSAGE("-------------------------------------------------------------------")
ENDIF(AVACORE_PRINT_MESSAGES) 

# Generating Definitions 
# --------------------------------------------------------------------------------
CONFIGURE_FILE(
    ${PROJECT_SOURCE_DIR}/include/config.h.in
    ${PROJECT_BINARY_DIR}/include/config.h 
)

# Main Executable File 
# --------------------------------------------------------------------------------
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}
    ${AVACORE_SOURCES}
)

# Target Link Libraries 
# --------------------------------------------------------------------------------
IF(WIN32 OR UNIX)
  target_link_libraries(${PROJECT_NAME} 
    ${QT5PACKAGES_LIBRARIES}
    )
ENDIF()










