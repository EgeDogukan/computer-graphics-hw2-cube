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
int positionFaceRepresentations[NumCubes][3] = { // 1 front, 2 right, 3 back, 4 left, 5 top, 6 bottom
    {1,2,5},
    {2,3,5},
    {1,2,6},
    {2,3,6},
    {1,4,5},
    {3,4,5},
    {1,4,6},
    {3,4,6},
};

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
            std::cout << temp_view, "\n";
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


//---------------------------------------------------------------------
//
// init
//

void
init()
{
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
    
    for(int index: faces[1]) {
        model_views[index] = getGlobalView() * RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] ) * RotateZ( Theta[Zaxis] ) * getInverseGlobalView() * model_views[index];
    }
    
    
    //try this when using perspective projection around fixed axis
    //model_view =   Translate(0,0,-2.5) * RotateX( Theta[Xaxis] ) * RotateY( Theta[Yaxis] ) * RotateZ( Theta[Zaxis] ) * Translate(0,0,2.5) * model_view ;
    
    for(int i = 0; i < NumCubes; i++) {
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_views[i] );
        glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
    }
    
    glFlush();
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   
    switch( key ) {
        case GLFW_KEY_ESCAPE: case GLFW_KEY_Q:
            exit( EXIT_SUCCESS );
            break;
        case GLFW_KEY_K:
            std::cout << model_views[0], "\n";
            std::cout << model_views[1], "\n";
            std::cout << model_views[2], "\n";
            std::cout << model_views[3], "\n";
            std::cout << model_views[4], "\n";
            std::cout << model_views[5], "\n";
            std::cout << model_views[6], "\n";
            std::cout << model_views[7], "\n";
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // the following emulates the middle button via shift modifier key
    
    if ( action == GLFW_PRESS ) {
        switch( button ) {
            case GLFW_MOUSE_BUTTON_RIGHT:    Axis = Xaxis;  break;
            //case GLFW_MOUSE_BUTTON_MIDDLE:  Axis = Yaxis;  break;
            case GLFW_MOUSE_BUTTON_LEFT:   if (mods & GLFW_MOD_SHIFT) Axis = Yaxis;
            else Axis = Zaxis;  break;
        }
    }
}

void
update( void )
{
    
    // use this to have rotation around fixed axes
    Theta[0] = Theta[1] = Theta[2] = 0.0;
    Theta[Axis] = 1.0;

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
        
        display();
        glfwSwapBuffers(window);
        
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}




