#pragma once

namespace Components {
    struct Tile : public Object {

        std::string ToString() const override {
            std::stringstream str;
            str << "    Component: Tile \n";

            return str.str();
        }
    };
}