﻿
#ifndef PLAYER_POWER_H
#define PLAYER_POWER_H
#include "BaseObject.h"
#include <vector>
class PlayerPower : public BaseObject
{
public:
	PlayerPower();
	~PlayerPower();
	void SetNumber(const int& num){number_ = num;}
	void AddPos (const int& xpos);
	void Render(SDL_Surface* des);
	void Init();
	void Decrease();
	void Increase();
private:
	int number_;
	std::vector <int> pos_list_; //vị trí của trái tim
};

#endif
