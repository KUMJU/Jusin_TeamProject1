#pragma once

#define		WINCX		800
#define		WINCY		600
#define		OUTLINE		100

#define		PI			3.14
#define     OBJ_NOEVENT 0
#define     OBJ_DEAD    1
#define		PURE		= 0

enum DIRECTION{DIR_LEFT, DIR_DOWN, DIR_RIGHT, DIR_UP, DIR_END};
enum OBJ_ID{OBJ_PLAYER, OBJ_MONSTER, OBJ_PLAYERBULLET,OBJ_MOSTERBULLET, OBJ_ITEM, OBJ_SKILL, OBJ_MOUSE, OBJ_END};
enum BULLETTYPE{BT_BASIC, BT_TWOWAY,BT_TRIPLE, BT_REF_BASIC, BT_REF_TWOWAY,BT_END};
enum SKILLTYPE{ST_WAVE,ST_SHIELD,ST_BOMB,ST_END};
enum PLAYERSTATE {PS_BASIC, PS_SUPERARMOR};

enum GAMESTATE {GS_PLAYING, GS_GAMEOVER};

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;


template<typename T>
void		Safe_Delete(T& Temp)
{
	if(Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct DeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if(Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

extern	HWND	g_hWnd;