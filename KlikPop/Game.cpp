#include "Game.h"


//Private functions
void Game::initializeVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->readHighscore = "";
	this->highscore = 0;
	this->health = std::stoi(this->readHealth);
	this->speedY = std::stoi(this->readEnemiesSpeed);
	this->SpawnTimerMax = 20.f;
	this->SpawnTimer = this->SpawnTimerMax;
	this->maxSpawns = std::stoi(this->readEnemiesOnScreen);
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new RenderWindow(this->videoMode, "KlikPop Game", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::savePointsToLeader()
{
	int numOfLines = 0;
	this->leaderboardFile.open("leaderboard.txt", std::ios::out | std::ios::in);

	if (this->leaderboardFile.is_open())
	{
		this->leaderboardFile.seekg(0, std::ios::end);
		this->leaderboardFile << std::endl;
		this->leaderboardFile << this->points;
		this->leaderboardFile.close();
	}
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("fonts/Mukta-Bold.ttf")) std::cout << "Error loading font" << std::endl;
}

void Game::initTextures()
{
	int r = rand() % (5 - 1 + 1) + 1;
	std::string randBG = "images/bg" + std::to_string(r) + ".png";
	if (!this->background.loadFromFile(randBG)) std::cout << "Error loading the background" << std::endl;
	if (!this->e1.loadFromFile("images/e1.png")) std::cout << "Error loading the enemy1 texture" << std::endl;
	if (!this->e2.loadFromFile("images/e2.png")) std::cout << "Error loading the enemy1 texture" << std::endl;
	if (!this->e3.loadFromFile("images/e3.png")) std::cout << "Error loading the enemy1 texture" << std::endl;
	if (!this->e4.loadFromFile("images/e4.png")) std::cout << "Error loading the enemy1 texture" << std::endl;
	if (!this->e5.loadFromFile("images/e5.png")) std::cout << "Error loading the enemy1 texture" << std::endl;
	if (!this->err.loadFromFile("images/err.png")) std::cout << "Error loading the enemy1 texture" << std::endl;
}

void Game::initText()
{
	//init text
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setPosition(sf::Vector2f(6.f, 3.f));
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
	//init text box
	this->uiTextBox.setSize(Vector2f(170.f, 120.f));
	this->uiTextBox.setFillColor(sf::Color::Transparent);
	this->uiTextBox.setOutlineColor(sf::Color::White);
	this->uiTextBox.setOutlineThickness(5);
	this->uiTextBox.setPosition(sf::Vector2f(3.f, 3.f));

	this->backToMain.setFont(this->font);
	this->backToMain.setCharacterSize(20);
	this->backToMain.setPosition(sf::Vector2f(720.f, 10.f));
	this->backToMain.setFillColor(sf::Color::White);
	this->backToMain.setString("Go back");
}

void Game::initFile()
{
	std::fstream f;
	f.open("highscore.txt", std::ios::app);
	f.close();

	std::fstream s;
	s.open("score.txt", std::ios::app);
	s.close();

	std::fstream h;
	h.open("options.txt", std::ios::app);
	h.close();

	std::fstream e;
	e.open("leaderboard.txt", std::ios::app);
	//check if file is empty
	e.seekg(0, std::ios::end);
	if (e.tellg() == 0)
	{
		e << "0";
	}
	e.close();
}

void Game::initMusic()
{
	if (!this->music.openFromFile("music/bgMusic.ogg")) std::cout << "Error loading the music" << std::endl;
	this->music.setPlayingOffset(sf::seconds(57.5f));
	this->music.setVolume(15.f);
	this->music.setLoop(true);
	this->music.play();
}

void Game::initEnemies()
{
	this->box.setPosition(10.f, 10.f);
	this->box.setSize(Vector2f(100.f, 100.f));
	this->box.setScale(Vector2f(0.5f, 0.5f));
	//this->box.setFillColor(sf::Color::Transparent);
}

//Constructors and Destructors
Game::Game()
{
	this->initFile();
	this->readOptionFile();
	this->initializeVariables();
	this->initWindow();
	this->initTextures();
	this->initFonts();
	this->initText();
	//this->initMusic(); //un comment this if you want to play the music
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Function
void Game::spawnEnemy()
{
	/*
		@return void
		Spawns box and sets their colors, types and positions randomly.
		-sets a random size
		-sets a random position.
		-sets a random color.
		-Adds enemy to the vector
	*/

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(1, 700);
	auto getRnd = std::bind(dist, rng);
	this->box.setPosition(getRnd(), 0.f);

	//randomise enemy type
	int type = rand() % 101; //1: 30 2: 25 3: 25 2: 15 1: 5
	if (type >= 0 && type <= 30)
	{
		this->box.setSize(sf::Vector2f(100.f, 100.f));
		this->box.setTexture(&this->e1);
	}
	else if (type >= 31 && type <= 55)
	{
		this->box.setSize(sf::Vector2f(100.f, 100.f));
		this->box.setTexture(&this->e2);
	}
	else if (type >= 56 && type <= 75)
	{
		this->box.setSize(sf::Vector2f(100.f, 100.f));
		this->box.setTexture(&this->e3);
	}
	else if (type >= 76 && type <= 90)
	{
		this->box.setSize(sf::Vector2f(100.f, 100.f));
		this->box.setTexture(&this->e4);
	}
	else if (type >= 91 && type <= 100)
	{
		this->box.setSize(sf::Vector2f(100.f, 100.f));
		this->box.setTexture(&this->e5);
	}
	else
	{
		this->box.setSize(sf::Vector2f(100.f, 100.f));
		this->box.setTexture(&this->err);
	}

	//spawn the enemy
	this->boxes.push_back(this->box);

}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		case sf::Event::MouseButtonReleased:
			if (this->ev.mouseButton.button == sf::Mouse::Left)
			{
				if (this->backToMain.getGlobalBounds().contains(this->mousePosView))
				{
					this->window->close();
				}
			}
			break;
		}
	}

}

void Game::updateMousePositions()
{
	/**
	@return void
	Updates the mouse positions
		- Mouse position relative to window (Vector2i)
	*/

	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::closeGame()
{
	this->window->close();
	this->endGame = true;
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health << "\n"
		<< "HighScore: " << this->readHighscore << "\n";
	this->uiText.setString(ss.str());
}

void Game::saveHsFile()
{
	this->file.open("highscore.txt");
	if (this->file.is_open())
	{
		if (this->readHighscore == "")
		{
			this->file << this->points;
		}
		else
		{
			if (this->points > std::stoi(this->readHighscore))
			{
				this->file << this->points;
			}
		}

	}
	else
	{
		std::cout << "File not open" << std::endl;
	}
	this->file.close();
}
void clear()
{
	std::ofstream file("score.txt");
	file << "";
	file.close();
}
void Game::savePointsFile()
{
	this->scoreFile.open("score.txt");
	if (this->scoreFile.is_open())
	{
		clear();
		this->scoreFile << this->points;

		this->scoreFile.close();
	}
}

void Game::readOptionFile()
{
	this->optionFile.open("options.txt", std::ios::out | std::ios::in);
	if (this->optionFile.is_open())
	{
		for (int i = 1; i <= 1; i++) std::getline(this->optionFile, this->readHealth);
		for (int i = 2; i <= 2; i++) std::getline(this->optionFile, this->readEnemiesOnScreen);
		for (int i = 3; i <= 3; i++) std::getline(this->optionFile, this->readEnemiesSpeed);
		for (int i = 4; i <= 4; i++) std::getline(this->optionFile, this->readDifficulty);

		if (this->readHealth == "") this->readHealth = "5";
		if (this->readEnemiesOnScreen == "") this->readEnemiesOnScreen = "5";
		if (this->readEnemiesSpeed == "") this->readEnemiesSpeed = "3";
		if (this->readDifficulty == "") this->readDifficulty = "Easy";

		std::cout << "Read Health: " << this->readHealth << std::endl;
		std::cout << "Read EnemiesOnScreen: " << this->readEnemiesOnScreen << std::endl;
		std::cout << "Read EnemiesSpeed: " << this->readEnemiesSpeed << std::endl;
		std::cout << "Read Difficulty: " << this->readDifficulty << std::endl;
		this->optionFile.close();
	}
	else
	{
		std::cout << "File not open" << std::endl;
	}
}

void Game::loadHsFile()
{
	this->file.open("highscore.txt");
	if (this->file.is_open())
	{
		std::getline(this->file, this->readHighscore);

	}
	else
	{
		std::cout << "File not open" << std::endl;
	}
	this->file.close();
}

void Game::updateBox()
{
	/**
		@return void
		Updates the enemy spawn timer and spawns box
		when the total amount of box is smaller than max.
		Moves the box down.
		Removes the box at the edge of screen //TODO
	*/


	//update the timer for enemy spawning
	if (this->boxes.size() < this->maxSpawns)
	{
		if (this->SpawnTimer <= this->SpawnTimerMax)
		{
			//spawn the enemy and reset the timer
			this->spawnEnemy();
			this->SpawnTimer = 0.f;
		}
		else
			this->SpawnTimer += 1.f;
	}
	//Move and update box
	for (int i = 0; i < this->boxes.size(); i++)
	{
		bool deleted = false;

		this->boxes[i].move(0.f, this->speedY);

		if (this->boxes[i].getPosition().y > this->window->getSize().y)
		{
			this->boxes.erase(this->boxes.begin() + i);
			this->health -= 1;
		}
	}
	//Check if clicked
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->boxes.size() && deleted == false; i++) {
				if (this->boxes[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Gain points
					if (this->boxes[i].getTexture() == &this->e1) {
						this->points += 1;
					}
					else if (this->boxes[i].getTexture() == &this->e2) {
						this->points += 2;
					}
					else if (this->boxes[i].getTexture() == &this->e3) {
						this->points += 3;
					}
					else if (this->boxes[i].getTexture() == &this->e4) {
						this->points += 4;
					}
					else if (this->boxes[i].getTexture() == &this->e5) {
						this->points += 5;
					}

					//Delet the enemy
					deleted = true;
					this->boxes.erase(this->boxes.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::update()
{
	this->pollEvents();

	if (!this->endGame)
	{
		this->updateMousePositions();

		this->loadHsFile();

		this->updateText();

		this->updateBox();
	}

	//End game condition
	if (this->health <= 0)
	{
		this->savePointsFile();

		this->saveHsFile();

		this->savePointsToLeader();

		this->endGame = true;
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->backToMain);
	//target.draw(this->uiTextBox);
}

void Game::renderBoxes(sf::RenderTarget& target)
{
	//render box 
	for (auto& e : this->boxes)
	{
		target.draw(e);
	}
}

void Game::renderBackground(sf::RenderTarget& target)
{
	sf::Sprite bg(this->background);
	target.draw(bg);
}

void Game::render()
{
	//renders the game objects;

	this->window->clear();

	//Draw game objects
	this->renderBackground(*this->window);
	
	this->renderBoxes(*this->window);

	this->renderText(*this->window);

	this->window->display();
}
