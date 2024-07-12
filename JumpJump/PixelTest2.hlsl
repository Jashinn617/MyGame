Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);
#define DX_D3D11_COMMON_CONST_LIGHT_NUM			(6)		// ���ʃp�����[�^�̃��C�g�̍ő吔
#define DX_LIGHTTYPE_POINT							(1)				// D_D3DLIGHT_POINT
#define DX_LIGHTTYPE_SPOT							(2)				// D_D3DLIGHT_SPOT
#define DX_LIGHTTYPE_DIRECTIONAL					(3)				// D_D3DLIGHT_DIRECTIONAL
// ���C�g�p�����[�^
struct DX_D3D11_CONST_LIGHT
{
    int Type; // ���C�g�^�C�v( DX_LIGHTTYPE_POINT �Ȃ� )
    int3 Padding1; // �p�f�B���O�P

    float3 Position; // ���W( �r���[��� )
    float RangePow2; // �L�������̂Q��

    float3 Direction; // ����( �r���[��� )
    float FallOff; // �X�|�b�g���C�g�pFallOff

    float3 Diffuse; // �f�B�t���[�Y�J���[
    float SpotParam0; // �X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0f ) )

    float3 Specular; // �X�y�L�����J���[
    float SpotParam1; // �X�|�b�g���C�g�p�p�����[�^�P( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )

    float4 Ambient; // �A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������

    float Attenuation0; // �����ɂ�錸�������p�p�����[�^�O
    float Attenuation1; // �����ɂ�錸�������p�p�����[�^�P
    float Attenuation2; // �����ɂ�錸�������p�p�����[�^�Q
    float Padding2; // �p�f�B���O�Q
};
// �}�e���A���p�����[�^
struct DX_D3D11_CONST_MATERIAL
{
    float4 Diffuse; // �f�B�t���[�Y�J���[
    float4 Specular; // �X�y�L�����J���[
    float4 Ambient_Emissive; // �}�e���A���G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[

    float Power; // �X�y�L�����̋���
    float TypeParam0; // �}�e���A���^�C�v�p�����[�^0
    float TypeParam1; // �}�e���A���^�C�v�p�����[�^1
    float TypeParam2; // �}�e���A���^�C�v�p�����[�^2
};

// �t�H�O�p�����[�^
struct DX_D3D11_VS_CONST_FOG
{
    float LinearAdd; // �t�H�O�p�p�����[�^ end / ( end - start )
    float LinearDiv; // �t�H�O�p�p�����[�^ -1  / ( end - start )
    float Density; // �t�H�O�p�p�����[�^ density
    float E; // �t�H�O�p�p�����[�^ ���R�ΐ��̒�

    float4 Color; // �J���[
};

// �s�N�Z���V�F�[�_�[�E���_�V�F�[�_�[���ʃp�����[�^
struct DX_D3D11_CONST_BUFFER_COMMON
{
    DX_D3D11_CONST_LIGHT Light[DX_D3D11_COMMON_CONST_LIGHT_NUM]; // ���C�g�p�����[�^
    DX_D3D11_CONST_MATERIAL Material; // �}�e���A���p�����[�^
    DX_D3D11_VS_CONST_FOG Fog; // �t�H�O�p�����[�^
};
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    DX_D3D11_CONST_BUFFER_COMMON g_Common;
};

// ���_�V�F�[�_�[�̏o��
struct PS_INPUT
{
    float4 Diffuse : COLOR0; // �f�B�t���[�Y�J���[
    float4 Specular : COLOR1; // �X�y�L�����J���[
    float3 Normal : NORMAL;
    float2 uv : TEXCOORD0; // �e�N�X�`�����W
    float4 svPosition : SV_POSITION; // ���W( �v���W�F�N�V������� )//P�Ɠ��l
    float4 Position : POSITION0; // ���W(���[���h��� )//
    float4 P : POSITION1; // ���W( �v���W�F�N�V������� )//3D��2D�ɐ��K�����ꂽ���W
    float4 VPosition : POSITION2; // ���W(���[���h���*�r���[ )//
};
float4 main(PS_INPUT input) : SV_TARGET
{  
    float amb = 0.25;
    float b = max(dot(normalize(-g_Common.Light[0].Direction), input.Normal), amb);
    float4 col = tex.Sample(smp, input.uv);
    
    
    // �m�[�}���}�b�v�̕\��
    return float4(input.Normal, 1);
    
    return float4(col.rbg * b, col.a);
}