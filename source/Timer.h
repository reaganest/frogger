//header
#ifndef __Timer__
#define __Timer__

#include "common.h"
#include <time.h>
class Timer {
public:
    vec2 timer_vert[4]; //whatever number needed
    vec3 timer_color[4];
    struct {
        int xpos;
        int ypos;
        vec2 cur_location;
        
    } state;
    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
    } GLvars;
//public:
    Timer();
    
      
    void gl_init();
        
    void draw(mat4 proj);
      
};


#endif /* defined(__Timer__) */
