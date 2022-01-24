#include "CustomCameras.h"
using namespace ffglex;

enum ParamID
{
	PID_UNREAL_PARAMS_CAM,
	PID_CAM_T_X,
	PID_CAM_T_Y,
	PID_CAM_T_Z,
	PID_MIN_X,
	PID_MIN_Y,
	PID_MIN_Z,
	PID_MAX_X,
	PID_MAX_Y,
	PID_MAX_Z,
	PID_CAM_R_X,
	PID_CAM_R_Y,
	PID_CAM_R_Z,
	PID_ROTATE_AROUND_OBJECT,
	PID_CAM_FOCAL_LENGTH
};

static CFFGLPluginInfo PluginInfo(
	PluginFactory< CustomCameras >, // Create method
	"GG77",							// Plugin unique ID of maximum length 4.
	"Custom Cameras",				// Plugin name
	2,								// API major version number
	1,								// API minor version number
	1,								// Plugin major version number
	000,							// Plugin minor version number
	FF_EFFECT,						// Plugin type
	"Create custom cameras",		// Plugin description
	"Resolume FFGL custom cameras"	// About
);


static const char vertexShaderCode[] = R"(#version 410
//do nothing 
)";

static const char fragmentShaderCode[] = R"(#version 410
// do nothing
)";

CustomCameras::CustomCameras() :
	unreal_params_cam(0),
	cam_t_X(312.0f), 
	cam_t_Y(48.2f), 
	cam_t_Z( -52.97 ),
	min_x( "0" ),
	min_y( "-200" ),
	min_z( "-200" ),
	max_x( "400" ),
	max_y( "200" ),
	max_z( "200" ),
	cam_r_X( 0.0f ), 
	cam_r_Y( 0.0f ), 
	cam_r_Z(0.0f),
	rotate_around_object(0.0f),
	cam_focal_length(35.0f)
{
	// Input properties
	SetMinInputs( 0 );
	SetMaxInputs( 0 );

	// Parameters
	//get unreal parameterss
	SetParamInfof( PID_UNREAL_PARAMS_CAM, "get initial unreal parameters", FF_TYPE_EVENT );

	//camera translation
	SetParamInfof( PID_CAM_T_X, "cam_t_X", FF_TYPE_STANDARD );
	SetParamInfof( PID_CAM_T_Y, "cam_t_Y", FF_TYPE_STANDARD );
	SetParamInfof( PID_CAM_T_Z, "cam_t_Z", FF_TYPE_STANDARD );

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
	
	//camera rotation
	SetParamInfof( PID_CAM_R_X, "cam_r_X", FF_TYPE_STANDARD );
	SetParamRange( PID_CAM_R_X, -180, 180 );
	SetParamInfof( PID_CAM_R_Y, "cam_r_Y", FF_TYPE_STANDARD );
	SetParamRange( PID_CAM_R_Y, -180, 180 );
	SetParamInfof( PID_CAM_R_Z, "cam_r_Z", FF_TYPE_STANDARD );
	SetParamRange( PID_CAM_R_Z, -180, 180 );

	//rotate around object
	SetParamInfof( PID_ROTATE_AROUND_OBJECT, "rotate_around_object", FF_TYPE_STANDARD );
	SetParamRange( PID_ROTATE_AROUND_OBJECT, -180, 180 );

	//camera lens settings
	//focal length
	SetParamInfof( PID_CAM_FOCAL_LENGTH, "cam_focal_length", FF_TYPE_STANDARD );

	FFGLLog::LogToHost( "Created Custom Parameters" );
}

FFResult CustomCameras::InitGL( const FFGLViewportStruct* vp )
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
FFResult CustomCameras::ProcessOpenGL( ProcessOpenGLStruct* pGL )
{
	//do nothing
	return FF_SUCCESS;
}

FFResult CustomCameras::DeInitGL()
{
	shader.FreeGLResources();
	quad.Release();
	return FF_SUCCESS;
}

char* CustomCameras::GetParameterDisplay( unsigned int index )
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

	default:
		return CFFGLPlugin::GetParameterDisplay( index );
	}
}


FFResult CustomCameras::SetFloatParameter( unsigned int dwIndex, float value )
{
	switch( dwIndex )
	{
	case PID_UNREAL_PARAMS_CAM:
		unreal_params_cam = static_cast< int > (value);
		break;
	case PID_CAM_T_X:
		cam_t_X = value * ( std::stof( max_x ) - std::stof( min_x ) ) + ( std::stof( min_x ) );
		break;
	case PID_CAM_T_Y:
		cam_t_Y = value * ( std::stof( max_y ) - std::stof( min_y ) ) + ( std::stof( min_y ) );
		break;
	case PID_CAM_T_Z:
		cam_t_Z = value * ( std::stof( max_z ) - std::stof( min_z ) ) + ( std::stof( min_z ) );
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
	default:
		return FF_FAIL;
	}

	return FF_SUCCESS;
}

FFResult CustomCameras::SetTextParameter( unsigned int index, const char* value )
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
	default:
		return FF_FAIL;
	}

	return FF_SUCCESS;
}

float CustomCameras::GetFloatParameter( unsigned int index )
{
	switch( index )
	{
	case PID_UNREAL_PARAMS_CAM:
		return unreal_params_cam;
	case PID_CAM_T_X:
		return ( cam_t_X - std::stof( min_x ) ) / ( std::stof( max_x ) - std::stof( min_x ) );
	case PID_CAM_T_Y:
		return ( cam_t_Y - std::stof( min_y ) ) / ( std::stof( max_y ) - std::stof( min_y ) );
	case PID_CAM_T_Z:
		return ( cam_t_Z - std::stof( min_z ) ) / ( std::stof( max_z ) - std::stof( min_z ) );
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

	}
	return 0.0f;
}

char* CustomCameras::GetTextParameter( unsigned int index )
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
	}

	return textBufferForHost;
}
