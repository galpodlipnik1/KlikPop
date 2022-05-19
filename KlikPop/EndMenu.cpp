#include "EndMenu.h"

void EndMenu::initializeVariables()
{
	this->window = nullptr;
}

void EndMenu::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new RenderWindow(this->videoMode, "KlikPop EndMenu", Style::Titlebar || Style::Close);
	this->window->setFramerateLimit(60);
}

void EndMenu::readFile()
{
	std::string tmp[100];
	std::string tmpOftmp;
	this->file.open("leaderboard.txt", std::ios::in | std::ios::out);
	
	for (int i = 0; i < this->numOfLines; i++)
	{
		getline(file,tmpOftmp);
		if (tmpOftmp != "0") {
			this->leaderboardArr[i] = stoi(tmpOftmp);
			
			time_t now = time(0);

			// convert now to string form
			char str[26];
			ctime_s(str, sizeof str, &now);
			this->dateArr[i] = str;
			
		}
	}
	this->file.close();
	
}

void EndMenu::outputArr()
{
	for (int i = 0; i < this->numOfLines; i++)
	{
		std::cout << this->leaderboardArr[i] << "\t";
	}
	std::cout << std::endl;
}

int EndMenu::swapElement(int arr[], int p, int r)
{
	int x = arr[p]; // pivot
	int i = p;
	int j = r;
	while (true) {

		while (arr[i] > x) {
			i++;
		}

		while (arr[j] < x) {
			j--;
		}
		if (i < j) {
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else {
			return j;
		}
	}
}
void EndMenu::SortArr(int arr[], int p, int r)
{
	if (p < r) {
		int q = swapElement(arr, p, r);
		SortArr(arr, p, q);
		SortArr(arr, q + 1, r);
	}
}


void EndMenu::sortLeaderboard()
{
	int n = this->numOfLines;
	SortArr(this->leaderboardArr, 0, n - 1);
	//this->outputArr();
}

void EndMenu::checkNumOfLines()
{
	this->file.open("leaderboard.txt", std::ios::in | std::ios::out);
	std::string tmp;
	
	//count number of lines in file
	while (getline(this->file, tmp))
	{
		this->numOfLines++;
	}
	this->file.close();
}

void EndMenu::initFonts()
{
	if (!this->font.loadFromFile("fonts/Mukta-Bold.ttf")) std::cout << "Error loading font" << "\n";
}

void EndMenu::initTextures()
{
	if (!this->background.loadFromFile("images/EndMenuBG.png")) std::cout << "Error loading the background" << "\n";
}

void EndMenu::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(80);
	this->uiText.setPosition(sf::Vector2f(170.f, 20.f));
	this->uiText.setFillColor(sf::Color::Red);
	this->uiText.setString("Game Over");

	this->initLText();
}

void EndMenu::initMusic()
{
	if (!this->music.openFromFile("music/bgMusic.ogg")) std::cout << "Error loading font" << "\n";
	this->music.setPlayingOffset(sf::seconds(57.5f));
	this->music.setVolume(15.f);
	this->music.setLoop(true);
	this->music.play();
}



EndMenu::EndMenu()
{
	this->checkNumOfLines();
	this->readFile();
	this->initializeVariables();
	this->initWindow();
	this->initTextures();
	this->sortLeaderboard();
	this->initFonts();
	this->initText();
	//this->initMusic();
}

EndMenu::~EndMenu()
{
	delete this->window;
}

//Accessors

const bool EndMenu::running() const
{
	return this->window->isOpen();
}

//Functions

void EndMenu::pollEvents()
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
			{
				this->window->close();
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (this->ev.mouseButton.button == sf::Mouse::Left)
			{
				if (this->playAgain.getGlobalBounds().contains(this->ev.mouseButton.x, this->ev.mouseButton.y))
				{
					this->window->close();
				}
			}
			break;
		}
	}
}

void EndMenu::closeGame()
{
	this->window->close();
}

void EndMenu::updateText()
{
	//update text here
	
}

void EndMenu::update()
{
	this->pollEvents();

	this->updateText();
}

void EndMenu::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->playAgain);
	target.draw(this->leaderboardText[0]);

	for (int i = 1; i <= 5; i++) {
		target.draw(this->leaderboardText[i]);
	}
}

void EndMenu::renderBackground(sf::RenderTarget& target)
{
	sf::Sprite bg(this->background);
	target.draw(bg);
}

void EndMenu::render()
{
	this->window->clear();

	this->renderBackground(*this->window);

	this->renderText(*this->window);

	this->window->display();
}



void EndMenu::initLText()
{
	this->playAgain.setFont(this->font);
	this->playAgain.setCharacterSize(20);
	this->playAgain.setPosition(sf::Vector2f(350.f, 550.f));
	this->playAgain.setFillColor(sf::Color::White);
	this->playAgain.setString("Go back");
	
	this->leaderboardText[0].setFont(this->font);
	this->leaderboardText[0].setCharacterSize(35);
	this->leaderboardText[0].setPosition(sf::Vector2f(250.f, 150.f));
	this->leaderboardText[0].setFillColor(sf::Color::White);
	this->leaderboardText[0].setString("LEADERBOARD:");
	
	for (int i = 1; i <= 5; i++)
	{
		this->leaderboardText[i].setFont(this->font);
		this->leaderboardText[i].setCharacterSize(30);
		this->leaderboardText[i].setPosition(sf::Vector2f(150.f, 150.f + (i * 50)));
		this->leaderboardText[i].setFillColor(sf::Color::Green);
	}
	std::stringstream ss;
	ss << "1. " << this->leaderboardArr[0];
	std::stringstream ss1;
	ss1 << "2. " << this->leaderboardArr[1];
	std::stringstream ss2;
	ss2 << "3. " << this->leaderboardArr[2];
	std::stringstream ss3;
	ss3 << "4. " << this->leaderboardArr[3];
	std::stringstream ss4;
	ss4 << "5. " << this->leaderboardArr[4];
	
	this->leaderboardText[1].setString(ss.str());
	this->leaderboardText[2].setString(ss1.str());
	this->leaderboardText[3].setString(ss2.str());
	this->leaderboardText[4].setString(ss3.str());
	this->leaderboardText[5].setString(ss4.str());
}