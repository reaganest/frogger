//header
#ifndef __Frog__
#define __Frog__

#include "common.h"
class Frog {
    vec2 frog_vert[4]; //whatever number needed
    vec3 frog_color[4];
    struct {
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
public:
    Frog();
    inline void hopRight(){
        
    }
    inline void hopLeft(){
        
    }
    inline void hopUp(){
        
    }
    inline void hopDown(){
        
    }
    void update_state();
      
      void gl_init();
        
      void draw(mat4 proj);
      
};

#endif /* defined(__Frog__) */
