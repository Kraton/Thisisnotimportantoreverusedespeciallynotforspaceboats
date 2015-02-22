#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

#define bpp_colour 32

void Game::Start(void)
{
	if(_gameState !=Uninitialized)
		return;
	printf("here2");
	_mainWindow.Create(sf::VideoMode(window_x_resolution,window_y_resolution,bpp_colour),"Spaceboats!");

	printf("here3");
	PlayerPaddle *player1 = new PlayerPaddle();
	GameBall *Ball1 = new GameBall();
	GameBall *Ball2 = new GameBall();
	GameBall *Ball3 = new GameBall();
	GameBall *Ball4 = new GameBall();
	GameBall *Ball5 = new GameBall();
	GameBall *Ball6 = new GameBall();
	GameBall *Ball7 = new GameBall();
	GameBall *Ball8 = new GameBall();
	GameBall *Ball9 = new GameBall();
	GameBall *Ball10 = new GameBall();



	Ball1->SetPosition(starting_ball_loc_1);
	Ball2->SetPosition(starting_ball_loc_2);
	Ball3->SetPosition(starting_ball_loc_3);
	Ball4->SetPosition(starting_ball_loc_4);
	Ball5->SetPosition(starting_ball_loc_5);
	Ball6->SetPosition(starting_ball_loc_6);
	Ball7->SetPosition(starting_ball_loc_7);
	Ball8->SetPosition(starting_ball_loc_8);
	Ball9->SetPosition(starting_ball_loc_9);
	Ball10->SetPosition(starting_ball_loc_10);
	player1->SetPosition(starting_paddle_loc);

	_gameObjectManager.Add("Paddle1", player1);
	_gameObjectManager.Add("ball1", Ball1);
	_gameObjectManager.Add("ball2", Ball2);
	_gameObjectManager.Add("ball3", Ball3);
	_gameObjectManager.Add("ball4", Ball4);
	_gameObjectManager.Add("ball5", Ball5);
	_gameObjectManager.Add("ball6", Ball6);
	_gameObjectManager.Add("ball7", Ball7);
	_gameObjectManager.Add("ball8", Ball8);
	_gameObjectManager.Add("ball9", Ball9);
	_gameObjectManager.Add("ball10", Ball10);
	_gameState = Game::ShowingSplash;

	sf::Image image;
	if(image.LoadFromFile(background_image) != true)
	{
		return;
	}
	sf::Sprite sprite(image);

	while(!IsExiting())
	{
		GameLoop(sprite);
	}

	_mainWindow.Close();

}

bool Game::IsExiting()
{
	if(_gameState == Game::Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Input& Game::GetInput() 
{
	return _mainWindow.GetInput();
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return _gameObjectManager;
}


void Game::GameLoop(sf::Sprite _background_image)
{
	sf::Event currentEvent;
	_mainWindow.GetEvent(currentEvent);


	switch(_gameState)
	{
	case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
	case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
	case Game::Playing:
		{

			_mainWindow.Draw(_background_image);
			
		
			_gameObjectManager.UpdateAll();
			_gameObjectManager.DrawAll(_mainWindow);

			_mainWindow.Display();

			if(currentEvent.Type == sf::Event::Closed)
			{
				_gameState = Game::Exiting;
			}

			if(currentEvent.Type == sf::Event::KeyPressed)
			{
				if(currentEvent.Key.Code == sf::Key::Escape) ShowMenu();
			}
			break;
		}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;