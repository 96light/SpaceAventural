#include "Enermy.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>
#include<fstream>
using namespace std;
Enermy::Enermy(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_active = false;
	m_MaxCooldown = 0.4;
	m_Cooldown = 0.0;
	m_speed = 250;
	m_MaxSpeed = 500;
	m_Heal = 50;
	m_Damage = 20;
	m_Explosive = false;
	m_SizeCollider = 20;
	
	ifstream FileIn;

	FileIn.open("config.txt", ios_base::in);

	if (FileIn.fail() == true)
	{
		cout << "\nFile cua ban khong ton tai";
	}
	int x;

	FileIn >> x;
	sfx = x;
}

Enermy::~Enermy()
{
}


void Enermy::Update(float deltaTime)
{
	if (!m_active)
		return;

	if (m_Heal <= 0 || m_Explosive)
	{ if(sfx==1){
		SoundManager::GetInstance()->PlaySound("explosive");
	}
		m_Explosive = true;
		GSPlay::m_score ++;
		return;
	}

	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltaTime;
	}

	Vector2 pos = Get2DPosition();
	pos.y = pos.y + m_speed * deltaTime;
	Set2DPosition(pos);

	if (pos.y > Application::screenHeight)
		m_active = false;
}

bool Enermy::CanShoot()
{
	return (m_Cooldown <= 0);
}

void Enermy::Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet)
{
	m_Cooldown = m_MaxCooldown;
	for (auto bullet : listBullet)
	{
		if (!bullet->IsActive())
		{
			bullet->SetActive(true);
			bullet->Set2DPosition(Get2DPosition());
			bullet->SetSpeed(-500);
			bullet->SetType(BULLET_TYPE::Enermy);
			return;
		}
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
	bullet->SetSize(20, 20);
	bullet->Set2DPosition(Get2DPosition());
	bullet->SetSpeed(-500);
	bullet->SetType(BULLET_TYPE::Enermy);
	listBullet.push_back(bullet);
}

float Enermy::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}


void Enermy::CheckCollider(std::vector<std::shared_ptr<Bullet>>& listBullet)
{
	Vector2 pos = Get2DPosition();

	for (auto bullet : listBullet)
	{
		if (bullet->IsActive() && bullet->GetType() == BULLET_TYPE::Player)
		{
			if (distance(pos, bullet->Get2DPosition()) < m_SizeCollider + bullet->GetColliderSize())
			{
				bullet->SetActive(false);
				m_Heal -= bullet->GetDamage();
				if (m_Heal <= 0)
					return;
			}
		}
	}
}


bool Enermy::IsActive()
{
	return m_active;
}

void Enermy::SetActive(bool status)
{
	m_active = status;
	m_Explosive = false;
	m_Heal = 10;
}

void Enermy::SetDamage(float damage)
{
	m_Damage = damage;
}

float Enermy::GetDamage()
{
	return m_Damage;
}

void Enermy::Explosive()
{
	m_Explosive = true;
}

bool Enermy::IsExplosive()
{
	return m_Explosive;
}


void Enermy::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Enermy::GetColliderSize()
{
	return m_SizeCollider;
}