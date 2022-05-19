#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Options
{
private:
	//Variables
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;

	//Mouse Position
	Vector2i mousePosWindow;
	Vector2f mousePosView;

	//Font
	sf::Font font;
	sf::Font fontTitle;
	sf::Font fontSelect;

	//File
	std::fstream file;
	
	//Text
	sf::Text uiText;
	sf::Text subTitle;
	sf::Text subTitle1;
	sf::Text presets[5];
	sf::Text healthText[5];
	sf::Text enemiesOnScreen[5];
	sf::Text enemiesSpeed[5];
	sf::Text lineDevider;
	sf::Text deleteData[3];
	sf::Text confirmSave;
	sf::Text clear;
	sf::Text backToMain;

	//BG Music
	sf::Music music;

	//Images
	sf::Texture background;

	//Option Variables
	std::string preset;
	std::string health;
	std::string enemiesOnScreenNum;
	std::string enemiesSpeedNum;
	std::string deleteConsent;

	//checkers
	bool isCustomSelected;
	bool presetSelected;
	bool healthSelected;
	bool enemiesOnScreenSelected;
	bool enemiesSpeedSelected;
	bool deleteDataSelected;
	bool confirmSaveSelected;

	void initializeVariables();
	void initWindow();
	void initText();
	void FixedText();
	void DynamicText();
	void saveToVariable(int from,int i);
	void updateSelected();
	void updateDataRemove();
	void clearFields();
	void initMusic();
	void initFonts();
	void initFile();
	void handelconfirmSave();
	void saveFile();
	void deleteFiles();
	void initTextures();

public:

	Options();
	virtual ~Options();

	//Accessors
	const bool running() const;

	//Functions
	void pollEvents();
	void updateMousePos();
	void closeGame();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderBackground(sf::RenderTarget& target);

	void render();
};

