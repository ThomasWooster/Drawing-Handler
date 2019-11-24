#pragma once
#include "simpleobject.h"

namespace tom
{
    class SimpleQuad : public SimpleObject
    {
    public:
        SimpleQuad(glm::vec3 pos, glm::vec3 colour, float scale); // uses the quad mesh initiliser
        virtual ~SimpleQuad();

        virtual void update(); // see parent

    protected:
    };

}