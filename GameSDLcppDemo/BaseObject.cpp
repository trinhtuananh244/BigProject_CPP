// lớp cơ sở
#include "BaseObject.h"


BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;
}
 BaseObject::~BaseObject()
{
	if(p_object_!=NULL)
	{
		SDL_FreeSurface(p_object_);
	}
}

bool BaseObject::LoadImg(const char* file_name)
{
	p_object_ = SDLComonFunc::LoadImage(file_name);
		if(p_object_ ==NULL)
			return false;
	return true;
}
void BaseObject::Show(SDL_Surface*des)
{
	if(p_object_!=NULL)
	{
		SDLComonFunc::ApplySurface(p_object_,des,rect_.x,rect_.y);

	}
}