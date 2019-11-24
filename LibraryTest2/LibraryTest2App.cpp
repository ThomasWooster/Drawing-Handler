#include "LibraryTest2App.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

LibraryTest2App::LibraryTest2App() 
{

}

LibraryTest2App::~LibraryTest2App() 
{

}

bool LibraryTest2App::startup() 
{
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

    // create simple camera transforms
    m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
    m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);

    // init camera
    m_camera = new tom::FlyCamera();
    m_camera->setLookAt(vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 1, 0));
    m_camera->setPerspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
    m_camera->setRotation(vec3(0, 0, 0));
    m_camera->setPosition(vec3(0, 0, 0));

    // init directional light
    m_light = new tom::Light();
    m_light->diffuse = { 0.8, 0.8, 0.8 };
    m_light->specular = { 1, 1 , 1 };
    m_light->direction = { 0, -1, 1 };
    m_ambientLight = { 0.5f, 0.5f, 0.5f };

    aie::OBJMesh* bunny = new aie::OBJMesh();
    bunny->load("./Models/stanford/Bunny.obj", true, true);
    aie::OBJMesh* spear = new aie::OBJMesh();
    spear->load("./Models/soulspear/soulspear.obj", true, true);
    
    // initilise the drawing hander
    drawHandle = tom::DrawingHandler::instance();

    float directionX = 0;
    float directionZ = 0;
    for (size_t i = 0; i < 100; i++)
    {

        tom::OBJobject* tempBunny = new tom::OBJobject(vec3(directionX, 0, directionZ), bunny, 0.5f);
        tom::OBJobject* tempSpear = new tom::OBJobject(vec3(directionX, 10, directionZ), spear, 1);

        m_legion.push_back(tempBunny);

        drawHandle->addtoDraw(tempBunny, tom::shaders::PHONG);
        drawHandle->addtoDraw(tempSpear, tom::shaders::ADVANCED);


        directionX += 5;
        if (directionX > 100)
        {
            directionX = 0;
            directionZ += 5;
        }
    }

	return true;
}

void LibraryTest2App::shutdown() 
{

	
}

void LibraryTest2App::update(float deltaTime) 
{
    m_camera->update(deltaTime);

    for (size_t i = 0; i < m_legion.size(); i++)
    {
        glm::vec3 tempRotate = m_legion[i]->getRotation();

        tempRotate += vec3(rand()%10-5, rand() % 10 - 5, rand() % 10 - 5) * deltaTime;

        m_legion[i]->setRotation(tempRotate);

        m_legion[i]->update();
    }
	
}

void LibraryTest2App::draw() 
{
    clearScreen();

    drawHandle->Draw(m_camera, m_light, m_ambientLight);
}