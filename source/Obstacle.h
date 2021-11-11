// Header file for Obstacle
#ifndef __Obstacle__
#define __Obstacle__

#include "common.h"

class Obstacle {
    vec2 obstacles_vert[4]; //whatever number needed
    vec3 obstacles_color[4];
    struct {
        int xpos;
        int ypos;
        float velocity; // Pixels per frame, include direction (- for left, + for right)
        int type;
        // "type" refers to what the obstacle is:
        // 0=car, 1=log, 2=turtle, 3=gator, 4=snake
    } ob_state;
    struct {
        GLuint vao;           //Vertex array object
        GLuint program;       //shader program
        GLuint buffer;        //Vertex buffer objects
        GLuint vertex_shader, fragment_shader;  //Shaders
        GLint vpos_location, vcolor_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
    } GLvars2;

public:
    Obstacle(int type);
    
    inline void update_state() {
        // Update shape's position
        /*
        for (std::vector< vec2 >::iterator it = obstacles_vert.begin(); it != obstacles_vert.end(); ++it) {
            (*it).x += this->ob_state.velocity;
        }
        */
        //This will work fine for now, ignore stuff above
        obstacles_vert[0].x += ob_state.velocity;
        obstacles_vert[1].x += ob_state.velocity;
        obstacles_vert[2].x += ob_state.velocity;
        obstacles_vert[3].x += ob_state.velocity;
        
        //TODO: how do we deal with the snake turning?
        // Update xpos
        ob_state.xpos += ob_state.velocity;
        //TODO: updating turtle, gator, and snake's animation cycles
        // for turtles and gator, animation cycle affects hitboxes

    }

    int getXpos(){ return ob_state.xpos; }
    int getYpos(){ return ob_state.ypos; }
    float getVelocity(){ return ob_state.velocity; }
      
    void gl_init();
        
    void draw(mat4 proj);
};

#endif /* defined(__Obstacle__) */
