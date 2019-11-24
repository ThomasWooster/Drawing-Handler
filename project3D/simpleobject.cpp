#include "simpleobject.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>

namespace tom
{

    SimpleObject::SimpleObject(glm::vec3 pos, glm::vec3 colour)
    {
        m_pos = glm::vec4(pos, 1);
        m_transform = glm::mat4(1);
        m_colour = colour;
        m_transform[3] = m_pos;
    }

    /******************************************************************************************************************************************************
    ******************************************************************************************************************************************************/

    SimpleObject::~SimpleObject()
    {
        delete m_object;
    }

}