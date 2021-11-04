// Header file for Obstacle
#ifndef __Obstacle__
#define __Obstacle__

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

#endif /* defined(__Frog) */
