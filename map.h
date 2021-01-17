#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
using namespace sf;

class Map
{
	//-----Текстуры планет-----
	Texture m_alienTexture;
	Texture m_sandTexture;
	Texture m_earthTexture;
	//-------------------------

	//-----Спрайты планет-----
	Sprite m_alienPlanet;
	Sprite m_sandPlanet;
	Sprite m_earthPlanet;
	//-------------------------

	RectangleShape m_space;//космос
	std::vector<CircleShape> m_closeStars;//вектор, хранящий звёзды заднего плана
	std::vector<CircleShape> m_farStars;//вектор, хранящий звёзды переднего плана	
	std::vector<Sprite> m_planets;//вектор планет

	void createStars(std::vector<CircleShape>& stars, const Color& color);

public:
	Map();
	Map& createPlanet();//сгенерировать планету
	Map& movePlanet();//движение планет
	//Равно ли количество планет нулю
	bool isPlanet() { return m_planets.size() != 0; }
	Map& createCloseStars();//генерация звёзд переднего плана
	Map& createFarStars();//генерация звёзд заднего плана
	Map& moveStars(float time);//движение звёзд

	RectangleShape& getSpace() { return m_space; }
	std::vector<CircleShape>& getCloseStars() { return m_closeStars; }
	std::vector<CircleShape>& getFarStars() { return m_farStars; }
	Sprite& getPlanet() { return m_planets[0]; }
};
