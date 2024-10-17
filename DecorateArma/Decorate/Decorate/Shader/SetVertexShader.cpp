#include "SetVertexShader.h"
#include "DxLib.h"

#include <cassert>

SetVertexShader::SetVertexShader()
{
	/*シェーダのロード
	ロードに失敗したら止める*/
	m_vertexShader1FrameH = LoadVertexShader("Data/Shader/VertexShader/VertexShader3D.vso");
	assert(m_vertexShader1FrameH != -1);
	m_vertexShader4FrameH = LoadVertexShader("Data/Shader/VertexShader/VertexShader3D4Frame.vso");
	assert(m_vertexShader4FrameH != -1);
	m_vertexShader8FrameH = LoadVertexShader("Data/Shader/VertexShader/VertexShader3D8Frame.vso");
	assert(m_vertexShader8FrameH != -1);
	m_vertexShaderNormal4FrameH = LoadVertexShader("Data/Shader/VertexShader/VertexShader3DNormal4Frame.vso");
	assert(m_vertexShaderNormal4FrameH != -1);
	m_vertexShaderNormal8FrameH = LoadVertexShader("Data/Shader/VertexShader/VertexShader3DNormal4Frame.vso");
	assert(m_vertexShaderNormal8FrameH != -1);
}

SetVertexShader::~SetVertexShader()
{
	/*シェーダのデリート*/
	DeleteShader(m_vertexShader1FrameH);
	DeleteShader(m_vertexShader4FrameH);
	DeleteShader(m_vertexShader8FrameH);
	DeleteShader(m_vertexShaderNormal4FrameH);
	DeleteShader(m_vertexShaderNormal8FrameH);
}

int SetVertexShader::SetVertexShaderH(int vertexShaderType)
{
	// シェーダのタイプによって返すハンドルを変える
	if (vertexShaderType == DX_MV1_VERTEX_TYPE_1FRAME)
	{
		return m_vertexShader1FrameH;
	}
	else if (vertexShaderType == DX_MV1_VERTEX_TYPE_4FRAME)
	{
		return m_vertexShader4FrameH;
	}
	else if (vertexShaderType == DX_MV1_VERTEX_TYPE_8FRAME)
	{
		return m_vertexShader8FrameH;
	}
	else if (vertexShaderType == DX_MV1_VERTEX_TYPE_NMAP_1FRAME)
	{
		return m_vertexShader1FrameH;
	}
	else if (vertexShaderType == DX_MV1_VERTEX_TYPE_NMAP_4FRAME)
	{
		return m_vertexShaderNormal4FrameH;
	}
	else if (vertexShaderType == DX_MV1_VERTEX_TYPE_NMAP_8FRAME)
	{
		return m_vertexShaderNormal8FrameH;
	}
	else if (vertexShaderType == DX_MV1_VERTEX_TYPE_NMAP_FREE_FRAME)
	{
		return m_vertexShader1FrameH;
	}
	else
	{
		return -1;
	}

	return -1;
}
