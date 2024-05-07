#pragma once
#include <memory>

class WorldSprite;
class Player;

using namespace std;

/// <summary>
/// ���W�p�A�C�e���N���X
/// </summary>
class RecoveredItem
{
public:
	RecoveredItem(shared_ptr<Player> pPlayer);
	~RecoveredItem();

	/// <summary>
	/// ������
	/// </summary>
	void Init(float x, float z);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	
	void CollisionToPlayer(VECTOR pVec, float pRad);

	/// <summary>
	/// ���݂��Ă��邩�ǂ���
	/// </summary>
	/// <returns>���݃t���O</returns>
	bool IsExist() { return m_isExist; }

private:	// �ϐ�
	VECTOR m_pos;	// �ʒu
	int m_modelHandle;	// ���f���n���h��
	int m_chatchSeHandle;	// �A�C�e���擾����SE
	/*�摜�̃T�C�Y*/
	int m_w;	// ��
	int m_h;	// �c

	bool m_isExist;	// ���݃t���O

	float m_sinCount;	// �ړ��̍ۂ�Sin�J�E���g
	float m_sinPosY;	// �ʒu�̌v�Z�Ɏg��Sin

	shared_ptr<Player> m_pPlayer;

private:	// �萔
	static constexpr float kSize = 2;	// �摜�̑S�̓I�ȃT�C�Y

	static constexpr float kRadius = 0.8f;	// ���a
	static constexpr float kUpPosY = 2.0f;	// ��ɂ���Ƃ��̈ʒu
	static constexpr float kDownPosY = 1.0f;	// ���ɂ���Ƃ��̈ʒu
	static constexpr float kScale = 1.5f;			// �g�嗦

	static constexpr float kSinSpeed = 0.05f;	// �ړ��X�s�[�h
	static constexpr float kMoveSwing = 0.01f;	// �ړ���
	static constexpr int kSeVolume = 130;		// SE�̉���
};

