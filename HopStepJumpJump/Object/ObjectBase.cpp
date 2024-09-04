#include "ObjectBase.h"

#include "CharacterBase.h"
#include "ObjectManager.h"
#include "Model.h"
#include "Circle.h"

#include "../Util/Time.h"

#include"../Shader/ToonShader.h"
#include"../Shader/ShadowMapShader.h"

namespace
{
	constexpr int kMaxColHitPolyNum = 2000;	// �ő哖���蔻��|���S����
	constexpr int kMaxColHitTryNum = 16;	// �ǉ����o�������̍ő厎�s��
	constexpr float kColHitSlideLength = 1.0f;		// �ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kMove = 0.01f;			// �ړ��������𔻒f���邽�߂̕ϐ�
	constexpr float kWallPolyBorder = 0.4f;	// �ǃ|���S�������|���S�����𔻒f���邽�߂̕ϐ�
	constexpr float kWallPolyHeight = 20.0f;	// �ǃ|���S���Ɣ��f���邽�߂̍����ϐ�
	constexpr int kExistTimeCount = 10;		// ����ł���̎���
	constexpr float kHeadHeight = 40.0f;	// ���̍���
}


ObjectBase::ObjectBase():
	m_objSize(0.0f),
	m_angle(0.0f),
	m_moveSpeed(0.0f),
	m_modelH(-1),
	m_isDamage(false),
	m_isMove(false),
	m_isHit(false),
	m_wallNum(0),
	m_floorNum(0),
	m_hitDim{},
	m_pWallPoly{},
	m_pFloorPoly{},
	m_pPoly(nullptr),
	m_lineRes{},
	m_oldPos{0,0,0},
	m_nextPos{0,0,0}
{
	m_pExistCountTime = std::make_shared<Time>(kExistTimeCount);

	m_info.pos = VGet(0.0f, 0.0f, 0.0f);
	m_info.vec = VGet(0.0f, 0.0f, 0.0f);
	m_info.rot = VGet(0.0f, 0.0f, 0.0f);
	m_info.isExist = true;
}

ObjectBase::~ObjectBase()
{
	/*��������*/
}

void ObjectBase::Init()
{
	/*��������*/
}

void ObjectBase::Update(Input& input)
{
	/*��������*/
}

void ObjectBase::Draw(std::shared_ptr<ToonShader> pToonShader)
{
	/*��������*/
}

void ObjectBase::ShadowMapDraw(std::shared_ptr<ShadowMapShader> pShadowMapShader)
{
	// ���f�����Ȃ��ꍇ�͕`������Ȃ�
	if (m_pModel == nullptr) return;

	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		int shaderType = MV1GetTriangleListVertexType(m_pModel->GetModelHandle(), i);
		pShadowMapShader->SetShader(shaderType);

		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
}

void ObjectBase::Draw2D()
{
	/*��������*/
}

void ObjectBase::StageClear()
{
	/*��������*/
}

void ObjectBase::GameEnd()
{
	/*��������*/
}

void ObjectBase::OnAttack()
{
	/*��������*/
}

bool ObjectBase::IsExistCount()
{
	// �K�莞�Ԃ��߂����瑶�݂�����
	if (m_pExistCountTime->Update())
	{
		return true;
	}
	return false;
}

void ObjectBase::End()
{
	*m_pWallPoly = nullptr;
	*m_pFloorPoly = nullptr;
	m_pPoly = nullptr;
}

void ObjectBase::MoveCollFieldUpdate(ObjectBase* pField)
{
	// �ړ��O�̍��W��ۑ����Ă���
	m_oldPos = m_info.pos;
	// �ړ���̍��W���v�Z����
	m_nextPos = VAdd(m_oldPos, GetInfo().vec);

	// �v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
	// �ړ��������l�����Ă��猟�o����
	m_hitDim = MV1CollCheck_Sphere(pField->GetModel()->GetModelHandle(), -1, GetInfo().pos,
		dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius() + VSize(GetInfo().vec));

	// X��Z��kMove(0.01f)�ȏ�ړ������ꍇ�͈ړ��������ɂ���
	if (fabs(dynamic_cast<CharacterBase*>(this)->GetInfo().vec.x) > kMove || fabs(GetInfo().vec.z) > kMove)
	{
		m_isMove = true;
	}
	else
	{
		m_isMove = false;
	}

	// �ǂƏ��̓����蔻����s��
	CheckWallAndFloor();
	// �ǂƂ̓����蔻�肩��ʒu�C������������
	FixPosWithWall();
	// �ǂƂ̓����蔻�肩��ʒu�C������������
	FixPosWithFloor();

	// �V�������W��ۑ�����
	m_info.pos = m_nextPos;

	// ���o�����v���C���[�̎��͂̃|���S�������J������(��n��)
	MV1CollResultPolyDimTerminate(m_hitDim);
}

void ObjectBase::CheckWallAndFloor()
{
	// �ǃ|���S���Ə��|���S���̐�������������
	m_wallNum = 0;
	m_floorNum = 0;

	// ���o���ꂽ�|���S���̐������J��Ԃ�
	for (int i = 0; i < m_hitDim.HitNum; i++)
	{
		// �|���S���̖@����Y������kWallPolyBorder�ɒB���Ă��邩
		// �ǂ����ŕǃ|���S�������|���S�����𔻒f����
		if (m_hitDim.Dim[i].Normal.y < kWallPolyBorder && m_hitDim.Dim[i].Normal.y > -kWallPolyBorder)
		{
			// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A
			// �v���C���[��Y���W���������|���S���݂̂Ɠ����蔻����s��
			if (m_hitDim.Dim[i].Position[0].y > GetInfo().pos.y + kWallPolyHeight ||
				m_hitDim.Dim[i].Position[1].y > GetInfo().pos.y + kWallPolyHeight ||
				m_hitDim.Dim[i].Position[2].y > GetInfo().pos.y + kWallPolyHeight)
			{
				// �|���S���̐������E���ɒB���Ă��Ȃ������ꍇ�̓|���S����z��ɒǉ�����
				if (m_wallNum < ColInfo::kMaxColHitPolyNum)
				{
					// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
					m_pWallPoly[m_wallNum] = &m_hitDim.Dim[i];

					// �ǃ|���S���̐��𑫂�
					m_wallNum++;
				}
			}
		}
		else
		{
			// �|���S���̐������E���ɒB���Ă��Ȃ������ꍇ�̓|���S����z��ɒǉ�����
			if (m_floorNum < ColInfo::kMaxColHitPolyNum)
			{
				// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
				m_pFloorPoly[m_floorNum] = &m_hitDim.Dim[i];

				// ���|���S���̐��𑫂�
				m_floorNum++;
			}
		}
	}

}

void ObjectBase::FixPosWithWall()
{
	// �ǃ|���S�����Ȃ������ꍇ�͉������Ȃ�
	if (m_wallNum == 0)return;

	/*�ǃ|���S���Ƃ̓����蔻��̏���*/
	// �ǂɓ����������ǂ����̃t���O��false�ɂ��Ă���
	m_isHit = false;
	
	/*�ړ��������ǂ����ŏ����𕪊򂷂�*/
	// �ړ����Ă����ꍇ
	if (m_isMove)
	{
		// �ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_wallNum; i++)
		{
			// i�Ԗڂ̕ǂ̃|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾����
			m_pPoly = m_pWallPoly[i];

			// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g�ɍs��
			if (!HitCheck_Capsule_Triangle(m_nextPos,
				VAdd(m_nextPos, VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(), 0.0f)),
				dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

			// �������Ă����瓖�����Ă���t���O�𗧂Ă�
			m_isHit = true;

			/*�ǂ��l�������ړ��ʂ��O�ς��g���ďo��*/
			
			// �X���C�h�����鋗��
			VECTOR SlideVec;

			// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����o��
			SlideVec = VCross(dynamic_cast<CharacterBase*>(this)->GetInfo().vec, m_pPoly->Normal);

			// ���ŏo�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����o���A
			// ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g�����o��
			SlideVec = VCross(m_pPoly->Normal, SlideVec);

			// �ړ��O�̍��W��SlideVec�𑫂������̂����̍��W�ɂ���
			m_nextPos = VAdd(m_oldPos, SlideVec);

			/*�V�����ړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����𔻒肷��*/

			// �ǂƓ������Ă��邩�ǂ����̃t���O������Ă���
			bool isHitWallPoly = false;
			for (int j = 0; j < m_wallNum; j++)
			{
				// j�Ԗڂ̕ǂ̃|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾����
				m_pPoly = m_pWallPoly[j];

				// �|���S���ƃv���C���[���������Ă����烋�[�v���甲����
				if (HitCheck_Capsule_Triangle(m_nextPos,
					VAdd(m_nextPos, VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(), 0.0f)),
					dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(),
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
				{
					// �������Ă���t���O�𗧂Ă�
					isHitWallPoly = true;
					break;
				}
			}

			// �S�Ẵ|���S���Ɠ������Ă��Ȃ������烋�[�v���I���
			if (!isHitWallPoly)
			{
				// �������Ă���t���O��false�ɂ���
				m_isHit = false;
				break;
			}
		}
	}
	else
	{
		/*�ړ����Ă��Ȃ��ꍇ�̏���*/

		// �ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_wallNum; i++)
		{
			// i�Ԗڂ̕ǂ̃|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾����
			m_pPoly = m_pWallPoly[i];

			// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g�ɍs��
			if (HitCheck_Capsule_Triangle(m_nextPos,
				VAdd(m_nextPos, VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(), 0.0f)),
				dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
			{
				// �������Ă���t���O�𗧂Ă�
				m_isHit = true;
				break;
			}
		}
	}

	// �ǂɓ������Ă�����ǂ��牟���o������������
	if (m_isHit)
	{
		FixPosWithWallInternal();
	}
}

void ObjectBase::FixPosWithWallInternal()
{
	// �ǂ���̉����o�����������E�܂ŌJ��Ԃ�
	for (int i = 0; i < ColInfo::kMaxColHitTryNum; i++)
	{
		/*������\���̂���ǃ|���S����S�Č���*/

		// �ǂƓ������Ă��邩�ǂ���
		bool isHitWall = false;

		// �ǃ|���S���̐������J��Ԃ�
		for (int j = 0; j < m_wallNum; j++)
		{
			// j�Ԗڂ̕ǂ̃|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾����
			m_pPoly = m_pWallPoly[j];

			// �L�����N�^�[�Ɠ������Ă��邩�ǂ����𔻒肷��
			// �������Ă��Ȃ������玟�̃J�E���g�ɍs��
			if (!HitCheck_Capsule_Triangle(m_nextPos,
				VAdd(m_nextPos, VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(), 0.0f)),
				dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

			// �������Ă����ꍇ�͋K�苗�����v���C���[��ǂ̖@�������Ɉړ�������
			m_nextPos = VAdd(m_nextPos, VScale(m_pPoly->Normal, kColHitSlideLength));

			// �ړ����������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒肷��
			for (int k = 0; k < m_wallNum; k++)
			{
				// �������Ă����烋�[�v�𔲂���
				m_pPoly = m_pWallPoly[k];
				if (HitCheck_Capsule_Triangle(m_nextPos,
					VAdd(m_nextPos, VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(), 0.0f)),
					dynamic_cast<CharacterBase*>(this)->GetCircle()->GetRadius(),
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
				{
					isHitWall = true;
					break;
				}
			}

			// �S�Ẵ|���S���Ɠ������Ă��Ȃ������烋�[�v���I���
			if (!isHitWall) break;

		}
		// ���[�v�I��
		if (!isHitWall) break;
	}
}

void ObjectBase::FixPosWithFloor()
{
	// ���|���S���������ꍇ�͉������Ȃ�
	if (m_floorNum == 0) return;

	/*���|���S���Ƃ̓����蔻��*/
	// �����������ǂ����̃t���O�̏�����
	bool isHitFlag = false;

	// �W�����v�����㏸���̏ꍇ
	if (dynamic_cast<CharacterBase*>(this)->IsJump()
		&& dynamic_cast<CharacterBase*>(this)->GetJumpPower() >= 0.0f)
	{
		// �V��ɓ����Ԃ��鏈�����s��
		// ��ԒႢ�V��ɂԂ��邽�߂̔���p�ϐ�������������
		float polyMinPosY = 0.0f;

		// ���|���S���̐������J��Ԃ�
		for (int i = 0; i < m_floorNum; i++)
		{
			// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾����
			m_pPoly = m_pFloorPoly[i];

			// ���悩�瓪�̍����܂ł̊ԂŃ|���S���ƐڐG���Ă��邩�ǂ����𔻒肷��
			m_lineRes = HitCheck_Line_Triangle(m_nextPos, VAdd(m_nextPos, VGet(0.0f, kHeadHeight, 0.0f)),
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]);

			// �ڐG���Ă��Ȃ������ꍇ�͉��������Ɏ��̃J�E���g�ɍs��
			if (!m_lineRes.HitFlag) continue;

			// �V��|���S�������܂Ō��o���ꂽ�|���S�����Ⴂ�ꍇ�͏�����ʂ�
			if (polyMinPosY < m_lineRes.Position.y)
			{
				// ���������t���O�𗧂Ă�
				isHitFlag = true;

				// �ڐG����Y���W��ۑ�����
				polyMinPosY = m_lineRes.Position.y;
			}
		}

		// �ڐG���Ă���|���S�����������ꍇ
		if (isHitFlag)
		{
			// �ڐG�����ꍇ�̓v���C���[��Y���W��ڐG���W�����ƂɍX�V����
			m_nextPos.y = polyMinPosY - kHeadHeight;

			// �n�ʂɓ����������̏������s��
			dynamic_cast<CharacterBase*>(this)->HitGroundUpdate();
		}
	}
	else
	{
		/*���|���S���Ƃ̓����蔻��*/

		// ��ԍ������|���S���ɂԂ��邽�߂̔���p�ϐ�������������
		float polyMaxPosY = 0.0f;

		// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
		m_isHit = false;

		// ���|���S���̐������J��Ԃ�
		for (int i = 0; i < m_floorNum; i++)
		{
			// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾����
			m_pPoly = m_pFloorPoly[i];

			// ���悩�瓪�̍����܂ł̊ԂŃ|���S���ƐڐG���Ă��邩�ǂ����𔻒肷��
			m_lineRes = HitCheck_Line_Triangle(VAdd(m_nextPos, VGet(0.0f, kHeadHeight, 0.0f)),
				m_nextPos,m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]);

			// �������Ă��Ȃ������牽�������Ɏ��̃J�E���g�ɍs��
			if (!m_lineRes.HitFlag) continue;

			// ���ɓ��������|���S��������A�����܂Ō��o����
			// ���|���S�����Ⴂ�ꍇ�͉��������Ɏ��̃J�E���g�ɍs��
			if (m_isHit && polyMaxPosY > m_lineRes.Position.y) continue;

			// �|���S���ɓ��������t���O�𗧂Ă�
			m_isHit = true;

			// �ڐG����Y���W��ۑ�����
			polyMaxPosY = m_lineRes.Position.y;
		}

		if (m_isHit)
		{
			// �ڐG�����|���S���o��ԍ���Y���W���v���C���[��Y���W�ɂ���
			m_nextPos.y = polyMaxPosY;
			dynamic_cast<CharacterBase*>(this)->HitGroundUpdate();

			// �W�����v�����A�W�����v�͂�0����������(�~����)�̏ꍇ�̓W�����v�������I������
			if (dynamic_cast<CharacterBase*>(this)->GetJumpPower() <= 0.0f &&
				dynamic_cast<CharacterBase*>(this)->IsJump())
			{
				dynamic_cast<CharacterBase*>(this)->EndJump();
			}
		}
	}
}
