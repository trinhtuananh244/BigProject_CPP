
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
#include "AmoObject.h"
#include "Common_Function.h"
#include "BaseObject.h"
#include<vector>
#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52
class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();
	void HandleInputAction(SDL_Event events);
	//Mix_Chunk *bullet_sound[2]
	void HandleMove();
	void SetAmoList(std::vector<AmoObject*>amo_list){ p_amo_list_ = amo_list;}
	std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}
	void MakeBullet(SDL_Surface* des);
	void RemoveAmo(const int& idx);
private:
	int x_val_;
	int y_val_;
	std:: vector<AmoObject*> p_amo_list_;

};


#endif //MAIN_OBJECT_H_