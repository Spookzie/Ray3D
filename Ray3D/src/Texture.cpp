#include "Texture.h"


Texture::Texture(const char* file_name, GLenum type, GLint texture_unit)
{
    this->type = type;
    this->textureUnit = texture_unit;

    unsigned char* img = SOIL_load_image(file_name, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

    glErrorCall( glGenTextures(1, &this->id) );
    glErrorCall( glBindTexture(type, this->id) );

    //Setting texture parameters
    glErrorCall( glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT) );                    //Resampling texture down if it needs to be rendered small
    glErrorCall( glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT) );                    //Resampling texture up if it needs to be rendered large
    glErrorCall( glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR) );                //Clamping horizontally
    glErrorCall( glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR) );  //Clamping vertically

    //Uploading texture data
    if (img)
    {
        glErrorCall( glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img) );
        glErrorCall( glGenerateMipmap(type) );
        SOIL_free_image_data(img);
    }
    else
        std::cout << "ERROR::Texture.cpp::Texture(): Failed to load texture: " << file_name << std::endl;


    glErrorCall( glBindTexture(type, 0) );
}

Texture::~Texture()
{
	glErrorCall( glDeleteTextures(1, &this->id) );
}


void Texture::Bind()
{
    glErrorCall( glActiveTexture(GL_TEXTURE0 + this->textureUnit) );
    glErrorCall( glBindTexture(this->type, this->id) );
}