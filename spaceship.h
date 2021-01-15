#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
using namespace sf;

class SpaceShip {
	const unsigned short SPRITE_SIZE_X = 49;
	const unsigned short SPRITE_SIZE_Y = 46;
	const unsigned short FIRE_SIZE_X = 12;
	const unsigned short FIRE_SIZE_Y = 41;
	const Texture m_textureArg;
	const Texture m_fireTexture;
	Sprite m_shipSprite; //������ �������
	Sprite m_firstFire; //������ ���� �� ������� �����
	Sprite m_secondFire; //������ ���� �� ������� �����

public:
	SpaceShip(const Texture& textureArg, const Texture& fireTexture);
	Spaceship
};