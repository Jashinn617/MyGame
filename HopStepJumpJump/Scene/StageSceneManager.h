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
	// �N���A��̃V�[���̃^�C�v
	enum class ClearSceneType
	{
		LeftImgDraw,		// ���摜�̕`��
		ClearTimeMeasure,	// �^�C���v��
		RankDraw,			// �����N�`��
		RankingDraw,		// �����L���O�`��
		SceneChange,		// �V�[���J��
	};

	enum class NextSelect
	{
		GameScene,	// �Q�[���V�[��
		Title,		// �^�C�g��
		Num,
	};

	enum class NextScene
	{
		My,		// �����̃V�[��
		GameScene,	// �Q�[���V�[��
		Title,		// �^�C�g���V�[��
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

	NextScene GetNextScene()const { return m_nextScene; }

private:	// �֐�
	void ClearUpdate();
	void ClearSoundUpdate();
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
	int m_clearTextH;			// �N���A���ɏo���摜�̃n���h��
	int m_operationH;			// ��������摜�n���h��
	int m_clearTime;			// �N���A����
	int m_drawClearTime;		// �\���p�̃N���A����
	float m_rankSize;			// �����N�̃T�C�Y
	bool m_isGameClear;			// �Q�[�����N���A�������ǂ���

	bool m_isMyRank;			// �����̃^�C�������f����Ă��邩

	bool m_isPlayClearSE;		// �N���A��SE�𗬂������ǂ���

	bool m_isExpasionRnak;	// �����N���g�咆��

	bool m_isButtonDraw;	// �{�^�����\�����ꂽ���ǂ���

	int m_minusLeftPosY;		// ���������̉摜��Y���W

	int m_minusRightPosX;		// �����E���̉摜��X���W

	int m_minusButtonPosY;		// �����{�^���̉摜��Y���W

	int m_alpha;			// ��ʂ̈Â�

	bool m_isButtonFall;		// �{�^�����������������ǂ���

	bool m_isPlayRankingSE;		// �����L���O�pSE�𗬂������ǂ���

	int m_buttonCount;		// �J�[�\���̃J�E���g

	NextSelect m_nextSelect;	// �Z���N�g
	NextScene m_nextScene;		// ���̃V�[��

	float m_titleChangeTextSize;
	float m_gameSceneChangeTextSize;


	std::array<int, 11> m_myTimeNumH{};	// ���g�̃N���A�^�C���̉摜�n���h��
	std::array<int, 11> m_rankingTimeNumH{};	// �����L���O�̃^�C���̉摜�n���h��
	std::array<int, 4> m_rankH{};			// �����N�摜�n���h��
	std::array<int, 3> m_textH{};	// �e�L�X�g�摜�n���h��
	std::array<int, 3> m_rankingH{};	// �����L���O�摜�n���h��
	std::array<int, 2> m_textBoxH{};	// �e�L�X�g�{�b�N�X�摜�n���h��
	std::array<int, 3> m_buttonH{};		// �{�^���̉摜�n���h��

	Rank m_rank;			// �����N
	ClearSceneType m_clearSceneType;	// �N���A��̃V�[���̃^�C�v
		
	std::vector<int> m_ranking{};	// �����L���O
	Game::Stage m_stageKind;	// �X�e�[�W�̎��

	std::shared_ptr<ObjectManager> m_pObjectManager;	// �I�u�W�F�N�g�}�l�[�W���[�N���X�̃|�C���^
	std::shared_ptr<CountTime> m_pCountTime;		// �b���J�E���g�̃|�C���^
	std::shared_ptr<Time> m_pImageDrawTime;		// �摜���\�������܂ł̎���
	std::shared_ptr<Time> m_pStageClearSETime;	// �X�e�[�W�N���A���̃T�E���h�̊J�n����
	std::shared_ptr <Time> m_pRankDrawTime;		// �����N���\�������܂ł̎���
	std::shared_ptr<Time> m_pLeftImgDrawTime;	// �����̉摜���\�������܂ł̎���
	std::shared_ptr<Time> m_pRightImgDrawTime;	// �E���̉摜���\�������܂ł̎���
	std::shared_ptr<Time> m_pButtonDrawTime;	// �{�^�����\�������܂ł̎���
	std::shared_ptr<Ranking> m_pRanking;	// �����L���O

};

