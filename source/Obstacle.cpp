// CPP file for Obstacle
#include "common.h"
#include "utils/lodepng.h"
#include "utils/SourcePath.h"

// obstacle constructor
Obstacle::Obstacle(int type, float xpos, int ypos, float velocity){
    Obstacle * obstacle;

    // setting x and y position
    ob_state.xpos = xpos;
    ob_state.ypos = ypos;

    // setting velocity
    ob_state.velocity = velocity;

    // obstacle type
    ob_state.type = type;

    /*switch(this->ob_state.type){
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
    */
    // obstacle colors (will be different later)
    obstacles_color[0] = vec3( 1.0, 1.0, 1.0 );
    obstacles_color[1] = vec3( 1.0, 1.0, 1.0 );
    obstacles_color[2] = vec3( 1.0, 1.0, 1.0 );
    obstacles_color[3] = vec3( 1.0, 1.0, 1.0 );

    obstacles_vert[0] = vec2( ob_state.xpos + 1.0, ob_state.ypos);
    obstacles_vert[1] = vec2( ob_state.xpos, ob_state.ypos);
    obstacles_vert[2] = vec2( ob_state.xpos + 1.0, ob_state.ypos + 1.0);
    obstacles_vert[3] = vec2( ob_state.xpos, ob_state.ypos + 1.0);
};

const int obstacle_size = { 4 };

void Obstacle::gl_init(){
    glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  
  std::string vshader = source_path + "/shaders/vshader.glsl";
  std::string fshader = source_path + "/shaders/fshader.glsl";
  
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
    glEnable(GL_COLOR_MATERIAL);
    glUseProgram( GLvars2.program );
    glBindVertexArray( GLvars2.vao );

    //If you have a modelview matrix, pass it with proj
    glUniformMatrix4fv(GLvars2.M_location, 1, GL_TRUE, proj);

    //Draw obstacle
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
    glUseProgram(0);

}
