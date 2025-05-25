// @brief console related functions
#pragma once
#include "bcul.h"
#include <windows.h>
#include <iostream>

namespace bcul::console {
    static bool showConsole = true; // shows the console by defaults

    inline void setVisibility(bool visible) {
        visible = showConsole; // copy data from showConsole, no need for a pointer
        if (!visible) { // if false
            FreeConsole(); // hide the console
        }
    }

	/* removed useless function, just use std::cout
    inline void print(const std::string& message) {
        std::cout << message << std::endl;		
    }
	*/
} 