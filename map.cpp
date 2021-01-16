#include "map.h"

Map::Map() :
	m_sandTexture{},
	m_alienTexture{},
	m_earthTexture{}
{
	//-----Загрузка текстур-----
	Image alienImage;
	alienImage.loadFromFile("Images/alienPlanet.png");
	m_alienTexture.loadFromImage(alienImage);

	Image sandImage;
	sandImage.loadFromFile("Images/sandPlanet.png");
	m_sandTexture.loadFromImage(sandImage);

	Image earthImage;
	earthImage.loadFromFile("Images/earth.png");
	m_earthTexture.loadFromImage(earthImage);
	//-------------------------
	//-----Настройка спрайтов-----
	m_space.setSize(Vector2f(600, 900));
	m_space.setFillColor(Color(9, 18, 31));
	m_space.setPosition(Vector2f(340, 0));
	m_alienPlanet.setTexture(m_alienTexture);
	m_alienPlanet.setColor(Color(104, 104, 104));
	m_sandPlanet.setTexture(m_sandTexture);
	m_sandPlanet.setColor(Color(104, 104, 104));
	m_earthPlanet.setTexture(m_earthTexture);
	m_earthPlanet.setColor(Color(104, 104, 104));
	//-------------------------
}

//сгенерировать планету
Map& Map::createPlanet()
{
	//выход, если планета уже есть
	if (isPlanet()) return *this;
	
	int posX = rand() % 890 + 340;
	int posY = 0;

	switch (rand() % 3) {
	case 0:
		m_alienPlanet.setPosition(posX, posY);
		m_planets.push_back(m_alienPlanet);
		break;
	case 1:
		m_sandPlanet.setPosition(posX, posY);
		m_planets.push_back(m_sandPlanet);
		break;
	case 2:
		m_earthPlanet.setPosition(posX, posY);
		m_planets.push_back(m_earthPlanet);
		break;
	}
	return *this;
}

//движение планеты
Map& Map::movePlanet()
{
	if (!isPlanet()) return *this;
	Vector2f currentPosition{ m_planets[0].getPosition() };
	if (currentPosition.y > 900) {
		m_planets.pop_back();
		return *this;
	}
	currentPosition.y++;
	m_planets[0].setPosition(currentPosition);
	return *this;
}

void Map::createStars(std::vector<CircleShape>& stars, const Color& color)
{
	int quantity = rand() % 2;
	int posX = rand() % 890 + 340;
	int posY = 0;
	for (int i = 0; i < quantity; ++i) {
		CircleShape star(3);
		star.setFillColor(color);
		star.setPosition(posX, posY);
		stars.push_back(star);
	}
}

//генерация звёзд переднего плана
Map& Map::createCloseStars()
{
	createStars(m_closeStars, Color(216, 220, 192));
	return *this;
}

//генерация звёзд заднего плана
Map& Map::createFarStars()
{
	createStars(m_farStars, Color(169, 178, 112));
	return *this;
}

//движение звёзд
Map& Map::moveStars(float time)
{
	Vector2f bufPos;

	for (int i = 0; i < m_closeStars.size(); ++i) {
		bufPos = m_closeStars[i].getPosition();
		bufPos.y += 0.1 * time;
		if (bufPos.y > 880) {
			m_closeStars.erase(m_closeStars.begin() + i);
			continue;
		}
		m_closeStars[i].setPosition(bufPos);
	}
	
	for (int i = 0; i < m_farStars.size(); ++i) {
		bufPos = m_farStars[i].getPosition();
		bufPos.y += 0.05 * time;
		if (bufPos.y > 880) {
			m_farStars.erase(m_farStars.begin() + i);
			continue;
		}
		m_farStars[i].setPosition(bufPos);
	}

	return *this;
}