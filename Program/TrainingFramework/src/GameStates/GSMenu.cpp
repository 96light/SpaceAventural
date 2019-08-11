#include "GSMenu.h"
#include<fstream>
using namespace std;
GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");
	
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);


	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 300);
	button->SetSize(100, 100);
	button	->SetRotation(180);
	button->SetOnClick([]() {
		
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button); 


		texture = ResourceManagers::GetInstance()->GetTexture("button_setting");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 500);
	button->SetSize(110, 110);
	button->SetRotation(180);
	button->SetOnClick([]() {
		
		ifstream FileIn;
		FileIn.open("config.txt", ios_base::in);

		
		int x;
		int y;
		FileIn >> x;
		FileIn >> y;

		//bgm = y;

		FileIn.close();
		if (x == 1 && y == 1) {
			Sleep(500);
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting);
		}
		else if (x == 1 && y == 0) {
			Sleep(500);
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting1);
		}
		else if (x == 0 && y == 1) {
			Sleep(500);
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting2);
		}
		else if (x == 0 && y == 0)

		{
			Sleep(500);
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting3);
		}
		});
	m_listButton.push_back(button);
	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 700);
	button->SetSize(110, 110);
	button->SetRotation(180);
	button->SetOnClick([]() {
		Sleep(500);
		exit(0);
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "SPACE ADVEVTURE", TEXT_COLOR::PURPLE, 3.0);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2-300, 120));

	
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::HandleMouseEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
