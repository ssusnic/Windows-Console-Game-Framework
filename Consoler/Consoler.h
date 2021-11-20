/**############################################################################
#
# @Program		CONSOLER v0.001
# @File			Consoler.h (header file: interface with declarations)
# @Description	A game framework for making games in C++ for Windows Console.
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

//=============================================================================
// Directives to properly use classes from the Consoler framework.
// Add the following switches to the compiler options:
//		- "-DSTATIC" for building and using a static library
//		- "-DEXPORT" for building dynamic library (exporting to a DLL)
//		- no switch for using dynamic library (importing from a DLL)
//=============================================================================

#ifdef STATIC
	#define UTIL
	#define AUDIO
	#define SPRITE
	#define CONSOLER
#elif EXPORT
	#define UTIL __declspec(dllexport)
	#define AUDIO __declspec(dllexport)
	#define SPRITE __declspec(dllexport)
	#define CONSOLER __declspec(dllexport)
#else
	#define UTIL __declspec(dllimport)
	#define AUDIO __declspec(dllimport)
	#define SPRITE __declspec(dllimport)
	#define CONSOLER __declspec(dllimport)
#endif

//=============================================================================
// included standard library header files.
//=============================================================================

#include <Windows.h>
#include <VersionHelpers.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

//=============================================================================
// Globals
//=============================================================================

// a constant value for parameters that we want to ignore by default
#define NONE -1

// Console color palette
enum {
	BLACK		,
	DARK_BLUE	,	
	DARK_GREEN	,
	DARK_CYAN	,
	DARK_RED	,
	DARK_MAGENTA,
	DARK_YELLOW	,
	GREY		,
	DARK_GREY	,
	BLUE		,
	GREEN		,
	CYAN		,
	RED			,
	MAGENTA		,
	YELLOW		,
	WHITE		
};

// Text alignments
enum {
	LEFT	,
	CENTER	,	
	RIGHT	
};

// Key structure
struct Key {
	int vkCode;
	bool stateOld = false;
	bool stateNew = false;
	bool isUp = true;
	bool isDown = false;
	bool isPressed = false;
	bool isReleased = false;
};

// Rectangle structure
struct Rect {
	int x1=0, y1=0;	// top-left coords
	int x2=0, y2=0;	// bottom-right coords
	int cx=0, cy=0;	// center coords
};

/******************************************************************************
*
* Util class
*
******************************************************************************/

class UTIL Util
{
public:
	//=========================================================================
	// Returns a random number in the given range.
	//=========================================================================
	static int Rand(int min, int max);
	
	//=========================================================================
	// Wraps a value within the given range.
	//=========================================================================
	static int Wrap(int value, int min, int max);
	
	//=========================================================================
	// Returns true if a point (px, py) is inside a circle (cx, cy, radius).
	//=========================================================================
	static bool IsPointInCircle(int px, int py, int cx, int cy, int radius);
	
	//=========================================================================
	// Returns distance between two points.
	//=========================================================================
	static int Distance(int p1x, int p1y, int p2x, int p2y, bool root = false);
	
	//=========================================================================
	// Returns modulo of floating point numbers.
	//=========================================================================
	static float Mod(float a, float b, bool isResultPositive = true);
};

/******************************************************************************
*
* Audio class
*
******************************************************************************/

class AUDIO Audio
{
private:
	// sound on/off flag
	static bool isSoundOn;
	
	// duration of the currently played sound
	static float duration;
	
	// the start time of playing sound
	static chrono::system_clock::time_point timeStart;
	
public:
	//=========================================================================
	// 	Sets the sound on/off.
	//=========================================================================
	static void SetSound(bool bSoundOn);

	//=========================================================================
	// Returns the sound on/off.
	//=========================================================================
	static bool IsSound();

	//=========================================================================
	// Plays a wav sound (please note that only one sound can be played!).
	//=========================================================================
	static void Play(
		LPCWSTR sndName, float sndDuration = 0, bool sndPriority = false
	);
};

/******************************************************************************
*
* Sprite class
*
******************************************************************************/

class SPRITE Sprite
{
private:
	// image size
	int imageW;
	int imageH;
	
	// current frame
	int frame;
	
	// coordinates of the current frame in the image
	int frameX;
	int frameY;
	
	// dimensions of the single frame
	int frameW;
	int frameH;
	
	// number of frames per rows and columns in the image
	int framesInRow;
	int framesInCol;
	
	// total number of frames
	int framesTotal;
	
	// transparent color
	short transparent;
	
	// array of pixel colors that make up this sprite
	short *pixels = nullptr;
	
	// animation structure
	struct Animation {
		vector<short> sequence;	// sequence of frames
		short index;			// current frame index of the sequence
		float duration;			// frame duration in seconds
		chrono::system_clock::time_point timeStart;	// frame starting time
		short loops;			// number of played loops
	};;
	
	// map of all animations for this sprite
	map<string, Animation> mapOfAnimations;
	
	// current animation
	Animation currAnimation;
	
	// sprite boundary used for collision detection
	Rect bound;
	
	// scaling factors
	float scaleX = 0;
	float scaleY = 0;
	
	// size of the scaled sprite
	int width = 0;
	int height = 0;
	
	// radius (half of the width/height) of the scaled sprite
	float rx, ry;
	
	// bigger radius of rx and ry
	float radius;
	
public:
	// top-left position
	float x = 0, y = 0;
	
	// velocity
	float vx = 0, vy = 0;
	
	// acceleration
	float ax = 0, ay = 0;
	
	// is it visible?
	bool isVisible = false;
	
	// is it alive?
	bool isAlive = false;
	
	// helper variables
	int counter = 0;	// for counting something
	int lives = 0; 		// number of lives
	int health = 0;		// health
	
	//=========================================================================
	// Constructor
	//=========================================================================
	Sprite(short transparentColor = NONE);

	//=========================================================================
	// Loads a binary file that contains pixel colors of the sprite.
	// (if the file cannot be loaded then a green solid sprite is created)
	//=========================================================================
	bool Load(wstring fileName, int frameWidth = 0, int frameHeight = 0);
	
	//=========================================================================
	// Sets the scaling factors.
	//=========================================================================
	void SetScale(float fScaleX, float fScaleY);
	
	//=========================================================================
	// Sets the current frame.
	//=========================================================================
	void SetFrame(int nFrame = 1);
	
	//=========================================================================
	// Sets the next frame by increasing the current frame 
	// for the specified number of steps.
	//=========================================================================
	void NextFrame(int steps);
	
	//=========================================================================
	// Adds a new animation sequence to the map of animations.
	//=========================================================================
	void AddAnimation(string name, vector<short> sequence, float duration = 0);
	
	//=========================================================================
	// Sets the current animation sequence.
	//=========================================================================
	void SetAnimation(string name, short frameOffset = 0);
	
	//=========================================================================
	// Plays the animation sequence.
	//=========================================================================	
	void PlayAnimation(short frameOffset = 0);
	
	//=========================================================================
	// Returns true if the animation played for the given number of loops.
	//=========================================================================
	bool IsAnimationPlayed(int numOfLoops);

	//=========================================================================
	// Returns the color of a pixel.
	//=========================================================================
	short GetPixelColor(int x, int y);
	
	//=========================================================================
	// Returns true if the given color is transparent.
	//=========================================================================
	bool IsTransparent(short color);
	
	//=========================================================================
	// Returns the sprite width.
	//=========================================================================	
	int GetW();
	
	//=========================================================================
	// Returns the sprite height.
	//=========================================================================
	int GetH();
	
	//=========================================================================
	// Returns the current frame.
	//=========================================================================
	int GetFrame();
	
	//=========================================================================
	// Returns the number of frames in row.
	//=========================================================================
	int GetFramesInRow();
	
	//=========================================================================
	// Returns the number of frames in column.
	//=========================================================================
	int GetFramesInCol();
	
	//=========================================================================
	// Returns the total number of frames.
	//=========================================================================
	int GetTotalFrames();
	
	//=========================================================================
	// Sets the visibility.
	//=========================================================================
	void SetVisible(bool bVisible);
	
	//=========================================================================
	// Sets the acceleration.
	//=========================================================================
	void SetAccel(float accelX, float accelY);
	
	//=========================================================================
	// Sets the velocity.
	//=========================================================================
	void SetVelocity(float velX, float velY);
	
	//=========================================================================
	// Sets the current XY position.
	//=========================================================================
	void SetPosition(float posX, float posY);
	
	//=========================================================================
	// Updates the current XY position.
	//=========================================================================
	void UpdatePosition();
	
	//=========================================================================
	// Updates the sprite boundaries relative to its current XY position.
	// CALL THIS FUNCTION EVERYTIME WHEN CHANGING THE SPRITE POSITION!
	//=========================================================================
	void UpdateBound();
	
	//=========================================================================
	// Returns the sprite boundaries.
	//=========================================================================
	Rect GetBound();
	
	//=========================================================================
	// Returns the sprite center X coord.
	//=========================================================================
	int GetCX();
	
	//=========================================================================
	// Returns the sprite center Y coord.
	//=========================================================================
	int GetCY();
	
	//=========================================================================
	// Returns the sprite radius in X direction.
	//=========================================================================
	float GetRX();
	
	//=========================================================================
	// Returns the sprite radius in Y direction.
	//=========================================================================
	float GetRY();
	
	//=========================================================================
	// Returns the sprite max radius.
	//=========================================================================
	float GetRadius();
	
	//=========================================================================
	// Returns distance between centers of this sprite and another one.
	//=========================================================================
	int DistanceTo(Sprite *otherSprite, bool root = false);
	
	//=========================================================================
	// Checks the circle-circle collision between this sprite and another one.
	//=========================================================================
	bool IsCircleCollision(Sprite *otherSprite);		
	
	//=========================================================================
	// Checks the rect-rect collision between this sprite and another one.
	//=========================================================================
	bool IsRectCollision(Sprite *otherSprite);
	
	//=========================================================================
	// Checks the pixel-pixel collision between this sprite and another one.
	//=========================================================================
	bool IsPixelCollision(Sprite *otherSprite);
	
	//=========================================================================
	// Checks if the center of this sprite is within the circle 
	// that surrounds another sprite.
	//=========================================================================
	bool IsCenterInCircle(Sprite *otherSprite);
	
	//=========================================================================
	// Checks if the center of this sprite is within a specified circle.
	//=========================================================================
	bool IsCenterInCircle(int circleX, int circleY, int circleR);
};

/******************************************************************************
*
* Consoler class
*
******************************************************************************/

class CONSOLER Consoler
{
private:
	// name of the game
	wstring gameName;
	
	// Console handlers
	HANDLE handleIn;
	HANDLE handleOut;
	
	// previous Console mode
	DWORD prevConsoleMode;
	
	// Console window rectangle
	SMALL_RECT windowRect;
	
	// canvas buffer used to draw pixels on it
	WORD *bufCanvas = nullptr;
	
	// window buffer used to zoom the canvas
	WORD *bufWindow = nullptr;

	// canvas size
	int canvasW;		// canvas width
	int canvasH;		// canvas height
	int canvasArea;		// canvas area	 = canvasW * canvasH
	
	// zooming params
	int zoomX; 			// zoom of the canvas in X direction
	int zoomY;			// zoom of the canvas in Y direction
	
	// window size
	int windowW;		// window width  = canvasW * zoomX
	int windowH;		// window height = canvasH * zoomY
	int windowArea;		// window area	 = windowW * windowH
	
	// pixels background color offset
	short backColorOffset = 16;
	
	// Console font attributes
	wstring fontName; 	// font name
	short fontSize;		// font size
	UINT fontWeight;	// font weight
	
	// list of the font names
	wstring fontNameList[5] = {
		L"Consolas",
		L"Lucida Console",
		L"Raster",
		L"ProggyCleanTT NF",
		L"TerminessTTF NF"
	};
	
	// timer
	float desiredTime;	// desired elapsed time between two frames
	float elapsedTime;	// real elapsed time between two frames
	float fps;			// frames per second
	
	chrono::system_clock::time_point time1; // starting time of the frame
	chrono::system_clock::time_point time2; // ending time of the frame
	
	// keys
	Key keyF1    = {VK_F1};		// F1    - set font name
	Key keyF3    = {VK_F3};		// F3    - set font size
	Key keyF4    = {VK_F4};		// F4    - set font weight
	Key keyF5    = {VK_F5};		// F5    - set zoom X
	Key keyF6    = {VK_F6};		// F6    - set zoom Y
	Key keyF7    = {VK_F7};		// F7    - set the next config
	Key keyF8    = {VK_F8};		// F8    - set the default config
	Key keyShift = {VK_SHIFT};	// SHIFT - invert direction of changing settings
	Key keyP     = {0x50};		// P     - pause/resume
	Key keyEsc   = {VK_ESCAPE};	// ESC   - game exit
	
	// mouse buttons
	Key mouse[5];
	
	// mouse coordinates
	int mouseX;
	int mouseY;
	
	// bitmap text properties
	struct TextProperty {
		Sprite *sprFont = nullptr;
		short align = LEFT;
		short spacing = 0;
		short fgColor = WHITE;
		short bgColor = NONE;
	} textProperty;

	// structure that contains changeable game configuration parameters
	struct Configuration {
		wstring fontName;
		short fontSize;
		UINT fontWeight;
		int zoomX;
		int zoomY;
	};
	
	// a list of all user-defined game configurations
	vector<Configuration> vecConfigs;
	
	// index number of the current configuration
	int currConfig;
	
	// true if the game is quit	
	static bool quit;
	
	// true if the game is paused
	static bool paused;
	
public:
	//=========================================================================
	// Constructor - creates a new Console.
	//=========================================================================	
	Consoler(
		wstring wsGameName = L"", 
		int cols = 160, 
		int rows = 100, 
		int nZoomX = 1, 
		int nZoomY = 1, 
		float desiredFPS = 60
	);

	//=========================================================================
	// Destructor
	//=========================================================================
	~Consoler();
	
	//=========================================================================
	// Sets the Console font properties.
	//=========================================================================
	void SetConsoleFont(
		wstring name = L"Consolas",	short size = 2, UINT weight = FW_NORMAL
	);

	//=========================================================================
	// Updates the Console window.
	//=========================================================================
	bool UpdateWindow();

	//=========================================================================
	// Control handler routine.
	//=========================================================================
	static BOOL CtrlHandler(DWORD signal);
	
	//=========================================================================
	// Runs the Main Game Loop!
	//=========================================================================
	void Run();
	
	//=========================================================================
	// Override these methods in your game!
	//=========================================================================
	virtual void Setup();
	virtual void Update();
	virtual void ShowPauseInfo();

	//=========================================================================
	// Adds a new configuration to the list.
	//=========================================================================
	void AddConfig(
		wstring fntName, short fntSize, UINT fntWeight, int nZoomX, int nZoomY
	);

	//=========================================================================
	// Returns elapsed time since the last frame.
	//=========================================================================
	float GetElapsedTime();

	//=========================================================================
	// Returns the Canvas width.
	//=========================================================================
	int GetCanvasW();

	//=========================================================================
	// Returns the Canvas height.
	//=========================================================================
	int GetCanvasH();
	
	//=========================================================================
	// Returns the X coordinate of the canvas center.
	//=========================================================================
	int GetCenterX();
	
	//=========================================================================
	// Returns the Y coordinate of the canvas center.
	//=========================================================================
	int GetCenterY();
	
	//=========================================================================
	// Clears the screen.
	//=========================================================================
	void ClearScreen(short color = BLACK);

	//=========================================================================
	// Clears the screen without back color offset.
	//=========================================================================
	void ClearScreen2(short color = BLACK);

	//=========================================================================
	// Draws a pixel.
	//=========================================================================
	void DrawPixel(int x, int y, short color);
	
	//=========================================================================
	// Gets the pixel color.
	//=========================================================================
	short GetPixelColor(int x, int y);
	
	//=========================================================================
	// Draws a line using the digital differential analyzer (DDA) algorithm.
	//=========================================================================
	void DrawLine(int x1, int y1, int x2, int y2, short color);

	//=========================================================================
	// Draws a rectangle at XY using its width and height.
	//=========================================================================
	void DrawRectangle(int x, int y, int width, int height, short color);
	
	//=========================================================================
	// Draws a rectangle using its top-left and bottom-right coords.
	//=========================================================================
	void DrawRectangleCoord(int x1, int y1, int x2, int y2, short color);
	
	//=========================================================================
	// Draws a bordered rectangle at XY using its width, height and stroke.
	//=========================================================================
	void DrawRectangleBorder(
		int x, int y, int width, int height, 
		short fillColor, short strokeColor, int strokeSize
	);
	
	//=========================================================================
	// Draws a bordered rectangle filled with the specified percentage 
	// at position XY using its width, height and stroke.
	//=========================================================================
	void DrawRectanglePercent(
		int x, int y, int width, int height, 
		short fillColor, short strokeColor, int strokeSize, 
		float percent = 1, bool isHor = true
	);

	//=========================================================================
	// Draws a circle.
	//=========================================================================
	void DrawCircle(
		int cx, int cy, int radius, 
		short strokeColor, short fillColor = NONE
	);
	
	//=========================================================================
	// Draws a sprite.
	// Specify fgColor to fill all non-transparent pixels in that color.
	//=========================================================================
	void DrawSprite(Sprite *sprite, short fgColor = NONE);
	
	//=========================================================================
	// Draws a sprite at the given XY coordinate.
	// Specify fgColor to fill all non-transparent pixels in that color.
	//=========================================================================
	void DrawSprite(Sprite *sprite, float x, float y, short fgColor = NONE);
	
	//=========================================================================
	// Draws a solid sprite.
	// Specify fgColor to fill all non-transparent pixels in that color.
	// Specify bgColor to fill all transparent pixels in that color.
	//=========================================================================
	void DrawSpriteSolid(
		Sprite *sprite, short fgColor = NONE, short bgColor = BLACK
	);
	
	//=========================================================================
	// Draws a solid sprite at the given XY coordinate.
	// Specify fgColor to fill all non-transparent pixels in that color.
	// Specify bgColor to fill all transparent pixels in that color.
	//=========================================================================
	void DrawSpriteSolid(
		Sprite *sprite, float x, float y, 
		short fgColor = NONE, short bgColor = BLACK
	);
	
	//=========================================================================
	// Draw a rectangle that surrounds the sprite.
	//=========================================================================
	void DrawSpriteRect(Sprite *sprite, short color = GREEN);
	
	//=========================================================================
	// Draw a circle that surrounds the sprite.
	//=========================================================================
	void DrawSpriteCircle(
		Sprite *sprite, short strokeColor = GREEN, short fillColor = NONE
	);
	
	//=========================================================================
	// Draws a bitmap text at XY position using the given alignment 
	// and optionally defined fore and back color.
	//=========================================================================
	void DrawBitmapText(
		wstring text, int x, int y, 
		short align, short fgColor = NONE, short bgColor = NONE
	);
	
	//=========================================================================
	// Draws a bitmap text at XY position using the predefined text properties.
	//=========================================================================
	void DrawBitmapText(wstring text, int x, int y);
	
	//=========================================================================
	// Sets the bitmap text properties all at once.
	//=========================================================================
	void SetTextProperty(
		Sprite *sprFont, 
		short align, 
		short spacing, 
		short fgColor, 
		short bgColor
	);
	
	//=========================================================================
	// Sets the sprite with the bitmap fonts.
	//=========================================================================
	void SetTextFont(Sprite *sprFont);
	
	//=========================================================================
	// Sets the bitmap text alignment.
	//=========================================================================
	void SetTextAlign(short align);
	
	//=========================================================================
	// Sets the bitmap text spacing.
	//=========================================================================
	void SetTextSpacing(short spacing);
	
	//=========================================================================
	// Sets the bitmap text foreground and background color.
	//=========================================================================
	void SetTextColor(short fgColor, short bgColor = -100);
	
	//=========================================================================
	// Sets the bitmap text foreground color.
	//=========================================================================
	void SetTextForeColor(short fgColor);

	//=========================================================================
	// Sets the bitmap text background color.
	//=========================================================================
	void SetTextBackColor(short bgColor);
	
	//=========================================================================
	// Draws the title bar rectangle.
	//=========================================================================
	void DrawTitleBar(int height = 9, short color = GREY);
	
	//=========================================================================
	// Draws the status bar rectangle.
	//=========================================================================
	void DrawStatusBar(int height = 9, short color = DARK_BLUE);
	
	//=========================================================================
	// Draws the key info in the title bar.
	//=========================================================================
	void DrawTitleBarInfo(
		wstring textLeft = L"",	
		wstring textRight = L"",
		short barColor = GREY, 
		int dx = 0, 
		int dy = 0
	);
	
	//=========================================================================
	// Draws the current config info in the status bar.
	//=========================================================================
	void DrawStatusBarInfo(
		short info = 0,
		short barColor = DARK_GREY,
		int dx = 0,
		int dy = 0
	);
	
	//=========================================================================
	// Draws a pause dialog showing the current console configuration.
	//=========================================================================
	void DrawPauseDialog(
		short fillColor = GREY, 
		short strokeColor = NONE, 
		int strokeSize = 0
	);

	//=========================================================================
	// Draws the console title
	//=========================================================================
	void DrawConsoleTitle();
	
	//=========================================================================
	// Redraws the entire Console screen.
	//=========================================================================
	void RedrawScreen();

	//=========================================================================
	// Handles a key input.
	//=========================================================================
	void HandleKey(Key *key);
	
	//=========================================================================
	// Handles a mouse input.
	//=========================================================================
	void HandleMouse();
	
	//=========================================================================
	// Returns the current state of the specified mouse button.
	// (left button = 0, right button = 1, middle button = 2)
	//=========================================================================
	Key Mouse(int button = 0);
	
	//=========================================================================
	// Returns the mouse X position.
	//=========================================================================
	int MouseX();
	
	//=========================================================================
	// Returns the mouse Y position.
	//=========================================================================
	int MouseY();
	
private:		
	//=========================================================================
	// Starts timer.
	//=========================================================================
	void StartTimer();
	
	//=========================================================================
	// Stops timer and calculates elapsed time and fps between two frames.
	//=========================================================================
	void StopTimer();
		
	//=========================================================================
	// Handles settings.
	//=========================================================================
	void HandleSettings();

	//=========================================================================
	// Handles inputs to pause/resume/quit the game.
	//=========================================================================
	void HandlePauseQuit();
};
