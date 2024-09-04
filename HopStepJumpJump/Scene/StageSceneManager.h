#pragma once
#include "../Util/Game.h"

#include <memory>
#include <vector>
#include <array>
#include <functional>

class Input;
class ObjectManager;
class CountTime;
class Ranking;
class Time;

class StageSceneManager
{
public:
	// �����N
	enum class Rank
	{
		S,
		A,
		B,
		C,
		RankNum,
	};
public:
	StageSceneManager(Game::Stage stageKind);
	virtual ~StageSceneManager();

	void Init();

	void Update(Input& input);
	void Draw();

	void SetGameClear();

	/// <summary>
	/// �X�e�[�W�̎擾
	/// </summary>
	/// <returns>�X�e�[�W�̎��</returns>
	Game::Stage GetStageKind() const { return m_stageKind; }
	const std::shared_ptr<ObjectManager> GetObjectManager() { return m_pObjectManager; }
	/// <summary>
	/// �Q�[���N���A���Ԃ̎擾
	/// </summary>
	/// <returns></returns>
	int GetGameClearTime() const{return m_clearTime; }

	/// <summary>
	/// �Q�[���N���A���ǂ���
	/// </summary>
	/// <returns></returns>
	bool IsGameClear()const { return m_isGameClear; }

private:	// �֐�
	void ClearUpdate();
	void ClearDraw();

	void ImageLoad();
	void ImageDelete();

	void TextDraw();
	void TimeDraw();
	void RankingDraw();
	void RankDraw();
	void RankTimeDraw(int ranking);
	void MyRankTimeDraw(int ranking);
	void ButtonDraw();

private:	// �ϐ�
	int m_clearTime;			// �N���A����
	bool m_isGameClear;			// �Q�[�����N���A�������ǂ���

	bool m_isFall;				// ��������
	bool m_isMyRank;			// �����̃^�C�������f����Ă��邩

	int m_minusPosY;				// ����Y���W

	std::array<int, 11> m_myTimeNumH{};	// ���g�̃N���A�^�C���̉摜�n���h��
	std::array<int, 11> m_rankingTimeNumH{};	// �����L���O�̃^�C���̉摜�n���h��
	std::array<int, 4> m_rankH{};			// �����N�摜�n���h��
	std::array<int, 3> m_textH{};	// �e�L�X�g�摜�n���h��
	std::array<int, 3> m_rankingH{};	// �����L���O�摜�n���h��
	std::array<int, 2> m_textBoxH{};	// �e�L�X�g�{�b�N�X�摜�n���h��
	std::array<int, 2> m_buttonH{};		// �{�^���̉摜�n���h��

	Rank m_rank;			// �����N
	
	std::vector<int> m_ranking{};	// �����L���O
	Game::Stage m_stageKind;	// �X�e�[�W�̎��

	std::shared_ptr<ObjectManager> m_pObjectManager;	// �I�u�W�F�N�g�}�l�[�W���[�N���X�̃|�C���^
	std::shared_ptr<CountTime> m_pCountTime;		// �b���J�E���g�̃|�C���^
	std::shared_ptr<Time> m_pImageDrawTime;		// �摜���\�������܂ł̎���
	std::shared_ptr<Time> m_pStageClearSETime;	// �X�e�[�W�N���A���̃T�E���h�̊J�n����
	std::shared_ptr<Ranking> m_pRanking;	// �����L���O

};

