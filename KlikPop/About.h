#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class About
{
private:
	//Variables
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;
	
	//Font
	sf::Font font;
	sf::Font font1;

	//Text
	sf::Text uiText;
	sf::Text text;
	sf::Text backToMain;

	//BG Music
	sf::Music music;

	//Images
	sf::Texture background;

	void initializeVariables();
	void initWindow();
	void initText();
	void initMusic();
	void initFonts();
	void initTextures();
	
public:
	
	About();
	virtual ~About();

	//Accessors
	const bool running() const;
	
	//Functions
	void pollEvents();
	void closeGame();
	void updateText();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderBackground(sf::RenderTarget& target);

	void render();
};

