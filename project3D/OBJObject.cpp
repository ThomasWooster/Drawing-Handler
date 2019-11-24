#include "OBJobject.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>

namespace tom
{

    OBJobject::OBJobject(glm::vec3 pos, aie::OBJMesh* object, float scale)
    {
        m_scale = glm::mat4(scale);
        m_transform = m_scale;
        m_pos = glm::vec4(pos, 1);
        m_transform[3] = m_pos;
        m_object = object;

        m_rotation = glm::vec3(0);
    }
    OBJobject::OBJobject(glm::vec3 pos, aie::OBJMesh* object, glm::vec3 colour, float scale)
    {
        m_scale = glm::mat4(scale);
        m_transform = m_scale;
        m_pos = glm::vec4(pos, 1);
        m_transform[3] = m_pos;
        m_object = object;
        m_colour = colour;

        m_rotation = glm::vec3(0);
    }
    OBJobject::OBJobject(glm::vec3 pos, aie::OBJMesh* object, float roughness, float reflectioncoefficient, float scale)
    {
        m_scale = glm::mat4(scale);
        m_transform = m_scale;
        m_pos = glm::vec4(pos, 1);
        m_transform[3] = m_pos; 
        m_object = object;

        m_roughness = roughness;
        m_reflectionCoefficent = reflectioncoefficient;

        m_rotation = glm::vec3(0);
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    OBJobject::~OBJobject()
    {
        delete m_object;
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    void OBJobject::update()
    {
        glm::mat4 translation(1);
        glm::mat4 rotation(1);

        glm::quat rotationQuat = glm::quat(m_rotation);// converts the m_rotation vector into a quaternion

        translation[3] = m_pos;

        rotation = glm::mat4(rotationQuat); // converts the quaternion into a rotation matrix

        m_transform = translation * rotation * m_scale;
    }

}