#include <iostream>

#include "unittest.hpp"
#include "Scene.hpp"


int main(int argc, char* argv[]) {
    string outputFile = "output.png";
    string inputFile = "entities.txt";
    if(argc > 1)
        outputFile = argv[1];
    if(argc > 2)
        inputFile = argv[2];
    Scene myScene(inputFile);
    myScene.createPicture(outputFile);
}