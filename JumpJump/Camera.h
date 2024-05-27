#pragma once

class Input;
class Player;
class StageTest;

class Camera
{
public:
	void Init();
	void Update(const Input& input, const Player& player, const StageTest& stage);

	const VECTOR& GetPos()const { return m_pos; }
	const VECTOR& GetTarget()const { return m_targetPos; }

private:	// �ϐ�
	float m_angle;		// �����p�x
	VECTOR m_pos;		// ���W
	VECTOR m_targetPos;	// �^�[�Q�b�g���W

private:	// �萔
	static constexpr float kSpeed = 0.1f;			// ��]���x
	static constexpr float kTargetH = 8.0f;		// �^�[�Q�b�g�̍��W���璍���_�܂ł̍���
	static constexpr float kStartTargetDir = 45.0f;	// �^�[�Q�b�g�Ƃ̏����̋���
	static constexpr float kColSize = 50.0f;		// �J�������̂̓����蔻��̃T�C�Y

};

