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
#ifndef TSHELL_ICOMMAND_H
#define TSHELL_ICOMMAND_H

#include <string>
#include "../TShellConfig.h"

/**
 * \brief Interface for the shell command.
 */
class ICommand {
public:
    /** Gets name of command. */
    virtual std::string get_name() = 0;
    /** Gets description of command. */
    virtual std::string get_description() = 0;
    /** Gets help usage text for command. */
    virtual std::string get_usage() = 0;
    /** Gets the {@ref TShellConfig::CommandType} of the command */
    virtual TShellConfig::CommandType get_command_type() = 0;
    /** Executes the functionality of the command. */
    virtual void execute(std::vector<std::string>) = 0;
};

#endif //TSHELL_ICOMMAND_H
