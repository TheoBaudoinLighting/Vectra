#include "Core.hpp"

namespace Vectra {

    Space::Space(std::vector<std::string> axes_names) : m_axes(std::move(axes_names)) {}

    void Space::addPoint(Point p) {
        m_points.push_back(std::move(p));
    }

    const std::vector<Point>& Space::getPoints() const {
        return m_points;
    }

    const std::vector<std::string>& Space::getAxes() const {
        return m_axes;
    }

    void Space::print() const {
        std::cout << "--- SPACE ---\n";
        std::cout << "  Axes: ";
        for(const auto& axis : m_axes) std::cout << axis << " ";
        std::cout << "\n  Points:\n";
        int i = 0;
        for(const auto& point : m_points) {
            std::cout << "    Point " << i++ << " { ";
            for(const auto& [axis, val] : point.coords) {
                std::cout << axis << ": ";
                std::visit([](auto&& arg){ std::cout << arg; }, val);
                std::cout << " ";
            }
            std::cout << "}\n";
        }
        std::cout << "-------------\n";
    }
}