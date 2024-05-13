#pragma once
#include <unordered_map>
#include <string>

using namespace std;

// <�n���h����,�n���h��>
using HandleTable_t = unordered_map<string, int>;

/// <summary>
/// �e�n���h���̊Ǘ�������N���X
/// </summary>
class HandleManager
{
public:
	HandleManager();
	~HandleManager();

	/// <summary>
	/// ���f���n���h�����擾����
	/// </summary>
	/// <param name="command">�n���h����</param>
	/// <returns>�n���h��</returns>
	int GetModel(const char* command)const;
	/// <summary>
	/// �摜�n���h�����擾����
	/// </summary>
	/// <param name="command">�n���h����</param>
	/// <returns>�n���h��</returns>
	int GetImg(const char* command)const;
	/// <summary>
	/// �T�E���h�n���h�����擾����
	/// </summary>
	/// <param name="command">�n���h����</param>
	/// <returns>�n���h��</returns>
	int GetSound(const char* command)const;
	/// <summary>
	/// �t�H���g�̃n���h�����擾����
	/// </summary>
	/// <param name="command">�n���h����</param>
	/// <returns>�n���h��</returns>
	int GetFont(const char* command)const;

private:	// �֐�
	/// <summary>
	/// ���f���̃��[�h
	/// </summary>
	void LoadModel();
	/// <summary>
	/// �摜�̃��[�h
	/// </summary>
	void LoadImg();
	/// <summary>
	/// �T�E���h�̃��[�h
	/// </summary>
	void LoadSound();
	/// <summary>
	/// �t�H���g�̃��[�h
	/// </summary>
	void LoadFont();

	/// <summary>
	/// ���f���̃f���[�g
	/// </summary>
	void DeleteModel();
	/// <summary>
	/// �摜�̃f���[�g
	/// </summary>
	void DeleteImg();
	/// <summary>
	/// �T�E���h�̃f���[�g
	/// </summary>
	void DeleteSound();
	/// <summary>
	///  �t�H���g�̃f���[�g
	/// </summary>
	void DeleteFont();

private:// �ϐ�
	/*�n���h�����ƃn���h�����y�A�ɂ����e�[�u��*/
	HandleTable_t m_modelHandleTable;	// 3D���f���̃n���h��
	HandleTable_t m_imgHandleTable;		// �摜�̃n���h��
	HandleTable_t m_soundHandleTable;	// �T�E���h�̃n���h��
};

