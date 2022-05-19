#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
    if (!font.loadFromFile("fonts/Mukta-Bold.ttf")) cout << "Error loading font" << endl;
    if (!titleFont.loadFromFile("fonts/Orbitron-VariableFont_wght.ttf")) cout << "Error loading font" << endl;
    if (!MainMenuBG.loadFromFile("images/MinMenueBG.png")) cout << "Error loading the background" << endl;
	
	//Title
    title.setFont(titleFont);
    title.setFillColor(Color::Red);
	title.setString("KlikPop");
    title.setCharacterSize(100);
    title.setPosition(220, 35);

	//subtitle
    subtitle.setFont(titleFont);
    subtitle.setFillColor(Color::White);
    subtitle.setString("VERSION... 1.0");
    subtitle.setCharacterSize(13);
    subtitle.setPosition(330, 150);

    //Play
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("PLAY");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(325, 175);
    //options
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("OPTIONS");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(275, 245);
    //About
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("ABOUT");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(300, 315);
    //Exit
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("EXIT");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(335, 450);

	//rights
    rights.setFont(font);
    rights.setFillColor(Color::White);
    rights.setString("©Gal Podlipnik 2022");
    rights.setCharacterSize(10);
    rights.setPosition(20, 580);

}

//Destructor
MainMenu::~MainMenu()
{
	
}

//Draw the main menu
void MainMenu::draw(RenderWindow& window)
{
    Sprite background(MainMenuBG);
    window.draw(background);
    window.draw(title);
	window.draw(subtitle);
    window.draw(rights);
    for(int i = 0; i < Max_main_menu; i++)
    {
        window.draw(mainMenu[i]);
    }
	
}

Vector2f MainMenu::getMousePos(RenderWindow& window)
{
    this->mousePosWindow = Mouse::getPosition(window);
    this->mousePosView = window.mapPixelToCoords(mousePosWindow);
	return this->mousePosView;
}
