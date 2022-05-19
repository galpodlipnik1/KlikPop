#include "Options.h"

void Options::initializeVariables()
{
	this->window = nullptr;
	this->isCustomSelected = false;

	this->presetSelected = false;
	this->healthSelected = false;
	this->enemiesOnScreenSelected = false;
	this->enemiesSpeedSelected = false;
	this->deleteDataSelected = false;
	this->confirmSaveSelected = false;
}

void Options::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new RenderWindow(this->videoMode, "KlikPop Options", Style::Titlebar || Style::Close);
	this->window->setFramerateLimit(60);
}

void Options::initFonts()
{
	if (!this->font.loadFromFile("fonts/Mukta-Bold.ttf")) std::cout << "Error loading font" << "\n";
	if (!this->fontTitle.loadFromFile("fonts/Orbitron-VariableFont_wght.ttf")) std::cout << "Error loading font" << "\n";
	if (!this->fontSelect.loadFromFile("fonts/Koulen-Regular.ttf")) std::cout << "Error loading font" << "\n";
}

void Options::initFile()
{
	std::fstream f("options.txt", std::ios::app);
	f.close();
}

void Options::handelconfirmSave()
{
	if (this->deleteConsent == "Yes")
	{
		this->deleteFiles();
	}
	else if (this->preset != "Custom")
	{
		//logic for premade preset
		if (this->preset == "Easy")
		{
			this->health = "10";
			this->enemiesOnScreenNum = "4";
			this->enemiesSpeedNum = "2";
		}
		else if (this->preset == "Medium")
		{
			this->health = "5";
			this->enemiesOnScreenNum = "6";
			this->enemiesSpeedNum = "3";
		}
		else if (this->preset == "Hard")
		{
			this->health = "3";
			this->enemiesOnScreenNum = "8";
			this->enemiesSpeedNum = "4";
		}
		
		saveFile();
	}
	else if (this->health != "" && this->enemiesOnScreenNum != "" && this->enemiesSpeedNum != "")
	{
		//logic for custom preset
		saveFile();
	}
	else
	{
		std::cout << "An error occured" << "\n";
	}
}

void Options::saveFile()
{
	//Save file logic
	this->file.open("options.txt", std::ios::in | std::ios::out);
	if (this->file.is_open())
	{
		//writing health to the first line
		this->file << this->health << "\n";
		
		//writing enemies on screen to the second line
		this->file << this->enemiesOnScreenNum << "\n";
		
		//writing enemies speed to the third line
		this->file << this->enemiesSpeedNum << "\n";

		//writing preset to the fourth line
		this->file << this->preset << "\n";

		this->file.close();
	}
	else
	{
		std::cout << "file is not open" << "\n";
	}
}

void Options::deleteFiles()
{
	//delete data(3x files)
	std::remove("options.txt");
	std::remove("score.txt");
	std::remove("highscore.txt");
	std::remove("leaderboard.txt");
}

void Options::initTextures()
{
	if (!this->background.loadFromFile("images/bg1.png")) std::cout << "Error loading the background" << "\n";
}

void Options::initText()
{
	this->FixedText();

	this->DynamicText();
}

void Options::initMusic()
{
	if (!this->music.openFromFile("music/bgMusic.ogg")) std::cout << "Error loading music" << "\n";

}

Options::Options()
{
	this->initializeVariables();
	this->initWindow();
	this->initTextures();
	this->initFonts();
	this->initText();
	this->initFile();
	//this->initMusic();
}

Options::~Options()
{
	delete this->window;
}

//Accessors

const bool Options::running() const
{
	return this->window->isOpen();
}

//Functions

void Options::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		case Event::MouseButtonReleased:
			if (this->ev.key.code == Mouse::Left)
			{
				for (int i = 1; i < 5; i++)
				{
					if (this->presets[i].getGlobalBounds().contains(mousePosView) && this->presetSelected == false)
					{
						this->presets[i].setFillColor(sf::Color::Green);
						this->presetSelected = true;
						saveToVariable(4, i);
						if(i == 4)
							this->isCustomSelected = true;
					}
						
					if (this->healthText[i].getGlobalBounds().contains(mousePosView) && this->healthSelected == false)
					{
						this->healthText[i].setFillColor(sf::Color::Green);						
						this->healthSelected = true;
						saveToVariable(1,i);
					}
					
					if (this->enemiesOnScreen[i].getGlobalBounds().contains(mousePosView) && this->enemiesOnScreenSelected == false)
					{
						this->enemiesOnScreen[i].setFillColor(sf::Color::Green);
						this->enemiesOnScreenSelected = true;
						saveToVariable(2, i);
					}
					
					if (this->enemiesSpeed[i].getGlobalBounds().contains(mousePosView) && this->enemiesSpeedSelected == false)
					{
						this->enemiesSpeed[i].setFillColor(sf::Color::Green);
						this->enemiesSpeedSelected = true;
						saveToVariable(3, i);
					}
				}
				for(int i = 1; i < 3; i++)
				{
					if (this->deleteData[i].getGlobalBounds().contains(mousePosView) && this->deleteDataSelected == false)
					{
						this->deleteData[i].setFillColor(sf::Color::Green);
						this->deleteDataSelected = true;
						this->deleteConsent = this->deleteData[i].getString();
					}
				}
				if (this->backToMain.getGlobalBounds().contains(mousePosView))
				{
					this->window->close();
				}
				if (this->confirmSave.getGlobalBounds().contains(mousePosView) && this->confirmSaveSelected == false)
				{
					this->confirmSave.setFillColor(sf::Color::Green);
					this->confirmSaveSelected = true;
					this->handelconfirmSave();
				}
				if (this->clear.getGlobalBounds().contains(mousePosView))
				{
					this->clear.setFillColor(sf::Color::Green);
					this->clearFields();
				}
				break;
			}
		}
	}
}
void Options::saveToVariable(int from,int i)
{
	//from: 1 = health, 2 = enemies on screen, 3 = enemies speed
	switch (from)
	{
		case 1:
			this->health = this->healthText[i].getString();
			break;
		case 2:
			this->enemiesOnScreenNum = this->enemiesOnScreen[i].getString();
			break;
		case 3:
			this->enemiesSpeedNum = this->enemiesSpeed[i].getString();
			break;
		case 4:
			this->preset = this->presets[i].getString();
			break;
	}
}

void Options::updateSelected()
{
	if (isCustomSelected == true)
	{
		this->render();
	}
}

void Options::updateDataRemove()
{
	if(isCustomSelected == false)
	{
		this->lineDevider.setPosition(sf::Vector2f(100.f, 190.f));
		
		this->deleteData[0].setPosition(sf::Vector2f(100.f, 230.f));
		this->deleteData[1].setPosition(sf::Vector2f(270, 230.f));
		this->deleteData[2].setPosition(sf::Vector2f(320.f, 230.f));
	}
	else
	{
		this->lineDevider.setPosition(sf::Vector2f(100.f, 400.f));

		this->deleteData[0].setPosition(sf::Vector2f(100.f, 430.f));
		this->deleteData[1].setPosition(sf::Vector2f(270, 430.f));
		this->deleteData[2].setPosition(sf::Vector2f(320.f, 430.f));
	}
}

void Options::clearFields()
{
	this->preset = "";
	this->health = "";
	this->enemiesOnScreenNum = "";
	this->enemiesSpeedNum = "";
	
	this->presetSelected = false;
	this->healthSelected = false;
	this->enemiesOnScreenSelected = false;
	this->enemiesSpeedSelected = false;
	this->deleteDataSelected = false;
	this->confirmSaveSelected = false;
	
	this->isCustomSelected = false;
	
	this->DynamicText();
	this->FixedText();
	this->render();
}


void Options::updateMousePos()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Options::closeGame()
{
	this->window->close();
}

void Options::update()
{
	this->pollEvents();
	this->updateMousePos();
	this->updateSelected();
}

void Options::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->subTitle);
	target.draw(this->subTitle1);
	target.draw(this->presets[0]);
	for(int i = 1; i < 5; i++)
		target.draw(this->presets[i]);
	
	if (this->isCustomSelected)
	{
		target.draw(this->healthText[0]);
		for (int i = 1; i < 5; i++) {
			target.draw(this->healthText[i]);
			target.draw(this->enemiesOnScreen[i]);
			target.draw(this->enemiesSpeed[i]);
		}
		target.draw(this->enemiesOnScreen[0]);
		target.draw(this->enemiesSpeed[0]);
	}
	this->updateDataRemove();
	target.draw(this->lineDevider);
	target.draw(this->deleteData[0]);
	for (int i = 1; i < 3; i++) {
		target.draw(this->deleteData[i]);
	}
	target.draw(this->confirmSave);
	target.draw(this->clear);
	target.draw(this->backToMain);
}

void Options::renderBackground(sf::RenderTarget& target)
{
	sf::Sprite bg(this->background);
	target.draw(bg);
}

void Options::render()
{
	this->window->clear();

	this->renderBackground(*this->window);

	this->renderText(*this->window);

	this->window->display();
}


void Options::FixedText()
{
	this->uiText.setFont(this->fontTitle);
	this->uiText.setCharacterSize(50);
	this->uiText.setPosition(sf::Vector2f(120.f, 10.f));
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("Welcome to Options");

	this->subTitle.setFont(this->fontSelect);
	this->subTitle.setCharacterSize(15);
	this->subTitle.setPosition(sf::Vector2f(250.f, 90.f));
	this->subTitle.setFillColor(sf::Color::White);
	this->subTitle.setString("Please select a preset or create your own");

	this->subTitle1.setFont(this->fontSelect);
	this->subTitle1.setCharacterSize(15);
	this->subTitle1.setPosition(sf::Vector2f(210.f, 110.f));
	this->subTitle1.setFillColor(sf::Color::White);
	this->subTitle1.setString("Or you can delete the Highscore,prev. score and prev. settings");

	this->presets[0].setFont(this->font);
	this->presets[0].setCharacterSize(25);
	this->presets[0].setPosition(sf::Vector2f(100.f, 150.f));
	this->presets[0].setFillColor(sf::Color::White);
	this->presets[0].setString("Presets:");

	this->healthText[0].setFont(this->font);
	this->healthText[0].setCharacterSize(25);
	this->healthText[0].setPosition(sf::Vector2f(100.f, 220.f));
	this->healthText[0].setFillColor(sf::Color::White);
	this->healthText[0].setString("Health:");

	this->enemiesOnScreen[0].setFont(this->font);
	this->enemiesOnScreen[0].setCharacterSize(25);
	this->enemiesOnScreen[0].setPosition(sf::Vector2f(100.f, 290.f));
	this->enemiesOnScreen[0].setFillColor(sf::Color::White);
	this->enemiesOnScreen[0].setString("Enemies on Screen:");

	this->enemiesSpeed[0].setFont(this->font);
	this->enemiesSpeed[0].setCharacterSize(25);
	this->enemiesSpeed[0].setPosition(sf::Vector2f(100.f, 360.f));
	this->enemiesSpeed[0].setFillColor(sf::Color::White);
	this->enemiesSpeed[0].setString("Enemies Speed:");

	this->deleteData[0].setFont(this->font);
	this->deleteData[0].setCharacterSize(25);
	this->deleteData[0].setPosition(sf::Vector2f(100.f, 430.f));
	this->deleteData[0].setFillColor(sf::Color::White);
	this->deleteData[0].setString("Delete data:");

	this->confirmSave.setFont(this->font);
	this->confirmSave.setCharacterSize(25);
	this->confirmSave.setPosition(sf::Vector2f(100.f, 500.f));
	this->confirmSave.setFillColor(sf::Color::Red);
	this->confirmSave.setString("Click to confirm");
	
	this->clear.setFont(this->font);
	this->clear.setCharacterSize(25);
	this->clear.setPosition(sf::Vector2f(500.f, 500.f));
	this->clear.setFillColor(sf::Color::Red);
	this->clear.setString("Clear selected");

	this->lineDevider.setFont(this->font);
	this->lineDevider.setCharacterSize(25);
	this->lineDevider.setPosition(sf::Vector2f(100.f, 500.f));
	this->lineDevider.setFillColor(sf::Color::White);
	this->lineDevider.setString("-----------------------------------------------------");

	this->backToMain.setFont(this->fontSelect);
	this->backToMain.setCharacterSize(20);
	this->backToMain.setPosition(sf::Vector2f(360.f, 550.f));
	this->backToMain.setFillColor(sf::Color::White);
	this->backToMain.setString("Go back");
}

void Options::DynamicText()
{
	for (int i = 1; i < 5; i++)
	{
		this->presets[i].setFont(this->fontSelect);
		this->presets[i].setCharacterSize(25);
		this->presets[i].setFillColor(Color::White);
		this->presets[i].setPosition(Vector2f(160 + (i * 50), 150.f));

		this->healthText[i].setFont(this->fontSelect);
		this->healthText[i].setCharacterSize(25);
		this->healthText[i].setFillColor(Color::White);
		this->healthText[i].setPosition(Vector2f(160 + (i * 50), 220.f));

		this->enemiesOnScreen[i].setFont(this->fontSelect);
		this->enemiesOnScreen[i].setCharacterSize(25);
		this->enemiesOnScreen[i].setFillColor(Color::White);
		this->enemiesOnScreen[i].setPosition(Vector2f(280 + (i * 50), 290.f));

		this->enemiesSpeed[i].setFont(this->fontSelect);
		this->enemiesSpeed[i].setCharacterSize(25);
		this->enemiesSpeed[i].setFillColor(Color::White);
		this->enemiesSpeed[i].setPosition(Vector2f(240 + (i * 50), 360.f));

		switch (i)
		{
		case 1:
			this->healthText[i].setString("5");
			this->presets[i].setString("Easy");
			this->enemiesOnScreen[i].setString("5");
			this->enemiesSpeed[i].setString("1");
			break;
		case 2:
			this->healthText[i].setString("10");
			this->presets[i].setString("Medium");
			this->presets[i].setPosition(Vector2f(280, 150.f));
			this->enemiesOnScreen[i].setString("10");
			this->enemiesSpeed[i].setString("2");
			break;
		case 3:
			this->healthText[i].setString("15");
			this->presets[i].setString("Hard");
			this->presets[i].setPosition(Vector2f(380, 150.f));
			this->enemiesOnScreen[i].setString("15");
			this->enemiesSpeed[i].setString("3");
			break;
		case 4:
			this->healthText[i].setString("20");
			this->presets[i].setString("Custom");
			this->presets[i].setPosition(Vector2f(450, 150.f));
			this->enemiesOnScreen[i].setString("20");
			this->enemiesSpeed[i].setString("4");
			break;
		default:
			this->healthText[i].setString("ERR");
			break;
		}
	}
	for (int i = 1; i <= 2; i++)
	{
		this->deleteData[i].setFont(this->fontSelect);
		this->deleteData[i].setCharacterSize(25);
		this->deleteData[i].setFillColor(Color::White);
		this->deleteData[i].setPosition(Vector2f(220 + (i * 50), 430.f));

		if (i == 1)
		{
			this->deleteData[i].setString("Yes");
		}
		else
		{
			this->deleteData[i].setString("No");
			this->deleteData[i].setPosition(Vector2f(350, 430.f));
		}
	}
}


