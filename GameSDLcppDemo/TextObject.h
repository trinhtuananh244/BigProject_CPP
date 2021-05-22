#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include "Common_Function.h"
#include "BaseObject.h"

#include <string>
#include <SDL_ttf.h>
//class base
class TextObject : public BaseObject
{
public:
	TextObject();
	~TextObject();
	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT =1,
		BLACK_TEXT =2,
	};
	

	void SetText(const std::string& text){str_val_=text;}
	void SetColor(const int& type);
	void CreateGameText(TTF_Font* font,SDL_Surface* des);
private:
	std::string str_val_;
	SDL_Color text_color_;
};


#endif