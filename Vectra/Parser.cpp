#include "Parser.hpp"
#include <sstream>
#include <iostream>
#include <algorithm>

namespace Vectra {

    Parser::Parser(Engine& engine) : m_engine(engine) {}

    void Parser::execute(const std::string& script) {
        std::stringstream script_stream(script);
        std::string line;
        int line_num = 0;

        while (std::getline(script_stream, line)) {
            line_num++;
            line.erase(std::remove(line.begin(), line.end(), ','), line.end());
            std::stringstream line_stream(line);
            std::vector<std::string> tokens;
            std::string token;
            while (line_stream >> token) {
                tokens.push_back(token);
            }

            if (!tokens.empty()) {
                try {
                    parseLine(tokens);
                } catch (const std::exception& e) {
                    std::cerr << "Erreur a la ligne " << line_num << ": " << e.what() << std::endl;
                    return;
                }
            }
        }
    }

    void Parser::parseLine(const std::vector<std::string>& tokens) {
        const auto& keyword = tokens[0];
        if (keyword == "ESPACE") parseSpace(tokens);
        else if (keyword == "POINT") parsePoint(tokens);
        else if (keyword == "PLIER") parseFold(tokens);
        else if (keyword == "PROJETER") parseProject(tokens);
        else throw std::runtime_error("Mot-cle inconnu: " + keyword);
    }

    void Parser::parseSpace(const std::vector<std::string>& tokens) {
        if (tokens.size() < 4 || tokens[2] != "SUR") {
            throw std::runtime_error("Syntaxe ESPACE invalide. Attendu: ESPACE <nom> SUR <axe1> ...");
        }
        std::vector<std::string> axes;
        for (size_t i = 3; i < tokens.size(); ++i) {
            axes.push_back(tokens[i]);
        }
        m_engine.createSpace(tokens[1], axes);
    }

    Point Parser::parsePointDefinition(const std::vector<std::string>& tokens, size_t startIndex) {
        if (tokens.size() < startIndex + 3 || tokens[startIndex] != "{") {
             throw std::runtime_error("Definition de point invalide.");
        }
        Point p;
        size_t i = startIndex + 1;
        while(i < tokens.size() && tokens[i] != "}") {
            std::string axis = tokens[i];
            if(axis.back() != ':') throw std::runtime_error("Axe doit finir par ':'.");
            axis.pop_back();
            i++;
            if(i >= tokens.size()) throw std::runtime_error("Valeur manquante pour l'axe " + axis);
            p.coords[axis] = std::stod(tokens[i]);
            i++;
        }
        return p;
    }

    void Parser::parsePoint(const std::vector<std::string>& tokens) {
        if (tokens.size() < 6 || tokens[2] != "DANS" || tokens[4] != "AVEC") {
            throw std::runtime_error("Syntaxe POINT invalide. Attendu: POINT <nom> DANS <espace> AVEC { axe: val ... }");
        }
        Point p = parsePointDefinition(tokens, 5);
        m_engine.addPoint(tokens[3], p);
    }

    void Parser::parseFold(const std::vector<std::string>& tokens) {
        if (tokens.size() < 6 || tokens[2] != "DE" || tokens[4] != "SUR") {
            throw std::runtime_error("Syntaxe PLIER invalide. Attendu: PLIER <nouvel_espace> DE <espace_source> SUR { axe: val ... }");
        }
        Point hyperplane = parsePointDefinition(tokens, 5);
        m_engine.fold(tokens[1], tokens[3], hyperplane);
    }

    void Parser::parseProject(const std::vector<std::string>& tokens) {
        if (tokens.size() != 6 || tokens[2] != "DE" || tokens[4] != "SUR") {
            throw std::runtime_error("Syntaxe PROJETER invalide. Attendu: PROJETER <nouvel_espace> DE <espace_source> SUR <axe>");
        }
        m_engine.project(tokens[1], tokens[3], tokens[5]);
    }
}