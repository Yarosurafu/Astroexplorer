#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "spaceship.h"

using namespace sf;
using namespace std;

//class SpaceShip {
//	const unsigned short SPRITE_SIZE_X = 49;
//	const unsigned short SPRITE_SIZE_Y = 46;
//	const unsigned short FIRE_SIZE_X = 12;
//	const unsigned short FIRE_SIZE_Y = 41;
//	Sprite shipSprite;
//	Sprite firstFire;
//	Sprite secondFire;
//
//public:
//	SpaceShip(Texture& textureArg, Texture& fireTexture) {
//		shipSprite.setTexture(textureArg);
//		shipSprite.setTextureRect(IntRect(345, 47, SPRITE_SIZE_X, SPRITE_SIZE_Y));//������ ������� �� ���� - 49, �� ������ - 48
//		shipSprite.setPosition(300, 450);
//		shipSprite.setColor(Color::Yellow);
//		firstFire.setTexture(fireTexture);
//		firstFire.setTextureRect(IntRect(30, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//		firstFire.setRotation(180);
//		secondFire.setTexture(fireTexture);
//		secondFire.setTextureRect(IntRect(30, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//		secondFire.setRotation(180);
//	}
//
//	void setFireSprite() {
//		Vector2f buf;
//		buf = shipSprite.getPosition();
//		buf.x += 23;
//		buf.y += 82;
//		firstFire.setPosition(buf);
//		buf = shipSprite.getPosition();
//		buf.x += 38;
//		buf.y += 82;
//		secondFire.setPosition(buf);
//	}
//
//	void changeFireSprite(int frame) {
//		switch (frame) {
//		case 50:
//			firstFire.setTextureRect(IntRect(30, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//			secondFire.setTextureRect(IntRect(30, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//			break;
//		case 100:
//			firstFire.setTextureRect(IntRect(47, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//			secondFire.setTextureRect(IntRect(64, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//			break;
//		case 150:
//			firstFire.setTextureRect(IntRect(64, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//			secondFire.setTextureRect(IntRect(47, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//			break;
//		case 200:
//			firstFire.setTextureRect(IntRect(83, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//			secondFire.setTextureRect(IntRect(83, 24, FIRE_SIZE_X, FIRE_SIZE_Y));
//			break;
//		}
//	}
//
//	void moveShip(int arg, float time) {
//		Vector2f buf;
//		buf = shipSprite.getPosition();
//		switch (arg) {
//		case 1:
//			if (buf.x >= 0)
//				shipSprite.move(-0.1 * time, 0);
//			break;
//		case 2:
//			if (buf.x <= 551)
//				shipSprite.move(0.1 * time, 0);
//			break;
//		case 3:
//			if (buf.y >= 0)
//				shipSprite.move(0, -0.1 * time);
//			break;
//		case 4:
//			if (buf.y <= 854)
//				shipSprite.move(0, 0.1 * time);
//			break;
//		}
//	}
//
//	Sprite getSprite() {
//		return shipSprite;
//	}
//
//	Sprite getFirstFire() {
//		return firstFire;
//	}
//
//	Sprite getSecondFire() {
//		return secondFire;
//	}
//};

class Map {
	RectangleShape space;//������
	vector<CircleShape> closeStars;//������� � ������������
	vector<CircleShape> farStars;//������� ������
	Sprite alienPlanet;
	Sprite sandPlanet;
	Sprite earthPlanet;
	vector<Sprite> planets;

public:
	Map(Texture& alien, Texture& sand, Texture& earth) {
		Vector2f sizeArg(600, 900);//������ �������������� "�������"
		Color col(9, 18, 31);//���� �������
		space.setSize(sizeArg);//������ ������ ��������������
		space.setFillColor(col);//������ ���� ��������������
		alienPlanet.setTexture(alien);
		alienPlanet.setColor(Color(104, 104, 104));
		sandPlanet.setTexture(sand);
		sandPlanet.setColor(Color(104, 104, 104));
		earthPlanet.setTexture(earth);
		earthPlanet.setColor(Color(104, 104, 104));
	}

	void createPlanet() {
		int posX = rand() % 550;
		int posY = 0;
		if (planets.size() != 0)
			return;
		int planetType = rand() % 3;
		switch (planetType) {
		case 0:
			alienPlanet.setPosition(posX, posY);
			planets.push_back(alienPlanet);
			break;
		case 1:
			sandPlanet.setPosition(posX, posY);
			planets.push_back(sandPlanet);
			break;
		case 2:
			earthPlanet.setPosition(posX, posY);
			planets.push_back(earthPlanet);
			break;
		}
	}

	void movePlanet() {
		if (planets.size() == 0) return;
		Vector2f buf;
		buf = planets[0].getPosition();
		if (buf.y > 900) {
			planets.pop_back();
			return;
		}
		buf.y++;
		planets[0].setPosition(buf);
	}

	bool isPlanet() {
		return (planets.size() != 0);
	}

	Sprite getPlanet() {
		return planets[0];
	}

	void createCloseStars() {//��������� ������� �����
		int quantity = rand() % 2;//���������� ������������ �����
		Color colClose(216, 220, 192);
		int posX = rand() % 600;
		int posY = 0;
		for (int i = 0; i < quantity; ++i) {
			CircleShape star(3);
			star.setFillColor(colClose);
			star.setPosition(posX, posY);
			closeStars.push_back(star);
		}
	}

	void createFarStars() {//��������� ������� �����
		int quantity = rand() % 2;//���������� ������������ �����
		Color colFar(169, 178, 112);
		int posX = rand() % 600;
		int posY = 0;
		for (int i = 0; i < quantity; ++i) {
			CircleShape star(2);
			star.setFillColor(colFar);
			star.setPosition(posX, posY);
			farStars.push_back(star);
		}
	}

	void moveStars(float time) {//�������� �����
		Vector2f bufPos;
		//������� ������
		for (int i = 0; i < closeStars.size(); ++i) {
			bufPos = closeStars[i].getPosition();
			bufPos.y += 0.1 * time;
			if (bufPos.y > 880) {
				closeStars.erase(closeStars.begin() + i);
				continue;
			}
			closeStars[i].setPosition(bufPos);
		}
		//������� ������
		for (int i = 0; i < farStars.size(); ++i) {
			bufPos = farStars[i].getPosition();
			bufPos.y += 0.05 * time;
			if (bufPos.y > 880) {
				farStars.erase(farStars.begin() + i);
				continue;
			}
			farStars[i].setPosition(bufPos);
		}
	}

	RectangleShape getSpace() {//������� "�������" ��� ���������
		return space;
	}

	vector<CircleShape> getCloseStars() {
		return closeStars;
	}

	vector<CircleShape> getFarStars() {
		return farStars;
	}
};

class Asteroids {
	Sprite asteroid;
	vector<Sprite> asteroids;

public:
	Asteroids(Texture& astTexture) {
		asteroid.setTexture(astTexture);
		asteroid.setTextureRect(IntRect(98, 130, 26, 29));
	}

	void createAsteroids() {
		int posX = rand() % 600;
		Sprite buf;
		buf.setTexture(*asteroid.getTexture());
		buf.setTextureRect(asteroid.getTextureRect());
		buf.setPosition(posX, 0);
		asteroids.push_back(buf);
	}

	void moveAsteroids(float time) {
		Vector2f buf;
		for (int i = 0; i < asteroids.size(); ++i) {
			buf = asteroids[i].getPosition();
			buf.y += 0.05 * time;
			if (buf.y > 900) {
				asteroids.erase(asteroids.begin() + i);
				continue;
			}
			asteroids[i].setPosition(buf);
		}
	}

	void deleteAsteroids() {
		for (int i = asteroids.size() - 1; i >= 0; --i)
			asteroids.erase(asteroids.begin() + i);
	}

	vector<Sprite> getAsteroids() {
		return asteroids;
	}
};

class MainTheme {
	Music theme;
public:
	MainTheme() {
		theme.openFromFile("Sound/space oddity.ogg");
		theme.setLoop(true);
	}

	virtual void musicOn() {
		theme.play();
	}

	virtual void musicOff() {
		theme.stop();
	}
};

class GameSound : public MainTheme {
	Music engines;
public:
	GameSound() {
		engines.openFromFile("Sound/engines.ogg");
		engines.setLoop(true);
		engines.setVolume(30);
	}

	void musicOn() {
		engines.play();
	}

	void musicOff() {
		engines.stop();
	}
};

class GameOverSound : public GameSound {
	Music gameOver;
public:
	GameOverSound() {
		gameOver.openFromFile("Sound/GameOver.ogg");
	}

	void musicOn() {
		gameOver.play();
	}
};

int main(int argc, char** argv) {
	srand(time(NULL));
	Clock clock;

	SpaceShip ship;

	
	Image alienImage;
	alienImage.loadFromFile("Images/alienPlanet.png");
	Texture alienTexture;
	alienTexture.loadFromImage(alienImage);

	Image sandImage;
	sandImage.loadFromFile("Images/sandPlanet.png");
	Texture sandTexture;
	sandTexture.loadFromImage(sandImage);

	Image earthImage;
	earthImage.loadFromFile("Images/earth.png");
	Texture earthTexture;
	earthTexture.loadFromImage(earthImage);

	Map space(alienTexture, sandTexture, earthTexture);
	vector<CircleShape> displayCloseStars;
	vector<CircleShape> displayFarStars;
	float spawnTime = 0;
	float spawnTimeAst = 0;
	int frame = 50;

	Image astImg;
	astImg.loadFromFile("Images/effects.png");
	Texture astText;
	astText.loadFromImage(astImg);
	astImg.~Image();
	Asteroids asteroids(astText);
	vector<Sprite> displayAst;

	Font font;
	font.loadFromFile("Fonts/xenosphere.ttf");

	RenderWindow window(VideoMode(600, 900), "Astroexplorer");
	window.setFramerateLimit(120);
	int windowState = 1;

	MainTheme main;
	GameSound gameSound;
	GameOverSound gameOverSound;
	main.musicOn();
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		if (windowState == 1) {
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				windowState = 2;
				main.musicOff();
				gameSound.musicOn();
			}
			Sprite background;
			Image arg;
			arg.loadFromFile("Images/main.png");
			Texture texture;
			texture.loadFromImage(arg);
			background.setTexture(texture);
			Text str;
			str.setString("ASTROEXPLORER");
			str.setFont(font);
			str.setFillColor(Color::White);
			str.setCharacterSize(55);
			str.setPosition(20, 20);
			Text play;
			play.setString("Press ENTER to start");
			play.setFont(font);
			play.setFillColor(Color::Red);
			play.setCharacterSize(30);
			play.setPosition(90, 450);
			Text author;
			author.setString("Created by Svirin Yaroslav, SP-226");
			author.setFont(font);
			author.setFillColor(Color::White);
			author.setCharacterSize(20);
			author.setPosition(80, 800);
			window.clear();
			window.draw(background);
			window.draw(str);
			window.draw(play);
			window.draw(author);
			window.display();
		}
		else if (windowState == 2) {
			float time = clock.getElapsedTime().asMicroseconds();
			time /= 400;
			spawnTime += time;
			spawnTimeAst += time;
			frame++;
			if (frame > 200) frame = 50;
			clock.restart();
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				ship.moveShip(1, time);
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				ship.moveShip(2, time);
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				ship.moveShip(3, time);
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				ship.moveShip(4, time);
			}
			ship.changeFireSprite(frame);

			if (spawnTime > 300)
				space.createCloseStars();
			displayCloseStars = space.getCloseStars();
			if (spawnTime > 400) {
				space.createFarStars();
				spawnTime = 0;
			}
			displayFarStars = space.getFarStars();
			if (spawnTimeAst > 500) {
				asteroids.createAsteroids();
				spawnTimeAst = 0;
			}

			displayAst = asteroids.getAsteroids();
			//��������� �������
			space.createPlanet();
			window.clear();
			window.draw(space.getSpace());//��������� �������
			if (space.isPlanet()) window.draw(space.getPlanet());
			for (int i = 0; i < displayCloseStars.size(); ++i)
				window.draw(displayCloseStars[i]);
			for (int i = 0; i < displayFarStars.size(); ++i)
				window.draw(displayFarStars[i]);
			for (int i = 0; i < displayAst.size(); ++i)
				window.draw(displayAst[i]);
			window.draw(ship.getSprite());//��������� �������
			window.draw(ship.getFirstFireSprite());
			window.draw(ship.getSecondFireSprite());
			window.display();
			for (int i = 0; i < displayAst.size(); ++i) {
				if (displayAst[i].getGlobalBounds().intersects(ship.getSprite().getGlobalBounds())) {
					asteroids.deleteAsteroids();
					windowState = 3;
					gameSound.musicOff();
					gameOverSound.musicOn();
					break;
				}

			}
			space.moveStars(time);//����� ��������� �����
			space.movePlanet();
			asteroids.moveAsteroids(time);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				gameSound.musicOn();
				windowState = 2;
			}
			Text text;
			text.setString("GAME OVER");
			text.setFillColor(Color::Red);
			text.setFont(font);
			text.setCharacterSize(50);
			text.setPosition(120, 300);
			Text again;
			again.setString("Press ENTER to try again");
			again.setFillColor(Color::Red);
			again.setFont(font);
			again.setCharacterSize(20);
			again.setPosition(130, 400);
			Text close;
			close.setString("Press ESC to exit");
			close.setFillColor(Color::Red);
			close.setCharacterSize(20);
			close.setFont(font);
			close.setPosition(180, 450);
			window.clear();
			window.draw(text);
			window.draw(again);
			window.draw(close);
			window.display();
		}
	}
	return 0;
}
