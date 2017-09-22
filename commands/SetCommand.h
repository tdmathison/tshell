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
#ifndef TSHELL_SETCOMMAND_H
#define TSHELL_SETCOMMAND_H

#include <iostream>
#include "ICommand.h"

/**
 * \brief Sets parameter values within a loaded module.
 */
class SetCommand : public BaseCommand {
public:
    /**
     * Constructs new Set command.
     * @param config Shared configuration object.
     */
    explicit SetCommand(std::shared_ptr<TShellConfig> &config) :
        BaseCommand(
            config,
            "set",                              // name
            "Sets a key/value within a module", // description
            "usage: set <key> <value>"          // usage
        ) {
    }

    /**
     * The type of command this class represents.
     * @return {@link TShellConfig::CommandType} of the command.
     */
    TShellConfig::CommandType get_command_type() override {
        return TShellConfig::MODULE;
    }

    /**
     * Executes the functionality of the command.
     * @param tokens Extra parameters to the command that may affect it's execution.
     */
    void execute(std::vector<std::string> tokens) override {
        if (config->loaded_module == nullptr) {
            std::cout << "The 'Set' command may only be used from within a module" << std::endl;
            return;
        }

        if (tokens.size() != 3) {
            std::cout << "Incorrect number of arguments to command" << std::endl;
            std::cout << usage << std::endl;
            return;
        }

        config->loaded_module->get_params()->set_param(tokens[1], tokens[2]);
    }
};

#endif //TSHELL_SETCOMMAND_H
