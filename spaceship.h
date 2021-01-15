#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
using namespace sf;

class SpaceShip {
	//������� �������� ������� � ����� �� �����
	const unsigned short SPRITE_SIZE_X = 49;
	const unsigned short SPRITE_SIZE_Y = 46;
	const unsigned short FIRE_SIZE_X = 12;
	const unsigned short FIRE_SIZE_Y = 41;

	
	Texture m_shipTexture;//�������� �������
	Texture m_fireTexture;//�������� �����

	Sprite m_shipSprite; //������ �������
	Sprite m_firstFire; //������ ���� �� ������� �����
	Sprite m_secondFire; //������ ���� �� ������� �����
	SpaceShip& setFireSprite();//��������� ��������� ����� ������������ �������

public:
	SpaceShip();
	SpaceShip& moveShip(int direction, float time);//����� ������� �������
	SpaceShip& changeFireSprite(int frame);//����� ������� ���� ��� ��������
	Sprite& getFirstFireSprite() { return m_firstFire; }
	Sprite& getSecondFireSprite() { return m_secondFire;  }
	Sprite& getSprite() { return m_shipSprite;  }
};