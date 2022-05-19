#include "About.h"

void About::initializeVariables()
{
	this->window = nullptr;
}

void About::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new RenderWindow(this->videoMode, "KlikPop About", Style::Titlebar || Style::Close);
	this->window->setFramerateLimit(60);
}

void About::initFonts()
{
	if(!this->font.loadFromFile("fonts/Mukta-Bold.ttf")) std::cout << "Error loading font" << "\n";
	if (!this->font1.loadFromFile("fonts/Orbitron-VariableFont_wght.ttf")) std::cout << "Error loading font" << "\n";
}

void About::initTextures()
{
	if (!this->background.loadFromFile("images/bg1.png")) std::cout << "Error loading the background" << "\n";
}

void About::initText()
{
	this->uiText.setFont(this->font1);
	this->uiText.setCharacterSize(50);
	this->uiText.setPosition(sf::Vector2f(150.f, 10.f));
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");

	this->text.setFont(this->font);
	this->text.setCharacterSize(25);
	this->text.setPosition(sf::Vector2f(200.f, 250.f));
	this->text.setFillColor(sf::Color::White);
	this->text.setString("NONE");

	this->backToMain.setFont(this->font);
	this->backToMain.setCharacterSize(20);
	this->backToMain.setPosition(sf::Vector2f(350.f, 550.f));
	this->backToMain.setFillColor(sf::Color::White);
	this->backToMain.setString("Go back");
}

void About::initMusic()
{
	if(!this->music.openFromFile("music/bgMusic.ogg")) std::cout << "Error loading font" << "\n";
	this->music.setPlayingOffset(sf::seconds(57.5f));
	this->music.setVolume(15.f);
	this->music.setLoop(true);
	this->music.play();
}



About::About()
{
	this->initializeVariables();
	this->initWindow();
	this->initTextures();
	this->initFonts();
	this->initText();
	//this->initMusic();
}

About::~About()
{
	delete this->window;
}

//Accessors

const bool About::running() const
{
	return this->window->isOpen();
}

//Functions

void About::pollEvents()
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
				if (this->backToMain.getGlobalBounds().contains(this->ev.mouseButton.x, this->ev.mouseButton.y))
				{
					this->window->close();
				}
			}
			break;
		}
	}
}

void About::closeGame()
{
	this->window->close();
}

void About::updateText()
{
	std::stringstream ss;
	std::stringstream ss1;
	ss << "About the project" << "\n";
	this->uiText.setString(ss.str());
	
	ss1 << "Project KlikPop is a school project" << "\n"
		<< "It doesn't have a special meaning it just exists :)" << "\n"
		<< "Good Aim practice tho" << "\n";
	this->text.setString(ss1.str());
}

void About::update()
{
	this->pollEvents();

	this->updateText();
}

void About::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->text);
	target.draw(this->backToMain);
}

void About::renderBackground(sf::RenderTarget& target)
{
	sf::Sprite bg(this->background);
	target.draw(bg);
}

void About::render()
{
	this->window->clear();

	this->renderBackground(*this->window);

	this->renderText(*this->window);

	this->window->display();
}