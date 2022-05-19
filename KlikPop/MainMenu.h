#pragma once

#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;


#define Max_main_menu 4
class MainMenu
{
	//Public Attributes
public:
	MainMenu(float width, float height);

	void draw(RenderWindow& window);
		Vector2f getMousePos(RenderWindow& window);

	~MainMenu();
	//Private Attributes
	Text mainMenu[Max_main_menu];
	Text rights;
private:
	
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	
	string readScore;
	
	Texture MainMenuBG;
	Font font,titleFont;
	Text title,subtitle;
};

