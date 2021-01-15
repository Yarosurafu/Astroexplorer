#include "spaceship.h"

SpaceShip::SpaceShip() :
	m_shipTexture{},
	m_fireTexture{}
{
	//Загрузка текстуры корабля
	Image shipImage;
	if (!shipImage.loadFromFile("Images/ship.png")) {
		shipImage.create(50, 50, Color::Blue);
	};
	m_shipTexture.loadFromImage(shipImage);

	//Загрузка текстуры огней
	Image fireImage;
	if (!fireImage.loadFromFile("Images/fire.png")) {
		fireImage.create(50, 50, Color::Red);
	};
	m_fireTexture.loadFromImage(fireImage);
	
	//Настройка спрайтов
	m_shipSprite.setTexture(m_shipTexture);
	m_shipSprite.setTextureRect(IntRect(345, 47, SPRITE_SIZE_X, SPRITE_SIZE_Y));
	m_shipSprite.setPosition(300, 450);
	m_shipSprite.setColor(Color::Yellow);

	m_firstFire.setTexture(m_fireTexture);
	m_firstFire.setTextureRect(IntRect(30, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
	m_firstFire.setRotation(180);

	m_secondFire.setTexture(m_fireTexture);
	m_secondFire.setTextureRect(IntRect(30, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
	m_secondFire.setRotation(180);
}

//изменение положения огней относительно корабля
SpaceShip& SpaceShip::setFireSprite()
{
	Vector2f currentShipPosition;
	currentShipPosition = m_shipSprite.getPosition();
	currentShipPosition.x += 23;
	currentShipPosition.y += 82;
	m_firstFire.setPosition(currentShipPosition);
	currentShipPosition = m_shipSprite.getPosition();
	currentShipPosition.x += 38;
	currentShipPosition.y += 82;
	m_secondFire.setPosition(currentShipPosition);
	return *this;
}

//смена спрайта огня для анимации
//спрайт меняется каждые 50 миллисекунд
SpaceShip& SpaceShip::changeFireSprite(int frame)
{
	switch (frame) {
	case 50:
		m_firstFire.setTextureRect(IntRect(30, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
		m_secondFire.setTextureRect(IntRect(30, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
		break;
	case 100:
		m_firstFire.setTextureRect(IntRect(47, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
		m_secondFire.setTextureRect(IntRect(64, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
		break;
	case 150:
		m_firstFire.setTextureRect(IntRect(64, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
		m_secondFire.setTextureRect(IntRect(47, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
		break;
	case 200:
		m_firstFire.setTextureRect(IntRect(83, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
		m_secondFire.setTextureRect(IntRect(83, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
		break;
	}
	setFireSprite();
	return *this;
}

//смена позиции корабля
SpaceShip& SpaceShip::moveShip(int direction, float time)
{
	Vector2f currentPosition;
	currentPosition = m_shipSprite.getPosition();
	switch (direction) {
	case 1:
		if (currentPosition.x >= 0)
			m_shipSprite.move(-0.1 * time, 0);
		break;
	case 2:
		if (currentPosition.x <= 551)
			m_shipSprite.move(0.1 * time, 0);
		break;
	case 3:
		if (currentPosition.y >= 0)
			m_shipSprite.move(0, -0.1 * time);
		break;
	case 4:
		if (currentPosition.y <= 854)
			m_shipSprite.move(0, 0.1 * time);
		break;
	}

	return *this;
}