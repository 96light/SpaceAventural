#pragma once
#include "baseobject.h"

class Sprite2D : public BaseObject
{
private:
	std::string		m_Text;
	void			CaculateWorldMatrix();
	Vector2			m_Vec2DPos;
	Vector2			m_Size2D;

public:
	Sprite2D(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	Sprite2D(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, Vector4& color);
	~Sprite2D();

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

};

