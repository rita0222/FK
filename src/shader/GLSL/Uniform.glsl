uniform mat4 fk_ProjectionMatrix;
uniform mat4 fk_ViewMatrix;
uniform mat4 fk_ModelMatrix;
uniform mat4 fk_ModelViewMatrix;
uniform mat4 fk_ModelViewProjectionMatrix;
uniform mat4 fk_NormalModelMatrix;
uniform mat4 fk_NormalModelViewMatrix;
uniform vec3 fk_CameraPosition;
uniform mat4 fk_ShadowMatrix;
uniform Material fk_Material;
uniform ParallelLight fk_ParallelLight[LIGHTNUM];
uniform PointLight fk_PointLight[LIGHTNUM];
uniform SpotLight fk_SpotLight[LIGHTNUM];
uniform int fk_ParallelLightNum;
uniform int fk_PointLightNum;
uniform int fk_SpotLightNum;
uniform vec4 fk_LineModelColor;
uniform vec4 fk_PointModelColor;
uniform vec4 fk_CurveModelColor;
uniform int fk_Degree;
uniform sampler2D fk_TexID[TEXTURENUM];
uniform sampler2D fk_ColorBuf;
uniform sampler2D fk_DepthBuf;
uniform sampler2DShadow fk_ShadowBuf;
uniform vec2 fk_FBOSize;
uniform float fk_ShadowVisibility;
uniform float fk_ShadowBias;
uniform vec4 fk_FogColor;
uniform vec3 fk_FogParam;
uniform int fk_GeomDiv;
