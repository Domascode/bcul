// @brief main file responsible for window management
// took multiple hours across days to document
#include "window_management.h"
#include <iostream>

namespace bcul::wman {
	
	// defining variables declared in header
	extern const int centerWidth = GetSystemMetrics(SM_CXSCREEN) / 2;
	extern const int centerHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
	const wchar_t* DEFAULT_WINDOW_CLASS = L"DefaultWindowClass";
    int openWindows = 0;
    std::vector<HWND> windowHandles;
    std::map<HWND, Button> buttons;
    std::map<HWND, Label> labels;
    std::map<HWND, TextInput> textInputs;
    HWND lastCreatedWindow = NULL;
    unsigned int buttonIdCounter = 0;
	
	// prevents multiple window class registrations
    static bool windowClassRegistered = false;
	
	// main message loop, checks and responds to messages
	void run() {
        MSG msg;
		
		// the message loop
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

	// process messages sent to a window
	// assigns the message to a function
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
			
			// when a button is clicked
            case WM_COMMAND: {
				
				// get clicked button handle
                HWND clickedHwnd = (HWND)lParam;
				
				// finds the clicked button in the map and its assigned callback(function)
                auto it = buttons.find(clickedHwnd);
				
				// checks if the button exists and the callback is valid
                if (it != buttons.end() && it->second.callback) {
					
					// execute the callback if both conditions are met
                    it->second.callback();
					
					// signals that WM_COMMAND was executed and prevents further processing
                    return 0;
                }
                break;
            }
            case WM_CLOSE:
				DestroyWindow(hwnd);
                return 0;
            case WM_DESTROY:
			
				// corrects the open window counter
                --openWindows;
				
				// iterate through windowHandles
                for (auto it = windowHandles.begin(); it != windowHandles.end(); ++it) {
					
					// if handles matches are found
                    if (*it == hwnd) {
						
						// remove the handle
                        windowHandles.erase(it);
						
                        break;
                    }
                }
				
				// if there are no more windows, return 0
                if (openWindows == 0) {
                    PostQuitMessage(0);
                }
                return 0;
        }
		
		// message handler
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void createWindow(const std::string& windowName, int width, int height, int x, int y) {
        HINSTANCE hInstance = GetModuleHandle(0);
        
        // only register the window class if it hasn't been registered yet
        if (!windowClassRegistered) {
			
			// register the class
            WNDCLASSW wc = {};
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = hInstance;
            wc.lpszClassName = DEFAULT_WINDOW_CLASS;
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
            
			// if registering class fails
            if (!RegisterClassW(&wc)) {
                std::cout << "Failed to register window class" << std::endl;
                return;
            }
			
			// prevents multiple window class registrations
            windowClassRegistered = true;
        }
        
        // store window handles and create the window
        lastCreatedWindow = CreateWindowW(
            DEFAULT_WINDOW_CLASS,    // class name
            L"",                     // temporary empty title
            WS_OVERLAPPEDWINDOW,     // style
            x,           			// x position
            y,           			// y position
            width,                   // width
            height,                  // height
            NULL,                    // parent
            NULL,                    // menu
            hInstance,               // instance
            NULL                     // additional data
        );
        
		// if there is a window handle
        if (lastCreatedWindow) {
			
            // converts the window name from string to wide string
            std::wstring wstr = toWideString(windowName);
			
			// casts wstr to an array of strings
            SetWindowTextW(lastCreatedWindow, wstr.c_str());
            
			// show and update window
            ShowWindow(lastCreatedWindow, SW_SHOW);
            UpdateWindow(lastCreatedWindow);
			
			// add the window handle to windowHandles
            windowHandles.push_back(lastCreatedWindow);
			
			// increments the open windows counter
            openWindows++;
			
        } else {
            DWORD error = GetLastError();
            std::cout << "Failed to create window. Error code: " << error << std::endl;
        }
    }

	// simplified message box creation
    void messageBox(const std::string& message, const std::string& title) {
        MessageBoxW(NULL, toWideString(message).c_str(), toWideString(title).c_str(), MB_OK);
    }
    
	// create button
    void createButton(const std::string& buttonText, int width, int height, std::function<void()> callback, int x, int y, int fontSize) {
		
		// if window creation fails
        if (!lastCreatedWindow) return;

		// 1. cast to a menu handle
		// 2. cast to a uintptr_t (unsigned integer type guaranteed to hold a pointer)
		// 3. preincrement buttonIdCounter (to immediately store the incremented value)
        HMENU buttonId = (HMENU)(uintptr_t)(++buttonIdCounter);
		
		// storing button handles and button creation
        HWND hwndButton = CreateWindowW(
            L"BUTTON",
            toWideString(buttonText).c_str(),
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            x, y, width, height,
            lastCreatedWindow,
            buttonId,
            (HINSTANCE)GetWindowLongPtr(lastCreatedWindow, GWLP_HINSTANCE),
            NULL
        );
		
		// if there is a button handle
        if (hwndButton) {
			
            // add font to the button
            HFONT hFont = CreateFontW(
                fontSize,  // height
                0,      // width
                0,      // escapement
                0,      // orientation
                FW_NORMAL,  // weight
                FALSE,      // italic
                FALSE,      // underline
                0,      // strikeout
                DEFAULT_CHARSET,	 		 //
                OUT_DEFAULT_PRECIS,	 		 //
                CLIP_DEFAULT_PRECIS, 		 // does something idk
                CLEARTYPE_QUALITY,	 		 //
                DEFAULT_PITCH | FF_DONTCARE, //
                L"Segoe UI" // typeface name (must be a font installed on the system)
            );

			// apply font
            SendMessage(hwndButton, WM_SETFONT, (WPARAM)hFont, TRUE);
            
			// construct the button class using user entered arguments
            Button button;
            button.handle = hwndButton;
            button.text = buttonText;
            button.width = width;
            button.height = height;
            button.x = x;
            button.y = y;
            button.callback = callback;
            fontSize;
            buttons[hwndButton] = button;
        }
    }

	// create a label
    void createLabel(const std::string& labelText, int x, int y, int width, int height, bool isBold, bool isItalic, bool isUnderlined, int fontSize) {
		
		// check if there is a window
        if (!lastCreatedWindow) return;

		// create a label and store it in hwndLabel
        HWND hwndLabel = CreateWindowW(
            L"STATIC",
            toWideString(labelText).c_str(),
            WS_VISIBLE | WS_CHILD | SS_LEFT,
            x, y, width, height,
            lastCreatedWindow,
            NULL,
            (HINSTANCE)GetWindowLongPtr(lastCreatedWindow, GWLP_HINSTANCE),
            NULL
        );
		
		// checks if there is a label handle
        if (hwndLabel) {
			
			HFONT hFont = CreateFontW(
                fontSize,  // height
                0,      // width
                0,      // escapement
                0,      // orientation
                FW_NORMAL,  // weight
                FALSE,      // italic
                FALSE,      // underline
                0,      // strikeout
                DEFAULT_CHARSET,	 		 //
                OUT_DEFAULT_PRECIS,	 		 //
                CLIP_DEFAULT_PRECIS, 		 // does something idk
                CLEARTYPE_QUALITY,	 		 //
                DEFAULT_PITCH | FF_DONTCARE, //
                L"Segoe UI" // typeface name (must be a font installed on the system)
            );
			
			// apply a font
            SendMessage(hwndLabel, WM_SETFONT, (WPARAM)hFont, TRUE);

			// construct the label class using user entered arguments
            Label label;
            label.handle = hwndLabel;
            label.text = labelText;
            label.x = x;
            label.y = y;
            label.width = width;
            label.height = height;
            label.isBold = isBold;
            label.isItalic = isItalic;
            label.isUnderlined = isUnderlined;
            label.fontSize = fontSize;
            labels[hwndLabel] = label;
        }
    }

	// create a text input
    void createTextInput(const std::string& placeholder, int x, int y, int width, int height, bool isPassword, bool isMultiline, int fontSize) {
		
		// check if there is a window handle, return if not
        if (!lastCreatedWindow) return;

		// default text input style
        DWORD style = WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL;
		
		// user enters true or false in arguments
        if (isMultiline) {
			
			// makes the text input multiline
            style |= ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL;
        }
        if (isPassword) {
			
			// hides the text input
            style |= ES_PASSWORD;
        }

		// create a label and store the handle in hwndInput
        HWND hwndInput = CreateWindowW(
            L"EDIT",							// class name
            toWideString(placeholder).c_str(),	// user text input
            style,								// style (defined above)
            x, y, width, height,				// spawn position, size
            lastCreatedWindow,					// spawn on lastCreatedWindow
            NULL,								
            (HINSTANCE)GetWindowLongPtr(lastCreatedWindow, GWLP_HINSTANCE),
            NULL
        );

		// if there is an input handle
        if (hwndInput) {
			
			HFONT hFont = CreateFontW(
                fontSize,  // height
                0,      // width
                0,      // escapement
                0,      // orientation
                FW_NORMAL,  // weight
                FALSE,      // italic
                FALSE,      // underline
                0,      // strikeout
                DEFAULT_CHARSET,	 		 //
                OUT_DEFAULT_PRECIS,	 		 //
                CLIP_DEFAULT_PRECIS, 		 // does something idk
                CLEARTYPE_QUALITY,	 		 //
                DEFAULT_PITCH | FF_DONTCARE, //
                L"Segoe UI" // typeface name (must be a font installed on the system)
            );
			
			// set the font
            SendMessage(hwndInput, WM_SETFONT, (WPARAM)hFont, TRUE);

			// construct input class using user entered parameters
            TextInput input;
            input.handle = hwndInput;
            input.text = placeholder;
            input.x = x;
            input.y = y;
            input.width = width;
            input.height = height;
            input.isPassword = isPassword;
            input.isMultiline = isMultiline;
            input.fontSize = fontSize;
            textInputs[hwndInput] = input;
        }
    }

	// converts strings into wide strings
    std::string getTextInputValue(HWND handle) {
		
		// find the desired handle in textInputs
        auto it = textInputs.find(handle);
		
		// proceed only if a handle is found
        if (it != textInputs.end()) {
			
			// stores the length of the text in a variable
            int length = GetWindowTextLengthW(handle);
			
			// proceed only if there is text
            if (length > 0) {
				
				// allocates a wide string buffer with room for the text plus the null terminator
                std::wstring wstr(length + 1, 0);
				
				// retrieve text from the window
                GetWindowTextW(handle, &wstr[0], length + 1);
				
				// convert the text to a wide string
                int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
                std::string str(size_needed, 0);
                WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, NULL, NULL);
                return str;
            }
        }
        return "";
    }

	// closes the newest window
    void closeLastWindow() {
		
		// check if there are window handles
        if (!windowHandles.empty()) {
			
			// get the handle of the last window
            HWND lastWindow = windowHandles.back();
			
			// close that window
            PostMessage(lastWindow, WM_CLOSE, 0, 0);
        }
    }

	// closes window by the specified index
    void closeWindowByIndex(size_t index) {
		
		// if index is a valid number
        if (index < windowHandles.size()) {
			
			// choose the window in windowHandles by index and close it
            PostMessage(windowHandles[index], WM_CLOSE, 0, 0);
        }
    }

	// returns the pointer to a button selected by an index
    Button* getButton(size_t index) {
		
		// if index is a valid number
        if (index < buttons.size()) {
			
			// initialize the operator
            auto it = buttons.begin();
			
			// moves it (iterator) <index> steps forward
            std::advance(it, index);
			
			// return the second parameter of the iterator (callback/function)
            return &it->second;
        }
		
		// return nullptr if not found
        return nullptr;
    }

	// finds a button by its handle
    Button* getButtonByHandle(HWND handle) {
		
		// finds a button by its handle in buttons
        auto it = buttons.find(handle);
		
		// proceed only if doesn't reach the end of the map
        if (it != buttons.end()) {
			
			// return the callback
            return &it->second;
        }
		
		// return nullptr if not found
        return nullptr;
    }

	// return a pointer to a label by its index
    Label* getLabel(size_t index) {
		
		// checks if index is a valid number
        if (index < labels.size()) {
			
			// initialize the iterator
            auto it = labels.begin();
			
			// moves the iterator by <index> steps
            std::advance(it, index);
			
			// return the callback
            return &it->second;
        }
		
		// return a nullptr if not found
        return nullptr;
    }

	// find a label by its handle
    Label* getLabelByHandle(HWND handle) {
		
		// initialize the iterator
        auto it = labels.find(handle);
		
		// proceed only if the iterator didn't reach the end
        if (it != labels.end()) {
			
			// return the callback
            return &it->second;
        }
		
		// return a nullptr if not found
        return nullptr;
    }

	// return a pointer to a text input by its index
    TextInput* getTextInput(size_t index) {
		
		// check if index is a valid number
        if (index < textInputs.size()) {
			
			// initialize the iterator
            auto it = textInputs.begin();
			
			// move the iterator by <index> steps
            std::advance(it, index);
			
			// return the callback
            return &it->second;
        }
		
		// return nullptr if not found
        return nullptr;
    }

	// get text input by its handle
    TextInput* getTextInputByHandle(HWND handle) {
		
		// initialize the iterator
        auto it = textInputs.find(handle);
		
		// proceed only if the iterator didn't reach the end
        if (it != textInputs.end()) {
			
			// return the callback
            return &it->second;
        }
		
		// return nullptr if not found
        return nullptr;
    }
} 