/**
 * @file console.h
 * @brief Console management functionality
 * @details Provides functions for controlling and using the console window
 */

#pragma once
#include "bcul.h"
#include <windows.h>
#include <iostream>

/**
 * @brief Namespace for console-related functionality
 * @details Manages the console window and output
 */
namespace bcul::console {
    static bool showConsole = true;  ///< Current visibility state of the console

    /**
     * @brief Sets the visibility of the console window
     * @param visible Whether the console should be visible
     */
    inline void setVisibility(bool visible) {
        showConsole = visible;
        if (!visible) {
            FreeConsole();
        }
    }

    /**
     * @brief Prints a message to the console
     * @param message The message to print
     */
    inline void print(const std::string& message) {
        std::cout << message << std::endl;
    }
} 