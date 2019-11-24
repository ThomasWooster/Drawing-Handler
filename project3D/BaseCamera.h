#pragma once
#include <glm/ext.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace tom
{

    // base camra class that other cameras types can be made from
    class BaseCamera
    {
    public:
        BaseCamera();
        virtual ~BaseCamera();

        // this function must be overwridden by a child class
        virtual void update(float deltatime) = 0;

        // this block allowes for the setting and modification of the values that all cameras need
        void setPerspective(float FOV, float aspectRatio, float near, float far) { m_projectionTransform = glm::perspective(FOV, aspectRatio, near, far); }
        void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up) { m_viewTransform = glm::lookAt(from, to, up); }
        void setPosition(glm::vec3 pos) { m_worldTransform[3] = glm::vec4(pos.x, pos.y, pos.z, 0); }
        void setRotation(glm::vec3 rotation) { m_rotation = rotation; }

        glm::mat4 getWorldTransform() { return m_worldTransform; }
        glm::mat4 getView() { return m_viewTransform; }
        glm::mat4 getProjection() { return m_projectionTransform; }
        glm::mat4 getProjectionView() { return m_projectionViewTransform; }

        // once any changes have been made this fuction needs to be called to apply the chages to the camera: ie. at the end of the update function
        void updateProjectionView();

    protected:

        glm::mat4 m_worldTransform;
        glm::mat4 m_viewTransform;
        glm::mat4 m_projectionTransform;
        glm::mat4 m_projectionViewTransform;
        glm::vec3 m_rotation;

    };

}