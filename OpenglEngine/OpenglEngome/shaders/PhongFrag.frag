#version 410

in vec3 vNormal;

uniform vec3 Ia; 
uniform vec3 Id; 
uniform vec3 Is; 
uniform vec3 Ka; 
uniform vec3 Kd;
uniform vec3 Ks; 

uniform float SpecularPower; 
uniform vec3 LightDirection;

out vec4 FragColour; 

void main()
{
   vec3 N = normalize(vNormal);
   vec3 L = normalize(LightDirection);

   float LambertTerm = max(0,min(1,dot(N,-L))); 

   //vec3 Ambeint = Ia * Ka; 
   //vec3 Diffuse = Id * Kd * LambertTerm;
   vec3 Diffuse = Id * LambertTerm;
	
   FragColour = vec4(Diffuse,1);
}