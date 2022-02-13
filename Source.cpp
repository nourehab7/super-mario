#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int main() {
	
	RenderWindow window(VideoMode(1000, 1000), "Super Mario");
	
			Texture marioTexture;
			marioTexture.loadFromFile("images/mario_spritesheet.png");
			Sprite mario(marioTexture);
			mario.setPosition(16, 740);
			mario.setScale(5, 5);

			int animationIndicator = 0,coin_animationIndicator = 0, score = 0;

			
			mario.setTextureRect(IntRect(0,0,16,32));
			bool isCoinVisible = true;
			bool canJump = false;
			
			Texture skyTexture;
			skyTexture.loadFromFile("images/sky2.jpg");
			Sprite sky(skyTexture);
			sky.setScale(4, 4);
			
			Texture groundtexture;
			groundtexture.loadFromFile("images/bricks2.png");
			Sprite ground(groundtexture);
			ground.setPosition(0, 900);
			

			/*Texture groundTexture;
			groundTexture.loadFromFile("images/bricks2.png");
			const int groundSize = 100;
			Sprite ground[groundSize];
			for (int i = 0; i < groundSize; i++) {
				ground[i].setPosition(ground[i].getGlobalBounds().width * i, 1000 - ground[i].getGlobalBounds().height);
					
			}*/
			Texture coinTexture;
			coinTexture.loadFromFile("images/coins2.png");
			Sprite coin(coinTexture);
			coin.setPosition(200, 865);
			coin.setTextureRect(IntRect(0, 0, 35, 32));

			Clock clock, animation_clock, coin_animation_clock;
			float deltaTime = 0;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				mario.move(Vector2f(3*deltaTime, 0));
				if (animation_clock.getElapsedTime().asSeconds() > 0.1) {
				animationIndicator++;
				animation_clock.restart();
				}
				mario.setScale(5, 5);
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Left)) {

				mario.move(Vector2f(-3*deltaTime, 0));
				if (animation_clock.getElapsedTime().asSeconds() > 0.1) {
					animationIndicator++;
					animation_clock.restart();
				}
				
				mario.setScale(-5, 5);
			}
			if (Keyboard::isKeyPressed(Keyboard::Space) && canJump) {
				mario.move(Vector2f(0, -200));
				canJump = false;
			}
			if (!mario.getGlobalBounds().intersects(ground.getGlobalBounds())) {
				mario.move(Vector2f(0,0.1));
			}
			else {
				canJump = true;
			}
			
		animationIndicator = animationIndicator % 3;
		mario.setTextureRect(IntRect(animationIndicator * 16, 0, 16, 32));
	    coin.setTextureRect(IntRect(coin_animationIndicator * 35, 0, 35, 32));
		if (mario.getGlobalBounds().intersects(coin.getGlobalBounds())) {
			isCoinVisible = false;
			score ++;
		}
		/*if (Keyboard::isKeyPressed(Keyboard::S)) {
			cout << "Your score is: " << score << endl;
		}*/
		if (coin_animation_clock.getElapsedTime().asSeconds() > 0.125) {
	    coin_animationIndicator++;
		coin_animation_clock.restart();
	    coin_animationIndicator = coin_animationIndicator % 6;
		}
	    window.clear();
		window.draw(sky);
		window.draw(mario);
		//for (int i = 0; i < groundSize; i++) {
		window.draw(ground);

		//}
		if (isCoinVisible) {
		window.draw(coin);
		}
		window.display();
		deltaTime = clock.restart().asSeconds()*100;
		
		
	}
	return 0;
}