//cpp
#include "common.h"


//frog constructor
Frog::Frog(){
    Frog * frog;
    
    //frog colors
    frog_color[0] = vec3( 0.0, 1.0, 0.0);
    frog_color[1] = vec3( 0.0, 1.0, 0.0);
    frog_color[2] = vec3( 0.0, 1.0, 0.0);
    frog_color[3] = vec3( 0.0, 1.0, 0.0);
    
    frog_vert[0] = vec2( 12.0, 2.0);
    frog_vert[1] = vec2(11.0, 2.0);
    frog_vert[2] = vec2(12.0, 3.0);
    frog_vert[3] = vec2( 11.0 , 3.0);

};



const int frog_size = { 4 };
const int obstacle_size = { 4 };





//Called everytime an animation tick happens
void Frog::update_state(){
  /*  Frog * frog;
    std::vector < Obstacle > curRow;
 if (died(frog,curRow)==true){
    frog_vert[0] = vec2( 0.2, 0.0);
    frog_vert[1] = vec2( 0.0, 0.2);
    frog_vert[2] = vec2( 0.2, 0.2);
    frog_vert[3] = vec2( 0.0, 0.0); } */


}


//Initialize the gl state and variables
void Frog::gl_init(){
  //Frog
  //!!!!!!!!Populate frog_vert and frog_color
    size_t frog_bytes = 4*sizeof(frog_vert);
    size_t frog_color_bytes = 4*sizeof(frog_color);
  
  std::string vshader = shader_path + "vshader.glsl";
  std::string fshader = shader_path + "fshader.glsl";
  
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
  
  glBindFragDataLocation(GLvars.program, 0, "fragColor");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );
  
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );
    
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, frog_bytes+ frog_color_bytes, NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, frog_bytes, frog_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, frog_bytes, frog_color_bytes, frog_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(frog_bytes) );
  
    glBindVertexArray(0);
}



//Draw a frog
void Frog::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  
  //If you have a modelview matrix, pass it with proj
  glUniformMatrix4fv(GLvars.M_location, 1, GL_TRUE, proj);

  //Draw ship
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
  
  glBindVertexArray(0);
  glUseProgram(0);

}



