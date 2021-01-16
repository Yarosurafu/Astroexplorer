#include "asteroids.h"

Asteroids::Asteroids()
{
	Image astImg;
	astImg.loadFromFile("Images/effects.png");
	m_asteroidTexture.loadFromImage(astImg);
	m_asteroidSprite.setTexture(m_asteroidTexture);
	m_asteroidSprite.setTextureRect(IntRect(98, 130, 26, 29));
}

Asteroids& Asteroids::createAsteroids()
{
	int posX = rand() % 600;
	Sprite newAsteroid;
	newAsteroid.setTexture(m_asteroidTexture);
	newAsteroid.setTextureRect(m_asteroidSprite.getTextureRect());
	newAsteroid.setPosition(posX, 0);
	m_asteroids.push_back(newAsteroid);
	return *this;
}

Asteroids& Asteroids::moveAsteroids(float time)
{
	Vector2f currentPosition;
	for (int i = 0; i < m_asteroids.size(); ++i) {
		currentPosition = m_asteroids[i].getPosition();
		currentPosition.y += 0.05 * time;
		if (currentPosition.y > 900) {
			m_asteroids.erase(m_asteroids.begin() + i);
			continue;
		}
		m_asteroids[i].setPosition(currentPosition);
	}
	return *this;
}

Asteroids& Asteroids::deleteAsteroids()
{
	for (int i = m_asteroids.size() - 1; i >= 0; --i)
		m_asteroids.erase(m_asteroids.begin() + i);
	return *this;
}