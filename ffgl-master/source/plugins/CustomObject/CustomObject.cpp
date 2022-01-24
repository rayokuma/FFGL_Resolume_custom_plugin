#include "CustomObject.h"
using namespace ffglex;

enum ParamID
{
	PID_UNREAL_PARAMS_OBJECT,
	PID_OBJECT_OPTION,
	PID_OBJECT_T_X,
	PID_OBJECT_T_Y,
	PID_OBJECT_T_Z,
	PID_MIN_X,
	PID_MIN_Y,
	PID_MIN_Z,
	PID_MAX_X,
	PID_MAX_Y,
	PID_MAX_Z,
	PID_OBJECT_R_X,
	PID_OBJECT_R_Y,
	PID_OBJECT_R_Z,
	PID_OBJECT_S,
	PID_MAX_SCALE
};

static CFFGLPluginInfo PluginInfo(
	PluginFactory< CustomObject >,  // Create method
	"HH88",							// Plugin unique ID of maximum length 4.
	"Custom Object",				// Plugin name
	2,								// API major version number
	1,								// API minor version number
	1,								// Plugin major version number
	000,							// Plugin minor version number
	FF_EFFECT,						// Plugin type
	"Create custom object",			// Plugin description
	"Resolume FFGL custom object"	// About
);


static const char vertexShaderCode[] = R"(#version 410
//do nothing 
)";

static const char fragmentShaderCode[] = R"(#version 410
// do nothing
)";

CustomObject::CustomObject() :
	unreal_params_obj(0),
	object_option( 2 ),
	object_t_x( 110.0f ),
	object_t_y( 0.0f ),
	object_t_z( 110.0f ),
	min_x( "0" ),
	min_y( "0" ),
	min_z( "0" ),
	max_x( "500" ),
	max_y( "500" ),
	max_z( "500" ),
	object_r_x( 0.0f ),
	object_r_y( 0.0f ),
	object_r_z( 0.0f ),
	object_s( 1.0f ),
	max_scale( "20" )

{
	// Input properties
	SetMinInputs( 0 );
	SetMaxInputs( 0 );

	//get Unreal Params
	SetParamInfof( PID_UNREAL_PARAMS_OBJECT, "get initial unreal parameters", FF_TYPE_EVENT );

	//object option
	SetOptionParamInfo( PID_OBJECT_OPTION, "object_option", 3, object_option );
	SetParamElementInfo( PID_OBJECT_OPTION, 0, "object 1", 0 );
	SetParamElementInfo( PID_OBJECT_OPTION, 1, "object 2", 1 );
	SetParamElementInfo( PID_OBJECT_OPTION, 2, "object 3", 2 );

	//object translation and rotation
	SetParamInfof( PID_OBJECT_T_X, "object_t_x", FF_TYPE_STANDARD );
	//SetParamRange( PID_OBJECT_T_X, std::stof( min_x ), std::stof( max_x ) );
	SetParamInfof( PID_OBJECT_T_Y, "object_t_y", FF_TYPE_STANDARD );
	SetParamInfof( PID_OBJECT_T_Z, "object_t_z", FF_TYPE_STANDARD );
	
	//minimum translation
	SetParamInfo( PID_MIN_X, "X Min", FF_TYPE_TEXT, min_x.c_str() );
	SetParamInfo( PID_MIN_Y, "Y Min", FF_TYPE_TEXT, min_y.c_str() );
	SetParamInfo( PID_MIN_Z, "Z Min", FF_TYPE_TEXT, min_z.c_str() );

	//maximum translation
	SetParamInfo( PID_MAX_X, "X Max", FF_TYPE_TEXT, max_x.c_str() );
	SetParamInfo( PID_MAX_Y, "Y Max", FF_TYPE_TEXT, max_y.c_str() );
	SetParamInfo( PID_MAX_Z, "Z Max", FF_TYPE_TEXT, max_z.c_str() );

	//make group from minumum and maximum translation 
	SetParamGroup( PID_MIN_X, "Translation Range" );
	SetParamGroup( PID_MAX_X, "Translation Range" );
	SetParamGroup( PID_MIN_Y, "Translation Range" );
	SetParamGroup( PID_MAX_Y, "Translation Range" );
	SetParamGroup( PID_MIN_Z, "Translation Range" );
	SetParamGroup( PID_MAX_Z, "Translation Range" );
	

	SetParamInfof( PID_OBJECT_R_X, "object_r_x", FF_TYPE_STANDARD );
	SetParamInfof( PID_OBJECT_R_Y, "object_r_y", FF_TYPE_STANDARD );
	SetParamInfof( PID_OBJECT_R_Z, "object_r_z", FF_TYPE_STANDARD );
	SetParamRange( PID_OBJECT_R_X, 0, 360 );
	SetParamRange( PID_OBJECT_R_Y, 0, 360 );
	SetParamRange( PID_OBJECT_R_Z, 0, 360 );

	//object scale
	SetParamInfof( PID_OBJECT_S, "object_scale", FF_TYPE_STANDARD );
	
	//max scale
	SetParamInfo( PID_MAX_SCALE, "max_scale", FF_TYPE_TEXT, max_scale.c_str() );

	FFGLLog::LogToHost( "Created Custom Object" );
}

FFResult CustomObject::InitGL( const FFGLViewportStruct* vp )
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
FFResult CustomObject::ProcessOpenGL( ProcessOpenGLStruct* pGL )
{
	//do nothing
	return FF_SUCCESS;
}
FFResult CustomObject::DeInitGL()
{
	shader.FreeGLResources();
	quad.Release();
	return FF_SUCCESS;
}

char* CustomObject::GetParameterDisplay( unsigned int index )
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
	case PID_OBJECT_T_X:
		sprintf( displayValueBuffer, "%f", object_t_x );
		return displayValueBuffer;
	case PID_OBJECT_T_Y:
		sprintf( displayValueBuffer, "%f", object_t_y );
		return displayValueBuffer;
	case PID_OBJECT_T_Z:
		sprintf( displayValueBuffer, "%f", object_t_z );
		return displayValueBuffer;
	case PID_OBJECT_R_X:
		sprintf( displayValueBuffer, "%f", object_r_x );
		return displayValueBuffer;
	case PID_OBJECT_R_Y:
		sprintf( displayValueBuffer, "%f", object_r_y );
		return displayValueBuffer;
	case PID_OBJECT_R_Z:
		sprintf( displayValueBuffer, "%f", object_r_z );
		return displayValueBuffer;
	case PID_OBJECT_S:
		sprintf( displayValueBuffer, "%f", object_s );
		return displayValueBuffer;
	default:
		return CFFGLPlugin::GetParameterDisplay( index );
	}
}


FFResult CustomObject::SetFloatParameter( unsigned int dwIndex, float value )
{
	switch( dwIndex )
	{
	case PID_UNREAL_PARAMS_OBJECT:
		unreal_params_obj = static_cast< int >( value );
		break;
	case PID_OBJECT_OPTION:
		object_option = static_cast< int >( value);
		break;
	case PID_OBJECT_T_X:
		object_t_x = value * ( std::stof( max_x ) - std::stof(min_x)) + (std::stof(min_x));
		break;
	case PID_OBJECT_T_Y:
		object_t_y = value * ( std::stof( max_y ) - std::stof( min_y ) ) + ( std::stof( min_y ) );
		break;
	case PID_OBJECT_T_Z:
		object_t_z = value * ( std::stof( max_z ) - std::stof( min_z ) ) + ( std::stof( min_z ) );
		break;
	case PID_OBJECT_R_X:
		object_r_x = value;
		break;
	case PID_OBJECT_R_Y:
		object_r_y = value;
		break;
	case PID_OBJECT_R_Z:
		object_r_z = value;
		break;
	case PID_OBJECT_S:
		object_s = value * ( std::stof( max_scale ));
		break;

	default:
		return FF_FAIL;
	}

	return FF_SUCCESS;
}

FFResult CustomObject::SetTextParameter( unsigned int index, const char* value ) 
{
	switch( index )
{
	case PID_MIN_X:
		min_x = value;
		break;
	case PID_MIN_Y:
		min_y = value;
		break;
	case PID_MIN_Z:
		min_z = value;
		break;
	case PID_MAX_X:
		max_x = value;
		break;
	case PID_MAX_Y:
		max_y = value;
		break;
	case PID_MAX_Z:
		max_z = value;
		break;
	case PID_MAX_SCALE:
		max_scale = value;
		break;

	default:
		return FF_FAIL;
	}
	

	return FF_SUCCESS;
}

float CustomObject::GetFloatParameter( unsigned int index )
{
	switch( index )
	{
	case PID_UNREAL_PARAMS_OBJECT:
		return unreal_params_obj;
	case PID_OBJECT_OPTION:
		return object_option;
	case PID_OBJECT_T_X:
		return ( object_t_x - std::stof( min_x ) ) / ( std::stof( max_x ) - std::stof( min_x ) );
	case PID_OBJECT_T_Y:
		return ( object_t_y - std::stof( min_y ) ) / ( std::stof( max_y ) - std::stof( min_y ) );
	case PID_OBJECT_T_Z:
		return ( object_t_z - std::stof( min_z ) ) / ( std::stof( max_z ) - std::stof( min_z) );
	case PID_OBJECT_R_X:
		return object_r_x;
	case PID_OBJECT_R_Y:
		return object_r_y;
	case PID_OBJECT_R_Z:
		return object_r_z;
	case PID_OBJECT_S:
		return ( object_s - 0.0f ) / std::stof( max_scale );
	}
	return 0.0f;
}


char* CustomObject::GetTextParameter( unsigned int index )
{
	static char textBufferForHost[ 512 ];
	switch( index )
	{
	case PID_MIN_X:
		strcpy( textBufferForHost, min_x.c_str() );
		break;
	case PID_MIN_Y:
		strcpy( textBufferForHost, min_y.c_str() );
		break;
	case PID_MIN_Z:
		strcpy( textBufferForHost, min_z.c_str() );
		break;
	case PID_MAX_X:
		strcpy( textBufferForHost, max_x.c_str() );
		break;
	case PID_MAX_Y:
		strcpy( textBufferForHost, max_y.c_str() );
		break;
	case PID_MAX_Z:
		strcpy( textBufferForHost, max_z.c_str() );
		break;
	case PID_MAX_SCALE:
		strcpy( textBufferForHost, max_scale.c_str() );
		break;

	}

	return textBufferForHost;
}
