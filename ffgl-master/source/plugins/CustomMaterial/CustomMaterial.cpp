#include "CustomMaterial.h"
using namespace ffglex;

enum ParamID
{
	PID_UNREAL_PARAMS_MATERIAL,
	PID_SPECULAR,
	PID_METALNESS,
	PID_EMISSION,
	PID_RED,
	PID_GREEN,
	PID_BLUE
};

static CFFGLPluginInfo PluginInfo(
	PluginFactory< CustomMaterial >,	// Create method
	"EE55",								// Plugin unique ID of maximum length 4.
	"Custom Material",					// Plugin name
	2,									// API major version number
	1,									// API minor version number
	1,									// Plugin major version number
	000,								// Plugin minor version number
	FF_EFFECT,							// Plugin type
	"Create custom materials",			// Plugin description
	"Resolume FFGL custom materials"	// About
);


static const char vertexShaderCode[] = R"(#version 410
//do nothing 
)";

static const char fragmentShaderCode[] = R"(#version 410
// do nothing
)";

CustomMaterial::CustomMaterial() :
	unreal_params_material(0), 
	specular_roughness( 0.9f ),
	metalness( 0.0f ),
	emission( 0.0f )
{
	rgba[ 0 ] = rgba[ 1 ] = rgba[ 2 ] = rgba[ 3 ] = 1.0f;
	// Input properties
	SetMinInputs( 0 );
	SetMaxInputs( 0 );

	// Parameters
	SetParamInfof( PID_UNREAL_PARAMS_MATERIAL, "get initial unreal parameters", FF_TYPE_EVENT );

	//specular roughness
	SetParamInfof( PID_SPECULAR, "Specular Roughness", FF_TYPE_STANDARD );

	//metalness
	SetParamInfof( PID_METALNESS, "Metalness", FF_TYPE_STANDARD );

	//emission
	SetParamInfof( PID_EMISSION, "Emission", FF_TYPE_STANDARD );

	//light color
	SetParamInfof( PID_RED, "Red", FF_TYPE_RED );
	SetParamInfof( PID_GREEN, "Green", FF_TYPE_GREEN );
	SetParamInfof( PID_BLUE, "Blue", FF_TYPE_BLUE );
	
	FFGLLog::LogToHost( "Created Custom Parameters" );
}

FFResult CustomMaterial::InitGL( const FFGLViewportStruct* vp )
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
FFResult CustomMaterial::ProcessOpenGL( ProcessOpenGLStruct* pGL )
{
	//do nothing
	return FF_SUCCESS;
}
FFResult CustomMaterial::DeInitGL()
{
	shader.FreeGLResources();
	quad.Release();
	return FF_SUCCESS;
}

char* CustomMaterial::GetParameterDisplay( unsigned int index )
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
	case PID_SPECULAR:
		sprintf( displayValueBuffer, "%f", specular_roughness );
		return displayValueBuffer;
	case PID_METALNESS:
		sprintf( displayValueBuffer, "%f", metalness );
		return displayValueBuffer;
	case PID_EMISSION:
		sprintf( displayValueBuffer, "%f", emission );
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


FFResult CustomMaterial::SetFloatParameter( unsigned int dwIndex, float value )
{
	switch( dwIndex )
	{
	case PID_UNREAL_PARAMS_MATERIAL:
		unreal_params_material = static_cast< int >( value );
		break;
	case PID_SPECULAR:
		specular_roughness = value;
		break;
	case PID_METALNESS:
		metalness = value;
		break;
	case PID_EMISSION:
		emission = value;
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

float CustomMaterial::GetFloatParameter( unsigned int index )
{
	switch( index )
	{
	case PID_UNREAL_PARAMS_MATERIAL:
		return unreal_params_material;
	case PID_SPECULAR:
		return specular_roughness;
	case PID_METALNESS:
		return metalness;
	case PID_EMISSION:
		return emission;
	case PID_RED:
		return rgba[ 0 ];
	case PID_GREEN:
		return rgba[ 1 ];
	case PID_BLUE:
		return rgba[ 2 ];
	}
	return 0.0f;
}
