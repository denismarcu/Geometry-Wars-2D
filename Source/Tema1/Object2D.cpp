#include "Object2D.h"

Object2D::Object2D()
{
}

Object2D::~Object2D()
{
}

/* Setarea pozitiei pe ecran */
void Object2D::setPosition(glm::vec2 position) {
	this->position = position;
}

/* Setarea scalii obiectului */
void Object2D::setScale(glm::vec2 scale) {
	this->scale = scale;
}

/* Setarea vectorului de viteza al obiectului */
void  Object2D::setVelocity(glm::vec2 velocity) {
	this->velocity = velocity;
}

/* Setarea unghiului de rotatie */
void Object2D::setAngle(glm::vec2 point) {
	this->angle = (float)(atan2(-point.x + this->position.x, point.y - this->position.y));
}

/* Setarea razei obiectului */
void Object2D::setRadius(float radius) {
	this->radius = radius;
}

/* Setarea vitezei obiectului */
void Object2D::setSpeed(float speed) {
	this->speed = speed;
}

/* Aflarea vectorului de viteza - obiectul se deplaseaza spre punctul de reper
cu ajutorul acestui vector: position = position + velocity. Avand viteza de deplasare,
vom calcula noua pozitie a obiectului in functie de cadranul in care se afla punctul de
reper in sistemul de axe asociat obiectului. */
void Object2D::setVelocityVector(glm::vec2 point) {
	float xA;
	float yA;
	bool withX = false;

	/* Aflam panta dreptei dintre obiect si punctul de reper */
	float panta = (float)((point.y - this->position.y) / (point.x - this->position.x));

	float differenceX = (float)this->position.x - point.x;
	float differenceY = (float)(this->position.y - point.y);
	float eps = 0.001f;

	/* Diferenta dintre x-uri = 0, deci ne vom deplasa in sus sau jos
	pe OY in functie de unde se afla punctul de reper */
	if ((-eps <= differenceX) && (differenceX <= eps)) {
		xA = 0;
		if (point.y >= this->position.y) {
			yA = this->speed;
		}
		else {
			yA = -this->speed;
		}

	}
	/* Diferenta dintre y-uri = 0, deci ne vom deplasa in dreapta sau
	standa pe OX in functie de unde se afla punctul de reper */
	else if ((-eps <= differenceY) && (differenceY <= eps)) {
		if (point.x >= this->position.x) {
			xA = this->speed;
		}
		else {
			xA = -this->speed;
		}
		yA = 0;
	}
	/* Punctul de reper este intr-unul dintre cadrane */
	else {
		/* Cadranul 1 */
		if (point.x > this->position.x && point.y > this->position.y) {

			/* Cu y-ul punctului de reper sub diagonala principala */
			if (point.y < point.x - this->position.x + this->position.y) {
				xA = this->position.x + this->speed;
				withX = true;
			}
			else {
				yA = this->position.y + this->speed;
				withX = false;
			}

		}
		/* Cadranul 4 */
		else if (point.x > this->position.x && point.y < this->position.y) {

			/* Cu y-ul punctului de reper deasupra diagonalei secundare */
			if (point.y > this->position.y - (point.x - this->position.x)) {
				xA = this->position.x + this->speed;
				withX = true;
			}
			else {
				yA = this->position.y - this->speed;
				withX = false;
			}

		}
		/* Cadranul 2 */
		else if (point.x < this->position.x && point.y > this->position.y) {

			/* Cu y-ul punctului de reper sub diagonala secundara */
			if (point.y < (this->position.x - point.x) + this->position.y) {
				xA = this->position.x - this->speed;
				withX = true;
			}
			else {
				yA = this->position.y + this->speed;
				withX = false;
			}

		}
		/* Cadranul 3 */
		else if (point.x < this->position.x && point.y < this->position.y) {
			/* Cu y-ul punctului de reper deasupra diagonalei principale */
			if (point.y >  this->position.y - (this->position.x - point.x)) {
				xA = this->position.x - this->speed;
				withX = true;
			}
			else {
				yA = this->position.y - this->speed;
				withX = false;
			}

		}

		/* Folosind ecuatia dreptei care trece printr-un punct aflam x sau y */
		if (withX == true) {
			yA = (float)(point.y - panta * (point.x - xA));
		}
		else {
			xA = (float)(point.x - (point.y - yA) / panta);
		}

		/* Obtinem vectorul de viteza pentru deplasarea obiectului
		catre punctul de reper, avand o anumita viteza */
		xA -= this->position.x;
		yA -= this->position.y;
	}

	velocity = glm::vec2(xA, yA);
}

/* Verificam daca 2 obiecte se intersecteaza.
(cercurile asociate obiectelor se intersecteaza) */
bool Object2D::interact(Object2D object) {
	
	/* Suma razelor */
	float sum = this->radius + object.radius;		
	
	/* AB^2 = (x2 -x1)^2 + (y2-y1)^2 */
	float expr = (this->position.x - object.position.x) *  (this->position.x - object.position.x);
	expr += (this->position.y - object.position.y) *  (this->position.y - object.position.y);

	float AB = (float)sqrt(expr);

	if (sum < AB) {
		return 0;
	}
	return 1;
}
