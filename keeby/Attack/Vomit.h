#pragma once
#include"../util/Vec2.h"
#include "../util/Rect.h"

#include <memory>

class Camera;
class Player;
class Vomit
{

public:
	Vomit();
	~Vomit();

	// ������
	void Init();
	// �`��
	void Draw();
	// �X�V
	void Update();
	// ��`���̎擾
	Rect GetRect();

	/*�����蔻��̎擾*/
	float GetLeft()const;
	float GetTop() const;
	float GetRight() const;
	float GetBottom()const;

	// �v���C���[�̍����ɒe���o��������
	void PutBulletLeft();
	// �v���C���[�̉E���ɒe���o��������
	void PutBulletRight();
	// ���݂�����
	void FalseExist() { m_isExist = false; }
	// �X�s�[�h��ύX����
	void SetSpeed(int speed) { m_speed = speed; }

	// �J�����̃|�C���^��ݒ肷��
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }
	// �v���C���[�̃|�C���^��ݒ肷��
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	// �e�����݂��Ă��邩�ǂ���
	bool IsExsist()const { return m_isExist; }

private:
	// �O���t�B�b�N
	int m_bulletHandle;
	// �O���t�B�b�N�̃T�C�Y
	int m_w;
	int m_h;
	// �e�̃X�s�[�h
	int m_speed;
	// �ʒu
	Vec2 m_pos;
	// �e�����݂��邩�ǂ����̃t���O
	bool m_isExist;
	// �����蔻��̋�`
	Rect m_colRect;

	// �X�N���[���ʂ̎擾�p��Camera�N���X�̃|�C���^
	std::shared_ptr<Camera> m_pCamera;
	// �v���C���[�̃|�C���^
	std::shared_ptr<Player> m_pPlayer;

};

