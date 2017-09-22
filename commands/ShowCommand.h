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
#ifndef TSHELL_SHOWCOMMAND_H
#define TSHELL_SHOWCOMMAND_H


#include <vector>
#include <iostream>
#include "ICommand.h"
#include "../utils/TokenUtils.h"
#include "../modules/IModule.h"

/**
 * \brief Shows the current module parameters and associated values.
 */
class ShowCommand : public BaseCommand {
public:
    /**
     * Constructs new Show command.
     * @param config Shared configuration object.
     */
    explicit ShowCommand(std::shared_ptr<TShellConfig> &config) :
        BaseCommand(
            config,
            "show",                                             // name
            "Displays options and configurations of a module",  // description
            "usage: show options\n       show info"             // usage
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
            std::cout << "The 'show' command may only be used from within a module" << std::endl;
            return;
        }

        if (tokens.empty() || tokens.size() != 2
            || (tokens[1] != "options" && tokens[1] != "info")) {
            std::cout << this->usage << std::endl << std::endl;
            return;
        }

        if (tokens[1] == "options") {
            config->loaded_module->get_params()->print_params();
        } else if (tokens[1] == "info") {
            std::cout << config->loaded_module->get_info();
        }
    }
};


#endif //TSHELL_SHOWCOMMAND_H
