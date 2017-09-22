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
#ifndef TSHELL_BASECOMMAND_H
#define TSHELL_BASECOMMAND_H

#include <utility>
#include "ICommand.h"

/**
 * \brief Abstract command class that all commands derive from.
 */
class BaseCommand : public ICommand {
public:
    /**
     * Constructor the derive class calls to initialize base command from.
     * @param config Shared configuration object.
     * @param name Name of the command.
     * @param description Description of the command.
     * @param usage Usage text on how to use the command.
     */
    explicit BaseCommand(const std::shared_ptr<TShellConfig> &config, std::string name, std::string description, std::string usage)
        : config(config), name(name), description(description), usage(usage) {
    }

    /**
     * Name of the command.
     * @return std::string
     */
    std::string get_name() {
        return name;
    }

    /**
     * Description of the command.
     * @return std::string
     */
    std::string get_description() {
        return description;
    }

    /**
     * Usage help text on how to use the command.
     * @return std::string
     */
    std::string get_usage() {
        return usage;
    }

protected:
    std::shared_ptr<TShellConfig> config;
    std::string name;
    std::string description;
    std::string usage;
};
#endif //TSHELL_BASECOMMAND_H
