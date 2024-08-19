SamplerState smp : register(s0);    // ディフューズマップテクスチャ

Texture2D tex : register(t0);       // ディフューズマップテクスチャ

struct PS_INPUT
{
    float4 Diffuse : COLOR0;            // ディフューズカラー
    float4 Specular : COLOR1;           // スぺキュラカラー
    float4 TexCoords0_1 : TEXCOORD0;    // xy:テクスチャ座標 zw:サブテクスチャ座標
    float3 VPosition : TEXCOORD1;       // 座標(ビュー空間)
    float3 VNormal : TEXCOORD2;         // 法線(ビュー空間)
    float1 Fog : TEXCOORD5;             // フォグパラメータ(x)
    float4 Position : SV_POSITION;      // 座標(プロジェクション空間)
};

struct PS_OUTPUT
{
    float4 col : SV_TARGET0;    // 色
    float4 depth : SV_TARGET1;  // 深度
    float4 norm : SV_TARGET2;   // 法線
};

cbuffer ConstantBuffer : register(b0)
{
    // ライトの向きの設定
    float3 m_lightDir;
}

cbuffer ConstantBuffer : register(b1)
{
    // カメラのターゲットの座標の設定
    float3 m_cameraTarget;
}

cbuffer ConstantBuffer : register(b2)
{
    // カメラの座標の設定
    float3 m_cameraPos;
}

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT ret;
    
    ret.depth = input.Position.zwyx;
    ret.col = input.Diffuse;
    ret.norm = float4(input.VNormal, 1.0f);
    
    // ライトの向きの設定
    float3 lightDir = m_lightDir;
    lightDir = normalize(lightDir);
    
    // 法線情報の正規化
    float3 n = normalize(input.VNormal);
    
    // 光の強さを計算する
    // ライトの方向と法線方向の内積
    float bright = dot(lightDir, n);
    
    // 光の強さを段階分けする
    bright = round(bright * 4) / 4;
    
    // 光の強さが0.4f以下にはならないようにする
    bright = max(bright, 0.4f);
    
    // 元の色に光の強さを×
    ret.col.rgb *= bright;
    
    // カメラの向いている方向を計算する
    float3 cameraDir = normalize(m_cameraTarget - m_cameraPos);
    
    // 法線の向きとカメラの向きでリムライトの強さを求める
    float rim = dot(n, cameraDir);
    
    // リムライトの強さが-0.25～0.25の場合は
    // 
    if (rim > -0.25f && rim < 0.25f)
    {
        ret.col.rbg = 0.05f;
    }
    
    return ret;
}