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
#ifndef TSHELL_MODULEPARAMS_H
#define TSHELL_MODULEPARAMS_H

#include <string>
#include <map>

/**
 * \brief A representation of parameters used to configure and execute a module.
 */
class ModuleParams {
public:
    /**
     * Constructor.
     */
    ModuleParams();

    /**
     * Destructor.
     */
    ~ModuleParams();

    /**
     * Adds a new parameter to the module configuration.
     * @param key Parameter key.
     * @param default_value Default value that the parameter should have.
     */
    void insert_param(std::string key, std::string default_value);

    /**
     * Sets the value of an existing module parameter.
     * @param key Parameter key.
     * @param value Parameter value.
     */
    void set_param(std::string key, std::string value);

    /**
     * Gets the value of an existing module parameter.
     * @param key Parameter key.
     * @return The value of the specified parameter.
     */
    std::string get_param(std::string key) const;

    /**
     * Prints all of the configured module parameters.
     */
    void print_params();

private:
    std::map<std::string, std::string> params;
    static bool compare_pred(unsigned char a, unsigned char b);
    bool compare(std::string const& a, std::string const& b) const;
};


#endif //TSHELL_MODULEPARAMS_H
