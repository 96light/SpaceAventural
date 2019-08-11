/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSSetting.h"
#include "GameStatebase.h"
#include"GSPlayagain.h"
#include "GSSetting1.h"
#include "GSSetting2.h"
#include "GSSetting3.h"
#include"GSPlayagain1.h"
std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case STATE_INVALID:
		break;
	case STATE_Intro:
		gs = std::make_shared<GSIntro>();
		break;
	case STATE_Menu:
		gs = std::make_shared<GSMenu>();
		break;
	case STATE_Play:
		gs = std::make_shared<GSPlay>();
		break;
	case STATE_Setting:
		gs = std::make_shared<GSSetting>(); 
		break;
	case STATE_Playagain:
	{   
		gs = std::make_shared<GSPlayagain>();
			break;
	}
	case STATE_Setting1:
		gs = std::make_shared<GSSetting1>();
		break;
	case STATE_Setting2:
		gs = std::make_shared<GSSetting2>();
		break;
	case STATE_Setting3:
		gs = std::make_shared<GSSetting3>();
		break;
	case STATE_Playagain1:
	{
		gs = std::make_shared<GSPlayagain1>();
		break;
	}
	default:
		break;
	}
	return gs;
}
