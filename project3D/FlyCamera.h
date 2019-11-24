#pragma once

#include "BaseCamera.h"

namespace tom
{

    // camera used to fly around the scene to get a good look at what you are doing
    class FlyCamera : public BaseCamera
    {
    public:
        FlyCamera();
        virtual ~FlyCamera();

        virtual void update(float deltatime); // updates the cameras lookat target based on the new position and rotation

        void setSpeed(float speed) { m_speed = speed; }

    protected:
        float m_speed; // how fast the camera mooves and turns
        glm::vec3 m_up; // which axies is "up" for the camera
    };

}