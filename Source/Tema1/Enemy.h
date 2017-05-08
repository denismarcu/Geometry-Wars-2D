#pragma once

#include <Tema1/Object2D.h>
#include <Tema1/Bullet.h>
#include <vector>
#include <stdlib.h> //random



class Enemy : public Object2D {

  public:

	int type;					/* tipul de inamic */ 
	glm::vec2 relativeScale;	/* noua scalare atunci cand inamicul pierde o viata */
	bool minimizing = false;
	float timeMinimizing = 0.25f;

	Enemy();
	~Enemy();

	void settingProperties(float height);
	void setNewScale(float deltaTimeSeconds);

};
