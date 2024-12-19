#include <iostream>
#include <nlohmann/json.hpp>

#include "scene.h"

using nlohmann::json;
using std::string;

int main(int argc, char* argv[]) {
  string output_file = "output.png";
  string input_file =
      "/Users/finnsaile/Documents/GitHub/RayTracer/entities.json";
  if (argc > 1) output_file = argv[1];
  if (argc > 2) input_file = argv[2];
  Scene scene;
  try {
    scene.ReadEntities(input_file);
  } catch (json::exception e) {
    std::cout << "Error occured while creating scene:" << e.what() << std::endl;
    return 1;
  };

  scene.CreatePicture(output_file);
}