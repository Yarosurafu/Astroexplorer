#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
using namespace sf;

class SpaceShip {
	//Размеры спрайтов корабля и огней из сопел
	const unsigned short SPRITE_SIZE_X = 49;
	const unsigned short SPRITE_SIZE_Y = 46;
	const unsigned short FIRE_SIZE_X = 12;
	const unsigned short FIRE_SIZE_Y = 41;

	
	Texture m_shipTexture;//текстура корабля
	Texture m_fireTexture;//текстура огней

	Sprite m_shipSprite; //спрайт корабля
	Sprite m_firstFire; //спрайт огня из первого сопла
	Sprite m_secondFire; //спрайт огня из второго сопла
	SpaceShip& setFireSprite();//изменение положения огней относительно корабля

public:
	SpaceShip();
	SpaceShip& moveShip(int direction, float time);//смена позиции корабля
	SpaceShip& changeFireSprite(int frame);//смена спрайта огня для анимации
	Sprite& getFirstFireSprite() { return m_firstFire; }
	Sprite& getSecondFireSprite() { return m_secondFire;  }
	Sprite& getSprite() { return m_shipSprite;  }
};