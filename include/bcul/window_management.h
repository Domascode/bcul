// @brief header file for window_management.cpp
// stores data and defines things
#pragma once
#include "bcul.h"
#include <windows.h>
#include <string>
#include <optional>
#include <vector>
#include <functional>
#include <map>

namespace bcul::wman {
	struct Button {
		HWND handle;                    // window handle for the button
		std::string text;               // text displayed on the button
		int width;                      // width of the button in pixels
		int height;                     // height of the button in pixels
		int x;                          // x position of the button
		int y;                          // y position of the button
		std::function<void()> callback; // function to call when button is clicked
		int fontSize;                   // font size in pixels
		HFONT hFont;
	};

	struct Label {
		HWND handle;           // window handle for the label
		std::string text;      // text displayed in the label
		int x;                 // x position of the label
		int y;                 // y position of the label
		int width;             // width of the label in pixels
		int height;            // height of the label in pixels
		bool isBold;           // whether the text is bold
		bool isItalic;         // whether the text is italic
		bool isUnderlined;     // whether the text is underlined
		int fontSize;          // font size in pixels
		HFONT hFont;
	};

	struct TextInput {
		HWND handle;           // window handle for the text input
		std::string text;      // current text in the input
		int x;                 // x position of the input
		int y;                 // y position of the input
		int width;             // width of the input in pixels
		int height;            // height of the input in pixels
		bool isPassword;       // whether this is a password input
		bool isMultiline;      // whether this is a multiline input
		int fontSize;          // font size in pixels
		HFONT hFont;
	};

	// static(public) variables
	
	// default window class
	extern const wchar_t* DEFAULT_WINDOW_CLASS;
	
	// open window counter
	extern int openWindows;
	
	// stores every window handle in a public vector
	extern std::vector<HWND> windowHandles;
	
	// maps each window handle to a button
	extern std::map<HWND, Button> buttons;
	
	// maps each window handle to a label
	extern std::map<HWND, Label> labels;
	
	// maps every window handle to a text input
	extern std::map<HWND, TextInput> textInputs;
	
	// stores the handle of the newest window
	extern HWND lastCreatedWindow;
	
	// stores the number of button id's
	extern unsigned int buttonIdCounter;

	// function declarations
	void run();
	void createWindow(const std::string& windowName, int width, int height, int x, int y);
	void createButton(const std::string& text, int width, int height, std::function<void()> callback, int x, int y, int fontSize);
	void createLabel(const std::string& text, int x, int y, int width, int height, bool isBold, bool isItalic, bool isUnderlined, int fontSize);
	void createTextInput(const std::string& placeholder, int x, int y, int width, int height, bool isPassword, bool isMultiline, int fontSize);
	void messageBox(const std::string& message, const std::string& title);
	void closeLastWindow();
	void closeWindowByIndex(size_t index);
	Button* getButton(size_t index);
	Button* getButtonByHandle(HWND handle);
	Label* getLabel(size_t index);
	Label* getLabelByHandle(HWND handle);
	TextInput* getTextInput(size_t index);
	TextInput* getTextInputByHandle(HWND handle);
	std::string getTextInputValue(HWND handle);
}