// @brief home of the bcul namespace; declares every bcul function
#pragma once

#include <string>
#include <functional>
#include <vector>
#include <map>
#include <optional>
#include <iostream>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN // excludes unnecessary api's, improves performance
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#include "console.h"			//
#include "window_management.h"  // includes every other .h file

namespace bcul {
	
	namespace metrics {
		inline int centerX(int width) {
			return (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		}

		inline int centerY(int height) {
			return (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
		}
	}
	
    namespace console {
        void setVisibility(bool visible); // sets console visibility (window/background)
        //void print(const std::string& message); 	removed useless function, just use std::cout
    }

    namespace wman {
        void createWindow(
            const std::string& windowName, // sets the window title; bugged to only show the first char of the string
            int width, int height, // window size
			int x, int y // spawn position
            );

        void createButton(
            const std::string& text, // sets the text on the button
            int width, int height, // button size
            std::function<void()> callback, // function to call on press
            int x, int y, // spawn position
            int fontSize = 14 // sets the font size
            );

        void createLabel(
            const std::string& text, // text to display
            int x, int y, // spawn position
            int width, int height, // label size
            bool isBold = false, // is bold
            bool isItalic = false, // is italic
            bool isUnderlined = false, // is underlined
            int fontSize = 14 // sets the font size
            );

        void createTextInput(
            const std::string& placeholder, // user entered text
            int x, int y, // spawn position
            int width, int height, // text input size
            bool isPassword = false, // is password, turns every symbol into "*" if true
            bool isMultiline = false, // is multiline, drops down when enough text is entered
            int fontSize = 14 // sets the font size
            );

        void messageBox(
            const std::string& message, // messsage to display
            const std::string& title // window title
            );
    }

    void run(); // runs the message loop
}

std::wstring toWideString(const std::string& str); // converts strings to wide strings, which are expected by win32