#pragma once
#include <FFGLSDK.h>

class CustomMaterial : public CFFGLPlugin
{
public:
	CustomMaterial();

	//CFFGLPlugin
	FFResult InitGL( const FFGLViewportStruct* vp ) override;
	FFResult ProcessOpenGL( ProcessOpenGLStruct* pGL ) override;
	FFResult DeInitGL() override;

	char* GetParameterDisplay( unsigned int index ) override;
	FFResult SetFloatParameter( unsigned int dwIndex, float value ) override;

	float GetFloatParameter( unsigned int index ) override;


private:
	//parameters
	int unreal_params_material;
	
	float specular_roughness;				//!< In range between 0.0 .. 1.0		
	float metalness;				//!< In range between -180.0 .. 180.0	
	float emission;				//!< In range between -1500.0 .. -1000.0
	float rgba[ 4 ];

	ffglex::FFGLShader shader;  //!< Utility to help us compile and link some shaders into a program.
	ffglex::FFGLScreenQuad quad;//!< Utility to help us render a full screen quad.
};


