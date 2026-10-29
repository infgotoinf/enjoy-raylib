################################################################################
#
#   Don't directly run cmake, use make!
#   Example commands:
#       make
#       make help
#       make build
#       make clean
#
################################################################################

cmake_minimum_required(VERSION 3.24)

if (NOT ("${BUILD_TYPE}" STREQUAL "Debug" OR "${BUILD_TYPE}" STREQUAL "Release"))
    message(FATAL_ERROR "Unknown BUILD_TYPE \"${BUILD_TYPE}\", please set BUILD_TYPE to \"Debug\" or \"Release\"")
else()
    set(CMAKE_BUILD_TYPE "${BUILD_TYPE}")
endif()

if ("${PROJECT_LANGUAGE}" STREQUAL "C")
    project("${PROJECT_NAME}" C)
elseif ("${PROJECT_LANGUAGE}" STREQUAL "C++")
    project("${PROJECT_NAME}" C CXX)
else()
    message(FATAL_ERROR "Unknown PROJECT_LANGUAGE \"${PROJECT_LANGUAGE}\", please set PROJECT_LANGUAGE to \"C\" or \"C++\"")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json

if (NOT ("${PLATFORM}" STREQUAL "Web" OR "${PLATFORM}" STREQUAL "Desktop"))
    message(FATAL_ERROR "Unknown PLATFORM \"${PLATFORM}\", please set PLATFORM to \"Web\" or \"Desktop\"")
endif()

include(FetchContent)



# === Dependencies ===
set(RAYLIB_VERSION 6.2)

set(FETCHCONTENT_QUIET FALSE) # Show download progress
# Fetches raylib if it wasn't found
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)



# === Our project ===
add_subdirectory(src)


# --- Project properties ---
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)


# --- Target link with raylib ---
set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)



# === Platform specific configurations ===
if ("${PLATFORM}" STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file
    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file resources)

elseif ("${PLATFORM}" STREQUAL "Desktop")

    # --- OS specific configurations ---
    if (LINUX OR BSD)
        target_link_libraries(${PROJECT_NAME}
            PRIVATE
                GL
                m
                pthread
                dl
                rt
                X11
        )
    endif()
    # Checks if OSX and links appropriate frameworks (Only required on MacOS)
    # if (APPLE)
    #   target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    #   target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    #   target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    # endif()
endif()
