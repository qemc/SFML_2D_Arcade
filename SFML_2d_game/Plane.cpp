#include "Plane.h"



Plane::Plane(const Texture& texture, const Texture& right_, const Texture& left_, const Texture& enemy_, const Texture& boss_) {

	setTexture(texture);
	setPosition(350, 630);
	
	hp_vis.setFillColor(Color::Green);
	hp_vis.setSize(Vector2f(180,500));
	hp_vis.setPosition(710, 690);
	hp_vis.setOrigin(0, 500);

	s_boss.setTexture(boss_);
	s_boss.setPosition(350+64, 100+128);
	s_boss.setRotation(180);


	velocity.x = 3;
	velocity.y = 0;


	plane = texture;
	left = left_;
	right = right_;
	enemy = enemy_;
	//boss = boss_;
}

void Plane::control() {

	Vector2f velocity;

//	cout << enemy_boss << endl;
	//funkcja sterowania/poruszanie siê samolotu

	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		velocity.x = -5;
		velocity.y = 0;

		setTexture(left);
	}
	else
	if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		velocity.x = 5;
		velocity.y = 0;

		setTexture(right);
	}
	else {
		velocity.x = 0;
		velocity.y = 0;
		setTexture(plane);

	}


	//ograniczenie poruszania sie samolotu

	if (this->getPosition().x < 0) {
		this->setPosition( 0, this->getPosition().y);

		velocity.x = 0;
		velocity.y = 0;

	}

	if (this->getPosition().x + this->getGlobalBounds().width > 700) {
		this->setPosition(700- this->getGlobalBounds().width, this->getPosition().y);

		velocity.x = 0;
		velocity.y = 0;
	}


	this->move(velocity);
}

void Plane::shoot(RenderWindow &window) {

	if (Keyboard::isKeyPressed(Keyboard::Key::W) && shoot_c.getElapsedTime().asSeconds()>0.25f) {
	
	
		CircleShape bullet(5);
		bullet.setOrigin(5, 5);
		bullet.setPosition(this->getPosition().x + 32, 670);
		bullets.emplace_back(bullet);
		shoot_c.restart();

	}

	for (int i = 0; i < bullets.size(); i++) {

		bullets[i].move(0, -8);
		window.draw(bullets[i]);

	}

	for (auto itr = bullets.begin(); itr != bullets.end();) {
		if (itr->getPosition().y < 0) {

			itr = bullets.erase(itr);
			cout << bullets.size() << endl;

		}
		else {
			itr++;
		}
	}
}

void Plane::spawn_enemy(RenderWindow& window) {



	if (enemy_c.getElapsedTime().asSeconds() > enemy_spawn_lvl && enemy_boss == false) {

		Sprite enemy_plane;
		enemy_plane.setRotation(180);
		enemy_plane.setTexture(enemy);
		enemy_plane.setPosition(32 + rand() % 668, -40);

		enemies.emplace_back(enemy_plane);

		enemy_c.restart();

	}


	for (int i = 0; i < enemies.size(); i++) {

		if (enemy_boss == false) {
			enemies[i].move(0, 4);

			window.draw(enemies[i]);
		}
	}

	for (auto itr = enemies.begin(); itr != enemies.end();) {
		if (itr->getPosition().y > 750 || itr->getGlobalBounds().intersects(this->getGlobalBounds())) {

			itr = enemies.erase(itr);
			player_hp--;
			cout << enemies.size() << endl;

		}
		else {
			itr++;
		}
	}


}


void Plane::bullet_coll() {

	for (int t = 0; t <bullets.size(); t++) {

		for (int d = 0; d <enemies.size(); d++) {

			if (bullets[t].getGlobalBounds().intersects(enemies[d].getGlobalBounds())) {

				player_points++;

				bullets.erase(bullets.begin() + t);
				enemies.erase(enemies.begin() + d);
				break;

			}
		}
	}

}

void Plane::b_bullet_coll() {

	for (int t = 0; t < b_bullets.size(); t++) {

		if (b_bullets[t].getGlobalBounds().intersects(this->getGlobalBounds())) {
			player_hp-=3;

			b_bullets.erase(b_bullets.begin() + t);

			break;

		}
		
	}


	for (int t = 0; t < bullets.size(); t++) {

		if (bullets[t].getGlobalBounds().intersects(s_boss.getGlobalBounds())) {

			boss_hp--;

			bullets.erase(bullets.begin() + t);

			break;

		}

	}

}


void Plane::update(RenderWindow &window) {

	if (clock_boss.getElapsedTime().asSeconds() > 10 && enemy_spawn_lvl>1) {

		if (enemy_lvl == 2) {
			enemy_boss = true;
		
			
		}
		enemy_lvl++;
		enemy_spawn_lvl = enemy_spawn_lvl -0.5;

	
		clock_boss.restart();
	}

	hp_vis.setSize(Vector2f(180, (500 * player_hp) / 5));


	window.draw(hp_vis);

	hp_vis.setOrigin(0, (500 * player_hp) / 5);


	if (player_hp <= 0) {
		hp_vis.setScale(0, 0);
	}





}
void Plane::shoot_b(RenderWindow& window) {

	if (boss_s.getElapsedTime().asSeconds() > 1) {


		CircleShape bullet(10);
		bullet.setFillColor(Color::Red);
		bullet.setOutlineColor(Color::Blue);
		bullet.setOutlineThickness(2);
		bullet.setOrigin(5, 5);
		bullet.setPosition(s_boss.getPosition().x-64, 228);
		b_bullets.emplace_back(bullet);
		boss_s.restart();

	}

	for (int i = 0; i < b_bullets.size(); i++) {

		b_bullets[i].move(0, 12);
		window.draw(b_bullets[i]);

	}

	for (auto itr = bullets.begin(); itr != bullets.end();) {
		if (itr->getPosition().y < 0) {

			itr = bullets.erase(itr);
			cout << bullets.size() << endl;

		}
		else {
			itr++;
		}
	}
}


void Plane::call_boss(RenderWindow &window) {

	

	if (enemy_boss == true) {

		enemies.clear();

		if (s_boss.getPosition().x > 700) {
			velocity.x = -3;
		}
		if (s_boss.getPosition().x - s_boss.getGlobalBounds().width < 0) {
			velocity.x = 3;
		}
		
		b_bullet_coll();
		s_boss.move(velocity);
		shoot_b(window);


		window.draw(s_boss);


	}



}



