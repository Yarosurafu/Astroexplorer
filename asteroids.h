#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
using namespace sf;

class Asteroids
{
	Texture m_asteroidTexture;
	Sprite m_asteroidSprite;
	std::vector<Sprite> m_asteroids;

public:
	Asteroids();
	Asteroids& createAsteroids();
	Asteroids& moveAsteroids(float time);
	Asteroids& deleteAsteroids();

	std::vector<Sprite>& getAsteroids() { return m_asteroids; }
};