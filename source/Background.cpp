//cpp
#include "common.h"
#include "utils/lodepng.h"
#include "utils/SourcePath.h"

//GLuint texId;
GLuint background_texture;


using namespace Angel;
void Background::loadFreeImageTexture(const char* lpszPathName, GLuint textureID, GLuint GLtex){
  
  std::vector<unsigned char> image;
  unsigned int width;
  unsigned int height;
  //decode
#ifdef _WIN32
  unsigned error = lodepng_decode_wfopen(image, width, height, lpszPathName, LCT_RGBA, 8);
#else
  unsigned error = lodepng::decode(image, width, height, lpszPathName, LCT_RGBA, 8);
#endif //_WIN32

  //if there's an error, display it
  if(error){
    std::cout << "decoder error " << error;
    std::cout << ": " << lodepng_error_text(error) << std::endl;
    return;
  }

  /* the image "shall" be in RGBA_U8 format */

  std::cout << "Image loaded: " << width << " x " << height << std::endl;
  std::cout << image.size() << " pixels.\n";
  std::cout << "Image has " << image.size()/(width*height) << "color values per pixel.\n";

  GLint GL_format = GL_RGBA;

  glActiveTexture( GLtex );
  glBindTexture( GL_TEXTURE_2D, textureID );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_format, width, height, 0, GL_format, GL_UNSIGNED_BYTE, &image[0] );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glGenerateMipmap(GL_TEXTURE_2D);
  
  //Put things away and free memory
  image.clear();

}
//background constructor
Background::Background(){
    Background * Background;
    
    //background colors
    background_color[0] = vec3( 0.0, 1.0, 0.0);
    background_color[1] = vec3( 1.0, 1.0, 0.0);
    background_color[2] = vec3( 0.0, 0.0, 0.0);
    background_color[3] = vec3( 1.0, 0.0, 0.0);
    
    //background verts
    background_vert[0] = vec2( 23.0, 0.0);
    background_vert[1] = vec2(0.0, 0.0);
    background_vert[2] = vec2(23.0, 23.0);
   background_vert[3] = vec2( 0.0 , 23.0);
    

    
};



const int background_size = { 4 };

//Initialize the gl state and variables
void Background::gl_init(){
  //!!!!!!!!Populate background_vert and background_color
  size_t background_bytes = sizeof(background_vert);
  size_t background_color_bytes = sizeof(background_color);
  
  std::string vshader = source_path + "/shaders/vshader.glsl";
  std::string fshader = source_path + "/shaders/fshader.glsl";
  
  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
  
  GLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GLvars.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(GLvars.vertex_shader);
  check_shader_compilation(vshader, GLvars.vertex_shader);
  
  GLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GLvars.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(GLvars.fragment_shader);
  check_shader_compilation(fshader, GLvars.fragment_shader);
  
  GLvars.program = glCreateProgram();
  glAttachShader(GLvars.program, GLvars.vertex_shader);
  glAttachShader(GLvars.program, GLvars.fragment_shader);
  
  glLinkProgram(GLvars.program);
  check_program_link(GLvars.program);
glUseProgram(GLvars.program);
  glBindFragDataLocation(GLvars.program, 0, "fragColor3");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vtex_location = glGetAttribLocation(GLvars.program, "vTexCoord" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );
   
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
    //Generate buffer to hold our vertex data
    glGenBuffers( 1, &GLvars.buffer );
 
    glGenTextures( 1, &background_texture );
    
    std::string background_img = source_path + "/images/background.png" ;
      loadFreeImageTexture(background_img.c_str(), background_texture, GL_TEXTURE0);
      glUniform1i( glGetUniformLocation(GLvars.program, "textureBackground"), 0 );
  
    //Set GL state to use vertex array object
    glBindVertexArray( GLvars.vao );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, background_bytes+ background_color_bytes, NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, background_bytes, background_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, background_bytes, background_color_bytes, background_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vtex_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vtex_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(background_bytes) );
  
  glBindVertexArray(0);
}



//Draw a background
void Background::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
   // glBindTexture( GL_TEXTURE_2D, texId );
  glBindVertexArray( GLvars.vao );
  
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv(GLvars.M_location, 1, GL_TRUE, proj);

  //Draw ship
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
  
  glBindVertexArray(0);
   // glBindTexture( GL_TEXTURE_2D, 0 );
  glUseProgram(0);

}



