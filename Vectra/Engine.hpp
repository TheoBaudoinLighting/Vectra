#pragma once

#include "Core.hpp"
#include <map>
#include <string>
#include <memory>

namespace Vectra {

    class Engine {
    public:
        void createSpace(const std::string& name, const std::vector<std::string>& axes);
        void addPoint(const std::string& spaceName, Point point);
        void fold(const std::string& newSpaceName, const std::string& sourceSpaceName, const Point& hyperplane);
        void project(const std::string& newSpaceName, const std::string& sourceSpaceName, const std::string& axis);

        const Space& getSpace(const std::string& name) const;
        bool hasSpace(const std::string& name) const;

    private:
        std::map<std::string, std::unique_ptr<Space>> m_spaces;
    };

}