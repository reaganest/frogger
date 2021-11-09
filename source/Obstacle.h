// Header file for Obstacle
#ifndef __Obstacle__
#define __Obstacle__

class Obstacle {
    vec2 obstacles_vert[4]; //whatever number needed
    vec3 obstacles_color[4];
    struct {
        int xpos;
        int ypos;
        float velocity;
        //add variable for type (e.g. log, snake, car, etc.)
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
    //int getXpos{ return xpos };
   // int getYpos{ return ypos };
   // float getVelocity{ return velocity };
      
    void gl_init();
        
    void draw(mat4 proj);
};

#endif /* defined(__Frog) */
