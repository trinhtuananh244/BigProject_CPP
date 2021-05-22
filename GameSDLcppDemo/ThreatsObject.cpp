
#include "ThreatsObject.h"

ThreatObject:: ThreatObject()
{
	rect_.x= SCREEN_WIDTH;
	rect_.y= SCREEN_HEIGHT*0.5;
	rect_.w= WIDTH_THREAT;
	rect_.h= HEIGHT_THREAT;

	x_val_ = 0;
	y_val_ = 0;

}

ThreatObject::~ThreatObject()
{
	if(p_amo_list_.size() > 0)
	{
		for(int i=0;i< p_amo_list_.size();i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if(p_amo != NULL)
			{
				delete p_amo;
				p_amo =NULL;
			}
		}
		p_amo_list_.clear();// giai phong bo nho
	}
}

void ThreatObject:: InitAmo(AmoObject* p_amo)
{
	if(p_amo)
	{
		bool ret = p_amo->LoadImg("sphere.png");
		if(ret){
			p_amo->set_is_move(true);//cho phep di chuyen
			p_amo->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);//cai dat chieu cao va rong cua dan phan dien
			p_amo->set_type(AmoObject::SPHERE);// kieu dan cua phan dien
			p_amo->SetRect(rect_.x,rect_.y+rect_.h*0.5);//vi tri xuat hien cua dan
			p_amo_list_.push_back(p_amo);//save dan
		}
	}
}

void ThreatObject:: MakeAmo(SDL_Surface* des,const int& x_limit,const int& y_limit)//khai bao ham ban dan
    {
		for(int i=0;i< p_amo_list_.size();i++)
		{
			AmoObject* p_amo =p_amo_list_.at(i);
			if(p_amo)
			{
				if(p_amo->get_is_move())
				{
					p_amo->Show(des);
					p_amo->HandleMoveRightToLeft();
				}
				else
				{
					p_amo->set_is_move(true);
					p_amo->SetRect(rect_.x,rect_.y+rect_.h*0.5);
				}
			}
		}
    }
void ThreatObject::HandleMove(const int& x_border,const int& y_border)
{
	rect_.x -=x_val_;
	if(rect_.x<0)
	{
		rect_.x = SCREEN_WIDTH;// vị trí xuất hiện
		int rand_y = rand()%400;
		if(rand_y > SCREEN_HEIGHT -200)
		{
			rand_y =SCREEN_HEIGHT*0.3;
		}
		rect_.y = rand_y;
	}
}
void ThreatObject::HandleInputAction(SDL_Event events)
{

}
void ThreatObject :: Reset(const int &xborder)
{
	rect_.x =xborder;
	
		int rand_y = rand()%400;
		if(rand_y > SCREEN_HEIGHT -200)
		{
			rand_y =SCREEN_HEIGHT*0.3;
		}
		rect_.y = rand_y;
		for(int i =0;i<p_amo_list_.size();i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if(p_amo)
			{
				ResetAmo(p_amo);
			}
		}
}
void ThreatObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(rect_.x,rect_.y+rect_.h*0.5);
}