#include "DrawingHandler.h"

namespace tom
{

    DrawingHandler::DrawingHandler()
    {
        //making the shaders
        m_simple = new aie::ShaderProgram();
        m_phong = new aie::ShaderProgram();
        m_advanced = new aie::ShaderProgram();
        m_texLight = new aie::ShaderProgram();

        // loading in the shaders
        m_simple->loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
        m_simple->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");

        m_phong->loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert"); 
        m_phong->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag"); 

        m_advanced->loadShader(aie::eShaderStage::VERTEX, "./shaders/normalmap.vert");
        m_advanced->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/advancedstuff.frag");

        m_texLight->loadShader(aie::eShaderStage::VERTEX, "./shaders/normalmap.vert");
        m_texLight->loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalmap.frag");

        // checking thast the shaders have loaded
        if (m_simple->link() == false)
        {
            printf("Shader Error: %s\n", m_simple->getLastError());
            return;
        }
        if (m_phong->link() == false)
        {
            printf("Shader Error: %s\n", m_phong->getLastError());
            return;
        }
        if (m_advanced->link() == false)
        {
            printf("Shader Error: %s\n", m_advanced->getLastError());
            return;
        }
        if (m_texLight->link() == false)
        {
            printf("Shader Error: %s\n", m_texLight->getLastError());
            return;
        }
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    DrawingHandler::~DrawingHandler()
    {
        delete m_simple;
        delete m_phong;
        delete m_advanced;
        delete m_texLight;
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    void DrawingHandler::Draw(BaseCamera* camera, Light* directionalLight, glm::vec3 ambientLight)
    {
        m_simple->bind();
        glm::mat4 pvm;

        for (size_t i = 0; i < m_simpleobject.size(); i++)
        {
            pvm = camera->getProjectionView() * m_simpleobject[i]->getTransform();

            m_simple->bindUniform("ProjectionViewModel", pvm);
            m_simple->bindUniform("Kd", m_simpleobject[i]->getColour());

            m_simpleobject[i]->getMesh()->draw();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        m_phong->bind();
        for (size_t i = 0; i < m_phongObject.size(); i++)
        {
            pvm = camera->getProjectionView() * m_phongObject[i]->getTransform();

            m_phong->bindUniform("ProjectionViewModel", pvm);
            // lighting information
            m_phong->bindUniform("Ia", ambientLight);
            m_phong->bindUniform("Id", directionalLight->diffuse);
            m_phong->bindUniform("Is", directionalLight->specular);
            m_phong->bindUniform("lightDirection", directionalLight->direction);
            m_phong->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_phongObject[i]->getTransform())));

            // if using coustom colour
            if (m_phongObject[i]->getColour() != glm::vec3(-1))
            {
                m_phong->bindUniform("Kd", m_phongObject[i]->getColour());
            }
            // camera
            m_phong->bindUniform("cameraPosition", camera->getWorldTransform()[3]);

            m_phongObject[i]->getMesh()->draw();
        }
        /////////////////////////////////////////////////////////////////////
        for (size_t i = 0; i < m_phongSimpleOnject.size(); i++)
        {
            pvm = camera->getProjectionView() * m_phongSimpleOnject[i]->getTransform();

            m_phong->bindUniform("ProjectionViewModel", pvm);
            // lighting information
            m_phong->bindUniform("Ia", ambientLight);
            m_phong->bindUniform("Id", directionalLight->diffuse);
            m_phong->bindUniform("Is", directionalLight->specular);
            m_phong->bindUniform("lightDirection", directionalLight->direction);
            m_phong->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_phongSimpleOnject[i]->getTransform())));

            // colour
            m_phong->bindUniform("Kd", m_phongSimpleOnject[i]->getColour());
            m_phong->bindUniform("Ka", m_phongSimpleOnject[i]->getColour() * 0.5f);
            m_phong->bindUniform("Ks", glm::vec3(0));

            m_phong->bindUniform("specularPower", 1.0f);

        
            // camera
            m_phong->bindUniform("cameraPosition", camera->getWorldTransform()[3]);

            m_phongSimpleOnject[i]->getMesh()->draw();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        m_advanced->bind();
        for (size_t i = 0; i < m_advancedObject.size(); i++)
        {
            pvm = camera->getProjectionView() * m_advancedObject[i]->getTransform();

            m_advanced->bindUniform("ProjectionViewModel", pvm);
            // lighting information
            m_advanced->bindUniform("Ia", ambientLight);
            m_advanced->bindUniform("Id", directionalLight->diffuse);
            m_advanced->bindUniform("Is", directionalLight->specular);
            m_advanced->bindUniform("lightDirection", directionalLight->direction);
            m_advanced->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_advancedObject[i]->getTransform())));
            m_advanced->bindUniform("ModelMatrix", m_advancedObject[i]->getTransform());
            m_advanced->bindUniform("roughness", m_advancedObject[i]->getRoughness());
            m_advanced->bindUniform("reflectionCoefficient", m_advancedObject[i]->getReflectionCoefficient());
            // camera
            m_advanced->bindUniform("cameraPosition", camera->getWorldTransform()[3]);

            m_advancedObject[i]->getMesh()->draw();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        m_texLight->bind();
        for (size_t i = 0; i < m_texLightObject.size(); i++)
        {
            pvm = camera->getProjectionView() * m_texLightObject[i]->getTransform();

            m_texLight->bindUniform("ProjectionViewModel", pvm);
            // lighting information
            m_texLight->bindUniform("Ia", ambientLight);
            m_texLight->bindUniform("Id", directionalLight->diffuse);
            m_texLight->bindUniform("Is", directionalLight->specular);
            m_texLight->bindUniform("lightDirection", directionalLight->direction);
            m_texLight->bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_texLightObject[i]->getTransform())));
            m_texLight->bindUniform("ModelMatrix", m_texLightObject[i]->getTransform());
            // camera
            m_texLight->bindUniform("cameraPosition", camera->getWorldTransform()[3]);

            m_texLightObject[i]->getMesh()->draw();
        }
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    void DrawingHandler::addtoDraw(tom::SimpleObject* object, shaders shader)
    {
        switch (shader) // the shaders enum is used to decide what vector(dynamic array) the object is sorted into
        {
        case tom::PHONG:
            m_phongSimpleOnject.push_back(object);
            break;
        case tom::SIMPLE:
            m_simpleobject.push_back(object);
            break;
        default: // if they dont use a valid shader is crashes here, rather that some weird shader shenanigans
            assert(false);
            break;
        }
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    void DrawingHandler::addtoDraw(tom::OBJobject* object, shaders shader)
    {
        switch (shader) // the shaders enum is used to decide what vector(dynamic array) the object is sorted into
        {
        case tom::PHONG:
            m_phongObject.push_back(object);
            break;
        case tom::ADVANCED:
            m_advancedObject.push_back(object);
            break;
        case tom::TEXLIGHT:
            m_texLightObject.push_back(object);
            break;
        default: // if they dont use a valid shader is crashes here, rather that some weird shader shenanigans
            assert(false);
            break;
        }
    }

}