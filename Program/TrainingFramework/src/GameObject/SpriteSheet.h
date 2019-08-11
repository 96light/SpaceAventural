#pragma once
#include "baseobject.h"

class SpriteSheet : public BaseObject
{
private:
	std::string		m_Text;
	void			CaculateWorldMatrix();
	Vector2			m_Vec2DPos;
	Vector2			m_Size2D;
	Vector2			m_data;
	bool			m_isDone;
	int				m_CurrentPos;
	int				m_StartPos;
	int				m_EndPos;
	float			m_Delay;
	float			m_Timer;

public:
	SpriteSheet(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime = 1.0);
	~SpriteSheet();

	void		Init() override;
	void		Draw() final;
	void		Update(GLfloat deltatime) override;

	void		SetText(std::string text);
	std::string	GetText();

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);

	const Vector2&	Get2DPosition() ;

	void		SetSize(GLint width, GLint height);
	void		SetSize(Vector2 size);

	const Vector2& GetSize();

	void		SetRotation(GLfloat angel);

	bool		IsDone();
	void		StartAnimation();

};

