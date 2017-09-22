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
#ifndef TSHELL_LSMODULE_H
#define TSHELL_LSMODULE_H


#include <string>
#include <iostream>
#include <iomanip>
#include "IModule.h"

/**
 * \brief Module to perform a simple Linux 'ls' command.
 */
class LsModule : public IModule {
public:
    /**
     * Constructs a new Ls module.
     */
    LsModule() :
        params(std::make_shared<ModuleParams>()){
        params->insert_param("PATH", "/");
        params->insert_param("LONG_LISTING", "false");
        params->insert_param("SHOW_HIDDEN", "false");
    }

    /**
     * Gets module name.
     * @return std::string
     */
    std::string get_name() {
        return "system/ls";
    };

    /**
     * Gets module description.
     * @return std::string
     */
    std::string get_description() {
        return "List files on file system";
    };

    /**
     * Gets module informational text.
     * @return std::string
     */
    std::string get_info() {
        return
            "----------------------------------------------\n"
            "                   List Module\n"
            "----------------------------------------------\n"
            "This module will perform the Linux system 'ls'\n"
            "command given the configured parameters.\n\n";
    }

    /**
     * Executes the module.
     */
    void execute() {
        std::string command_to_run = "ls ";
        if (this->params->get_param("LONG_LISTING") == "true") {
            command_to_run += "-l ";
        }

        if (this->params->get_param("SHOW_HIDDEN") == "true") {
            command_to_run += "-a ";
        }

        command_to_run += this->params->get_param("PATH");

        system(command_to_run.c_str());
    };

    std::shared_ptr<ModuleParams> get_params() {
        return this->params;
    }

private:
    std::shared_ptr<ModuleParams> params;
};


#endif //TSHELL_LSMODULE_H
