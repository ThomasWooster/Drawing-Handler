#include "SimpleQuad.h"

namespace tom
{

    SimpleQuad::SimpleQuad(glm::vec3 pos, glm::vec3 colour, float scale) : SimpleObject(pos, colour)
    {
        m_transform = glm::mat4(scale);
        m_transform[3] = m_pos;
        m_object = new Mesh;
        m_object->initiliseQuad();
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    SimpleQuad::~SimpleQuad()
    {
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    void SimpleQuad::update()
    {
        glm::mat4 translation(1);
        glm::mat4 rotation(1);

        glm::quat rotationQuat = glm::quat(m_rotation); // converts the m_rotation vector into a quaternion

        translation[3] = m_pos;

        rotation = glm::mat4(rotationQuat); // converts the quaternion into a rotation matrix

        m_transform = translation * rotation * m_scale;
    }
}