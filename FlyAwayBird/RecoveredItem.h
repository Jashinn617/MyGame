#pragma once
#include <memory>

class WorldSprite;

using namespace std;

/// <summary>
/// ���W�p�A�C�e���N���X
/// </summary>
class RecoveredItem
{
public:
	RecoveredItem();
	~RecoveredItem();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:	// �ϐ�
	VECTOR m_pos;	// �ʒu
	int m_handle;	// �摜�̃n���h��
	/*�摜�̃T�C�Y*/
	int m_w;	// ��
	int m_h;	// �c

	float m_sinCount;	// �ړ��̍ۂ�Sin�J�E���g
	float m_sinPosY;	// �ʒu�̌v�Z�Ɏg��Sin

	shared_ptr<WorldSprite> m_pSprite;	// �X�v���C�g

private:	// �萔
	int kSize = 2;	// �摜�̑S�̓I�ȃT�C�Y

	static constexpr float kRadius = 0.8f;	// ���a
	static constexpr float kUpPosY = 2.0f;	// ��ɂ���Ƃ��̈ʒu
	static constexpr float kDownPosY = 1.0f;	// ���ɂ���Ƃ��̈ʒu

	static constexpr float kSinSpeed = 0.05f;	// �ړ��X�s�[�h
	static constexpr float kMoveSwing = 0.01f;	// �ړ���
};

