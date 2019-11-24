#pragma once
#include "simpleobject.h"

namespace tom
{

    class SimpleBox : public SimpleObject
    {
    public:
        SimpleBox(glm::vec3 pos, glm::vec3 extents, glm::vec3 colour, float scale); // uses the cube mesh initiliser
        virtual ~SimpleBox();

        virtual void update(); // see parent
    };

}