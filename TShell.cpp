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
#include <algorithm>
#include "TShell.h"
#include "commands/BackCommand.h"
#include "commands/HelpCommand.h"
#include "commands/SearchCommand.h"
#include "commands/ShowCommand.h"
#include "commands/UseCommand.h"
#include "commands/RunCommand.h"
#include "commands/SetCommand.h"
#include "commands/ExitCommand.h"
#include "modules/LsModule.h"
#include <readline/readline.h>
#include <readline/history.h>

bool g_module_loaded = false;

char *core_commands[5] = {
    const_cast<char *>("exit"),
    const_cast<char *>("help"),
    const_cast<char *>("search"),
    const_cast<char *>("use"),
    nullptr
};

char *module_commands[10] = {
    const_cast<char *>("exit"),
    const_cast<char *>("help"),
    const_cast<char *>("search"),
    const_cast<char *>("use"),
    const_cast<char *>("back"),
    const_cast<char *>("run"),
    const_cast<char *>("set"),
    const_cast<char *>("show"),
    nullptr
};

char *show_commands[3] = {
    const_cast<char *>("options"),
    const_cast<char *>("info"),
    nullptr
};

char* command_name_generator(const char *text, int state) {
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = static_cast<int>(strlen(text));
    }

    std::string buffer(rl_line_buffer);

    if (::g_module_loaded) {
        if (buffer.length() >= 4 && buffer.substr(0, 4) == "show") {
            while ((name = show_commands[list_index++])) {
                if (strncmp(name, text, static_cast<size_t>(len)) == 0) {
                    return strdup(name);
                }
            }
        } else {
            while ((name = module_commands[list_index++])) {
                if (strncmp(name, text, static_cast<size_t>(len)) == 0) {
                    return strdup(name);
                }
            }
        }
    } else {
        while ((name = core_commands[list_index++])) {
            if (strncmp(name, text, static_cast<size_t>(len)) == 0) {
                return strdup(name);
            }
        }
    }

    return nullptr;
}

char** command_name_completion(const char *text, int start, int end) {
    return rl_completion_matches(text, command_name_generator);
}

TShell::TShell() :
    config(std::make_shared<TShellConfig>()) {
    initialize();
}

TShell::~TShell() {
    config->modules.erase(config->modules.begin(), config->modules.end());
    config->commands.erase(config->commands.begin(), config->commands.end());
};

void TShell::initialize() {
    // commands
    config->commands.push_back(std::make_shared<ExitCommand>(config));
    config->commands.push_back(std::make_shared<HelpCommand>(config));
    config->commands.push_back(std::make_shared<BackCommand>(config));
    config->commands.push_back(std::make_shared<SearchCommand>(config));
    config->commands.push_back(std::make_shared<ShowCommand>(config));
    config->commands.push_back(std::make_shared<UseCommand>(config));
    config->commands.push_back(std::make_shared<RunCommand>(config));
    config->commands.push_back(std::make_shared<SetCommand>(config));

    // modules
    config->modules.push_back(std::make_shared<LsModule>());
}

std::string TShell::get_prompt() {
    auto prompt = config->prompt;

    if (config->loaded_module != nullptr) {
        prompt += " module(";
        prompt += TShellColors::RED;
        prompt += (*config).loaded_module->get_name();
        prompt += TShellColors::RESET;
        prompt += ") > ";
    } else {
        prompt += " > ";
    }

    return prompt;
}

void TShell::run() {
    std::cout << "[*] Initializing TSHELL..." << std::endl;
    std::cout << "[" << TShellColors::GREEN << "+" << TShellColors::RESET << "] " << config->commands.size()
              << " commands loaded..." << std::endl;
    std::cout << "[" << TShellColors::GREEN << "+" << TShellColors::RESET << "] " << config->modules.size()
              << " modules loaded..." << std::endl;
    std::cout << "[*] Initialization completed." << std::endl << std::endl;

    rl_attempted_completion_function = command_name_completion;

    bool exit = false;

    while (!exit) {
        char *buffer = readline(get_prompt().c_str());
        if (buffer) {
            add_history(buffer);
            std::string s(buffer);

            std::transform(s.begin(), s.end(), s.begin(), ::tolower);
            std::vector<std::string> tokens = TokenUtils::tokenize(s);

            if (!tokens.empty()) {
                bool command_found = false;
                for (const auto &command : config->commands) {
                    if (command->get_name() == tokens[0]) {
                        command->execute(tokens);
                        command_found = true;

                        ::g_module_loaded = config->loaded_module != nullptr;

                        if (command->get_name() == "exit") {
                            exit = true;
                        }

                        break;
                    }
                }

                if (!command_found) {
                    std::cout << "[" << TShellColors::RED << "-" << TShellColors::RESET << "] Unknown command: "
                              << tokens[0] << std::endl;
                }
            }

            free(buffer);
        }
    }
}
