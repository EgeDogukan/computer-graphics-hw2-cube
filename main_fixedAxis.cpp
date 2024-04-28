//
//  Display a rotating cube around fixed coordinate axes
//

#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 points[NumVertices] = {
    // Front face (triangles)
    point4(-0.49, -0.49, 0.49, 1.0),
    point4(-0.49, 0.49, 0.49, 1.0),
    point4(0.49, 0.49, 0.49, 1.0),

    point4(-0.49, -0.49, 0.49, 1.0),
    point4(0.49, 0.49, 0.49, 1.0),
    point4(0.49, -0.49, 0.49, 1.0),

    // Back face (triangles)
    point4(-0.49, -0.49, -0.49, 1.0),
    point4(-0.49, 0.49, -0.49, 1.0),
    point4(0.49, 0.49, -0.49, 1.0),

    point4(-0.49, -0.49, -0.49, 1.0),
    point4(0.49, 0.49, -0.49, 1.0),
    point4(0.49, -0.49, -0.49, 1.0),

    // Left face (triangles)
    point4(-0.49, -0.49, 0.49, 1.0),
    point4(-0.49, -0.49, -0.49, 1.0),
    point4(-0.49, 0.49, -0.49, 1.0),

    point4(-0.49, -0.49, 0.49, 1.0),
    point4(-0.49, 0.49, -0.49, 1.0),
    point4(-0.49, 0.49, 0.49, 1.0),

    // Right face (triangles)
    point4(0.49, -0.49, 0.49, 1.0),
    point4(0.49, -0.49, -0.49, 1.0),
    point4(0.49, 0.49, -0.49, 1.0),

    point4(0.49, -0.49, 0.49, 1.0),
    point4(0.49, 0.49, -0.49, 1.0),
    point4(0.49, 0.49, 0.49, 1.0),

    // Top face (triangles)
    point4(-0.49, 0.49, 0.49, 1.0),
    point4(-0.49, 0.49, -0.49, 1.0),
    point4(0.49, 0.49, -0.49, 1.0),

    point4(-0.49, 0.49, 0.49, 1.0),
    point4(0.49, 0.49, -0.49, 1.0),
    point4(0.49, 0.49, 0.49, 1.0),

    // Bottom face (triangles)
    point4(-0.49, -0.49, 0.49, 1.0),
    point4(-0.49, -0.49, -0.49, 1.0),
    point4(0.49, -0.49, -0.49, 1.0),

    point4(-0.49, -0.49, 0.49, 1.0),
    point4(0.49, -0.49, -0.49, 1.0),
    point4(0.49, -0.49, 0.49, 1.0)
};

point4 backPoints[NumVertices] = {
    // Front face (triangles)
    point4(-0.50, -0.50, 0.50, 1.0),
    point4(-0.50, 0.50, 0.50, 1.0),
    point4(0.50, 0.50, 0.50, 1.0),

    point4(-0.50, -0.50, 0.50, 1.0),
    point4(0.50, 0.50, 0.50, 1.0),
    point4(0.50, -0.50, 0.50, 1.0),

    // Back face (triangles)
    point4(-0.50, -0.50, -0.50, 1.0),
    point4(-0.50, 0.50, -0.50, 1.0),
    point4(0.50, 0.50, -0.50, 1.0),

    point4(-0.50, -0.50, -0.50, 1.0),
    point4(0.50, 0.50, -0.50, 1.0),
    point4(0.50, -0.50, -0.50, 1.0),

    // Left face (triangles)
    point4(-0.50, -0.50, 0.50, 1.0),
    point4(-0.50, -0.50, -0.50, 1.0),
    point4(-0.50, 0.50, -0.50, 1.0),

    point4(-0.50, -0.50, 0.50, 1.0),
    point4(-0.50, 0.50, -0.50, 1.0),
    point4(-0.50, 0.50, 0.50, 1.0),

    // Right face (triangles)
    point4(0.50, -0.50, 0.50, 1.0),
    point4(0.50, -0.50, -0.50, 1.0),
    point4(0.50, 0.50, -0.50, 1.0),

    point4(0.50, -0.50, 0.50, 1.0),
    point4(0.50, 0.50, -0.50, 1.0),
    point4(0.50, 0.50, 0.50, 1.0),

    // Top face (triangles)
    point4(-0.50, 0.50, 0.50, 1.0),
    point4(-0.50, 0.50, -0.50, 1.0),
    point4(0.50, 0.50, -0.50, 1.0),

    point4(-0.50, 0.50, 0.50, 1.0),
    point4(0.50, 0.50, -0.50, 1.0),
    point4(0.50, 0.50, 0.50, 1.0),

    // Bottom face (triangles)
    point4(-0.50, -0.50, 0.50, 1.0),
    point4(-0.50, -0.50, -0.50, 1.0),
    point4(0.50, -0.50, -0.50, 1.0),

    point4(-0.50, -0.50, 0.50, 1.0),
    point4(0.50, -0.50, -0.50, 1.0),
    point4(0.50, -0.50, 0.50, 1.0)
};



// RGBA olors
color4 colors[NumVertices] = {
    color4(1.0, 0.0, 0.0, 1.0),  // Front face (red)
    color4(1.0, 0.0, 0.0, 1.0),
    color4(1.0, 0.0, 0.0, 1.0),
    
    color4(1.0, 0.0, 0.0, 1.0),  // Front face (red)
    color4(1.0, 0.0, 0.0, 1.0),
    color4(1.0, 0.0, 0.0, 1.0),

    color4(0.0, 1.0, 0.0, 1.0),  // Back face (green)
    color4(0.0, 1.0, 0.0, 1.0),
    color4(0.0, 1.0, 0.0, 1.0),
    
    color4(0.0, 1.0, 0.0, 1.0),  // Back face (green)
    color4(0.0, 1.0, 0.0, 1.0),
    color4(0.0, 1.0, 0.0, 1.0),

    color4(0.0, 0.0, 1.0, 1.0),  // Left face (blue)
    color4(0.0, 0.0, 1.0, 1.0),
    color4(0.0, 0.0, 1.0, 1.0),
    
    color4(0.0, 0.0, 1.0, 1.0),  // Left face (blue)
    color4(0.0, 0.0, 1.0, 1.0),
    color4(0.0, 0.0, 1.0, 1.0),

    color4(1.0, 1.0, 0.0, 1.0),  // Right face (yellow)
    color4(1.0, 1.0, 0.0, 1.0),
    color4(1.0, 1.0, 0.0, 1.0),
    
    color4(1.0, 1.0, 0.0, 1.0),  // Right face (yellow)
    color4(1.0, 1.0, 0.0, 1.0),
    color4(1.0, 1.0, 0.0, 1.0),

    color4(1.0, 0.647, 0.0, 1.0),  // Top face (orange)
    color4(1.0, 0.647, 0.0, 1.0),
    color4(1.0, 0.647, 0.0, 1.0),
    
    color4(1.0, 0.647, 0.0, 1.0),  // Top face (orange)
    color4(1.0, 0.647, 0.0, 1.0),
    color4(1.0, 0.647, 0.0, 1.0),

    color4(1.0, 1.0, 1.0, 1.0),  // Bottom face (white)
    color4(1.0, 1.0, 1.0, 1.0),
    color4(1.0, 1.0, 1.0, 1.0),
    
    color4(1.0, 1.0, 1.0, 1.0),  // Bottom face (white)
    color4(1.0, 1.0, 1.0, 1.0),
    color4(1.0, 1.0, 1.0, 1.0),

};


// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Zaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;
const int NumCubes = 8;
mat4 model_views[NumCubes];
mat4 picking_model_views[NumCubes];
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

int turnCount = 20;
int turns[20][2];

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

    
    // Create and initialize an index buffer object
    GLuint index_buffer;
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)) );

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
    glClearColor(0.7, 0.7, 1.0, 1.0);
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
        glDrawArrays(GL_TRIANGLES,0, NumVertices);
    }
    
    glFlush();
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
    } else {
        if(turnCount > 0){
            selectedFace = turns[turnCount-1][0];
            turnDirection = turns[turnCount-1][1];
            setFaces();
            turnCube(turnDirection);
            TotalRotation = 0;
            turnCount --;
        }
    }
}


void setSelectedFace(int face) {
    if(TotalRotation >= 90) {
        selectedFace = face;
    }
}

void printHelp() {
    std::cout << "Help Menu:\n"
              << "  [ESC, Q] - Quit the application\n"
              << "  [A] - Select the front face of the cube\n"
              << "  [S] - Select the right face of the cube\n"
              << "  [D] - Select the back face of the cube\n"
              << "  [Z] - Select the left face of the cube\n"
              << "  [X] - Select the top face of the cube\n"
              << "  [C] - Select the bottom face of the cube\n"
              << "  [LEFT CLICK] - Select the clicked face of the cube\n"
              << "  [LEFT ARROW] - Rotate the selected face clockwise\n"
              << "  [RIGHT ARROW] - Rotate the selected face counterclockwise\n"
              << "  [RIGHT CLICK] - Mouse drag with right button, rotate the entire cube\n";
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

if (action == GLFW_PRESS) {   
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
            case GLFW_KEY_H:
                    printHelp();
                    break;
        }
    }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if ( action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) { // this is from lecture, not implemented
            //glDrawBuffer(GL_BACK); //back buffer is default thus no need
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            //Render triangles with different id colors to back buffer
            glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), backPoints );
            for(int i = 0; i < NumCubes; i++) {
                picking_model_views[i]=  getGlobalView() * Translate(positionValues[i][0],positionValues[i][1],positionValues[i][2]);
            }
            for(int i = 0; i < NumCubes; i++) {
                glUniformMatrix4fv( ModelView, 1, GL_TRUE, picking_model_views[i] );
                glDrawArrays(GL_TRIANGLES,0, NumVertices);
            }
            glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
            
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
            if (int(pixel[0]) == 255 && int(pixel[1]) == 0 && int(pixel[2]) == 0){
                selectedFace = 0;
            }
            if (int(pixel[0]) == 255 && int(pixel[1]) == 255 && int(pixel[2]) == 0){
                selectedFace = 1;
            }
            if (int(pixel[0]) == 0 && int(pixel[1]) == 255 && int(pixel[2]) == 0){
                selectedFace = 2;
            }
            if (int(pixel[0]) == 0 && int(pixel[1]) == 0 && int(pixel[2]) == 255){
                selectedFace = 3;
            }
            if (int(pixel[0]) == 255 && int(pixel[1]) == 165 && int(pixel[2]) == 0){
                selectedFace = 4;
            }
            if (int(pixel[0]) == 255 && int(pixel[1]) == 255 && int(pixel[2]) == 255){
                selectedFace = 5;
            }

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

void randomCubeShuffle() {
    srand(time(NULL)); // Initialize random seed

    for (int i = 0; i < 20; i++) {
        int randomFace = rand() % 6;     // Randomly select a face (0-5)
        int randomDirection = rand() % 2; // Randomly select a direction (0 or 1)

        // Rotate the cube based on the random face and direction
        turns[i][0] = randomFace;
        turns[i][1] = randomDirection == 0 ? 1 : -1;
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
    randomCubeShuffle();

    double frameRate = 60, currentTime, previousTime = 0.0;
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        currentTime = glfwGetTime();
        
        if (currentTime - previousTime >= 0.1/frameRate){
            previousTime = currentTime;
            update();
        }
        rotateWithMouse(window);
        display();
        glfwSwapBuffers(window);
        
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}




