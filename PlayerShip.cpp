#include "stdafx.h"
#include "PlayerShip.h"
#include "game.h"
#include "Defines.h"

PlayerShip::PlayerShip() : 
_velocity(0),
_maxVelocity(600.0f),
_angle(0), //0 is up
_maxMoves(6),
_turningspeed(22.5)
{
	Load(player_ship_image);
	assert(IsLoaded());

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);

}

PlayerShip::~PlayerShip()
{
};

void PlayerShip::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

float PlayerShip::GetVelocity() const
{
	return _velocity;
}
void PlayerShip::Update(float elapsedTime)
{
	printf("moves made is %i",_moves);
	int turn = 0;
	float moveAmount = 0;

	if(_moves <_maxMoves){

	if(Game::GetInput().IsKeyDown(sf::Key::Up))
	{
		moveAmount =30.0f;
		_moves++;
		Sleep(500);
	}
	if(Game::GetInput().IsKeyDown(sf::Key::Down))
	{
		//_velocity-=3.0f;
		//++_moves;
	}
	if(Game::GetInput().IsKeyDown(sf::Key::Right))
	{
		_angle += _turningspeed;
		//rotate angle is inverse to other angles
		GetSprite().Rotate(-_turningspeed);
		_moves++;
		Sleep(500);
	}
	if(Game::GetInput().IsKeyDown(sf::Key::Left))
	{
		_angle -= _turningspeed;
		GetSprite().Rotate(_turningspeed);
		_moves++;
		Sleep(500);
	}
	}
	//if(_velocity > _maxVelocity)
	//	_velocity = _maxVelocity;
	//if(_velocity < 0)
	//	_velocity = 0;
	if(_angle > 360.f) _angle -= 360.0f;

	sf::Vector2f pos = this->GetPosition();

	//if(pos.x < GetSprite().GetSize().x/2  + edge_gap && _velocity <0 
	//	|| pos.x > (Game::window_x_resolution - edge_gap - GetSprite().GetSize().x/2) && _velocity >0)
	//{
	//	_velocity = -_velocity; //bounce in opposite direction
	//}

//	float moveAmount = _velocity * elapsedTime;

	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;

		//collide with side of screen
	if(GetPosition().x + moveByX <= 0 +GetWidth()/2 + edge_gap|| 
		GetPosition().x + GetWidth()/2 + moveByX >= Game::window_x_resolution - edge_gap) 
	{
		//_angle = 360.0f -_angle;
		//if(_angle > 260.0f && _angle < 280.0f) _angle += 20.f;
		//if(_angle > 80.0f && _angle < 100.0f) _angle += 20.f;
		_velocity = 0;
		moveByX = -moveByX;
	}

	if(GetPosition().y - GetHeight()/2 + moveByY <=0 +edge_gap||
		GetPosition().y + GetHeight()/2 + moveByY >= Game::window_y_resolution - edge_gap)
	{
		//_angle = 180- _angle;
		_velocity = 0;
		moveByY = -moveByY;
	}

	
	
	GetSprite().Move(moveByX, moveByY);
	
	
}