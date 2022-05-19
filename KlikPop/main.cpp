#include <iostream>

#include "Game.h"
#include "MainMenu.h"
#include "About.h"
#include "Options.h"
#include "EndMenu.h"
using namespace sf;

void gotoEndMenu();
void makeGame(MainMenu mainMenu);
void makeOptions();
void makeAbout();

int main()
{
	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));
	
	RenderWindow MENU(VideoMode(800, 600), "Klik Pop main menu", Style::Titlebar | Style::Close);
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);


	
	Vector2f mousePos;
	while (MENU.isOpen())
	{
		mousePos = mainMenu.getMousePos(MENU);
		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				MENU.close();
			}
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
					if (mainMenu.mainMenu[0].getGlobalBounds().contains(mousePos))
					{
						makeGame(mainMenu);
					}
					else if (mainMenu.mainMenu[1].getGlobalBounds().contains(mousePos))
					{
						makeOptions();
					}
					else if (mainMenu.mainMenu[2].getGlobalBounds().contains(mousePos))
					{
						makeAbout();
					}
					else if (mainMenu.mainMenu[3].getGlobalBounds().contains(mousePos))
					{
						MENU.close();
						break;
					}
					
			}
			if (event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				if (mainMenu.rights.getGlobalBounds().contains(mousePos))
				{
					string op = string("start ").append("https://github.com/galpodlipnik1/KlikPop");
					system(op.c_str());
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if (mainMenu.mainMenu[i].getGlobalBounds().contains(mousePos))
				{
					mainMenu.mainMenu[i].setFillColor(sf::Color (160, 160, 160));
				}
				if (!mainMenu.mainMenu[i].getGlobalBounds().contains(mousePos))
				{
					mainMenu.mainMenu[i].setFillColor(sf::Color::White);
				}
			}

		}
		MENU.clear();
		mainMenu.draw(MENU);
		MENU.display();
	}
	return 0;
}


void gotoEndMenu()
{
	EndMenu endMenu;
	while (endMenu.running())
	{
		//update
		endMenu.update();

		//render
		endMenu.render();
	}
};

void makeGame(MainMenu mainMenu)
{
	Game game;
	while (game.running() && !game.getEndGame())
	{

		//update
		game.update();

		//render
		game.render();

		if (game.getEndGame() == true)
		{
			game.closeGame();
			gotoEndMenu();
		}
	}
}

void makeAbout()
{
	About ABOUT;
	while (ABOUT.running())
	{

		//update
		ABOUT.update();

		//render
		ABOUT.render();

	}
}

void makeOptions()
{
	Options OPTIONS;
	while (OPTIONS.running())
	{

		//update
		OPTIONS.update();

		//render
		OPTIONS.render();

	}
}