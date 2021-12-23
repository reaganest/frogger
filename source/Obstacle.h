// Header file for Obstacle
#ifndef __Obstacle__
#define __Obstacle__

#include "common.h"

class Obstacle {
public:
    vec2 obstacles_vert[4]; //whatever number needed
    vec3 obstacles_color[4];
    struct {
        float xpos;
        int ypos;
        float velocity; // Blocks per frame, include direction (- for left, + for right)
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

    Obstacle(int type, float xpos, int ypos, float velocity);
    
    inline void update_state() {
        // Update shape's position

        // Update xpos
        ob_state.xpos += ob_state.velocity;
        
        //Screen Wrapping:
        // Right side
        if((ob_state.xpos)>22){
            ob_state.xpos = 0;
            for(int i=0; i<4; i++){
                if(i%2)
                    obstacles_vert[i].x = 1.0;
                else
                    obstacles_vert[i].x = 0.0;
            }
        }
        
        // Left side
        if((ob_state.xpos)<0){
            ob_state.xpos = 22;
            for(int i=0; i<4; i++){
                if(i%2)
                    obstacles_vert[i].x = 23.0;
                else
                    obstacles_vert[i].x = 22.0;
            }
        }

        obstacles_vert[1].x = floor(ob_state.xpos);
        obstacles_vert[3].x = floor(ob_state.xpos);
        
        switch(ob_state.type){
          // Car
          case(0):
            obstacles_vert[0].x = floor(ob_state.xpos) + 1;
            obstacles_vert[2].x = floor(ob_state.xpos) + 1;
            break;
          // Log
          case(1):
            obstacles_vert[0].x = floor(ob_state.xpos) + 2;
            obstacles_vert[2].x = floor(ob_state.xpos) + 2;
            break;
          // Turtle
          case(2):
            obstacles_vert[0].x = floor(ob_state.xpos) + 2;
            obstacles_vert[2].x = floor(ob_state.xpos) + 2;
            break;
          // Gator
          case(3):
            obstacles_vert[0].x = floor(ob_state.xpos) + 2;
            obstacles_vert[2].x = floor(ob_state.xpos) + 2;
            break;
          //Snake
          case(4):
            obstacles_vert[0].x = floor(ob_state.xpos) + 1;
            obstacles_vert[2].x = floor(ob_state.xpos) + 1;
            break;
        }
        
        

        //TODO: updating turtle, gator, and snake's animation cycles
        // for turtles and gator, animation cycle affects hitboxes
        /*
        if (type>1) {
            // update animations every so often
            // update some variable that tells you whether surface is valid or not
        }
        */

    }

    int getXpos(){ return ob_state.xpos; }
    int getYpos(){ return ob_state.ypos; }
    float getVelocity(){ return ob_state.velocity; }
      
    void gl_init();

    void draw(mat4 proj);
};

#endif /* defined(__Obstacle__) */
