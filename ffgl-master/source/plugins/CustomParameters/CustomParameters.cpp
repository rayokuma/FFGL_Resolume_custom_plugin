#include "CustomParameters.h"
using namespace ffglex;

enum ParamID
{
	PID_OBJECT_OPTION,
	PID_OBJECT_T,
	PID_OBJECT_R,
	PID_CAM_T_X,
	PID_CAM_T_Y,
	PID_CAM_T_Z,
	PID_CAM_R_X,
	PID_CAM_R_Y,
	PID_CAM_R_Z,
	PID_ROTATE_AROUND_OBJECT,
	PID_CAM_FOCAL_LENGTH,
	PID_LIGHT_BRIGHTNESS,
	PID_RED,
	PID_GREEN,
	PID_BLUE
};

static CFFGLPluginInfo PluginInfo(
	PluginFactory< CustomParameters >,	// Create method
	"DD44",								// Plugin unique ID of maximum length 4.
	"Custom Parameters",				// Plugin name
	2,									// API major version number
	1,									// API minor version number
	1,									// Plugin major version number
	000,								// Plugin minor version number
	FF_EFFECT,							// Plugin type
	"Create custom parameters",			// Plugin description
	"Resolume FFGL custom parameters"	// About
);


static const char vertexShaderCode[] = R"(#version 410
//do nothing 
)";

static const char fragmentShaderCode[] = R"(#version 410
// do nothing
)";

CustomParameters::CustomParameters() :
	object_option( 3 ),
	object_t (110.0f), 
	object_r(0.0f),
	cam_t_X(-1220.0f), 
	cam_t_Y(9.820283f), 
	cam_t_Z( 120.105713f ), 
	cam_r_X( 0.0f ), 
	cam_r_Y( 0.0f ), 
	cam_r_Z(0.0f),
	rotate_around_object(0.0f),
	cam_focal_length(35.0f), 
	light_brightness(160.0)
{
	rgba[ 0 ] = rgba[ 1 ] = rgba[ 2 ] = rgba[ 3 ] = 1.0f;
	// Input properties
	SetMinInputs( 0 );
	SetMaxInputs( 0 );

	// Parameters

	SetOptionParamInfo( PID_OBJECT_OPTION, "object_option", 3, object_option );
	SetParamElementInfo( PID_OBJECT_OPTION, 0, "object 1", 0 );
	SetParamElementInfo( PID_OBJECT_OPTION, 1, "object 2", 1 );
	SetParamElementInfo( PID_OBJECT_OPTION, 2, "object 3", 2 );


	//object translation and rotation
	SetParamInfof( PID_OBJECT_T, "object_t", FF_TYPE_STANDARD );
	SetParamInfof( PID_OBJECT_R, "object_r", FF_TYPE_STANDARD );
	SetParamRange( PID_OBJECT_R, -180, 180 );


	//camera translation
	SetParamInfof( PID_CAM_T_X, "cam_t_X", FF_TYPE_STANDARD );
	SetParamInfof( PID_CAM_T_Y, "cam_t_Y", FF_TYPE_STANDARD );
	SetParamInfof( PID_CAM_T_Z, "cam_t_Z", FF_TYPE_STANDARD );
	
	//camera rotation
	SetParamInfof( PID_CAM_R_X, "cam_r_X", FF_TYPE_STANDARD );
	SetParamRange( PID_CAM_R_X, -180, 180 );
	SetParamInfof( PID_CAM_R_Y, "cam_r_Y", FF_TYPE_STANDARD );
	SetParamRange( PID_CAM_R_Y, -180, 180 );
	SetParamInfof( PID_CAM_R_Z, "cam_r_Z", FF_TYPE_STANDARD );
	SetParamRange( PID_CAM_R_Z, -180, 180 );

	SetParamInfof( PID_ROTATE_AROUND_OBJECT, "rotate_around_object", FF_TYPE_STANDARD );
	SetParamRange( PID_ROTATE_AROUND_OBJECT, -180, 180 );


	//camera lens settings
	SetParamInfof( PID_CAM_FOCAL_LENGTH, "cam_focal_length", FF_TYPE_STANDARD );

	//light brightness
	SetParamInfof( PID_LIGHT_BRIGHTNESS, "light_brightness", FF_TYPE_STANDARD );

	//light color
	SetParamInfof( PID_RED, "Red", FF_TYPE_RED );
	SetParamInfof( PID_GREEN, "Green", FF_TYPE_GREEN );
	SetParamInfof( PID_BLUE, "Blue", FF_TYPE_BLUE );
	
	FFGLLog::LogToHost( "Created Custom Parameters" );
}

FFResult CustomParameters::InitGL( const FFGLViewportStruct* vp )
{
	if( !shader.Compile( vertexShaderCode, fragmentShaderCode ) )
	{
		DeInitGL();
		return FF_FAIL;
	}
	if( !quad.Initialise() )
	{
		DeInitGL();
		return FF_FAIL;
	}

	ScopedShaderBinding shaderBinding( shader.GetGLID() );
	//Use base-class init as success result so that it retains the viewport.
	return CFFGLPlugin::InitGL( vp );
}
FFResult CustomParameters::ProcessOpenGL( ProcessOpenGLStruct* pGL )
{
	//do nothing
	return FF_SUCCESS;
}
FFResult CustomParameters::DeInitGL()
{
	shader.FreeGLResources();
	quad.Release();
	return FF_SUCCESS;
}

char* CustomParameters::GetParameterDisplay( unsigned int index )
{
	/**
	 * We're not returning ownership over the string we return, so we have to somehow guarantee that
	 * the lifetime of the returned string encompasses the usage of that string by the host. Having this static
	 * buffer here keeps previously returned display string alive until this function is called again.
	 * This happens to be long enough for the hosts we know about.
	 */
	static char displayValueBuffer[ 15 ];
	memset( displayValueBuffer, 0, sizeof( displayValueBuffer ) );

	switch( index )
	{
	case PID_OBJECT_T:
		sprintf( displayValueBuffer, "%f", object_t );
		return displayValueBuffer;
	case PID_OBJECT_R:
		sprintf( displayValueBuffer, "%f", object_r );
		return displayValueBuffer;
	case PID_CAM_T_X:
		sprintf( displayValueBuffer, "%f", cam_t_X );
		return displayValueBuffer;
	case PID_CAM_T_Y:
		sprintf( displayValueBuffer, "%f", cam_t_Y );
		return displayValueBuffer;
	case PID_CAM_T_Z:
		sprintf( displayValueBuffer, "%f", cam_t_Z );
		return displayValueBuffer;
	case PID_CAM_R_X:
		sprintf( displayValueBuffer, "%f", cam_r_X );
		return displayValueBuffer;
	case PID_CAM_R_Y:
		sprintf( displayValueBuffer, "%f", cam_r_Y );
		return displayValueBuffer;
	case PID_CAM_R_Z:
		sprintf( displayValueBuffer, "%f", cam_r_Z );
		return displayValueBuffer;
	case PID_ROTATE_AROUND_OBJECT:
		sprintf( displayValueBuffer, "%f", rotate_around_object );
		return displayValueBuffer;
	case PID_CAM_FOCAL_LENGTH:
		sprintf( displayValueBuffer, "%f", cam_focal_length );
		return displayValueBuffer;
	case PID_LIGHT_BRIGHTNESS:
		sprintf( displayValueBuffer, "%f", light_brightness );
		return displayValueBuffer;
	case PID_RED:
		sprintf( displayValueBuffer, "%f", rgba[ 0 ] );
		return displayValueBuffer;
	case PID_GREEN:
		sprintf( displayValueBuffer, "%f", rgba[ 1 ] );
		return displayValueBuffer;
	case PID_BLUE:
		sprintf( displayValueBuffer, "%f", rgba[ 2 ] );
		return displayValueBuffer;

	default:
		return CFFGLPlugin::GetParameterDisplay( index );
	}
}


FFResult CustomParameters::SetFloatParameter( unsigned int dwIndex, float value )
{
	switch( dwIndex )
	{
	case PID_OBJECT_OPTION:
		object_option = static_cast< int >( value);
		break;
	case PID_OBJECT_T:
		object_t = value * 500.0f + 0.0f;
		break;
	case PID_OBJECT_R:
		object_r = value;
		break;
	case PID_CAM_T_X:
		cam_t_X = value * 1000.0f + ( -1500.0f );
		break;
	case PID_CAM_T_Y:
		cam_t_Y = value * 100.0f + ( -100.0f );
		break;
	case PID_CAM_T_Z:
		cam_t_Z = value * 500.0f +  0.0f;
		break;
	case PID_CAM_R_X:
		cam_r_X = value;
		break;
	case PID_CAM_R_Y:
		cam_r_Y = value;
		break;
	case PID_CAM_R_Z:
		cam_r_Z = value;
		break;
	case PID_ROTATE_AROUND_OBJECT:	
		rotate_around_object = value;
		break;
	case PID_CAM_FOCAL_LENGTH:
		cam_focal_length = value * 119.0 + 1.0f; 
		break;
	case PID_LIGHT_BRIGHTNESS:
		light_brightness = value * 500.0f + 0.0f;
		break;
	case PID_RED:
		rgba[ 0 ] = value;
		break;
	case PID_GREEN:
		rgba[ 1 ] = value;
		break;
	case PID_BLUE:
		rgba[ 2 ] = value;
		break;
	default:
		return FF_FAIL;
	}

	return FF_SUCCESS;
}

float CustomParameters::GetFloatParameter( unsigned int index )
{
	switch( index )
	{
	case PID_OBJECT_OPTION:
		return object_option;
	case PID_OBJECT_T:
		return (object_t - 0.0f) / 500.0f;
	case PID_OBJECT_R:
		return object_r;
	case PID_CAM_T_X:
		return ( cam_t_X - ( -1500.0f ) ) / 1000.0f;
	case PID_CAM_T_Z:
		return ( cam_t_Z - 0.0f) / 500.0f;
	case PID_CAM_R_X:
		return cam_r_X;
	case PID_CAM_R_Y:
		return cam_r_Y;
	case PID_CAM_R_Z:
		return cam_r_Z;
	case PID_ROTATE_AROUND_OBJECT:
		return rotate_around_object;
	case PID_CAM_FOCAL_LENGTH:
		return ( cam_focal_length - 1.0f ) / 119.0f;
	case PID_LIGHT_BRIGHTNESS:
		return ( light_brightness - 0.0f ) / 500.0f;
	case PID_RED:
		return rgba[ 0 ];
	case PID_GREEN:
		return rgba[ 1 ];
	case PID_BLUE:
		return rgba[ 2 ];
	}
	return 0.0f;
}

