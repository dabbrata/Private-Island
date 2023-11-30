//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "sphere.h"

#include "cube.h"
#include "stb_image.h"

#include <iostream>
#include "Sphere2.h"
#include "curve.h"
#include "cylinder.h"
#include<stdlib.h>
#include<windows.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawWindow(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);


void drawTable(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawSofa(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawAlmirah(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawOuterWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawWallTv(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

void drawRelling(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawRelling2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawLamp(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void load_texture2(unsigned int& texture, string image_name, GLenum format, bool repeat);

void door(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color);
void door2(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color);

void dolna(Cube& cube, Cube& cube2, Shader& ourShader, Shader& lightingShader, glm::mat4 als);
void swing(Cube& cube, Cube& cube2, Shader& ourShader, Shader& lightingShader, glm::mat4 als);
void fchair(Cube& cube, Cube& cube2, Shader& lightingShader, glm::mat4 als);
void drawFan(unsigned int VAO, Shader ourShader, glm::mat4 matr, float r);
void drawBoat(Curve& Boat, Cube& cube2, Shader& ourShader, Shader& lightingShader, glm::mat4 als, float angle);


//void drawBookself(unsigned int VAO, Shader ourShader, glm::mat4 matr);
//void drawTable(unsigned int VAO, Shader ourShader, glm::mat4 matr);
//void drawChair(unsigned int VAO, Shader ourShader, glm::mat4 matr);
//void drawCup(unsigned int VAO, Shader ourShader, glm::mat4 matr);
//void drawSofa(unsigned int VAO, Shader ourShader);
//void drawTelevision(unsigned int VAO, Shader ourShader, glm::mat4 matr);
//void drawFan(unsigned int VAO, Shader ourShader, glm::mat4 matr, float r);
//void drawOuterWall(unsigned int VAO, Shader ourShader);
////void drawOuterWall(unsigned int VAO, Shader& lightingShader, Shader ourShader);
//void drawFrame(unsigned int VAO, Shader ourShader, glm::mat4 matr);
//void drawWindow(unsigned int VAO, Shader& ourShader);
//void drawFloor(unsigned int VAO, Shader ourShader, glm::mat4 matr);

//dynamic door
unsigned int texture0, texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

float r = 0.0f;
float r1 = 0.0f;
float r2 = 0.0f;
bool fanOn = false;
bool fanisOn = true;
float angle = 0.0f;
float angleB = 0.0f;
float angle2 = 0.0f;
bool hasWater = false;
float level = -12.0;


float rotationAngle = 0.0f;

float gravity = 9.81f;  // Acceleration due to gravity
float pendulumLength = 1.0f;

// camera
Camera camera(glm::vec3(0.0f, 8.1f, -30.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 0.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(4.0f,  8.3f,  0.0f),
    glm::vec3(-0.5f,  48.5f,  -5.5f),
    glm::vec3(-4.10f,  3.5f,  0.0f),
    glm::vec3(-12.65f,  8.3f,  0.0f),
    //main door upper light
    glm::vec3(-9.0f,  3.7f,  -5.5f),
       
    glm::vec3(-20.0f,  6.2f,  -42.0f),
    glm::vec3(-6.0f,  6.2f,  -42.0f),

    glm::vec3(44.0f,  4.2f,  23.2f),//40.2
    glm::vec3(-44.2f,  4.2f,  23.2f),

    glm::vec3(44.0f,  4.2f,  -41.5f),
    glm::vec3(-44.2f,  4.2f,  -41.5f),
    glm::vec3(-30.5f,  9.2f,  5.0f),
    //for room relling light fixed this loc
    glm::vec3(-0.5f,  8.5f,  -5.5f)
};
PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    20.05f, 20.05f, 20.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);
PointLight pointlight5(

    pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number
);
PointLight pointlight6(

    pointLightPositions[5].x, pointLightPositions[5].y, pointLightPositions[5].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6       // light number
);
PointLight pointlight7(

    pointLightPositions[6].x, pointLightPositions[6].y, pointLightPositions[6].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    7       // light number
);
PointLight pointlight8(

    pointLightPositions[7].x, pointLightPositions[7].y, pointLightPositions[7].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    8       // light number
);
PointLight pointlight9(

    pointLightPositions[8].x, pointLightPositions[8].y, pointLightPositions[8].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    9       // light number
);
PointLight pointlight10(

    pointLightPositions[9].x, pointLightPositions[9].y, pointLightPositions[9].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    10       // light number
);
PointLight pointlight11(

    pointLightPositions[10].x, pointLightPositions[10].y, pointLightPositions[10].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    11       // light number
);
PointLight pointlight12(

    pointLightPositions[11].x, pointLightPositions[11].y, pointLightPositions[11].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    12       // light number
);
PointLight pointlight13(

    pointLightPositions[12].x, pointLightPositions[12].y, pointLightPositions[12].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    13       // light number
);

// light settings
bool pointLightOn = true;
bool pointLightOn1 = false;
bool pointLightOn2 = false;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;

bool dLightOn = false;//true hobe..just off kore rakhsi
bool dAmbientLightOn = true;
bool dDiffuseLightOn = true;
bool dSpecularLightOn = true;

bool sLightOn = true;
bool sAmbientLightOn = true;
bool sDiffuseLightOn = true;
bool sSpecularLightOn = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Private Island", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;  
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    vector<float>Hillvertices = {

        -0.8950, 1.9450, 5.1000,
        -0.8200, 1.8300, 5.1000,
        -0.7650, 1.7300, 5.1000,
        -0.7050, 1.5900, 5.1000,
        -0.6700, 1.4700, 5.1000,
        -0.6400, 1.3550, 5.1000,
        -0.6400, 1.2250, 5.1000,
        -0.6300, 1.1150, 5.1000,
        -0.6300, 1.0250, 5.1000,
        -0.6400, 0.9150, 5.1000,
        -0.6450, 0.8200, 5.1000,
        -0.6550, 0.6950, 5.1000,
        -0.6650, 0.6150, 5.1000,

    };

    vector<float>Pillarvertices = {
        -0.3050, 2.1650, 5.1000,
        -0.3050, 1.9250, 5.1000,
        -0.3000, 1.6900, 5.1000,
        -0.3050, 1.4150, 5.1000,
        -0.3100, 1.1350, 5.1000
    };
    

    vector<float>Groundvertices = {
        
        -1.0100, 1.1200, 5.1000,
        -0.7750, 1.3150, 5.1000,
        -0.4300, 1.4300, 5.1000,
        -0.0100, 1.4350, 5.1000

    };

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    cout << "Press 1 : turn off and on day light" << endl;
    cout << "Press 2 : turn off and on directional light" << endl;
    cout << "Press 3 : turn off and on TV using spot light" << endl;
    cout << "Press 4 : turn off and on day light with only diffusive property" << endl;
    cout << "Press 5,7,8 : turn off and on room's light" << endl;
    cout << "Press 6,9 : turn off and on room's light's others property(specular)" << endl;
    cout << "Press W : Zoom in x direction" << endl;
    cout << "Press S : Zoom out x direction" << endl;
    cout << "Press A : Go to left(camera position)" << endl;
    cout << "Press D : Go to right" << endl;
    cout << "Press L : Fill the swimming pool with water" << endl;
    cout << "Press K : Remove water from the swimming pool" << endl;
    cout << "Press E : Open the main door of the house" << endl;
    cout << "Press F : Fan on/off" << endl;
    cout << "Press R : Close the main door of the house" << endl;
    cout << "Press T : Open the door of the area" << endl;
    cout << "Press Y : Close the door of the area" << endl;
    cout << "Press UP,DOWN,LEFT,RIGHT : Move the boat in the sea" << endl;

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Sphere sphere = Sphere();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    //Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    //all frame
    string diffuseMapPath = "frame.png";
    string specularMapPath = "frame.png";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "frame2.jpg";
    string specularMapPathFrame2 = "frame2.jpg";
    unsigned int diffMapFrame2 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapFrame2 = loadTexture(specularMapPathFrame2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeFrame2 = Cube(diffMapFrame2, specMapFrame2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "frame3.jpg";
    string specularMapPathFrame3 = "frame3.jpg";
    unsigned int diffMapFrame3 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapFrame3 = loadTexture(specularMapPathFrame3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeFrame3 = Cube(diffMapFrame3, specMapFrame3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "frame4.jpg";
    string specularMapPathFrame4 = "frame4.jpg";
    unsigned int diffMapFrame4 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapFrame4 = loadTexture(specularMapPathFrame4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeFrame4 = Cube(diffMapFrame4, specMapFrame4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    //

    diffuseMapPath = "floor.jpg";
    string specularMapPath2 = "floor.jpg";
    unsigned int diffMap2 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "frontwall.png";
    string specularMapPathWall = "frontwall.png";
    unsigned int diffMapWall = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapWall = loadTexture(specularMapPathWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeFrontWall = Cube(diffMapWall, specMapWall, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "wall.png";
    string specularMapPathWall2 = "wall.png";
    unsigned int diffMapWall2 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapWall2 = loadTexture(specularMapPathWall2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeFrontWall2 = Cube(diffMapWall2, specMapWall2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "window.png";
    string specularMapPathWindow = "window.png";
    unsigned int diffMapWindow = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapWindow = loadTexture(specularMapPathWindow.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeFrontWindow = Cube(diffMapWindow, specMapWindow, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "door.jpg";
    string specularMapPathDoor = "door.jpg";
    unsigned int diffMapDoor = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapDoor = loadTexture(specularMapPathDoor.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeFrontDoor = Cube(diffMapDoor, specMapDoor, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //roof relling
    diffuseMapPath = "roofrelling.jpg";
    string specularMapPathRoofRelling = "roofrelling.jpg";
    unsigned int diffMapRoofRelling = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapRoofRelling = loadTexture(specularMapPathRoofRelling.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeRoofRelling = Cube(diffMapRoofRelling, specMapRoofRelling, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //ground bricks..
    diffuseMapPath = "rfield.jpg";
    string specularMapGroundBricks = "rfield.jpg";
    unsigned int diffMapGroundBricks = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapGroundBricks = loadTexture(specularMapGroundBricks.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeGroundBricks = Cube(diffMapGroundBricks, specMapGroundBricks, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //sky
    //ground bricks..
    /*diffuseMapPath = "sky.jpg";
    string specularMapSky = "sky.jpg";
    unsigned int diffMapSky = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapSky = loadTexture(specularMapSky.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeSky = Cube(diffMapSky, specMapSky, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);*/
    //Sphere sphereSky = Sphere(diffMapSky, specMapSky, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "groundbricks.jpg";
    string specularMapGroundBricks2 = "groundbricks.jpg";
    unsigned int diffMapGroundBricks2 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapGroundBricks2 = loadTexture(specularMapGroundBricks2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeGroundBricks2 = Cube(diffMapGroundBricks2, specMapGroundBricks2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //remote field

    diffuseMapPath = "rfield.jpg";
    string specularMapGroundField = "rfield.jpg";
    unsigned int diffMapGroundField = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapGroundField = loadTexture(specularMapGroundField.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube remoteField = Cube(diffMapGroundField, specMapGroundField, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //remote tree
    diffuseMapPath = "wood.jpg";
    string specularMapGroundTree = "wood.jpg";
    unsigned int diffMapGroundTree = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapGroundTree = loadTexture(specularMapGroundTree.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube Wood = Cube(diffMapGroundTree, specMapGroundTree, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //swimming pool

    diffuseMapPath = "tiles.jpg";
    string specularMapGroundTiles = "tiles.jpg";
    unsigned int diffMapGroundTiles = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapGroundTiles = loadTexture(specularMapGroundTiles.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube poolSideTiles = Cube(diffMapGroundTiles, specMapGroundTiles, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "blacktiles.jpg";
    string specularMapGroundBlackTiles = "blacktiles.jpg";
    unsigned int diffMapGroundBlackTiles = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapGroundBlackTiles = loadTexture(specularMapGroundBlackTiles.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube poolSideBlackTiles = Cube(diffMapGroundBlackTiles, specMapGroundBlackTiles, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //side wall

    diffuseMapPath = "sidewall.jpg";
    string specularMapSideWall = "sidewall.jpg";
    unsigned int diffMapSideWall = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapSideWall = loadTexture(specularMapSideWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube sideWall = Cube(diffMapSideWall, specMapSideWall, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //left room wall
    diffuseMapPath = "designwall.jpg";
    string specularMapDesignWall = "designwall.jpg";
    unsigned int diffMapDesignWall = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapDesignWall = loadTexture(specularMapDesignWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube designWall = Cube(diffMapDesignWall, specMapDesignWall, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    load_texture2(texture7, "leftdoor.png", GL_RGBA, true);
    load_texture2(texture6, "rightdoor.png", GL_RGBA, true);

    load_texture2(texture5, "oleftgate.png", GL_RGBA, true);
    load_texture2(texture4, "orightgate.png", GL_RGBA, true);

    //cubelight
    diffuseMapPath = "whiteBackground.png";
    string specularMapLight = "whiteBackground.png";
    unsigned int diffMapLight = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapLight = loadTexture(specularMapLight.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeLight = Cube(diffMapLight, specMapLight, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //board...

    diffuseMapPath = "ballboard.jpg";
    string specularMapBoard = "ballboard.jpg";
    unsigned int diffMapBoard = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapBoard = loadTexture(specularMapBoard.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube ballBoard = Cube(diffMapBoard, specMapBoard, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //ball ground...

    diffuseMapPath = "ballground.jpg";
    string specularMapGround = "ballground.jpg";
    unsigned int diffMapGround = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapGround = loadTexture(specularMapGround.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube ballGround = Cube(diffMapGround, specMapGround, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    //sphere
    string diffuseMapPath22 = "sky.jpg";
    string specularMapPath22 = "sky.jpg";

    unsigned int diffMap22 = loadTexture(diffuseMapPath22.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap22 = loadTexture(specularMapPath22.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Sphere2  planet = Sphere2(1.0f, 144, 72, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap22, specMap22, 0.0f, 0.0f, 1.0f, 1.0f);



    string diffuseMapPath222 = "night.jpg";
    string specularMapPath222 = "night.jpg";

    unsigned int diffMap222 = loadTexture(diffuseMapPath222.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap222 = loadTexture(specularMapPath222.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Sphere2  planet2 = Sphere2(1.0f, 144, 72, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap222, specMap222, 0.0f, 0.0f, 1.0f, 1.0f);


    //gate lamp light
    string diffuseMapPath23 = "whiteBackground.png";
    string specularMapPath23 = "whiteBackground.png";

    unsigned int diffMap23 = loadTexture(diffuseMapPath23.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap23 = loadTexture(specularMapPath23.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Sphere2  lampLight = Sphere2(1.0f, 144, 72, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap23, specMap23, 0.0f, 0.0f, 1.0f, 1.0f);


    //basketball
    string diffuseMapPath24 = "basketball.jpg";
    string specularMapPath24 = "basketball.jpg";

    unsigned int diffMap24 = loadTexture(diffuseMapPath24.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap24 = loadTexture(specularMapPath24.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Sphere2  basketBall = Sphere2(1.0f, 144, 72, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap24, specMap24, 0.0f, 0.0f, 1.0f, 1.0f);


    //water

    diffuseMapPath = "sea.jpg";
    string specularMapSea = "sea.jpg";
    unsigned int diffMapSea = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapSea = loadTexture(specularMapSea.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube seaWater = Cube(diffMapSea, specMapSea, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
   

    //curve hill
    string diffuseMapHill = "whitenet.png";
    string specularMapHill = "whitenet.png";
    unsigned int diffMapHill = loadTexture(diffuseMapHill.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapHill = loadTexture(specularMapHill.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Curve  Hill = Curve(Hillvertices, diffMapHill , specMapHill , 5);

    //curve pillar
    string diffuseMapPillar = "whiteBackground.png";
    string specularMapPillar = "whiteBackground.png";
    unsigned int diffMapPillar = loadTexture(diffuseMapPillar.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapPillar = loadTexture(specularMapPillar.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Curve  Pillar = Curve(Pillarvertices, diffMapPillar, specMapPillar, 5);

    //curve ground

    string diffuseMapGround = "rfield.jpg";
    string specularMapGroundCurve = "rfield.jpg";
    unsigned int diffMapGroundCurve = loadTexture(diffuseMapGround.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapGroundCurve = loadTexture(specularMapGroundCurve.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Curve  Ground = Curve(Groundvertices, diffMapGroundCurve, specMapGroundCurve, 5);

    //curve boat
    string diffuseMapBoat = "container2.png";
    string specularMapBoatCurve = "container2.png";
    unsigned int diffMapBoatCurve = loadTexture(diffuseMapBoat.c_str(), GL_MIRRORED_REPEAT, GL_MIRRORED_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapBoatCurve = loadTexture(specularMapBoatCurve.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Curve  Boat = Curve(Groundvertices, diffMapBoatCurve, specMapBoatCurve, 5);


    //cylinder table
    string diffuseMapCyl = "whiteBackground.png";
    string specularMapCyl = "whiteBackground.png";
    unsigned int diffMapCyl = loadTexture(diffuseMapCyl.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapCyl = loadTexture(specularMapCyl.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cylinder ccyl = Cylinder(diffMapCyl, specMapCyl, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    string diffuseMapCyl2 = "boatmiddle.jpg";
    string specularMapCyl2 = "boatmiddle.jpg";
    unsigned int diffMapCyl2 = loadTexture(diffuseMapCyl2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapCyl2 = loadTexture(specularMapCyl2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cylinder bcyl = Cylinder(diffMapCyl2, specMapCyl2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //boat drawing

    

    //draw window

    /*diffuseMapPath = "sidewall.jpg";
    string specularMapPathWall = "sidewall.jpg";
    unsigned int diffMapWall = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapWall = loadTexture(specularMapPathWall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cubeWall = Cube(diffMapWall, specMapWall, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);*/

    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);
        //point light 5
        pointlight5.setUpPointLight(lightingShader);
        //6
        pointlight6.setUpPointLight(lightingShader);
        //7
        pointlight7.setUpPointLight(lightingShader);
        //8
        pointlight8.setUpPointLight(lightingShader);
        //9
        pointlight9.setUpPointLight(lightingShader);
        //10
        pointlight10.setUpPointLight(lightingShader);
        //11
        pointlight11.setUpPointLight(lightingShader);
        //12
        pointlight12.setUpPointLight(lightingShader);
        //13
        pointlight13.setUpPointLight(lightingShader);
        //for directional light

        lightingShader.setVec3("directionalLight.direction", 0.0f, 1.0f, 0.0f);
        lightingShader.setVec3("directionalLight.ambient", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("directionalLight.diffuse", 0.8f, 0.8f, 0.8f);
        lightingShader.setVec3("directionalLight.specular", 1.0f, 1.0f, 1.0f);
        
        lightingShader.setBool("directionalLightOn", dLightOn);
        lightingShader.setBool("directionalAmbientLightOn", dAmbientLightOn);
        lightingShader.setBool("directionalDiffuseLightOn", dDiffuseLightOn);
        lightingShader.setBool("directionalSpecularLightOn", dSpecularLightOn);
        

        lightingShader.setVec3("spotLight.position", -2.0, 1, -0.5);
        lightingShader.setVec3("spotLight.direction", 0, -1, 0);
        lightingShader.setVec3("spotLight.ambient", .2, .2, .2);
        lightingShader.setVec3("spotLight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotLight.k_c", 1.0f);
        lightingShader.setFloat("spotLight.k_l", 0.09);
        lightingShader.setFloat("spotLight.k_q", 0.032);
        lightingShader.setFloat("cos_theta", glm::cos(glm::radians(0.005f)));

        lightingShader.setBool("spotLightOn", sLightOn);
        lightingShader.setBool("spotAmbientLightOn", sAmbientLightOn);
        lightingShader.setBool("spotDiffuseLightOn", sDiffuseLightOn);
        lightingShader.setBool("spotSpecularLightOn", sSpecularLightOn);

        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);



        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);

        //previous............................................................


        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        bed(cubeVAO, lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.3, 0.4, -0.5));
        drawTable(cubeVAO, lightingShader, model*translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5, 0.4, -1.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        drawSofa(cubeVAO, lightingShader, model*translateMatrix*rotateYMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5, 0.0, 0.0));
        drawAlmirah(cubeVAO, lightingShader, model*translateMatrix);
        drawOuterWall(cubeVAO, lightingShader, model);
        drawWallTv(cubeVAO, lightingShader, model);
        drawWindow(cubeVAO, lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-12.5, 0.0, 50.0));
        drawLamp(cubeVAO, lightingShader, model*translateMatrix);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-12.5, 0.0,23.0));
        drawLamp(cubeVAO, lightingShader, model* translateMatrix);

        //for boat
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.4f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0, 0.0, -5.0));
        drawLamp(cubeVAO, lightingShader, model * translateMatrix* scaleMatrix);

        //fan on roof

   
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 0.0f, 1.0f));
        drawFan(cubeVAO, lightingShader, rotateZMatrix, r);
        /*rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r+90), glm::vec3(0.0f, 1.0f, 0.0f));
        drawFan(VAO, ourShader, rotateYMatrix);*/
        if (fanisOn)
        {
            r += 2.0;
        }

        drawFan(cubeVAO, lightingShader, identityMatrix*rotateZMatrix, r);
      




        //second floor
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5, 5.1, 3.5));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        drawSofa(cubeVAO, lightingShader, model* translateMatrix* rotateYMatrix*scaleMatrix);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5, 5.1, -1.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        drawSofa(cubeVAO, lightingShader, model* translateMatrix* rotateYMatrix* scaleMatrix);
        
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, 5.1, 0.2));
        drawTable(cubeVAO, lightingShader, model* translateMatrix* scaleMatrix);
        

        /*glm::mat4 modelForSphere = glm::mat4(1.0f);
        modelForSphere = glm::translate(model, glm::vec3(-0.5f, -0.2f, 0.98f)) * glm::scale(model, glm::vec3(70.0f, 70.0f, 70.0f));
        sphere.drawSphere(lightingShader, modelForSphere);*/

        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 13; i++)
        {
            //if (i % 2 != 0)continue;
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));

     
   
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);


        
        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        // point light 5
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        //6
        pointlight6.setUpPointLight(lightingShaderWithTexture);
        //7
        pointlight7.setUpPointLight(lightingShaderWithTexture);
        //8
        pointlight8.setUpPointLight(lightingShaderWithTexture);
        //9
        pointlight9.setUpPointLight(lightingShaderWithTexture);
        //10
        pointlight10.setUpPointLight(lightingShaderWithTexture);
        //11
        pointlight11.setUpPointLight(lightingShaderWithTexture);
        //12
        pointlight12.setUpPointLight(lightingShaderWithTexture);
        //13
        pointlight13.setUpPointLight(lightingShaderWithTexture);
        //frame
        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.8f, 0.08f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 3.8f, 42.0f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //second floor frame
        modelMatrixForContainer = glm::mat4(1.0f);
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 1.8f, 0.08f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 3.5f, 42.0f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //second floor left room left wall
      
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 4.5f, 8.5f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(84.0f, 0.99f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        designWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);
       /* scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 8.5f));
        translate = glm::translate(model, glm::vec3(84.0f, 0.99f, -0.59f));
        model = alTogether * scale * translate;*/

        //2nd floor right room frame
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.8f, 0.08f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0f, 7.8f, 42.0f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.8f, 0.08f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5f, 7.8f, 42.0f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeFrame2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.8f, 0.08f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5f, 9.2f, 42.0f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeFrame3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.8f, 0.08f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0f, 9.2f, 42.0f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeFrame4.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.5f, 0.01f, 8.5f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //second floor floor
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.5f, 0.01f, 10.5f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.55f, 445.0f, -.67f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);
        //front wall second floor

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.5f, 4.5f, 0.05f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.55f, 1.0f, -100.97f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeFrontWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);
        //
        
        //roof room

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.5f, 3.5f, 4.05f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.85f, 2.6f, -0.97f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeFrontWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15.6, 17.4, 25.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.55f, 0.5f, 0.5f));
        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        drawRelling(cubeVAO, lightingShader, model*translateMatrix * scaleMatrix);

        //ground front wall
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.5f, 4.5f, 0.05f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.55f, 0.0f, -100.97f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeFrontWall2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //frond wall second floor Door

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 2.5f, 0.1f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.75f, 0.01f, -50.97f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeFrontDoor.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        
        

        //window

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 2.0f, 0.1f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.25f, 0.6f, -50.97f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeFrontWindow.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //draw relling
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.0, -25.0, 28.0));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.55f, 0.5f, 0.5f));
        drawRelling(cubeVAO, lightingShader, model*translateMatrix);

        //draw belconi relling

        //draw relling
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-28.0, -25.0, 28.0));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.55f, 0.5f, 0.5f));
        drawRelling2(cubeVAO, lightingShader, model* translateMatrix);

        //right room floor

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.5f, 0.01f, 8.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.68f, 445.0f,-1.30f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.5f, 0.01f, 8.6f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.34f, 0.0f, -.58f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.5f, 0.01f, 8.7f));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.0, 0.0, 28.0));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        //modelMatrixForContainer = scaleMatrix * translateMatrix;
        //cube2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //roof relling
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(17.0f, 1.5f, 0.3f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.75f, 6.0f, -17.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeRoofRelling.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        ////right
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 1.5f, 16.5f));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.75f, 6.0f, -17.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        //modelMatrixForContainer = scaleMatrix * translateMatrix;
        //cubeRoofRelling.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        //sky......outer area....
        glm::mat4 modelForSphereE = glm::mat4(1.0f);
        modelForSphereE = glm::translate(model, glm::vec3(-0.5f, -0.2f, 0.98f)) * glm::scale(model, glm::vec3(1870.0f, 1270.0f, 1870.0f));
        planet.drawSphereWithTexture(lightingShaderWithTexture, modelForSphereE);
        
        
        

        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(100.0f, 100.0f, 80.0f));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, -0.2f, -0.58f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        //modelMatrixForContainer = scaleMatrix * translateMatrix;
        //cubeSky.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //ground grass
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.01f, 30.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.50f, -22.7f, -.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeGroundBricks.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.01f, 30.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.50f, -22.7f, -.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeGroundBricks.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.01f, 30.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.50f, -22.7f, -.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeGroundBricks.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //side pool grass

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(40.0f, 0.01f, 30.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.14f, -22.7f, -1.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeGroundBricks.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(40.0f, 0.01f, 30.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.12f, -22.7f, -1.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeGroundBricks.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(45.0f, 0.01f, 30.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, -22.715f, -2.12f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeGroundBricks.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        

        //remote grass

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.01f, 30.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.50f, -22.7f, 0.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        remoteField.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.01f, 30.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.50f, -22.7f, .5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        remoteField.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0f, 0.01f, 30.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.50f, -22.7f, .5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        remoteField.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //remote Tree

        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(90.0f, 12.01f, 0.1f));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.50f, -0.07f, 400.5f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        //modelMatrixForContainer = scaleMatrix * translateMatrix;
        //remoteTree.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);
        

        //ground bricks2
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(25.5f, 0.2f, 24.7f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.60f, -1.7f, -.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeGroundBricks2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.5f, 0.2f, 25.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.78f, -1.7f, -1.492f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //swimming pool

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 5.2f, 17.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, -1.02f, -1.95f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 5.2f, 17.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.78f, -1.02f, -1.95f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.3f, 5.2f, 1.4f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.545f, -1.02f, -24.65f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //front pool side bar

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.3f, 5.2f, 1.4f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.545f, -1.02f, -11.7f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.3f, 4.2f, 1.9f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.545f, -1.15f, -9.6f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.5f, 0.1f, 1.9f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.558f, -6.2f, -9.6f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideBlackTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //bottom wall

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.3f, 0.2f, 17.4f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.545f, -20.02f, -1.9f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //siri pool
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.3f, 5.2f, 1.4f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, -1.2f, -14.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.3f, 5.2f, 1.4f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, -1.35f, -15.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.3f, 5.2f, 1.4f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.0f, -1.5f, -16.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //siripool front building

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.4f, 4.0f, 1.4f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.7f, -0.82f, -4.6f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.4f, 4.0f, 1.4f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.7f, -0.9f, -5.6f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.4f, 5.2f, 1.4f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.7f, -0.98f, -6.6f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        //siri inside room
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 5.2f, 4.3f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.5f, -0.14f, -0.2f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 5.2f, 4.3f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-7.5f, -0.29f, -0.2f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 5.2f, 4.3f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.5f, -0.44f, -0.2f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 5.2f, 4.3f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.5f, -0.59f, -0.2f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 5.2f, 4.3f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5f, -0.74f, -0.2f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 5.2f, 4.3f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.5f, -0.89f, -0.2f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        poolSideTiles.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        //side area wall

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(90.0f, 4.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.50f, -0.07f, 23.0f)); //40
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        sideWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 4.0f, 65.5f));//85
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-45.0f, -0.07f, -0.63f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        sideWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 4.0f, 65.5f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(44.0f, -0.07f, -0.63f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        sideWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //front 2 separate wall
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(25.0f, 4.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.8f, -0.07f, -42.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        sideWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(50.0f, 4.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.1f, -0.07f, -42.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        sideWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //front gate

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 6.0f, 3.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.5f, -0.07f, -14.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        sideWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 6.0f, 3.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.5f, -0.07f, -14.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        sideWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-32.2f, 0.4f, -48.5));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 1.4f, 1.0f));
        glActiveTexture(GL_TEXTURE0);
        glm::vec4 color2 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        door2(lightingShaderWithTexture, translateMatrix* scaleMatrix, color2);

        /*scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.5f, 4.5f, 0.05f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, -0.01f, 70.0f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeWall.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);*/

        //dynamic door
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-14.0f, 0.5f, -11.15));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 1.0f, 0.8f));

        glActiveTexture(GL_TEXTURE0);
        glm::vec4 color1 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
 
        //glBindTexture(GL_TEXTURE_2D, texture7);
        door(lightingShaderWithTexture, translateMatrix* scaleMatrix, color1);


        //light with sphere
        glm::mat4 modelForSphere2 = glm::mat4(1.0f);
        modelForSphere2 = glm::translate(model, glm::vec3(-27.0f, -19.0f, -177.0f)) * glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
        lampLight.drawSphereWithTexture(lightingShaderWithTexture, modelForSphere2);

        glm::mat4 modelForSphere3 = glm::mat4(1.0f);
        modelForSphere3 = glm::translate(model, glm::vec3(-97.0f, -19.0f, -177.0f)) * glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
        lampLight.drawSphereWithTexture(lightingShaderWithTexture, modelForSphere3);

        //light cube
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-31.0f, 8.8f, 4.7f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeLight.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-31.0f, 8.8f, -21.1f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        cubeLight.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //ball board
        
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 3.0f, 0.2f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.6f, 1.8f, 27.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        ballBoard.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 3.0f, 0.2f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.6f, 1.8f, -105.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        ballBoard.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);
        

        // wall sphere
        glm::mat4 modelForSphere4 = glm::mat4(1.0f);
        modelForSphere4 = glm::translate(model, glm::vec3(-217.0f, -28.3f, -175.0f)) * glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
        lampLight.drawSphereWithTexture(lightingShaderWithTexture, modelForSphere4);

        glm::mat4 modelForSphere5 = glm::mat4(1.0f);
        modelForSphere5 = glm::translate(model, glm::vec3(222.0f, -28.3f, -175.0f)) * glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
        lampLight.drawSphereWithTexture(lightingShaderWithTexture, modelForSphere5);

        glm::mat4 modelForSphere6 = glm::mat4(1.0f);
        modelForSphere6 = glm::translate(model, glm::vec3(-217.0f, -28.3f, 150.0f)) * glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f)); //235
        lampLight.drawSphereWithTexture(lightingShaderWithTexture, modelForSphere6);

        glm::mat4 modelForSphere7 = glm::mat4(1.0f);
        modelForSphere7 = glm::translate(model, glm::vec3(222.0f, -28.3f, 150.0f)) * glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f)); //235
        lampLight.drawSphereWithTexture(lightingShaderWithTexture, modelForSphere7);

        //basket ball spehere

        glm::mat4 modelForSphereBall = glm::mat4(1.0f);
        modelForSphereBall = glm::translate(model, glm::vec3(-150.0f, -47.0f, -6.5f)) * glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
        basketBall.drawSphereWithTexture(lightingShaderWithTexture, modelForSphereBall);

        //basket ball ground

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(14.0f, 1.0f, 26.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.7f, -1.0f, -0.8f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        ballGround.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //ball net using curve
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-30.5f, 4.5f, 4.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        Hill.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-30.5f, 4.5f, -19.9f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        Hill.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

        //pillar
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 5.0f, 0.8f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.5f, -1.29f, -12.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        Pillar.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 5.0f, 0.8f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-13.5f, -1.29f, -12.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        Pillar.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

        //ground curve

        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.8f, 6.0f, 5.8f));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.5f, -1.29f, -9.5f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        //modelMatrixForContainer = scaleMatrix * translateMatrix;
        //Ground.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.8f, 6.0f, 5.8f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.5f, -1.29f, -9.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        Ground.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.8f, 6.0f, 5.8f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, -1.29f, -9.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        Ground.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.8f, 6.0f, 5.8f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, -1.29f, -10.0f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        Ground.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

  

        //dolna dynamic movement
        
        float time = glfwGetTime();
        float theta = glm::radians(30.0f) * std::sin(std::sqrt(gravity / pendulumLength) * time);

        glm::mat4 rotateMatrix, modelMatrix;

        rotateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.7f, 0.0f)) *
            glm::rotate(identityMatrix, theta, glm::vec3(0.0f, 0.0, 1.0f)) *
            glm::translate(identityMatrix, glm::vec3(0.0f, -1.7f, 0.0f));

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 3.0f, 3.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, -0.25, -7.0));
        model = scaleMatrix * identityMatrix * translateMatrix;
        swing(cubeLight, cube2, ourShader, lightingShaderWithTexture, model * rotateYMatrix);
        modelMatrix = scaleMatrix * translateMatrix * rotateMatrix;
        dolna(cubeLight, cube2, ourShader, lightingShaderWithTexture, modelMatrix * rotateYMatrix);

        // dynamic air calc



        //outer chair table 

        translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0, -0.25, -28.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0, 3.0, 3.0));
        model = translateMatrix * scaleMatrix;
        fchair(cube2, cubeLight, lightingShaderWithTexture, model);


        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(22.0, -0.25, -25.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0, 3.0, 3.0));
        model = translateMatrix * scaleMatrix;
        fchair(cube2, cubeLight, lightingShaderWithTexture, model * rotateYMatrix);


        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(24.0, -0.25, -28.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0, 3.0, 3.0));
        model = translateMatrix * scaleMatrix;
        fchair(cube2, cubeLight, lightingShaderWithTexture, model*rotateYMatrix);


        //cylinder

        //table

        translateMatrix = glm::translate(identityMatrix, glm::vec3(22.0, 1.2, -27.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 1.25, 0.2));
        model = translateMatrix * scaleMatrix;
        ccyl.drawCylinderWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(22.0, 0.1, -27.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.25, 0.5));
        model = translateMatrix * scaleMatrix;
        ccyl.drawCylinderWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(22.0, 2.5, -27.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 0.25, 1.5));
        model = translateMatrix * scaleMatrix;
        ccyl.drawCylinderWithTexture(lightingShaderWithTexture, model);

        //for air fan on roof cylinder

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.0, 11.0, -2.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 1.5, 0.1));
        model = translateMatrix * scaleMatrix;
        ccyl.drawCylinderWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.0, 12.5, -2.2));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 0.2, 0.1));
        model = translateMatrix * scaleMatrix;
        bcyl.drawCylinderWithTexture(lightingShaderWithTexture, model);


        //sea water
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(45.8f, 0.4f, 25.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, -1.0f, -3.2f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        seaWater.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(45.8f, 0.4f, 35.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.47f, -1.5f, -2.2f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        seaWater.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(45.8f, 0.4f, 35.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.47f, -1.5f, -2.2f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        seaWater.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //right side water
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(20.8f, 0.4f, 90.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.15f, -1.5f, -0.50f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        seaWater.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //left side water
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(20.8f, 0.4f, 90.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.15f, -1.5f, -0.50f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        seaWater.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //backside water
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(130.8f, 0.4f, 25.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, -1.5f, 1.5f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        seaWater.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        //pool water

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.1f, 0.4f, 15.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.55f, level, -2.22f));
        //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        modelMatrixForContainer = scaleMatrix * translateMatrix;
        seaWater.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //dynamic board drawing...

        

        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.8f, 4.5f, 2.0f));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.6f, 1.4f, -25.0f));
        //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        ////modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
        //modelMatrixForContainer = scaleMatrix * translateMatrix * rotateZMatrix;
        //Boat.draw(lightingShaderWithTexture, modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

        translateMatrix = glm::translate(identityMatrix, glm::vec3(r1, 0.0f, r2));
        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(angleB), glm::vec3(0.0f, 1.0f, 0.0f));
        model = identityMatrix*translateMatrix;
        drawBoat(Boat, Wood, ourShader, lightingShaderWithTexture, model,angleB);
             
        
             
        /*translateMatrix = glm::translate(identityMatrix, glm::vec3(-28.5f, 0.7f, -50.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.5, 0.25, 1.5));
        model = translateMatrix * scaleMatrix;
        bcyl.drawCylinderWithTexture(lightingShaderWithTexture, model);*/

        

        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 0.8;
    float blanketLength = 0.7;
    float headHeight = 0.6;

    //base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //foam
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight, 0));
    scale = glm::scale(model, glm::vec3(width, 0.06, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);

    //pillow 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((width / 2) - (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //pillow 2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((-width / 2) + (0.1 + pillowWidth / 2), baseHeight + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //blanket
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight + 1 * 0.06, -(length / 2 - 0.025) + blanketLength / 2));
    scale = glm::scale(model, glm::vec3(blanketWidth, 0.015, blanketLength));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886);

    //head
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

}

//previous draw furniture...all functions.............................



void drawTable(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    //glm::mat4 model = glm::mat4(1.0f);
    //glm::mat4 translate = glm::mat4(1.0f);
    //glm::mat4 translate2 = glm::mat4(1.0f);
    //glm::mat4 scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(0.6f, 0.10f, 1.2f));
    //translate = glm::translate(model, glm::vec3(0.4, 0.4, 0.8));
    //model = alTogether * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.0, 0.1, 0.375);

    ////leg

    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(0.10, -0.5, 0.10));
    //translate = glm::translate(model, glm::vec3(3.5, -0.2, 10.5));
    //model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(0.10, -0.5, 0.10));
    //translate = glm::translate(model, glm::vec3(3.5, -0.2, 19.5));
    //model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(0.10, -0.5, 0.10));
    //translate = glm::translate(model, glm::vec3(7.0, -0.2, 19.5));
    //model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(0.10, -0.5, 0.10));
    //translate = glm::translate(model, glm::vec3(7.0, -0.2, 10.5));
    //model = alTogether * translate2 * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);


    float rotateAngle_Y = 0.0;


    glm::mat4 rotateY = glm::mat4(1.0f);
    glm::mat4 rotateZ = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //base
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.2, 0.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 0.12, 0.3));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.188, 0.137, 0.329); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);

    }

    //leg
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, -0.45, 0.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.7, 0.05));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.15, 0.376, 0.18); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);

    }

    //bottom base
    for (float i = 0.0f; i < 360.0f; i += 2.50f) {
        //Center

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, -0.45, 0.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y + i), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.08, 0.1, 0.08));
        model = alTogether * translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.145, 0.176, 0.18); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
        //glBindVertexArray(VAO);

    }

    ////leg 1
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.125, 0.2, 0.0));
    ////rotateZMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, -0.60, 0.1));
    //model = alTogether * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.145, 0.176, 0.18);

}


void drawSofa(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    /*glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.65f, 0.10f, 1.6f));
    translate = glm::translate(model, glm::vec3(2.0, 0.4, 0.8));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.10, 0.7, 1.6));
    translate = glm::translate(model, glm::vec3(18.5, 0.20, 0.797));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.10, 0.40, 1.6));
    translate = glm::translate(model, glm::vec3(18.5, -0.86, 0.797));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.10, 0.45, 1.6));
    translate = glm::translate(model, glm::vec3(12.0, -0.680, 0.797));
    model = alTogether * translate2 * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);*/

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;


    //Sofa Seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 - 0.15, 0.875));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .125f, 0.55f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.941f, 0.443f, 0.176f);

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.1 - 0.5 * 0.2, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .5f, 0.1f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.941f, 0.443f, 0.176f);

    //frame
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05 - 0.1, -0.25, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.15f, .25f, 0.7f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f);

    //Sofa leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, -0.25, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.2f, 0.05f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f);

    //Sofa leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, -0.25, 0.8 + 0.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.2f, 0.05f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f);

    //Sofa leg2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.05 - 0.25, -0.25, 0.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.2f, 0.05f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f);

    //Sofa leg4
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.05 - 0.025, -0.25, 0.8 + 0.5 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.2f, 0.05f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f);

    //handle1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05 - 0.1, -0.15, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.125f, .3f, 0.7f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f);

    //handle2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.1 + 0.025, -0.15, 0.72));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.125f, .3f, 0.7f));
    model = alTogether * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.05, 0.1f, 0.125f);

}

void drawAlmirah(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.85f, 1.8f, 0.6f));
    translate = glm::translate(model, glm::vec3(-0.5, 0.0, 3.8));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.41f, 1.8f, 0.03f));
    translate = glm::translate(model, glm::vec3(0.05, 0.0, 75.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.245, 0.171, 0.175);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.41f, 1.8f, 0.03f));
    translate = glm::translate(model, glm::vec3(-1.05, 0.0, 75.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.245, 0.171, 0.175);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 0.2f, 0.05f));
    translate = glm::translate(model, glm::vec3(0.8, 5.4, 44.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0245, 0.0171, 0.0175);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 0.2f, 0.05f));
    translate = glm::translate(model, glm::vec3(-1.8, 5.4, 44.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0245, 0.0171, 0.0175);

}

void drawWallTv(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.1f, 0.8f, 1.6f));
    translate = glm::translate(model, glm::vec3(-42.4, 1.8, -1.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 0.72f, 1.5f));
    translate = glm::translate(model, glm::vec3(-82.8, 2.05, -1.05));
    model = alTogether * scale * translate;
    float r = 1.0, g = 1.0 , b = 1.0;
    if (!sLightOn) {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }
    drawCube(cubeVAO, lightingShader, model, r, g, b);
}

void drawWindow(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.8f, 1.2f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.5, 1.0, 68.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.667, 0.596, 0.8);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(2.0f, 1.4f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.5, 0.78, 69.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.106, 0.063, 0.18);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.15f, 1.3f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.3, 0.9, 67.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.106, 0.063, 0.18);

    /*model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.5f, 0.72f, 0.05f));
    translate = glm::translate(model, glm::vec3(-62.8, 2.05, -1.05));
    model = alTogether * scale * translate;*/
    float r = 1.0, g = 1.0, b = 1.0;
    /*if (!sLightOn) {
        r = 0.0;
        g = 0.0;
        b = 0.0;
    }*/
    drawCube(cubeVAO, lightingShader, model, r, g, b);
}


void drawOuterWall(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 4.5f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.5f, -0.01f, 70.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 8.5f));
    translate = glm::translate(model, glm::vec3(84.0f, -0.01f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 6.5f));
    translate = glm::translate(model, glm::vec3(-85.0f, -0.01f, -0.45f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 1.8f, 2.5f));
    translate = glm::translate(model, glm::vec3(-85.0f, 1.45f, -2.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


    //ceil of the room..

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 0.05f, 8.5f));
    translate = glm::translate(model, glm::vec3(-0.5f, 88.0f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //second floor

    //outer wall

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 4.5f, 0.05f));
    translate = glm::translate(model, glm::vec3(-0.5f, 0.99f, 70.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.45);

    /*model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 8.5f));
    translate = glm::translate(model, glm::vec3(84.0f, 0.99f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.75);*/

    /*model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 4.5f, 8.5f));
    translate = glm::translate(model, glm::vec3(-85.0f, 0.99f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.75);*/

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(17.0f, 0.05f, 8.5f));
    translate = glm::translate(model, glm::vec3(-0.75f, 179.0f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.05f, 9.0f, 8.5f));
    translate = glm::translate(model, glm::vec3(-255.0f, -0.0f, -0.59f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.9, 0.9, 0.75);


    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(8.5f, 9.0f, 0.05f));
    translate = glm::translate(model, glm::vec3(-1.5f, 0.0f, 70.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.45);

    //front wall main door

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(2.2f, 4.4f, 0.2f));
    translate = glm::translate(model, glm::vec3(-3.35f, 0.0f, -25.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.45);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(2.2f, 4.4f, 0.2f));
    translate = glm::translate(model, glm::vec3(-5.75f, 0.0f, -25.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.45);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(3.1f, 1.2f, 0.2f));
    translate = glm::translate(model, glm::vec3(-3.377f, 2.7f, -25.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.7, 0.7, 0.45);



    //floor of the room..

    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(8.5f, 0.01f, 8.5f));
    //translate = glm::translate(model, glm::vec3(-0.5f, -5.0f, -0.59f));
    //model = alTogether * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.0, 0.0, 0.0);


    //for (int i = 0; i <= 16; i++) {
    //    if (i % 2 == 0) {
    //        for (int j = 0; j < 16; j++) {
    //            
    //            if (j % 2 == 0) {
    //                //ourShader.setVec4("color", glm::vec4(0.82f, 0.698f, 0.576f, 1.0f));
    //                model = glm::mat4(1.0f);
    //                translate = glm::mat4(1.0f);
    //                translate2 = glm::mat4(1.0f);
    //                scale = glm::mat4(1.0f);
    //                scale = glm::scale(model, glm::vec3(0.475f, 0.01f, 0.5f));
    //                translate = glm::translate(model, glm::vec3((-8.9 + 1.05 * i), -4.0f, (-10.0 + 1.05 * j)));
    //                model = alTogether * scale * translate;
    //                drawCube(cubeVAO, lightingShader, model, 0.839, 0.725, 0.725);
    //                //ourShader.setVec4("color", glm::vec4(0.839f, 0.725f, 0.725f, 1.0f));
    //            }
    //            else {
    //                //ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    //                model = glm::mat4(1.0f);
    //                translate = glm::mat4(1.0f);
    //                translate2 = glm::mat4(1.0f);
    //                scale = glm::mat4(1.0f);
    //                scale = glm::scale(model, glm::vec3(0.475f, 0.01f, 0.5f));
    //                translate = glm::translate(model, glm::vec3((-8.9 + 1.05 * i), -4.0f, (-10.0 + 1.05 * j)));
    //                model = alTogether * scale * translate;
    //                drawCube(cubeVAO, lightingShader, model, 0.439, 0.384, 0.384);
    //            }
    //            //ourShader.setVec4("color", glm::vec4(0.894f, 0.902f, 0.906f, 1.0f));

    //           
    //        }
    //    }
    //    else {

    //        for (int j = 0; j < 16; j++) {

    //            if (j % 2 != 0) {
    //                //ourShader.setVec4("color", glm::vec4(0.82f, 0.698f, 0.576f, 1.0f));
    //                model = glm::mat4(1.0f);
    //                translate = glm::mat4(1.0f);
    //                translate2 = glm::mat4(1.0f);
    //                scale = glm::mat4(1.0f);
    //                scale = glm::scale(model, glm::vec3(0.475f, 0.01f, 0.5f));
    //                translate = glm::translate(model, glm::vec3((-8.9 + 1.05 * i), -4.0f, (-10.0 + 1.05 * j)));
    //                model = alTogether * scale * translate;
    //                drawCube(cubeVAO, lightingShader, model, 0.839, 0.725, 0.725);
    //                //ourShader.setVec4("color", glm::vec4(0.839f, 0.725f, 0.725f, 1.0f));
    //            }
    //            else {
    //                //ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    //                model = glm::mat4(1.0f);
    //                translate = glm::mat4(1.0f);
    //                translate2 = glm::mat4(1.0f);
    //                scale = glm::mat4(1.0f);
    //                scale = glm::scale(model, glm::vec3(0.475f, 0.01f, 0.5f));
    //                translate = glm::translate(model, glm::vec3((-8.9 + 1.05 * i), -4.0f, (-10.0 + 1.05 * j)));
    //                model = alTogether * scale * translate;
    //                drawCube(cubeVAO, lightingShader, model, 0.439, 0.384, 0.384);
    //            }
    //            //ourShader.setVec4("color", glm::vec4(0.894f, 0.902f, 0.906f, 1.0f));

    //            
    //        }

    //    }
    //}



}


void drawRelling(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 4.5f, 10.5f));
    translate = glm::translate(model, glm::vec3(-9.0f, 1.1f, -3.40f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 4.5f, 10.5f));
    translate = glm::translate(model, glm::vec3(81.0f, 1.1f, -3.35f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    glm::mat4 rotateYMatrix = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scale = glm::scale(model, glm::vec3(45.0f, 4.5f, 0.5f));
    translate = glm::translate(model, glm::vec3(-0.1f, 1.1f, -70.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 1.0, 1.0, 1.0);

}

void drawRelling2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-3.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-8.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-13.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-18.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-23.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-23.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-28.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-33.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-38.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-43.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-48.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-53.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    /*model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 4.5f, 10.5f));
    translate = glm::translate(model, glm::vec3(81.0f, 1.1f, -3.35f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);*/

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    glm::mat4 rotateYMatrix = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scale = glm::scale(model, glm::vec3(30.0f, 0.5f, 0.5f));
    translate = glm::translate(model, glm::vec3(-0.95f, 25.0f, -100.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    //side relling

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotateYMatrix = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scale = glm::scale(model, glm::vec3(0.5f, 0.5f, 25.0f));
    translate = glm::translate(model, glm::vec3(-58.0f, 25.0f, -2.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -95.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -90.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -85.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -80.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -75.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -70.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -65.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -60.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -55.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(-58.0f, 0.60f, -50.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    //side relling left

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    rotateYMatrix = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scale = glm::scale(model, glm::vec3(0.5f, 0.5f, 25.0f));
    translate = glm::translate(model, glm::vec3(2.0f, 25.0f, -2.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -95.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -90.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -85.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -80.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -75.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -70.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -65.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -60.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -55.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 8.0f, 0.5f));
    translate = glm::translate(model, glm::vec3(2.0f, 0.60f, -50.0f));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.129, 0.031, 0.161);


}

void drawLamp(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether) {

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.3f, 10.5f, 0.3f));
    translate = glm::translate(model, glm::vec3(-60.5, -0.01, -148.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.1, 0.0, 0.1);

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(1.5f, 0.5f, 1.5f));
    translate = glm::translate(model, glm::vec3(-12.5, -1.0, -30.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.667, 0.596, 0.8);

    //model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(0.15f, 1.3f, 0.05f));
    //translate = glm::translate(model, glm::vec3(-0.3, 0.9, 67.0));
    //model = alTogether * scale * translate;
    //drawCube(cubeVAO, lightingShader, model, 0.106, 0.063, 0.18);

    ///*model = glm::mat4(1.0f);
    //translate = glm::mat4(1.0f);
    //translate2 = glm::mat4(1.0f);
    //scale = glm::mat4(1.0f);
    //scale = glm::scale(model, glm::vec3(1.5f, 0.72f, 0.05f));
    //translate = glm::translate(model, glm::vec3(-62.8, 2.05, -1.05));
    //model = alTogether * scale * translate;*/
    //float r = 1.0, g = 1.0, b = 1.0;
    ///*if (!sLightOn) {
    //    r = 0.0;
    //    g = 0.0;
    //    b = 0.0;
    //}*/
    //drawCube(cubeVAO, lightingShader, model, r, g, b);
}




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    /*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }*/
    //if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        level -= 0.4;
        level = max(level, -12);
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        level += 0.4;
        level = min(level, -3);
        
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    //if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    /*if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }*/
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    /*if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }*/
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        if(fanisOn)
            fanisOn = false;
        else
            fanisOn = true;
        
    }
    /*if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }*/
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    /*if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }*/
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }

    /*pointlight2.turnOff();
    pointlight4.turnOff();*/


}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            pointlight1.turnOff();           
            /*pointlight3.turnOff();*/
            pointlight2.turnOff();
            pointlight4.turnOff();
            //pointLightOn1 = false;
            pointLightOn = !pointLightOn;
        }
        else
        {

            pointlight1.turnOn();
            //pointlight3.turnOn();
            pointlight2.turnOn();
            pointlight4.turnOn();
            pointLightOn = !pointLightOn;
            //pointLightOn1 = true;
        }
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            //pointlight1.turnOff();
            pointlight3.turnOff();
            pointlight2.turnOff();
            pointlight4.turnOff();
            //pointLightOn2 = false;
            pointLightOn = !pointLightOn;
        }
        else
        {
            //pointlight1.turnOn();
            pointlight3.turnOn();
            pointlight2.turnOff();
            pointlight4.turnOff();
            //pointLightOn2 = true;
            pointLightOn = !pointLightOn;
        }
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (ambientToggle)
        {
            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {
            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }

    if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (specularToggle)
        {
            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }

    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (dLightOn)
        {
            dLightOn = false;
        }
        else
        {
            dLightOn = true;
        }
    }
    if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        if (dAmbientLightOn)
        {
            dAmbientLightOn = false;
        }
        else
        {
            dAmbientLightOn = true;
        }
    }
    if (key == GLFW_KEY_8 && action == GLFW_PRESS)
    {
        if (dDiffuseLightOn)
        {
            dDiffuseLightOn = false;
        }
        else
        {
            dDiffuseLightOn = true;
        }
    }
    if (key == GLFW_KEY_9 && action == GLFW_PRESS)
    {
        if (dSpecularLightOn)
        {
            dSpecularLightOn = false;
        }
        else
        {
            dSpecularLightOn = true;
        }
    }

    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (sLightOn)
        {
            sLightOn = false;
        }
        else
        {
            sLightOn = true;
        }
    }

    if (key == GLFW_KEY_I && action == GLFW_PRESS)
    {
        if (sAmbientLightOn)
        {
            sAmbientLightOn = false;
        }
        else
        {
            sAmbientLightOn = true;
        }
    }
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        if (sDiffuseLightOn)
        {
            sDiffuseLightOn = false;
        }
        else
        {
            sDiffuseLightOn = true;
        }
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        if (sSpecularLightOn)
        {
            sSpecularLightOn = false;
        }
        else
        {
            sSpecularLightOn = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)                   //Door open-close
    {
        angle -= 2;
        angle = max(angle, -120);

    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)                   //Door open-close
    {
        angle += 2;
        angle = min(angle, 0);

    }

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)                   //Door open-close
    {
        angle2 -= 2;
        angle2 = max(angle2, -120);

    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)                   //Door open-close
    {
        angle2 += 2;
        angle2 = min(angle2, 0);

    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)                   //Door open-close
    {
        r1 -= 1;
        r1 = max(r1, -30.0);

    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)                   //Door open-close
    {
        r1 += 1;
        r1 = min(r1, 0.0);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)                   //Door open-close
    {
        //angleB += 2;
        
        r2 += 1;
        //r2 = max(r1, -30.0);

    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)                   //Door open-close
    {
        //angleB -= 2;
        r2 -= 1;
        //r2 = min(r1, 0.0);
        

    }



    

   
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void load_texture2(unsigned int& texture, string image_name, GLenum format, bool repeat)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (repeat) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(image_name.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture " << image_name << endl;
    }
    stbi_image_free(data);
}


//void door(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color)
//{
//    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;
//
//    glBindTexture(GL_TEXTURE_2D, texture7);
//    //Left Side
//    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.98f, -0.42f, 7.6f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.2f, 3.2f, 0.2f));
//    model = translateMatrix * rotateYMatrix * scaleMatrix;
//    ourShader.setMat4("model", moveMatrix * model);
//    ourShader.setVec4("material.ambient", color);
//    ourShader.setVec4("material.diffuse", color);
//    ourShader.setVec4("material.specular", color * 0.5f);
//    ourShader.setFloat("material.shininess", 32.0f);
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//    glBindTexture(GL_TEXTURE_2D, texture7);
//    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(7.1f, -0.42f, 7.5f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 3.2f, 0.2f));
//    model = translateMatrix * scaleMatrix;*/
//    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-angle + 180), glm::vec3(0.0f, 1.0f, 0.0f));
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(8.42f, -0.42f, 7.8f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.2f, 3.2f, 0.2f));
//    model = translateMatrix * rotateYMatrix * scaleMatrix;
//    ourShader.setMat4("model", moveMatrix * model);
//    ourShader.setVec4("material.ambient", color);
//    ourShader.setVec4("material.diffuse", color);
//    ourShader.setVec4("material.specular", color * 0.5f);
//    ourShader.setFloat("material.shininess", 32.0f);
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//}

void door(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;

    /*loadTexture(texture7, "door.jpg", GL_RGBA, true);
    glActiveTexture(GL_TEXTURE0);*/
    glBindTexture(GL_TEXTURE_2D, texture7);
    //Left Side
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.4f, -0.42f, 7.6f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 3.2f, 0.2f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", color * 0.5f);
    ourShader.setFloat("material.shininess", 32.0f);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, texture6);
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(7.1f, -0.42f, 7.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 3.2f, 0.2f));
    model = translateMatrix * scaleMatrix;*/
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-angle + 180), glm::vec3(0.0f, 1.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(8.40f, -0.42f, 7.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 3.2f, 0.2f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", color * 0.5f);
    ourShader.setFloat("material.shininess", 32.0f);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void door2(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;

    /*loadTexture(texture7, "door.jpg", GL_RGBA, true);
    glActiveTexture(GL_TEXTURE0);*/
    glBindTexture(GL_TEXTURE_2D, texture5);
    //Left Side
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(angle2), glm::vec3(0.0f, 1.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.4f, -0.42f, 7.6f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 3.2f, 0.2f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", color * 0.5f);
    ourShader.setFloat("material.shininess", 32.0f);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindTexture(GL_TEXTURE_2D, texture4);
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(7.1f, -0.42f, 7.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 3.2f, 0.2f));
    model = translateMatrix * scaleMatrix;*/
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-angle2 + 180), glm::vec3(0.0f, 1.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(8.40f, -0.42f, 7.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 3.2f, 0.2f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", color * 0.5f);
    ourShader.setFloat("material.shininess", 32.0f);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

//void door(Shader lightingShaderWithTexture, glm::mat4 moveMatrix, glm::vec4 color)
//{
//    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;
//
//    string diffuseMapPath = "door.jpg";
//    string specularMapPathDoor = "door.jpg";
//    unsigned int diffMapDoor = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
//    unsigned int specMapDoor = loadTexture(specularMapPathDoor.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
//    Cube cubeFrontDoor = Cube(diffMapDoor, specMapDoor, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
//
//    lightingShaderWithTexture.use();
//    // point light 1
//    pointlight1.setUpPointLight(lightingShaderWithTexture);
//    // point light 2
//    pointlight2.setUpPointLight(lightingShaderWithTexture);
//    // point light 3
//    pointlight3.setUpPointLight(lightingShaderWithTexture);
//    // point light 4
//    pointlight4.setUpPointLight(lightingShaderWithTexture);
//    // point light 5
//    pointlight5.setUpPointLight(lightingShaderWithTexture);
//    //6
//    pointlight6.setUpPointLight(lightingShaderWithTexture);
//    /*loadTexture(texture7, "door.jpg", GL_RGBA, true);
//    glActiveTexture(GL_TEXTURE0);*/
//    //glBindTexture(GL_TEXTURE_2D, texture7);
//    //Left Side
//    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
//    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.98f, -0.42f, 7.6f));
//    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.2f, 3.2f, 0.2f));
//    model = translateMatrix * rotateYMatrix * scaleMatrix;
//    cubeFrontDoor.drawCubeWithTexture(lightingShaderWithTexture, model);
//    /*ourShader.setMat4("model", moveMatrix * model);
//    ourShader.setVec4("material.ambient", color);
//    ourShader.setVec4("material.diffuse", color);
//    ourShader.setVec4("material.specular", color * 0.5f);
//    ourShader.setFloat("material.shininess", 32.0f);*/
//    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//
//    //glBindTexture(GL_TEXTURE_2D, texture7);
//    ///*translateMatrix = glm::translate(identityMatrix, glm::vec3(7.1f, -0.42f, 7.5f));
//    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 3.2f, 0.2f));
//    //model = translateMatrix * scaleMatrix;*/
//    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-angle + 180), glm::vec3(0.0f, 1.0f, 0.0f));
//    //translateMatrix = glm::translate(identityMatrix, glm::vec3(8.42f, -0.42f, 7.8f));
//    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.2f, 3.2f, 0.2f));
//    //model = translateMatrix * rotateYMatrix * scaleMatrix;
//    //ourShader.setMat4("model", moveMatrix * model);
//    //ourShader.setVec4("material.ambient", color);
//    //ourShader.setVec4("material.diffuse", color);
//    //ourShader.setVec4("material.specular", color * 0.5f);
//    //ourShader.setFloat("material.shininess", 32.0f);
//    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//}


void dolna(Cube& cube, Cube& cube2, Shader& ourShader, Shader& lightingShader, glm::mat4 als) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    //swing-seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.95f, .025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //dori1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.95, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .8f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
    //dori2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2, 0.95, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .8f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.95, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle12
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.95, 0.5 - 0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.1750f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2, 0.95, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, .025f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //handle22
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2, 0.95, 0.5 - 0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.1750f, 0.025f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25, 0.75 + 0.025 * 0.2, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.95f, .5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);
}

void swing(Cube& cube, Cube& cube2, Shader& ourShader, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, .05f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //standleft
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, -1.75f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, -1.75f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //stand right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5 - 0.05, 1.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, -1.75f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.5 - 0.05, 1.75, 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05f, -1.75f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-30.0f), glm::vec3(1.0f, 1.0f, 0.0f));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);


}


void fchair(Cube& cube, Cube& cube2, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    //Sofa Seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1, 0.3, -0.9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, .15f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //hande
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.00, 0.65, -0.95));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, .05f, 0.65f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);


    //hande
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, 0.65, -0.95));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, .05f, 0.65f));
    model = als * translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.3 + 0.5 * 0.2, -0.9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, .5f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //Sofa leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.65, -0.95 + 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.65f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(15.0f), glm::vec3(1.0, 0.0, 0.0));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //Sofa leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.65, -0.55 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.65f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-15.0f), glm::vec3(1.0, 0.0, 0.0));

    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //Sofa leg1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, 0.65, -0.9 + 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.65f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(15.0f), glm::vec3(1.0, 0.0, 0.0));
    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //Sofa leg3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, 0.65, -0.45 - 0.05));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, -.65f, 0.05f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-15.0f), glm::vec3(1.0, 0.0, 0.0));

    model = als * translateMatrix * rotateYMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);



}

void drawFan(unsigned int VAO, Shader ourShader, glm::mat4 matr, float r) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, combined, translateMatrix3;
    /*translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;*/

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
    //rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 2.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));

    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 3.0f, 0.8f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.6f, 0.10f, 0.2f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
    //model = translateMatrix * matr * glm::translate(identityMatrix, glm::vec3(-0.4f, -3.0f, -0.8f)) * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.4f, 3.0f, 0.8f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.6f, 0.10f, 0.2f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r+90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //model = translateMatrix * matr * glm::translate(identityMatrix, glm::vec3(-0.4f, -3.0f, -0.8f)) * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 12.5f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.2f, 0.1f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 0.0f, 1.0f));
    model = translateMatrix * glm::translate(identityMatrix, glm::vec3(-8.0f, 0.0f, -2.7f)) * rotateYMatrix * glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -0.5f)) * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    ourShader.setVec4("color", glm::vec4(0.071f, 0.071f, 0.067f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 12.5f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.2f, 0.1f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = translateMatrix * glm::translate(identityMatrix, glm::vec3(-8.0f, 0.0f, -2.7f)) * rotateYMatrix * glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -0.5f)) * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 12.5f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.2f, 0.1f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 230.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = translateMatrix * glm::translate(identityMatrix, glm::vec3(-8.1f, 0.0f, -2.6f)) * rotateYMatrix * glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -0.5f)) * scaleMatrix;
    ourShader.setMat4("model", model);


    //ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.465f, 12.54f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.88f, 0.1f));
    //model = translateMatrix * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //ourShader.setVec4("color", glm::vec4(0.259f, 0.259f, 0.251f, 1.0f));
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 3.0f, 1.0f));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.1f, 0.2f));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //model = translateMatrix * glm::translate(identityMatrix, glm::vec3(0.5f, 0.0f, 0.0f)) * rotateYMatrix * glm::translate(identityMatrix, glm::vec3(-0.5f, 0.0f, 0.0f)) * scaleMatrix;
    //ourShader.setMat4("model", model);
    ////ourShader.setVec3("aColor", glm::vec3(0.2f, 0.1f, 0.4f));
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void drawBoat(Curve& Boat, Cube& cube2, Shader& ourShader, Shader& lightingShader, glm::mat4 als, float angle) {

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, modelMatrixForContainer;

    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.8f, 4.5f, 2.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.6f, 1.4f, -25.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.5f, -5.0f, -0.59f));
    modelMatrixForContainer = als * rotateYMatrix *  scaleMatrix * translateMatrix * rotateZMatrix;
    Boat.draw(lightingShader,  modelMatrixForContainer, glm::vec3(1.0f, 0.0f, 0.0f));

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.2f, 3.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-62.0f, 3.5f, -17.1f));
    modelMatrixForContainer = als * scaleMatrix * translateMatrix;
    cube2.drawCubeWithTexture(lightingShader, modelMatrixForContainer);

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.2f, 3.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-65.0f, 3.5f, -17.1f));
    modelMatrixForContainer = als * scaleMatrix * translateMatrix;
    cube2.drawCubeWithTexture(lightingShader, modelMatrixForContainer);

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.2f, 3.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-68.0f, 3.5f, -17.1f));
    modelMatrixForContainer = als * scaleMatrix * translateMatrix;
    cube2.drawCubeWithTexture(lightingShader, modelMatrixForContainer);

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.2f, 3.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-71.0f, 3.5f, -17.1f));
    modelMatrixForContainer = als * scaleMatrix * translateMatrix;
    cube2.drawCubeWithTexture(lightingShader, modelMatrixForContainer);

    /*scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.2f, 3.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-71.0f, 3.5f, -17.1f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(1.0f, 0.0f, 0.0f));
    model = als*rotateXMatrix * scaleMatrix * translateMatrix;
    drawFan(cubeVAO, lightingShader, model);*/


}