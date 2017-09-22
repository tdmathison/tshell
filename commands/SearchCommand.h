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
#ifndef TSHELL_LISTCOMMAND_H
#define TSHELL_LISTCOMMAND_H


#include <vector>
#include <iostream>
#include <iomanip>
#include "ICommand.h"
#include "../modules/IModule.h"
#include "../utils/Colors.h"

/**
 * \brief Searches for loaded modules.
 */
class SearchCommand : public BaseCommand {
public:
    /**
     * Constructs new Search command.
     * @param config Shared configuration object.
     */
    explicit SearchCommand(std::shared_ptr<TShellConfig> &config) :
        BaseCommand(
            config,
            "search",                       // name
            "Searches available modules",   // description
            "usage: search\n       search <module-name>"   // usage
        ) {
    }

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
        if (tokens.empty()) {
            std::cout << usage << std::endl;
            return;
        }

        std::string filter = "";
        std::vector<std::shared_ptr<IModule>> matching_modules;

        if (tokens.size() == 2) {
            filter = tokens[1];
        }

        for (auto &iter : config->modules) {
            if (filter.length() > 0 && iter->get_name().find(filter) == std::string::npos) {
                continue;
            }

            matching_modules.push_back(iter);
        }

        if (matching_modules.size() > 0) {
            std::cout <<std::endl;
            std::cout << "Matching Modules" << std::endl;
            std::cout << "================" << std::endl << std::endl;

            std::cout << std::setw(4) << "" << std::left <<std::setw(20)
                      << "Name" << std::setw(40) << "Description" << std::endl;
            std::cout << std::setw(4) << "" << std::left << std::setw(20)
                      << "----" << std::setw(40) << "-----------" << std::endl;

            for (auto &iter : matching_modules) {
                std::cout << std::setw(4) << "" << std::setw(7) << iter->get_name()
                          << std::setw(11) << "" << std::left << std::setw(40) << iter->get_description()
                          << std::endl;
            }
        } else {
            std::cout << std::endl << "[" << TShellColors::RED << "-" << TShellColors::RESET << "] "
                      << " No modules found" << std::endl;
        }

        std::cout << std::setw(0) << std::endl;
    }
};


#endif //TSHELL_LISTCOMMAND_H
