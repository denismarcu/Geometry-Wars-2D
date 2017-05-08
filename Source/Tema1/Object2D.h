#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>
#include <string>
#include <math.h> // atan


class Object2D : public SimpleScene
{
public:
	
	glm::vec2 position;
	glm::vec2 scale;
	glm::vec2 velocity;

	float angle = 0.0;
	float radius;
	float speed;
	float time = 0.0f;

	Object2D();
	~Object2D();

	
	void setPosition(glm::vec2 position);
	void setScale (glm::vec2 scale);
	void setVelocity(glm::vec2 velocity);

	
	void setAngle(glm::vec2 point);
	void setRadius(float radius);
	void setSpeed(float speed);

	void setVelocityVector(glm::vec2 point);
	bool interact(Object2D object);

};

