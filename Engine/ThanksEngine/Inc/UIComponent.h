#pragma once

#include "Component.h"

namespace ThanksEngine
{
    class UIComponent : public Component
    {
    public:
        virtual void Render() = 0;
    };
}