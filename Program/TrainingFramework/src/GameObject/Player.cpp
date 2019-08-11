#include "Player.h"
#include "GameManager/ResourceManagers.h"
#include<fstream>
using namespace std;
Player::Player(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	ifstream FileIn;

	FileIn.open("config.txt", ios_base::in);

	if (FileIn.fail() == true)
	{
		cout << "\nFile cua ban khong ton tai";
	}
	int x;
	
	FileIn >> x;
	sfx = x;
	m_TargetPosition = Vector2(0, 0);
	m_MaxCooldown = 0.1;
	m_Cooldown = 0.0;
	m_speed = 250;
	m_MaxSpeed = 500;
	m_Heal = 100;
	m_SizeCollider = 15;
	m_isAlive = true;
}

Player::~Player()
{
}


void Player::MoveToPossition(Vector2 pos)
{
	m_TargetPosition = pos;
}

void Player::Update(GLfloat deltatime)
{
	if (!m_isAlive)
		return;

	if (m_Heal <= 0)
	{ if(sfx==1){
		SoundManager::GetInstance()->PlaySound("explosive_2");
	}
		m_isAlive = false;
		return;
	}
	
	if (m_Cooldown > 0)
	{
		m_Cooldown -= deltatime;
	}

	Vector2 pos = Get2DPosition();

	if (pos.x < m_TargetPosition.x)
	{
		pos.x += m_speed * deltatime;
		if (pos.x > m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.x > m_TargetPosition.x)
	{
		pos.x -= m_speed * deltatime;
		if (pos.x < m_TargetPosition.x)
			pos.x = m_TargetPosition.x;
	}

	if (pos.y < m_TargetPosition.y)
	{
		pos.y += m_speed * deltatime;
		if (pos.y > m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	if (pos.y > m_TargetPosition.y)
	{
		pos.y -= m_speed * deltatime;
		if (pos.y < m_TargetPosition.y)
			pos.y = m_TargetPosition.y;
	}

	Set2DPosition(pos);
}

bool Player::CanShoot()
{
	return (m_Cooldown <= 0);
}

void Player::Shoot(std::vector<std::shared_ptr<Bullet>>& listBullet,int s)
{if (sfx ==1){
	SoundManager::GetInstance()->PlaySound("fire");
}

   m_Cooldown = m_MaxCooldown;
	for (auto bullet : listBullet)
	{
		if (!bullet->IsActive())
		{
			bullet->SetActive(true);
			bullet->Set2DPosition(Get2DPosition());
			bullet->SetSpeed(500);
			bullet->SetType(BULLET_TYPE::Player);
			return;
		}
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bullet");

	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
	bullet->SetSize(20, 20);
	bullet->Set2DPosition(Get2DPosition());
	bullet->SetSpeed(500);
	bullet->SetType(BULLET_TYPE::Player);

	listBullet.push_back(bullet);


}

float Player::distance(Vector2 pos, Vector2 target)
{
	return sqrt((pos.x - target.x) * (pos.x - target.x) + (pos.y - target.y) * (pos.y - target.y));
}

void Player::CheckCollider(std::vector<std::shared_ptr<Bullet>>& listBullet, std::vector<std::shared_ptr<Bullet2>>& listBullet2, std::vector<std::shared_ptr<Bullet3>>& listBullet3, std::vector<std::shared_ptr<Enermy>> listEnermy)
{
	Vector2 pos = Get2DPosition();
	for (auto enermy : listEnermy)
	{
		if (enermy->IsActive())
		{
			if (distance(pos, enermy->Get2DPosition()) < m_SizeCollider + enermy->GetColliderSize())
			{
				enermy->Explosive();
				m_Heal -= enermy->GetDamage();
			}
		}
	}

	for (auto bullet : listBullet)
	{
		if (bullet->IsActive() && bullet->GetType() == BULLET_TYPE::Enermy)
		{
			if (distance(pos, bullet->Get2DPosition()) < m_SizeCollider + bullet->GetColliderSize())
			{
				bullet->SetActive(false);
				m_Heal -= bullet->GetDamage();
			}
		}
	}

	for (auto bullet : listBullet3)
	{
		if (bullet->IsActive() && bullet->GetType() == BULLET_TYPE3::Enermy)
		{
			if (distance(pos, bullet->Get2DPosition()) < m_SizeCollider + bullet->GetColliderSize())
			{
				bullet->SetActive(false);
				m_Heal -= bullet->GetDamage();
			}
		}
	}

	for (auto bullet : listBullet3)
	{
		if (bullet->IsActive() && bullet->GetType() == BULLET_TYPE3::Enermy)
		{
			if (distance(pos, bullet->Get2DPosition()) < m_SizeCollider + bullet->GetColliderSize())
			{
				bullet->SetActive(false);
				m_Heal -= bullet->GetDamage();
			}
		}
	}
}

void Player::CheckCollider2(std::vector<std::shared_ptr<Meteor>> listMeteor)
{
	Vector2 pos = Get2DPosition();
	for (auto meteor : listMeteor)
	{
		if (meteor->IsActive())
		{
			if (distance(pos, meteor->Get2DPosition()) < m_SizeCollider + meteor->GetColliderSize())
			{
				meteor->Explosive();
				m_Heal -= meteor->GetDamage();
			}
		}
	}
}

void Player::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Player::GetColliderSize()
{
	return m_SizeCollider;
}

int Player::GetHeal()
{
	return m_Heal;
}

bool Player::IsAlive()
{
	return m_isAlive;
}
