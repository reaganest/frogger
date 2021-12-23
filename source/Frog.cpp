//cpp
#include "common.h"
#include "utils/lodepng.h"
#include "utils/SourcePath.h"

//GLuint texId;
GLuint frog_texture;


using namespace Angel;


#ifdef _WIN32
static
unsigned int lodepng_decode_wfopen(std::vector<unsigned char>& out, unsigned& w, unsigned& h,
  const std::string& filename,
  LodePNGColorType colortype = LCT_RGBA, unsigned bitdepth = 8)
{
  std::wstring wcfn;
  if (u8names_towc(filename.c_str(), wcfn) != 0)
    return 78;
  FILE* fp = _wfopen(wcfn.c_str(), L"rb");
  if (fp == NULL) { return 78; }

  std::vector<unsigned char> buf;
  fseek(fp, 0L, SEEK_END);
  long const size = ftell(fp);
  if (size < 0) {
    fclose(fp);
    return 78;
  }

  fseek(fp, 0L, SEEK_SET);
  buf.resize(size);
  fread(buf.data(), 1, size, fp);
  fclose(fp);

  return lodepng::decode(out, w, h, buf, colortype, bitdepth);
}
#endif //_WIN32
void Frog::loadFreeImageTexture(const char* lpszPathName, GLuint textureID, GLuint GLtex){
  
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


//frog constructor
Frog::Frog(){
    Frog * frog;
    
    //frog colors
    frog_color[0] = vec3( 0.0, 1.0, 0.0);
    frog_color[1] = vec3( 1.0, 1.0, 0.0);
    frog_color[2] = vec3( 0.0, 0.0, 0.0);
    frog_color[3] = vec3( 1.0, 0.0, 0.0);
    
    //frog verts
    frog_vert[0] = vec2( 12.0, 2.0);
    frog_vert[1] = vec2(11.0, 2.0);
    frog_vert[2] = vec2(12.0, 3.0);
   frog_vert[3] = vec2( 11.0 , 3.0);
    

    //frog position (based on bottom left corner)
    state.xpos = 11;
    state.ypos = 2;

};



const int frog_size = { 4 };
const int obstacle_size = { 4 };





//Called everytime an animation tick happens
void Frog::update_state(){
  
  // Screen Wrapping:
  // Right side
    // Accounts for log
    state.xpos += state.velocity;
    

    // Screen Wrapping:
    // Right side
    if((state.xpos)>22){
      state.xpos = 0;
      for(int i=0; i<frog_size; i++){
        if(i%2)
          frog_vert[i].x = 1.0;
        else
          frog_vert[i].x = 0.0;
      }
    }
    // Left Side
    else if((state.xpos)<0){
      state.xpos = 22;
      for(int i=0; i<frog_size; i++){
        if(i%2)
          frog_vert[i].x = 23.0;
        else
          frog_vert[i].x = 22.0;
      }
    }

    // Not on side
    else {
      frog_vert[0].x = floor(state.xpos) + 1;
      frog_vert[1].x = floor(state.xpos);
      frog_vert[2].x = floor(state.xpos) + 1;
      frog_vert[3].x = floor(state.xpos);
    }

  }


//Initialize the gl state and variables
void Frog::gl_init(){
    Frog frog;
  //!!!!!!!!Populate frog_vert and frog_color
  size_t frog_bytes = sizeof(frog_vert);
  size_t frog_color_bytes = sizeof(frog_color);
  
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
  glBindFragDataLocation(GLvars.program, 0, "fragColor2");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vtex_location = glGetAttribLocation(GLvars.program, "vTexCoord" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );
   
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
    //Generate buffer to hold our vertex data
    glGenBuffers( 1, &GLvars.buffer );
 
    glGenTextures( 1, &frog_texture );
    
    std::string frog_img = source_path + "/images/frog.png" ;
      loadFreeImageTexture(frog_img.c_str(), frog_texture, GL_TEXTURE1);
      glUniform1i( glGetUniformLocation(GLvars.program, "textureFrog"), 1 );
  
    //Set GL state to use vertex array object
    glBindVertexArray( GLvars.vao );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, frog_bytes+ frog_color_bytes, NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, frog_bytes, frog_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, frog_bytes, frog_color_bytes, frog_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vtex_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( GLvars.vtex_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(frog_bytes) );
  
  glBindVertexArray(0);
}



//Draw a frog
void Frog::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
   // glBindTexture( GL_TEXTURE_2D, texId );
  glBindVertexArray( GLvars.vao );
  
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv(GLvars.M_location, 1, GL_TRUE, proj);

  //Draw ship
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
  
  glBindVertexArray(0);
  glUseProgram(0);

}



