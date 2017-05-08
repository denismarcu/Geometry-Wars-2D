#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

/* Functie pentru setarea proprietatilor unui inamic */
void Enemy::settingProperties(float height) {

	/* Setam pozitia random a inamicului de pe cercul cu centru
	in mijlocul ecranului. (ecranul este patrat) */

	float positionX =  (float)(rand() % (int)(height + 1));
	float positionY;
	float expr;
	float radical;
	int semn = rand() % 2;	// coordonata y este deasupra / dedesubptul axei OX

	if (positionX == 0 || positionX == height) {
		positionY = height / 2; 
	}
	else if (positionX == height / 2) {
		positionY = (float) semn * height;
	}
	else {
		/* Ecuatie cerc cu centrul in C(a,b): (x - a)^2  + (y - b)^2 = r^2 
		 r = height / 2 -> inamicii vor aparea la marginea ecranului */

		expr = (float)(positionX - height / 2) * (positionX - height / 2);
		radical = (float)sqrt(height * height / 4 - expr);
		positionY = (float) radical + height / 2;

		/* Coordonata y este dedesubtul axei OX */
		if (semn == 0) {
			positionY = height - positionY;
		}
	}
	
	/* Setam pozitiile inamicului */
	this->setPosition(glm::vec2(positionX, positionY));

	/* Setam viteza random intre 0.5 si 2 => daca se dubleaza ajunge la 4 < viteza navei */

	int viteza = rand() % 151 + 50;
	this->speed = (float)viteza / 100;

	/* Scala, unghiul si tipul inamicului */
	scale = glm::vec2(30, 30);
	radius = 30.0f;
	type = rand() % 2 + 1;
}


/* Animatie pentru scalare - calculeaza noua scalare in functie de timp,
ajungand la timeMinimizing = 0.25s cu scalarea la jumatate */
void Enemy::setNewScale(float deltaTimeSeconds) {
	time += deltaTimeSeconds;
	if (time > timeMinimizing - 0.001f) {
			time = timeMinimizing;
			minimizing = false;
		}
	// functie de gradul I: f(time) = a - 2a * time, a = scala inamicului
	float aux = scale.x - 2 * scale.x * time;

	relativeScale = glm::vec2(aux, aux);
	radius = aux;
}
