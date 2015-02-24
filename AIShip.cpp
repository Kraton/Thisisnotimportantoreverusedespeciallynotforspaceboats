#include "stdafx.h"
#include "AIShip.h"
#include "game.h"
#include "Defines.h"


AIShip::AIShip() : 
_velocity(100.0f),
_maxVelocity(600.0f),
_angle(0.0f)
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


			if (ideal_rotate_angle > (desired_turning_speed_per_second*elapsedTime))
			{
				rotate_angle = (desired_turning_speed_per_second*elapsedTime);
			}
			else if (ideal_rotate_angle < -(desired_turning_speed_per_second*elapsedTime))
			{
				rotate_angle = -(desired_turning_speed_per_second*elapsedTime);
			}
			else {
				rotate_angle = ideal_rotate_angle;
			}

			angle_to_fly = _angle + rotate_angle;

			float linVelX = LinearVelocityX(angle_to_fly);
			float linVelY = LinearVelocityY(angle_to_fly);

			moveByX = linVelX * moveAmount ;
			moveByY = linVelY * moveAmount ;

			if(p1BoundaryBox.Intersects(GetBoundingRect()))
			{
				SetPosition(starting_AI_loc);
				printf(" got you ");
			}
			//printf("angle is %f \n", _angle);
			//rotate angle is inverse to all other angles
			GetSprite().Rotate(-rotate_angle);

			_angle=angle_to_fly;

		}
	}

	
	GetSprite().Move(moveByX, moveByY);
	
	
}