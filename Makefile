.PHONY: build run clean help


# Project configuration
PROJECT_NAME     ?= game
PROJECT_LANGUAGE ?= C
# PROJECT_LANGUAGE ?= C++

PLATFORM   ?= Desktop
# PLATFORM   ?= Web
BUILD_TYPE ?= Debug
# BUILD_TYPE ?= Release

CMAKE_C_COMPILER_LAUNCHER   ?= ccache
CMAKE_CXX_COMPILER_LAUNCHER ?= ccache
CMAKE_C_STANDARD   ?= 23
CMAKE_CXX_STANDARD ?= 23
CMAKE_GENERATOR    ?= Ninja
BUILD_DIR ?= build


# Makefile commands
all: help

build:
	cmake -B $(BUILD_DIR) -DPROJECT_NAME=$(PROJECT_NAME) -DPROJECT_LANGUAGE=$(PROJECT_LANGUAGE) \
		-DPLATFORM=$(PLATFORM) -DBUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_C_COMPILER_LAUNCHER=$(CMAKE_C_COMPILER_LAUNCHER) -DCMAKE_CXX_COMPILER_LAUNCHER=$(CMAKE_CXX_COMPILER_LAUNCHER) -DCMAKE_C_STANDARD=$(CMAKE_C_STANDARD) -DCMAKE_CXX_STANDARD=$(CMAKE_CXX_STANDARD) -DCMAKE_GENERATOR=$(CMAKE_GENERATOR)
	cmake --build $(BUILD_DIR)

run:
	cd $(BUILD_DIR)/$(PROJECT_NAME) && ./$(PROJECT_NAME)

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Usage:"
	@echo "  make <COMMAND> [VARIABLE=VALUE]"
	@echo ""
	@echo "Commands:"
	@echo "  build  Build project"
	@echo "  run    Run executable with this PROJECT_NAME"
	@echo "  clean  Remove build folder"
	@echo "  help   Prints this message"
	@echo ""
	@echo "Variables:"
	@echo "  PROJECT_NAME      The name of execautable"
	@echo "                    Current value: $(PROJECT_NAME)"
	@echo ""
	@echo "  PROJECT_LANGUAGE  The primary language used for the project. Set to C if it has no C++ code and set to C++ if it has"
	@echo "                    Current value: $(PROJECT_LANGUAGE)"
	@echo "                    Possible values: C, C++"
	@echo ""
	@echo "  PLATFORM          The platform for which the project will be built"
	@echo "                    Current value: $(PLATFORM)"
	@echo "                    Possible values: Desktop, Web"
	@echo ""
	@echo "  BUILD_TYPE        Current value: $(BUILD_TYPE)"
	@echo "                    Possible values: Debug, Release"
	@echo ""
	@echo "  BUILD_DIR         Directory where the project will be built"
	@echo "                    Current value: $(BUILD_DIR)"
	@echo ""
	@echo "CMake variables:"
	@echo "   CMAKE_C_COMPILER_LAUNCHER    Current value: $(CMAKE_C_COMPILER_LAUNCHER)"
	@echo "   CMAKE_CXX_COMPILER_LAUNCHER  Current value: $(CMAKE_CXX_COMPILER_LAUNCHER)"
	@echo "   CMAKE_C_STANDARD             Current value: $(CMAKE_C_STANDARD)"
	@echo "   CMAKE_CXX_STANDARD           Current value: $(CMAKE_CXX_STANDARD)"
	@echo "   CMAKE_GENERATOR              Current value: $(CMAKE_GENERATOR)"
	@echo ""
	@echo "Examples:"
	@echo "  make build"
	@echo "  make build PLATFORM=Web"
	@echo "  make build BUILD_TYPE=Release"
	@echo "  make build PLATFORM=Web BUILD_TYPE=Release"
	@echo "  make clean"
