
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
		case PokemonType::BUG: { return std::string{ "BUG" }; }
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

	// These two go hand in hand to display an image on the screen
	// NOTE: owning pointers (probably change to unique or shared ptrs later
	sf::Texture* m_PictureTexture{ nullptr };
	//sf::Sprite* m_PictureSprite{ nullptr };

	PokedexEntry() = default;

	PokedexEntry(std::string Name, unsigned int ID, unsigned int Stam, unsigned int Atk, unsigned int Def,
					PokemonType TyOne, PokemonType TyTwo, double Weight, double Height, std::string Desc, std::string PictureFileName) :
		m_Name{ Name }, m_ID{ ID }, m_Stamina{ Stam }, m_Attack{ Atk }, m_Defense{ Def },
		m_FirstType{ TyOne }, m_SecondType{ TyTwo }, m_Weight{ Weight }, m_Height{ Height }, m_Description{ Desc }
	{

		// TODO: Probably shouldnt have this load inside a constructor?
		// Load a sprite to display
		m_PictureTexture = new sf::Texture();

		if (!m_PictureTexture->loadFromFile(PictureFileName))
			throw std::exception("Error loading picture for pokemon");

		//m_PictureSprite = new sf::Sprite(*m_PictureTexture);
		//m_PictureSprite->setTexture(*m_PictureTexture);
	}

	~PokedexEntry()
	{
		//if (m_PictureSprite)
		//{
		//	delete m_PictureSprite;
		//}
		
		// TODO: I need to make this a shared_ptr.
		//if (m_PictureTexture)
		//{
		//	delete m_PictureTexture;
		//}
	}

	PokedexEntry(const PokedexEntry& copy)
	{
		m_Name = copy.m_Name;
		m_ID = copy.m_ID;
		m_Stamina = copy.m_Stamina;
		m_Attack = copy.m_Attack;
		m_Defense = copy.m_Defense;

		m_FirstType = copy.m_FirstType;
		m_SecondType = copy.m_SecondType;

		m_Weight = copy.m_Weight; // inputed in Kilograms
		m_Height = copy.m_Height; // inputed in Meters

		m_Description = copy.m_Description;

		if (copy.m_PictureTexture)
		{
			m_PictureTexture = new sf::Texture(*copy.m_PictureTexture);
		}
		else
		{
			m_PictureTexture = nullptr;
		}

		// NOTE: for some reason when I tried to track the sprite pointer here to,
		// something went wrong and I was losing the handle to it somehow.

		//if (copy.m_PictureSprite)
		//{
		//	m_PictureSprite = new sf::Sprite(*copy.m_PictureSprite);
		//	m_PictureSprite->setTexture(*copy.m_PictureTexture);
		//}
		//else
		//{
		//	m_PictureSprite = nullptr;
		//}
		
		
	}

	PokedexEntry& operator=(const PokedexEntry& copyassign)
	{
		PokedexEntry Temp(copyassign);
		*this = Temp;
		return *this;
	}

	//PokedexEntry(PokedexEntry&& move) = delete;


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


		std::string PictureFileName = PKMNDataBase[Rows][10];
		
		if (PictureFileName != "NONE")
		{
			// Load a sprite to display
			CurrentEntry.m_PictureTexture = new sf::Texture();

			if (!CurrentEntry.m_PictureTexture->loadFromFile(PictureFileName))
				throw std::exception("Error loading picture for pokemon");

			//CurrentEntry.m_PictureSprite = new sf::Sprite(*CurrentEntry.m_PictureTexture);
			//CurrentEntry.m_PictureSprite->setTexture(*CurrentEntry.m_PictureTexture);
		}
		else
		{
			CurrentEntry.m_PictureTexture = nullptr;
			//CurrentEntry.m_PictureSprite = nullptr;
		}

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

	// NOTE: Pokemon picture stuff not added here, but it works in the SFML UI
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
	FILTERMENU,
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
		case GAMESTATE::FILTERMENU:
		{
			return std::string{ "FILTERMENU" };
		}
		case GAMESTATE::POKEDEXMENU:
		{
			return std::string{ "POKEDEXMENU" };
		}

	}

	return "INVAID CURRENT MENU ~ INVESTIGATE!";
}


#define MAX_NUMBER_OF_MAINMENU_ITEMS 3



class Menu
{
protected:
	Menu() = default;
	Menu(float width, float height);
	int& ModifySelectedItemIndex() { return selectedItemIndex; }

public:
	virtual ~Menu() {}
	virtual void drawTo(sf::RenderWindow& window) = 0;
	virtual void MoveNext() = 0;
	virtual void MovePrevious() = 0;

	int GetPressedItem() { return selectedItemIndex; }
	//sf::Font GetFont() const { return font; }



	// These two will only be overidden in Pokedex Menu class
	virtual void GoNextPokemon()  {};
	virtual void GoPreviousPokemon() {};


	virtual void UpdateMenu() {};


	// only used by Pokedex filtermenu at the moment
	virtual int GetPresssedItemPokemonID(int SelectedID) { return 0; };
	
private:
	int selectedItemIndex{ 0 };
	
};



Menu::Menu(float width, float height)
{
	//sf::Font font;
	//if (!font.loadFromFile("arial.ttf"))
	//{
	//	// TODO: handle error
	//}

	selectedItemIndex = 0;
}



class MainMenu : public Menu
{
public:
	MainMenu(float width, float height, sf::Font font);
	~MainMenu() {}

	virtual void drawTo(sf::RenderWindow& window) override;
	virtual void MoveNext() override;
	virtual void MovePrevious() override;


	//int GetPressedItem() { return selectedItemIndex; }

protected:
	//int& ModifySelectedItemIndex() { return selectedItemIndex; }

private:
	sf::Text menu[MAX_NUMBER_OF_MAINMENU_ITEMS];
	sf::Font m_Font;
	int selectedItemIndex{ 0 };
};

MainMenu::MainMenu(float width, float height, sf::Font font) : Menu(width, height)
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


#define MAX_NUMBER_OF_POKEDEX_ITEMS 18

#define MAX_NUMBER_OF_POKEMON_IN_POKEDEX 151


// A PokedexMenu hmmm, how should I organize this?
class PokedexMenu final : public Menu
{
public:
	PokedexMenu(float width, float height, sf::Font font, int CurrentPokemonID = 1);
	~PokedexMenu() {}

	virtual void drawTo(sf::RenderWindow& window) override;
	virtual void MoveNext() override;
	virtual void MovePrevious() override;


	// TODO: Make this more generic later
	PokedexEntry* CurrentEntry{ nullptr };

	// TODO: Encapsulate this variable later
	int m_CurrentPokemonID{ 1 };

	//int GetPressedItem() { return selectedItemIndex; }


	virtual void GoNextPokemon() override final
	{
		if ((m_CurrentPokemonID + 1) > MAX_NUMBER_OF_POKEMON_IN_POKEDEX)
		{
			m_CurrentPokemonID = 1;
		}
		else
		{
			m_CurrentPokemonID++;
		}
		
		UpdateMenu();
	}

	virtual void GoPreviousPokemon() override final
	{
		if ((m_CurrentPokemonID - 1) < 1)
		{
			m_CurrentPokemonID = 151;
		}
		else
		{
			m_CurrentPokemonID--;
		}
		
		UpdateMenu();
	}

	virtual void UpdateMenu() override final
	{
		CurrentEntry = &(m_PokedexData[m_CurrentPokemonID]);

		//sf::Text PokemonNameSFText(CurrentEntry->m_Name, m_Font);
		//menu[0] = PokemonNameSFText;

		//sf::Text PokemonDescriptionSFText(CurrentEntry->m_Description, m_Font);
		//menu[1] = PokemonDescriptionSFText;
		////menu[1].setFillColor(sf::Color::White);


		//sf::Text PokemonNameSFText(CurrentEntry->m_Name, m_Font);
		//menu[0] = PokemonNameSFText;
		//menu[0].setFillColor(sf::Color::Red);
		//menu[0].setPosition(sf::Vector2f(0, m_Height / (3 + 1) * 1));

		//sf::Text PokemonDescriptionSFText(CurrentEntry->m_Description, m_Font);
		//menu[1] = PokemonDescriptionSFText;
		//menu[1].setFillColor(sf::Color::White);
		//menu[1].setCharacterSize(12);
		//menu[1].setPosition(sf::Vector2f(0, m_Height / (3 + 1) * 2));

		//menu[2].setFont(m_Font);
		//menu[2].setFillColor(sf::Color::White);
		//menu[2].setString("Press A and D to move to different pokemon");
		//menu[2].setPosition(sf::Vector2f(0, m_Height / (3 + 1) * 3));

		//if (CurrentEntry->m_PictureTexture != nullptr)
		//{
		//	m_PokemonPicture = new sf::Sprite(*CurrentEntry->m_PictureTexture);
		//	m_PokemonPicture->setPosition(sf::Vector2f(m_Width / 2, 0));
		//}
		//else
		//{
		//	m_PokemonPicture = nullptr;
		//}

		sf::Text PokemonNameSFText(CurrentEntry->m_Name, m_Font);
		menu[0] = PokemonNameSFText;
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setPosition(sf::Vector2f(0, 50.f));

		sf::Text PokemonDescriptionSFText(CurrentEntry->m_Description, m_Font);
		menu[1] = PokemonDescriptionSFText;
		menu[1].setFillColor(sf::Color::White);
		menu[1].setCharacterSize(12);
		menu[1].setPosition(sf::Vector2f(0, m_Height - 50.f));

		menu[2].setFont(m_Font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Press A and D to move to different pokemon");
		menu[2].setPosition(sf::Vector2f(0, m_Height - 100.f));

		menu[3].setString("ID: ");
		menu[3].setCharacterSize(30); // default
		menu[3].setFont(m_Font);
		menu[3].setFillColor(sf::Color::White);
		menu[3].setPosition(sf::Vector2f(m_Width - 100, 50.f));

		
		sf::Text PokemonIDText(std::to_string(CurrentEntry->m_ID), m_Font);
		menu[4] = PokemonIDText;
		menu[4].setFillColor(sf::Color::White);
		menu[4].setCharacterSize(30);
		menu[4].setPosition(sf::Vector2f(menu[3].getPosition().x + 50.f, menu[3].getPosition().y));


		const int LabelPaddingX = 75;
		const int LabelPaddingY = 0;

		const int VariablePaddingX = 10;
		const int VariablePaddingY = 30;

		const unsigned int LabelCharacterSize = 20;
		const unsigned int VariableCharacterSize = 15;

		menu[5].setString("HP");
		menu[5].setCharacterSize(LabelCharacterSize); // default
		menu[5].setFont(m_Font);
		menu[5].setFillColor(sf::Color::White);
		menu[5].setPosition(sf::Vector2f(0.f, 300.f));

		sf::Text PokemonHPText(std::to_string(CurrentEntry->m_Stamina), m_Font);
		menu[6] = PokemonHPText;
		menu[6].setFillColor(sf::Color::White);
		menu[6].setCharacterSize(VariableCharacterSize);
		menu[6].setPosition(sf::Vector2f(menu[5].getPosition().x + VariablePaddingX, menu[5].getPosition().y + VariablePaddingY));


		menu[7].setString("Attack");
		menu[7].setCharacterSize(LabelCharacterSize); // default
		menu[7].setFont(m_Font);
		menu[7].setFillColor(sf::Color::White);
		menu[7].setPosition(sf::Vector2f(menu[5].getPosition().x + LabelPaddingX, menu[5].getPosition().y));


		sf::Text PokemonAttackText(std::to_string(CurrentEntry->m_Attack), m_Font);
		menu[8] = PokemonAttackText;
		menu[8].setFillColor(sf::Color::White);
		menu[8].setCharacterSize(VariableCharacterSize);
		menu[8].setPosition(sf::Vector2f(menu[7].getPosition().x + VariablePaddingX, menu[7].getPosition().y + VariablePaddingY));


		menu[9].setString("Defense");
		menu[9].setCharacterSize(LabelCharacterSize); // default
		menu[9].setFont(m_Font);
		menu[9].setFillColor(sf::Color::White);
		menu[9].setPosition(sf::Vector2f(menu[7].getPosition().x + LabelPaddingX, menu[7].getPosition().y));


		sf::Text PokemonDefenseText(std::to_string(CurrentEntry->m_Defense), m_Font);
		menu[10] = PokemonDefenseText;
		menu[10].setFillColor(sf::Color::White);
		menu[10].setCharacterSize(VariableCharacterSize);
		menu[10].setPosition(sf::Vector2f(menu[9].getPosition().x + VariablePaddingX, menu[9].getPosition().y + VariablePaddingY));





		// Print Types
		const int PokemonTypeTextPadding = 75;

		menu[11].setString("Type: ");
		menu[11].setCharacterSize(20); // default
		menu[11].setFont(m_Font);
		menu[11].setFillColor(sf::Color::White);
		menu[11].setPosition(sf::Vector2f(m_Width / 2, m_Height / 2));


		sf::Text PokemonFirstTypeText(GetPokemonTypeName(CurrentEntry->m_FirstType), m_Font);
		menu[12] = PokemonFirstTypeText;
		menu[12].setFillColor(sf::Color::White);
		menu[12].setCharacterSize(20);
		menu[12].setPosition(sf::Vector2f(menu[11].getPosition().x + PokemonTypeTextPadding, menu[11].getPosition().y));

		sf::Text PokemonSecondTypeText(GetPokemonTypeName(CurrentEntry->m_SecondType), m_Font);
		menu[13] = PokemonSecondTypeText;
		menu[13].setFillColor(sf::Color::White);
		menu[13].setCharacterSize(20);
		menu[13].setPosition(sf::Vector2f(menu[12].getPosition().x + PokemonTypeTextPadding, menu[12].getPosition().y));

		if (CurrentEntry->m_SecondType == PokemonType::NONE)
		{
			menu[13].setString("");
		}

		// Height/Weight texts

		const int PokemonWeightTextPadding = 100;

		menu[14].setString("Weight(kg): ");
		menu[14].setCharacterSize(20); // default
		menu[14].setFont(m_Font);
		menu[14].setFillColor(sf::Color::White);
		menu[14].setPosition(sf::Vector2f(300.f, 600.f));

		sf::Text PokemonWeightText(std::to_string(CurrentEntry->m_Weight), m_Font);
		menu[15] = PokemonWeightText;
		menu[15].setFillColor(sf::Color::White);
		menu[15].setCharacterSize(20);
		menu[15].setPosition(sf::Vector2f(menu[14].getPosition().x + PokemonWeightTextPadding, menu[14].getPosition().y));



		menu[16].setString("Height(m): ");
		menu[16].setCharacterSize(20); // default
		menu[16].setFont(m_Font);
		menu[16].setFillColor(sf::Color::White);
		menu[16].setPosition(sf::Vector2f(300.f, 625.f));

		sf::Text PokemonHeightText(std::to_string(CurrentEntry->m_Height), m_Font);
		menu[17] = PokemonHeightText;
		menu[17].setFillColor(sf::Color::White);
		menu[17].setCharacterSize(20);
		menu[17].setPosition(sf::Vector2f(menu[16].getPosition().x + PokemonWeightTextPadding, menu[16].getPosition().y));



		if (CurrentEntry->m_PictureTexture != nullptr)
		{
			if (m_PokemonPicture)
			{
				delete m_PokemonPicture;
				m_PokemonPicture = new sf::Sprite(*CurrentEntry->m_PictureTexture);
				m_PokemonPicture->setPosition(sf::Vector2f((m_Width / 2) - 200.f, 0));
			}
			else
			{
				m_PokemonPicture = new sf::Sprite(*CurrentEntry->m_PictureTexture);
				m_PokemonPicture->setPosition(sf::Vector2f((m_Width / 2) - 200.f, 0));
			}

			//m_PokemonPicture = new sf::Sprite(*CurrentEntry->m_PictureTexture);
			//m_PokemonPicture->setPosition(sf::Vector2f((m_Width / 2) - 100.f, 0));
		}
		else
		{
			m_PokemonPicture = nullptr;
		}

		
		//m_PokemonPicture->setColor(sf::Color::Transparent);
	}

	//sf::Font GetFont() const { return m_font; }

protected:
	//int& ModifySelectedItemIndex() { return selectedItemIndex; }

private:

	//int selectedItemIndex{ 0 };

	//sf::Text menu[MAX_NUMBER_OF_POKEDEX_ITEMS]; // not using this until I know how many i actually need (using 3 as a temp variable for testing below)
	int m_Width{ 0 };
	int m_Height{ 0 };

	sf::Text menu[MAX_NUMBER_OF_POKEDEX_ITEMS];
	sf::Font m_Font;
	
	sf::Sprite* m_PokemonPicture{ nullptr };
};

PokedexMenu::PokedexMenu(float width, float height, sf::Font font, int CurrentPokemonID) : Menu(width, height)
{
	m_Font = font;
	m_CurrentPokemonID = CurrentPokemonID;

	CurrentEntry = &(m_PokedexData[m_CurrentPokemonID]);


	m_Width = width;
	m_Height = height;


	sf::Text PokemonNameSFText(CurrentEntry->m_Name, m_Font);
	menu[0] = PokemonNameSFText;
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setPosition(sf::Vector2f(0, 50.f));

	sf::Text PokemonDescriptionSFText(CurrentEntry->m_Description, m_Font);
	menu[1] = PokemonDescriptionSFText;
	menu[1].setFillColor(sf::Color::White);
	menu[1].setCharacterSize(12);
	menu[1].setPosition(sf::Vector2f(0, m_Height - 50.f));

	menu[2].setFont(m_Font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Press A and D to move to different pokemon");
	menu[2].setPosition(sf::Vector2f(0, m_Height - 100.f));

	menu[3].setString("ID: ");
	menu[3].setCharacterSize(30); // default
	menu[3].setFont(m_Font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setPosition(sf::Vector2f(m_Width - 100, 50.f));

	sf::Text PokemonIDText(std::to_string(CurrentEntry->m_ID), m_Font);
	menu[4] = PokemonIDText;
	menu[4].setFillColor(sf::Color::White);
	menu[4].setCharacterSize(30);
	menu[4].setPosition(sf::Vector2f(menu[3].getPosition().x + 50, menu[3].getPosition().y));




	const int LabelPaddingX = 75;
	const int LabelPaddingY = 0;

	const int VariablePaddingX = 10;
	const int VariablePaddingY = 30;

	const unsigned int LabelCharacterSize = 20;
	const unsigned int VariableCharacterSize = 15;

	menu[5].setString("HP");
	menu[5].setCharacterSize(LabelCharacterSize); // default
	menu[5].setFont(m_Font);
	menu[5].setFillColor(sf::Color::White);
	menu[5].setPosition(sf::Vector2f(0.f, 300.f));

	sf::Text PokemonHPText(std::to_string(CurrentEntry->m_Stamina), m_Font);
	menu[6] = PokemonHPText;
	menu[6].setFillColor(sf::Color::White);
	menu[6].setCharacterSize(VariableCharacterSize);
	menu[6].setPosition(sf::Vector2f(menu[5].getPosition().x + VariablePaddingX, menu[5].getPosition().y + VariablePaddingY));


	menu[7].setString("Attack");
	menu[7].setCharacterSize(LabelCharacterSize); // default
	menu[7].setFont(m_Font);
	menu[7].setFillColor(sf::Color::White);
	menu[7].setPosition(sf::Vector2f(menu[5].getPosition().x + LabelPaddingX, menu[5].getPosition().y));


	sf::Text PokemonAttackText(std::to_string(CurrentEntry->m_Attack), m_Font);
	menu[8] = PokemonAttackText;
	menu[8].setFillColor(sf::Color::White);
	menu[8].setCharacterSize(VariableCharacterSize);
	menu[8].setPosition(sf::Vector2f(menu[7].getPosition().x + VariablePaddingX, menu[7].getPosition().y + VariablePaddingY));


	menu[9].setString("Defense");
	menu[9].setCharacterSize(LabelCharacterSize); // default
	menu[9].setFont(m_Font);
	menu[9].setFillColor(sf::Color::White);
	menu[9].setPosition(sf::Vector2f(menu[7].getPosition().x + LabelPaddingX, menu[7].getPosition().y));


	sf::Text PokemonDefenseText(std::to_string(CurrentEntry->m_Defense), m_Font);
	menu[10] = PokemonDefenseText;
	menu[10].setFillColor(sf::Color::White);
	menu[10].setCharacterSize(VariableCharacterSize);
	menu[10].setPosition(sf::Vector2f(menu[9].getPosition().x + VariablePaddingX, menu[9].getPosition().y + VariablePaddingY));




	// Print Types
	const int PokemonTypeTextPadding = 100;

	menu[11].setString("Type: ");
	menu[11].setCharacterSize(20); // default
	menu[11].setFont(m_Font);
	menu[11].setFillColor(sf::Color::White);
	menu[11].setPosition(sf::Vector2f(m_Width / 2, m_Height / 2));


	sf::Text PokemonFirstTypeText(GetPokemonTypeName(CurrentEntry->m_FirstType), m_Font);
	menu[12] = PokemonFirstTypeText;
	menu[12].setFillColor(sf::Color::White);
	menu[12].setCharacterSize(20);
	menu[12].setPosition(sf::Vector2f(menu[11].getPosition().x + PokemonTypeTextPadding, menu[11].getPosition().y));

	sf::Text PokemonSecondTypeText(GetPokemonTypeName(CurrentEntry->m_SecondType), m_Font);
	menu[13] = PokemonSecondTypeText;
	menu[13].setFillColor(sf::Color::White);
	menu[13].setCharacterSize(20);
	menu[13].setPosition(sf::Vector2f(menu[12].getPosition().x + PokemonTypeTextPadding, menu[12].getPosition().y));

	if (CurrentEntry->m_SecondType == PokemonType::NONE)
	{
		menu[13].setString("");
	}




	const int PokemonWeightTextPadding = 100;

	menu[14].setString("Weight(kg): ");
	menu[14].setCharacterSize(20); // default
	menu[14].setFont(m_Font);
	menu[14].setFillColor(sf::Color::White);
	menu[14].setPosition(sf::Vector2f(300.f, 600.f));

	sf::Text PokemonWeightText(std::to_string(CurrentEntry->m_Weight), m_Font);
	menu[15] = PokemonWeightText;
	menu[15].setFillColor(sf::Color::White);
	menu[15].setCharacterSize(20);
	menu[15].setPosition(sf::Vector2f(menu[14].getPosition().x + PokemonWeightTextPadding, menu[14].getPosition().y));



	menu[16].setString("Height(m): ");
	menu[16].setCharacterSize(20); // default
	menu[16].setFont(m_Font);
	menu[16].setFillColor(sf::Color::White);
	menu[16].setPosition(sf::Vector2f(300.f, 625.f));

	sf::Text PokemonHeightText(std::to_string(CurrentEntry->m_Height), m_Font);
	menu[17] = PokemonHeightText;
	menu[17].setFillColor(sf::Color::White);
	menu[17].setCharacterSize(20);
	menu[17].setPosition(sf::Vector2f(menu[16].getPosition().x + PokemonWeightTextPadding, menu[16].getPosition().y));



	if (CurrentEntry->m_PictureTexture != nullptr)
	{
		m_PokemonPicture = new sf::Sprite(*CurrentEntry->m_PictureTexture);
		m_PokemonPicture->setPosition(sf::Vector2f((m_Width / 2) - 200.f, 0));
	}
	else
	{
		m_PokemonPicture = nullptr;
	}


}


void PokedexMenu::drawTo(sf::RenderWindow& window)
{
	//for (int i = 0; i < MAX_NUMBER_OF_POKEDEX_ITEMS; i++)
	//{
	//	window.draw(menu[i]);
	//}

	for (int i = 0; i < MAX_NUMBER_OF_POKEDEX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
	
	if (m_PokemonPicture != nullptr)
	{
		window.draw(*m_PokemonPicture);
	}
}

// These are unused atm
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
	if (GetPressedItem() + 1 < 11)
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






// Testing filter menu

#define MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES 5
#define MAX_NUMBER_OF_POKEDEX_ENTRIES 151

class PokedexFilterMenu : public Menu
{

public:
	PokedexFilterMenu(float width, float height, sf::Font font);
	~PokedexFilterMenu() {}

	virtual void drawTo(sf::RenderWindow& window) override;
	virtual void MoveNext() override;
	virtual void MovePrevious() override;

	virtual void UpdateMenu() override;

	virtual int GetPresssedItemPokemonID(int SelectedID) override
	{
		return m_PokemonListData->at(TextIndexes[SelectedID]).m_ID - 1;
	}

private:
	sf::Font m_Font;
	sf::Text m_menu[MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES];
	int selectedItemIndex{ 0 };
	sf::RectangleShape m_BackgroundRect;
	std::vector<PokedexEntry>* m_PokemonListData{ nullptr };

	std::vector<int> TextIndexes{ 1, 2, 3, 4, 5 };

	void IncreaseTextIndexes(); 
	void DecreaseTextIndexes();

	
};

PokedexFilterMenu::PokedexFilterMenu(float width, float height, sf::Font font) : Menu(width, height)
{
	m_Font = font;
	m_BackgroundRect.setSize(sf::Vector2f(100, 250));
	m_BackgroundRect.setPosition(sf::Vector2f(100, 250));
	m_BackgroundRect.setFillColor(sf::Color::Transparent);
	m_BackgroundRect.setOutlineColor(sf::Color::Black);
	m_BackgroundRect.setOutlineThickness(1);
	m_PokemonListData = &m_PokedexData;

	const unsigned int TextCharSize = 15;
	
	sf::Text FirstEntrySFText(m_PokemonListData->at(TextIndexes[0]).m_Name, m_Font);
	m_menu[0] = FirstEntrySFText;
	m_menu[0].setFillColor(sf::Color::Red);
	m_menu[0].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y));// height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 1));
	m_menu[0].setCharacterSize(TextCharSize);

	sf::Text SecondEntrySFText(m_PokemonListData->at(TextIndexes[1]).m_Name, m_Font);
	m_menu[1] = SecondEntrySFText;
	m_menu[1].setFillColor(sf::Color::White);
	m_menu[1].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y + 15)); // height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 2));
	m_menu[1].setCharacterSize(TextCharSize);

	sf::Text ThirdEntrySFText(m_PokemonListData->at(TextIndexes[2]).m_Name, m_Font);
	m_menu[2] = ThirdEntrySFText;
	m_menu[2].setFillColor(sf::Color::White);
	m_menu[2].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y + 30)); // height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 3));
	m_menu[2].setCharacterSize(TextCharSize);

	sf::Text FourthEntrySFText(m_PokemonListData->at(TextIndexes[3]).m_Name, m_Font);
	m_menu[3] = FourthEntrySFText;
	m_menu[3].setFillColor(sf::Color::White);
	m_menu[3].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y + 45)); // height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 4));
	m_menu[3].setCharacterSize(TextCharSize);

	sf::Text FifthEntrySFText(m_PokemonListData->at(TextIndexes[4]).m_Name, m_Font);
	m_menu[4] = FifthEntrySFText;
	m_menu[4].setFillColor(sf::Color::White);
	m_menu[4].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y + 60)); // height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 5));
	m_menu[4].setCharacterSize(TextCharSize);


}

// TODO: Create a highlight I will start by highlighting the first name
// - When I get to the bottom of the list and keep going then all the index names will update by one to show I am scrolling down in the list.

// TODO: Once list scroll is working, increase the size of it to 10

// TODO: Once size of the list is 10 and updating correctly, Make it so hitting enter on that name will open the pokedex menu for that pokemon.

// TODO: Add functionality for the pokedex individual entry menus so that when you hit backspace it will open the PokedexFilterMenu again.

// TODO: Add a couple more images to the Pokemon CSV sheet, (250,250, transparent)

// TODO: Tidy up the individual pokedex menu so its a more presentable

void PokedexFilterMenu::drawTo(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES; i++)
	{
		window.draw(m_menu[i]);
	}

	window.draw(m_BackgroundRect);

}

void PokedexFilterMenu::MovePrevious()
{
	if (GetPressedItem() - 1 <= 0)
	{
		m_menu[GetPressedItem()].setFillColor(sf::Color::White);
		
		ModifySelectedItemIndex() = 0;

		if (TextIndexes[0] > 1)
		{
			DecreaseTextIndexes();
			UpdateMenu();
		}

		m_menu[GetPressedItem()].setFillColor(sf::Color::Red);

	}
	else if (GetPressedItem() - 1 > 0)
	{
		m_menu[GetPressedItem()].setFillColor(sf::Color::White);
		ModifySelectedItemIndex()--;
		m_menu[GetPressedItem()].setFillColor(sf::Color::Red);
	}


	//if (TextIndexes[0] < 1)
	//{
	//	// do nothing
	//}
	//else
	//{
	//	ModifySelectedItemIndex() = 0;

	//	DecreaseTextIndexes();
	//	UpdateMenu();

	//	m_menu[GetPressedItem()].setFillColor(sf::Color::Red);
	//}
}

void PokedexFilterMenu::MoveNext()
{
	if (GetPressedItem() + 1 == MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES)
	{
		IncreaseTextIndexes();
		UpdateMenu();
		m_menu[GetPressedItem()].setFillColor(sf::Color::Red);

	}
	else if (GetPressedItem() + 1 < MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES)
	{
		m_menu[GetPressedItem()].setFillColor(sf::Color::White);
		ModifySelectedItemIndex()++;
		m_menu[GetPressedItem()].setFillColor(sf::Color::Red);
	}
	//else
	//{
	//	m_menu[GetPressedItem()].setFillColor(sf::Color::White);
	//	ModifySelectedItemIndex() = 0;
	//	m_menu[GetPressedItem()].setFillColor(sf::Color::Red);
	//}
}

void PokedexFilterMenu::UpdateMenu()
{
	m_BackgroundRect.setSize(sf::Vector2f(100, 250));
	m_BackgroundRect.setPosition(sf::Vector2f(100, 250));
	m_BackgroundRect.setFillColor(sf::Color::Transparent);
	m_BackgroundRect.setOutlineColor(sf::Color::Black);
	m_BackgroundRect.setOutlineThickness(1);
	m_PokemonListData = &m_PokedexData;

	const unsigned int TextCharSize = 15;

	sf::Text FirstEntrySFText(m_PokemonListData->at(TextIndexes[0]).m_Name, m_Font);
	m_menu[0] = FirstEntrySFText;
	//m_menu[0].setFillColor(sf::Color::Red);
	m_menu[0].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y));// height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 1));
	m_menu[0].setCharacterSize(TextCharSize);

	sf::Text SecondEntrySFText(m_PokemonListData->at(TextIndexes[1]).m_Name, m_Font);
	m_menu[1] = SecondEntrySFText;
	//m_menu[1].setFillColor(sf::Color::Red);
	m_menu[1].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y + 15)); // height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 2));
	m_menu[1].setCharacterSize(TextCharSize);

	sf::Text ThirdEntrySFText(m_PokemonListData->at(TextIndexes[2]).m_Name, m_Font);
	m_menu[2] = ThirdEntrySFText;
	//m_menu[2].setFillColor(sf::Color::Red);
	m_menu[2].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y + 30)); // height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 3));
	m_menu[2].setCharacterSize(TextCharSize);

	sf::Text FourthEntrySFText(m_PokemonListData->at(TextIndexes[3]).m_Name, m_Font);
	m_menu[3] = FourthEntrySFText;
	//m_menu[3].setFillColor(sf::Color::Red);
	m_menu[3].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y + 45)); // height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 4));
	m_menu[3].setCharacterSize(TextCharSize);

	sf::Text FifthEntrySFText(m_PokemonListData->at(TextIndexes[4]).m_Name, m_Font);
	m_menu[4] = FifthEntrySFText;
	//m_menu[4].setFillColor(sf::Color::Red);
	m_menu[4].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, m_BackgroundRect.getPosition().y + 60)); // height / (MAX_NUMBER_OF_POKEDEX_FILTER_ENTRIES + 1) * 5));
	m_menu[4].setCharacterSize(TextCharSize);
}

void PokedexFilterMenu::IncreaseTextIndexes() 
{
	for (int i = 0; i < TextIndexes.size(); ++i) 
	{ 
		TextIndexes[i]++; 
	} 
}

void PokedexFilterMenu::DecreaseTextIndexes() 
{
	for (int i = 0; i < TextIndexes.size(); ++i) 
	{ 
		TextIndexes[i]--;
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




	Menu* CurrentMenu = new MainMenu(width, height, DebugFont);




	while (window.isOpen())
	{
		sf::Event Event;


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
								//CurrentMainMenu->MoveNext();
								CurrentMenu->MoveNext();
								break;
							}
							else if (CurrentGameState == GAMESTATE::FILTERMENU)
							{
								CurrentMenu->MoveNext();
								break;
							}
							else if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							{
								CurrentMenu->GoNextPokemon();
								break;
							}

						}
						case sf::Keyboard::Left:
						{
							if (CurrentGameState == GAMESTATE::MAINMENU)
							{
								//CurrentMainMenu->MovePrevious();
								CurrentMenu->MovePrevious();
								break;
							}
							else if (CurrentGameState == GAMESTATE::FILTERMENU)
							{
								CurrentMenu->MovePrevious();
								break;
							}
							else if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							{
								CurrentMenu->GoPreviousPokemon();
								break;
							}
						}
						case sf::Keyboard::Return:
						{
							if (CurrentGameState == GAMESTATE::MAINMENU)
							{
								//switch (CurrentMainMenu->GetPressedItem())
								switch (CurrentMenu->GetPressedItem())
								{
									case 0:
									{
										std::cout << "Play button has been pressed" << std::endl;
										

										// TODO: Temp comment out for testing

										//delete CurrentMenu;
										//CurrentMenu = new PokedexMenu(width, height, DebugFont);
										////CurrentPokedexMenu = new PokedexMenu(width, height, DebugFont);
										//CurrentGameState = GAMESTATE::POKEDEXMENU;
										//
										//GameStateDebugText.setString("Current GameState: " + GetGameStateAsString(CurrentGameState));

										delete CurrentMenu;
										CurrentMenu = new PokedexFilterMenu(width, height, DebugFont);
										CurrentGameState = GAMESTATE::FILTERMENU;
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
							else if (CurrentGameState == GAMESTATE::FILTERMENU)
							{
								//switch (CurrentMainMenu->GetPressedItem())
								switch (CurrentMenu->GetPressedItem())
								{
								
									case 0:
									{
										auto ChosenID = CurrentMenu->GetPresssedItemPokemonID(0);

										std::cout << "First Item In Filter Menu Selected Entering Menu" << std::endl;
										delete CurrentMenu;
										CurrentMenu = new PokedexMenu(width, height, DebugFont, ChosenID);
										CurrentGameState = GAMESTATE::POKEDEXMENU;
										GameStateDebugText.setString("Current GameState: " + GetGameStateAsString(CurrentGameState));

										break;
									}
									case 1:
									{

										auto ChosenID = CurrentMenu->GetPresssedItemPokemonID(1);
										
										std::cout << "Second Item In Filter Menu Selected Entering Menu" << std::endl;
										delete CurrentMenu;
										CurrentMenu = new PokedexMenu(width, height, DebugFont, ChosenID);
										CurrentGameState = GAMESTATE::POKEDEXMENU;
										GameStateDebugText.setString("Current GameState: " + GetGameStateAsString(CurrentGameState));

										break;
									}
									case 2:
									{
										auto ChosenID = CurrentMenu->GetPresssedItemPokemonID(2);
										
										std::cout << "Third Item In Filter Menu Selected Entering Menu" << std::endl;
										delete CurrentMenu;
										CurrentMenu = new PokedexMenu(width, height, DebugFont, ChosenID);
										CurrentGameState = GAMESTATE::POKEDEXMENU;
										GameStateDebugText.setString("Current GameState: " + GetGameStateAsString(CurrentGameState));

										break;

									}
									case 3:
									{
										auto ChosenID = CurrentMenu->GetPresssedItemPokemonID(3);

										std::cout << "Fourth Item In Filter Menu Selected Entering Menu" << std::endl;
										delete CurrentMenu;
										CurrentMenu = new PokedexMenu(width, height, DebugFont, ChosenID);
										CurrentGameState = GAMESTATE::POKEDEXMENU;
										GameStateDebugText.setString("Current GameState: " + GetGameStateAsString(CurrentGameState));

										break;

									}
									case 4:
									{
										auto ChosenID = CurrentMenu->GetPresssedItemPokemonID(4);

										std::cout << "Fifth Item In Filter Menu Selected Entering Menu" << std::endl;
										delete CurrentMenu;
										CurrentMenu = new PokedexMenu(width, height, DebugFont, ChosenID);
										CurrentGameState = GAMESTATE::POKEDEXMENU;
										GameStateDebugText.setString("Current GameState: " + GetGameStateAsString(CurrentGameState));

										break;

									}
								}
							}
							else if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							{
								break;
							}
						}
						case sf::Keyboard::D:
						{
							if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							{
								// CurrentPokedexMenu->GoNextPokemon();
								CurrentMenu->GoNextPokemon();
								break;
							}
							else if (CurrentGameState == GAMESTATE::MAINMENU)
							{
								break;
							}
						}
						case sf::Keyboard::A:
						{
							if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							{
								// CurrentPokedexMenu->GoPreviousPokemon();
								CurrentMenu->GoPreviousPokemon();
								break;
							}
							else if (CurrentGameState == GAMESTATE::MAINMENU)
							{
								break;
							}
						}
						case sf::Keyboard::Backspace:
						{
							if (CurrentGameState == GAMESTATE::POKEDEXMENU)
							{
								delete CurrentMenu;
								CurrentMenu = new PokedexFilterMenu(width, height, DebugFont);
								CurrentGameState = GAMESTATE::FILTERMENU;
								GameStateDebugText.setString("Current GameState: " + GetGameStateAsString(CurrentGameState));

								break;
							}
							else if (CurrentGameState == GAMESTATE::MAINMENU)
							{
								break;
							}
							else if (CurrentGameState == GAMESTATE::FILTERMENU)
							{
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


		window.clear(sf::Color::Cyan);

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


		window.draw(GameStateDebugText);

		if (CurrentMenu != nullptr)
		{
			CurrentMenu->drawTo(window);
		}
		


		window.display();
	}

	return 0;
}








// TODO: Filter this out into its own class

//#define MAX_NUMBER_OF_LIST_VIEW_ITEMS 10
//
//class PokedexListView
//{
//private:
//	// define a 120x50 rectangle
//	sf::RectangleShape m_BackgroundRect; // (sf::Vector2f(120, 50));
//	sf::Text m_DisplayTexts[10];
//	sf::Font m_Font;
//
//	std::vector<PokedexEntry>* m_PokemonListData{ nullptr };
//
//
//public:
//
//	PokedexListView() = default;
//
//	PokedexListView(int Width, int Height, sf::Font DisplayFont);
//
//};
//
//PokedexListView::PokedexListView(int Width, int Height, sf::Font DisplayFont)
//{
//	m_PokemonListData = &m_PokedexData;
//	m_Font = DisplayFont;
//

//
//	sf::Text SixthEntrySFText(m_PokemonListData->at(5).m_Name, m_Font);
//	m_DisplayTexts[5] = FirstEntrySFText;
//	m_DisplayTexts[5].setFillColor(sf::Color::Red);
//	m_DisplayTexts[5].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, Height / (MAX_NUMBER_OF_LIST_VIEW_ITEMS + 1) * 6));
//	m_DisplayTexts[5].setCharacterSize(10);
//
//	sf::Text SeventhEntrySFText(m_PokemonListData->at(6).m_Name, m_Font);
//	m_DisplayTexts[6] = FirstEntrySFText;
//	m_DisplayTexts[6].setFillColor(sf::Color::Red);
//	m_DisplayTexts[6].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, Height / (MAX_NUMBER_OF_LIST_VIEW_ITEMS + 1) * 7));
//	m_DisplayTexts[6].setCharacterSize(10);
//
//	sf::Text EigthEntrySFText(m_PokemonListData->at(7).m_Name, m_Font);
//	m_DisplayTexts[7] = FirstEntrySFText;
//	m_DisplayTexts[7].setFillColor(sf::Color::Red);
//	m_DisplayTexts[7].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, Height / (MAX_NUMBER_OF_LIST_VIEW_ITEMS + 1) * 8));
//	m_DisplayTexts[7].setCharacterSize(10);
//
//	sf::Text NinthEntrySFText(m_PokemonListData->at(8).m_Name, m_Font);
//	m_DisplayTexts[8] = FirstEntrySFText;
//	m_DisplayTexts[8].setFillColor(sf::Color::Red);
//	m_DisplayTexts[8].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, Height / (MAX_NUMBER_OF_LIST_VIEW_ITEMS + 1) * 9));
//	m_DisplayTexts[8].setCharacterSize(10);
//
//	sf::Text TenthEntrySFText(m_PokemonListData->at(9).m_Name, m_Font);
//	m_DisplayTexts[9] = FirstEntrySFText;
//	m_DisplayTexts[9].setFillColor(sf::Color::Red);
//	m_DisplayTexts[9].setPosition(sf::Vector2f(m_BackgroundRect.getPosition().x, Height / (MAX_NUMBER_OF_LIST_VIEW_ITEMS + 1) * 10));
//	m_DisplayTexts[9].setCharacterSize(10);
//
//
//	//for (int i = 0; i < 20; ++i)
//	//{
//	//	m_DisplayTexts->setCharacterSize(10);
//	//}
//
//
//	//sf::Text PokemonNameSFText(CurrentEntry->m_Name, m_Font);
//	//menu[0] = PokemonNameSFText;
//	//menu[0].setFillColor(sf::Color::Red);
//	//menu[0].setPosition(sf::Vector2f(0, height / (3 + 1) * 1));
//
//	//m_DisplayTexts[0]
//}