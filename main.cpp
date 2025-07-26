#include "Vectra/Engine.hpp"
#include "Vectra/Parser.hpp"
#include <iostream>

int main() {
    std::string script = R"(
        ESPACE Initial SUR x
        POINT p1 DANS Initial AVEC { x: -7.5 }
        POINT p2 DANS Initial AVEC { x: 4.0 }

        PLIER EspacePlie DE Initial SUR { x: 0 }

        PROJETER Sortie DE EspacePlie SUR x
    )";

    try {
        Vectra::Engine engine;
        Vectra::Parser parser(engine);

        parser.execute(script);

        std::cout << "## ETAT INITIAL ##" << std::endl;
        engine.getSpace("Initial").print();

        std::cout << "\n## ETAT APRES PLIAGE ##" << std::endl;
        engine.getSpace("EspacePlie").print();

        std::cout << "\n## ETAT APRES PROJECTION ##" << std::endl;
        engine.getSpace("Sortie").print();

    } catch (const std::exception& e) {
        std::cerr << "Erreur fatale Vectra: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}