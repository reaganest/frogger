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
    
    void update_state();
    int getXpos(){ return ob_state.xpos; }
    int getYpos(){ return ob_state.ypos; }
    float getVelocity(){ return ob_state.velocity; }
      
    void gl_init();
        
    void draw(mat4 proj);
};

#endif /* defined(__Obstacle__) */
