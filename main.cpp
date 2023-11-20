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
#include "directionalLight.h"
#include "spotLight.h"
#include "cube.h"
#include "stb_image.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
//void bed(Shader& lightingShader, glm::mat4 alTogether, Cube& cube);
void Table(Cube &cube,Shader& lightingShader, glm::mat4 alTogether);
void Floor(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void FWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Sofa(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void DiningTable(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Tool(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Chair(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Bookself(Cube& cube, Shader& lightingShader, Shader& lightingShaderTexture, glm::mat4 alTogether);
void TV_Trolly(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void TV(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Wardrobe(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Shokez(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Show(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Door(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void bed(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void ladder(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Ladder(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);//Main one
void Fan(Cube& cube, Cube& cube2, Shader& lightingShader, glm::mat4 alTogether);
void Cupboard(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Wardrobe2(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Shokez(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void RoundTable(Cube& cube, Cube& cube2, Shader& lightingShader, glm::mat4 alTogether);


glm::mat4 transform(float tr_x, float tr_y, float tr_z, float rot_x, float rot_y, float rot_z, float scal_x, float scal_y, float scal_z) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(tr_x, tr_y, tr_z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rot_x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians( rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians( rot_z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scal_x, scal_y, scal_z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    return model;
}



// settings
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 720;

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
float lad_x = 0.0;
float lad_y = 0.0;
float lad_z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float rotateLevel = 0.0;
float rotate_Now = 0.0;
bool open_cupboard = false;
bool open_cupboard2 = false;
bool open_shokez = false;
bool open_wardrobe = false;
bool open_door = false;
bool open_lad = false;
float open_seseme = 0.0;

unsigned int ch_wood_tex;
unsigned int almari_tex;
unsigned int cushion_tex;
unsigned int black_tex;
unsigned int drawer_inside_tex;
unsigned int drawer_outside_tex;
unsigned int plywood_tex;

Camera camera(glm::vec3(0.0f, 3.1f, 13.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 lad = glm::vec3(5.07116, 0.656352, 10.6899);

// lights
// positions of the point lights
glm::vec3 LightPositions[] = {
    glm::vec3(3.06996 ,4.92 ,13.1897),
    glm::vec3(-5.12181 ,4.92 ,13.1597),
    glm::vec3(-6.75269 ,4.92 ,2.44401),
    glm::vec3(4.36687 ,4.92 ,5.62477)
};
DirLight dirlight(
    LightPositions[0].x, LightPositions[0].y, LightPositions[0].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 0.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
SpotLight spotlight(

    LightPositions[1].x, LightPositions[1].y, LightPositions[1].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight1(

    LightPositions[2].x, LightPositions[2].y, LightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    LightPositions[3].x, LightPositions[3].y, LightPositions[3].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);


// light settings
bool pointLightOn1 = true;
bool pointLightOn2 = true;
bool dirLightOn = true;
bool spotLightOn = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool emissionToggle = true;


//Furniture open

bool open_shokej = false;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
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
    
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    string diffuseMapPath = "container2.png";
    string specularMapPath = "container2_specular.png";
    string f_tiles = "floor_tiles.jpg";
    string wood = "wood.png";
    string woods = "woods.jpg";
    string sofa = "sofa.jpg";
    string marbel = "marbel.jpg";
    string cushion = "cushion.jpg";
    string plywood = "plywood.jpg";
    string ch_wood = "ch_wood.jpg";
    string chair = "chair.jpg";
    string wall = "wall.jpg";
    string walls = "walls.jpg";
    string black = "black.jpg";
    string news = "news.jpg";
    string city = "city.jpg";
    string almari = "almari.jpg";
    string door = "door.jpg";
    string drawer_inside = "drawer_inside.jpg";
    string drawer_outside = "drawyer.jpg";

    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int floor_tiles = loadTexture(f_tiles.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wood_tex = loadTexture(wood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int woods_tex = loadTexture(woods.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int sofa_tex = loadTexture(sofa.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int marbel_tex = loadTexture(marbel.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    cushion_tex = loadTexture(cushion.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    plywood_tex = loadTexture(plywood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    ch_wood_tex = loadTexture(ch_wood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int chair_tex = loadTexture(chair.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wall_tex = loadTexture(wall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int walls_tex = loadTexture(walls.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    black_tex = loadTexture(black.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int news_tex = loadTexture(news.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int city_tex = loadTexture(city.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    almari_tex = loadTexture(almari.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int door_tex = loadTexture(door.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    drawer_inside_tex = loadTexture(drawer_inside.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    drawer_outside_tex = loadTexture(drawer_outside.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube tiles_cube = Cube(floor_tiles, floor_tiles, 32.0, 0.0f, 0.0f, 20.0f, 20.0f);
    

    vector<float> v_wheel = {
                     0, 1.65, 5.1000,
                     0, 1.72, 5.1000,
                     -0.005, 1.72, 5.1000,
                    -0.1600, 1.72, 5.1000,
                    -0.2300, 1.72, 5.1000,
                    -0.2950, 1.7200, 5.1000,
                    -0.3700, 1.7200, 5.1000,
                    -0.4500, 1.7200, 5.1000,
                    -0.5400, 1.7200, 5.1000,
                    -0.6100, 1.7200, 5.1000,
                    -0.6900, 1.7200, 5.1000,
                    -0.6900, 1.6600, 5.1000,
                    -0.6900, 1.6150, 5.1000,
                    -0.6900, 1.5600, 5.1000,
                    -0.6600, 1.56, 5.1000,
                    -0.5950, 1.56, 5.1000,
                    -0.5450, 1.56, 5.1000,
                    -0.4850, 1.56, 5.1000,
                    -0.4200, 1.56, 5.1000,
                    -0.3600, 1.56, 5.1000,
                    -0.2800, 1.56, 5.1000,
                    -0.1900, 1.56, 5.1000,
                    -0.1250, 1.56, 5.1000,
                    -0.0650, 1.56, 5.1000,
                     0, 1.56, 5.1000,
    };


    vector<float>v_vase = {
            -0.3700, 1.6750, 5.1000,
            -0.3850, 1.6100, 5.1000,
            -0.3350, 1.5300, 5.1000,
            -0.2900, 1.4850, 5.1000,
            -0.2600, 1.4350, 5.1000,
            -0.2600, 1.3200, 5.1000,
            -0.3200, 1.2500, 5.1000,
            -0.4000, 1.1200, 5.1000,
            -0.4750, 1.0100, 5.1000,
            -0.5450, 0.8650, 5.1000,
            -0.5800, 0.7350, 5.1000,
            -0.5850, 0.5950, 5.1000,
            -0.5400, 0.4800, 5.1000,
            -0.4400, 0.3550, 5.1000,
            -0.3700, 0.2400, 5.1000,
            -0.3150, 0.1450, 5.1000,
            -0.3050, 0.0650, 5.1000,
            -0.2950, 0.0100, 5.1000,
            -0.1950, 0.0050, 5.1000,
            -0.1050, -0.0050, 5.1000,
            -0.0350, -0.0050, 5.1000,
    };

    Cube vase = Cube(glm::vec3(1, 1, 1));
    vase.initiate(v_vase);


    Cube wheel = Cube(glm::vec3(1, 1, 1));
    wheel.initiate(v_wheel);
    //Sphere sphere = Sphere();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


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
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lad = glm::vec3(5.07116+lad_x, 0.656352+lad_y, 10.6899+lad_z);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);
        
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);
       
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        dirlight.setUpPointLight(lightingShaderWithTexture);
        spotlight.setUpPointLight(lightingShaderWithTexture);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.42, 0.11, 8.18f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix;

        cube.setTextureProperty(diffMap, specMap, 32.0f);
        cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        

        cube.setTextureProperty(ch_wood_tex, ch_wood_tex, 32);

        //Drawing Table
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.065, 4.86783));
        Table(cube, lightingShaderWithTexture, translateMatrix);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(lad_x, lad_y, lad_z));
        Ladder(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.42, 0.11, 8.18f));
        Tool(cube, lightingShaderWithTexture, translateMatrix);
        ////cube.setTextureProperty(woods_tex, woods_tex, 32.0f);
        ////translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0, 0.065, 4.86783));
        ////Table(cube, lightingShaderWithTexture, translateMatrix);

        cube.setTextureProperty(marbel_tex, marbel_tex, 32.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.10874, -1.29, 5.57778));
        RoundTable(wheel,vase, lightingShaderWithTexture, translateMatrix);

        ////front
        cube.setTextureProperty(chair_tex, chair_tex, 32.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.57002, -0.08, -4.6));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        Chair(cube, lightingShaderWithTexture, translateMatrix* rotateYMatrix* scaleMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.33, -0.08, -4.6));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        Chair(cube, lightingShaderWithTexture, translateMatrix* rotateYMatrix* scaleMatrix);
        //back
        translateMatrix = glm::translate(identityMatrix, glm::vec3(6.57002, -0.08, -8.03));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.33, -0.08, -8.03));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
        Chair(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);

        cube.setTextureProperty(walls_tex, walls_tex, 32.0f);
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(-25.2967, -0.9099926, 0.6557));
        //Floor(cube, lightingShaderWithTexture, translateMatrix);//-4.22f, -0.989999f, -5.28003f
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.7402, -0.83, 0.67));
        FWall(cube, lightingShaderWithTexture, translateMatrix);

        //back wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-14.88, -0.83, 18));
        FWall(cube, lightingShaderWithTexture, translateMatrix);
        //Uppder wall
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.7402, 3.2, 18));
        FWall(cube, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-11.7402, -0.83, 18));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        FWall(cube, lightingShaderWithTexture, translateMatrix * rotateYMatrix);

        //Middle 
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1, 0.4));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.53005, -0.83, 18));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        FWall(cube, lightingShaderWithTexture, scaleMatrix * translateMatrix * rotateYMatrix);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1, 0.52));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.53005, -0.83, 35.0));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        FWall(cube, lightingShaderWithTexture, scaleMatrix * translateMatrix * rotateYMatrix);

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 0.5, 1));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.27, 4.35, 18.441));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        FWall(cube, lightingShaderWithTexture, scaleMatrix * translateMatrix * rotateYMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.7402, -0.83, 18));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        FWall(cube, lightingShaderWithTexture, translateMatrix * rotateYMatrix);

        //Ceil
        cube.setTextureProperty(wall_tex, wall_tex, 32.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25.2967, 5, 0.6557));
        Floor(cube, lightingShaderWithTexture, translateMatrix);//-4.22f, -0.989999f, -5.28003f

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25.2967, -0.9099926, 0.6557));
        Floor(tiles_cube, lightingShaderWithTexture, translateMatrix);
        //
        
        cube.setTextureProperty(news_tex, news_tex, 32.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.15, 0.54, 0.89));
        Show(cube, lightingShaderWithTexture,translateMatrix);
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-13.5602, 0.83, -3.16));
        cube.setTextureProperty(city_tex, city_tex, 32.0f);
        Show(cube, lightingShaderWithTexture, rotateYMatrix*translateMatrix);

        cube.setTextureProperty(door_tex, door_tex, 32.0f);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.75, -0.83, 17.87f));
        Door(cube, lightingShaderWithTexture, translateMatrix);

        cube.setTextureProperty(black_tex, black_tex, 32.0f);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.49, -0.85, 0.87));
        TV_Trolly(cube, lightingShaderWithTexture, translateMatrix);
        
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.51001, 0.0, -15.29));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        cube.setTextureProperty(almari_tex, almari_tex, 32.0f);
       
        Cupboard(cube, lightingShaderWithTexture, rotateYMatrix* translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.51001, 0.0, -12.29));
        cube.setTextureProperty(ch_wood_tex, ch_wood_tex, 32.0f);
        Wardrobe2(cube, lightingShaderWithTexture, rotateYMatrix* translateMatrix);
        cube.setTextureProperty(plywood_tex, plywood_tex, 32.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.49, -0.08, -5.77));
        Shokez(cube, lightingShaderWithTexture, rotateYMatrix* translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.76, 0.059, -9.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.0f, 1.0f));//
        //middle sofa
        cube.setTextureProperty(sofa_tex, sofa_tex, 32);
        Sofa(cube, lightingShaderWithTexture, translateMatrix* scaleMatrix);//,translate_X, translate_Y, translate_Z
        //Right Sofa
        cube.setTextureProperty(sofa_tex, sofa_tex, 32);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.89776, -0.099, -3.64292));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.0f, 1.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(283.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        Sofa(cube, lightingShaderWithTexture, rotateYMatrix* translateMatrix* scaleMatrix);//,translate_X, translate_Y, translate_Z

        //Left Sofa
        cube.setTextureProperty(sofa_tex, sofa_tex, 32);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.06396, 0.043, -5.37979));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.0f, 1.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(77.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        Sofa(cube, lightingShaderWithTexture, translateMatrix* rotateYMatrix* scaleMatrix);//,translate_X, translate_Y, translate_Z

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.18, -0.83, 13.8402));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.5f, 3.0f, 4.5f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        bed(cube, lightingShaderWithTexture, translateMatrix* rotateYMatrix* scaleMatrix);//,


        lightingShader.use();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);
        
        

        pointlight1.setUpPointLight(lightingShader);
        pointlight2.setUpPointLight(lightingShader);
        dirlight.setUpPointLight(lightingShader);
        spotlight.setUpPointLight(lightingShader);

        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        
        
        //Table(cube, lightingShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.3, 0.32, 18.91));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 0.4, 0.3));
        vase.drawObject(lightingShader, scaleMatrix* translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.22, 0.47, 0.87));
        TV(cube, lightingShader, translateMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.69, -0.82, 14.6902));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 3.0f, 2.5f));
        //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(77.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //Bookself(cube, lightingShader, lightingShaderWithTexture, translateMatrix* scaleMatrix);//,translate_X, translate_Y, translate_Z
       
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.36, -0.82, 19.69));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 3.0f, 2.5f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //Bookself(cube, lightingShader, lightingShaderWithTexture, translateMatrix* rotateYMatrix* scaleMatrix);
        
        rotate_Now = (rotate_Now + rotateLevel);
        if (rotate_Now == 361.0)
            rotate_Now = 0.0;

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotate_Now), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.51, 4.08, 4.82));//translate_X, translate_Y, translate_Z
        Fan(cube, wheel, lightingShader, translateMatrix * rotateYMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.88, 4.08, 5.12));//translate_X, translate_Y, translate_Z
        Fan(cube, wheel, lightingShader, translateMatrix * rotateYMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-7.06, 4.08, 13.52));//translate_X, translate_Y, translate_Z
        Fan(cube, wheel, lightingShader, translateMatrix * rotateYMatrix);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 4.08, 12.44));//translate_X, translate_Y, translate_Z
        Fan(cube, wheel, lightingShader, translateMatrix * rotateYMatrix);


        // also draw the lamp object(s)
        
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        glm::vec3 LightColor[] = {
        glm::vec3(0.8f, 0.8f, 0.8f),// White - Dir
        glm::vec3(1.0f,  0.0f,  0.0f),//Red - Spot Light
        glm::vec3(0.0f,  1.0f,  0.0f),//Green - Point Light 1
        glm::vec3(0.0f,  0.0f,  1.0f)//Blue - Point Light 1
        };
        
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            //LightPositions[i].y = translate_Y;
            model = glm::translate(model, LightPositions[i]);
            model = glm::scale(model, glm::vec3(0.5f)); // Make it a smaller cube
            cube.drawCube(ourShader, model);
        }
        
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    cout << translate_X << ", " << translate_Y << ", " <<translate_Z << endl;
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
        glm::vec3 pos = camera.Position;
        if (abs(lad[0] - pos[0]) <= 0.2 && abs(lad[2] - pos[2]) <= 1.5)//0.2, 1.5
        {
            cout << "Ladder Up" << endl;
            camera.ProcessKeyboard(UP, deltaTime);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
        glm::vec3 pos = camera.Position;
        if (abs(lad[0] - pos[0]) <= 0.2 && abs(lad[2] - pos[2]) <= 1.5)//0.2, 1.5
        {
            cout << "Ladder Up" << endl;
            camera.ProcessKeyboard(DOWN, deltaTime);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }

    /*if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }*/
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) 
    { 
        translate_Y += 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        translate_Y -= 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        translate_X += 0.01;
        if (open_lad)
        {
            lad_x += 0.05;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        translate_X -= 0.01;
        if (open_lad)
            lad_x -= 0.05;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        translate_Z += 0.01;
        if (open_lad)
            lad_z += 0.05;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        translate_Z -= 0.01;
        if (open_lad)
            lad_z -= 0.05;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;



}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (dirLightOn)
        {
            dirlight.turnOff();
            dirLightOn = !dirLightOn;
        }
        else
        {
            dirlight.turnOn();
            dirLightOn = !dirLightOn;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn1)
        {
            pointlight1.turnOff();
            pointLightOn1 = !pointLightOn1;
        }
        else
        {
            pointlight1.turnOn();
            pointLightOn1 = !pointLightOn1;
        }
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (pointLightOn2)
        {
            pointlight2.turnOff();
            pointLightOn2 = !pointLightOn2;
        }
        else
        {
            pointlight2.turnOn();
            pointLightOn2 = !pointLightOn2;
        }
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (spotLightOn)
        {
            spotlight.turnOff();
            spotLightOn = !spotLightOn;
        }
        else
        {
            spotlight.turnOn();
            spotLightOn = !spotLightOn;
        }
    }
    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (ambientToggle)
        {
            if (pointLightOn1)
                pointlight1.turnAmbientOff();
            if (pointLightOn2)
                pointlight2.turnAmbientOff();
            spotlight.turnAmbientOff();
            if (dirLightOn)
                dirlight.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {
            if (pointLightOn1)
                pointlight1.turnAmbientOn();
            if (pointLightOn2)
                pointlight2.turnAmbientOn();
            if (spotLightOn)
                spotlight.turnAmbientOn();
            if (dirLightOn)
                dirlight.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            if (pointLightOn1)
                pointlight1.turnDiffuseOff();
            if (pointLightOn2)
                pointlight2.turnDiffuseOff();
            if (dirLightOn)
                dirlight.turnDiffuseOff();
            if (spotLightOn)
                spotlight.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            if (pointLightOn1)
                pointlight1.turnDiffuseOn();
            if (pointLightOn2)
                pointlight2.turnDiffuseOn();
            if (dirLightOn)
                dirlight.turnDiffuseOn();
            if (spotLightOn)
                spotlight.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }
    if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        if (specularToggle)
        {
            if (pointLightOn1)
                pointlight1.turnSpecularOff();
            if (pointLightOn2)
                pointlight2.turnSpecularOff();
            if (dirLightOn)
                dirlight.turnSpecularOff();
            if (spotLightOn)
                spotlight.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            if (pointLightOn1)
                pointlight1.turnSpecularOn();
            if (pointLightOn2)
                pointlight2.turnSpecularOn();
            if (dirLightOn)
                dirlight.turnSpecularOn();
            if (spotLightOn)
                spotlight.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }
    
    if (key == GLFW_KEY_8 && action == GLFW_PRESS)
    {
        glm::vec3 pos = camera.Position;
        //glm::vec3 cupboard = glm::vec3(-6.67089, 1.16779, -1.3655);
        glm::vec3 cupboard = glm::vec3(-10.6976, 1.04105, 13.8016);
        glm::vec3 shokejP = glm::vec3(-10.7603, 1.04047, 4.01365);
        glm::vec3 wardrobeP = glm::vec3(-10.6666, 0.910231, 10.53);
        glm::vec3 door = glm::vec3(5.33418, 3.16694, 20.9356);
        
        if (cupboard[0] - pos[0] >= -6.0 && cupboard[0] - pos[0] <= 0 && abs(cupboard[2] - pos[2]) <= 2.0)
        {
            cout << "cupboard" << endl;
            open_cupboard = !open_cupboard;

        }
        /*if (cupboard2[0] - pos[0] >= -6.0 && cupboard2[0] - pos[0] <= 0 && abs(cupboard2[2] - pos[2]) <= 2.0)
        {
            cout << "cupboard2" << endl;
            open_cupboard2 = !open_cupboard2;

        }*/
        if (shokejP[0] - pos[0] >= -6.0 && shokejP[0] - pos[0] <= 0 && abs(shokejP[2] - pos[2]) <= 2.0)
        {
            cout << "shokej" << endl;
            open_shokez = !open_shokez;
        }
        if (wardrobeP[0] - pos[0] >= -6.0 && wardrobeP[0] - pos[0] <= 0 && abs(wardrobeP[2] - pos[2]) <= 2.0)
        {
            cout << "wardrobe" << endl;
            open_wardrobe = !open_wardrobe;
        }
        if (abs(lad[0] - pos[0]) <= 4.0 && abs(lad[2] - pos[2]) <= 4.0)//0.2, 1.5
        {
            cout << "Ladder" << endl;
            open_lad = !open_lad;
            //camera.PrintInfo();
        }
        else
        {
            camera.PrintInfo();
        }

    }
    if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
        rotateLevel = rotateLevel + 5.0;
        if (rotateLevel == 25.0)
            rotateLevel = 0.0;
    }
    if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        glm::vec3 pos = camera.Position;
        if (abs(lad[0] - pos[0]) <= 4.0 && abs(lad[2] - pos[2]) <= 4.0)//0.2, 1.5
        {
            cout << "Ladder" << endl;
            open_lad = !open_lad;
            //camera.PrintInfo();
        }
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


void ladder(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 model = transform(-2.0, -.8, -4, 0, 0, 0, .15, 5.3, .15);
    cube.setTextureProperty(almari_tex, almari_tex, 32.0f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    model = transform(-1.4, -.8, -4, 0, 0, 0, .15, 5.3, .15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(-2.0, -.4, -4, 0, 0, 0, 1.2, 0.15, .15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(-2.0, 0, -4, 0, 0, 0, 1.2, 0.15, .15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(-2.0, 0.4, -4, 0, 0, 0, 1.2, 0.15, .15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(-2.0, 0.8, -4, 0, 0, 0, 1.2, 0.15, .15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    model = transform(-2.0, 1.2, -4, 0, 0, 0, 1.2, 0.15, .15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(-2.0, 1.6, -4, 0, 0, 0, 1.2, 0.15, .15);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void bed(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    float baseHeight = 0.3;
    float width = 1;
    float length = 2;
    float pillowWidth = 0.3;
    float pillowLength = 0.15;
    float blanketWidth = 1.0;
    float blanketLength = 1.8;
    float headHeight = 0.6;

    //base
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(width, baseHeight, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
    cube.setTextureProperty(ch_wood_tex, ch_wood_tex, 32.0);
    cube.drawCubeWithTexture(lightingShader, model);

    //foam
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight / 2, 0));
    scale = glm::scale(model, glm::vec3(width, 0.06, length));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 0.804, 0.361, 0.361);
    cube.setTextureProperty(cushion_tex, cushion_tex, 32.0);
    cube.drawCubeWithTexture(lightingShader, model);

    //pillow 1
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((width / 4) - (0.1 + pillowWidth / 2), baseHeight / 2 + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.46, 0, -0.5));
    model = alTogether * translate2 * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);
    cube.drawCubeWithTexture(lightingShader, model);

    //pillow 2
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3((-width / 4) + (0.1 + pillowWidth / 2), baseHeight / 2 + 1 * 0.06, (length / 2) - (0.025 + pillowWidth / 2)));
    scale = glm::scale(model, glm::vec3(pillowWidth, 0.04, pillowLength));
    translate = glm::translate(model, glm::vec3(-0.21, 0.0, -0.5));
    model = alTogether * translate2 * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 1, 0.647, 0);
    cube.drawCubeWithTexture(lightingShader, model);

    //blanket
    /*model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, baseHeight/2 + 1 * 0.06, -(length / 2 - 0.025) + blanketLength / 2));
    scale = glm::scale(model, glm::vec3(blanketWidth, 0.015, blanketLength));
    translate = glm::translate(model, glm::vec3(-0.5, -0.05, -0.41));
    model = alTogether * translate2 * translate * scale ;
    drawCube(cubeVAO, lightingShader, model, 0.541, 0.169, 0.886);*/

    //head
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    translate2 = glm::translate(model, glm::vec3(0, 0, (length / 2 - 0.02 / 2) + 0.02));
    scale = glm::scale(model, glm::vec3(width, headHeight, 0.02));
    translate = glm::translate(model, glm::vec3(-0.5, 0, -0.5));
    model = alTogether * translate2 * translate * scale;
    //drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
    cube.setTextureProperty(almari_tex, almari_tex, 32.0);
    cube.drawCubeWithTexture(lightingShader, model);
}

void Table(Cube &cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //cube.setMaterialisticProperty(glm::vec3(0.862f, 0.46f, 0.321f));
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, -0.2f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.2f, 3.0f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -0.1f));
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model1 = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.drawCubeWithTexture(lightingShader, alTogether * model1);

    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.8f, 0.0f, -0.1f));
    rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model2 = rotateXMatrix2 * translateMatrix2 * scaleMatrix2;
    cube.drawCubeWithTexture(lightingShader, alTogether * model2);

    glm::mat4 translateMatrix3, rotateXMatrix3, rotateYMatrix3, rotateZMatrix3, scaleMatrix3, model3;
    translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.8f, 0.0f, -1.49f));
    rotateXMatrix3 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model3 = rotateXMatrix3 * translateMatrix3 * scaleMatrix3;
    cube.drawCubeWithTexture(lightingShader, alTogether * model3);
    // Modelling Transformation
    glm::mat4 translateMatrix4, rotateXMatrix4, rotateYMatrix4, rotateZMatrix4, scaleMatrix4, model4;
    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -1.49f));
    rotateXMatrix4 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model4 = rotateXMatrix4 * translateMatrix4 * scaleMatrix4;
    cube.drawCubeWithTexture(lightingShader, alTogether * model4);
}

void Sofa(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //Back
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.19f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.55f, 2.0f, 0.5f));
    alTogether = rotateYMatrix * alTogether;
    model = scaleMatrix * translateMatrix;
    //cube.setMaterialisticProperty(glm::vec3(0.4f, 0.226f, 0.44f));
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //Seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, -0.5f, 0.0f));//translate_X, translate_Y, translate_Z
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 1.0f, 2.0f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    ////left hand
    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(1.1f, -0.5f, -1.0f));
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.0f, 2.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.setMaterialisticProperty(glm::vec3(0.52f, 0.39f, 0.31f));
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    ////right hand
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.79f, -0.5f, -1.0f));
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.0f, 2.0f));
    model = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    ////left Leg
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.79f, 0.35f, -1.0f));//translate_X, translate_Y, translate_Z
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.2f, 0.8f, 2.0f));
    model = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    ////right Leg
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(1.08f, 0.35f, -1.0f));//translate_X, translate_Y, translate_Z
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.2f, 0.8f, 2.0f));
    model = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

}

void Floor(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.387f, 0, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(35.0f, 0.1f, 35.0f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;

    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void Ladder(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.77006, -0.75, 14.1102));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    ladder(cube, lightingShader, alTogether*translateMatrix * rotateZMatrix);
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.77006, 0.62, 14.75));
    ladder(cube, lightingShader, alTogether*translateMatrix * rotateZMatrix);
    
}


void FWall(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(35.0f, 12.0f, 0.1f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model = scaleMatrix * translateMatrix;
    //moveMatrix = rotateZMatrix * moveMatrix;
    lightingShader.setMat4("model", alTogether * model);
    //drawCube(cubeVAO, lightingShader, alTogether * model, 0.53f, 0.81f, 0.92f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}


void DiningTable(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 0, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 0.3f, 3.0f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //drawCube(cubeVAO, lightingShader, alTogether * model, 0.478, 0.573, 0.62);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, 2.52, -0.025));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.5f, 0.05f, 3.5f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //ourShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -0.1f));
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model1 = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.drawCubeWithTexture(lightingShader, alTogether * model1);

    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.8f, 0.0f, -0.1f));
    rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model2 = rotateXMatrix2 * translateMatrix2 * scaleMatrix2;
    cube.drawCubeWithTexture(lightingShader, alTogether * model2);

    glm::mat4 translateMatrix3, rotateXMatrix3, rotateYMatrix3, rotateZMatrix3, scaleMatrix3, model3;
    translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.8f, 0.0f, -1.49f));
    rotateXMatrix3 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model3 = rotateXMatrix3 * translateMatrix3 * scaleMatrix3;
    cube.drawCubeWithTexture(lightingShader, alTogether * model3);
    // Modelling Transformation
    glm::mat4 translateMatrix4, rotateXMatrix4, rotateYMatrix4, rotateZMatrix4, scaleMatrix4, model4;
    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -1.49f));
    rotateXMatrix4 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model4 = rotateXMatrix4 * translateMatrix4 * scaleMatrix4;
    cube.drawCubeWithTexture(lightingShader, alTogether * model4);
}

void Tool(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2f, -0.2f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 2.0f));
    model = scaleMatrix * translateMatrix;
    //drawCube(cubeVAO, lightingShader, alTogether * model, 0.0f, 0.4f, 0.18f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //Leg
    glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;//translate_X, translate_Y, translate_Z
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.05f, -0.86f, 0.36f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.5f, 1.7f, 0.5f));
    model1 = translateMatrix1 * scaleMatrix1;
    cube.setMaterialisticProperty(glm::vec3(0.52f, 0.39f, 0.31f));
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model1);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.16f, -4.27f, 0.21f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.2f, 1.0f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
}

void Chair(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //Seat
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.22, -1.0, 0.05));//
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
    alTogether = rotateYMatrix * alTogether;
    model = scaleMatrix * translateMatrix;
    //drawCube(cubeVAO, lightingShader, alTogether * model, 0.165, 0.435, 0.451);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //Back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.22, 0.15f, 0.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.7f, 0.1f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    glm::mat4 identityMatrix1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.2f, 0.1, -0.1f));
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
    model1 = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.drawCubeWithTexture(lightingShader, alTogether * model1);

    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.2f, 0.1, -0.5f));
    rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
    model2 = rotateXMatrix2 * translateMatrix2 * scaleMatrix2;
    cube.drawCubeWithTexture(lightingShader, alTogether * model2);

    // Modelling Transformation
    glm::mat4 identityMatrix3 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix3, rotateXMatrix3, rotateYMatrix3, rotateZMatrix3, scaleMatrix3, model3;
    translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.2f, 0.1, -0.1f));
    rotateXMatrix3 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
    model3 = rotateXMatrix3 * translateMatrix3 * scaleMatrix3;
    cube.drawCubeWithTexture(lightingShader, alTogether * model3);
    // Modelling Transformation

    glm::mat4 translateMatrix4, rotateXMatrix4, rotateYMatrix4, rotateZMatrix4, scaleMatrix4, model4;
    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(0.2f, 0.1, -0.5f));
    rotateXMatrix4 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
    model4 = rotateXMatrix4 * translateMatrix4 * scaleMatrix4;
    cube.drawCubeWithTexture(lightingShader, alTogether * model4);

    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(-0.2f, -0.1f, 0.05f));
    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 0.1f));
    model4 = translateMatrix4 * scaleMatrix4;
    cube.drawCubeWithTexture(lightingShader, alTogether * model4);

    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(0.2f, -0.1f, 0.05f));
    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 0.1f));
    model4 = translateMatrix4 * scaleMatrix4;
    cube.drawCubeWithTexture(lightingShader, alTogether * model4);

}

void Bookself(Cube& cube, Shader& lightingShader, Shader& lightingShaderTexture, glm::mat4 alTogether)
{
    // base
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 0.1f, 0.5f));
    model = translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, alTogether * model,);
    //cube.setMaterialisticProperty(glm::vec3(0.462f, 0.258f, 0.145f));
    cube.setTextureProperty(black_tex, black_tex, 32.0f);
    cube.drawCubeWithTexture(lightingShaderTexture, alTogether * model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, 1.3, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7f, 0.1f, 0.5f));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderTexture, alTogether * model);

    // mid 1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, 1.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.1f, 0.5f));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderTexture, alTogether * model);

    // mid 2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, .7, 1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, .1, 0.5));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderTexture, alTogether * model);

    // mid 3
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.55, .35, 1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5, .1, 0.5));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderTexture, alTogether * model);

    // left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5, .05, 1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1, 2.5, 0.5));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderTexture, alTogether * model);

    //right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.8, .05, 1));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1, 2.5, 0.5));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShaderTexture, alTogether * model);

    //Books
    float colors[] = { 0.545455, 0.909091, 0.545455, 0.181818, 0.0909091, 0.363636, 0, 0.545455, 0.272727, 0.0909091, 0.727273, 0.636364, 0.454545, 0.272727, 0.636364, 0.363636, 0.818182, 0.909091, 0.181818, 0, 0.909091, 0.727273, 0.454545, 0, 0.363636, 0.545455, 0, 0.909091, 0.272727, 0.909091, 0.909091, 0.636364, 0.909091, 0.272727, 0.636364, 0.818182 };
    int k = 0;
    for (float j = 0; j <= 0.9; j = j + 0.3)
    {
        for (float i = 0; i < 0.2; i = i + 0.06)
        {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.75 - i, 1.05 - j, 1.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05, 0.5, 0.6));
            model = translateMatrix * scaleMatrix;
            k = k + 3;
            //drawCube(cubeVAO, lightingShader, alTogether * model, colors[k], colors[k + 1], colors[k + 2]);
            cube.setMaterialisticProperty(glm::vec3(colors[k], colors[k + 1], colors[k + 2]));
            cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
        }
    }


}

void TV(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0f, 4.0f, 0.2f));
    model = scaleMatrix * translateMatrix;
    cube.setMaterialisticProperty(glm::vec3(0.0f, 0.0f, 0.0f));
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

}
void Show(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.70f, 3.70f, 0.2f));
    model = scaleMatrix * translateMatrix;
    //cube.setMaterialisticProperty(glm::vec3(0.0f, 0.0f, 0.0f));
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

}

void Door(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 9.0f, 0.2f));
    model = scaleMatrix * translateMatrix;
    //cube.setMaterialisticProperty(glm::vec3(0.0f, 0.0f, 0.0f));
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

}
void TV_Trolly(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.0f, 2.0f, 1.0f));
    model = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void Wardrobe(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //WARDROBE 
        //back
    glm::mat4 translateMatrix, scaleMatrix, model;
    model = transform(6.95, -0.75, -8.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 7.0f, 4.0f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //left
    model = transform(5.95, -0.75, -8.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    //right
    model = transform(5.95, -0.75, -6.55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //upper
    model = transform(5.95, 2.75, -8.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.1f, .1f, 4.0f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //.5 down
    model = transform(5.95, -0.5 - 0.025, -8.5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //WARDROBE front self
    model = transform(5.95, -0.5 + 0.025, -8.5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 6.45f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //WARDROBE front self border
    model = transform(5.95 - 0.01, -0.5 + 0.025, -7.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 6.45f, 0.02f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void Fan(Cube& cube, Cube& cube2, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    //wings
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.2f, 0.5f));
    model = scaleMatrix * translateMatrix;
    cube.setMaterialisticProperty(glm::vec3(0.0f, 0.0f, 1.0f));
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0));//,translate_X, translate_Y, translate_Z
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.2f, 0.5f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = rotateYMatrix * scaleMatrix * translateMatrix;
    cube.setMaterialisticProperty(glm::vec3(0.0f, 0.0f, 1.0f));
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));//,
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 0.2f, 0.5f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = rotateYMatrix * scaleMatrix * translateMatrix;
    cube.setMaterialisticProperty(glm::vec3(0.0f, 0.0f, 1.0f));
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    //circle
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, -1.60902, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.0f, 0.5f));
    model = scaleMatrix * translateMatrix;
    lightingShader.setMat4("model", alTogether * model);
    cube2.setMaterialisticProperty(glm::vec3(0.0f, 0.0f, 1.0f));
    cube2.drawObjectFilled(lightingShader, alTogether * model);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, -1.60902 + 0.05, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 6.0f, 0.1f));
    model = scaleMatrix * translateMatrix;
    lightingShader.setMat4("model", alTogether * model);
    cube2.setMaterialisticProperty(glm::vec3(1.0f, 1.0f, 1.0f));
    cube2.drawObjectFilled(lightingShader, alTogether * model);

}

void Cupboard(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;
    model = transform(6.95, -0.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 7.0f, 4.0f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //left
    model = transform(5.95, -0.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //right
    model = transform(5.95, -0.75, 2.45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //upper
    model = transform(5.95, 2.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.1f, .1f, 4.0f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    //3
    model = transform(5.99, 0.75 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //.4
    model = transform(5.99, 0.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //.5
    model = transform(5.99, -0.5 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //front left door
    glm::mat4 rotateXMatrix, rotateXMatrix2, rotateZMatrix, translateMatrix2;
    if (open_cupboard || open_cupboard2)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2, 0.0, .104));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.34, 0, -0.042));
    }
    else
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
    }
    model = transform(5.95, -0.5 + 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 6.5f, 1.9f);

    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix * rotateXMatrix * model);
    //front right door
    model = transform(5.95, -0.5 + 0.025, .5 + 0.987991, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 6.5f, 1.9f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix2 * rotateXMatrix2 * model);

    //front self border
    model = transform(5.95 - 0.01, -0.5 + 0.025, 1.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.1f, 6.5f, 0.02f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //4
    model = transform(5.99, 1.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //5
    model = transform(5.99, 1.75 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    //6 
    model = transform(5.99, 2.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);



}


void Wardrobe2(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, scaleMatrix, model;
    cube.setTextureProperty(plywood_tex, plywood_tex, 32);
    model = transform(6.95, -0.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 7.0f, 4.0f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //left
    model = transform(5.95, -0.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //right
    model = transform(5.95, -0.75, 2.45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //upper
    model = transform(5.95, 2.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.1f, .1f, 4.0f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //3

    model = transform(5.95, 0.75 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix * model);
    //.4
    cube.setTextureProperty(plywood_tex, plywood_tex, 32);
    model = transform(5.95, 0.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //.5
    model = transform(5.95, -0.5 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //4
    model = transform(5.95, 1.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //5
    model = transform(5.95, 1.75 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //6 
    model = transform(5.95, 2.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    glm::mat4 rotateXMatrix, rotateXMatrix2, rotateZMatrix, translateMatrix2;
    if (open_wardrobe)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(open_seseme, 0.0, 0.0));
        open_seseme = open_seseme - 0.01;
        open_seseme = max(open_seseme, -0.69f);

    }
    else
    {
        open_seseme = open_seseme + 0.01;
        open_seseme = min(open_seseme, 0.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(open_seseme, 0, 0));
    }


    //.3 droyer 
    cube.setTextureProperty(drawer_inside_tex, drawer_inside_tex, 32);
    model = transform(5.95, 0.80 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix * model);
    //.4 droyer 
    model = transform(5.95, 0.30 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //.5 droyer 
    model = transform(5.95, -0.45 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, 1.5f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix * model);
    //4 droyer
    model = transform(5.95, 1.30 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //5 droyer 
    model = transform(5.95, 1.80 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //6 droyer 
    model = transform(5.95, 2.30 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix * model);


    //.3 droyer ex
    cube.setTextureProperty(drawer_outside_tex, drawer_outside_tex, 32);
    model = transform(5.94, 0.80 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix * model);
    //.4 droyer ex
    model = transform(5.94, 0.30 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //.5 droyer ex
    model = transform(5.94, -0.45 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 1.5f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix * model);
    //4 droyer ex
    model = transform(5.94, 1.30 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //5 droyer ex
    model = transform(5.94, 1.80 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //6 droyer ex
    model = transform(5.94, 2.30 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 0.9f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix * model);

}


void Shokez(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{

    glm::mat4 translateMatrix, scaleMatrix, model;
    model = transform(6.95, -0.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 7.0f, 4.0f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //left
    model = transform(5.95, -0.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //right
    model = transform(5.95, -0.75, 2.45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, 7.0f, 0.1f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //upper
    model = transform(5.95, 2.75, .5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.1f, .1f, 4.0f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    //3
    model = transform(5.95, 0.75 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //.5
    model = transform(5.95, -0.5 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    glm::mat4 rotateXMatrix, rotateXMatrix2, rotateZMatrix, translateMatrix2;
    glm::mat4 identityMatrix = glm::mat4(1.0f);

    if (open_shokez)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.2, 0.0, .104));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.34, 0, -0.043));
    }
    else
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0, 0));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.0, 0.0, 0.0));
    }

    //front left door
    model = transform(5.95, -0.5 + 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 2.4f, 1.9f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix * rotateXMatrix * model);
    //front right door
    model = transform(5.95, -0.5 + 0.025, .5 + 0.987991, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1f, 2.4f, 1.9f);
    cube.drawCubeWithTexture(lightingShader, alTogether * translateMatrix2 * rotateXMatrix2 * model);

    //front self border
    model = transform(5.95 - 0.01, -0.5 + 0.025, 1.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.1f, 2.4f, 0.02f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //4
    model = transform(5.95, 1.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //5
    model = transform(5.95, 1.75 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.0f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    //6 
    model = transform(5.95, 2.25 - 0.025, .5 + .05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.8f, .1f, 3.8f);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //bokself end


}

void RoundTable(Cube& cube, Cube& cube2, Shader& lightingShader, glm::mat4 alTogether)
{
    //Upper
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 1.0f, 2.0f));

    model = scaleMatrix * translateMatrix;
    lightingShader.setMat4("model", alTogether * model);
    cube.setMaterialisticProperty(glm::vec3(0.631, 0.616, 0.569));
    cube.drawObjectFilled(lightingShader, alTogether * model);

    //Lower
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, -1.1f, 0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8f, 1.0f, 0.8f));

    model = scaleMatrix * translateMatrix;
    lightingShader.setMat4("model", alTogether * model);
    cube.setMaterialisticProperty(glm::vec3(0.769, 0.753, 0.706));
    cube.drawObjectFilled(lightingShader, alTogether * model);

    //Base
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.0f, 0.5f));
    model = scaleMatrix;
    cube2.setMaterialisticProperty(glm::vec3(0.769, 0.753, 0.706));
    cube2.drawObject(lightingShader, alTogether * model);
}