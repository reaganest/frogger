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
    int xpos;
    int ypos;
    // hopRight and hopLeft controlled by 1/20 (by columns/width) * 2 for some reason
    inline void hopRight(){
        frog_vert[0].x+= 0.1;
        frog_vert[1].x+= 0.1;
        frog_vert[2].x+= 0.1;
        frog_vert[3].x+= 0.1;
        }
    inline void hopLeft(){
        frog_vert[0].x-= 0.1;
        frog_vert[1].x-= 0.1;
        frog_vert[2].x-= 0.1;
        frog_vert[3].x-= 0.1;
    }
    // hopUp and hopDown controlled by 1/15 (by rows/height)
    inline void hopUp(){
        frog_vert[0].y+= 0.13333333;
        frog_vert[1].y+= 0.13333333;
        frog_vert[2].y+= 0.13333333;
        frog_vert[3].y+= 0.13333333;
        
    }
    inline void hopDown(){
        frog_vert[0].y-= 0.13333333;
        frog_vert[1].y-= 0.13333333;
        frog_vert[2].y-= 0.13333333;
        frog_vert[3].y-= 0.13333333;
        
    }
    void update_state();
      
      void gl_init();
        
      void draw(mat4 proj);
      
};


#endif /* defined(__Frog__) */
