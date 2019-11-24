#pragma once
#include "SimpleQuad.h"
#include "simpleobject.h"
#include "Shader.h"
#include "BaseCamera.h"
#include "OBJobject.h"
#include <vector>

namespace tom
{
    struct Light // this struct is a directional light. only use one. 
    {
        glm::vec3 direction;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    enum shaders // this enum is used to for identifing shaders
    {
        SIMPLE,
        PHONG,
        ADVANCED,
        TEXLIGHT
    };

    class DrawingHandler
    {
    public:
        static DrawingHandler* instance() // the handler is a singulton. this is how you create the instance
        {
            static DrawingHandler* instance = new DrawingHandler();
            return instance;
        }

        ~DrawingHandler();

        void Draw(BaseCamera* camera, Light* directionalLight, glm::vec3 ambientLight); // this function draws all the objects to the screen and handles all the shader binding
        void addtoDraw(SimpleObject* object, shaders shader); // this function adds a simple object to the drawing handler
        void addtoDraw(OBJobject* object, shaders shader); // this function adds an OBJobject to the drawing handler
        

    private:
        DrawingHandler(); // this constructor is kept private because the class is a singulton. this is so that only the class may create its self
        
        // all the vecters holding the game objects to be drawn
        std::vector<SimpleObject*> m_simpleobject; // simple objects using the simple shader
        std::vector<SimpleObject*> m_phongSimpleOnject; // simple objects using the phong shader
        std::vector<OBJobject*> m_phongObject; // obj objets using the phong shader
        std::vector<OBJobject*> m_advancedObject; // obj objects using the advanced shader
        std::vector<OBJobject*> m_texLightObject; // obj objects using the texlight shader

        //the shaders
        aie::ShaderProgram* m_simple; // a simple shader that applyes colour
        aie::ShaderProgram* m_phong; // a shader that uses phong lighting
        aie::ShaderProgram* m_advanced; // a shader that uses material based rendering, it also applies textures
        aie::ShaderProgram* m_texLight; // a shader that uses phong lighting and applies textures

    };

}

