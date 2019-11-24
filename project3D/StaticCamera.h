#pragma once
#include "BaseCamera.h"

namespace tom
{

    
    class StaticCamera : public BaseCamera
    {
    public:
        StaticCamera();
        virtual ~StaticCamera();

        virtual void update(float deltatime); // this updates its viewing direction but is not changed by input

    };

}