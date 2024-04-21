//
//  Display a rotating cube around fixed coordinate axes
//

#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 points[8] = {
    point4( -0.49, -0.49,  0.49, 1.0 ),
    point4( -0.49,  0.49,  0.49, 1.0 ),
    point4(  0.49,  0.49,  0.49, 1.0 ),
    point4(  0.49, -0.49,  0.49, 1.0 ),
    point4( -0.49, -0.49, -0.49, 1.0 ),
    point4( -0.49,  0.49, -0.49, 1.0 ),
    point4(  0.49,  0.49, -0.49, 1.0 ),
    point4(  0.49, -0.49, -0.49, 1.0 )
};

// RGBA olors
color4 colors[NumVertices] = {
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(1.0, 0.647, 0.0, 1.0),  // orange
    color4(1.0, 0.647, 0.0, 1.0),  // orange
    color4(1.0, 0.647, 0.0, 1.0),  // orange
    color4(1.0, 0.647, 0.0, 1.0),  // orange
};

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Zaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;
const int NumCubes = 8;
mat4 model_views[NumCubes];
double angles[3] = {0, 45, 45};

int faces[6][4];
double positionValues[NumCubes][3] = {
    {0.5,0.5,0.5},
    {0.5,0.5,-0.5},
    {0.5,-0.5,0.5},
    {0.5,-0.5,-0.5},
    {-0.5,0.5,0.5},
    {-0.5,0.5,-0.5},
    {-0.5,-0.5,0.5},
    {-0.5,-0.5,-0.5}
};
int positionFaceRepresentations[NumCubes][3] = { // 0 front, 1 right, 2 back, 3 left, 4 top, 5 bottom
    {0,1,4},
    {1,2,4},
    {0,1,5},
    {1,2,5},
    {0,3,4},
    {2,3,4},
    {0,3,5},
    {2,3,5},
};

double TotalRotation = 90;
int selectedFace = 0;
int turnDirection = 1;

double mouseStartX = 0.0;
double mouseStartY = 0.0;
double mouseX = 0.0;
double mouseY = 0.0;
bool rightMouseButtonPressed = false;
bool leftMouseButtonPressed = false;



int highlightedFace = -1; // No face highlighted initially

// The highlight color
color4 highlightColor = color4(1.0, 1.0, 0.0, 1.0); // Yellow for highlighting

// Function prototypes
int pick(int x, int y);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);



mat4 getGlobalView() {
    mat4 global_view = RotateX(angles[0]) * RotateY(angles[1]) * RotateZ(angles[2]);
    return global_view;
}

mat4 getInverseGlobalView() {
    mat4 inverse_global_view = RotateZ(-angles[2]) * RotateY(-angles[1]) * RotateX(-angles[0]);
    return inverse_global_view;
}

void setFaces() {
    double positions[NumCubes][3];
    for(int i = 0; i < NumCubes; i++) {
        for(int j = 0; j < 3; j++) {
            mat4 temp_view = getInverseGlobalView() * model_views[i];
            positions[i][j] = temp_view[j][3];
        }
    }
    
    int faceIndexes[8] = {0};
    
    for(int i = 0; i < NumCubes; i++) {
        for(int j = 0; j < NumCubes; j++) {
            if(abs(positions[i][0]-positionValues[j][0]) < 0.5 &&
               abs(positions[i][1]-positionValues[j][1]) < 0.5 &&
               abs(positions[i][2]-positionValues[j][2]) < 0.5) {
                for(int face: positionFaceRepresentations[j]) {
                    faces[face][faceIndexes[face]++] = i;
                }
            }
        }
    }
}

GLuint program;
GLuint Color;


//---------------------------------------------------------------------
//
// init
//

void
init()
{
    std::cout << " init \n";
    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );

    // Load shaders and use the resulting shader program
    program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    
    GLuint cube_indices[] = {
            0, 1, 2,
            2, 3, 0,
            1, 5, 6,
            6, 2, 1,
            7, 6, 5,
            5, 4, 7,
            4, 0, 3,
            3, 7, 4,
            4, 5, 1,
            1, 0, 4,
            3, 2, 6,
            6, 7, 3
        };
    
    // Create and initialize an index buffer object
    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 4, BUFFER_OFFSET(sizeof(points)) );

    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    // Set projection matrix
    mat4  projection;
    projection = Ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // Ortho(): user-defined function in mat.h
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
    
    //try this for perspective projection
    //projection = Perspective( 45.0, 1.0, 0.5, 3.0 );
    //glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
    Color = glGetUniformLocation( program, "color" );

    
    //model_view=identity();
    for(int i = 0; i < NumCubes; i++) {
        model_views[i]=  getGlobalView() * Translate(positionValues[i][0],positionValues[i][1],positionValues[i][2]);
    }
    setFaces();
    
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}


//---------------------------------------------------------------------
//
// display
//


void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //  Generate the model-view matrix
    
    //use this to rotate around fixed coordinate axes
    //model_view =   RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] ) * RotateZ( Theta[Zaxis] ) * model_view ;
    
    //use this to rotate around cube's own axes
    //model_view =   model_view  * RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] ) * RotateZ( Theta[Zaxis] ) ;
    
    
    //try this when using perspective projection around fixed axis
    //model_view =   Translate(0,0,-2.5) * RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] ) * RotateZ( Theta[Zaxis] ) * Translate(0,0,2.5) * model_view ;
    
    for(int i = 0; i < NumCubes; i++) {
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_views[i] );
        glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
    }
    
    glFlush();
}

void update()
{
    if (TotalRotation < 90.0) {
        // use this to have rotation around fixed axes
        Theta[0] = Theta[1] = Theta[2] = 0.0;
        Theta[Axis] = 1.5 * turnDirection;
        
        for(int index: faces[selectedFace]) {
            model_views[index] = getGlobalView() * RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] ) * RotateZ( Theta[Zaxis] ) * getInverseGlobalView() * model_views[index];
        }
        TotalRotation += 1.5;
    }
}

void turnCube(int direction) {
    if(selectedFace == 0 || selectedFace == 2) {
        Axis = Zaxis;
    }
    else if (selectedFace == 1 || selectedFace == 3) {
        Axis = Xaxis;
    }
    else if (selectedFace == 4 || selectedFace == 5) {
        Axis = Yaxis;
    }
    
    if(selectedFace == 0 || selectedFace == 1 || selectedFace == 4) {
        turnDirection = direction;
    }
    else if(selectedFace == 2 || selectedFace == 3 || selectedFace == 5) {
        turnDirection = -direction;
    }
    TotalRotation = 0;
}

void setSelectedFace(int face) {
    if(TotalRotation >= 90) {
        selectedFace = face;
    }
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   
    switch( key ) {
        case GLFW_KEY_ESCAPE: case GLFW_KEY_Q:
            exit( EXIT_SUCCESS );
            break;
        case GLFW_KEY_A: // 0 front, 1 right, 2 back, 3 left, 4 top, 5 bottom
            setSelectedFace(0);
            break;
        case GLFW_KEY_S:
            setSelectedFace(1);
            break;
        case GLFW_KEY_D:
            setSelectedFace(2);
            break;
        case GLFW_KEY_Z:
            setSelectedFace(3);
            break;
        case GLFW_KEY_X:
            setSelectedFace(4);
            break;
        case GLFW_KEY_C:
            setSelectedFace(5);
            break;
        case GLFW_KEY_LEFT:
            if(TotalRotation >= 90) {
                setFaces();
                turnCube(1);
            }
            break;
        case GLFW_KEY_RIGHT:
            if(TotalRotation >= 90) {
                setFaces();
                turnCube(-1);
            }
            break;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if ( action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) { // this is from lecture, not implemented
            //glDrawBuffer(GL_BACK); //back buffer is default thus no need
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //Render triangles with different id colors to back buffer
            glUniform4f( Color, 0.0, 1.0, 0.0, 1.0 );
            glDrawArrays( GL_TRIANGLES, 0, 3 );
            glUniform4f( Color, 0.0, 0.0, 1.0, 1.0 );
            glDrawArrays(GL_TRIANGLES, 3, 3);
            glFlush(); //forces all drawing commands to be sent to the graphics card and executed immediately.
            
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            int fb_width, fb_height;
            glfwGetFramebufferSize(window, &fb_width, &fb_height);
            int win_width, win_height;
            glfwGetWindowSize(window, &win_width, &win_height);
            
            //Have to differentiate between window and frame buffer sizes
            x*=(fb_width/win_width);
            y*=(fb_height/win_height);
            y = fb_height - y;
                    
            //glReadPixels reads from frame buffer, hence use frame buffer size
            unsigned char pixel[4];
            glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
            if (pixel[0]==0 && pixel[1]==255 && pixel[2]==0) std::cout << "First triangle"<<std::endl;
            else if (pixel[0]==0 && pixel[1]==0 && pixel[2]==255) std::cout << "Second triangle"<<std::endl;
            else std::cout << "None"<<std::endl;
            
            std::cout << "R: " << (int)pixel[0] << std::endl;
            std::cout << "G: " << (int)pixel[1] << std::endl;
            std::cout << "B: " << (int)pixel[2] << std::endl;
            std::cout << std::endl;
            
            //glfwSwapBuffers(window); //you can enable (and disable the other) this to display the triangles with their hidden id colors
        }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS)
        {
            rightMouseButtonPressed = true;
            glfwGetCursorPos(window, &mouseStartX, &mouseStartY);
        }
        else if (action == GLFW_RELEASE)
        {
            rightMouseButtonPressed = false;
        }
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        leftMouseButtonPressed = true;

        glfwGetCursorPos(window, &mouseStartX, &mouseStartY);
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        leftMouseButtonPressed = false;
    }
}

void rotateWithMouse(GLFWwindow* window) {
    if(!rightMouseButtonPressed){
        return;
    }
    glfwGetCursorPos(window, &mouseX, &mouseY);
    
    for(int i = 0; i < NumCubes; i++) {
        model_views[i]=  getInverseGlobalView() * model_views[i];
    }
    
    double deltaX = (mouseX - mouseStartX) / 2;
    double deltaY = (mouseY - mouseStartY) / 2;
    
    angles[0] += deltaY;
    angles[0] = fmod(angles[0], 360);
    
    if(angles[0] > 90 && angles[0] < 270){
        angles[1] -= deltaX;
        angles[1] = fmod(angles[1], 360);
    } else {
        angles[1] += deltaX;
        angles[1] = fmod(angles[1], 360);
    }
    
    for(int i = 0; i < NumCubes; i++) {
        model_views[i]=  getGlobalView() * model_views[i];
    }
    
    mouseStartX = mouseX;
    mouseStartY = mouseY;
}

// Add this function to convert screen coordinates to object coordinates and perform the picking
int pick(int x, int y) {
    // Placeholder for picking logic, should return the face index or -1
    // You will need to implement this based on your camera setup
    return -1;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    highlightedFace = pick(xpos, ypos); // Perform picking with the current mouse position
}


// Call this function in your main rendering loop to perform the blinking effect
void applyBlinkingEffect(GLFWwindow* window) {
    highlightedFace = 0;
    setSelectedFace(0);

    if(!leftMouseButtonPressed){
        return;
    }
    glfwGetCursorPos(window, &mouseX, &mouseY);

    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float>(currentTime - lastTime).count();

    if (highlightedFace != -1) {
        // Calculate the blinking intensity based on the elapsed time
        float intensity = (sin(time * 3.14f * 2.0f) + 1.0f) * 0.5f; // Oscillates between 0 and 1
        glUniform1f(glGetUniformLocation(program, "intensity"), intensity);
    } else {
        glUniform1f(glGetUniformLocation(program, "intensity"), 0.0f); // No blinking when no face is highlighted
    }
}


//---------------------------------------------------------------------
//
// main
//

int
main()
{
    if (!glfwInit())
            exit(EXIT_FAILURE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(512, 512, "Spin Cube", NULL, NULL);
    glfwMakeContextCurrent(window);
    
    if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    
    init();

    double frameRate = 60, currentTime, previousTime = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        currentTime = glfwGetTime();
        if (currentTime - previousTime >= 1/frameRate){
            previousTime = currentTime;
            update();
        }
        rotateWithMouse(window);
        applyBlinkingEffect(window); // Apply blinking effect
        display();
        glfwSwapBuffers(window);
        
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}




