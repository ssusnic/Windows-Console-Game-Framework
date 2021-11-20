/**############################################################################
#
# @Program		DEMO #8
# @File			Demo-08.cpp
# @Description	Demo #8 made by using Consoler game framework.
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
		ClearScreen();
	
		if (counter == 0) counter = 100;
		else counter--;
		
		DrawRectanglePercent(60, 20, 200, 20, RED, WHITE, 2, counter/100.0, true);
		DrawRectanglePercent(150, 60, 20, 120, GREEN, WHITE, 2, counter/100.0, false);	
		
		DrawRectangleCoord(0, 10, 10, 190, MAGENTA);
		DrawRectangleCoord(310, 10, 320, 190, DARK_YELLOW);
		DrawRectangleCoord(0, 0, 320, 10, GREY);
		DrawRectangleCoord(0, 190, 320, 200, DARK_BLUE);
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