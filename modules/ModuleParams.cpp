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
#include <iostream>
#include <utility>
#include <iomanip>
#include "ModuleParams.h"
#include "../utils/Colors.h"

ModuleParams::ModuleParams() :
    params(std::map<std::string, std::string>()){
}

ModuleParams::~ModuleParams() = default;

void ModuleParams::set_param(std::string key, std::string value) {
    for (auto &param : params) {
        if (compare(param.first, key)) {
            param.second = value;
            return;
        }
    }

    std::cout << "[" << TShellColors::RED << "-" << TShellColors::RESET << "] "
              << "Key '" << key << "' not found." << std::endl;
}

std::string ModuleParams::get_param(std::string key) const {
    for (auto &param : params) {
        if (compare(param.first, key)) {
            return param.second;
        }
    }

    return std::string();
}

void ModuleParams::print_params() {
    std::cout << std::endl;
    std::cout << std::setw(25) << std::left << "KEY" << std::setw(25) << "VALUE" << std::endl;
    std::cout << std::setw(25) << std::left << "---" << std::setw(25) << "-----" << std::endl;

    for (auto &param : params) {
        std::cout << std::setw(25) << std::left << param.first
                  << std::setw(50) << param.second << std::endl;
    }

    std::cout << std::endl;
}

void ModuleParams::insert_param(std::string key, std::string default_value) {
    params.insert(std::make_pair(key, default_value));
}

bool ModuleParams::compare_pred(unsigned char a, unsigned char b)
{
    return std::tolower(a) == std::tolower(b);
}

bool ModuleParams::compare(std::string const& a, std::string const& b) const
{
    if (a.length()==b.length()) {
        return std::equal(b.begin(), b.end(),
                          a.begin(), compare_pred);
    }
    else {
        return false;
    }
}
