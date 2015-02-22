#pragma once
#include "visiblegameobject.h"

class PlayerPaddle: public VisibleGameObject
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);

	float GetVelocity() const;

private:
	float _velocity; //-- list ++ right
	float _maxVelocity;

};