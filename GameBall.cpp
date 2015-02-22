#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"
#include "GameObjectManager.h"
#include "Defines.h"

GameBall::GameBall() : 
_velocity(230.0f),
_elapsedTimeSinceStart(0.0f)
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);

	sf::Randomizer::SetSeed(std::clock());
	_angle = (float)sf::Randomizer::Random(0,360);
}
GameBall::~GameBall()
{
}

void GameBall::Update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	//Delay start time by 3 seconds
	if(_elapsedTimeSinceStart <3.0f)
		return;

	float moveAmount = _velocity * elapsedTime;

	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;
	//if outside screen
	if(GetPosition().y >= Game::window_y_resolution + GetHeight() - edge_gap || 
		GetPosition().y <= 0 - GetHeight() +edge_gap ||
		GetPosition().x >= Game::window_x_resolution + GetWidth() - edge_gap||
		GetPosition().x <= 0- GetWidth() + edge_gap)
	{
		//move back to middle
		GetSprite().SetPosition(Game::window_x_resolution/2, Game::window_y_resolution/2);
		_angle = (float)sf::Randomizer::Random(0,360);
		_velocity = 230.0f;
		_elapsedTimeSinceStart =0.0f;
	}

	//collide with side of screen
	if(GetPosition().x + moveByX <= 0 +GetWidth()/2 + edge_gap|| 
		GetPosition().x + GetWidth()/2 + moveByX >= Game::window_x_resolution - edge_gap) 
	{
		_angle = 360.0f -_angle;
		if(_angle > 260.0f && _angle < 280.0f) _angle += 20.f;
		if(_angle > 80.0f && _angle < 100.0f) _angle += 20.f;
		moveByX = -moveByX;
	}



	std::vector<std::string> vector = Game::GetGameObjectManager().getGameObjectNames();

	for (std::vector<std::string>::iterator itr = vector.begin(); itr != vector.end(); ++itr)
	{
		PlayerPaddle * player1= dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get(*itr));
		if(player1 != NULL)
		{
			sf::Rect<float> p1BoundaryBox = player1->GetBoundingRect();
		
			if(p1BoundaryBox.Intersects(GetBoundingRect()))
			{
				_angle = 360.0f - (_angle - 180.0f);
				if(_angle > 360.f) _angle -= 360.0f;

				moveByY = -moveByY;

				//make sure ball isnt inside paddle
				if(GetBoundingRect().Bottom > player1->GetBoundingRect().Top)
				{
					SetPosition(GetPosition().x,player1->GetBoundingRect().Top - GetWidth()/2 -1 );
				}
			}
		}
		GameBall * ball= dynamic_cast<GameBall*>(Game::GetGameObjectManager().Get(*itr));
		if(ball != NULL)
		{
			if(ball != this)
			{
				sf::Rect<float> ballBoundaryBox = ball->GetBoundingRect();
				if(ballBoundaryBox.Intersects(GetBoundingRect()))
				{
					_angle = 360.0f - (_angle - 180.0f);
					if(_angle > 360.f) _angle -= 360.0f;
					_velocity += sf::Randomizer::Random(-10,10);

					moveByY = -moveByY;

					//make sure ball isnt inside ball
					if(GetBoundingRect().Bottom > ball->GetBoundingRect().Top)
					{
						SetPosition(GetPosition().x + sf::Randomizer::Random(-GetWidth(),GetWidth()),GetPosition().y + sf::Randomizer::Random(-GetWidth(),GetWidth()) );
					}
				}
			}
		}

	}
	if(GetPosition().y - GetHeight()/2 <=0 +edge_gap|| GetPosition().y + GetHeight()/2 + moveByY >= Game::window_y_resolution - edge_gap)
	{
		_angle = 180- _angle;
		moveByY = -moveByY;
	}

	//if(GetPosition().y + GetHeight()/2 + moveByY >= Game::window_y_resolution)
	//{
	//	//move back to middle
	//	GetSprite().SetPosition(Game::window_x_resolution/2, Game::window_y_resolution/2);
	//	_angle = (float)sf::Randomizer::Random(0,360);
	//	_velocity = 230.0f;
	//	_elapsedTimeSinceStart =0.0f;
	//}

	GetSprite().Move(moveByX, moveByY);
	
}

float GameBall::LinearVelocityX(float angle)
{
  angle -= 90;
    if (angle < 0) angle = 360 + angle;
    return (float)std::cos( angle * ( 3.1415926 / 180.0f ));
}

float GameBall::LinearVelocityY(float angle)
{
  angle -= 90;
    if (angle < 0) angle = 360 + angle;
    return (float)std::sin( angle * ( 3.1415926 / 180.0f ));
}