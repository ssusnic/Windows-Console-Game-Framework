/**############################################################################
#
# @Program		DEMO #15
# @File			Demo-15.cpp
# @Description	Demo #15 made by using Consoler game framework.
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
	Sprite *fontLarge = new Sprite(BLACK);
	Sprite *fontSmall = new Sprite(BLACK);
	
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
		fontLarge->Load(L".\\assets\\fnt_7x9.bin", 7, 9);
		fontSmall->Load(L".\\assets\\fnt_5x7.bin", 5, 7);
	}
	
	//=========================================================================
	// Updates the main game loop.
	//=========================================================================	
	void Update() override
	{	
		ClearScreen();
		
		int cx = GetCenterX(); // get the screen center

		SetTextProperty(fontLarge, CENTER, 0, WHITE, BLUE);
		DrawBitmapText(L" TEXT DEMO in Windows Console ", cx, 10);
		
		SetTextColor(BLACK, YELLOW);
		DrawBitmapText(L" using bitmap fonts ", cx, 30);
		
		SetTextSpacing(-1);
		SetTextColor(RED, NONE);
		DrawBitmapText(L"Lorem ipsum dolor sit amet, consectetur", cx, 55);
		DrawBitmapText(L"adipiscing elit, sed do eiusmod tempor", cx, 70);
		DrawBitmapText(L"incididunt ut labore et dolore magna aliqua.", cx, 85);
		
		SetTextFont(fontSmall);
		SetTextColor(GREEN);
		DrawBitmapText(L"Ut enim ad minim veniam, quis nostrud exercitation", cx, 110);
		DrawBitmapText(L"ullamco laboris nisi ut aliquip ex ea commodo consequat.", cx, 120);
		DrawBitmapText(L"DUIS AUTE IRURE DOLOR IN REPREHENDERIT IN VOLUPTATE", cx, 130);
		DrawBitmapText(L"VELIT ESSE CILLUM DOLORE EU FUGIAT NULLA PARIATUR.", cx, 140);
		
		SetTextFont(fontLarge);
		SetTextColor(CYAN);
		SetTextAlign(LEFT);
		DrawBitmapText(L"Left Align", 5, 165);
		
		SetTextColor(GREY);
		SetTextAlign(RIGHT);
		DrawBitmapText(L"Right Align", 315, 165);
		
		SetTextColor(MAGENTA);
		SetTextAlign(CENTER);
		DrawBitmapText(L"Center Align", cx, 165);
		
		SetTextSpacing(1);
		SetTextColor(YELLOW, DARK_GREY);
		DrawBitmapText(L"AskForGameTask (C) 2021", cx, 185);
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