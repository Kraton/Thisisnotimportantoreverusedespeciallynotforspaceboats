#include "stdafx.h"
#include "AIShip.h"
#include "game.h"
#include "Defines.h"


AIShip::AIShip() : 
_velocity(100.0f),
_maxVelocity(600.0f),
_angle(0.0f),
_maxMoves(6),
_turningspeed(22.5)
{
	Load(AI_ship_image);
	assert(IsLoaded());

	GetSprite().SetCenter(GetSprite().GetSize().x /2, GetSprite().GetSize().y / 2);

}

AIShip::~AIShip()
{
};

void AIShip::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

float AIShip::GetVelocity() const
{
	return _velocity;
}
void AIShip::Update(float elapsedTime)
{
	float moveByX = 1;
	float moveByY = 1;
	int desired_turning_speed_per_second = 90;
//	printf("velocity is %f", _velocity);
//	printf("elapsed Time is %f \n", elapsedTime);
	float moveAmount = _velocity * elapsedTime;
//	printf("moveAmount is %f \n", moveAmount);
	if(_moves <_maxMoves){
	std::vector<std::string> vector = Game::GetGameObjectManager().getGameObjectNames();

	for (std::vector<std::string>::iterator itr = vector.begin(); itr != vector.end(); ++itr)
	{
		PlayerShip * player1= dynamic_cast<PlayerShip*>(Game::GetGameObjectManager().Get(*itr));
		if(player1 != NULL)
		{

			sf::Rect<float> p1BoundaryBox = player1->GetBoundingRect();

			float playerx =player1->GetPosition().x;
			float playery =player1->GetPosition().y;
			//printf("playerx is %f \n", playerx);
			//printf("playery is %f \n", playery);

			float AIx = GetPosition().x;
			float AIy = GetPosition().y;
			//printf("AIx is %f \n", AIx);
			//printf("AIy is %f \n", AIy);
			float angle_to_player = 0;

			//using sohcahtoa to calcuate angle between ai ship and player
			if( AIx>playerx && AIy < playery)
			{
				//printf("player is bottom left of AI");
				angle_to_player = 90 - (atan((std::abs(AIy-playery))/std::abs(AIx - playerx)))* 180/pi_value; //90 to accomdate for angle defaults
				//printf("pure angle to player is%f \n", angle_to_player);
				angle_to_player = -1*(180-angle_to_player);
				//printf("modified angle to player is%f \n", angle_to_player);
			}
			else if( AIx>playerx && AIy > playery)
			{
				//printf("player is top left of AI");
				angle_to_player = 90 - (atan((std::abs(AIy-playery))/std::abs(AIx - playerx)))* 180/pi_value; //90 to accomdate for angle defaults
				//printf("pure angle to player is%f \n", angle_to_player);
				angle_to_player = -1*(angle_to_player);
				//printf("modified angle to player is%f \n", angle_to_player);
			}
			else if( AIx<playerx && AIy > playery)
			{
				//printf("player is top right of AI");
				angle_to_player = 90 - (atan((std::abs(AIy-playery))/std::abs(AIx - playerx)))* 180/pi_value; //90 to accomdate for angle defaults
				//printf("pure angle to player is%f \n", angle_to_player);
				angle_to_player = (angle_to_player);
				//printf("modified angle to player is%f \n", angle_to_player);
			}
			else if( AIx<playerx && AIy < playery)
			{
				//printf("player is bottom right of AI");
				angle_to_player = 90 - (atan((std::abs(AIy-playery))/std::abs(AIx - playerx)))* 180/pi_value; //90 to accomdate for angle defaults
				//printf("pure angle to player is%f \n", angle_to_player);
				angle_to_player = (180 - angle_to_player);
				//printf("modified angle to player is %f \n", angle_to_player);
			}

			float angle_to_fly = 0;
			float rotate_angle= 0;
			float ideal_rotate_angle=0;
//			if (angle_to_player > 0.0f)
//			{
			ideal_rotate_angle= angle_to_player-_angle;
			if (ideal_rotate_angle <-180){
			ideal_rotate_angle +=360;
			}
			//}
			//else if(angle_to_player <= 0.0f)
			//{
			//	printf("in <=0 area");
			//ideal_rotate_angle= angle_to_player+_angle;
			//}

			printf("ideal rotate angle to player is %f \n", ideal_rotate_angle);
			if (ideal_rotate_angle > 30.f)
			{
				printf("triggered for > 30 \n");
				_angle += _turningspeed;
				GetSprite().Rotate(-_turningspeed);
				_moves++;
				Sleep(500);
			}
			else if (ideal_rotate_angle < -30.f)
			{
				printf("triggered for < 30 \n ");
				_angle -= _turningspeed;
				GetSprite().Rotate(_turningspeed);
				_moves++;
				Sleep(500);
			}
			else {
				moveAmount =30.0f;
				_moves++;
				Sleep(500);
			}

			if(_angle > 360.f) _angle -= 360.0f;
			if(_angle < 0) _angle += 360.0f;

			float linVelX = LinearVelocityX(_angle);
			float linVelY = LinearVelocityY(_angle);

			moveByX = linVelX * moveAmount ;
			moveByY = linVelY * moveAmount ;

			if(p1BoundaryBox.Intersects(GetBoundingRect()))
			{
				SetPosition(starting_AI_loc);
				printf(" got you ");
			}

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


		}
	}
	
	
	GetSprite().Move(moveByX, moveByY);


	}
	
}