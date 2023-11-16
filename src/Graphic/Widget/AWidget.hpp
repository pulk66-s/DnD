#pragma once

namespace dnd::graphic::widget
{
    class AWidget {
        protected:
            bool *open = new bool(true);
        public:
            AWidget() {}
            AWidget(bool *open) : open(open) {}
            virtual void display() = 0;
    };
} // namespace dnd::graphic::widget
