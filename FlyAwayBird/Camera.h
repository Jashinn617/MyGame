#pragma once
#include <memory>

using namespace std;

class Player;
class Input;

/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
public:
	Camera(shared_ptr<Player> player);
	~Camera();

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input">����</param>
	/// <param name="isOperate">���삪�ł��邩�ǂ���</param>
	void Update(Input& input, bool isOperate);

	/// <summary>
	/// �ʒu�̎擾
	/// </summary>
	/// <returns>���݈ʒu</returns>
	const VECTOR GetPos()const { return m_pos; }

private:	// �ϐ�
	VECTOR m_pos;	// �ʒu
	float m_angle;	// �p�x

	shared_ptr<Player> m_pPlayer;	// �v���C���[�̃|�C���^

private:	// �萔
	static constexpr float kCameraDist = 3.0f;		// �J�����̋���
	static constexpr float kCameraHeight = 2.2f;	// �J�����̍���
	static constexpr float kCameraNear = 0.5f;		// �J�����̍ŒZ�`�拗��
	static constexpr float kCameraFar = 1000.0f;	// �J�����̍Œ��`�拗��
	static constexpr float kSpeed = 0.025f;			// ��]���ړ����x
};

