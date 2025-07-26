#pragma once

#include <string>
#include <vector>
#include <variant>
#include <map>
#include <iostream>
#include <stdexcept>
#include <memory>

namespace Vectra {

    using Value = std::variant<double, std::string>;

    struct Point {
        std::map<std::string, Value> coords;
    };

    class Space {
    public:
        explicit Space(std::vector<std::string> axes_names);
        void addPoint(Point p);
        const std::vector<Point>& getPoints() const;
        const std::vector<std::string>& getAxes() const;
        void print() const;

    private:
        std::vector<std::string> m_axes;
        std::vector<Point> m_points;
    };

}