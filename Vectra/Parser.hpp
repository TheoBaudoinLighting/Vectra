#pragma once

#include "Engine.hpp"
#include <string>
#include <vector>

namespace Vectra {

    class Parser {
    public:
        explicit Parser(Engine& engine);
        void execute(const std::string& script);

    private:
        void parseLine(const std::vector<std::string>& tokens);
        void parseSpace(const std::vector<std::string>& tokens);
        void parsePoint(const std::vector<std::string>& tokens);
        void parseFold(const std::vector<std::string>& tokens);
        void parseProject(const std::vector<std::string>& tokens);

        Point parsePointDefinition(const std::vector<std::string>& tokens, size_t startIndex);

        Engine& m_engine;
    };
}