#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool IsInverted = false;

out vec4 Fragment;

void main()
{
	vec3 finalColor = Color;
	
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
		finalColor = SolidColor;

	if(IsInverted)
	{
		finalColor = vec3(1,1,1) - finalColor;
	}

	Fragment = vec4(finalColor,1);

	return;
}