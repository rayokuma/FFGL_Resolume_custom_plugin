#pragma once
#include <FFGLSDK.h>

class CustomObject : public CFFGLPlugin
{
public:
	CustomObject();

	//CFFGLPlugin
	FFResult InitGL( const FFGLViewportStruct* vp ) override;
	FFResult ProcessOpenGL( ProcessOpenGLStruct* pGL ) override;
	FFResult DeInitGL() override;

	char* GetParameterDisplay( unsigned int index ) override;
	FFResult SetFloatParameter( unsigned int dwIndex, float value ) override;
	FFResult SetTextParameter( unsigned int index, const char* value ) override;

	float GetFloatParameter( unsigned int index ) override;
	char* GetTextParameter( unsigned int index ) override;

	//parameters
	//void Randomize();

	int unreal_params_obj;
	int object_option;
	float object_t_x;				//!< In range between 0.0 .. 500.0		
	float object_t_y;               //!< In range between 0.0 .. 500.0		
	float object_t_z;               //!< In range between 0.0 .. 500.0	
	
	std::string min_x;
	std::string min_y;
	std::string min_z;

	std::string max_x;
	std::string max_y;
	std::string max_z;

	float object_r_x;				//!< In range between 0.0 .. 0.0
	float object_r_y;               //!< In range between 0.0 .. 0.0	
	float object_r_z;               //!< In range between -180.0 .. 180.0
	float object_s;					//!< In range between 0.0 .. 100.0
	std::string max_scale;

	//int b;
	//char* amount[ 1 ];
	ffglex::FFGLShader shader;  //!< Utility to help us compile and link some shaders into a program.
	ffglex::FFGLScreenQuad quad;//!< Utility to help us render a full screen quad.
};

