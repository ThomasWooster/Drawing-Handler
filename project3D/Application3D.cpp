#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include "DrawingHandler.h"
#include "SimpleQuad.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

bool Application3D::startup() {
	
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

    m_light = new tom::Light();
    m_light->diffuse = { 0.8, 0.8, 0.8 };
    m_light->specular = { 1, 1 , 1 };
    m_light->direction = {0, -1, 1};
    m_ambientLight = { 0.5f, 0.5f, 0.5f };

    aie::OBJMesh* bunny = new aie::OBJMesh();
    bunny->load("./Models/stanford/Bunny.obj", true, true);

    aie::OBJMesh* spear = new aie::OBJMesh();
    spear->load("./Models/soulspear/soulspear.obj", true, true);

    drawHandle = tom::DrawingHandler::instance(); 
    drawHandle->addtoDraw(new tom::SimpleQuad(glm::vec3(0, 0, 0), glm::vec3(1, 0, 1), 10));
    drawHandle->addtoDraw(new tom::OBJobject(vec3(0, 2, 0), bunny), tom::shaders::PHONG);
    drawHandle->addtoDraw(new tom::OBJobject(vec3(5, 2, 0), spear, 0.5f, 0.5f), tom::shaders::ADVANCED);



	return true;
}


void Application3D::shutdown() 
{
    
}

void Application3D::update(float deltaTime) 
{
    m_camera->update(deltaTime);


    // quit if we press escape
    aie::Input* input = aie::Input::getInstance();

    if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
        quit();
}

void Application3D::draw() 
{
    clearScreen();

   drawHandle->Draw(m_camera, m_light, m_ambientLight);

}