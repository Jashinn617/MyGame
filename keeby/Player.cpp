#include "Player.h"
#include "DxLib.h"
#include "Game.h"
#include "util/Input.h"
#include "Attack/Vomit.h"
#include "Attack/AirBullet.h"
#include "Attack/Inhale.h"
#include "Object/Needle.h"
#include "Camera.h"

namespace
{
	// �v���C���[�̃X�s�[�h
	constexpr int m_Speed = 8;
	// �O���t�B�b�N�̐؂���T�C�Y
	constexpr int kWidth = 68;
	constexpr int kHeight = 67;
	// �d��
	constexpr float kGravity = 0.6f;
	// �z�o�����O���̏d��
	constexpr float kHoveringGravity = 0.15f;
	// �W�����v��
	constexpr float kJumpAcc = -10.0f;
	// �z�o�����O���̃W�����v��
	constexpr float kJumpHoveringAcc = -4.0f;
	// �e�̃X�s�[�h
	constexpr int kVomitSpeed = 10;
	constexpr int kAirSpeed = 15;
	// �v���C���[�̍ő�HP
	constexpr int kMaxHp = 6;
	// �v���C���[�̍ő�c�@
	constexpr int kMaxRemainingLives = 3;
	// �A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,1 };
	// 1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 12;
	// �P�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
	// �_���[�W���o�̃t���[����
	constexpr int kDamegeFrame = 60;

	// �_���T�[�̐�
	constexpr int kDancerNum = 3;

	// �_���X�̐؂���T�C�Y
	constexpr int kDancerWidth1 = 72;
	constexpr int kDanceHeight1 = 70;
	constexpr int kDancerWidth2 = 43;
	constexpr int kDanceHeight2 = 48;

	// �_���X�̃A�j���[�V����
	constexpr int kDanceUseFrame[]{ 0,1,0 };
	// 1�R�}�̃t���[����
	constexpr int kDanceAnimFrameNum = 12;
	// �P�T�C�N���̃t���[����
	constexpr int kDanceAnimFrameCycle = _countof(kUseFrame) * kDanceAnimFrameNum;
	// �X�s�[�h
	constexpr float kDanceSinSpeed1 = 0.1f;
	constexpr float kDanceSinSpeed2 = 0.25f;
	// �h�ꕝ
	constexpr float kDanceAnimSwing1 = -200;
	constexpr float kDanceAnimSwing2 = 80;
}

Player::Player() :
	m_pos(0,0),
	m_move(0,0),
	m_condition(kFall),
	m_dir(kDirRight),
	m_x(0),
	m_y(0),
	m_w(64),
	m_h(64),
	m_walkHandle(-1),
	m_inhaleHandle(-1),
	m_hoveringHandle(-1),
	m_gulpHandle(-1),
	m_jumpHandle(-1),
	m_missHandle(-1),
	m_danceHandle1(-1),
	m_danceHandle2(-1),
	m_clearBgmHandle(-1),
	m_inhaleSeHandle(-1),
	m_jumpSeHandle(-1),
	m_damageSeHandle(-1),
	m_fallSpeed(0.0f),
	m_jumpCount(0),
	m_hp(kMaxHp),
	m_remainingLives(kMaxRemainingLives),
	m_isGlup(false),
	m_isVomit(false),
	m_vomitFrame(0),
	m_animFrame(0),
	m_damageFrame(0),
	m_isDamage(false),
	m_isMiss(false),
	m_missFrame(0),
	m_missRotate(0.0f),
	m_isFellMiss(false),
	m_isDamageMiss(false),
	m_isDance(false),
	m_isFlowerMove(false),
	m_eventFrame(0),
	m_danceRotate(0),
	m_rotatePattern(0),
	m_danceSinCount(0),
	m_danceAnimationPosY(0),
	m_choreography(kRotate),
	m_danceAnimFrame(0),
	m_moveEventX(0),
	m_moveEventY(0),
	m_moveEventFrame(0)
{
	/*�O���t�B�b�N�̃��[�h*/
	m_walkHandle = LoadGraph(_T("data/Player/Walk.png"));
	m_inhaleHandle = LoadGraph(_T("data/Player/Inhale.png"));
	m_gulpHandle = LoadGraph(_T("data/Player/Gulp.png"));
	m_hoveringHandle = LoadGraph(_T("data/Player/Hovering.png"));
	m_jumpHandle = LoadGraph(_T("data/Player/Jump.png"));
	m_missHandle = LoadGraph(_T("data/Player/Miss.png"));
	m_danceHandle1 = LoadGraph(_T("data/Event/Dance1.png"));
	m_danceHandle2 = LoadGraph(_T("data/Event/Dance2.png"));

	/*BGM�̃��[�h*/
	m_clearBgmHandle = LoadSoundMem(_T("data/Sound/SE/Clear.wav"));

	/*SE�̃��[�h*/
	m_inhaleSeHandle = LoadSoundMem(_T("data/Sound/SE/Inhale.wav"));
	m_jumpSeHandle = LoadSoundMem(_T("data/Sound/SE/Jump.mp3"));
	m_attackSeHandle = LoadSoundMem(_T("data/Sound/SE/Vomit.mp3"));
	m_damageSeHandle = LoadSoundMem(_T("data/Sound/SE/Damage.wav"));
}

Player::~Player()
{
	/*�O���t�B�b�N�̃f���[�g*/
	DeleteGraph(m_walkHandle);
	DeleteGraph(m_inhaleHandle);
	DeleteGraph(m_gulpHandle);
	DeleteGraph(m_hoveringHandle);
	DeleteGraph(m_jumpHandle);
	DeleteGraph(m_missHandle);
	DeleteGraph(m_danceHandle1);
	DeleteGraph(m_danceHandle2);
	
	/*SE�̃f���[�g*/
	DeleteSoundMem(m_inhaleSeHandle);
	DeleteSoundMem(m_jumpSeHandle);
	DeleteSoundMem(m_attackSeHandle);
	DeleteSoundMem(m_damageSeHandle);
}

void Player::Init()
{
	// ���g���C���̐��l�̏�����
	m_isMiss = false;
	m_missFrame = 0;
	m_dir = kDirRight;
	m_condition = kFall;
	m_damageFrame = 0;
	m_isDamageMiss = false;
	m_isFellMiss = false;
	m_isDance = false;
	m_isFlowerMove = false;
	m_isGlup = false;
	m_isVomit = false;
	m_eventFrame = 0;

	// �U���̏�����
	m_pAirBullet->Init();
	m_pInhale->Init();
	m_pVomit->Init();
}


void Player::Draw()
{
	// �_���[�W���̓_��
	if (m_damageFrame % 4 >= 2)return;

	// ���������̍��W��������W�ɕϊ�����
	m_x = m_pos.x - kWidth * 0.5f;
	m_y = m_pos.y - kHeight;
	// �X�N���[���ʂ𔽉f����
	m_x -= m_pCamera->GetScrollX();
	m_y -= m_pCamera->GetScrollY();
	// �A�j���[�V����
	int animFrame = m_animFrame / kAnimFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	// ���݂̏�Ԃɂ���ĉ摜���؂�ւ��
	switch (m_condition)
	{
	case Player::kMove:
		DrawRectGraph(static_cast<int>(m_x), static_cast<int>(m_y + 5), srcX, srcY, kWidth, kHeight, m_walkHandle, true);
		break;
	case Player::kInhale:
		DrawRectGraph(static_cast<int>(m_x), static_cast<int>(m_y + 5), srcX, srcY, kWidth, kHeight, m_inhaleHandle, true);
		break;
	case Player::kVomit:
		DrawRectGraph(static_cast<int>(m_x), static_cast<int>(m_y + 5), srcX, srcY, kWidth, kHeight, m_inhaleHandle, true);
		break;
	case Player::kGulp:
		DrawRectGraph(static_cast<int>(m_x), static_cast<int>(m_y + 5), srcX, srcY, kWidth, kHeight, m_gulpHandle, true);
		break;
	case Player::kJump:
		DrawRectGraph(static_cast<int>(m_x), static_cast<int>(m_y + 5), 0, srcY, kWidth, kHeight, m_jumpHandle, true);
		break;
	case Player::kHovering:
		DrawRectGraph(static_cast<int>(m_x), static_cast<int>(m_y + 5), srcX, srcY, kWidth, kHeight, m_hoveringHandle, true);
		break;
	case Player::kFall:
		DrawRectGraph(static_cast<int>(m_x), static_cast<int>(m_y + 5), 0, srcY, kWidth, kHeight, m_jumpHandle, true);
		break;
	case Player::kMiss:
		DrawRotaGraph(static_cast<int>(m_x), static_cast<int>(m_y + 5), 1.0, m_missRotate, m_missHandle, true);
		break;
	case Player::kDance:
		DanceDraw();
		break;
	default:
		break;
	}

#ifdef _DEBUG
	// �����蔻��p�̋�`
	DrawBox(static_cast<int>(GetColLect()), static_cast<int>(GetColTop()), static_cast<int>(GetColRight()), static_cast<int>(GetColBottom()), 0xff0000, false);
#endif

	// �U���̕`��
	m_pAirBullet->Draw();
	m_pInhale->Draw();
	m_pVomit->Draw();
}

void Player::Update(Input& input, std::vector<std::vector<int>> mapData, int chipNumX, int chipNumY, int chipWidth, int chipHeight)
{
	// �z�����ݒ��Ƀ~�X�������Ƃ��ɉ����葱���Ȃ��悤�ɂ���
	if (m_condition != kInhale)
	{
		StopSoundMem(m_inhaleSeHandle);
		m_pInhale->FalseExist();
	}

	// �~�X�������Ƃ��͑���ⓖ���蔻�肪�����ɂȂ�
	if (!m_isMiss)
	{
		// �_���[�W���o
		// HP���[���ɂȂ����ꍇ�͂��Ȃ�
		if (m_hp >= 1)
		{
			m_damageFrame--;
			if (m_damageFrame < 0)m_damageFrame = 0;
		}

		// �����Ă���Ƃ������A�j���[�V��������
		bool isMove = false;
		if (m_condition == kHovering)
		{
			isMove = true;
		}
		// �d��
		// �z�o�����O���͗����鑬�x���x���Ȃ�

		if (m_condition == kHovering)
		{
			m_move.y += kHoveringGravity;
		}
		else
		{
			m_move.y += kGravity;
		}		

		// �v���C���[�̈ړ�
		m_move.x = 0.0f;
		if (input.IsPressing("left"))
		{
			m_move.x -= m_Speed;

			m_dir = kDirLeft;
			isMove = true;
		}
		if (input.IsPressing("right"))
		{
			m_move.x += m_Speed;

			m_dir = kDirRight;
			isMove = true;
		}
		// �W�����v&�z�o�����O
		if (m_condition == kMove || 
			m_condition == kJump || 
			m_condition == kHovering || 
			m_condition == kVomit ||
			m_condition == kFall)
		{
			//  B�{�^�����X�y�[�X�L�[����������W�����v����
			if (input.IsTriggered("B"))
			{
				PlaySoundMem(m_jumpSeHandle, DX_PLAYTYPE_BACK, true);
				if (m_jumpCount >= 1)
				{
					m_move.y = kJumpHoveringAcc;
				}
				else
				{
					m_move.y = kJumpAcc;
					m_condition = kJump;
				}
				m_jumpCount++;
				isMove = true;
			}
			// �W�����v�𑱂���2��ȏシ��ƃz�o�����O��ԂɂȂ�
			if (m_jumpCount >= 2)
			{
				m_condition = kHovering;
			}
		}

		/*�}�b�v�Ƃ̓����蔻��*/
		m_pos.x += m_move.x;
		// �����瓖�����������`�F�b�N����
		Rect chipRect; // ���������}�b�v�`�b�v�̋�`
		if (IsMapCollision(mapData, chipNumX, chipNumY, chipWidth, chipHeight, GetRect(), chipRect))
		{
			// ������Ԃ������ꍇ�̏���
			if (m_move.x > 0.0f)// �E����
			{
				m_pos.x = chipRect.left - chipWidth * 0.5f - 1;
			}
			else if (m_move.x < 0.0f)// ������
			{
				m_pos.x = chipRect.right + chipWidth * 0.5f + 1;
			}
		}

		m_pos.y += m_move.y;
		// �c���瓖�����������`�F�b�N����
		if (IsMapCollision(mapData, chipNumX, chipNumY, chipWidth, chipHeight, GetRect(), chipRect))
		{
			// �c���瓖�����������`�F�b�N����
			if (m_move.y > 0.0f)// ������(����)
			{
				m_pos.y = chipRect.top - 1;

				// �ړ��l���[���ɂ���
				m_move.y = 0;
				// �W�����v�̃J�E���g���[���ɂ���
				m_jumpCount = 0;

				// �G�����ݍ���ł��Ȃ������ꍇ�͈ړ���Ԃɖ߂�
				if (!m_isGlup && !m_isVomit)
				{
					m_condition = kMove;
				}
			}
			else if (m_move.y < 0.0f)// �����(��)
			{
				m_pos.y = chipRect.bottom + chipHeight + 1;
				// ���ɒ��˕Ԃ�
				m_move.y *= -0.2f;
			}
		}

		// �ړ����̂݃A�j���[�V����������
		if (isMove)
		{
			// �A�j���[�V����
			m_animFrame++;
			if (m_animFrame >= kAnimFrameCycle)
			{
				m_animFrame = 0;
			}
		}

		// ��ʊO�ɏo�Ȃ��悤�ɂ���
		if (GetLeft() <= 0)
		{
			m_pos.x = 0 + kWidth * 0.5f;
		}
		if (GetRight() >= m_pCamera->GetMapWidth())
		{
			m_pos.x = m_pCamera->GetMapWidth() - kWidth * 0.5f;
		}
		if (GetTop() <= 0)
		{
			m_pos.y = 0 + kHeight;
			m_move.y *= -0.2f;
		}
		// HP�̍ő�l��ݒ肵�Ă���
		if (m_hp >= kMaxHp)
		{
			m_hp = kMaxHp;
		}
		// �G��f���o���Ă��班���̊Ԃ������݂��ł��Ȃ��悤�ɂ���
		if (m_isVomit)
		{
			m_vomitFrame++;
		}
		if (m_vomitFrame >= 30)
		{
			m_vomitFrame = 0;
			m_isVomit = false;
		}

		/*�U���̍X�V*/
		// ��������
		AttackInhale(input);
		m_pInhale->Update();
		// �f���o��
		AttackVomit(input);
		m_pVomit->Update();
		// ��C�e
		AttackAirBullet(input);
		m_pAirBullet->Update();

		// �����蔻��̍X�V
		GetColRect();

	}
	else
	{
		// �~�X���������̉��o
		m_condition = kMiss;
		m_missFrame++;
		m_missRotate += 0.1f;
		// ���������Ƃ��̃~�X
		// �オ�鑬�x������
		if (m_isFellMiss)
		{
			if (m_missFrame <= 30)
			{
				m_pos.y -= 20;
			}
			else if (m_missFrame >= 60)
			{
				m_pos.y += 8;
			}
		
		}
		// �_���[�W��0�ɂȂ������̃~�X
		// �����鑬�x������
		if (m_isDamageMiss)
		{
			if (m_missFrame <= 30)// ��������~�܂�
			{
				m_pos.y += 0;
				m_missRotate = 0.0f;
			}
			if (m_missFrame <= 45)
			{
				m_pos.y -= 8;
			}
			else if (m_missFrame >= 60)
			{
				m_pos.y += 20;
			}
		}
	}
}


bool Player::IsMapCollision(std::vector<std::vector<int>> mapData, int chipNumX, int chipNumY, int chipWidth, int chipHeight, Rect playerRect, Rect& chipRect)
{
	/*�}�b�v�Ƃ̓����蔻��*/
	for (int x = 0; x < chipNumX; x++)
	{
		for (int y = 0; y < chipNumY; y++)
		{

			// mapData��0�������瓖����Ȃ�
			if (mapData[y][x] == 0)continue;

			float chipLeft = static_cast<float>(chipWidth * x);
			float chipRight = static_cast<float>(chipLeft + chipWidth);
			float chipTop = static_cast<float>(chipHeight * y);
			float chipBottom = static_cast<float>(chipTop + chipHeight);

			// ��΂ɓ�����Ȃ��ꍇ����
			if (chipLeft > playerRect.right)continue;
			if (chipTop > playerRect.bottom)continue;
			if (chipRight < playerRect.left)continue;
			if (chipBottom < playerRect.top)continue;

			// �Ԃ������}�b�v�`�b�v�̋�`���擾����
			chipRect.left = chipLeft;
			chipRect.right = chipRight;
			chipRect.top = chipTop;
			chipRect.bottom = chipBottom;

			// ������̃`�b�v�Ɠ������Ă�����true��Ԃ��ďI������(�������Ă���)
			return true;
		}
	}
	// ���ׂẴ`�b�v�Ɠ������Ă��Ȃ����false��Ԃ�(�������Ă��Ȃ�)
	return false;
}

void Player::DanceDraw()
{
	// ���������̍��W��������W�ɕϊ�����
	m_x = m_pos.x - kWidth * 0.5f;
	m_y = m_pos.y - kHeight;
	// �X�N���[���ʂ𔽉f����
	m_x -= m_pCamera->GetScrollX();
	m_y -= m_pCamera->GetScrollY();
	// �A�j���[�V����
	int animFrame = m_danceAnimFrame / kDanceAnimFrameNum;
	int srcX = kDanceUseFrame[animFrame] * kDancerWidth2;
	int srcY = kDanceHeight2 * m_dir;

	for (int i = 0; kDancerNum > i; i++)
	{
		int x = static_cast<int>(m_x) + (200 * i);
		int y = static_cast<int>(m_y) + static_cast<int>(m_danceAnimationPosY);

		if (m_choreography == kRotate)
		{
			DrawRectRotaGraph(x, y, m_rotatePattern * kDancerWidth1, 0, kDancerWidth1, kDanceHeight1, 1.8, m_danceRotate, m_danceHandle1, true);
		}
		else if (m_choreography == kLateralMove)
		{
			DrawRectRotaGraph(x, y, srcX, srcY, kDancerWidth2, kDanceHeight2, 1.8, 0.0, m_danceHandle2, true);
		}
	}
}


void Player::AttackInhale(Input& input)
{
	/* �z�����݂̎���*/
	if ((m_condition == kMove || m_condition == kInhale) && !m_isVomit)
	{
		//  A�{�^������������z������
		if (input.IsPressing("A"))
		{
			// SE��炷
			if (!CheckSoundMem(m_inhaleSeHandle))
			{
				PlaySoundMem(m_inhaleSeHandle, DX_PLAYTYPE_LOOP, true);
			}
			// �������ݏ�Ԃɂ���
			m_condition = kInhale;

			// �z�����݂̏���
			if (m_dir == kDirRight)
			{
				m_pInhale->PutBulletRight();
			}
			if (m_dir == kDirLeft)
			{
				m_pInhale->PutBulletLeft();
			}
		}
		else // ���������Ă��Ȃ��Ƃ�
		{
			// SE���~�߂�
			StopSoundMem(m_inhaleSeHandle);
			// �ړ���Ԃɂ���
			m_condition = kMove;
			// ���݂�false�ɂ���
			m_pInhale->FalseExist();
		}
	}
	else if (m_condition == kGulp) // �ق��΂��Ԃ̏ꍇ
	{
		// SE���~�߂�
		StopSoundMem(m_inhaleSeHandle);
		// ���݂�false�ɂ���
		m_pInhale->FalseExist();
	}
}

void Player::AttackVomit(Input& input)
{
	// �f���o���U���̎���
	// �ق��΂��Ԃ̂Ƃ���A�{�^������������Ԃ�f���o��
	if (m_condition == kGulp && input.IsTriggered("A"))
	{
			// �����ɋz�����ݏ�ԂɂȂ�Ȃ����߂�m_isVomit��true�ɂ���
			// m_isVomit��true�̎��́A�������ݏ�ԂɂȂ�Ȃ�
			// �ڍׂ�Update���ɋL��
			m_isVomit = true;
			// SE��炷
			PlaySoundMem(m_attackSeHandle, DX_PLAYTYPE_BACK, true);

			// �f���o������
			if (m_dir == kDirRight)
			{
				m_pVomit->PutBulletRight();
				m_pVomit->SetSpeed(-kVomitSpeed);
			}
			if (m_dir == kDirLeft)
			{
				m_pVomit->PutBulletLeft();
				m_pVomit->SetSpeed(kVomitSpeed);
			}

			// �f���o����Ԃɂ���
			m_condition = kVomit;
			m_isGlup = false;
	}
}

void Player::AttackAirBullet(Input& input)
{
	// ��C�e�̏���
	// �z�o�����O����A�{�^�������������C�e��f���o���ė�������
	// �������͈ړ��ȊO�����ł��Ȃ�
	if (m_condition == kHovering && input.IsTriggered("A"))
	{
		m_jumpCount = 0;
		// SE��炷
		PlaySoundMem(m_attackSeHandle, DX_PLAYTYPE_BACK, true);

		// ��C�e�̏���
		if (m_dir == kDirRight)
		{
			m_pAirBullet->PutBulletRight();
			m_pAirBullet->SetSpeed(-kAirSpeed);
		}
		if (m_dir == kDirLeft)
		{
			m_pAirBullet->PutBulletLeft();
			m_pAirBullet->SetSpeed(kAirSpeed);
		}
		// �f���o�������Ƃ͗�����ԂɂȂ�
		m_condition = kFall;
	}
}

Rect Player::GetRect()
{
	Rect rect;
	rect.top = GetTop();
	rect.left = GetLeft();
	rect.bottom = GetBottom();
	rect.right = GetRight();

	return rect;
}

Rect Player::GetColRect()
{
	m_colRect.top = GetColTop();
	m_colRect.left = GetColLect();
	m_colRect.bottom = GetColBottom();
	m_colRect.right = GetColRight();

	return m_colRect;
}

float Player::GetColLect() const
{
	// ����������������W�ɕϊ�����
	int x = static_cast<int>(m_pos.x - kWidth * 0.5f);
	int y = static_cast<int>(m_pos.y - kHeight);
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();
	
	// ���ۂ̓����蔻��͏�������������
	return static_cast<float>(x + 15);
}

float Player::GetColRight() const
{
	// ����������������W�ɕϊ�����
	int x = static_cast<int>(m_pos.x - kWidth * 0.5f);
	int y = static_cast<int>(m_pos.y - kHeight);
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	// ���ۂ̓����蔻��͏�������������
	return static_cast<float>(x + kWidth - 15);
}

float Player::GetColTop() const
{
	// ����������������W�ɕϊ�����
	int x = static_cast<int>(m_pos.x - kWidth * 0.5f);
	int y = static_cast<int>(m_pos.y - kHeight);
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	// ���ۂ̓����蔻��͏�������������
	return static_cast<float>(y + 15);
}

float Player::GetColBottom() const
{
	// ����������������W�ɕϊ�����
	int x = static_cast<int>(m_pos.x - kWidth * 0.5f);
	int y = static_cast<int>(m_pos.y - kHeight);
	// �X�N���[���ʂ𔽉f������
	x -= m_pCamera->GetScrollX();
	y -= m_pCamera->GetScrollY();

	// ���ۂ̓����蔻��͏�������������
	return static_cast<float>(y + kHeight - 15);
}

void Player::SetStartPos(float posX, float posY)
{
	m_pos.x = posX;
	m_pos.y = posY;
}

void Player::CompleteRecoveryLives()
{
	// �c�@��S������
	m_remainingLives = kMaxRemainingLives;
}

void Player::CompleteRecoveryHp()
{
	// HP��S������
	m_hp = kMaxHp;
}

void Player::RecoveryHp2()
{
	// HP���񕜂���
	if (m_hp <= 3)
	{
		m_hp += 3;
	}
	else if (m_hp = 4)
	{
		m_hp += 2;
	}
	else if (m_hp = 5)
	{
		m_hp += 1;
	}
	else
	{
	}
	
}

void Player::OnDamage()
{
	m_isDamage = false;
	// �_���[�W���͍ēx�H���Ȃ�
	if (m_damageFrame > 0)
	{
		m_isDamage = true;
		return;
	}
	// SE��炷
	PlaySoundMem(m_damageSeHandle, DX_PLAYTYPE_BACK, true);
	// HP�����炷
	m_hp--;
	// ���o�t���[�����̐ݒ�
	m_damageFrame = kDamegeFrame;
}

void Player::OnMiss()
{
	m_isMiss = true;
	// �_���[�W���̉��o�t���[��������������
	m_damageFrame = 0;
}

void Player::OnDance()
{
	m_condition = kDance;
	m_dir = kDirLeft;
	m_isDance;
	m_eventFrame++;
	

	if (m_eventFrame >= 0 && m_eventFrame < 30)
	{
		m_pos.x = 900;
		m_pos.y += 10;
		if (m_pos.y >= 800)
		{
			m_pos.y = 800;
		}
	}
	
	if (m_eventFrame >= 60)
	{
		if (!CheckSoundMem(m_clearBgmHandle))
		{
			PlaySoundMem(m_clearBgmHandle, DX_PLAYTYPE_BACK, true);
		}
	}
	
	if (m_eventFrame >= 60 && m_eventFrame < 120)
	{
		m_choreography = kLateralMove;
		m_pos.x -= 10;
	}
	if (m_eventFrame >= 120 && m_eventFrame < 170)
	{
		m_dir = kDirRight;
		m_pos.x += 5;
	}
	if (m_eventFrame >= 170 && m_eventFrame < 208)
	{
		m_choreography = kRotate;
		m_danceRotate += 0.1f;
		m_pos.x += 3;
		m_pos.y -= 5;
	}
	if (m_eventFrame >= 208 && m_eventFrame < 254)
	{
		m_danceRotate -= 0.1f;
		m_pos.x -= 3;
	}
	if (m_eventFrame >= 208 && m_eventFrame < 254)
	{
		m_danceSinCount += kDanceSinSpeed1;

		m_danceRotate += 0.1f;
		m_pos.x += 15;
		m_danceAnimationPosY = sinf(m_danceSinCount) * kDanceAnimSwing1;
	}
	if (m_eventFrame >= 254 && m_eventFrame < 300)
	{
		m_danceSinCount = 0;
		m_danceAnimationPosY = 0;
		m_danceRotate -= 0.2f;
		m_pos.x -= 5;
	}
	if (m_eventFrame >= 300 && m_eventFrame < 338)
	{
		m_danceSinCount += kDanceSinSpeed2;
		m_danceRotate = 0;
		m_choreography = kLateralMove;
		m_dir = kDirLeft;
		m_pos.x -= 8;
		m_danceAnimationPosY = sinf(m_danceSinCount) * kDanceAnimSwing2;
	}
	if (m_eventFrame >= 338 && m_eventFrame < 390)
	{
		m_danceSinCount = 0;
		m_danceAnimationPosY = 0;
		m_choreography = kRotate;
		m_pos.y -= 8;
	}
	if (m_eventFrame >= 415 && m_eventFrame < 450)
	{
		m_danceRotate += 0.5;
		m_pos.y += 10;
	}
	if (m_eventFrame >= 460 && m_eventFrame < 520)
	{
		m_danceRotate -= 0.2f;
		m_pos.x += 8;
	}
	if (m_eventFrame >= 520 && m_eventFrame < 575)
	{
		m_danceSinCount += kDanceSinSpeed2;
		m_pos.x -= 10;
		m_danceAnimationPosY = sinf(m_danceSinCount) * kDanceAnimSwing2;
	}
	if (m_eventFrame >= 575 && m_eventFrame < 590)
	{
		m_danceSinCount = 0;
		m_danceAnimationPosY = 0;
		m_danceRotate += 0.5;
		m_pos.y -= 10;
	}
	if (m_eventFrame >= 590 && m_eventFrame < 660)
	{
		m_danceRotate = 0;
		m_choreography = kLateralMove;
		m_dir = kDirRight;
		m_pos.x += 7;
	}
	if (m_eventFrame >= 660 && m_eventFrame < 700)
	{
		m_dir = kDirLeft;
		m_pos.x -= 10;
	}
	if (m_eventFrame >= 700 && m_eventFrame < 720)
	{
		m_choreography = kRotate;
		m_rotatePattern = 1;
		m_pos.y -= 3;
	}
	if (m_eventFrame >= 820)
	{
		StopSoundMem(m_clearBgmHandle);

		m_isFlowerMove = true;
	}
}