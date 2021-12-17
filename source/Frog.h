//header
#ifndef __Frog__
#define __Frog__

#include "common.h"
class Frog {
public:
    vec2 frog_vert[4]; //whatever number needed
    vec3 frog_color[4];
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
    Frog();
    
    // hopRight and hopLeft controlled by 1/21 (by columns/width) 
    inline void hopRight(){
        frog_vert[0].x += 1.0;
        frog_vert[1].x += 1.0;
        frog_vert[2].x += 1.0;
        frog_vert[3].x += 1.0;
        state.xpos += 1;
    }
    inline void hopLeft(){
        frog_vert[0].x -= 1.0;
        frog_vert[1].x -= 1.0;
        frog_vert[2].x -= 1.0;
        frog_vert[3].x -= 1.0;
        state.xpos -= 1;
    }
    // hopUp and hopDown controlled by 1/21 (by rows/height)
    inline void hopUp(){
        frog_vert[0].y += 1.0;
        frog_vert[1].y += 1.0;
        frog_vert[2].y += 1.0;
        frog_vert[3].y += 1.0;
        state.ypos += 1;
        
    }
    inline void hopDown(){
        if(state.ypos>2){
            frog_vert[0].y -= 1.0;
            frog_vert[1].y -= 1.0;
            frog_vert[2].y -= 1.0;
            frog_vert[3].y -= 1.0;
            state.ypos -= 1;
        }
    }
    void update_state();
      
    void gl_init();
        
    void draw(mat4 proj);
      
};


#endif /* defined(__Frog__) */
