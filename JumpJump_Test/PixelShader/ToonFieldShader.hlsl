SamplerState smp : register(s0); // �f�B�t���[�Y�}�b�v�e�N�X�`��

Texture2D tex : register(t0); // �f�B�t���[�Y�}�b�v�e�N�X�`��
Texture2D shadowMapSmp : register(t1); // �f�B�t���[�Y�}�b�v�e�N�X�`��

struct PS_INPUT
{
    float4 Diffuse : COLOR0; // �f�B�t���[�Y�J���[
    float4 Specular : COLOR1; // �X�؃L�����J���[
    float4 TexCoords0_1 : TEXCOORD0; // xy:�e�N�X�`�����W zw:�T�u�e�N�X�`�����W
    float3 VPosition : TEXCOORD1; // ���W(�r���[���)
    float3 VNormal : TEXCOORD2; // �@��(�r���[���)
    float1 Fog : TEXCOORD5; // �t�H�O�p�����[�^(x)
    float4 Position : SV_POSITION; // ���W(�v���W�F�N�V�������)
    float4 posInLVP : TEXCOORD3;    // ���C�g�r���[�X�N���[����Ԃł̃s�N�Z�����W    
};

struct PS_OUTPUT
{
    float4 col : SV_TARGET0; // �F
    float4 depth : SV_TARGET1; // �[�x
    float4 norm : SV_TARGET2; // �@��
};

cbuffer ConstantBuffer : register(b0)
{
    // ���C�g�̌����̐ݒ�
    float3 m_lightDir;
}

cbuffer ConstantBuffer : register(b1)
{
    // �J�����̃^�[�Q�b�g�̍��W�̐ݒ�
    float3 m_cameraTarget;
}

cbuffer ConstantBuffer : register(b2)
{
    // �J�����̍��W�̐ݒ�
    float3 m_cameraPos;
}

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT ret;
    
    ret.depth = input.Position.zwyx;
    ret.col = input.Diffuse;
    ret.norm = float4(input.VNormal, 1.0f);
    
    // ���C�g�̌����̐ݒ�
    float3 lightDir = m_lightDir;
    lightDir = normalize(lightDir);
    
    // �@�����̐��K��
    float3 n = normalize(input.VNormal);
    
    // ���̋������v�Z����
    // ���C�g�̕����Ɩ@�������̓���
    float bright = dot(lightDir, n);
    
    // ���̋�����i�K��������
    bright = round(bright * 4) / 4;
    
    // ���̋�����0.6f�ȉ��ɂ͂Ȃ�Ȃ��悤�ɂ���
    bright = max(bright, 0.6f);
    
    // ���̋�����1.0f�ȏ�ɂȂ�Ȃ��悤�ɂ���
    bright = min(bright, 1.0f);
    
    ///*�e�̏���*/
    //float2 uv = input.posInLVP.xy / input.posInLVP.w;
    //uv = uv * float2(0.5f, 0.5f);
    //uv += 0.5f;
    
    //// �e�����]���Ȃ��悤�ɂ���
    //uv.y *= -1;
    //uv.y += 1.0f;
    
    //float4 shadowMap = float4(0.0f, 0.0f, 0.0f, 1.0f);
    
    //// �e�̃T���v�����O������
    //shadowMap = shadowMapSmp.Sample(smp, uv);
    
    //// �e���𔽉f���ꂽ�F��Ԃ�
    //ret.col.rgb = ret.col.rgb * shadowMap.rgb * bright;
    
    ret.col.rgb = ret.col.rgb * bright;
    
    return ret;
}
