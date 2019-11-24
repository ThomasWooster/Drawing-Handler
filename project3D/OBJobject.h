#pragma once
#include "OBJMesh.h"
#include <glm/mat4x4.hpp>

namespace tom
{

    class OBJobject
    {
    public:
        OBJobject(glm::vec3 pos, aie::OBJMesh* object, float scale); // constructor for objs using phong, texture shader and built in colour
        OBJobject(glm::vec3 pos, aie::OBJMesh* object, glm::vec3 colour, float scale); // constructior for objs using phong and texture shader
        OBJobject(glm::vec3 pos, aie::OBJMesh* object, float roughness, float reflectioncoefficient, float scale); // constructor used for material based shader
        virtual ~OBJobject();

        glm::mat4 getTransform() { return m_transform; }
        glm::vec3 getPos() { return glm::vec3(m_pos[0], m_pos[1], m_pos[2]); }
        glm::vec3 getColour() { return m_colour; }
        aie::OBJMesh* getMesh() { return m_object; }
        glm::vec3 getRotation() { return m_rotation; }
        float getRoughness() { return m_roughness; }
        float getReflectionCoefficient() { return m_reflectionCoefficent; }

        void setPos(glm::vec3 position) { m_pos = glm::vec4(position, 1); }
        void setColour(glm::vec3 colour) { m_colour = colour; }
        void setRotation(glm::vec3 rotation) { m_rotation = rotation; }
        void setRoughness(float roughness) { m_roughness = roughness; }
        void setReflectionCoefficient(float reflectionCoefficient) { m_reflectionCoefficent = reflectionCoefficient; }

        void update(); // // applyes changes made to the transform, place at the end of update functions

    protected:
        glm::mat4 m_transform; // matri4 that holds the locational, rotational and scale information
        glm::mat4 m_scale; // scale matix used in update function
        glm::vec4 m_pos; // holds the position of the object, asessed through set and get functions. applyed to m_transform in the update function
        glm::vec3 m_colour; // holds the colour of the object
        glm::vec3 m_rotation; // in radians
        float m_roughness; // used in the advanced shader, it changes how mush the light is diffused/scatterd in the surface (roughness)
        float m_reflectionCoefficent; // used in the advanced shader, it changes how much light is reflected of the surface (shinyness)

        aie::OBJMesh* m_object;
    };

}