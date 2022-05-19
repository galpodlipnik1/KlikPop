#pragma once

#include <iostream>
#include <functional>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class EndMenu
{
private:
	//Variables
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

	//leaderboard array
	int leaderboardArr[100];
	int numOfLines;
	
	std::string dateArr[100];
	
	//Font
	sf::Font font;

	//file
	std::fstream file;

	//Text
	sf::Text uiText;
	sf::Text leaderboardText[6];
	sf::Text playAgain;

	//BG Music
	sf::Music music;

	//Images
	sf::Texture background;

	void initializeVariables();
	void initWindow();
	void checkNumOfLines();
	void readFile();
	void outputArr();
	int swapElement(int arr[], int p, int r);
	void SortArr(int arr[], int p, int r);
	void sortLeaderboard();
	void initText();
	void initMusic();
	void initFonts();
	void initTextures();
	void initLText();

public:

	EndMenu();
	virtual ~EndMenu();

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

