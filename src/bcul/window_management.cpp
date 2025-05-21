#include "window_management.h"
#include <iostream>

namespace bcul::wman {
    static bool windowClassRegistered = false;

    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
            case WM_COMMAND: {
                HWND clickedHwnd = (HWND)lParam;
                auto it = buttons.find(clickedHwnd);
                if (it != buttons.end() && it->second.callback) {
                    it->second.callback();
                    return 0;
                }
                break;
            }
            case WM_CLOSE:
                DestroyWindow(hwnd);
                return 0;
            case WM_DESTROY:
                --openWindows;
                for (auto it = windowHandles.begin(); it != windowHandles.end(); ++it) {
                    if (*it == hwnd) {
                        windowHandles.erase(it);
                        break;
                    }
                }
                if (openWindows == 0) {
                    PostQuitMessage(0);
                }
                return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void createWindow(const std::string& windowName, int width, int height) {
        HINSTANCE hInstance = GetModuleHandle(0);
        
        // only register the window class if it hasn't been registered yet
        if (!windowClassRegistered) {
            WNDCLASSW wc = {};
            wc.lpfnWndProc = WindowProc;
            wc.hInstance = hInstance;
            wc.lpszClassName = DEFAULT_WINDOW_CLASS;
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
            
            if (!RegisterClassW(&wc)) {
                std::cout << "Failed to register window class" << std::endl;
                return;
            }
            windowClassRegistered = true;
        }
        
        // Create the window with a temporary title    ai coded this part idk what a lastCreatedWindow is either
        lastCreatedWindow = CreateWindowW(
            DEFAULT_WINDOW_CLASS,    // Class name
            L"",                     // Temporary empty title
            WS_OVERLAPPEDWINDOW,     // Style
            CW_USEDEFAULT,           // X position
            CW_USEDEFAULT,           // Y position
            width,                   // Width
            height,                  // Height
            NULL,                    // Parent
            NULL,                    // Menu
            hInstance,               // Instance
            NULL                     // Additional data
        );
        
        if (lastCreatedWindow) {
            // Convert and set the window title after creation
            std::wstring wstr = toWideString(windowName);
            SetWindowTextW(lastCreatedWindow, wstr.c_str());
            
            ShowWindow(lastCreatedWindow, SW_SHOW);
            UpdateWindow(lastCreatedWindow);
            windowHandles.push_back(lastCreatedWindow);
            openWindows++;
        } else {
            DWORD error = GetLastError();
            std::cout << "Failed to create window. Error code: " << error << std::endl;
        }
    }

    void messageBox(const std::string& message, const std::string& title) {
        MessageBoxW(NULL, toWideString(message).c_str(), toWideString(title).c_str(), MB_OK);
    }
    
    void createButton(const std::string& buttonText, int width, int height, std::function<void()> callback, int x, int y, int fontSize) {
        if (!lastCreatedWindow) return;

        HMENU buttonId = (HMENU)(uintptr_t)(++buttonIdCounter);
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
        
        if (hwndButton) {
            // Add a consistent font to the button
            HFONT hFont = CreateFontW(
                fontSize,  // Height - using the provided font size
                0,      // Width
                0,      // Escapement
                0,      // Orientation
                FW_NORMAL,  // Weight
                FALSE,      // Italic
                FALSE,      // Underline
                0,      // StrikeOut
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L"Segoe UI"
            );

            SendMessage(hwndButton, WM_SETFONT, (WPARAM)hFont, TRUE);
            
            Button button;
            button.handle = hwndButton;
            button.text = buttonText;
            button.width = width;
            button.height = height;
            button.x = x;
            button.y = y;
            button.callback = callback;
            button.fontSize = fontSize;
            buttons[hwndButton] = button;
        }
    }

    void createLabel(const std::string& labelText, int x, int y, int width, int height, bool isBold, bool isItalic, bool isUnderlined, int fontSize) {
        if (!lastCreatedWindow) return;

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

        if (hwndLabel) {
            HFONT hFont = CreateFontW(
                fontSize,  // Height - using the provided font size
                0,      // Width
                0,      // Escapement
                0,      // Orientation
                isBold ? FW_BOLD : FW_NORMAL,  // Weight
                isItalic,                      // Italic
                isUnderlined,                  // Underline
                0,      // StrikeOut
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L"Segoe UI"
            );

            SendMessage(hwndLabel, WM_SETFONT, (WPARAM)hFont, TRUE);

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

    void createTextInput(const std::string& placeholder, int x, int y, int width, int height, bool isPassword, bool isMultiline, int fontSize) {
        if (!lastCreatedWindow) return;

        DWORD style = WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL;
        if (isMultiline) {
            style |= ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL;
        }
        if (isPassword) {
            style |= ES_PASSWORD;
        }

        HWND hwndInput = CreateWindowW(
            L"EDIT",
            toWideString(placeholder).c_str(),
            style,
            x, y, width, height,
            lastCreatedWindow,
            NULL,
            (HINSTANCE)GetWindowLongPtr(lastCreatedWindow, GWLP_HINSTANCE),
            NULL
        );

        if (hwndInput) {
            HFONT hFont = CreateFontW(
                fontSize,  // Height - using the provided font size
                0,      // Width
                0,      // Escapement
                0,      // Orientation
                FW_NORMAL,  // Weight
                FALSE,      // Italic
                FALSE,      // Underline
                0,      // StrikeOut
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY,
                DEFAULT_PITCH | FF_DONTCARE,
                L"Segoe UI"
            );

            SendMessage(hwndInput, WM_SETFONT, (WPARAM)hFont, TRUE);

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

    std::string getTextInputValue(HWND handle) {
        auto it = textInputs.find(handle);
        if (it != textInputs.end()) {
            int length = GetWindowTextLengthW(handle);
            if (length > 0) {
                std::wstring wstr(length + 1, 0);
                GetWindowTextW(handle, &wstr[0], length + 1);
                int size_needed = WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
                std::string str(size_needed, 0);
                WideCharToMultiByte(CP_ACP, 0, &wstr[0], (int)wstr.size(), &str[0], size_needed, NULL, NULL);
                return str;
            }
        }
        return "";
    }

    void closeLastWindow() {
        if (!windowHandles.empty()) {
            HWND lastWindow = windowHandles.back();
            PostMessage(lastWindow, WM_CLOSE, 0, 0);
        }
    }

    void closeWindowByIndex(size_t index) {
        if (index < windowHandles.size()) {
            PostMessage(windowHandles[index], WM_CLOSE, 0, 0);
        }
    }

    Button* getButton(size_t index) {
        if (index < buttons.size()) {
            auto it = buttons.begin();
            std::advance(it, index);
            return &it->second;
        }
        return nullptr;
    }

    Button* getButtonByHandle(HWND handle) {
        auto it = buttons.find(handle);
        if (it != buttons.end()) {
            return &it->second;
        }
        return nullptr;
    }

    Label* getLabel(size_t index) {
        if (index < labels.size()) {
            auto it = labels.begin();
            std::advance(it, index);
            return &it->second;
        }
        return nullptr;
    }

    Label* getLabelByHandle(HWND handle) {
        auto it = labels.find(handle);
        if (it != labels.end()) {
            return &it->second;
        }
        return nullptr;
    }

    TextInput* getTextInput(size_t index) {
        if (index < textInputs.size()) {
            auto it = textInputs.begin();
            std::advance(it, index);
            return &it->second;
        }
        return nullptr;
    }

    TextInput* getTextInputByHandle(HWND handle) {
        auto it = textInputs.find(handle);
        if (it != textInputs.end()) {
            return &it->second;
        }
        return nullptr;
    }
} 