/**############################################################################
#
# @Program		DEMO #10
# @File			Demo-10.cpp
# @Description	Demo #10 made by using Consoler game framework.
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
	Sprite *sprImage = new Sprite();
	
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
		sprImage->Load(L".\\assets\\spr_julija_2.bin", 320, 200);
		sprImage->SetVisible(true);
	}
	
	//=========================================================================
	// Updates the main game loop.
	//=========================================================================	
	void Update() override
	{	
		ClearScreen();
		DrawSprite(sprImage);
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