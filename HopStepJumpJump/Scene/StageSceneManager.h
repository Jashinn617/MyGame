#pragma once
#include "../Util/Game.h"

#include <memory>
#include <vector>
#include <array>
#include <functional>

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
		S,			// S�����N
		A,			// A�����N
		B,			// B�����N
		C,			// C�����N
		RankNum,	// �����N�̐�
	};
	// �N���A��̃V�[���̃^�C�v
	enum class ClearSceneType
	{
		LeftImgDraw,		// ���摜�̕`��
		ClearTimeMeasure,	// �^�C���v��
		RankDraw,			// �����N�`��
		RankingDraw,		// �����L���O�`��
		SceneChange,		// �V�[���J��
	};
	// ���̑I��
	enum class NextSelect
	{
		GameScene,	// �Q�[���V�[��
		Select,		// �^�C�g��
		Num,		// �Z���N�g��
	};
	// ���̃V�[��
	enum class NextScene
	{
		My,			// �����̃V�[��
		GameScene,	// �Q�[���V�[��
		Select,		// �Z���N�g�V�[��
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="stageKind">�X�e�[�W�̎��</param>
	StageSceneManager(Game::Stage stageKind);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~StageSceneManager();

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

	/// <summary>
	/// �X�e�[�W�̎�ނ̎擾
	/// </summary>
	/// <returns>�X�e�[�W�̎��</returns>
	Game::Stage GetStageKind() const { return m_stageKind; }
	
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

	NextScene GetNextScene()const { return m_nextScene; }

private:	// �֐�
	/// <summary>
	/// �N���A���̍X�V
	/// </summary>
	void ClearUpdate();

	/// <summary>
	/// �N���A���̕`��
	/// </summary>
	void ClearDraw();

	/// <summary>
	/// �e�L�X�g�̕`��
	/// </summary>
	void TextDraw();
	/// <summary>
	/// �^�C���̕`��
	/// </summary>
	void TimeDraw();
	/// <summary>
	/// �����L���O�̕`��
	/// </summary>
	void RankingDraw();
	/// <summary>
	/// �����N�̕`��
	/// </summary>
	void RankDraw();
	/// <summary>
	/// �����L���O�^�C���̕`��
	/// </summary>
	/// <param name="ranking">�����L���O</param>
	void RankingTimeDraw(int ranking);
	/// <summary>
	/// �����L���O���ɂ��鎩�g�̃^�C���̕`��
	/// </summary>
	/// <param name="ranking">�����L���O</param>
	void MyRankTimeDraw(int ranking);
	/// <summary>
	/// �{�^���̕`��
	/// </summary>
	void ButtonDraw();

	/// <summary>
	/// �摜�̃��[�h
	/// </summary>
	void LoadImg();
	/// <summary>
	/// �摜�̃f���[�g
	/// </summary>
	void DeleteImg();

private:	// �ϐ�
	int m_clearTime;					// �N���A����
	int m_drawClearTime;				// �\���p�̃N���A����
	int m_minusLeftPosY;				// ���������̉摜��Y���W
	int m_minusRightPosX;				// �����E���̉摜��X���W
	int m_minusButtonPosY;				// �����{�^���̉摜��Y���W
	int m_alpha;						// ��ʂ̈Â�
	int m_buttonCount;					// �J�[�\���̃J�E���g
	float m_rankSize;					// �����N�̃T�C�Y
	float m_selectChangeTextSize;		// �Z���N�g�V�[���ɖ߂�{�^���p�e�L�X�g�̃T�C�Y
	float m_gameSceneChangeTextSize;	// �Q�[���V�[���ɖ߂�{�^���p�e�L�X�g�̃T�C�Y
	bool m_isGameClear;					// �Q�[�����N���A�������ǂ���
	bool m_isMyRank;					// �����̃^�C���������L���O�ɏ���Ă��邩
	bool m_isPlayClearSE;				// �N���A��SE�𗬂������ǂ���
	bool m_isExpasionRnak;				// �����N���g�咆��
	bool m_isButtonFall;				// �{�^�����������������ǂ���
	bool m_isPlayRankingSE;				// �����L���O�pSE�𗬂������ǂ���

	NextSelect m_nextSelect;			// �Z���N�g
	NextScene m_nextScene;				// ���̃V�[��
	Rank m_rank;						// �����N
	ClearSceneType m_clearSceneType;	// �N���A��̃V�[���̃^�C�v
	Game::Stage m_stageKind;			// �X�e�[�W�̎��

	std::array<int, 11> m_myTimeNumH{};			// ���g�̃N���A�^�C���̉摜�n���h��
	std::array<int, 11> m_rankingTimeNumH{};	// �����L���O�̃^�C���̉摜�n���h��
	std::array<int, 4> m_rankH{};				// �����N�摜�n���h��
	std::array<int, 3> m_textH{};				// �e�L�X�g�摜�n���h��
	std::array<int, 3> m_rankingH{};			// �����L���O�摜�n���h��
	std::array<int, 2> m_textBoxH{};			// �e�L�X�g�{�b�N�X�摜�n���h��
	std::array<int, 3> m_buttonH{};				// �{�^���̉摜�n���h��
	std::vector<int> m_ranking{};				// �����L���O

	int m_clearTextH;									// �N���A���ɏo���摜�̃n���h��
	int m_operationH;									// ��������摜�n���h��
	std::shared_ptr<ObjectManager> m_pObjectManager;	// �I�u�W�F�N�g�}�l�[�W���[�N���X�̃|�C���^
	std::shared_ptr<CountTime> m_pCountTime;			// �b���J�E���g�̃|�C���^
	std::shared_ptr<Time> m_pImageDrawTime;				// �摜���\�������܂ł̎���
	std::shared_ptr<Time> m_pStageClearSETime;			// �X�e�[�W�N���A���̃T�E���h�̊J�n����
	std::shared_ptr <Time> m_pRankDrawTime;				// �����N���\�������܂ł̎���
	std::shared_ptr<Time> m_pLeftImgDrawTime;			// �����̉摜���\�������܂ł̎���
	std::shared_ptr<Time> m_pRightImgDrawTime;			// �E���̉摜���\�������܂ł̎���
	std::shared_ptr<Time> m_pButtonDrawTime;			// �{�^�����\�������܂ł̎���
	std::shared_ptr<Ranking> m_pRanking;				// �����L���O
};