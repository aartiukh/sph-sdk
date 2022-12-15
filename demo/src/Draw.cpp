#include "Draw.h"

#define GL_SILENCE_DEPRECATION

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// include header with math functions
#define _USE_MATH_DEFINES
#include <math.h>

#include "algorithms/src/MarchingCubes.h"
#include "algorithms/src/Shapes.h"
#include "sph/src/Config.h"
#include "sph/src/SPH.h"

// Window dimensions
float aspect_ratio = 1.;
static int width = 900;
static int height = 900;

static float angle = 360;

static SPHSDK::SPH sph;

static SPHAlgorithms::Point3FVector mesh;

void renderSphere(float x, float y, float z, double radius, double velocity, int subdivisions/*, GLUquadricObj* quadric*/)
{
    glPushMatrix();
    glTranslatef(x, y, z);

    float red = 0.f;
    float blue = 0.f;
    float green = 0.f;

    glColor3f(red, green, blue);

    // color depends on velocity
    if (velocity > SPHSDK::Config::SpeedTreshold / 2.)
    {
        red = 1.0f;
    }
    else if (velocity > SPHSDK::Config::SpeedTreshold / 4.)
    {
        red = 0.99f;
        green = 0.7f;
    }
    else
    {
        blue = 1.0f;
    }

    glColor3f(red, green, blue);
    // gluSphere(quadric, radius, subdivisions, subdivisions);

    glPopMatrix();
}

void renderSphere_convenient(float x, float y, float z, double radius, double velocity, int subdivisions)
{
    // the same quadric can be re-used for drawing many spheres
    // GLUquadricObj* quadric = gluNewQuadric();
    // gluQuadricNormals(quadric, GLU_SMOOTH);
    // renderSphere(x, y, z, radius, velocity, subdivisions, quadric);
    // gluDeleteQuadric(quadric);
}

void setOrthographicProjection()
{
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    // save previous matrix which contains the
    // settings for the perspective projection
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    // set a 2D orthographic projection
    // gluOrtho2D(0, width, height, 0);

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void MyDisplay(void)
{
    // clock_t t;
    // t = clock();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    // gluLookAt(7.0, 8.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glRotatef(angle, -1, 0, 0);

    sph.run();

    const float cubeSize = static_cast<float>(SPHSDK::Config::CubeSize);

    // Draw the obstacle
    glBegin(GL_TRIANGLES);
    for (const auto& triangle : mesh)
    {
        glColor3f(1.0f / cubeSize, 1.5f * triangle.y / cubeSize, 2.5f * triangle.z / cubeSize);
        glVertex3f(triangle.x, triangle.y, triangle.z);
    }
    glEnd();

    for (auto& particle : sph.particles)
    {
        renderSphere_convenient(static_cast<float>(particle.position.x), static_cast<float>(particle.position.y),
                                static_cast<float>(particle.position.z), particle.radius,
                                particle.velocity.calcNormSqr(), 4);
    }

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);

    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, cubeSize);

    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, cubeSize, 0.f);

    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(cubeSize, 0.f, 0.f);

    glVertex3f(cubeSize, cubeSize, cubeSize);
    glVertex3f(0.f, cubeSize, cubeSize);

    glVertex3f(cubeSize, cubeSize, cubeSize);
    glVertex3f(cubeSize, 0.f, cubeSize);

    glVertex3f(cubeSize, cubeSize, cubeSize);
    glVertex3f(cubeSize, cubeSize, 0.f);

    glVertex3f(cubeSize, 0.f, 0.f);
    glVertex3f(cubeSize, cubeSize, 0.f);

    glVertex3f(0.f, 0.f, cubeSize);
    glVertex3f(cubeSize, 0.f, cubeSize);

    glVertex3f(0.f, 0.f, cubeSize);
    glVertex3f(0.f, cubeSize, cubeSize);

    glVertex3f(0.f, cubeSize, cubeSize);
    glVertex3f(0.f, cubeSize, 0.f);

    glVertex3f(cubeSize, 0.f, cubeSize);
    glVertex3f(cubeSize, 0.f, 0.f);

    glVertex3f(0.f, cubeSize, 0.f);
    glVertex3f(cubeSize, cubeSize, 0.f);
    glEnd();

    setOrthographicProjection();
    resetPerspectiveProjection();

    glFlush();
}

void updateGravity()
{
    //   |1     0           0| |x|   |        x        |   |x'|
    //   |0   cos θ    −sin θ| |y| = |y cos θ − z sin θ| = |y'|
    //   |0   sin θ     cos θ| |z|   |y sin θ + z cos θ|   |z'|
    SPHSDK::Config::GravitationalAcceleration =
        SPHAlgorithms::Point3D(SPHSDK::Config::InitialGravitationalAcceleration.x,
                               SPHSDK::Config::InitialGravitationalAcceleration.y * cos(angle / 180 * M_PI) -
                                   SPHSDK::Config::InitialGravitationalAcceleration.z * sin(angle / 180 * M_PI),
                               SPHSDK::Config::InitialGravitationalAcceleration.y * sin(angle / 180 * M_PI) +
                                   SPHSDK::Config::InitialGravitationalAcceleration.z * cos(angle / 180 * M_PI));
}

void resize_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    aspect_ratio = height ? width / (float) height : 1.f;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
        case GLFW_KEY_UP:
            angle -= 0.5;
            updateGravity();
            break;
        case GLFW_KEY_DOWN:
            angle += 0.5;
            updateGravity();
            break;
        case GLFW_KEY_HOME:
            angle = 360.0;
            SPHSDK::Config::GravitationalAcceleration = SPHAlgorithms::Point3D(0.0, 0.0, -9.82);
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
    }
}

void Draw::MainDraw(int argc, char** argv)
{
    static const std::function<float(float, float, float)> obstacle = SPHAlgorithms::Shapes::Pawn;
    sph = SPHSDK::SPH(&obstacle);

    mesh = SPHAlgorithms::MarchingCubes::generateMesh(obstacle);

    // GLFW initialization
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // set up window size
    auto window = glfwCreateWindow(width, height, "SPH model", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetKeyCallback(window, key_callback);

    // Set initial aspect ratio
    glfwGetFramebufferSize(window, &width, &height);
    resize_callback(window, width, height);

    while (!glfwWindowShouldClose(window))
    {
        MyDisplay();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
