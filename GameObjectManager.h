#pragma once
#include "visiblegameobject.h"
#include "stdafx.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string name) const;
	std::vector<std::string> getGameObjectNames() const;

	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();
	void ResetAllMoves();

	void DrawGroup(sf::RenderWindow& renderWindow, int lowerGroupBound, int upperGroupBound);
	void UpdateGroup(int lowerGroupBound, int upperGroupBound);
	void PressEnterToContinue();

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
};