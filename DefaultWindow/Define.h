#pragma once

#define		WINCX		800
#define		WINCY		600
#define		OUTLINE		100


#define     OBJ_NOEVENT 0
#define     OBJ_DEAD    1
#define		PURE		= 0

enum DIRECTION{DIR_LEFT, DIR_DOWN, DIR_RIGHT, DIR_UP, DIR_END};
enum OBJ_ID{OBJ_PLAYER, OBJ_PLAYERBULLET,OBJ_MOSTERBULLET, OBJ_MONSTER, OBJ_ITEM, OBJ_SKILL, OBJ_END};
enum BULLETTYPE{BT_BASIC, BT_TWOWAY,BT_TRIPLE,BT_END};
enum SKILLTYPE{ST_WAVE,ST_SHIELD,ST_BOMB,ST_END};


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