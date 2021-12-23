//header
#ifndef __Background__
#define __Background__

#include "common.h"
class Background {
public:
    vec2 background_vert[4]; //whatever number needed
    vec3 background_color[4];
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
        GLint vpos_location, vtex_location;   //reference to pos and color in shaders
        GLint M_location;     //Reference to matrix in shader
    } GLvars;
//public:
    Background();
    void loadFreeImageTexture(const char* lpszPathName, GLuint textureID, GLuint GLtex);
    void gl_init();
        
    void draw(mat4 proj);
      
};


#endif /* defined(__Background__) */
