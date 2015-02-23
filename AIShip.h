#pragma once
#include "visiblegameobject.h"

class AIShip: public VisibleGameObject
{
public:
	AIShip();
	~AIShip();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

	float GetVelocity() const;

private:
	float _velocity; //-- list ++ right
	float _maxVelocity;
	float _angle; //0 is up

};