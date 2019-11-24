#include "StaticCamera.h"

namespace tom
{

    StaticCamera::StaticCamera()
    {

    }

    /**************************************************************************************************************************************
    **************************************************************************************************************************************/

    StaticCamera::~StaticCamera()
    {

    }

    /**************************************************************************************************************************************
    **************************************************************************************************************************************/

    void StaticCamera::update(float deltatime)
    {

        // the following code makes it sot he camera looks upwards
        glm::quat newR(m_rotation);

        m_worldTransform = glm::mat4(newR);

        setLookAt(m_worldTransform[3], m_worldTransform[2] + m_worldTransform[3], glm::vec3(0, 1, 0));

        updateProjectionView();
    }

}