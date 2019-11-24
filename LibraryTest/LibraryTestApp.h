#pragma once

#include "Application.h"
#include <FlyCamera.h>
#include <DrawingHandler.h>
#include <glm/mat4x4.hpp>

class LibraryTestApp : public aie::Application {
public:

	LibraryTestApp();
	virtual ~LibraryTestApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

    //drawing handler (singlton)
    tom::DrawingHandler* drawHandle = nullptr;

    // camera used to see things
    tom::BaseCamera* m_camera;

    // direction light
    tom::Light* m_light;
    glm::vec3 m_ambientLight;


	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

    // actors for demo

    tom::OBJobject* bunnyMove;
    tom::SimpleObject* boxSpin;
    tom::OBJobject* spearSpin;
};