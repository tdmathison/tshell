/**
 * \brief A small project to make a command shell that behaves similar to msfconsole.
 * \details
 * \author Travis Mathison
 * \copyright
 *
 *  MIT License
 *
 *  Copyright (c) 2017 Travis Mathison
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */
#ifndef TSHELL_TSHELLCONFIG_H
#define TSHELL_TSHELLCONFIG_H

#include <vector>
#include <memory>
#include <iostream>
#include "modules/IModule.h"

class ICommand;

/**
 * \brief Configuration object to hold commands and modules loaded into the shell.
 */
class TShellConfig {
public:
    TShellConfig() = default;;
    ~TShellConfig() = default;;

    /** The context of the command. */
    enum CommandType {
        /** Commands that can be used in any context. */
        CORE,
        /** Commands that can be used only when a module is loaded */
        MODULE
    };

    /** Commands loaded into shell. */
    std::vector<std::shared_ptr<ICommand>> commands;

    /** Modules loaded into shell. */
    std::vector<std::shared_ptr<IModule>> modules;

    /** Currently loaded module. */
    std::shared_ptr<IModule> loaded_module = nullptr;

    /** Prefix of the shell's prompt. */
    std::string prompt = "tshell";
};


#endif //TSHELL_TSHELLCONFIG_H
