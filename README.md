This and the other documentation files are 100% hand written so I'd appreaciate you reading them)

# BCUL
BCUL (Basic C++ Utilities (misleading I know)) is a project of mine designed to make doing repetitive C++ tasks as "Pythonic" (easy, one-line) as possible. It's build using C++, raw Win32 (the combo of pain) and CMake. As of now, it really only has 1 purpose: creating native Windows applications as easily as possible, but I'm planning to expand it into further aspects in the near or so future.

# Usage
1. Clone the git by entering this command in your terminal: git clone github.com/Domascode/bcul
-- make sure you're cloning it into your desired folder! (cd <your destination>)

2. Add the library to your project
The ideal file tree should look something like this:
(i hate it too)

| project
|-- include 				(header files)
|--|-- bcul 				(bcul folder containing .h files)
|--|--|-- bcul .h files 	(bcul library's .h files are placed here)
|-- src 					(cpp files)
|--|-- bcul					(bcul folder containing .cpp files)
|--|--|-- bcul .cpp files	(bcul library's .cpp files are placed here)
|-- main.cpp				(your source file, must be main.cpp, if not then edit CMakeLists)
|-- build					(CMake build destination)

3. Include the library in your file (include this line): #include "bcul/bcul.h"

4. Compile your project with CMake (paste these commands in the terminal):
cd build (change directory to build folder)
cmake ..
cmake --build .

# Documentation
(not done yet) read DOCUMENTATION.txt
or CHEAT_SHEET.txt
