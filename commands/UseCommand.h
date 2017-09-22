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
#ifndef TSHELL_USECOMMAND_H
#define TSHELL_USECOMMAND_H


#include <vector>
#include <iostream>
#include "ICommand.h"
#include "../modules/IModule.h"

/**
 * \brief Loads a specific module as the current context.
 */
class UseCommand : public BaseCommand {
public:
    /**
     * Constructs new Use command.
     * @param config Shared configuration object.
     */
    explicit UseCommand(std::shared_ptr<TShellConfig> &config) :
        BaseCommand(
            config,
            "use",                                 // name
            "Sets context to a specific module",   // description
            "usage: use <module-name>"             // usage
        ) {
    }

    ~UseCommand() = default;

    /**
     * The type of command this class represents.
     * @return {@link TShellConfig::CommandType} of the command.
     */
    TShellConfig::CommandType get_command_type() override {
        return TShellConfig::CORE;
    }

    /**
     * Executes the functionality of the command.
     * @param tokens Extra parameters to the command that may affect it's execution.
     */
    void execute(std::vector<std::string> tokens) override {
        if (tokens.empty() || tokens.size() != 2) {
            std::cout << usage << std::endl << std::endl;
            return;
        }

        for (auto &iter : config->modules) {
            if (iter->get_name() == tokens[1]) {
                config->loaded_module = iter;
                return;
            }
        }

        std::cout << "Module '" << tokens[1] << "' not found." << std::endl;
    }
};


#endif //TSHELL_USECOMMAND_H
