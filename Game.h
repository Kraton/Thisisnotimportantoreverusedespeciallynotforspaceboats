#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "PlayerShip.h"
#include "GameObjectManager.h"
#include "stdafx.h"
#include "GameBall.h"

class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	const static sf::Input& GetInput();
	const static GameObjectManager& GetGameObjectManager();
	

	const static int window_x_resolution = window_width;
	const static int window_y_resolution = window_height;


private:
	static bool IsExiting();
	static void GameLoop(sf::Sprite);

	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState { Uninitialized, ShowingSplash, Paused, 
		ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;

};
