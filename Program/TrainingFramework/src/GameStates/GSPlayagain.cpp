#include "GSPlayagain.h"
#include <GameStates\GSPlay.h>

GSPlayagain::GSPlayagain()
{

}


GSPlayagain::~GSPlayagain()
{
}



void GSPlayagain::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);


	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_again");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2+300, 300);
	button->SetSize(110, 110);
	button->SetRotation(180);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);


	texture = ResourceManagers::GetInstance()->GetTexture("button_Menu");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2-300, 300);
	button->SetSize(110, 110);
	button->SetRotation(180);
	button->SetOnClick([]() {
		
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);
	


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "Play AGAIN ?", TEXT_COLOR::PURPLE, 3.0);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 200, 120));
}

void GSPlayagain::Exit()
{
}


void GSPlayagain::Pause()
{

}

void GSPlayagain::Resume()
{

}


void GSPlayagain::HandleEvents()
{

}

void GSPlayagain::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPlayagain::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlayagain::HandleMouseEvents(int x, int y)
{
}

void GSPlayagain::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPlayagain::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
