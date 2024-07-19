#pragma once

class Input;
class Player;
class StageTest;

class Camera
{
public:

	Camera();
	~Camera();

	void Init();
	void Update(const Input& input, const Player& player, const StageTest& stage);

	const VECTOR& GetPos()const { return m_pos; }
	const VECTOR& GetTarget()const { return m_targetPos; }

private:	// �ϐ�
	float m_angle;		// �����p�x
	VECTOR m_pos;		// ���W
	VECTOR m_targetPos;	// �^�[�Q�b�g���W
};

