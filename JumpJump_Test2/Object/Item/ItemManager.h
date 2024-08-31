#pragma once
#include "DxLib.h"
#include "../../Util/Game.h"

#include <vector>
#include <memory>
#include <array>

class ItemBase;
class SpownItem;
class ObjectBase;
class Player;
class ObjectManager;
class CountGetItem;
class Time;

class ItemManager
{
public:
	ItemManager(Game::Stage stage, ObjectManager* pObjectManager);

	~ItemManager();

	void Init();
	void Update();
	void Draw();

	/// <summary>
	/// �A�C�e���̎擾���̒ǉ�
	/// </summary>
	void AddGetNum();

	// �A�C�e���̎擾���p�̃|�C���^�̎擾
	const std::shared_ptr<CountGetItem> GetCountItem()const { return m_pCountGetItem; }

	/// <summary>
	/// �N���A��Ԃ��ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsClear()const { return m_isClear; }

private:
	bool m_isSpown;		// �A�C�e�����o�������邩�ǂ���
	bool m_isClear;		// �N���A�������ǂ���
	ObjectManager* m_pObjectManager;	// �I�u�W�F�N�g�}�l�[�W���[�̃|�C���^
	std::shared_ptr<CountGetItem> m_pCountGetItem;	// �A�C�e���̎擾��
	std::shared_ptr<SpownItem> m_pSpown;	// �A�C�e���̏o��

};

