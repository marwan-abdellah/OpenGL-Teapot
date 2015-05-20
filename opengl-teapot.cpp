#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

#include <math.h>
#include <unistd.h>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512

// X-rotation
GLfloat xRot = 0.f;

// Y-rotation
GLfloat yRot = 0.f;

// Z-rotation
GLfloat zRot = 0.f;
\
// X-rotation CUBE
GLfloat xRotCube= 0.f;

// Y-rotation CUBE
GLfloat yRotCube = 0.f;

// Z-rotation CUBE
GLfloat zRotCube = 0.f;

// Teapot size
GLdouble size = 1;

// FBO
GLuint fboId;

// Texture attached to the FBO
GLuint fboTexId;

// Render to FBO
bool renderOnbox = true;

/******************************************************************************/
// Prototypes
/******************************************************************************/
void initialize(int argc, char** argv);
void keyboard(unsigned char key, int x, int y);
void display(void);
void reshape(int width, int height);
void idle(void);
void renderTeapot();
/******************************************************************************/

/**
 * @brief randf
 * @return
 */
float randf()
{
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

/**
 * @brief initializeFBO
 */
void initializeFBO()
{
    // Generate the FBO and assign an ID to it
    glGenFramebuffers(1, &fboId);

    // Bind the FBO to set its properties
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    // Generate the texture we're going to render the scene to
    glGenTextures(1, &fboTexId);

    // "Bind" the newly created texture.
    glBindTexture(GL_TEXTURE_2D, fboTexId);

    // Give an empty image to OpenGL ( the last "0" ) to allocate the texture
    // on the GPU.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 WINDOW_WIDTH, WINDOW_HEIGHT,
                 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fboTexId, 0);
}

/**
 * @brief initialize
 * @param argc
 * @param argv
 */
void initialize(int argc, char** argv)
{
    // Initialize GLEW
    glutInit(&argc, argv);

    // Display mode
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);

    // Window size
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create the window
    glutCreateWindow("Teapot FBO");

    // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    // Clear the buffer color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Register the GLUT functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    // GLEW initialization
    glewInit();

    // Initializtion FBO
    // initializeFBO();
}

/**
 * @brief renderTeapot
 */
void renderTeapot()
{
    // Clear color of the FBO
    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

    // Clear Screen And Depth Buffer on the framebuffer to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset the matrix
    glMatrixMode(GL_MODELVIEW);

    // Clean the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    // Load the I
    glLoadIdentity();

    // Translation
    glTranslatef(0.0, 0.0, 0.f);

    // Color the teapot
    glColor3f(randf(), randf(), randf());

    // Rotate the teapot
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    // Scale the teapot
    glScalef(1.0, 1.0, 1.0);

    // Draw the teapot
    glutSolidTeapot(size);
}

/**
 * @brief renderToFBO
 */
void renderToFBO()
{
    // Bind the FBO to render to it
    glBindFramebuffer(GL_FRAMEBUFFER, fboId);

    // Render on the whole framebuffer
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Render the teapot to the FBO texture
    renderTeapot();

    // Render back on screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
 * @brief drawBox
 */
void drawBox()
{
    glBegin(GL_QUADS);

    //////////////////////////////////////////////////////////////// Front Face
    // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

    // Bottom Right Of The Texture and Quad`
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);

    // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);

    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    //////////////////////////////////////////////////////////////// Back Face
    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

    // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

    // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
    //////////////////////////////////////////////////////////////// Top Face
    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

    // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);

    // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
    //////////////////////////////////////////////////////////////// Bottom Face
    // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

    // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);

    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    //////////////////////////////////////////////////////////////// Right face
    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

    // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);

    // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
    //////////////////////////////////////////////////////////////// Left Face
    // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

    // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

    // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

    // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

    glEnd();
}

/**
 * @brief drawQuad
 */
void drawQuad()
{
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);
    glEnd();
}

/**
 * @brief renderTextureToGeometry
 */
void renderTextureToGeometry()
{
    // Render the teapot to the FBO
    renderToFBO();

    // Clear color of the FBO
    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

    // Clear Screen And Depth Buffer on the framebuffer to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable the 2D texturing
    glEnable(GL_TEXTURE_2D);

    // Bind our FBO texture
    glBindTexture(GL_TEXTURE_2D, fboTexId);

    // Set The Current Viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Reset The Modelview Matrix
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(xRotCube, 1.0f, 0.0f, 0.0f);
    glRotatef(yRotCube, 0.0f, 1.0f, 0.0f);
    glRotatef(zRotCube, 0.0f, 0.0f, 1.0f);
    glColor3f(1, 1, 1);

    // glScalef(0.5, 0.5, 0.5);

    if (renderOnbox) {
        // Texture the CUBE with the teapot texture
        drawBox();
    } else {
        // Texture a quad
        drawQuad();
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    // Disable the 2D texturing
    glDisable(GL_TEXTURE_2D);

    // Swap the buffers
    glutSwapBuffers();
}

/**
 * @brief display
 */
void display(void)
{
    // Render the texture to the cube.
    renderTextureToGeometry();

    // renderTeapot();

    // Swap the buffers
    glutSwapBuffers();
}

/**
 * @brief keyboard
 * @param key
 * @param x
 * @param y
 */
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27 :   // Escape
    case 'q':
        exit(0);
        break;

    case ' ':
        renderOnbox = !(renderOnbox);
        break;

    default:
        break;
    }
}

/**
 * @brief reshape
 * @param x
 * @param y
 */
void reshape(int width, int height)
{
    if (height == 0 || width == 0) return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    const float furstumSideLength = 5;
    glOrtho(-furstumSideLength / 2,
            +furstumSideLength / 2,
            -furstumSideLength / 2,
            +furstumSideLength / 2,
            -100, +100);
    glViewport(0, 0, width, height);
}

/**
 * @brief idle
 */
void idle(void)
{
    // Rotating the teapot
    xRot += 1.0;
    yRot += 1.0;
    zRot += 1.0;

    xRotCube += 1.0;
    yRotCube += 1.0;
    zRotCube += 1.0;

    // Redisplay
    glutPostRedisplay();
}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{
    // Initialize
    initialize(argc, argv);

    // Run the rendering loop
    glutMainLoop();

    return 0;
}
