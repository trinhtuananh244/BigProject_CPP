﻿
#include "MainObject.h"
MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}
MainObject::~MainObject()
{
	;
}
//,Mix_Chunk *bullet_sound[2]
void MainObject::HandleInputAction(SDL_Event events)
{
	if(events.type==SDL_KEYDOWN)
	{
		switch(events.key.keysym.sym) 
 {
   case SDLK_UP: 
	   y_val_ -= HEIGHT_MAIN_OBJECT/10;
   break;
   case SDLK_DOWN: 
	   y_val_ +=HEIGHT_MAIN_OBJECT/10;
   break;
   case SDLK_LEFT: 
	   x_val_-= WIDTH_MAIN_OBJECT/10;

   break;
   case SDLK_RIGHT: 
	   x_val_ += WIDTH_MAIN_OBJECT/10;
   break;
 }
 
	}
	else if(events.type==SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: y_val_ += HEIGHT_MAIN_OBJECT/10;
		
			break;
		case SDLK_DOWN:y_val_ -= HEIGHT_MAIN_OBJECT/10;
			break;
		case SDLK_LEFT:x_val_ += WIDTH_MAIN_OBJECT/10;
			break;
		case SDLK_RIGHT:x_val_ -=WIDTH_MAIN_OBJECT/10;
			break;
		}
	}
	else if(events.type==SDL_MOUSEBUTTONDOWN)
	{
		AmoObject* p_amo =new AmoObject();
		if(events.button.button == SDL_BUTTON_LEFT)
		{
			p_amo->SetWidthHeight(WIDTH_LASER,HEIGHT_LASER);
			p_amo->LoadImg("Rocket.png");
			p_amo->set_type(AmoObject::LASER);
			//Mix_PlayChannel(-1,bullet_sound[0],0);
		}
		else if(events.button.button==SDL_BUTTON_RIGHT)
		{
			p_amo->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
			p_amo->LoadImg("Shuriken.png");
			p_amo->set_type(AmoObject::SPHERE);
			//Mix_PlayChannel(-1, bullet_sound[1], 0);
		}
		p_amo->SetRect(this->rect_.x+this->rect_.w-40,this->rect_.y+this->rect_.h*0.8);
		p_amo->set_is_move(true);
		p_amo_list_.push_back(p_amo);
	}
	else if(events.type==SDL_MOUSEBUTTONUP)
	{

	}
	else
	{
		;//
	}

}


void MainObject::MakeBullet(SDL_Surface* des)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
	AmoObject* p_amo_ = p_amo_list_.at(i);
		if (p_amo_ != NULL)
		{
			if (p_amo_->get_is_move())
			{
				p_amo_->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_amo_->Show(des);
			}
			else
			{
				if (p_amo_ != NULL)
				{
					p_amo_list_.erase(p_amo_list_.begin() + i);
					delete p_amo_;
					p_amo_ = NULL;
				}
			}
		}
	}
}
void MainObject::HandleMove()
{
	rect_.x += x_val_;
	if(rect_.x<0||rect_.x+WIDTH_MAIN_OBJECT> SCREEN_WIDTH)
	{
		rect_.x -=x_val_;
	}

	rect_.y +=y_val_;
	if(rect_.y<0||rect_.y+HEIGHT_MAIN_OBJECT>SCREEN_HEIGHT-200)//  giới hạn chiều bay(cao) của main
	{
		rect_.y -=y_val_;
	}
}
void MainObject::RemoveAmo(const int& idx)
{
		for(int i = 0;i< p_amo_list_.size();i++)
		{
			if(idx < p_amo_list_.size())
			{
				AmoObject* p_amo =p_amo_list_.at(idx);
			p_amo_list_.erase(p_amo_list_.begin() + idx);
			if(p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		
			}
		}
	}
	
