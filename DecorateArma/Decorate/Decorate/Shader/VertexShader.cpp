#include "VertexShader.h"
#include "DxLib.h"

#include <cassert>

VertexShader::VertexShader()
{
	/*シェーダのロード
	ロードに失敗したら止める*/
	m_vertexShader1FrameH = LoadVertexShader("");

	m_vertexShader4FrameH = LoadVertexShader("");
	
	m_vertexShader8FrameH = LoadVertexShader("");

	m_vertexShaderNormal4FrameH = LoadVertexShader("");

	m_vertexShaderNormal8FrameH = LoadVertexShader("");
}

VertexShader::~VertexShader()
{
	/*シェーダのデリート*/
	DeleteShader(m_vertexShader1FrameH);
	DeleteShader(m_vertexShader4FrameH);
	DeleteShader(m_vertexShader8FrameH);
	DeleteShader(m_vertexShaderNormal4FrameH);
	DeleteShader(m_vertexShaderNormal8FrameH);
}

int VertexShader::SetVertexShaderH(int vertexShaderType)
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
