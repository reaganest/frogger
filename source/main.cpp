//main
#include "common.h"

using namespace Angel;

Frog frog;
unsigned int number_of_deaths = 0;
// we could declare the other objects here too

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    // Key callbacks for hopping: might end up modifying slightly
    if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        frog.hopLeft();
    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        frog.hopRight();
    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
        frog.hopUp();
    if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
        frog.hopDown();
}

// Useful functions

// Checks collision with obstacles of current row
bool overlaps(Frog * frog, std::vector < Obstacle > curRow){
    
    /*
    iterate over every obstacle in the current row, figure out where its pixels are,
    return true if frog's x position is in one of the obstacles
    (screen is 640x480, so there are 640(?) possible pixel values, probably less
    since the screen has borders
    */
    return false; //temporary
}

// Takes in frog object, current obstacle row, and frog's y position, outputs boolean
bool died(Frog * frog, std::vector < Obstacle > curRow){
    
    bool hitCar = false;
    // 10 is placeholder, want to check only the road
    if (frog->state.ypos < 10){
        //if overlaps(frog, curRow)
            //hitCar = true;
        
    }

    bool inWater = true;
    // 9 is placeholder, want to check only river
    if (frog->state.ypos > 9){
        //if overlaps(frog,curRow)
          //  inWater = false;
        
    }
    
    if (inWater || hitCar)
        return true;

    return false;
    number_of_deaths++;
}

void endGame(){
   if (number_of_deaths == 3) {
        GLFWwindow* window;
        glfwDestroyWindow(window);
    
   }
    // End the game; game over screen
}
void init(){
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
  frog.gl_init();
}

//Calls update 5 times a second
void animate()
{
    if(glfwGetTime() > 0.2){
        glfwSetTime(0.0);
        if(number_of_deaths<3) {
          frog.update_state();
          obstacles.update_states();
          bool died = died(frog, obstacles);
          updateTimer();
        } else {
          endgame();
          // move frog to start of level
        }
    }
}

int main(void)
{
  GLFWwindow* window;
  
  glfwSetErrorCallback(error_callback);
  
  if (!glfwInit())
    exit(EXIT_FAILURE);
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwWindowHint(GLFW_SAMPLES, 10);
  
  
  // Change window size(?)
  window = glfwCreateWindow(640, 480, "Frogger", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwSetKeyCallback(window, key_callback);
  
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  
  init();
  
  while (!glfwWindowShouldClose(window)){
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //Pick a coordinate system that makes the most sense to you
    //(left, right, top, bottom)
    mat4 proj = Ortho2D(-1.0, 1.0, -1.0, 1.0);
    
    animate();
    
    glClear(GL_COLOR_BUFFER_BIT);

     
    //Draw all the sprites here
      frog.gl_init();
    frog.draw(proj);
    //everything_else.draw(proj);

    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
