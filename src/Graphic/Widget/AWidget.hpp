#pragma once

namespace dnd::graphic::widget
{
    class AWidget {
        protected:
            AWidget() {};
        public:
            virtual void display() = 0;
    };
} // namespace dnd::graphic::widget
