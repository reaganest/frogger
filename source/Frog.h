//header
#ifndef __Frog__Obstacle__
#define __Frog__Obstacle__

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
class Obstacle {
    vec2 obstacles_vert[4]; //whatever number needed
    vec3 obstacles_color[4];
    struct {
        vec2 cur_location;
        vec2 velocity;
    } state2;
    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
    } GLvars2;
public:
    Obstacle();
    
    void update_state();
      
      void gl_init();
        
      void draw(mat4 proj);
    void move_obstacle(vec2 dist, vec2 * vert, Obstacle * obstacle);
      
};


#endif /* defined(__Frog__Obstacle__) */
