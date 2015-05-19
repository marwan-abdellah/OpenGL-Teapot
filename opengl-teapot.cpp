#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

#include <math.h>
#include <unistd.h>

// X-rotation
GLfloat xRot = 0.f;

// Y-rotation
GLfloat yRot = 0.f;

// Z-rotation
GLfloat zRot = 0.f;

// Teapot size
GLdouble size = 1;



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
    glutInitWindowSize(400,350);

    // Create the window
    glutCreateWindow("Teapot FBO");

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    // Clear the buffer color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Register the GLUT functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
}

/**
 * @brief renderTeapot
 */
void renderTeapot()
{
    // Reset the matrix
    glMatrixMode(GL_MODELVIEW);

    // Clean the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

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
    default:
        break;
    }
}

/**
 * @brief display
 */
void display(void)
{
    // Render the teapot
    renderTeapot();

    // Swap the buffers
    glutSwapBuffers();
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
