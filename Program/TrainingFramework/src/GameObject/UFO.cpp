#include "UFO.h"
#include "GameManager/ResourceManagers.h"
#include <GameStates\GSPlay.h>
#include<fstream>
using namespace std;
UFO::UFO(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_active = false;
	m_MaxCooldown = 0.6;
	m_Cooldown = 0.5;
	m_speed = 0;
	m_MaxSpeed = 500;
	m_Heal = 100;
	m_Damage = 20;
	m_Explosive = false;
	m_SizeCollider = 200;

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

UFO::~UFO()
{
}


void UFO::Update(float deltaTime){
	if (!m_active)
		return;

	if (m_Heal <= 0 || m_Explosive)
 	 {  if(sfx==1){
		SoundManager::GetInstance()->PlaySound("win");
	}
		m_Explosive = true;
		GSPlay::m_score+10;
		return;
	}

	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltaTime;
	}

	Vector2 pos = Get2DPosition();
	//pos.y = pos.y + m_speed * deltaTime;
	pos.x = pos.x + m_speed * deltaTime;
	Set2DPosition(pos);

	if (pos.x > Application::screenWidth)
		m_active = false;
}

bool UFO::CanShoot()
{
	return (m_Cooldown <= 0);
}

void UFO::Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet)
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

void UFO::Shoot2(std::vector<std::shared_ptr<Bullet2>>& listBullet)
{
	m_Cooldown = m_MaxCooldown;
	for (auto bullet : listBullet)
	{
		if (!bullet->IsActive())
		{
			bullet->SetActive(true);
			bullet->Set2DPosition(Get2DPosition());
			bullet->SetSpeed(-500);
			bullet->SetType(BULLET_TYPE2::Enermy);
			return;
		}
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");

	std::shared_ptr<Bullet2> bullet = std::make_shared<Bullet2>(model, shader, texture);
	bullet->SetSize(20, 20);
	bullet->Set2DPosition(Get2DPosition());
	bullet->SetSpeed(-500);
	bullet->SetType(BULLET_TYPE2::Enermy);
	listBullet.push_back(bullet);
}

void UFO::Shoot3(std::vector<std::shared_ptr<Bullet3>>& listBullet)
{
	m_Cooldown = m_MaxCooldown;
	for (auto bullet : listBullet)
	{
		if (!bullet->IsActive())
		{
			bullet->SetActive(true);
			bullet->Set2DPosition(Get2DPosition());
			bullet->SetSpeed(-500);
			bullet->SetType(BULLET_TYPE3::Enermy);
			return;
		}
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");

	std::shared_ptr<Bullet3> bullet = std::make_shared<Bullet3>(model, shader, texture);
	bullet->SetSize(20, 20);
	bullet->Set2DPosition(Get2DPosition());
	bullet->SetSpeed(-500);
	bullet->SetType(BULLET_TYPE3::Enermy);
	listBullet.push_back(bullet);
}
float UFO::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}


void UFO::CheckCollider(std::vector<std::shared_ptr<Bullet>>& listBullet)
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


bool UFO::IsActive()
{
	return m_active;
}

void UFO::SetActive(bool status)
{
	m_active = status;
	m_Explosive = false;
	m_Heal = 500;
}

void UFO::SetDamage(float damage)
{
	m_Damage = damage;
}

float UFO::GetDamage()
{
	return m_Damage;
}

void UFO::Explosive()
{
	m_Explosive = true;
}

bool UFO::IsExplosive()
{
	return m_Explosive;
}


void UFO::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float UFO::GetColliderSize()
{
	return m_SizeCollider;
}