#include "bcul.h"
#include <windows.h>
#include <string>

/**
 * @brief Converts a string to a wide string for win32
 * @param str The string to convert
 * @return The converted wide string
 */
std::wstring toWideString(const std::string& str) {
    if (str.empty()) return std::wstring();
    
    // get the required size for wide string
    int size_needed = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    if (size_needed <= 0) {
        return std::wstring();
    }
    
    // create a wide string with the required size
    std::wstring wstr(size_needed, 0);
    
    // convert the string
    int result = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], size_needed);
    if (result <= 0) {
        return std::wstring();
    }
    
    // remove the null terminator from the string length
    wstr.resize(result - 1);
    
    return wstr;
} 