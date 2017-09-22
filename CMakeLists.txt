cmake_minimum_required(VERSION 3.8)
project(tshell)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
find_package(Readline REQUIRED)
link_libraries(${READLINE_LIBRARY})

set(SOURCE_FILES main.cpp TShell.cpp TShell.h commands/ICommand.h modules/IModule.h utils/TokenUtils.h commands/HelpCommand.h modules/LsModule.h commands/SearchCommand.h commands/UseCommand.h commands/BackCommand.h commands/ShowCommand.h TShellConfig.h commands/RunCommand.h commands/SetCommand.h commands/ExitCommand.h modules/ModuleParams.cpp modules/ModuleParams.h commands/BaseCommand.h utils/Colors.h)
add_executable(tshell ${SOURCE_FILES})
