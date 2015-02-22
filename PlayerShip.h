#pragma once
#include "visiblegameobject.h"

class PlayerShip: public VisibleGameObject
{
public:
	PlayerShip();
	~PlayerShip();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

	float GetVelocity() const;

private:
	float _velocity; //-- list ++ right
	float _maxVelocity;
	float _angle; //90 is up

};