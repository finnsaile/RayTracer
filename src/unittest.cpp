#include <vector>
#include <iostream>
#include <map>

#include "Scene.hpp"
#include "Screen.hpp"
#include "unittest.hpp"

#define BLACK "\u001b[30m"
#define RED "\u001b[31m"
#define GREEN "\u001b[32m"
#define YELLOW "\u001b[33m"
#define BLUE "\u001b[34m"
#define MAGENTA "\u001b[35m"
#define CYAN "\u001b[36m"
#define WHITE "\u001b[37m"
#define RESET "\u001b[0m"

using std::vector, std::map;
using std::cout, std::endl;
using std::string;
using Eigen::Vector2d;


#define TEST

// void ut::RunTests() {
//     map<string, bool (*)()> testMap = {{"ScreenTest1", ScreenTest1}, 
//                                         {"GetVecFromLineTest1", GetVecFromLineTest1}, 
//                                         {"GetVecFromLineTest2", GetVecFromLineTest2}};

//     for(auto& t : testMap) {
//         cout << BLUE << t.first << ": " RESET << (t.second() ? (GREEN "PASSSED") : (RED "FAILED")) << RESET << "\n" << endl;
//     }
// }

// bool ut::ScreenTest1() {
//     vector<vector<Eigen::Vector3i>> expected = 
//                                         {{{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}},
//                                          {{0, -1, 0}, {1, -1, 0}, {2, -1, 0}, {3, -1, 0}},
//                                          {{0, -2, 0}, {1, -2, 0}, {2, -2, 0}, {3, -2, 0}},
//                                          {{0, -3, 0}, {1, -3, 0}, {2, -3, 0}, {3, -3, 0}}};

//     vector<vector<Eigen::Vector3i>> result(4, vector<Eigen::Vector3i>(4));

//     Screen testScreen(Point({0, 0, 0}), Vec({0, 0, 1}, {0, 0, 0}), 4, 4, 4, 4, true);
    
//     for(int i = 0; i < 4; i++) {
//         for(int j = 0; j < 4; j++) {
//             result[i][j] = testScreen.getPixelLocation(i, j).ori().cast<int>();
//         }
//     }

//     #ifdef TESTOUTPUT
//     cout << endl<< endl;
//     map<string, vector<vector<Eigen::Vector3i>>> testMap = {{"Expected:", expected}, {"Result:", result}};
    
//     for(auto& v : testMap) {
//         cout << v.first << endl;
//         for(auto& v1 : v.second) {
//             for(auto& v2 : v1) {
//                 cout << "{";
//                 for(auto& v3 : v2) {
//                     cout << v3 << " ";
//                 }
//                 cout << "\b}" << " ";;
//             }
//             cout << endl;
//         }
//         cout << endl;
//     }
//     #endif
//     return expected == result;
// }

// bool ut::GetVecFromLineTest1() {
//     bool testPass = true;
//     struct testStorage3d {
//         string testLine;
//         string testHandle;
//         Vector3d expected;
//         Vector3d result;
//     };

//     vector<testStorage3d> vec3d =  {{"pos: 3 1 -3", "pos:", {3, 1, -3}},
//                                     {"n: 12 -31 -1", "n:", {12, -31, -1}},
//                                     {"rgb: 0 123 45", "rgb:", {0, 123, 45}}};
//     #ifdef TESTOUTPUT
//     cout << "\n\nExpected:   Result:" << endl; 
//     #endif
//     for(auto& t : vec3d) {
//         t.result = vecTrans::getVecFromLine<Vector3d>(t.testHandle, t.testLine);
//         #ifdef TESTOUTPUT
//         cout << "{";
//         for(auto& i : t.expected) 
//             cout << i  << ", ";
//         cout << "\b\b}";

//         cout << "  {";
//         for(auto& i : t.result) 
//             cout << i  << ", ";
//         cout << "\b\b}\n" << endl;
//         #endif
//         if(t.result != t.expected)
//             testPass = false;
//     }

//     return testPass;
// }

// bool ut::GetVecFromLineTest2() {
//     bool testPass = true;
//     struct testStorage2d {
//         string testLine;
//         string testHandle;
//         Vector2d expected;
//         Vector2d result;
//     };

//     vector<testStorage2d> vec2d =  {{"w/h: 10 15", "w/h:", {10, 15}},
//                                     {"w/h: -32 -31", "w/h:", {-32, -31}},
//                                     {"xr/yr: 12 634", "xr/yr:", {12, 634}},
//                                     {"xr/yr: -63 -41", "xr/yr:", {-63, -41}}};
//     #ifdef TESTOUTPUT
//     cout << "\n\nExpected:   Result:" << endl; 
//     #endif
//     for(auto& t : vec2d) {
//         t.result = vecTrans::getVecFromLine<Vector2d>(t.testHandle, t.testLine);
//         #ifdef TESTOUTPUT
//         cout << "{";
//         for(auto& i : t.expected) 
//             cout << i  << ", ";
//         cout << "\b\b}";

//         cout << "  {";
//         for(auto& i : t.result) 
//             cout << i  << ", ";
//         cout << "\b\b}\n" << endl;
//         #endif
//         if(t.result != t.expected)
//             testPass = false;
//     }

//     return testPass;
// }