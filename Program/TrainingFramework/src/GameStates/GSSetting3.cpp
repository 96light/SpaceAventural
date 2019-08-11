#include "GSSetting3.h"
#include<fstream>
using namespace std;
GSSetting3::GSSetting3()
{

}


GSSetting3::~GSSetting3()
{
}



void GSSetting3::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("button_quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2 + 400, 700);
	button->SetSize(110, 110);
	button->SetRotation(180);
	button->SetOnClick([]() {
		Sleep(500);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("button_bgoff");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 300);
	button->SetSize(110, 110);
	//button->SetRotation(180);
	button->SetOnClick([]() {
		
		int x;
		int y;
		// ====================== GHI FILE ======================
		ofstream FileOut;
		FileOut.open("config.txt", ios_base::out);
		FileOut << 0 << " ";
		FileOut << 1;
		FileOut.close();
		Sleep(500);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting2);
		});
	m_listButton.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("button_sfoff");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 700);
	button->SetSize(110, 110);
	button->SetRotation(180);
	button->SetOnClick([]() {
		
		int x;
		int y;
		// ====================== GHI FILE ======================
		ofstream FileOut;
		FileOut.open("config.txt", ios_base::out);
		FileOut << 1 << " ";
		FileOut << 0;
		Sleep(500);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting1);
		FileOut.close();
		});
	m_listButton.push_back(button);
	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "SETTING", TEXT_COLOR::PURPLE, 3.0);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 300, 120));
}

void GSSetting3::Exit()
{
}


void GSSetting3::Pause()
{

}

void GSSetting3::Resume()
{

}


void GSSetting3::HandleEvents()
{

}

void GSSetting3::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSSetting3::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSSetting3::HandleMouseEvents(int x, int y)
{
}

void GSSetting3::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSSetting3::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
