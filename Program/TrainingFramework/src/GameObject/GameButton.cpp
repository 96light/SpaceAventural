#include "GameButton.h"


GameButton::GameButton(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_pBtClick = nullptr;
	m_isHandle = false;
}

GameButton::~GameButton()
{
}

void GameButton::SetOnClick(void(*pBtClickFun)())
{
	m_pBtClick = pBtClickFun;
}

void GameButton::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	m_isHandle = false;
	if ((x > Get2DPosition().x - GetSize().x / 2) && (x < Get2DPosition().x + GetSize().x / 2) && (y > Get2DPosition().y - GetSize().y / 2) && (y < Get2DPosition().y + GetSize().y / 2))
	{
		m_pBtClick();
		m_isHandle = true;
	}
}

bool GameButton::IsHandle()
{
	return m_isHandle;
}
