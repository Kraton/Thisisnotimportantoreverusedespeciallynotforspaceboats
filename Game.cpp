#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

#define bpp_colour 32

void Game::Start(void)
{
	if(_gameState !=Uninitialized)
		return;
	_mainWindow.Create(sf::VideoMode(window_x_resolution,window_y_resolution,bpp_colour),"Spaceboats!");

	PlayerShip *player1 = new PlayerShip();
	AIShip *AI1 = new AIShip();
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
	player1->SetPosition(starting_player_loc);
	AI1->SetPosition(starting_AI_loc);

	_gameObjectManager.Add("1", player1);
	_gameObjectManager.Add("1001", AI1);
	_gameObjectManager.Add("2001", Ball1);
	_gameObjectManager.Add("2002", Ball2);
	_gameObjectManager.Add("2003", Ball3);
	_gameObjectManager.Add("2004", Ball4);
	_gameObjectManager.Add("2005", Ball5);
	_gameObjectManager.Add("2006", Ball6);
	_gameObjectManager.Add("2007", Ball7);
	_gameObjectManager.Add("2008", Ball8);
	_gameObjectManager.Add("2009", Ball9);
	_gameObjectManager.Add("2010", Ball10);
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
			DWORD begin =GetTickCount();
			//printf("clock time is %d",begin);
			_mainWindow.Draw(_background_image);
			switch(_currentActiveParty)
			{
			case Game::Player1:
				{

			_gameObjectManager.UpdateGroup(player1_objects_lower_bound, player1_objects_upper_bound);
			if(currentEvent.Type == sf::Event::KeyPressed)
			{
				if(currentEvent.Key.Code == sf::Key::Space)
				{
					_currentActiveParty = Game::AI;
					_gameObjectManager.ResetAllMoves();
				}
			}	
			break;
				}
			case Game::AI:
				{
			_gameObjectManager.UpdateGroup(AI_objects_lower_bound, AI_objects_upper_bound);
			if(currentEvent.Key.Code == sf::Key::PageUp)
				{
					_currentActiveParty = Game::Env;
					_gameObjectManager.ResetAllMoves();
				}	
			
			break;
				}
			case Game::Env:
				{
			_gameObjectManager.UpdateGroup(env_objects_lower_bound, env_objects_upper_bound);
			if(currentEvent.Key.Code == sf::Key::PageDown)
				{
					_currentActiveParty = Game::Player1;
					_gameObjectManager.ResetAllMoves();
					
				}	
			break;
				}
			}
			while (begin +(1000/desired_fps) > GetTickCount()){
			Sleep(1);
			}
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
		_currentActiveParty = Game::Player1;
		break;
	}
}

Game::GameState Game::_gameState = Uninitialized;
Game::ActiveParty Game::_currentActiveParty = NotStarted;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;