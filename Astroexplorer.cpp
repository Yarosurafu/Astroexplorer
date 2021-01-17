#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "spaceship.h"
#include "map.h"
#include "asteroids.h"

using namespace sf;
using namespace std;

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
	Map space;
	vector<CircleShape> displayCloseStars;
	vector<CircleShape> displayFarStars;
	float spawnTime = 0;
	float spawnTimeAst = 0;
	int frame = 50;
	int score{};
	int highScore{};

	Asteroids asteroids;
	vector<Sprite> displayAst;

	Font font;
	font.loadFromFile("Fonts/xenosphere.ttf");

	RenderWindow window(VideoMode(600, 900), "Astroexplorer");
	RenderWindow gameWindow(VideoMode(1280, 900), "Astroexplorer");
	//Загрузка текстуры карбона
	Image carbonImage;
	if (!carbonImage.loadFromFile("Images/carbon.png")) {
		carbonImage.create(340, 900);
	}
	Texture carbonTexture;
	carbonTexture.loadFromImage(carbonImage);
	Sprite carbon;
	carbon.setTexture(carbonTexture);
	carbon.setPosition(Vector2f(0, 0));

	Image rightPanelImage;
	if (!rightPanelImage.loadFromFile("Images/right_panel.png")) {
		rightPanelImage.create(340, 900);
	}
	Texture rightPanelTexture;
	rightPanelTexture.loadFromImage(rightPanelImage);
	Sprite carbon2;
	carbon2.setTexture(rightPanelTexture);
	carbon2.setPosition(Vector2f(940, 0));
	gameWindow.setVisible(false);

	window.setFramerateLimit(120);
	int windowState = 1;

	MainTheme main;
	GameSound gameSound;
	GameOverSound gameOverSound;
	main.musicOn();
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				gameWindow.close();
			}
		}
		while (gameWindow.pollEvent(event)) {
			if(event.type == Event::Closed) {
				window.close();
				gameWindow.close();
			}
		}
		//Главное меню
		if (windowState == 1) {
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				window.setVisible(false);
				windowState = 2;
				main.musicOff();
				gameSound.musicOn();
				gameWindow.setVisible(true);
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
			author.setString("Created by Svirin Yaroslav");
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
			if (frame > 200) { 
				frame = 50; 
				++score;
			}
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
			
			space.createPlanet();
			gameWindow.clear();
			gameWindow.draw(space.getSpace());
			if (space.isPlanet()) gameWindow.draw(space.getPlanet());
			for (int i = 0; i < displayCloseStars.size(); ++i)
				gameWindow.draw(displayCloseStars[i]);
			for (int i = 0; i < displayFarStars.size(); ++i)
				gameWindow.draw(displayFarStars[i]);
			for (int i = 0; i < displayAst.size(); ++i)
				gameWindow.draw(displayAst[i]);
			gameWindow.draw(ship.getSprite());
			gameWindow.draw(ship.getFirstFireSprite());
			gameWindow.draw(ship.getSecondFireSprite());
			gameWindow.draw(carbon);
			gameWindow.draw(carbon2);

			Text highScoreText;
			highScoreText.setString("High score:\n" + std::to_string(highScore));
			highScoreText.setFillColor(Color::Red);
			highScoreText.setFont(font);
			highScoreText.setCharacterSize(30);
			highScoreText.setPosition(978, 245);

			Text scoreText;
			scoreText.setString("Score:\n" + std::to_string(score));
			scoreText.setFillColor(Color::Red);
			scoreText.setFont(font);
			scoreText.setCharacterSize(30);
			scoreText.setPosition(978, 400);
			gameWindow.draw(highScoreText);
			gameWindow.draw(scoreText);

			gameWindow.display();
			for (int i = 0; i < displayAst.size(); ++i) {
				if (displayAst[i].getGlobalBounds().intersects(ship.getSprite().getGlobalBounds())) {
					if (score > highScore) highScore = score;
					score = 0;
					asteroids.deleteAsteroids();
					windowState = 3;
					gameSound.musicOff();
					gameOverSound.musicOn();
					gameWindow.setVisible(false);
					ship.setSpawn();
					window.setVisible(true);
					break;
				}
			}
			space.moveStars(time);
			space.movePlanet();
			asteroids.moveAsteroids(time);
		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
				gameWindow.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				window.setVisible(false);
				gameWindow.setVisible(true);
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
