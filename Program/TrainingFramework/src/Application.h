#pragma once
#include "Helper/Singleton.h"
#include "GameConfig.h"


class Application : public CSingleton<Application>
{
public:
	Application();
	~Application();
	void		Init();
	void		Update( GLfloat deltaTime);
	void		Render();
	void		HandleKeyEvent(unsigned char key, bool bIsPresseded);
	void		HandleTouchEvent(GLint x, GLint y, bool bIsPresseded);
	void		HandleMouseEvent(GLint x, GLint y);
	void		Exit();

	static int screenWidth;
	static int screenHeight;
private:

};

