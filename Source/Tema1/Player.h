#pragma once

#include <Tema1/Object2D.h>
#include <Tema1/Bullet.h>
#include <vector>

class Player : public Object2D {

  public:

	vector<Bullet> Bullets;
	int lives;
	bool shield = false;
	float timeShield = 0.0f;

	/* Campuri folosite de boss */
	int sign = 1;		// se deplaseaza in stanga sau dreapta
	float shoot = 1.0f;		// viteza de tragere 
	int type;
	
	Player();
	~Player();

};
