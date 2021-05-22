// tạo ảnh 


#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <Windows.h>
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include <SDL_ttf.h>
//SCREEN
const int WIDTH_BACKGROUND =4800;
const int HEIGHT_BACKGROUND =600;	
const int SCREEN_WIDTH =1200;
const int SCREEN_HEIGHT =600;
const int SCREEN_BPP =32;
//MAIN
const int POS_X_START_MAIN_OBJ = 100;
const int POS_Y_START_MAIN_OBJ =200;
const int SPEED_BULLET_MAIN = 5 ;
//THREATS
const int NUM_THREATS =3;
const int VAL_OFFSET_START_POST_THREATS = 400;
const int SPEED_THREAT = 2;
const int SPEED_THREAT1 = 4;
const int SPEED_THREAT2 = 8;
const int SPEED_THREAT3 = 10;
static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Event g_even;
static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];



//Bonus


//Expolusion
static char g_name_exp_main[] = { "exp_main.png" };
static char g_name_exp_threats[] = { "exp_main.png" };

namespace SDLComonFunc 
{
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src,SDL_Surface* des,SDL_Rect* clip,int x,int y);
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object1,const SDL_Rect& object2);
	//int ShowMenu(SDL_Surface* g_screen, TTF_Font* font);
}
#endif