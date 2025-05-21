/**
 * @file bcul.h
 * @brief Main header file for the BCUL library
 * @details Contains core functionality and namespace definitions.
 * This is the only header users need to include to use the full library.
 */

#pragma once

// Standard library includes
#include <string>
#include <functional>
#include <vector>
#include <map>
#include <optional>
#include <iostream>

// Include Windows API - internally used by the library
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

// Internal BCUL library headers
#include "console.h"
#include "window_management.h"
#include "main.h"

/**
 * @brief Main namespace for the BCUL library
 * @details Contains all components of the BCUL library
 */
namespace bcul {
    /**
     * @brief Console management namespace
     * @details Handles console window visibility and output
     */
    namespace console {
        void setVisibility(bool visible);
        void print(const std::string& message);
    }

    /**
     * @brief Window management namespace
     * @details Handles window creation and control
     */
    namespace wman {
        void createWindow(
            const std::string& windowName, 
            int width, int height
            );

        void createButton(
            const std::string& text,
            int width, int height, 
            std::function<void()> callback, 
            int x, int y, 
            int fontSize = 14
            );

        void createLabel(
            const std::string& text, 
            int x, int y,
            int width, int height, 
            bool isBold = false, 
            bool isItalic = false, 
            bool isUnderlined = false, 
            int fontSize = 14
            );

        void createTextInput(
            const std::string& placeholder, 
            int x, int y, 
            int width, int height, 
            bool isPassword = false, 
            bool isMultiline = false, 
            int fontSize = 14
            );

        void messageBox(
            const std::string& message, 
            const std::string& title
            );
    }

    /**
     * @brief Runs the main message loop
     * @details Processes Windows messages and keeps the application running
     */
    void run();
}

/**
 * @brief Converts a standard string to a wide string
 * @param str The string to convert
 * @return The converted wide string
 */
std::wstring toWideString(const std::string& str); 