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
#ifndef TSHELL_COLORS_H
#define TSHELL_COLORS_H

#include <string>

/**
 * \brief Color codes used for colorization of the console.
 */
class TShellColors {
public:
    static constexpr const char* RED = "\033[0;31m";
    static constexpr const char* GREEN = "\033[1;32m";
    static constexpr const char* YELLOW = "\033[1;33m";
    static constexpr const char* CYAN = "\033[0;36m";
    static constexpr const char* MAGENTA = "\033[0;35m";
    static constexpr const char* RESET = "\033[0m";
};

#endif //TSHELL_COLORS_H
