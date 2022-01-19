#pragma once
#include <FFGLSDK.h>

class CustomParameters : public CFFGLPlugin
{
public:
	CustomParameters();

	//CFFGLPlugin
	FFResult InitGL( const FFGLViewportStruct* vp ) override;
	FFResult ProcessOpenGL( ProcessOpenGLStruct* pGL ) override;
	FFResult DeInitGL() override;

	char* GetParameterDisplay( unsigned int index ) override;
	FFResult SetFloatParameter( unsigned int dwIndex, float value ) override;

	float GetFloatParameter( unsigned int index ) override;


private:
	//parameters
	int object_option;
	float object_t;				//!< In range between 0.0 .. 500.0		
	float object_r;				//!< In range between -180.0 .. 180.0	
	float cam_t_X;				//!< In range between -1500.0 .. -1000.0
	float cam_t_Y;				//!< In range between -100.0 .. 100.0
	float cam_t_Z;				//!< In range between 0.0 .. 500.0
	float cam_r_X;				//!< In range between -180.0 .. 180.0
	float cam_r_Y;				//!< In range between -180.0 .. 180.0
	float cam_r_Z;				//!< In range between -180.0 .. 180.0
	float rotate_around_object; //!< In range between -180.0 .. 180.0
	float cam_focal_length;		//!< In range between 1.0 .. 120.0
	float light_brightness;     //!< In range between 0.0 .. 500.0
	float rgba[ 4 ];

	ffglex::FFGLShader shader;  //!< Utility to help us compile and link some shaders into a program.
	ffglex::FFGLScreenQuad quad;//!< Utility to help us render a full screen quad.
};


