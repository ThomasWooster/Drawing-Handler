#include "simpleBox.h"

namespace tom
{

    SimpleBox::SimpleBox(glm::vec3 pos, glm::vec3 extents, glm::vec3 colour, float scale) : SimpleObject(pos, colour)
    {
        m_scale = glm::mat4(scale);
        m_scale[0][0] *= extents.x;
        m_scale[1][1] *= extents.y;
        m_scale[2][2] *= extents.z;
        m_transform = m_scale;
        m_pos = glm::vec4(pos, 1);
        m_transform[3] = m_pos;
        m_object = new Mesh();
        m_object->initializeCube();
        m_rotation = glm::vec3(0);

    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    SimpleBox::~SimpleBox()
    {
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    void SimpleBox::update()
    {
        glm::mat4 translation(1);
        glm::mat4 rotation(1);

        glm::quat rotationQuat = glm::quat(m_rotation);// converts the m_rotation vector into a quaternion

        translation[3] = m_pos;

        rotation = glm::mat4(rotationQuat);// converts the quaternion into a rotation matrix

        m_transform = translation * rotation * m_scale;
    }
}
