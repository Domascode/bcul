# Every BCUL function/macro cheat sheet  
  
x, y - position  
  
# Window management  
bcul::wman::createWindow(<str>name, <int>width, <int>height);  
bcul::wman::createButton(<str>text, <int>width, <int>height, <function>on press function, <int>x, <int>y, <int>fontSize);  
bcul::wman::createLabel(<str>text, <int>x, <int>y, <int>width, <int>height, <bool>isBold, <bool>isItalic, <bool>isUnderlined, <int>fontSize);  
bcul::wman::createTextInput(<str>placeholder, <int>x, <int>y, <int>width, <int>height, <bool>isPassword, <bool>isMultiline, <int>fontSize);  
bcul::wman::messageBox(<str>message, <str>title);  
bcul::wman::closeLastWindow();  
bcul::wman::closeWindowByIndex(<int>index);  
bcul::run();  
  
# Console  
bcul::console::setVisibility(visible);  
bcul::console::print(<any>message);   exact same as std::cout  
  
# Wide string conversion (expected string format for Win32)  
toWideString(<str>str).c_str();  
