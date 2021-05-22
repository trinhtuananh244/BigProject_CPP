
#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include <iostream>
#include "PlayerPow.h"
#include "TextObject.h"
#include "Bonus.h"
#include<vector>

TTF_Font* g_font_text = NULL;
bool Init()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    return false;
  }
  g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  if (g_screen == NULL)
  {
    return false; 
	/*if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	return false;*/
  }

	//read file wav
 	/*g_sound_bullet[0] = Mix_LoadWAV("Laser.wav");
	g_sound_bullet[1] = Mix_LoadWAV("Fire1.wav");
	g_sound_exp[0] = Mix_LoadWAV("Explo.wav");
	g_sound_exp[1] = Mix_LoadWAV("Bomb1.wav");
	*/
	//	
	//if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[1] == NULL)
	//{
	//	return false;
	//}
  if(TTF_Init() == -1)
  {
	  return false;
  }
  g_font_text = TTF_OpenFont("JosefinSans-SemiBold.ttf",20);
  if(g_font_text ==NULL)
  {
	  return false;
  }
	return true;

}
 


SDL_Surface* LoadImage(std::string file_path)
{
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image =IMG_Load(file_path.c_str());
	if(load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
	}
	if (optimize_image != NULL) 
 {
   UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF);
   SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
 }
	return optimize_image;
}

void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(src, NULL, des, &offset);
}


void CleanUp()
{
  SDL_FreeSurface(g_screen);
  SDL_FreeSurface(g_bkground);
}
 
 
int main(int arc, char*argv[])
{
	std::cout << "Hello" << std::endl;
  int bkgn_x =0;
  bool is_quit = false;
  if (Init() == false)
   return 0;
 
  g_bkground = SDLComonFunc:: LoadImage("bk1.png");
  if (g_bkground == NULL)
  {
    return 0;
  }

  // Make Player Power
  PlayerPower player_power;
  player_power.Init();

  TextObject mark_game;
  mark_game.SetColor(TextObject::RED_TEXT);


  TextObject time_game;
  time_game.SetColor(TextObject::BLACK_TEXT);
// Tạo MainObject
  MainObject plane_object;
  plane_object.SetRect(100,200);
  bool ret = plane_object.LoadImg("plane_fly.png");
	if(!ret)
	{
		return 0;
	}
	//Init explosionobject(vụ nổ của main và threats)
		ExplosionObject exp_main;
	ExplosionObject exp_threats;
	ret = exp_main.LoadImg(g_name_exp_main);
	exp_main.set_clip();
	if (ret == false) 
		return 0;

	ret = exp_threats.LoadImg(g_name_exp_threats);
	exp_threats.set_clip();
	if (!ret) 
		return 0;
	// Tạo BonusObject
	BonusObject* p_bonus = new BonusObject();
	ret = p_bonus->LoadImg("Star.png");
	if(ret==false)
	{
		return 0;
	}
	
		int rand_y =rand()%500;
		if(rand_y> SCREEN_HEIGHT-200)
		{
			rand_y =SCREEN_HEIGHT*0.2;
		}
		
	

	p_bonus->SetRect(SCREEN_WIDTH,rand_y);
	p_bonus->set_x_val(5);

 // Tạo ThreatObject
	ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
	for(int t=0;t<NUM_THREATS;t++)
	{
		ThreatObject* p_threat = (p_threats +t);
		if(p_threat)
		{
			ret=p_threat->LoadImg("GreenPlane.png");
	if(ret== false)
	{
		return 0;
	}
	

		int rand_y = rand()%400;
		if(rand_y > SCREEN_HEIGHT -200)
		{
			rand_y = SCREEN_HEIGHT*0.3;
		}
		
	

	p_threat->SetRect(SCREEN_WIDTH +t*400, rand_y);
	p_threat->set_x_val(3);

	AmoObject* p_amo = new AmoObject();
	p_threat->InitAmo(p_amo);
	}
		}
	
	unsigned int die_number= 0;
	unsigned int mark_value = 0;
  while (!is_quit) 
  {
    while (SDL_PollEvent(&g_even)) 
    {
      if (g_even.type == SDL_QUIT)
      {
        is_quit = true;
        break;
      }
	  plane_object.HandleInputAction(g_even);
	  //g_sound_bullet
    }
	 //Apply background
	bkgn_x -=2;
	SDLComonFunc:: ApplySurface(g_bkground, g_screen,bkgn_x, 0);
	SDLComonFunc::ApplySurface(g_bkground,g_screen,bkgn_x+SCREEN_WIDTH,0);
	if(bkgn_x<=-SCREEN_WIDTH)
	{
		bkgn_x=0;
	}
	//Show Player power
	player_power.Render(g_screen);


  // Implement mainobject
	plane_object.HandleMove();
	plane_object.Show(g_screen);
	plane_object.MakeBullet(g_screen);
	//bonus 
	
			
	p_bonus->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
	p_bonus->Show(g_screen);
	
	//kiểm tra va chạm giữa main và heart
	bool is_col2= SDLComonFunc::CheckCollision(plane_object.GetRect(), p_bonus->GetRect());
	if(is_col2 )
	{   		
		p_bonus->Reset(SCREEN_WIDTH);
		mark_value+=5;
		
	
	
	if(SDL_Flip(g_screen) == -1)
	{
	delete [] p_bonus;
	delete [] p_threats;
		SDLComonFunc::CleanUp();
		SDL_Quit();
		return 0;
	}
	}
	// Run Threat
	for(int tt=0;tt<NUM_THREATS;tt++)
	{
		ThreatObject* p_threat =(p_threats+tt);
		if(p_threat)
		{
	p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
	p_threat->Show(g_screen);
	p_threat->MakeAmo(g_screen,SCREEN_WIDTH,SCREEN_HEIGHT);
	if (mark_value>= 0 && mark_value <= 75) {
						p_threat->set_x_val(SPEED_THREAT);
					}
					else if (mark_value > 75 && mark_value <= 150) {
						p_threat->set_x_val(SPEED_THREAT1);
					}
					else if (mark_value > 150 && mark_value <= 300) {
						p_threat->set_x_val(SPEED_THREAT2);
					}
					else p_threat->set_x_val(SPEED_THREAT3);
	
	// kiểm tra va chạm giữa đạn threat và main
	bool is_col1=false;
	std::vector<AmoObject*> amo_arr = p_threat->GetAmoList();
					for (int am = 0; am < amo_arr.size(); am++)
					{
						AmoObject* p_amo = amo_arr.at(am);
						if (p_amo)
						{
							is_col1 = SDLComonFunc::CheckCollision(p_amo->GetRect(), plane_object.GetRect());
							if (is_col1 == true)
							{
								p_threat->ResetAmo(p_amo);
								break;
							}
						}
					}

	// kiểm tra va chạm giữa main và threats

	bool is_col = SDLComonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
					if (is_col1 || is_col)
					{
						for (int ex = 0; ex < 4; ex++)
						{
							int x_pos = (plane_object.GetRect().x + plane_object.GetRect().w*0.5) - EXP_WIDTH * 0.5;
							int y_Pos = (plane_object.GetRect().y + plane_object.GetRect().h*0.5) - EXP_HEIGHT * 0.5;

							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_Pos);
							exp_main.SHowEx(g_screen);
							SDL_Delay(50);
							//Update screen

							if (SDL_Flip(g_screen) == -1)
							{
								delete[] p_threats;
								SDLComonFunc::CleanUp();
								SDL_Quit();
								return 0;
							}
						}
						//Mix_PlayChannel(-1,g_sound_exp[1],0);	
						die_number++;
						if(die_number <= 2)
						{
							SDL_Delay(1000);
							plane_object.SetRect(POS_X_START_MAIN_OBJ,POS_Y_START_MAIN_OBJ);
							player_power.Decrease();
							player_power.Render(g_screen);

							if(SDL_Flip(g_screen)==-1)
							{
								delete [] p_threats;
								SDLComonFunc::CleanUp();
								SDL_Quit();
								return 0;
							}
						}
						else
						{
							if(MessageBox(NULL,L"GAME OVER!",L"Info",MB_OK)== IDOK)
						{
								delete [] p_threats;
								SDLComonFunc:: CleanUp();
								SDL_Quit();
								return 1;
						}
					}
				}
		// va chạm đạn của main vs threats
		std:: vector<AmoObject*>amo_list =plane_object.GetAmoList();
	for(int im = 0;im<amo_list.size();im++)
	{
		AmoObject* p_amo=amo_list.at(im);
		if(p_amo!=NULL)
		{
				
			bool ret_col =SDLComonFunc::CheckCollision(p_amo->GetRect(),p_threat->GetRect());
			if(ret_col)
			{
				mark_value++;
				p_threat->Reset(SCREEN_WIDTH +tt*VAL_OFFSET_START_POST_THREATS);
				plane_object.RemoveAmo(im);
				//Mix_PlayChannel(-1,g_sound_exp[0],0);
			}
	}
	}
		}
	}

	for(int i=0;i<plane_object.GetAmoList().size();i++)
	{	std::vector<AmoObject*>amo_list = plane_object.GetAmoList();
	AmoObject* p_amo =amo_list.at(i);
	if(p_amo!=NULL)
	{
		if(p_amo->get_is_move())
		{
			p_amo->HandleMove(SCREEN_WIDTH,SCREEN_WIDTH);
			p_amo->Show(g_screen);
		

		}
		else
		{
			if(p_amo!=NULL)
			{
				amo_list.erase(amo_list.begin()+i);
				plane_object.SetAmoList(amo_list);
				delete p_amo;
				p_amo=NULL;
			}
		}
	}
	}

	
	//Show time lên màn hình
	std::string str_time = "Time : ";
	Uint32 time_val = SDL_GetTicks()/1000;
	std::string str_val = std::to_string(time_val);
	str_time+=str_val;

	time_game.SetText(str_time);
	time_game.SetRect(SCREEN_WIDTH -200,10);
	time_game.CreateGameText(g_font_text,g_screen);

	//Show điểm lên màn hình
	std::string val_str_mark = std::to_string(mark_value);
	std::string strMark("Mark: ");
	strMark += val_str_mark;

	mark_game.SetText(strMark);
	mark_game.CreateGameText(g_font_text,g_screen);
	

	//update screen
    if ( SDL_Flip(g_screen) == -1)
	
    return 0;
  }
  delete [] p_threats;
  SDLComonFunc:: CleanUp();
  SDL_Quit();
  return 1;
}
  