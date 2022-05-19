#pragma once

#include <random>
#include <functional>

#include <iostream>
#include <stdio.h>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts the game engine.
	Wrapper class.
*/
using namespace sf;

class Game
{
private:
	//Variables
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

	//Mouse positions
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//Font
	sf::Font font;

	//Text
	sf::Text uiText;
	sf::Text backToMain;

	//File
	std::fstream file;
	std::fstream scoreFile;
	std::fstream optionFile;
	std::fstream leaderboardFile;

	//BG Music
	sf::Music music;

	//Images
	sf::Texture background;
	sf::Texture e1;
	sf::Texture e2;
	sf::Texture e3;
	sf::Texture e4;
	sf::Texture e5;
	sf::Texture err;

	//Game logic
	bool endGame;
	unsigned points;
	unsigned speedY;
	int health;
	int highscore;
	float SpawnTimer;
	float SpawnTimerMax;
	int maxSpawns;
	bool mouseHeld;
	std::string readHighscore;
	std::string readHealth;
	std::string readEnemiesOnScreen;
	std::string readEnemiesSpeed;
	std::string readDifficulty;

	//Game objects
	std::vector<RectangleShape> boxes;
	RectangleShape box;
	RectangleShape uiTextBox;

	//Private functions
	void initializeVariables();
	void initWindow();
	void savePointsToLeader();
	void initFonts();
	void initTextures();
	void initText();
	void initFile();
	void initMusic();
	void initEnemies();

public:

	//constructors and Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();

	void closeGame();
	void updateText();
	void updateBox();
	void saveHsFile();
	void savePointsFile();
	void readOptionFile();
	void loadHsFile();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderBoxes(sf::RenderTarget& target);
	void renderBackground(sf::RenderTarget& target);

	void render();
};