#version 410

in vec4 vPosition; 
in vec3 vNormal;

uniform vec3 Ka; 
uniform vec3 Kd; 
uniform vec3 Ks; 
uniform vec3 cameraPosition;
uniform float SpecularPower; 
uniform float SpecularPower1; 

uniform vec3 Ia; 
uniform vec3 Id;
uniform vec3 Is; 

uniform vec3 Id1;
uniform vec3 Is1;


uniform vec3 LightDirection;
uniform vec3 LightDirection1;

out vec4 FragColour;

void main() {
//Ensure normal and light direction are normalised 
vec3 N = normalize(vNormal);

vec3 L = normalize(LightDirection);
vec3 L1 = normalize(LightDirection1);

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
vec3 Diffuse = Id * Kd * LambertTerm;
vec3 Specular = Is * Ks * SpecularTerm;

vec3 Diffuse1 = Id1 * Kd * LambertTerm1;
vec3 Specular1 = Is1 * Ks * SpecularTerm1; 

//FragColour = vec4( Ambient + Diffuse  + Specular  , 1 );
FragColour = vec4( Ambient + Diffuse +  Diffuse1 + Specular + Specular1 , 1 );


}