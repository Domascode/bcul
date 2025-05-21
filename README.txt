This and the other documentation files are 100% hand written so I'd appreaciate you reading them)

# BCUL
BCUL (Basic C++ Utilities (misleading I know)) is a project of mine designed to make doing repetitive C++ tasks as "Pythonic" (easy, one-line) as possible. It's build using C++, raw Win32 (the combo of pain) and CMake. As of now, it really only has 1 purpose: creating native Windows applications as easily as possible, but I'm planning to expand it into further aspects in the near or so future.

# Usage
1. Clone the git by entering this command in your terminal: git clone github.com/Domascode/bcul
-- make sure you're cloning it into your desired folder! (cd <your destination>)

2. Add the library to your project
The ideal file tree should look something like this:

| project
|-- include 	(where you place the bcul library)
|--|-- bcul 	(the library)
|-- src 		(your own project files)
|-- build		(CMake build destination)

3. Include the library in your file (include this line): #include "bcul/bcul.h"

4. Happy software development!

# Documentation
(not done yet) read DOCUMENTATION.txt
or CHEAT_SHEET.txt