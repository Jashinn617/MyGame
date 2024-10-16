#include "ObjectBase.h"

#include "CharacterBase.h"
#include "Model.h"

#include "../Shader/VertexShader.h"

#include "../Utility/Sphere.h"

namespace
{
	constexpr int kMaxColHitPolyNum = 2000;		// �ő哖���蔻��|���S����
	constexpr int kMaxColHitTryNum = 16;		// �ǉ����o�������̍ő厎�s��
	constexpr float kColHitSlideLength = 1.0f;	// �ǉ����o�����ɃX���C�h�����鋗��
	constexpr float kMove = 0.01f;				// �ړ��������𔻒f���邽�߂̕ϐ�
	constexpr float kWallPolyBorder = 0.4f;		// �ǃ|���S�������|���S�����𔻒f����ׂ̕ϐ�
	constexpr float kWallPolyHeight = 20.0f;	// �ǃ|���S���Ɣ��f���邽�߂̍����ϐ�
	constexpr float kHeadHeight = 40.0f;		// ���̍���
}

ObjectBase::ObjectBase():
	m_modelH(-1),
	m_objSize(0.0f),
	m_angle(0.0f),
	m_moveSpeed(0.0f),
	m_isDamage(false),
	m_pModel(nullptr),
	m_pVertexShader(std::make_shared<VertexShader>()),
	m_pObjectManager(nullptr),
	m_wallNum(0),
	m_floorNum(0),
	m_isMove(false),
	m_isPolyHit(false),
	m_prevPos{0.0f,0.0f,0.0f},
	m_nextPos{0.0f,0.0f,0.0f},
	m_pPoly(nullptr)
{
	// �L�����N�^�[���̏�����
	m_characterInfo.pos = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.vec = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.rot = VGet(0.0f, 0.0f, 0.0f);
	m_characterInfo.isExist = true;
}

ObjectBase::~ObjectBase()
{
	/*��������*/
}

void ObjectBase::End()
{
	/*�|�C���^�̉��*/
	*m_pWallPoly = nullptr;
	*m_pFloorPoly = nullptr;
	m_pPoly = nullptr;
}

void ObjectBase::ShaderMapDraw(std::shared_ptr<ShadowMapShader> pShadowMapShader)
{
	// ���f���|�C���^�������ꍇ�͉������Ȃ�
	if (m_pModel == nullptr)return;

	for (int i = 0; i < MV1GetTriangleListNum(m_pModel->GetModelHandle()); i++)
	{
		// �V�F�[�_�̐ݒ�

		// �`��
		MV1DrawTriangleList(m_pModel->GetModelHandle(), i);
	}
	// �V�F�[�_���g��Ȃ��ݒ�ɖ߂�

}

void ObjectBase::MoveCollField(ObjectBase* pField)
{
	// �ړ��O�̍��W��ۑ�����
	m_prevPos = m_characterInfo.pos;
	// �ړ���̍��W���v�Z����
	m_nextPos = VAdd(m_prevPos, m_characterInfo.vec);

	/*���͂ɂ���X�e�[�W�|���S�����ړ��������l�����Ď擾����
	(���f���n���h��,
	�R���W���������X�V����t���[���ԍ�,�����蔻��p�̋��̒��S���W,
	���̔��a)*/
	m_hitDin = MV1CollCheck_Sphere(pField->GetModel()->GetModelHandle(), 
		-1, m_characterInfo.pos,
		dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius() + VSize(m_characterInfo.vec));

	// X,Z�����ւ̈ړ��ʂ�0.01f�ȉ��������ꍇ�͈ړ������Ă��Ȃ����Ƃɂ���
	if (fabs(m_characterInfo.vec.x) <= kMove || fabs(m_characterInfo.vec.z) > kMove)
	{
		m_isMove = false;
	}
	else // 0.01f�ȏゾ������ړ����������Ƃɂ���
	{
		m_isMove = true;
	}

	// �ǂƏ��̓����蔻����s��
	CheckWallAndFloor();
	// �ǂƂ̓����蔻�肩��ʒu�C���������s��
	FixPosWithWall();
	// ���Ƃ̓����蔻�肩��ʒu�C���������s��
	FixPosWithFloor();

	// �V�������W��ۑ�����
	m_characterInfo.pos = m_nextPos;

	// ���o�����v���C���[�̎��͂̃|���S�������������(��n��)
	MV1CollResultPolyDimTerminate(m_hitDin);
}

void ObjectBase::CheckWallAndFloor()
{
	// �ǃ|���S���Ə��|���S���̐�������������
	m_wallNum = 0;
	m_floorNum = 0;

	// ���o���ꂽ�|���S���̐������J��Ԃ�
	for (int i = 0; i < m_hitDin.HitNum; i++)
	{
		/*�|���S���̖@����Y�������قڏc�ɐ������ǂ�����
		�ǃ|���S�������|���S�����𔻒f����
		(0.4f�ȏ�΂߂ɂȂ��Ă����珰�|���S������ɂ���)*/
		if (m_hitDin.Dim[i].Normal.y < kWallPolyBorder &&
			m_hitDin.Dim[i].Normal.y > -kWallPolyBorder) // �ǂ������ꍇ
		{
			// �|���S���̐������E���ɒB���Ă��Ȃ������ꍇ
			if (m_wallNum < ColInfo::kMaxColHitPolyNum)
			{
				// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�ɕۑ�����
				m_pWallPoly[m_wallNum] = &m_hitDin.Dim[i];
				// �ǃ|���S���̐��𑫂�
				m_wallNum++;
			}
		}
		else	// ���|���S���̏ꍇ
		{
			// �|���S���̐������E���ɒB���Ă��Ȃ������ꍇ
			if (m_floorNum < ColInfo::kMaxColHitPolyNum)
			{
				// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�ɕۑ�����
				m_pFloorPoly[m_floorNum] = &m_hitDin.Dim[i];
				// ���|���S���̐��𑫂�
				m_floorNum++;
			}
		}
	}
}

void ObjectBase::FixPosWithWall()
{
	// �ǃ|���S�������������ꍇ�͉������Ȃ�
	if (m_wallNum == 0)return;

	/*�ǃ|���S���Ƃ̓����蔻��̏���*/

	// �ǂɓ����������ǂ����̃t���O��false�ɂ��Ă���
	m_isPolyHit = false;

	/*�ړ����Ă��邩�ǂ����ŏ����𕪊򂷂�*/
	if (m_isMove)	// �ړ����Ă����ꍇ
	{
		// �ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_wallNum; i++)
		{
			// i�Ԗڂ̕ǂ̃|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾����
			m_pPoly = m_pWallPoly[i];

			// �|���S���ƃL�����N�^�[���������Ă��Ȃ������玟�̃J�E���g�ɍs��
			if (!HitCheck_Capsule_Triangle(m_nextPos,
				VAdd(m_nextPos,
					VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(), 0.0f)),
				dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

			// �������Ă��Ȃ������瓖�����Ă���t���O�𗧂Ă�
			m_isPolyHit = true;

			/*�ǂ��l�������ړ��ʂ��O�ς��g���ďo��*/
			// �X���C�h�����鋗��
			VECTOR slideVec;
			// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����o��
			slideVec = VCross(m_characterInfo.vec, m_pPoly->Normal);
			/*���ŏo�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����o���A
			���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g�����o��*/
			slideVec = VCross(m_pPoly->Normal, slideVec);
			// �ړ��O�̍��W�ɃX���C�h�����鋗���𑫂������̂����̍��W�ɂ���
			m_nextPos = VAdd(m_prevPos, slideVec);

			/*�V�����ړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����𔻒肷��*/
			// �ǂƓ������Ă��邩�ǂ����̃t���O�����
			bool isHitWallPoly = false;
			// �ǃ|���S���̐������J��Ԃ�
			for (int j = 0; j < m_wallNum; j++)
			{
				// j�Ԗڂ̕ǂ̃|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾����
				m_pPoly = m_pWallPoly[j];

				// �|���S���ƃL�����N�^�[���������Ă����ꍇ
				if (HitCheck_Capsule_Triangle(m_nextPos,
					VAdd(m_nextPos,
						VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(), 0.0f)),
					dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(),
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
				{
					// �������Ă���t���O�𗧂Ă�
					isHitWallPoly = true;
					// ���[�v���甲����
					break;
				}
			}
			// �S�Ẵ|���S���Ɠ������Ă��Ȃ������ꍇ
			if (!isHitWallPoly)
			{
				// �������Ă���t���O��false�ɂ���
				m_isPolyHit = false;
				// ���[�v���甲����
				break;
			}
		}
	}
	else	// �ړ����Ă��Ȃ������ꍇ
	{
		// �ǃ|���S���̐������J��Ԃ�
		for (int i = 0; i < m_wallNum; i++)
		{
			// i�Ԗڂ̕ǂ̃|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾����
			m_pPoly = m_pWallPoly[i];

			// �|���S���ƃL�����N�^�[���������Ă����ꍇ
			if (HitCheck_Capsule_Triangle(m_nextPos,
				VAdd(m_nextPos,
					VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(), 0.0f)),
				dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
			{
				// �������Ă���t���O�𗧂Ă�
				m_isPolyHit = true;
				// ���[�v�𔲂���
				break;
			}
		}
	}

	// �ǂɓ������Ă����ꍇ�ǂ���̉����o������������
	if (m_isPolyHit) FixPosWithWallInternal();
}

void ObjectBase::FixPosWithWallInternal()
{
	// �ǂ���̉����o�����������E�܂ŌJ��Ԃ�
	for (int i = 0; i < ColInfo::kMaxColHitTryNum; i++)
	{
		/*������\���̂���ǃ|���S����S�Č���*/
		// �ǂƓ������Ă��邩�ǂ����̃t���O
		bool isHitWall = false;

		// �ǃ|���S���̐������J��Ԃ�
		for (int j = 0; j < m_wallNum; j++)
		{
			// j�Ԗڂ̕ǂ̃|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾����
			m_pPoly = m_pWallPoly[j];

			// �|���S���ƃL�����N�^�[���������Ă��Ȃ������玟�̃J�E���g�ɍs��
			if (!HitCheck_Capsule_Triangle(m_nextPos,
				VAdd(m_nextPos,
					VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(), 0.0f)),
				dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(),
				m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2])) continue;

			// �������Ă����ꍇ�͊�ꋗ�����A�ǂ̖@�������Ɉړ�������
			m_nextPos = VAdd(m_nextPos, VScale(m_pPoly->Normal, kColHitSlideLength));

			// �ړ����������ŕǃ|���S���ƐڐG���Ă��邩�ǂ����𔻒肷��
			for (int k = 0; k < m_wallNum; k++)
			{
				m_pPoly = m_pWallPoly[k];
				// �������Ă����ꍇ
				if (HitCheck_Capsule_Triangle(m_nextPos,
					VAdd(m_nextPos,
						VGet(0.0f, dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(), 0.0f)),
					dynamic_cast<CharacterBase*>(this)->GetSphere()->GetRadius(),
					m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]))
				{
					// �������Ă���t���O�𗧂Ă�
					isHitWall = true;
					// ���[�v�𔲂���
					break;
				}
			}
			// �S�Ẵ|���S���Ɠ������Ă��Ȃ������烋�[�v���I���
			if (!isHitWall) break;
		}
		// ���[�v���I���
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
	if (dynamic_cast<CharacterBase*>(this)->IsJump() &&
		dynamic_cast<CharacterBase*>(this)->GetJumpPower() >= 0.0f)
	{
		/*�V��ɓ����Ԃ��鏈�����s��*/
		// ��ԒႢ�V��ɂԂ���ׂ̔���p�ϐ�������������
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
			// �ڐG�����ꍇ�̓v���C���[��Y���W��ڐG���W�����ɍX�V����
			m_nextPos.y = polyMinPosY - kHeadHeight;
			// �W�����v�͂𔽓]���ĉ��~������
			dynamic_cast<CharacterBase*>(this)->InvertJumpPower();
			// �n�ʂɓ����������̏������s��
			dynamic_cast<CharacterBase*>(this)->HitGround();
		}
	}
	else	// �W�����v�ł͖����A���~���������ꍇ
	{
		/*���|���S���Ƃ̓����蔻��*/
		// ��ԍ������|���S���ɂԂ��邽�߂̔���p�ϐ�������������
		float polyMaxPosY = 0.0f;

		// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
		m_isPolyHit = false;

		// ���|���S���̐������J��Ԃ�
		for (int i = 0; i < m_floorNum; i++)
		{
			// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾����
			m_pPoly = m_pFloorPoly[i];

			// ���悩�瓪�̍����܂ł̊ԂŃ|���S���ƐڐG���Ă��邩�ǂ����𔻒肷��
			m_lineRes = HitCheck_Line_Triangle(VAdd(m_nextPos, VGet(0.0f, kHeadHeight, 0.0f)),
				m_nextPos, m_pPoly->Position[0], m_pPoly->Position[1], m_pPoly->Position[2]);

			// �������Ă��Ȃ������牽�������Ɏ��̃J�E���g�ɍs��
			if (!m_lineRes.HitFlag) continue;

			// ���ɓ��������|���S��������A�����܂Ō��o����
			// ���|���S�����Ⴂ�ꍇ�͉��������Ɏ��̃J�E���g�ɍs��
			if (m_isPolyHit && polyMaxPosY > m_lineRes.Position.y) continue;

			// �|���S���ɓ��������t���O�𗧂Ă�
			m_isPolyHit = true;

			// �ڐG����Y���W��ۑ�����
			polyMaxPosY = m_lineRes.Position.y;
		}

		if (m_isPolyHit)	// ���ɓ������Ă����ꍇ
		{
			// �ڐG�����|���S���o��ԍ���Y���W���v���C���[��Y���W�ɂ���
			m_nextPos.y = polyMaxPosY;
			dynamic_cast<CharacterBase*>(this)->HitGround();

			// �W�����v�����A�W�����v�͂�0����������(�~����)�̏ꍇ�̓W�����v�������I������
			if (dynamic_cast<CharacterBase*>(this)->GetJumpPower() <= 0.0f &&
				dynamic_cast<CharacterBase*>(this)->IsJump())
			{
				dynamic_cast<CharacterBase*>(this)->EndJump();
			}
		}
	}
}