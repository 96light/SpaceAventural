#include "SpriteSheet.h"
#include "Application.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"

void SpriteSheet::CaculateWorldMatrix()
{
	Matrix m_Sc, m_Rx, m_Ry, m_Rz, m_T;
	m_Sc.SetScale(m_Vec3Scale);
	GLfloat tempX = (GLfloat)(m_Vec3Rotation.x * PI * 2 / MAX_DEGREE);
	m_Rx.SetRotationX(tempX);
	GLfloat tempY = (GLfloat)(m_Vec3Rotation.y * PI * 2 / MAX_DEGREE);
	m_Ry.SetRotationY(tempY);
	GLfloat tempZ = (GLfloat)(m_Vec3Rotation.z * PI * 2 / MAX_DEGREE);
	m_Rz.SetRotationZ(tempZ);
	m_T.SetTranslation(m_Vec3Position);

	m_WorldMat = m_Sc * m_Rz * m_Rx * m_Ry * m_T;
}

SpriteSheet::SpriteSheet(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime)
	: BaseObject()
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;
	m_Vec3Position = Vector3(0, 0, 0);
	Vector2 size = m_pTexture->GetTextureSize();
	m_Size2D.y = size.y;
	m_Size2D.x = size.x;
	m_Vec3Scale = Vector3(m_Size2D.x / Application::screenWidth, m_Size2D.y / Application::screenHeight, 1);

	//animation
	m_Timer = 0.0f;
	m_StartPos = start;
	m_EndPos = end;
	m_CurrentPos = m_StartPos;
	m_data.x = (int)(pictureSize.x / spriteSize.x);
	m_data.y = (int)(pictureSize.y / spriteSize.y);
	m_Delay = lengthTime / m_EndPos - m_StartPos;
}


SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::Init()
{
	CaculateWorldMatrix();
}

void SpriteSheet::Draw()
{
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_WorldMat;//* m_pCamera->GetLookAtCamera();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}
	else
	{
		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
		if (iTempShaderVaribleGLID != -1)
			glUniform4f(iTempShaderVaribleGLID, m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*) "a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);


	GLint u_data = m_pShader->GetUniformLocation((char*)"u_data");
	if (u_data != -1)
	{
		glUniform2fv(u_data, 1, (GLfloat*)(&m_data));
	}


	GLint u_pos = m_pShader->GetUniformLocation((char*)"u_pos");
	if (u_pos != -1)
	{
		int column = m_CurrentPos % (int)m_data.x;
		int row = m_CurrentPos / (int)m_data.x;
		Vector2 data(column, row);
		glUniform2fv(u_pos, 1, (GLfloat*)(&data));
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);



	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void SpriteSheet::Update(GLfloat deltatime)
{
	if (m_CurrentPos == (m_EndPos) && m_Timer > m_Delay)
	{
		m_CurrentPos = m_StartPos;
		m_Timer = -0.0f;
		m_isDone = true;
	}
	else if (m_Timer > m_Delay)
	{
		m_CurrentPos++;
		m_Timer = 0.0f;
	}
	else
	{
		m_Timer += deltatime;
	}
}



void SpriteSheet::SetText(std::string text)
{
	m_Text = text;
}

std::string SpriteSheet::GetText()
{
	return m_Text;
}

void SpriteSheet::Set2DPosition(GLfloat width, GLfloat height)
{
	m_Vec2DPos.x = width;
	m_Vec2DPos.y = height;

	float xx = (2.0 * m_Vec2DPos.x) / Application::screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / Application::screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);

	CaculateWorldMatrix();
}

void SpriteSheet::Set2DPosition(Vector2 pos)
{
	m_Vec2DPos = pos;

	float xx = (2.0 * m_Vec2DPos.x) / Application::screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / Application::screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);

	CaculateWorldMatrix();
}

const Vector2& SpriteSheet::Get2DPosition()
{
	return m_Vec2DPos;
}


void SpriteSheet::SetSize(GLint width, GLint height)
{
	m_Size2D.x = width;
	m_Size2D.y = height;
	m_Vec3Scale = Vector3(m_Size2D.x / Application::screenWidth, m_Size2D.y / Application::screenHeight, 1);
	CaculateWorldMatrix();
}

void SpriteSheet::SetSize(Vector2 size)
{
	m_Size2D = size;
	m_Vec3Scale = Vector3(m_Size2D.x / Application::screenWidth, m_Size2D.y / Application::screenHeight, 1);
	CaculateWorldMatrix();
}

const Vector2& SpriteSheet::GetSize()
{
	return m_Size2D;
}

void SpriteSheet::SetRotation(GLfloat angel)
{
	m_Vec3Rotation.z = angel;
	CaculateWorldMatrix();

}

bool SpriteSheet::IsDone()
{
	return m_isDone;
}

void SpriteSheet::StartAnimation()
{
	m_CurrentPos = m_StartPos;
	m_isDone = false;
}
