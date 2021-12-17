//main
#include "common.h"

using namespace Angel;

Frog frog;
std::vector< std::vector<Obstacle> > rows;

// Initialize obstacles vector: first 9 entries cars, next 9 entries gators/turtles



//Obstacle  obstacle;
unsigned int number_of_deaths = 0;
// Keeps track of which ending spots are occupied
bool occupied[5] = { false, false, false, false, false};
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
    if (key == GLFW_KEY_LEFT) {
        if (action == GLFW_PRESS)
            frog.hopLeft();
        else if ((action == GLFW_REPEAT) && (glfwGetTime()>0.17))
            frog.hopLeft();
    }
    if (key == GLFW_KEY_RIGHT) {
        if (action == GLFW_PRESS)
            frog.hopRight();
        else if ((action == GLFW_REPEAT) && (glfwGetTime()>0.17))
            frog.hopRight();
    }
    if (key == GLFW_KEY_UP) {
        if (action == GLFW_PRESS)
            frog.hopUp();
        else if ((action == GLFW_REPEAT) && (glfwGetTime()>0.17))
            frog.hopUp();
    }
    if (key == GLFW_KEY_DOWN) {
        if (action == GLFW_PRESS)
            frog.hopDown();
        else if ((action == GLFW_REPEAT) && (glfwGetTime()>0.17))
            frog.hopDown();
    }
}

// Useful functions

// Checks collision with obstacles of current row
bool overlaps(Frog frog, std::vector < Obstacle > curRow){
    
    /*
    iterate over every obstacle in the current row, figure out where its pixels are,
    return true if frog's x position is in one of the obstacles
    (screen is 640x480, so there are 640(?) possible pixel values, probably less
    since the screen has borders
    */
    //TODO: make this work for obstacles with more than one square
    for(std::vector<Obstacle>::iterator it = curRow.begin(); it != curRow.end(); it++){
        if(frog.state.xpos == floor((*it).ob_state.xpos))
            return true;
    }
    return false;
}

// Takes in frog object, current obstacle row, and frog's y position, outputs boolean
bool died(Frog frog, std::vector < Obstacle > curRow){
    
    bool hitCar = false;
    
    // Safe squares (start)
    if(frog.state.ypos < 3)
        return false;

    // Roads, bank, and safe space in road
    if ((frog.state.ypos > 2) && (frog.state.ypos < 17)){
        if (overlaps(frog, curRow))
            hitCar = true;
    }

    bool inWater = true;
    // River + top row
    if (frog.state.ypos > 16){
        // overlaps checks Obstacles in row
        if (overlaps(frog, curRow)) {
            //TODO: need to account for turtles and gators.
            inWater = false;
        }
    }
    
    if (inWater || hitCar) {
        number_of_deaths++;
        return true;
    }
    return false;
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
          // Update state of all obstacles
          for(int i=0; i<23; i++){
            for(int j=0; j<2; j++){
                rows[i][j].update_state();
            }
          }
          // Checking if frog has reached goal
          //if(frog->state.ypos==22){
            // Check each
          //}
          //obstacle.update_state();
          int curRow = (frog.state.ypos) - 1;
          bool dead = died(frog, rows[curRow]);
          if(dead){
            frog.state.xpos = 11;
            frog.state.ypos = 2;
          }
       //   updateTimer();
        } else {
            endGame();
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
  window = glfwCreateWindow(736, 736, "Frogger", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwSetKeyCallback(window, key_callback);
  
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  
  // Populating Obstacles vector
  // Road: rows 3-11
  
  for(int i=0; i<23; i++){
      std::vector<Obstacle> row;
      // Final row
      if(i>21)
        row = {};
      // River
      else if(i>16) {
        // Logs
        if(i%2) {
          for(int j=0; j<3; j++) {
            // Spawn log
            row.push_back(Obstacle(1,((j*7) + 3), i, ((i!=19) ? (-1*((i+4.0)/10)) : ((i+4.0)/10))));
          }
        } else {
          for(int j=0; j<4; j++) {
            // Spawn turtle
            row.push_back(Obstacle(2,((j*5) + 3), i, ((i==18) ? (-1*((i+4.0)/10)) : ((i+4.0)/10))));
          }
        }
      }
      
      //Break 2 (riverbank)
      else if(i==16){
        row.push_back(NULL);
      }

      // Road 2
      else if(i>9){
        for(int j=0; j<2; j++){
          row.push_back(Obstacle(0,((j*11) + 3), i, ((i%2) ? (-1*((i+4.0)/10)) : ((i+4.0)/10))));
        }
      }

      // Break 1 (middle of road)
      else if(i==9){
        row.push_back(NULL);
      }

      // Road 1
      else if(i>2){
        for(int j=0; j<2; j++){
          row.push_back(Obstacle(0,((j*11) + 3), i, ((i%2) ? (-1*((i+4.0)/10)) : ((i+4.0)/10))));
        }
      }

      else {
        row.push_back(NULL);
      }

      /*
      for(int j=0; j<2; j++){
          row.push_back(Obstacle(0,((j*11) + 3), i+3, ((i%2) ? (-1*((i+4.0)/10)) : ((i+4.0)/10))));
      }
      */

      // Push whole row to rows
      rows.push_back(row);
  }
  

  // River: rows 13-21

  init();
  
  while (!glfwWindowShouldClose(window)){
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //Pick a coordinate system that makes the most sense to you
    //(left, right, top, bottom)
    mat4 proj = Ortho2D(0.0, 23.0, 0.0, 23.0);
    
    animate();
    
    glClear(GL_COLOR_BUFFER_BIT);

     
    // Draw all the sprites here
    

    // Drawing obstacles
    for(int i=0; i<23; i++){
        for(std::vector<Obstacle>::iterator it = rows[i].begin(); it != rows[i].end(); it++){
            // Draw all obstacles
            if(it[0] != NULL){
              (*it).gl_init();
              (*it).draw(proj);
            }
        }
    }
    
    // Drawing frog
    frog.gl_init();
    frog.draw(proj);

    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
