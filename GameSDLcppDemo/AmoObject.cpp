#include "AmoObject.h"
#include <math.h>
#include <iostream>

AmoObject:: AmoObject()
{
	rect_.x = 0;
	rect_.y= 0;
	x_val_ = 0;
	y_val_ = 0;
	is_move_ =false;
	amo_type_ = NONE;
	changeDirection = false;
	
}
AmoObject::~AmoObject()
{
	
}
// đạn bắn của main
void AmoObject::HandleMove(const int& x_border,const int & y_border)
{

	if(is_move_ == true)
	{
	rect_.x+=SPEED_BULLET_MAIN;
	if(rect_.x>x_border)
	{
		is_move_ =false;
	}
  }
}
// đạn bắn của Threat
void AmoObject:: HandleMoveRightToLeft()
{
	rect_.x-=5;
	if(rect_.x<0)
	{
		is_move_ =false;
	}
	

	if (!changeDirection && rect_.y < 0){
		//std::cout << "Here" << std::endl;
		changeDirection = true;
	}
	else if (rect_.y >500){
		changeDirection = false;
	}
	if (changeDirection){
		//std::cout << "Here1" << std::endl;
		rect_.y += 3;
	}
	else{
		//std::cout << "Here2" << std::endl;
		rect_.y -= 3;
	}
}
void AmoObject:: HandleInputAction (SDL_Event events)
{
	;
}
