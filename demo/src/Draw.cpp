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
static const GLfloat pointSize = 5.f;

static SPHSDK::SPH sph;

static SPHAlgorithms::Point3FVector mesh;

struct SVertex
{
    GLfloat x,y,z;
    GLfloat r,g,b;
};

// TODO: optimize this, do not copy arrays to draw
std::vector<SVertex> points(SPHSDK::Config::ParticlesNumber);

void MyDisplay(void)
{
    mat4x4 view;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Setup orthogonal projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0 * aspect_ratio, 3.0 * aspect_ratio, -3.0, 3.0, 1.0, 50.0);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    {
      vec3 eye = { 7.f, 8.f, 5.f };
      vec3 center = { 0.f, 0.f, 0.f };
      vec3 up = { 0.f, 0.f, 1.f };
      mat4x4_look_at(view, eye, center, up);
    }

    glLoadMatrixf((const GLfloat*) view);
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

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glPointSize(pointSize);

    for (size_t i = 0; i < sph.particles.size(); ++i)
    {
        points[i].x = static_cast<GLfloat>(sph.particles[i].position.x);
        points[i].y = static_cast<GLfloat>(sph.particles[i].position.y);
        points[i].z = static_cast<GLfloat>(sph.particles[i].position.z);

        const double velocity = sph.particles[i].velocity.calcNormSqr();
        // color depends on velocity
        if (velocity > SPHSDK::Config::SpeedTreshold / 2.)
        {
            points[i].r = 1.0f;
            points[i].g = 0.0f;
            points[i].b = 0.0f;
        }
        else if (velocity > SPHSDK::Config::SpeedTreshold / 4.)
        {
            points[i].r = 0.99f;
            points[i].g = 0.7f;
            points[i].b = 0.0f;
        }
        else
        {
            points[i].r = 0.0f;
            points[i].g = 0.0f;
            points[i].b = 1.0f;
        }
    }

    glVertexPointer(3, GL_FLOAT, sizeof(SVertex), points.data());
    glColorPointer(3, GL_FLOAT, sizeof(SVertex), &points[0].r);
    glDrawArrays(GL_POINTS, 0, SPHSDK::Config::ParticlesNumber);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

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

    glFlush();
}

void updateGravity()
{
    //   |1     0           0| |x|   |        x        |   |x'|
    //   |0   cos θ    −sin θ| |y| = |y cos θ − z sin θ| = |y'|
    //   |0   sin θ     cos θ| |z|   |y sin θ + z cos θ|   |z'|
    SPHSDK::Config::GravitationalAcceleration =
        SPHAlgorithms::Point3F(SPHSDK::Config::InitialGravitationalAcceleration.x,
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
            SPHSDK::Config::GravitationalAcceleration = SPHAlgorithms::Point3F(0.0, 0.0, -9.82);
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
