/**############################################################################
#
# @Program		CONSOLE IMAGE CONVERTER
# @File			Converter.c
# @Description	Converts .png image to a binary format using SFML library.
#				The converted image can be displayed in Windows Console
#               by us the Consoler game framework.
#
# @Usage		Converter.exe [folder] [filename]
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

#include <SFML/Graphics.hpp>

#include <windows.h>
#include <math.h>

#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

// windows console palette colors
const int palette[16][3] = {
	{0,0,0},
	{0,0,128},
	{0,128,0},
	{0, 128, 128},
	{128, 0, 0},
	{128, 0, 128},
	{128, 128, 0},
	{192, 192, 192},
	{128, 128, 128},
	{0, 0, 255},
	{0, 255, 0},
	{0, 255, 255},
	{255, 0, 0},
	{255, 0, 255},
	{255, 255, 0},
	{255, 255, 255}
};

// get the closest Console color for the given RGB color
int GetClosestColor(int r, int g, int b)
{
	int colorIndex = 0;
	int colorDistance = 1000;
	
	for (int i = 0; i < 16; i++){
		float distance = sqrt(pow(r - palette[i][0], 2) + pow(g - palette[i][1], 2) + pow(b - palette[i][2], 2));
		
		if (distance < colorDistance){
			colorIndex = i;
			colorDistance = distance;
		}
	}
	
	return colorIndex;
}

// get the best color by using RGB approximation
Color rgbx_approx(int red, int green, int blue, int x) {
	float threshold = (x + 1) * 255 / 3;
	int r = (red > threshold ? 1 : 0);
	int g = (green > threshold ? 1 : 0);
	int b = (blue > threshold ? 1 : 0);
	return Color(r, g, b);
}

// convert a 4-bit RGBI color back to 24-bit RGB
Color rgbi_to_rgb24(int r, int g, int  b, int i) {
	int red = (2*r + i) * 255 / 3;
	int green = (2*g + i) * 255 / 3;
	int blue = (2*b + i) * 255 / 3;
	return Color(red, green, blue);
}

// return the (squared) Euclidean distance between two RGB colors
int color_distance(int red_a, int green_a, int  blue_a, int red_b, int green_b, int blue_b) {
	int d_red = red_a - red_b;
	int d_green = green_a - green_b;
	int d_blue = blue_a - blue_b;
	return (d_red * d_red) + (d_green * d_green) + (d_blue * d_blue);
}

// find the closest 4-bit RGBI approximation (by Euclidean distance) to a 24-bit RGB color
Color rgbi_approx(int red, int green, int blue) {
	// find best RGB0 and RGB1 approximations
	Color c0 = rgbx_approx(red, green, blue, 0);
	Color c1 = rgbx_approx(red, green, blue, 1);

	// convert them back to 24-bit RGB
	Color col0 = rgbi_to_rgb24(c0.r, c0.g, c0.b, 0);
	Color col1 = rgbi_to_rgb24(c1.r, c1.g, c1.b, 1);

	// return the color closer to the original
	int d0 = color_distance(red, green, blue, col0.r, col0.g, col0.b);
	int d1 = color_distance(red, green, blue, col1.r, col1.g, col1.b);

	if (d0 <= d1) return Color(col0.r, col0.g, col0.b);
	else return Color(col1.r, col1.g, col1.b);
}

// save the converted image
bool Save(string fileNameOut, int width, int height, short data[])
{
	FILE *f = nullptr;
	f = fopen(fileNameOut.c_str(), "wb");
	if (f == nullptr)
		return false;

	fwrite(&width, sizeof(int), 1, f);
	fwrite(&height, sizeof(int), 1, f);
	fwrite(data, sizeof(short), width * height, f);

	fclose(f);

	return true;
}

// get the application path
string GetExePath() {
	char filename[MAX_PATH];
	GetModuleFileName(NULL, filename, MAX_PATH);
	
	string path = string(filename);
	return path.substr(0, path.find_last_of( "\\/" ));
}

// main program
int main(int argc, char * argv[])
{
	cout << "\n--------------------------------------------------------------------";
	cout << "\nProgram: Console Image Converter ver. 0.001\n";
	cout << "\nCommand: Converter.exe [folder] [filename]";
	cout << "\n--------------------------------------------------------------------\n";
	
	cout << "\nImage Folder   (Arg 1): " << argv[1];
	cout << "\nImage Filename (Arg 2): " << argv[2];
	
	// generate file names using input arguments
	string imageName = "";
	imageName = imageName + argv[2];

	string folder = "";
	folder = folder + argv[1] + "\\";
	
	string fileNameOut = "";
	fileNameOut = fileNameOut + argv[2];
	
	size_t foundPos = fileNameOut.find("img_");
	if (foundPos == std::string::npos){
		fileNameOut.insert(0, "spr_");
	} else {
		fileNameOut.replace(foundPos, 4, "spr_");
	}
	
	string fileNameIn = folder + argv[2] + ".png";
	string fileNameOut1 = folder + fileNameOut + "_1.bin";
	string fileNameOut2 = folder + fileNameOut + "_2.bin";
	
	// load fonts
	Font font;
	if (!font.loadFromFile(GetExePath()+"\\arial.ttf"))
	{
		cout << "Font error!\n";
	}
	
	// load the original (input) image
	cout << "\n\nLoading image...\n" + fileNameIn +"\n";
	
	Image imageOrig;
	if (!imageOrig.loadFromFile(fileNameIn)){		
		return 0;  // loading failed
	}
	
	// create window
	RenderWindow window(VideoMode(800, 600), "Console Image Converter");	
	
	// create text
	Text text0;
	text0.setFont(font);
	text0.setCharacterSize(16); 
	text0.setFillColor(Color::White);
	text0.setString("Original image: " + imageName + ".png");
	
	Text text1;
	text1.setFont(font);
	text1.setCharacterSize(16); 
	text1.setFillColor(Color::Yellow);
	text1.setString("Converted image: " + fileNameOut + "_1.bin");
	
	Text text2;
	text2.setFont(font);
	text2.setCharacterSize(16); 
	text2.setFillColor(Color::Yellow);
	text2.setString("Converted image: " + fileNameOut + "_2.bin");
	
	// create sprite using the original image
	Texture textureOrig;
	textureOrig.loadFromImage(imageOrig);
	
	Sprite spriteOrig;
	spriteOrig.setTexture(textureOrig);
	spriteOrig.setPosition(10, 35);
	
	// get image size
	int width = imageOrig.getSize().x;
	int height = imageOrig.getSize().y;

	// create temporary image
	Image imageTemp;
	imageTemp.create(width, height, Color::Black);
	
	// create output-1 image
	Image imageOut1;
	imageOut1.create(width, height, Color::Black);
	
	// create output-2 image
	Image imageOut2;
	imageOut2.create(width, height, Color::Black);

	// create array to store the color data of the output images
	short *colorData1 = new short[width * height];
	short *colorData2 = new short[width * height];
	
	// image processing
	cout << "\nConverting image...\n";
	
	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			// processing original image
			Color colorOrig = imageOrig.getPixel(i, j);
			
			int idx1 = GetClosestColor(colorOrig.r, colorOrig.g, colorOrig.b);
			colorData1[j * width + i] = idx1;
			
			Color color1(palette[idx1][0], palette[idx1][1], palette[idx1][2]);
			imageOut1.setPixel(i, j, color1);
						
			// processing temporary image
			Color colorTemp = rgbi_approx(colorOrig.r, colorOrig.g, colorOrig.b);
			imageTemp.setPixel(i, j, colorTemp);
			
			int idx2 = GetClosestColor(colorTemp.r, colorTemp.g, colorTemp.b);
			colorData2[j * width + i] = idx2;
			
			Color color2(palette[idx2][0], palette[idx2][1], palette[idx2][2]);
			imageOut2.setPixel(i, j, color2);
		}
	}
	
	// set text position
	int posX = max(280, 50 + width);
	
	text0.setPosition(10, 5);
	text1.setPosition(posX, 5);
	text2.setPosition(posX, 60 + height);
	
	// create sprite using temporary image
	Texture textureTemp;
	textureTemp.loadFromImage(imageTemp);
	
	Sprite spriteTemp;
	spriteTemp.setTexture(textureTemp);
	spriteTemp.setPosition(10, 90 + height);
	
	// create sprite using output-1 image
	Texture textureOut1;
	textureOut1.loadFromImage(imageOut1);
	
	Sprite spriteOut1;
	spriteOut1.setTexture(textureOut1);
	spriteOut1.setPosition(posX, 35);
	
	// create sprite using output-2 image
	Texture textureOut2;
	textureOut2.loadFromImage(imageOut2);
	
	Sprite spriteOut2;
	spriteOut2.setTexture(textureOut2);
	spriteOut2.setPosition(posX, 90 + height);
	
	// save output images
	cout << "\nSaving image to binary file 1...\n" + fileNameOut1 +"\n";
	Save(fileNameOut1, width, height, colorData1);
	
	cout << "\nSaving image to binary file 2...\n" + fileNameOut2 +"\n";
	Save(fileNameOut2, width, height, colorData2);

	cout << "\nImage processing completed.\n";
	cout << "\n--------------------------------------------------------------------\n";
	cout << "\nClose the window to exit!\n";
	
	// main loop
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::Closed:
					window.close();
					break;
					
				case Event::Resized:
					FloatRect visibleArea(0, 0, event.size.width, event.size.height);
					window.setView(View(visibleArea));
					break;
			}
		}
		
		// rendering
		window.clear();
		
		window.draw(text0);
		window.draw(spriteOrig);
		
		window.draw(text1);
		window.draw(spriteOut1);
		
		window.draw(text2);
		window.draw(spriteOut2);
		
		window.display();
	}
	
	cout << "Bye!\n";

	return 0;
}