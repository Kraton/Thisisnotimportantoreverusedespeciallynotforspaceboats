#include "stdafx.h"
#include "visiblegameobject.h"

VisibleGameObject::VisibleGameObject()
{
	_isLoaded = false;
}

VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
	if(_image.LoadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.SetImage(_image);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if(_isLoaded)
	{
		renderWindow.Draw(_sprite);
	}
}

void VisibleGameObject::Update(float elapsedTime)
{
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if(_isLoaded)
	{
		_sprite.SetPosition(x,y);
	}
}

float VisibleGameObject::GetHeight() const
{
	return _sprite.GetSize().y;
}

float VisibleGameObject::GetWidth() const
{
	return _sprite.GetSize().x;
}

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if(_isLoaded)
	{
		return _sprite.GetPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	sf::Vector2f size = _sprite.GetSize();
	sf::Vector2f position = _sprite.GetPosition();

	return sf::Rect<float>(
		position.x - size.x/2,
		position.y - size.y/2,
		position.x + size.x/2,
		position.y + size.y/2);
}

float VisibleGameObject::LinearVelocityX(float angle)
{
  angle -= 90;
    if (angle < 0) angle = 360 + angle;
    return (float)std::cos( angle * ( pi_value / 180.0f ));
}

float VisibleGameObject::LinearVelocityY(float angle)
{
  angle -= 90;
    if (angle < 0) angle = 360 + angle;
    return (float)std::sin( angle * ( pi_value / 180.0f ));
}