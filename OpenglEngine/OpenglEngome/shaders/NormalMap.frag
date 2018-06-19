#version 410

in vec2 vTexCoord;
in vec3 vNormal;
in vec3 vTangent;
in vec3 vBiTangent;
in vec4 vPosition; 

out vec4 FragColour;

uniform sampler2D DiffuseTexture; 
uniform sampler2D SpecularTexture; 
uniform sampler2D NormalTexture; 

uniform vec3 Ka; 
uniform vec3 Kd; 
uniform vec3 Ks; 
uniform float SpecularPower; 
uniform float SpecularPower1; 

uniform vec3 Ia; 
uniform vec3 Id;
uniform vec3 Is; 
uniform vec3 Id1;
uniform vec3 Is1;
uniform vec3 LightDirection;
uniform vec3 LightDirection1;

uniform vec3 cameraPosition;

void main() {
//Ensure normal and light direction are normalised 
vec3 N = normalize(vNormal);
vec3 T = normalize(vTangent);
vec3 B = normalize(vBiTangent);
vec3 L = normalize(LightDirection);
vec3 L1 = normalize(LightDirection1);

mat3 TBN = mat3(T,B,N);

vec3 TexDiffuse = texture(DiffuseTexture,vTexCoord).rgb;
vec3 TexSpecular = texture(SpecularTexture,vTexCoord).rgb;
vec3 TexNormal = texture(NormalTexture, vTexCoord).rgb;

// calculate lambert term (negate light direction)
float LambertTerm = max( 0, min( 1, dot( N, -L ) ) );

float LambertTerm1 = max( 1, min( 0, dot( N, -L1 ) ) );

// Calulates the view vector and the reflecttion vector 
vec3 V = normalize(cameraPosition - vPosition.xyz); 
vec3 R = reflect(L,N);
vec3 R1 = reflect(L1,N);

//Calculates specular term 
float SpecularTerm = pow(max(0,dot(R,V)) , SpecularPower); 
float SpecularTerm1 = pow(max(0,dot(R1,V)) , SpecularPower1); 

//Calculates each Colour property 
vec3 Ambient = Ia * Ka; 
vec3 Diffuse = Id * Kd * TexDiffuse * LambertTerm;

vec3 Specular = Is * Ks * TexSpecular * SpecularTerm;

vec3 Diffuse1 = Id1 * Kd * TexDiffuse * LambertTerm1;
vec3 Specular1 = Is1 * Ks * TexSpecular * SpecularTerm1; 

//FragColour = vec4( Ambient + Diffuse  + Specular  , 1 );
FragColour = vec4( Ambient + Diffuse +  Diffuse1 + Specular + Specular1 , 1 );
}