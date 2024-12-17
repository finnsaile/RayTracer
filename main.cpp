#include <iostream>
#include <nlohmann/json.hpp>

#include "Scene.hpp"

using nlohmann::json;

int main(int argc, char* argv[]) {
    string outputFile = "output.png";
    string inputFile = "/Users/finnsaile/Documents/GitHub/RayTracer/entities.json";
    if(argc > 1)
        outputFile = argv[1];
    if(argc > 2)
        inputFile = argv[2];
    Scene myScene;
    try {
        myScene.readEntities(inputFile);
    } catch (json::exception e) {
        std::cout << "Error occured while creating scene:" << e.what() << std::endl;
        return 1;
    };

    myScene.createPicture(outputFile);
}