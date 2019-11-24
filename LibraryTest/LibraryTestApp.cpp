#include "LibraryTestApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <SimpleQuad.h>
#include <simpleBox.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

LibraryTestApp::LibraryTestApp() {

}

LibraryTestApp::~LibraryTestApp() {

}

bool LibraryTestApp::startup() {

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


    // load meshes
    aie::OBJMesh* bunny = new aie::OBJMesh();
    bunny->load("./Models/stanford/Bunny.obj", true, true);

    aie::OBJMesh* spear = new aie::OBJMesh();
    spear->load("./Models/soulspear/soulspear.obj", true, true);

    // init game objects
    bunnyMove = new tom::OBJobject(vec3(0, 0, 0), bunny, 0.5f);
    boxSpin = new tom::SimpleBox(vec3(0, 5, 0), vec3(2, 1, 1), vec3(1, 1, 0), 1);
    spearSpin = new tom::OBJobject(vec3(5, 2, 0), spear, 0.5f, 0.5f, 1);

    drawHandle = tom::DrawingHandler::instance();
    drawHandle->addtoDraw(new tom::SimpleQuad(glm::vec3(0, 0, 0), glm::vec3(1, 0, 1), 10), tom::shaders::SIMPLE);
    drawHandle->addtoDraw(bunnyMove, tom::shaders::PHONG);
    drawHandle->addtoDraw(spearSpin, tom::shaders::ADVANCED);
    drawHandle->addtoDraw(boxSpin, tom::shaders::PHONG);

    return true;
}


void LibraryTestApp::shutdown()
{
    delete drawHandle;
    delete m_light;
    delete bunnyMove;
    delete boxSpin;
}

void LibraryTestApp::update(float deltaTime)
{
    m_camera->update(deltaTime);

    vec3 newPos = bunnyMove->getPos();
    newPos += glm::vec3(1, 0, 0) * deltaTime;

    vec3 newRotate1 = bunnyMove->getRotation();
    newRotate1 += glm::vec3(0, 1, 0) * deltaTime;

    bunnyMove->setPos(newPos);
    bunnyMove->setRotation(newRotate1);
    bunnyMove->update();

    vec3 newRotate2 = boxSpin->getRotation();
    newRotate2 += glm::vec3(1, -1, 1) * deltaTime;

    vec3 newColour = boxSpin->getColour();
    newColour = vec3(rand() %100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f);

    boxSpin->setColour(newColour);
    boxSpin->setRotation(newRotate2);
    boxSpin->update();

    vec3 newRotate3 = spearSpin->getRotation();
    newRotate3 += glm::vec3(0, 0.5f, 0) * deltaTime;

    spearSpin->setRotation(newRotate3);
    spearSpin->update();


    // quit if we press escape
    aie::Input* input = aie::Input::getInstance();

    if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
        quit();
}

void LibraryTestApp::draw()
{
    clearScreen();

    drawHandle->Draw(m_camera, m_light, m_ambientLight);

}