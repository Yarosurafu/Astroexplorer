#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
using namespace sf;

class Map
{
	//-----�������� ������-----
	Texture m_alienTexture;
	Texture m_sandTexture;
	Texture m_earthTexture;
	//-------------------------

	//-----������� ������-----
	Sprite m_alienPlanet;
	Sprite m_sandPlanet;
	Sprite m_earthPlanet;
	//-------------------------

	RectangleShape m_space;//������
	std::vector<CircleShape> m_closeStars;//������, �������� ����� ������� �����
	std::vector<CircleShape> m_farStars;//������, �������� ����� ��������� �����	
	std::vector<Sprite> m_planets;//������ ������

	void createStars(std::vector<CircleShape>& stars, const Color& color);

public:
	Map();
	Map& createPlanet();//������������� �������
	Map& movePlanet();//�������� ������
	//����� �� ���������� ������ ����
	bool isPlanet() { return m_planets.size() != 0; }
	Map& createCloseStars();//��������� ���� ��������� �����
	Map& createFarStars();//��������� ���� ������� �����
	Map& moveStars(float time);//�������� ����

	RectangleShape& getSpace() { return m_space; }
	std::vector<CircleShape>& getCloseStars() { return m_closeStars; }
	std::vector<CircleShape>& getFarStars() { return m_farStars; }
	Sprite& getPlanet() { return m_planets[0]; }
};
