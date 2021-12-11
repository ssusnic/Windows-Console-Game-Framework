/**############################################################################
#
# @Program		DEMO #17
# @File			Demo-17.cpp
# @Description	Demo #17 made by using Consoler game framework.
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
	Sprite *sprTree = new Sprite(BLACK);
	Sprite *sprTreeHi = new Sprite();
	Sprite *sprTreeLo = new Sprite();
	
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
		// load a tree sprite
		sprTree->Load(L".\\assets\\spr_tree_1.bin", 30, 50);
		sprTree->SetPosition(150, 150);
		sprTree->SetVisible(true);
		
		// create a high tree by copying and scaling up the original tree
		*sprTreeHi = *sprTree;
		sprTreeHi->SetPosition(220, 50);
		sprTreeHi->SetScale(2, 3);
		
		// create a low tree by copying and scaling down the original tree
		*sprTreeLo = *sprTree;
		sprTreeLo->SetPosition(70, 175);
		sprTreeLo->SetScale(0.8, 0.5);
	}
	
	//=========================================================================
	// Updates the main game loop.
	//=========================================================================	
	void Update() override
	{	
		ClearScreen(DARK_BLUE);
		
		// draw trees
		DrawSprite(sprTree);
		DrawSprite(sprTreeHi);
		DrawSprite(sprTreeLo);
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