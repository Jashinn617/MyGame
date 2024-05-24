#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "Util/Input.h"

Player::Player():
	m_pos{0.0f,0.0f,0.0f},
	m_targetDir{1.0f,0.0f,0.0f},
	m_angle(0.0f),
	m_currentJunpPower(0.0f),
	m_modelHandle(-1)
{
	// モデルのロード
	m_modelHandle = MV1LoadModel("Data/Model/Player/Knight.mv1");
}

Player::~Player()
{
	// モデルのデリート
	MV1DeleteModel(m_modelHandle);
}

void Player::Init()
{
	

}

void Player::Update(const Input& input, const Camera& camera)
{
}

void Player::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void Player::End()
{
}