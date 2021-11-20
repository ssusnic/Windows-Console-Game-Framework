# Windows-Console-Game-Framework
To facilitate the process of coding games in C++ for the Windows Console, I developed a simple game framework named **Consoler**.

This repo contains the Consoler framework, including the following files:  
1. **Consoler.h**         - the framework interface
2. **Consoler.dll**       - the dynamic library
3. **ConsolerStatic.lib** - the static library
4. **manual.txt**         - the user manual

This repo also contains the source codes of the demos and games made by using this framework.  


## API Documentation
The framework interface file (Consoler.h) can be used as the reference documentation of the Consoler API.  
All globals, constants and classes with their variables and methods are listed there and commented very well.  
So, you should easily find out how to use them for making your own console games.  

In addition, you can always check out examples published in this repo to learn more details about implementing games based on this framework.

The video tutorials on this topic are also available on my Youtube channel:  
https://www.youtube.com/ssusnic


## Usage
1. create a new C++ source code file  
2. include the **Consoler.h**  
3. define a new **Game class** which inherits the **Consoler class** and then:  
	a. override the **Setup()** method to set up game and load sprites/sounds  
	b. override the **Update()** method to update the game logic  
	c. override the **ShowPauseInfo()** method to handle the game when it is paused  
4. inside the **main program**:  
	a. initialize a new game object  
	b. run the main game loop  
5. build your game dynamically with **Consoler.dll** or statically with **ConsolerStatic.lib**  


## Program Template
Here is a basic program template that uses the Consoler framework.  
It creates a new console window and then clears the screen in each frame.  

```c++
// include interface of the Consoler framework
#include "Consoler.h"

// Game class - inherits Consoler class.
class Game : public Consoler
{
public:
	// inherit Consoler constructor
	using Consoler::Consoler;
	
	// override Setup() method to set up game and load sprites/sounds
	void Setup() override
	{
	}
	
	// override Update() method to update game logic (this is the main game loop)
	void Update() override
	{
		ClearScreen();
	}
};

// Main program
int main(){
	// initialize a new game by defining the size of the console screen and target fps
	Game game(L"Consoler Demo", 320, 200, 1, 1, 60);
	
	// run the main game loop
	game.Run();
	
	return 0;
}
```

## Compiling
To compile your C++ program, you should have a C++ compiler installed on your computer.  
Since I'm using the MinGW development tools, here are instructions how to build a game by running the **g++ compiler** at the command prompt.  

**Prerequisites:**  
  - **MinGW installed** on your computer (https://www.mingw-w64.org/)  
  - the **PATH** environment variable set to **MinGW\bin** directory, so the system knows where to find the g++ compiler.  

**Steps to build a game:**  
1. start the command prompt (by running cmd.exe)
2. change directory to the folder with the source code of your game
3. set the path to the folder with the Consoler framework
4. run the g++ compiler to build the game:
  - dynamically by using **Consoler.dll**:  
  ```shell
	  g++ -I../Consoler MyGame.cpp -o MyGame.exe -DUNICODE -O3 -lwinmm -L../Consoler -lConsoler
  ``` 
  - statically by using **ConsolerStatic.lib**:
  ```shell  
	  g++ -I../Consoler MyGame.cpp ../Consoler/ConsolerStatic.lib -o MyGame.exe -DUNICODE -O3 -DSTATIC -lwinmm -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread
  ```

I guess you can compile your programs in a similar way on any other C ++ development platform. 


## Batch Scripts
To execute previous commands more efficiently and quickly, you can use batch scripts.

Here are some examples:

1. **start_cmd.bat**
```shell
cmd /k "set path=%path%;%~dp0..\Consoler"
```

- this script starts the Windows command prompt and sets the path to the Consoler folder
- place this script in your project folder
- to run it, open the project folder using File Explorer, and then double-click on the script file  

2. **make.bat**
```bat
@echo off
Set "appName=MyGame"

if "%1"=="-s" (
	goto compile_static_lib
) else (
	goto compile_dynamic_lib
)

:compile_dynamic_lib
	echo Compiling with the Consoler dynamic library...
	@echo on
	g++ -I../Consoler %appName%.cpp -o %appName%.exe -DUNICODE -O3 -lwinmm -L../Consoler -lConsoler
	@echo off
	goto end

:compile_static_lib
	echo Compiling with the Consoler static library...
	@echo on
	g++ -I../Consoler %appName%.cpp ../Consoler/ConsolerStatic.lib -o %appName%.exe -DUNICODE -O3 -DSTATIC -lwinmm -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread
	@echo off
	goto end

:end
	if %errorlevel% == 0 (
		echo.
		echo Successfully Compiled.
		echo Running %appName%.exe...
		%appName%.exe
	)
```

- this script compiles the source code of your game (MyGame.cpp) and makes its executable code (MyGame.exe)
- if the compilation is successfull, the game starts
- to build the game dynamically enter **"make -d"** or just **"make"** at the command prompt
- to build the game statically enter **"make -s"** at the command prompt  

3. **run.bat**
```shell
MyGame.exe
```

- this script runs the executable code of your game (MyGame.exe)


## License notice
Copyright (C) 2021 Ask For Game Task

All programs in this repository are protected by GNU General Public License version 3.  
If you use them, you must attribute me.

Each program in this repository is free software: 
you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version.

Each program in this repository is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

See the LICENSE file for more details on the GNU General Public License.

