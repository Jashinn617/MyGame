#include "DxLib.h"
#include "StageTest.h"
#include "../Player.h"

#include <cassert>

/// <summary>
/// �萔��`
/// </summary>
namespace
{
	constexpr float kDefaultSize = 800.0f;		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
	constexpr float kHitWidth = 200.0f;			// �����蔻��̃J�v�Z���̉��̔��a
	constexpr float kHitHeight = 700.0f;		// �����蔻��̃J�v�Z���̍���
	constexpr float kHitSlideLength = 5.0f;		// ��x�̕ǂ̉����o�������ŃX���C�h�����鋗��
	constexpr float kModelScale = 50.0f;		// ���f���̃X�P�[��
	constexpr int   kHitTryNum = 16;			// �ǂ̉����o�������̍ő厎�s��
}

StageTest::StageTest() :
	m_modelHandle(-1),
	m_vs(-1),
	m_ps(-1),
	m_wallNum(0),
	m_floorNum(0),
	m_wall{ nullptr },
	m_floor{ nullptr }
{
	/*��������*/
}

StageTest::~StageTest()
{
	// ���f���̃f���[�g
	MV1DeleteModel(m_modelHandle);
}

void StageTest::Init()
{
	// ���f���̃��[�h
	m_modelHandle = MV1LoadModel("Data/Model/Ground.mv1");
	assert(m_modelHandle != -1);
	// �V�F�[�_�̃��[�h
	m_vs = LoadVertexShader("VertexShader.vso");
	assert(m_vs != -1);
	m_ps = LoadPixelShader("PixelTest.pso");
	assert(m_ps != -1);

	// ���f���̑傫���̐ݒ�
	MV1SetScale(m_modelHandle, VGet(kModelScale, kModelScale, kModelScale));

	// ���f���̈ʒu�̐ݒ�(��)
	MV1SetPosition(m_modelHandle, VGet(0, -10, 0));

	// ���f���S�̂̃R���W�������̃Z�b�g�A�b�v
	MV1SetupCollInfo(m_modelHandle);
}

void StageTest::Draw()
{
	// �V�F�[�_��L���ɂ���
	MV1SetUseOrigShader(true);
	SetUseVertexShader(m_vs);
	SetUsePixelShader(m_ps);

	// ���f���̕`��
	MV1DrawModel(m_modelHandle);

	// �V�F�[�_�𖳌��ɂ���
	MV1SetUseOrigShader(false);
}

void StageTest::End()
{
	/*��������*/
}

VECTOR StageTest::CheckCollision(Player& player, const VECTOR& moveVector)
{
	// �ړ��O�̃v���C���[�̍��W���L�����Ă���
	VECTOR oldPos = player.GetPos();
	// �ړ���̃v���C���[�̍��W�̌v�Z
	VECTOR nextPos = VAdd(oldPos, moveVector);

	// �X�e�[�W�|���S������������ꍇ�͂������J��Ԃ��̏����ɂȂ�
	{
		// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
		// �ړ��������l�������͈͂��擾����
		auto hitDim = MV1CollCheck_Sphere(m_modelHandle, -1, oldPos, kDefaultSize + VSize(moveVector));

		// ���o���ꂽ�|���S�����ǃ|���S�������|���S�����𔻒f���ĕۑ�����
		AnalyzeWallAndFloor(hitDim, oldPos);

		// �ǃ|���S���Ƃ̓����蔻����`�F�b�N���Ĉړ��x�N�g����␳����
		nextPos = CheckHitWithWall(player, nextPos);

		// �ǃ|���S���Ƃ̓����蔻����`�F�b�N���Ĉړ��x�N�g����␳����
		nextPos = CheckHitWithFloor(player, nextPos);

		// ���o�����v���C���[�̎��͂̃|���S�������������
		MV1CollResultPolyDimTerminate(hitDim);
	}
	return nextPos;
}

void StageTest::AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition)
{
	// �ǃ|���S���Ə��|���S���̐�������������
	m_wallNum = 0;
	m_floorNum = 0;

	// ���o���ꂽ�|���S���̐������J��Ԃ�
	for (int i = 0; i < hitDim.HitNum; i++)
	{
		// XZ���ʂɐ������ǂ����̓|���S���̖@����Y������0�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
		if (hitDim.Dim[i].Normal.y<0.000001f && hitDim.Dim[i].Normal.y>-0.000001f)
		{
			// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[��Y���W���
			// 1.0f�����|���S���݂̂ɓ����蔻����s��
			bool isPlayerHight0 = hitDim.Dim[i].Position[0].y > checkPosition.y + 1.0f;
			bool isPlayerHight1 = hitDim.Dim[i].Position[1].y > checkPosition.y + 1.0f;
			bool isPlayerHight2 = hitDim.Dim[i].Position[2].y > checkPosition.y + 1.0f;
			if (isPlayerHight0 || isPlayerHight1 || isPlayerHight2)
			{
				// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�����
				if (m_wallNum < kMaxHitColl)
				{
					// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�̔z��ɕۑ�����
					m_wall[m_wallNum] = &hitDim.Dim[i];
					m_wallNum++;
				}
			}
		}
		else	// ���Ƃ��ď�������
		{
			// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�����
			if (m_floorNum < kMaxHitColl)
			{
				// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�̔z��ɕۑ�����
				m_floor[m_floorNum] = &hitDim.Dim[i];
				m_floorNum++;
			}
		}
	}
}

VECTOR StageTest::CheckHitWithWall(Player& player, const VECTOR& checkPosition)
{
	// �C������ʒu�̍쐬
	VECTOR fixedPos = checkPosition;

	// �ǂ̐���0�������ꍇ�͉������Ȃ�
	if (m_wallNum == 0)return fixedPos;

	// �ǂ���̉����o���������ő吔�܂ŌJ��Ԃ�
	for (int k = 0; k < kHitTryNum; k++)
	{
		bool isHitWall = false;
		for (int i = 0; i < m_wallNum; i++)
		{
			// �ǃ|���S���̃A�h���X��z�񂩂�擾����
			auto poly = m_wall[i];

			// �v���C���[�Ɠ������Ă����ꍇ
			if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
				kHitWidth, poly->Position[0], poly->Position[1], poly->Position[2]))
			{
				// �K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
				// �ړ���̈ʒu���X�V����
				fixedPos = VAdd(fixedPos, VScale(poly->Normal, kHitSlideLength));

				// �ړ������ǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒肷��
				for (int j = 0; j < m_wallNum; j++)
				{
					// �������Ă����烋�[�v�𔲂���
					poly = m_wall[j];
					if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
						kHitWidth, poly->Position[0], poly->Position[1], poly->Position[2]))
					{
						isHitWall = true;
						break;
					}
				}

				// �S�Ẵ|���S���Ɠ���Ȃ��Ȃ����ꍇ�͂����Ń��[�v���I������
				if (!isHitWall)
				{
					break;
				}
			}
		}
		// �S�Ă̕ǃ|���S���ƐڐG���Ȃ��Ȃ����烋�[�v���甲����
		if (!isHitWall)
		{
			break;
		}
	}

	return fixedPos;
}

VECTOR StageTest::CheckHitWithFloor(Player& player, const VECTOR& checkPosition)
{
	// �C������ʒu�̍쐬
	VECTOR fixedPos = checkPosition;

	// ���̐���0�������ꍇ�͉������Ȃ�
	if (m_floorNum == 0)return fixedPos;

	// �W�����v���ŏ㏸���������ꍇ�͏����𕪊򂷂�
	if (player.GetState() == Player::State::Jump && player.GetJumpPower() > 0.0f)
	{
		// �V��ɓ����Ԃ��鏈�����s��
		bool isHitRoof = false;
		// ��ԒႢ�V��̔���p�̕ϐ��̏�����
		float minY = 0.0f;

		// ���|���S���̐������J��Ԃ�
		for (int i = 0; i < m_floorNum; i++)
		{
			// ���|���S���̃A�h���X�̎擾
			auto poly = m_floor[i];

			// ���悩�瓪�̍����܂ł̊ԂŃ|���S���ƐڐG���Ă��邩�ǂ����𔻒肷��
			// �����ƃ|���S���̓����蔻��̌��ʂ�����\����
			HITRESULT_LINE lineResult;
			lineResult = HitCheck_Line_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
				poly->Position[0], poly->Position[1], poly->Position[2]);

			// �ڐG���Ă��Ȃ������ꍇ
			if (lineResult.HitFlag)
			{
				// ���łɃ|���S���ɓ������Ă��āA���܂Ō��o�����V��|���S����荂�������ꍇ�͉������Ȃ�
				if (!(isHitRoof && minY < lineResult.Position.y))
				{
					// �Փ˃t���O�𗧂Ă�
					isHitRoof = true;

					// �ڐG����Y���W��ۑ�����
					minY = lineResult.Position.y;
				}
			}
		}

		// �ڐG�����|���S�����������ꍇ
		if (isHitRoof == true)
		{
			// �v���C���[��Y���W�𓖂��������W�����ƂɍX�V����
			fixedPos.y = minY - kHitHeight;
			player.OnHitRoof();
		}
	}
	// ���������W�����v������Ȃ��Ƃ��̏���
	else
	{
		bool isHitFloor = false;
		float maxY = 0.0f;

		// ���|���S���̐������J��Ԃ�
		for (int i = 0; i < m_floorNum; i++)
		{
			// ���|���S���̃A�h���X
			auto poly = m_floor[i];

			HITRESULT_LINE lineResult;
			if (player.GetState() == Player::State::Jump)
			{
				// �W�����v���̏ꍇ�͓��̐悩�瑫���菭���Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒肷��
				lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
					VAdd(fixedPos, VGet(0.0f, -1.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
			}
			else
			{
				// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�
				// (�X�΂ŗ�����ԂɂȂ�Ȃ����߂ɂ���)
				lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, kHitHeight, 0.0f)),
					VAdd(fixedPos, VGet(0.0f, -40.0f, 0.0f)), poly->Position[0], poly->Position[1], poly->Position[2]);
			}

			// ���ɓ��������|���S��������A���܂Ō��o�������|���S�������Ⴂ�͈��͉������Ȃ�
			if (lineResult.HitFlag)
			{
				if (!(isHitFloor && maxY > lineResult.Position.y))
				{
					// �ڐG����Y���W��ێ�����
					isHitFloor = true;
					maxY = lineResult.Position.y;
				}
			}
		}

		// ���|���S���ɓ�������
		if (isHitFloor)
		{
			// �ڐG�����|���S���ň�ԍ���Y���W���v���C���[��Y���W�ɂ���
			fixedPos.y = maxY;

			// ���ɓ���������
			player.OnHitFloor();
		}
		else
		{
			// ���R���W�����ɓ������Ă��Ȃ��ăW�����v��ԂłȂ������ꍇ�͗�����ԂɂȂ�
			player.OnFall();
		}
	}
	return fixedPos;
}
