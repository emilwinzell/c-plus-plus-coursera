# Getting Started with your Lab Sandbox

## What tools are already installed in this environment?
- iostream
- vector
- array
- algorithm
- random
- ctime
- numeric
- string
- fstream
- string
- forward_list
- initializer_list

## How can I compile C++ Code in my Terminal?
We have placed a C++ file in this lab for you to use to practice   
compiling a file on Linux in VSCode prior to creating  
your assignment files. Inside the PROJECT folder (which contains 
the file you are currently reading) you will see a folder named "helloworld".    
Inside this folder you will see a file named helloworld.cpp 
which is what you can compile for practice.  

**To compile this file you can either:**
1) Right click your ".cpp file" and select "Run Code" (fastest approach)
2) Or for a more in-depth approach with VSCode:  
  - Open helloworld.cpp (keep it visible on your screen during the next step).  
  - From the main menu, choose Terminal > Configure Default Build Task.   
    A dropdown appears showing various predefined build tasks for C++   
    compilers. Choose C/C++: g++ build active file.  
    This will create a tasks.json file in a .vscode folder and open it in the editor.  
  - Go back to helloworld.cpp. Your task builds the active file   
    and you want to build helloworld.cpp.  
  - To run the build task defined in tasks.json, press Ctrl+Shift+B   
    or from the Terminal main menu choose Run Build Task.  
  - Create a new terminal using the + button (at the lower right   
    side of your lab) and you'll have a terminal running your default  
    shell with the helloworld folder as the working directory   
    (make sure helloworld is showing as the default directory -   
    use cd helloworld if necessary).  
  - You can run helloworld in the terminal by typing ./helloworld. 

  More information on compiling code in VSCode can be found here:  
  https://code.visualstudio.com/docs/cpp/config-linux

## How can I Debug helloworld.cpp?
1. From the main menu, choose Run > Add Configuration.. and 
then choose C++ (GDB/LLDB).  
2. Choose g++ build and debug active file.  
3. VS Code creates a launch.json file, opens it in the editor,   
and builds and runs 'helloworld'.  
4. By default, the C++ extension won't add any breakpoints to   
your source code and the stopAtEntry value is set to false.   
Change the stopAtEntry (in launch.json) value to true to cause   
the debugger to stop on the main method when you start debugging.  
6. Press F5 or from the main menu choose Run > Start Debugging.  
7. At the top of the code editor, a debugging control panel appears.   
You can move this around the screen by grabbing the dots on the left side.  
8. Click or press the Step over icon in the debugging control panel.  
9. You can keep pressing Step over until all the words in the vector   
have been printed to the console.  

More information on debugging in VSCode can be found here:   
https://code.visualstudio.com/docs/editor/debugging