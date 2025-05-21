/**
 * @file main.h
 * @brief Main application loop functionality
 * @details Contains the core message loop for the application
 */

#pragma once
#include "bcul.h"
#include "window_management.h"
#include "console.h"
#include <windows.h>

/**
 * @brief Main namespace for application functionality
 * @details Contains the core message loop and application control
 */
namespace bcul {
    /**
     * @brief Runs the main message loop
     * @details Processes Windows messages and keeps the application running
     * until all windows are closed
     */
    inline void run() {
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}