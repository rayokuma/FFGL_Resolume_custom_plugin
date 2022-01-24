#include "CustomLight.h"
using namespace ffglex;

enum ParamID
{
	PID_UNREAL_PARAMS_LIGHT,
	PID_LIGHT_OPTION,
	PID_LIGHT_INTENSITY,
	PID_INNER_CONE_ANGLE,
	PID_OUTER_CONE_ANGLE,
	PID_RED,
	PID_GREEN,
	PID_BLUE
};

static CFFGLPluginInfo PluginInfo(
	PluginFactory< CustomLight >,   // Create method
	"FF66",								// Plugin unique ID of maximum length 4.
	"Custom Light",				// Plugin name
	2,									// API major version number
	1,									// API minor version number
	1,									// Plugin major version number
	000,								// Plugin minor version number
	FF_EFFECT,							// Plugin type
	"Create custom lights",			// Plugin description
	"Resolume FFGL custom lights"	// About
);


static const char vertexShaderCode[] = R"(#version 410
//do nothing 
)";

static const char fragmentShaderCode[] = R"(#version 410
// do nothing
)";

CustomLight::CustomLight() :
	unreal_params_light(0),
	light_option( 0 ),
	light_intensity( 0.9f ),
	inner_cone_angle( 0.0f ),
	outer_cone_angle( 0.0f )
{
	rgba[ 0 ] = rgba[ 1 ] = rgba[ 2 ] = rgba[ 3 ] = 1.0f;
	// Input properties
	SetMinInputs( 0 );
	SetMaxInputs( 0 );

	// Parameters
	//get unreal_params
	SetParamInfof( PID_UNREAL_PARAMS_LIGHT, "get initial unreal parameters", FF_TYPE_EVENT );
	 
	//light option
	SetOptionParamInfo( PID_LIGHT_OPTION, "light_option", 3, light_option );
	SetParamElementInfo( PID_LIGHT_OPTION, 0, "light 1", 0 );
	SetParamElementInfo( PID_LIGHT_OPTION, 1, "light 2 ", 1 );
	SetParamElementInfo( PID_LIGHT_OPTION, 2, "all lights", 2 );

	//light intensity
	SetParamInfof( PID_LIGHT_INTENSITY, "Light intensity", FF_TYPE_STANDARD );

	//inner cone angle
	SetParamInfof( PID_INNER_CONE_ANGLE, "Inner cone angle", FF_TYPE_STANDARD );

	//outer cone angle
	SetParamInfof( PID_OUTER_CONE_ANGLE, "Outer cone angle", FF_TYPE_STANDARD );

	//light color
	SetParamInfof( PID_RED, "Red", FF_TYPE_RED );
	SetParamInfof( PID_GREEN, "Green", FF_TYPE_GREEN );
	SetParamInfof( PID_BLUE, "Blue", FF_TYPE_BLUE );
	
	FFGLLog::LogToHost( "Created Custom Lights" );
}

FFResult CustomLight::InitGL( const FFGLViewportStruct* vp )
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
FFResult CustomLight::ProcessOpenGL( ProcessOpenGLStruct* pGL )
{
	//do nothing
	return FF_SUCCESS;
}
FFResult CustomLight::DeInitGL()
{
	shader.FreeGLResources();
	quad.Release();
	return FF_SUCCESS;
}

char* CustomLight::GetParameterDisplay( unsigned int index )
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
	case PID_LIGHT_INTENSITY:
		sprintf( displayValueBuffer, "%f", light_intensity );
		return displayValueBuffer;
	case PID_INNER_CONE_ANGLE:
		sprintf( displayValueBuffer, "%f", inner_cone_angle );
		return displayValueBuffer;
	case PID_OUTER_CONE_ANGLE:
		sprintf( displayValueBuffer, "%f", outer_cone_angle );
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


FFResult CustomLight::SetFloatParameter( unsigned int dwIndex, float value )
{
	switch( dwIndex )
	{
	case PID_UNREAL_PARAMS_LIGHT:
		unreal_params_light = static_cast< int >( value );
		break;
	case PID_LIGHT_OPTION:
		light_option = static_cast< int >( value );
		break;
	case PID_LIGHT_INTENSITY:
		light_intensity = value;
		break;
	case PID_INNER_CONE_ANGLE:
		inner_cone_angle = value;
		break;
	case PID_OUTER_CONE_ANGLE:
		outer_cone_angle = value;
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

float CustomLight::GetFloatParameter( unsigned int index )
{
	switch( index )
	{
	case PID_UNREAL_PARAMS_LIGHT:
		return unreal_params_light;
	case PID_LIGHT_OPTION:
		return light_option;
	case PID_LIGHT_INTENSITY:
		return light_intensity;
	case PID_INNER_CONE_ANGLE:
		return inner_cone_angle;
	case PID_OUTER_CONE_ANGLE:
		return outer_cone_angle;
	case PID_RED:
		return rgba[ 0 ];
	case PID_GREEN:
		return rgba[ 1 ];
	case PID_BLUE:
		return rgba[ 2 ];
	}
	return 0.0f;
}

