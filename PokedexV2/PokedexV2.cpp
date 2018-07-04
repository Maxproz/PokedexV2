﻿
// PokedexV2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <SFML/Graphics.hpp>

//
//class Pokemon
//{
//private:
//
//public:
//
//
//};


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <Windows.h>



enum class PokemonType
{
	BUG = 0,
	ELECTRIC = 1,
	FIRE = 2,
	GRASS = 3,
	NORMAL = 4,
	ROCK = 5,
	DARK = 6,
	FAIRY = 7,
	FLYING = 8,
	GROUND = 9,
	POISON = 10,
	STEEL = 11,
	DRAGON = 12,
	FIGHT = 13,
	GHOST = 14,
	ICE = 15,
	PSYCHIC = 16,
	WATER = 17,

	NONE = 18
};

std::string GetPokemonTypeName(const PokemonType& InType)
{
	switch (InType)
	{
		case PokemonType::BUG: { return std::string{ "Bug" }; }
		case PokemonType::ELECTRIC: { return std::string {"ELECTRIC"}; }
		case PokemonType::FIRE: { return std::string{ "FIRE" }; }
		case PokemonType::GRASS: { return std::string{ "GRASS" }; }
		case PokemonType::NORMAL: { return std::string{ "NORMAL" }; }
		case PokemonType::ROCK: { return std::string{ "ROCK" }; }
		case PokemonType::DARK: { return std::string{ "DARK" }; }
		case PokemonType::FAIRY: { return std::string{ "FAIRY" }; }
		case PokemonType::FLYING: { return std::string{ "FLYING" }; }
		case PokemonType::GROUND: { return std::string{ "GROUND" }; }
		case PokemonType::POISON: { return std::string{ "POISON" }; }
		case PokemonType::STEEL: { return std::string{ "STEEL" }; }
		case PokemonType::DRAGON: { return std::string{ "DRAGON" }; }
		case PokemonType::FIGHT: { return std::string{ "FIGHT" }; }
		case PokemonType::GHOST: { return std::string{ "GHOST" }; }
		case PokemonType::ICE: { return std::string{ "ICE" }; }
		case PokemonType::PSYCHIC: { return std::string{ "PSYCHIC" }; }
		case PokemonType::WATER: { return std::string{ "WATER" }; }
		
		case PokemonType::NONE: { return std::string{ "NONE" }; }
	}
	return std::string{ "" };
}

PokemonType GetPokemonTypeFromString(const std::string& InString)
{
	if (InString == "BUG") return PokemonType::BUG;
	else if (InString == "ELECTRIC") return PokemonType::ELECTRIC;
	else if (InString == "FIRE") return PokemonType::FIRE;
	else if (InString == "GRASS") return PokemonType::GRASS;
	else if (InString == "NORMAL") return PokemonType::NORMAL;
	else if (InString == "ROCK") return PokemonType::ROCK;
	else if (InString == "DARK") return PokemonType::DARK;
	else if (InString == "FAIRY") return PokemonType::FAIRY;
	else if (InString == "FLYING") return PokemonType::FLYING;
	else if (InString == "GROUND") return PokemonType::GROUND;
	else if (InString == "POISON") return PokemonType::POISON;
	else if (InString == "STEEL") return PokemonType::STEEL;
	else if (InString == "DRAGON") return PokemonType::DRAGON;
	else if (InString == "FIGHT") return PokemonType::FIGHT;
	else if (InString == "GHOST") return PokemonType::GHOST;
	else if (InString == "ICE") return PokemonType::ICE;
	else if (InString == "PSYCHIC") return PokemonType::PSYCHIC;
	else if (InString == "WATER") return PokemonType::WATER;
	else if (InString == "NONE") return PokemonType::NONE;
	else
	{
		return PokemonType::NONE;
	}
}


// TODO: Organize this code for reading our CSV pokemon data somehow.

typedef std::string String;
typedef std::vector<String> CSVRow;
typedef CSVRow::const_iterator CSVRowCI;

typedef std::vector<CSVRow> CSVDatabase;
typedef CSVDatabase::const_iterator CSVDatabaseCI;

void readCSV(std::istream& input, CSVDatabase& db);
void display(const CSVRow&);
void display(const CSVDatabase&);

CSVDatabase FirstGenerationDB;


struct PokedexEntry
{
public:
	std::string m_Name{ "" };
	unsigned int m_ID{ 0 };
	unsigned int m_Stamina{ 0 };
	unsigned int m_Attack{ 0 };
	unsigned int m_Defense{ 0 };

	PokemonType m_FirstType{ PokemonType::NONE };
	PokemonType m_SecondType{ PokemonType::NONE };

	double m_Weight{ 0 }; // inputed in Kilograms
	double m_Height{ 0 }; // inputed in Meters

	std::string m_Description{ "" };

	PokedexEntry() = default;

	PokedexEntry(std::string Name, unsigned int ID, unsigned int Stam, unsigned int Atk, unsigned int Def,
					PokemonType TyOne, PokemonType TyTwo, double Weight, double Height, std::string Desc) :
		m_Name{ Name }, m_ID{ ID }, m_Stamina{ Stam }, m_Attack{ Atk }, m_Defense{ Def },
		m_FirstType{ TyOne }, m_SecondType{ TyTwo }, m_Weight{ Weight }, m_Height{ Height }, m_Description{ Desc }
	{

	}

};

std::vector<PokedexEntry> m_PokedexData;

void InitializePokedex(const CSVDatabase& PKMNDataBase)
{
	//m_PokedexData.reserve(152);

	PokedexEntry PlaceHolder;
	m_PokedexData.push_back(PlaceHolder);

	for (unsigned int Rows = 1; Rows < 152; ++Rows)
	{
		PokedexEntry CurrentEntry;
		CurrentEntry.m_Name = PKMNDataBase[Rows][0];
		CurrentEntry.m_ID = std::stoi(PKMNDataBase[Rows][1]);
		CurrentEntry.m_Stamina = std::stoi(PKMNDataBase[Rows][2]);
		CurrentEntry.m_Attack = std::stoi(PKMNDataBase[Rows][3]);
		CurrentEntry.m_Defense = std::stoi(PKMNDataBase[Rows][4]);

		CurrentEntry.m_FirstType = GetPokemonTypeFromString(PKMNDataBase[Rows][5]);
		CurrentEntry.m_SecondType = GetPokemonTypeFromString(PKMNDataBase[Rows][6]);

		CurrentEntry.m_Weight = std::stod(PKMNDataBase[Rows][7]);
		CurrentEntry.m_Height = std::stod(PKMNDataBase[Rows][8]);
		CurrentEntry.m_Description = PKMNDataBase[Rows][9];

		m_PokedexData.push_back(CurrentEntry);
	}
}



// data test function to see if we transfered the csv data correctly to the desired formats
void DisplayPokedexEntry(const unsigned int PokemonID)
{
	std::cout << "Name: " << m_PokedexData[PokemonID].m_Name << std::endl;
	std::cout << "ID: " << m_PokedexData[PokemonID].m_ID << std::endl;
	std::cout << "HP: " << m_PokedexData[PokemonID].m_Stamina << std::endl;
	std::cout << "Attack: " << m_PokedexData[PokemonID].m_Attack << std::endl;
	std::cout << "Defense: " << m_PokedexData[PokemonID].m_Defense << std::endl;
	std::cout << "Type: " << GetPokemonTypeName(m_PokedexData[PokemonID].m_FirstType);
	if (m_PokedexData[PokemonID].m_SecondType != PokemonType::NONE)
	{
		std::cout << " " << GetPokemonTypeName(m_PokedexData[PokemonID].m_SecondType) << std::endl;
	} 
	else
	{
		std::cout << std::endl;
	}

	// TODO: In the UI Format also add the height and weight nearby in pounds and feet/inches
	std::cout << "Weight (kg): " << m_PokedexData[PokemonID].m_Weight << std::endl;
	std::cout << "Height (m): " << m_PokedexData[PokemonID].m_Height << std::endl;

	std::cout << "Description: " << m_PokedexData[PokemonID].m_Description << std::endl << std::endl;
}


void readCSV(std::istream& input, CSVDatabase& db)
{
	String csvLine;
	// read every line from the stream
	while (std::getline(input, csvLine))
	{
		std::istringstream csvStream(csvLine);
		CSVRow csvRow;
		String csvCol;
		// read every element from the line that is seperated by commas
		// and put it into the vector of strings
		while (std::getline(csvStream, csvCol, ','))
		{
			csvRow.push_back(csvCol);
		}

		//display(csvRow);
		//std::cout << std::endl << std::endl;
		db.push_back(csvRow);
	}
}

void display(const CSVRow& row)
{
	if (!row.size())
		return;

	CSVRowCI i = row.begin();
	std::cout << *(i++);

	for (; i != row.end(); ++i)
	{
		std::cout << ',' << *i;
	}
}

void display(const CSVDatabase& db) 
{
	if (!db.size())
		return;

	CSVDatabaseCI i = db.begin();
	for (; i != db.end(); ++i)
	{
		display(*i);
		std::cout << std::endl;
	}
}

enum class GAMESTATE
{
	MAINMENU,
	POKEDEXMENU
};

std::string GetGameStateAsString(const GAMESTATE& InGameState)
{
	switch (InGameState)
	{
		case GAMESTATE::MAINMENU: 
		{
			return std::string{ "MAINMENU" };
		}
		case GAMESTATE::POKEDEXMENU:
		{
			return std::string{ "POKEDEXMENU" };
		}
	}

	return "INVAID CURRENT MENU ~ INVESTIGATE!";
}


#define MAX_NUMBER_OF_MAINMENU_ITEMS 3
#define MAX_NUMBER_OF_POKEDEX_ITEMS 10


//class Menu
//{
//protected:
//	Menu() = default;
//	Menu(float width, float height);
//	int& ModifySelectedItemIndex() { return selectedItemIndex; }
//
//public:
//	virtual ~Menu() {}
//	virtual void drawTo(sf::RenderWindow& window) = 0;
//	virtual void MoveNext() = 0;
//	virtual void MovePrevious() = 0;
//
//	int GetPressedItem() { return selectedItemIndex; }
//	//sf::Font GetFont() const { return font; }
//
//
//
//	// These two will only be overidden in Pokedex Menu class
//	virtual void GoNextPokemon()  {};
//	virtual void GoPreviousPokemon() {};
//
//
//	virtual void UpdateMenu() {};
//
//	
//private:
//	int selectedItemIndex{ 0 };
//	
//};
//
//
//
//Menu::Menu(float width, float height)
//{
//	sf::Font font;
//	if (!font.loadFromFile("arial.ttf"))
//	{
//		// TODO: handle error
//	}
//
//	selectedItemIndex = 0;
//}



class MainMenu //: public Menu
{
public:
	MainMenu(float width, float height, sf::Font font);
	~MainMenu() {}

	/*virtual */void drawTo(sf::RenderWindow& window);// override;
	/*virtual */void MoveNext();// override;
	/*virtual */void MovePrevious();// override;


	int GetPressedItem() { return selectedItemIndex; }

protected:
	int& ModifySelectedItemIndex() { return selectedItemIndex; }

private:
	sf::Text menu[MAX_NUMBER_OF_MAINMENU_ITEMS];
	sf::Font m_Font;
	int selectedItemIndex{ 0 };
};

MainMenu::MainMenu(float width, float height, sf::Font font) //: Menu(width, height)
{
	m_Font = font;

	menu[0].setFont(m_Font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_MAINMENU_ITEMS + 1) * 1));

	menu[1].setFont(m_Font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_MAINMENU_ITEMS + 1) * 2));

	menu[2].setFont(m_Font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_MAINMENU_ITEMS + 1) * 3));

}


void MainMenu::drawTo(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_MAINMENU_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void MainMenu::MovePrevious()
{
	if (GetPressedItem() - 1 >= 0)
	{
		menu[GetPressedItem()].setFillColor(sf::Color::White);
		ModifySelectedItemIndex()--;
		menu[GetPressedItem()].setFillColor(sf::Color::Red);
	}
}

void MainMenu::MoveNext()
{
	if (GetPressedItem() + 1 < MAX_NUMBER_OF_MAINMENU_ITEMS)
	{
		menu[GetPressedItem()].setFillColor(sf::Color::White);
		ModifySelectedItemIndex()++;
		menu[GetPressedItem()].setFillColor(sf::Color::Red);
	}
	else
	{
		menu[GetPressedItem()].setFillColor(sf::Color::White);
		ModifySelectedItemIndex() = 0;
		menu[GetPressedItem()].setFillColor(sf::Color::Red);
	}
}

// A PokedexMenu hmmm, how should I oragnize this?
class PokedexMenu // : public Menu
{
public:
	PokedexMenu(float width, float height, sf::Font font);
	~PokedexMenu() {}

	/*virtual*/ void drawTo(sf::RenderWindow& window);// override;
	/*virtual*/ void MoveNext();// override;
	/*virtual*/ void MovePrevious();// override;


	// TODO: Make this more generic later
	PokedexEntry* CurrentEntry{ nullptr };

	// TODO: Encapsulate this variable later
	int CurrentPokemonID{ 1 };

	int GetPressedItem() { return selectedItemIndex; }


	void GoNextPokemon() // override
	{
		CurrentPokemonID++;
		UpdateMenu();
	}

	void GoPreviousPokemon() // override
	{
		CurrentPokemonID--;
		UpdateMenu();
	}

	void UpdateMenu() // override
	{
		CurrentEntry = &(m_PokedexData[CurrentPokemonID]);

		//sf::Text PokemonNameSFText(CurrentEntry->m_Name, m_Font);
		//menu[0] = PokemonNameSFText;

		//sf::Text PokemonDescriptionSFText(CurrentEntry->m_Description, m_Font);
		//menu[1] = PokemonDescriptionSFText;
		////menu[1].setFillColor(sf::Color::White);


		sf::Text PokemonNameSFText(CurrentEntry->m_Name, m_Font);
		menu[0] = PokemonNameSFText;
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setPosition(sf::Vector2f(0, m_Height / (3 + 1) * 1));

		sf::Text PokemonDescriptionSFText(CurrentEntry->m_Description, m_Font);
		menu[1] = PokemonDescriptionSFText;
		menu[1].setFillColor(sf::Color::White);
		menu[1].setCharacterSize(12);
		menu[1].setPosition(sf::Vector2f(0, m_Height / (3 + 1) * 2));

		menu[2].setFont(m_Font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Press A and D to move to different pokemon");
		menu[2].setPosition(sf::Vector2f(0, m_Height / (3 + 1) * 3));

	}

	//sf::Font GetFont() const { return m_font; }

protected:
	int& ModifySelectedItemIndex() { return selectedItemIndex; }

private:

	int selectedItemIndex{ 0 };

	//sf::Text menu[MAX_NUMBER_OF_POKEDEX_ITEMS];
	int m_Width{ 0 };
	int m_Height{ 0 };

	sf::Text menu[3];
	sf::Font m_Font;
	
};

PokedexMenu::PokedexMenu(float width, float height, sf::Font font) // : Menu(width, height)
{
	m_Font = font;

	CurrentPokemonID = 1;

	CurrentEntry = &(m_PokedexData[CurrentPokemonID]);


	m_Width = width;
	m_Height = height;


	sf::Text PokemonNameSFText(CurrentEntry->m_Name, m_Font);
	menu[0] = PokemonNameSFText;
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setPosition(sf::Vector2f(0, height / (3 + 1) * 1));

	sf::Text PokemonDescriptionSFText(CurrentEntry->m_Description, m_Font);
	menu[1] = PokemonDescriptionSFText;
	menu[1].setFillColor(sf::Color::White);
	menu[1].setCharacterSize(12);
	menu[1].setPosition(sf::Vector2f(0, height / (3 + 1) * 2));

	menu[2].setFont(m_Font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Press A and D to move to different pokemon");
	menu[2].setPosition(sf::Vector2f(0, height / (3 + 1) * 3));

}


void PokedexMenu::drawTo(sf::RenderWindow& window)
{
	//for (int i = 0; i < MAX_NUMBER_OF_POKEDEX_ITEMS; i++)
	//{
	//	window.draw(menu[i]);
	//}

	for (int i = 0; i < 3; i++)
	{
		window.draw(menu[i]);
	}
}

void PokedexMenu::MovePrevious()
{
	if (GetPressedItem() - 1 >= 0)
	{
		menu[GetPressedItem()].setFillColor(sf::Color::White);
		ModifySelectedItemIndex()--;
		menu[GetPressedItem()].setFillColor(sf::Color::Red);
	}
}

void PokedexMenu::MoveNext()
{
	if (GetPressedItem() + 1 < MAX_NUMBER_OF_POKEDEX_ITEMS)
	{
		menu[GetPressedItem()].setFillColor(sf::Color::White);
		ModifySelectedItemIndex()++;
		menu[GetPressedItem()].setFillColor(sf::Color::Red);
	}
	else
	{
		menu[GetPressedItem()].setFillColor(sf::Color::White);
		ModifySelectedItemIndex() = 0;
		menu[GetPressedItem()].setFillColor(sf::Color::Red);
	}
}



int main(int argc, char* argv[])
{
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);


	sf::RenderWindow window;

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(900, 900), "SFML Pokedex", sf::Style::Titlebar | sf::Style::Close);

	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);




	// Try to convert the CSV data into sortable data
	std::fstream File("file.csv", std::ios::in);
	if (!File.is_open())
	{
		std::cout << "File not found!\n";
		return 1;
	}

	readCSV(File, FirstGenerationDB);


	InitializePokedex(FirstGenerationDB);


	GAMESTATE CurrentGameState = GAMESTATE::MAINMENU;


	sf::Font DebugFont;
	if (!DebugFont.loadFromFile("arial.ttf"))
	{
		// handle error
		std::cout << "Error loading font " << std::endl;
	}

	sf::Text GameStateDebugText;

	GameStateDebugText.setFont(DebugFont);
	GameStateDebugText.setCharacterSize(15);
	GameStateDebugText.setFillColor(sf::Color::Green);
	GameStateDebugText.setString("Current GameState: " + GetGameStateAsString(CurrentGameState));
	GameStateDebugText.setPosition(sf::Vector2f(0, 0));




	// get the size of the window
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x;
	unsigned int height = size.y;

	MainMenu* CurrentMainMenu = new MainMenu(width, height, DebugFont);// = new MainMenu(width, height);
	PokedexMenu* CurrentPokedexMenu = new PokedexMenu(width, height, DebugFont);// { nullptr };

	

	// WORKED!
	//DisplayPokedexEntry(65); // This test should display an accurate data entry for Alakazam




	//// change the position of the window (relatively to the desktop)
	//window.setPosition(sf::Vector2i(10, 50));

	//// change the size of the window
	//window.setSize(sf::Vector2u(640, 480));

	// change the title of the window
	//window.setTitle("SFML window");

	//bool PlayButtonPressed = false;


	while (window.isOpen())
	{
		sf::Event Event;


		//if (CurrentGameState == GAMESTATE::POKEDEXMENU)
		//{
		//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		//	{

		//		// if (OnPokedexEntryWindow())
		//		//		GoToNextEntry();
		//	}
		//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		//	{

		//		// if (OnPokedexEntryWindow())
		//		//		GoToPreviousEntry();
		//	}
		//}
		//else
		//{

		//}


		//Event Loop:
		while (window.pollEvent(Event))
		{

			switch (Event.type)
			{
				case sf::Event::KeyReleased:
				{
					switch (Event.key.code)
					{
						case sf::Keyboard::Right:
						{
							if (CurrentGameState == GAMESTATE::MAINMENU)
							{
								CurrentMainMenu->MoveNext();
								break;
							}
							//else if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							//{

							//}

						}
						case sf::Keyboard::Left:
						{
							if (CurrentGameState == GAMESTATE::MAINMENU)
							{
								CurrentMainMenu->MovePrevious();
								break;
							}
							//else if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							//{

							//}
						}
						case sf::Keyboard::Return:
						{
							if (CurrentGameState == GAMESTATE::MAINMENU)
							{
								switch (CurrentMainMenu->GetPressedItem())
								{
									case 0:
									{
										std::cout << "Play button has been pressed" << std::endl;
										//PlayButtonPressed = true;
										//CurrentPokedexMenu = new PokedexMenu(width, height, DebugFont);
										CurrentGameState = GAMESTATE::POKEDEXMENU;
										GameStateDebugText.setString("Current GameState: " + GetGameStateAsString(CurrentGameState));
										//delete CurrentMainMenu;
										//CurrentMainMenu = nullptr;
										break;
									}
									case 1:
									{
										std::cout << "Option button has been pressed" << std::endl;
										break;
									}
									case 2:
									{
										window.close();
										break;
									}

								}

								break; // break out of this inner switch 
							}
							//else if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							//{

							//}
						}
						case sf::Keyboard::D:
						{
							if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							{
								CurrentPokedexMenu->GoNextPokemon();
								break;
							}
						}
						case sf::Keyboard::A:
						{
							if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							{
								CurrentPokedexMenu->GoPreviousPokemon();
								break;
							}
						}
					}
					break; // break out of the key released switch 
				}
				case sf::Event::Closed:
				{
					window.close();
					break;
				}
			}
		}
		

		//if (PlayButtonPressed)
		//	CurrentGameState = GAMESTATE::POKEDEXMENU;

		window.clear();

		// SFML example game code
		//coin1.drawTo(window);
		//window.draw(lblScore);
		//coin2.drawTo(window);
		//player.drawTo(window);

		// SFML tutorial code
		//window.draw(shape);

		// NOTE: How do we get rid of the menu when we select PLAY for example and hit ENTER?﻿
		/*
		Use an if function before you draw.
		e.g
		clear window
		if (play == true)
		draw(players and stuff)
		else
		draw(menu stuff)
		display window﻿
		*/

		if (CurrentGameState == GAMESTATE::MAINMENU)
		{
			if (CurrentMainMenu)
			{
				CurrentMainMenu->drawTo(window);
			}
		}
		else if (CurrentGameState == GAMESTATE::POKEDEXMENU)
		{
			if (CurrentPokedexMenu)
			{
				CurrentPokedexMenu->drawTo(window);
			}
		}
		else
		{

		}

		
		// Its fine if I draw debug texts seperate from the window for now.
		//window.draw(GameStateDebugText);

		window.display();
	}

	return 0;
}
