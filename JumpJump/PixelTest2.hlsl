Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);
#define DX_D3D11_COMMON_CONST_LIGHT_NUM			(6)		// 共通パラメータのライトの最大数
#define DX_LIGHTTYPE_POINT							(1)				// D_D3DLIGHT_POINT
#define DX_LIGHTTYPE_SPOT							(2)				// D_D3DLIGHT_SPOT
#define DX_LIGHTTYPE_DIRECTIONAL					(3)				// D_D3DLIGHT_DIRECTIONAL
// ライトパラメータ
struct DX_D3D11_CONST_LIGHT
{
    int Type; // ライトタイプ( DX_LIGHTTYPE_POINT など )
    int3 Padding1; // パディング１

    float3 Position; // 座標( ビュー空間 )
    float RangePow2; // 有効距離の２乗

    float3 Direction; // 方向( ビュー空間 )
    float FallOff; // スポットライト用FallOff

    float3 Diffuse; // ディフューズカラー
    float SpotParam0; // スポットライト用パラメータ０( cos( Phi / 2.0f ) )

    float3 Specular; // スペキュラカラー
    float SpotParam1; // スポットライト用パラメータ１( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )

    float4 Ambient; // アンビエントカラーとマテリアルのアンビエントカラーを乗算したもの

    float Attenuation0; // 距離による減衰処理用パラメータ０
    float Attenuation1; // 距離による減衰処理用パラメータ１
    float Attenuation2; // 距離による減衰処理用パラメータ２
    float Padding2; // パディング２
};
// マテリアルパラメータ
struct DX_D3D11_CONST_MATERIAL
{
    float4 Diffuse; // ディフューズカラー
    float4 Specular; // スペキュラカラー
    float4 Ambient_Emissive; // マテリアルエミッシブカラー + マテリアルアンビエントカラー * グローバルアンビエントカラー

    float Power; // スペキュラの強さ
    float TypeParam0; // マテリアルタイプパラメータ0
    float TypeParam1; // マテリアルタイプパラメータ1
    float TypeParam2; // マテリアルタイプパラメータ2
};

// フォグパラメータ
struct DX_D3D11_VS_CONST_FOG
{
    float LinearAdd; // フォグ用パラメータ end / ( end - start )
    float LinearDiv; // フォグ用パラメータ -1  / ( end - start )
    float Density; // フォグ用パラメータ density
    float E; // フォグ用パラメータ 自然対数の低

    float4 Color; // カラー
};

// ピクセルシェーダー・頂点シェーダー共通パラメータ
struct DX_D3D11_CONST_BUFFER_COMMON
{
    DX_D3D11_CONST_LIGHT Light[DX_D3D11_COMMON_CONST_LIGHT_NUM]; // ライトパラメータ
    DX_D3D11_CONST_MATERIAL Material; // マテリアルパラメータ
    DX_D3D11_VS_CONST_FOG Fog; // フォグパラメータ
};
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    DX_D3D11_CONST_BUFFER_COMMON g_Common;
};

// 頂点シェーダーの出力
struct PS_INPUT
{
    float4 Diffuse : COLOR0; // ディフューズカラー
    float4 Specular : COLOR1; // スペキュラカラー
    float3 Normal : NORMAL;
    float2 uv : TEXCOORD0; // テクスチャ座標
    float4 svPosition : SV_POSITION; // 座標( プロジェクション空間 )//Pと同様
    float4 Position : POSITION0; // 座標(ワールド空間 )//
    float4 P : POSITION1; // 座標( プロジェクション空間 )//3D→2Dに正規化された座標
    float4 VPosition : POSITION2; // 座標(ワールド空間*ビュー )//
};
float4 main(PS_INPUT input) : SV_TARGET
{  
    float amb = 0.25;
    float b = max(dot(normalize(-g_Common.Light[0].Direction), input.Normal), amb);
    float4 col = tex.Sample(smp, input.uv);
    
    
    // ノーマルマップの表示
    return float4(input.Normal, 1);
    
    return float4(col.rbg * b, col.a);
}