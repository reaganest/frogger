// CPP file for Obstacle

#include "common.h"

// obstacle constructor
Obstacle::Obstacle(int type){
    
    // obstacle type
    this->ob_state.type = type;

    switch(this->ob_state.type){
        case(0):
            // Car
        case(1):
            // Log
        case(2):
            // Turtle
        case(3):
            // Gator
        case(4):
            // Snake
    }

    // obstacle colors (will be different later)
    obstacles_color[0] = vec3( 0.588, 0.294, 0.0 );
    obstacles_color[1] = vec3( 0.588, 0.294, 0.0 );
    obstacles_color[2] = vec3( 0.588, 0.294, 0.0 );
    obstacles_color[3] = vec3( 0.588, 0.294, 0.0 );
};

const int obstacle_size = { 4 };

// Implemented in header
//void Obstacle::update_state();

void Obstacle::gl_init(){
  
  std::string vshader = shader_path + "vshader.glsl";
  std::string fshader = shader_path + "fshader.glsl";
  
  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
  
  GLvars2.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GLvars2.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(GLvars2.vertex_shader);
  check_shader_compilation(vshader, GLvars2.vertex_shader);
  
  GLvars2.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GLvars2.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(GLvars2.fragment_shader);
  check_shader_compilation(fshader, GLvars2.fragment_shader);
  
  GLvars2.program = glCreateProgram();
  glAttachShader(GLvars2.program, GLvars2.vertex_shader);
  glAttachShader(GLvars2.program, GLvars2.fragment_shader);
  
  glLinkProgram(GLvars2.program);
  check_program_link(GLvars2.program);
  
  glBindFragDataLocation(GLvars2.program, 0, "fragColor");
  
  GLvars2.vpos_location   = glGetAttribLocation(GLvars2.program, "vPos");
  GLvars2.vcolor_location = glGetAttribLocation(GLvars2.program, "vColor" );
  GLvars2.M_location = glGetUniformLocation(GLvars2.program, "M" );
  
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars2.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars2.vao );
    
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars2.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars2.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, sizeof(obstacles_vert) + sizeof(obstacles_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(obstacles_vert), obstacles_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(obstacles_vert), sizeof(obstacles_color), obstacles_color );
  
  glEnableVertexAttribArray(GLvars2.vpos_location);
  glEnableVertexAttribArray(GLvars2.vcolor_location );
  
  glVertexAttribPointer( GLvars2.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars2.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(obstacles_vert)) );
  
  glBindVertexArray(0);
}

void Obstacle::draw(mat4 proj){

    glUseProgram( GLvars2.program );
    glBindVertexArray( GLvars2.vao );

    //If you have a modelview matrix, pass it with proj
    glUniformMatrix4fv(GLvars2.M_location, 1, GL_TRUE, proj);

    //Draw obstacle
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
    glUseProgram(0);

}
