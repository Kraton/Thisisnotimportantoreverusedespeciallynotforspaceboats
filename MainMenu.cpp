#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	//load menu image from file
	sf::Image image;
	image.LoadFromFile(main_menu_image);
	sf::Sprite sprite(image);

	//setup clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.Top=0;
	playButton.rect.Bottom=window_height/3;
	playButton.rect.Left= (window_width/3) ;
	playButton.rect.Right=(window_width/3)*2;
	playButton.action = Play;

	//Exit menu item Coordinates

	 MenuItem exitButton;
	exitButton.rect.Left = (window_width/3);
	exitButton.rect.Right = (window_width/3)*2;
	exitButton.rect.Top = (window_height/3)*2;
	exitButton.rect.Bottom = window_height;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	
	window.Draw(sprite);
	window.Display();

	return GetMenuResponse(window);

}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for ( it = _menuItems.begin(); it !=_menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if( menuItemRect.Bottom > y 
			&& menuItemRect.Top < y 
			&& menuItemRect.Left < x 
			&& menuItemRect.Right > x)
		{
			return (*it).action;
		}
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while(true)
	{
		while(window.GetEvent(menuEvent))
		{
			if(menuEvent.Type ==sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.MouseButton.X, menuEvent.MouseButton.Y);
			}
			if(menuEvent.Type ==sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}


