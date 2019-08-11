#include "Application.h"
#include "GameStates/GameStateMachine.h"
#include "GameStates/GameStatebase.h"
#include "GameManager/SoundManager.h"

int Application::screenWidth = 1200;
int Application::screenHeight = 800;

Application::Application()
{
}


Application::~Application()
{
}


void Application::Init()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Intro);
}

void Application::Update(GLfloat deltaTime)
{
	GameStateMachine::GetInstance()->PerformStateChange();

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Draw();

}

void Application::HandleKeyEvent(unsigned char key, bool bIsPresseded)
{
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(key, bIsPresseded);

}

void Application::HandleTouchEvent(GLint x, GLint y, bool bIsPresseded)
{

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(x, y, bIsPresseded);
}

void Application::HandleMouseEvent(GLint x, GLint y)
{
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleMouseEvents(x, y);
}

void Application::Exit()
{
	exit(0);
}
