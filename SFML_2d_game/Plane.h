#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

using namespace std;
using namespace sf;



class Plane : public Sprite {
private:

	Texture left;
	Texture right;
	Texture plane;
	Texture enemy;
	vector<CircleShape> bullets;
	vector<CircleShape> b_bullets;
	vector<Sprite> enemies;
	Clock boss_s;
	Clock shoot_c;
	Clock enemy_c;
	Vector2f velocity;
	Vector2f enemy_velocity;
	Texture boss;
	Sprite s_boss;
public:
	Plane(const Texture& texture, const Texture& right, const Texture& left, const Texture &enemy, const Texture& boss);

	int enemy_lvl = 1;
	int player_points=0;
	int player_hp = 5;
	int boss_hp = 10;
	bool enemy_boss = false;
	float enemy_spawn_lvl = 2;
	Clock clock_boss;

	RectangleShape hp_vis;


	void control();
	void shoot(RenderWindow& window);
	void spawn_enemy(RenderWindow& window);
	void bullet_coll();
	void update(RenderWindow& window);
	void call_boss(RenderWindow& window);
	void shoot_b(RenderWindow& window);
	void b_bullet_coll();

};

