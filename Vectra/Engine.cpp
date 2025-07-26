#include "Engine.hpp"

namespace Vectra {

    void Engine::createSpace(const std::string& name, const std::vector<std::string>& axes) {
        m_spaces[name] = std::make_unique<Space>(axes);
    }

    void Engine::addPoint(const std::string& spaceName, Point point) {
        if (!hasSpace(spaceName)) {
            throw std::runtime_error("Espace introuvable: " + spaceName);
        }
        m_spaces.at(spaceName)->addPoint(std::move(point));
    }

    void Engine::fold(const std::string& newSpaceName, const std::string& sourceSpaceName, const Point& hyperplane) {
        const auto& sourceSpace = getSpace(sourceSpaceName);
        createSpace(newSpaceName, sourceSpace.getAxes());
        auto& newSpace = *m_spaces.at(newSpaceName);

        for (const auto& p : sourceSpace.getPoints()) {
            Point newPoint = p;
            for (const auto& [axis, foldValue] : hyperplane.coords) {
                if (newPoint.coords.count(axis)) {
                    double pointValue = std::get<double>(newPoint.coords.at(axis));
                    double foldLine = std::get<double>(foldValue);
                    if (pointValue < foldLine) {
                        newPoint.coords[axis] = foldLine + (foldLine - pointValue);
                    }
                }
            }
            newSpace.addPoint(newPoint);
        }
    }

    void Engine::project(const std::string& newSpaceName, const std::string& sourceSpaceName, const std::string& axis) {
        const auto& sourceSpace = getSpace(sourceSpaceName);
        createSpace(newSpaceName, {axis});
        auto& newSpace = *m_spaces.at(newSpaceName);

        for (const auto& p : sourceSpace.getPoints()) {
            if(p.coords.count(axis)) {
                Point projectedPoint;
                projectedPoint.coords[axis] = p.coords.at(axis);
                newSpace.addPoint(projectedPoint);
            }
        }
    }

    const Space& Engine::getSpace(const std::string& name) const {
        if (!hasSpace(name)) {
            throw std::runtime_error("Espace introuvable a l'acces: " + name);
        }
        return *m_spaces.at(name);
    }

    bool Engine::hasSpace(const std::string& name) const {
        return m_spaces.count(name);
    }
}