//cpp
#include "common.h"
#include "utils/SourcePath.h"



//timer constructor
Timer::Timer(){
    Timer * timer;
    //int start = clock();
    
    //timer colors
    timer_color[0] = vec3( 1.0, 0.0, 0.0);
    timer_color[1] = vec3( 1.0, 0.0, 0.0);
    timer_color[2] = vec3( 1.0, 0.0, 0.0);
    timer_color[3] = vec3( 1.0, 0.0, 0.0);
    
    //timer verts
    timer_vert[0] = vec2( 23.0, 0.0);
    timer_vert[1] = vec2(11.0, 0.0);
    timer_vert[2] = vec2(23.0, 1.0);
    timer_vert[3] = vec2( 11.0 , 1.0);
    state.xpos = 11;
    state.ypos = 0;


};

const int timer_size = { 4 };
//const int obstacle_size = { 4 };





//Called everytime an animation tick happens
    
  

//Initialize the gl state and variables
void Timer::gl_init(){
  //timer
  //!!!!!!!!Populate timer_vert and timer_color
  size_t timer_bytes = 4*sizeof(timer_vert);
  size_t timer_color_bytes = 4*sizeof(timer_color);
  
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
  glBufferData( GL_ARRAY_BUFFER, timer_bytes+ timer_color_bytes, NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, timer_bytes, timer_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, timer_bytes, timer_color_bytes, timer_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(timer_bytes) );
  
  glBindVertexArray(0);
}



//Draw a timer
void Timer::draw(mat4 proj){
    
    glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
  glUniformMatrix4fv(GLvars.M_location, 1, GL_TRUE, proj);
    
  //If you have a modelview matrix, pass it with proj
  //Draw Timer
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  
  glBindVertexArray(0);
  glUseProgram(0);

}



