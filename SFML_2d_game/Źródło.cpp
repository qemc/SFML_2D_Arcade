#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Plane.h"
#include "Sidebar.h"
#include <cstdlib>
#include "Plane.h"
#include <vector>




using namespace std;
using namespace sf;


int main() {
	//                 (DEKLARACJE OBIEKTÓW KLAS):
	RenderWindow window(VideoMode(900, 700), "The Battle Of England");
	window.setFramerateLimit(60);
	Event event;

	Font end_font;
	Text end_text;
	
	end_font.loadFromFile("font/ff.ttf");
	end_text.setFont(end_font);
	end_text.setCharacterSize(30);
	end_text.setPosition(30, 30);




	Texture texture_bg;
	texture_bg.loadFromFile("images/background.png");
	Sprite background;
	background.setTexture(texture_bg);

	Texture plane_texture;
	Texture plane_right_texture;
	Texture plane_left_texture;
	Texture enemy;
	Texture boss;


	plane_texture.loadFromFile("images/plane.png");
	plane_right_texture.loadFromFile("images/plane-r.png");
	plane_left_texture.loadFromFile("images/plane-l.png");
	enemy.loadFromFile("images/enemy.png");
	boss.loadFromFile("images/boss.png");


	Plane plane(plane_texture, plane_right_texture, plane_left_texture,enemy, boss);
	Sidebar sidebar;


	srand(time(NULL));
	bool game = true;
	

		//pêtla odpowiadaj¹ca za wyœwitlania okna
	while (window.isOpen()) {
	
	

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
		}

		while (game == true) {


			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
					break;
				}
			}


			window.clear();
			window.draw(background);
			plane.control();
			plane.shoot(window);
			plane.spawn_enemy(window);
			plane.bullet_coll();
			plane.update(window);
			plane.call_boss(window);
			sidebar.update(plane);
			window.draw(sidebar);
			window.draw(plane);


			if (plane.player_hp <= 0) {
				end_text.setString("YOU LOST \n \n  PRESS SPACE TO RETRY");
				game = false;
			}
			else if (plane.boss_hp <= 0) {
				end_text.setString("YOU WON \n \n  PRESS SPACE TO RETRY");
				game = false;
			}

			window.display();


		}
		window.clear();
		window.draw(end_text);
		window.display();


		if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {

			plane.enemy_lvl = 1;
			plane.player_points = 0;
			plane.player_hp = 5;
			plane.boss_hp = 10;
			plane.enemy_boss = false;
			plane.enemy_spawn_lvl = 2;
			plane.clock_boss.restart();

			game = true;

		}
	}
		return 0;
	}
