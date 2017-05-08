#pragma once

#include <Tema1/Object2D.h>

/* Clasa bonus - obiecte bonus (viata sau scut) pentru player */
class Bonus : public Object2D {

  public:
	bool active = false;
	bool life = false;
	bool shield = false;

	Bonus();
	~Bonus();

};
