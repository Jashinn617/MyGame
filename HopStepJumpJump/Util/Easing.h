#pragma once

namespace Easing
{
	
	/// <summary>
	/// �e���v���[�g�N���X
	/// �C�[�W���O�֐����e���v���[�g�֐��ɂ���
	/// �����̌^��ς�����悤�ɂ���
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="t">�o�ߎ���</param>
	/// <param name="b">�����l</param>
	/// <param name="c">�ω���</param>
	/// <param name="d">������</param>
	/// <returns>�ω���̒l</returns>
	template<typename T>
	inline T Linear(T t, T b, T c, T d)
	{
		return c * t / d + b;
	}

	template<typename T>
	inline T InQuad(T t, T b, T c, T d)
	{
		t /= d;
		return c * t * t + b;
	}

	template<typename T>
	inline T OutQuad(T t, T b, T c, T d)
	{
		t /= d;
		return -c * t * (t - 2) + b;
	}

	template<typename T>
	inline T InOutQuad(T t, T b, T c, T d)
	{
		t /= d / 2;
		if (t < 1) return c / 2 * t * t + b;
		--t;
		return -c / 2 * (t * (t - 2) - 1) + b;
	}

	template<typename T>
	inline T InCubic(T t, T b, T c, T d)
	{
		t /= d;
		return c * t * t * t + b;
	}

	template<typename T>
	inline T OutCubic(T t, T b, T c, T d)
	{
		t /= d;
		--t;
		return c * (t * t * t + 1) + b;
	}

	template<typename T>
	inline T InOutCubic(T t, T b, T c, T d)
	{
		t /= d / 2;
		if (t < 1) return c / 2 * t * t * t + b;
		t -= 2;
		return c / 2 * (t * t * t + 2) + b;
	}

	template<typename T>
	inline T InQuart(T t, T b, T c, T d)
	{
		t /= d;
		return c * t * t * t * t + b;
	}

	template<typename T>
	inline T OutQuart(T t, T b, T c, T d)
	{
		t /= d;
		--t;
		return -c * (t * t * t * t - 1);
	}

	template<typename T>
	inline T EaseOutCubic(T t, T b, T c, T d)
	{
		t /= d;
		t--;
		return c * (t * t * t + 1) + b * (1 - (t * t * t + 1));
	}
}