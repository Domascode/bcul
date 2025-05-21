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
		HWND handle;                    ///< Window handle for the button
		std::string text;               ///< Text displayed on the button
		int width;                      ///< Width of the button in pixels
		int height;                     ///< Height of the button in pixels
		int x;                          ///< X position of the button
		int y;                          ///< Y position of the button
		std::function<void()> callback; ///< Function to call when button is clicked
		int fontSize;                   ///< Font size in pixels
	};

	struct Label {
		HWND handle;           ///< Window handle for the label
		std::string text;      ///< Text displayed in the label
		int x;                 ///< X position of the label
		int y;                 ///< Y position of the label
		int width;             ///< Width of the label in pixels
		int height;            ///< Height of the label in pixels
		bool isBold;           ///< Whether the text is bold
		bool isItalic;         ///< Whether the text is italic
		bool isUnderlined;     ///< Whether the text is underlined
		int fontSize;          ///< Font size in pixels
	};

	struct TextInput {
		HWND handle;           ///< Window handle for the text input
		std::string text;      ///< Current text in the input
		int x;                 ///< X position of the input
		int y;                 ///< Y position of the input
		int width;             ///< Width of the input in pixels
		int height;            ///< Height of the input in pixels
		bool isPassword;       ///< Whether this is a password input
		bool isMultiline;      ///< Whether this is a multiline input
		int fontSize;          ///< Font size in pixels
	};

	// static(public) variables
	static constexpr const wchar_t* DEFAULT_WINDOW_CLASS = L"DefaultWindowClass";
	static int openWindows = 0;
	static std::vector<HWND> windowHandles;
	static std::map<HWND, Button> buttons;
	static std::map<HWND, Label> labels;
	static std::map<HWND, TextInput> textInputs;
	static HWND lastCreatedWindow = NULL;
	static unsigned int buttonIdCounter = 0;

	// function declarations
	void createWindow(const std::string& windowName, int width, int height);
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