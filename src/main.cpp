#include "bcul.h"

// button callback to spawn a message box
void onBasicButton() {
    bcul::wman::messageBox("You clicked this button", "you did");
}

// gets text from input field and prints it in a message box
void onReadInput() {
	
    // get text input from the first field
    auto* input = bcul::wman::getTextInput(0);
	
	// if input is not null and handle is valid
    if (input && input->handle) {
		
		// calls getTextInputValue() with the handle, to retrieve the text entered in that input field
        std::string value = bcul::wman::getTextInputValue(input->handle);
        bcul::wman::messageBox("Input value: " + value, "text input");
    }
}

// button callback to close a window
void onExit() {
    bcul::wman::closeLastWindow();
}

// gui creation
int main() {
    // enable/disable console output
    bcul::console::setVisibility(true);

    // main application window
    bcul::wman::createWindow(
		"Someone please fix the window setting only the first char of the window name as its title", 
		800, 600, 
		bcul::metrics::centerX(800),
		bcul::metrics::centerY(600)
	);

    // button examples (label)
    bcul::wman::createLabel("Button Examples", 20, 20, 300, 30, true, false, false, 18);
    
    // standard button
    bcul::wman::createButton("Click Me", 150, 35, onBasicButton, 20, 60);
    
    // button with large font
    bcul::wman::createButton("Large Button", 180, 40, onBasicButton, 180, 60, 16);
    
    // read input button
    bcul::wman::createButton("Read Input", 150, 35, onReadInput, 20, 110);
    
    // exit button
    bcul::wman::createButton("Exit", 100, 35, onExit, 180, 110);

    // label examples
    bcul::wman::createLabel("Label Examples", 20, 170, 300, 30, true, false, false, 18);
    
    // style variations
    bcul::wman::createLabel("Regular Label", 20, 210, 200, 25);
    bcul::wman::createLabel("Bold Label", 20, 240, 200, 25, true);
    bcul::wman::createLabel("Italic Label", 20, 270, 200, 25, false, true);
    bcul::wman::createLabel("Underlined Label", 20, 300, 200, 25, false, false, true);
    
    // size variations
    bcul::wman::createLabel("Small Font", 250, 210, 200, 25, false, false, false, 10);
    bcul::wman::createLabel("Large Font", 250, 240, 200, 25, false, false, false, 18);
    bcul::wman::createLabel("Extra Large", 250, 270, 200, 25, false, false, false, 24);

    // text input examples (label)
    bcul::wman::createLabel("Text Input Examples", 20, 350, 300, 30, true, false, false, 18);
    
    // regular text input
    bcul::wman::createLabel("Standard Input:", 20, 390, 150, 25);
    bcul::wman::createTextInput("Type something here...", 180, 390, 300, 25);
    
    // password input
    bcul::wman::createLabel("Password:", 20, 430, 150, 25);
    bcul::wman::createTextInput("Enter password...", 180, 430, 300, 25, true);
    
    // multiline input
    bcul::wman::createLabel("Multiline:", 20, 470, 150, 25);
    bcul::wman::createTextInput("Type multiple lines here...", 180, 470, 300, 80, false, true);

    // instructions (labels)
    bcul::wman::createLabel("Instructions:", 500, 20, 280, 30, true, false, false, 18);
    bcul::wman::createLabel("--Click buttons to see actions", 510, 60, 280, 25);
    bcul::wman::createLabel("--Enter text in the input fields", 510, 90, 280, 25);
    bcul::wman::createLabel("--Click 'Read Input' to display the text", 510, 120, 280, 25);
    bcul::wman::createLabel("--Try the password and multiline inputs", 510, 150, 280, 25);

    // run the message loop (necessary)
    bcul::wman::run();
    return 0;
}

