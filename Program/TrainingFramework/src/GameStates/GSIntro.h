#pragma once
#include "gamestatebase.h"

class GSIntro :
	public GameStateBase
{
public:
	GSIntro();
	~GSIntro();

	void Init()override;
	void Exit()override;

	void Pause()override;
	void Resume()override;

	void HandleEvents()override;
	void HandleKeyEvents(int key, bool bIsPressed)override;
	void HandleTouchEvents(int x, int y, bool bIsPressed)override;
	void HandleMouseEvents(int x, int y) override;
	void Update(float deltaTime) override;
	void Draw()override;

private:
	std::shared_ptr<Sprite2D> m_logo;
	std::shared_ptr<Sprite2D> m_BackGround;
	float m_time;
};

