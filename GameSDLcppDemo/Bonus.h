#ifndef BONUS_OBJECT_H_
#define BONUS_OBJECT_H_
#include"BaseObject.h"
#include"Common_Function.h"
#include<vector>
#define BONUS_HEIGHT 30
#define BONUS_WIDTH 29

//const int MAX_COUNT = 100 ; // until count_  reach this value then bonus object disappear (being deleted) .

class BonusObject : public BaseObject
{
public:
    BonusObject();
	~BonusObject();
	void HandleMove(const int& x_border,const int& y_border);
	void HandleInputAction(SDL_Event events);

	void set_x_val(const int& val){x_val_ =val;}
	void set_y_val(const int& val){y_val_=val;}
	int get_x_val() const {return x_val_;}
	int get_y_val()const {return y_val_;}
  	void Reset(const int& xborder);
	void ResetBonus(BonusObject* p_bonus);
private:
	int x_val_;
	int y_val_;

};

#endif // BONUS_OBJECT_H_