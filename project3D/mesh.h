#pragma once
#include <glm/ext.hpp>

namespace tom
{

    class Mesh
    {
    public:

        Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {} // constructor is in header
        virtual ~Mesh();

        struct Vertex // this struck is used to hold all the information required for the vetexes, for use in vertex and fragment shaders
        {
            glm::vec4 position; // the location of the vertex in relation to the mesh
            glm::vec4 normal; // the direction of the normal
            glm::vec2 texCoord; // the texture coord mapping
        };

        void initiliseQuad(); // makes the mesh a quad
        void initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr); // makes a custom mesh using the inputs
        void initialiseFullscreenQuad(); // makes the mesh a full screen quad for use with post prossessing effects
        void initializeCube(); // makes the mesh a cube

        virtual void draw(); // draws the mesh to the screen using the bound shader

    protected:

        unsigned int triCount; // how many triangles are in the mesh
        unsigned int vao, vbo, ibo;// vertex array object, vertex buffer object, index buffer object. 
    };

}