#pragma once

#include <memory>

class Player;
class Camera
{
public:
	// ���ǂ̃}�b�v�ɂ��邩
	enum ScrollPattern
	{
		// ���X�N���[��
		kHorizontal,
		kHorizontal2,
		// �c�X�N���[��
		kVertical,
		// �c���X�N���[��
		kMixture
	};

public:
	Camera();
	~Camera();

	// ������
	void Init();
	// ���X�N���[��
	int GetScrollX();
	// �c�X�N���[��
	int GetScrollY();
	/*�}�b�v�̑傫���̌���*/
	void StartHorizon() { m_scrollPattern = kHorizontal; }
	void StartHorizon2() { m_scrollPattern = kHorizontal2; }
	void StartVertical() { m_scrollPattern = kVertical; }
	void StartMixture() { m_scrollPattern = kMixture; }
	/*�}�b�v�T�C�Y�̎擾*/
	int GetMapWidth()const { return m_mapWidth; }
	int GetMapHeight()const { return m_mapHeight; }

	// �v���C���[�̃|�C���^��ݒ肷��
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }


private:
	// �v���C���[�̃|�C���^
	std::shared_ptr<Player> m_pPlayer;
	// ���݂̃}�b�v���
	ScrollPattern m_scrollPattern;
	/*���݂̃}�b�v�̃T�C�Y*/
	// ��
	int m_mapWidth;
	// �c
	int m_mapHeight;

};

