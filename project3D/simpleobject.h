#pragma once
#include "mesh.h"
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace tom 
{
    class SimpleObject
    {
    public:
        SimpleObject(glm::vec3 pos, glm::vec3 colour);
        virtual ~SimpleObject();

        glm::mat4 getTransform() { return m_transform; }
        glm::vec3 getColour() { return m_colour; }
        glm::vec3 getPos() { return glm::vec3(m_pos[0], m_pos[1], m_pos[2]); }
        glm::vec3 getRotation() { return m_rotation; }
        Mesh* getMesh() { return m_object; }

        void setColour(glm::vec3 colour) { m_colour = colour; }
        void setPos(glm::vec3 position) { m_pos = glm::vec4(position, 1); }
        void setRotation(glm::vec3 rotationXYZ) { m_rotation = rotationXYZ; } 

        virtual void update() = 0; // applyes changes made to the transform, place at the end of update functions

    protected:
        glm::mat4 m_transform; // matri4 that holds the locational, rotational and scale information
        glm::mat4 m_scale; // scale matix used in update function
        glm::vec4 m_pos; // holds the position of the object, asessed through set and get functions. applyed to m_transform in the update function
        glm::vec3 m_colour; // holds the colour of the object
        glm::vec3 m_rotation; // in radians
        Mesh* m_object; // holds the mesh information for the object ( vector points, normals, tex coords)

    };

}

