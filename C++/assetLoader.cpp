#include "assetLoader.h"


AssetLoader::AssetLoader(){
}

bool AssetLoader::loadObj( std::string filename , std::vector<GLfloat>& vertices , std::vector<GLushort>& indices , std::vector<GLfloat>& normals , std::vector<GLfloat>& texcoords ){
	vector<GLfloat> localVertices , localNormals , localUVs, storedUVs, storedNormals;
	std::ifstream file;
	std::string type , d;
	GLfloat coord = 0;
	GLushort val = 0;
	file.open( filename );
	if( ! ( file.is_open() ) )
	{
		std::cout << "Model: could not load " << filename << std::endl;
		return false;
	}
	while( file >> type )
	{
		if( ( type == "#" ) || ( type == "g" ) || ( type == "s" ) )
		{
			getline(file , d , '\n' );
		} else
		if( type == "v" )
		{
			for( int i=0 ; i < 3 ; ++i )
			{
				file >> coord;
				localVertices.push_back( coord );
			}
		} else
		if( type == "f" )
		{
			for( int i=0 ; i < 3 ; ++i )
			{
				getline(file , d , '/' );
				val = atoi( d.c_str() );	
				indices.push_back( val - 1 );
				getline(file , d , '/' );
				val = atoi( d.c_str() );	
				storedUVs.push_back( (float)(val - 1) );
				getline(file , d , ' ' );
				val = atoi( d.c_str() );
				storedNormals.push_back( (float)(val - 1) );
			}
		} else
		if( type == "vn" )
		{
			for( int i=0 ; i < 3 ; ++i )
			{
				file >> coord;
				localNormals.push_back( coord );
			}
		} else
		if( type == "vt" )
		{
			file >> coord;
			localUVs.push_back( coord );
			file >> coord;
			localUVs.push_back( coord );
			file >> coord;
			localUVs.push_back( coord );
		}
	}

	for( unsigned int i=0; i < indices.size(); ++i )
	{
		vertices.push_back( localVertices[ indices[i]*3 ] );	
		vertices.push_back( localVertices[ indices[i]*3 + 1] );
		vertices.push_back( localVertices[ indices[i]*3 + 2] );

		normals.push_back( localNormals[ (unsigned int)storedNormals[i]*3 ] );	
		normals.push_back( localNormals[ (unsigned int)storedNormals[i]*3 + 1] );
		normals.push_back( localNormals[ (unsigned int)storedNormals[i]*3 + 2] );

		texcoords.push_back(localUVs[ (unsigned int)storedUVs[i]*3 ] );	
		texcoords.push_back(1-localUVs[ (unsigned int)storedUVs[i]*3 + 1] );
		texcoords.push_back( localUVs[ (unsigned int)storedUVs[i]*3 + 2] );
	}
	
	file.close();
	return true;
}

GLuint AssetLoader::loadImage( const char * filename ){
	GLuint texture;
	string ext;
	
	const char *dot = strrchr(filename, '.');	// Gets fix extension (.xxx)
	ext = dot + 1;


	if( ext == "raw" || ext == "Raw" || ext == "RAW" )	// handle .raw
	{
		texture = loadRaw( filename );
	} else
	if( ext == "png" || ext == "Png" || ext == "PNG" ) // handle .png
	{
		texture = loadSFMLImage( filename );
	} else
	if( ext == "jpg" || ext == "Jpg" || ext == "JPG" ) // handle .jpg
	{
		texture = loadSFMLImage( filename );
	} else
	if (ext == "tga" || ext == "Tga" || ext == "TGA" ) // handle .tga
	{
		texture = loadSFMLImage( filename );
	}
	
	return texture;
}

GLuint AssetLoader::loadRaw( const char * filename ){	
	GLuint texture;
	char *data;
	int size = 3;
	int width , height;

    std::fstream file( filename , std::ios::binary | std::ios::in | std::ios::ate );
	if ( !file.good() )
	{
		std::cout << "Texture: could not load " << filename << std::endl;
		return 0;
	}
	float s = (float)file.tellg();
	file.seekg( 0 );
	int  i = 1;
	while ( i <=2048 )
	{
		i = i * 2;
		if( (s/4) == i*i ) { size = 4; i=2049; } 
	}
	if(size==4) 
		width = (int)sqrt( (s/4) ); 
	else 
		width = (int)sqrt( (s/3) );

	height = width;

	// allocate buffer
	data = static_cast<char*>( malloc( width * height * size ) );
	// read texture data
	file.read( data, width * height * size );
	file.close();

    // allocate a texture name
    glGenTextures( 1 , &texture );

    // select current texture
    glBindTexture( GL_TEXTURE_2D , texture );

	// build our texture MIP maps
	if ( size == 4 )
	{
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA16, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
		glTexEnvi( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_REPLACE );
	} else {
		gluBuild2DMipmaps( GL_TEXTURE_2D , 3 , width , height, GL_RGB, GL_UNSIGNED_BYTE, data );
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
		glTexEnvi( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE );
	}
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_NEAREST);

	free(data);
    return texture;
}

GLuint AssetLoader::loadSFMLImage( const char * filename ){
	if(!image.loadFromFile( filename ) )
	{
		cout << "Texture: Could not load " << filename << endl;
	}
	int width = image.getSize().x;
	int height = image.getSize().y;

	// allocate a texture name
    glGenTextures( 1 , &texture );
	
    // select current texture
    glBindTexture( GL_TEXTURE_2D , texture );

	// build our texture MIP maps
	//gluBuild2DMipmaps( GL_TEXTURE_2D , 3 , width , height, GL_RGBA16, GL_UNSIGNED_BYTE, image.GetPixelsPtr() );
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA8, width , height, 0, GL_RGBA
		, GL_UNSIGNED_BYTE, image.getPixelsPtr() );
	glTexEnvi( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE );

	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR);

    return texture;
}

AssetLoader::~AssetLoader(){
	glDeleteTextures( 1 ,  &texture );
}