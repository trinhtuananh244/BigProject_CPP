#include "BaseObject.h"
#include "Bonus.h"
//#include "Common_Function.h"

BonusObject::BonusObject()
{
	rect_.x = SCREEN_WIDTH;
    rect_.y = SCREEN_HEIGHT * 0.5;
	rect_.w = BONUS_WIDTH;
	rect_.h = BONUS_HEIGHT;


	x_val_ = 0;
	y_val_ = 0;

}
BonusObject::~BonusObject()
{
	
}
void BonusObject::HandleMove(const int& x_border,const int& y_border)
{
	rect_.x -= x_val_;
	if(rect_.x < 0)
	{
		rect_.x= SCREEN_WIDTH;
		int rand_y =rand()%500;
		if(rand_y> SCREEN_HEIGHT-200)
		{
			rand_y =SCREEN_HEIGHT*0.2;
		}
		rect_.y = rand_y;
	}

}
void BonusObject::HandleInputAction(SDL_Event events)
{

}

void BonusObject::Reset(const int& xboder)
{
	rect_.x=xboder;
	rect_.x= SCREEN_WIDTH;
	int rand_y =rand()%500;
	if(rand_y> SCREEN_HEIGHT-200)
	{
	rand_y =SCREEN_HEIGHT*0.2;
	}
	rect_.y = rand_y;
}