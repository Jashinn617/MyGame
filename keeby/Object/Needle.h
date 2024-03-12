#pragma once
#include <memory>
#include "../util/Vec2.h"
#include "../util/Rect.h"

class Camera;
class Player;
class Needle
{
public:
	Needle();
	~Needle();

	// ������
	// �����ʒu��ݒ肷�邽�߂̈�����n���Ă���
	void Init(float x, float y, float angle);
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ��`���̎擾
	Rect GetRect();
	// �����蔻��̎擾
	float GetLeft()const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom()const;
	// �v���C���[�Ƃ̓����蔻��
	void PlayerCollision();
	/*�|�C���^�̐ݒ�*/
	// �J����
	void SetCamera(std::shared_ptr<Camera> pCamera) { m_pCamera = pCamera; }
	// �v���C���[
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
private:
	/*�|�C���^�̎擾*/
	// �J����
	std::shared_ptr<Camera> m_pCamera;
	// �v���C���[
	std::shared_ptr<Player> m_pPlayer;

	// ���W
	Vec2 m_pos;
	// �X�N���[���p�̍��W
	int m_x;
	int m_y;
	// �T�C�Y
	int m_w;
	int m_h;
	// �����蔻��p�̋�`
	Rect m_colRect;

	/*�O���t�B�b�N*/
	int m_handle;

	// �p�x
	float m_angle;
};

