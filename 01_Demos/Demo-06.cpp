/**############################################################################
#
# @Program		DEMO #6
# @File			Demo-06.cpp
# @Description	Demo #6 made by using Consoler game framework.
#
# @Author		Srdjan Susnic
# @Website		https://www.askforgametask.com
# @Github		https://www.github.com/ssusnic
# @Youtube		https://www.youtube.com/ssusnic
#
# Copyright (C) 2021 Ask For Game Task
# 
# This program is protected by GNU General Public License version 3.
# If you use it, you must attribute me.
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You can view this license here:
# https://opensource.org/licenses/GPL-3.0
#
#############################################################################*/

// include interface of the Consoler framework
#include "Consoler.h"

/******************************************************************************
*
* Game class - inherits Consoler class.
*
******************************************************************************/

class Game : public Consoler
{
private:
	int counter = 0;
	
public:
	//=========================================================================
	// Inherits Consoler constructor.
	//=========================================================================
	using Consoler::Consoler;
	
	//=========================================================================
	// Sets up the game objects.
	//=========================================================================
	void Setup() override
	{
		// initialize random seed
		srand(time(NULL));
	}
	
	//=========================================================================
	// Updates the main game loop.
	//=========================================================================	
	void Update() override
	{	
		if (counter == 0){
			ClearScreen();
			
			DrawLine(10, 10, 310, 10, RED);
			DrawLine(310, 10, 310, 190, BLUE);
			DrawLine(310, 190, 10, 190, YELLOW);
			DrawLine(10, 190, 10, 10, DARK_GREEN);
			
			counter = 20;
			
		} else {
			DrawLine(
				Util::Rand(0, GetCanvasW()), 
				Util::Rand(0, GetCanvasH()),
				Util::Rand(0, GetCanvasW()), 
				Util::Rand(0, GetCanvasH()),
				Util::Rand(1, 15)
			);
			
			counter--;
		}	
	}
};

/******************************************************************************
*
* Main program
*
******************************************************************************/

int main(){
	// initialize a new game
	Game game(L"Consoler Demo", 320, 200, 1, 1, 60);
	
	// run the main game loop
	game.Run();
	
	return 0;
}