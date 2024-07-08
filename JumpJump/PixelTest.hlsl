SamplerState smp : register(s0);
Texture2D<float4> tex : register(t0);

// �e�X�g�p�s�N�Z���V�F�[�_

// ���_�V�F�[�_�[�̓���
struct PS_INPUT
{
    float4 Diffuse : COLOR0; // �f�B�t���[�Y�J���[
    float4 Specular : COLOR1; // �X�y�L�����J���[
    float3 Normal : NORMAL;
    float2 TexCoords0 : TEXCOORD0; // �e�N�X�`�����W
    float4 svPosition : SV_POSITION; // ���W(�v���W�F�N�V�������)
    float4 Position : POSITION0; // ���W(���[���h���)
    float4 P : POSITION1; // ���W(�v���W�F�N�V�������)
    float4 VPosition : POSITION2; // ���W(���[���h���*�r���[���)
};

struct PS_OUTPUT
{
    float4 color : SV_Target0; // �F
    float4 depth : SV_Target1; // �[�x�l
    float4 normal : SV_Target2; // �@�����
};

float4 main(PS_INPUT input) : SV_Target
{
    // ���f���̃f�B�t���[�Y�J���[���g�p���ĐF���o��
    return input.Diffuse.brga;
}