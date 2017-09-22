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
#ifndef TSHELL_HELPCOMMAND_H
#define TSHELL_HELPCOMMAND_H


#include <iostream>
#include <iomanip>
#include "ICommand.h"

/**
 * \brief Shows available commands and provides help text on specific commands.
 */
class HelpCommand : public BaseCommand {
public:
    /**
     * Constructs new Help command.
     * @param config Shared configuration object.
     */
    explicit HelpCommand(std::shared_ptr<TShellConfig> &config) :
        BaseCommand(
            config,
            "help",                                 // name
            "Displays this help",                   // description
            "usage: help\n       help <command>"    // usage
        ) {
    }

    ~HelpCommand() = default;

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
        if (tokens.size() == 2) {
            for (auto &iter : config->commands) {
                if (iter->get_name() == tokens[1]) {
                    std::cout << iter->get_usage() << std::endl << std::endl;
                    return;
                }
            }

            std::cout << "[-] Command '" << tokens[1] << "' not found" << std::endl << std::endl;
            return;
        }

        std::cout <<std::endl;
        std::cout << "Core Commands" << std::endl;
        std::cout << "=============" << std::endl << std::endl;

        std::cout << std::setw(4) << "" << std::left <<std::setw(11) << "Command"
                  << std::setw(25) << "Description" << std::endl;
        std::cout << std::setw(4) << "" << std::left << std::setw(11) << "-------"
                  << std::setw(25) << "-----------" << std::endl;

        // enumerate core commands
        for (auto &iter : config->commands) {
            if (iter->get_command_type() == TShellConfig::CORE) {
                std::cout << std::setw(4) << "" << std::setw(7) << iter->get_name()
                          << std::setw(4) << "" << std::left << std::setw(25) << iter->get_description()
                          << std::endl;
            }
        }

        if (config->commands.empty()) {
            std::cout << "No commands loaded." << std::endl;
        }

        std::cout << std::endl;

        if (config->loaded_module != nullptr) {
            std::cout <<std::endl;
            std::cout << "Module Commands" << std::endl;
            std::cout << "===============" << std::endl << std::endl;

            std::cout << std::setw(4) << "" << std::left <<std::setw(11) << "Command"
                      << std::setw(25) << "Description" << std::endl;
            std::cout << std::setw(4) << "" << std::left << std::setw(11) << "-------"
                      << std::setw(25) << "-----------" << std::endl;

            // enumerate module commands
            for (auto &iter : config->commands) {

                if (iter->get_command_type() == TShellConfig::MODULE) {
                    std::cout << std::setw(4) << "" << std::setw(7) << iter->get_name()
                              << std::setw(4) << "" << std::left << std::setw(25) << iter->get_description()
                              << std::endl;
                }
            }

            std::cout << std::endl;
        }
    }
};


#endif //TSHELL_HELPCOMMAND_H
