#include <sstream>
#include <fstream>
#include "CImg.h"
#include <vector>
#include <cmath>
#include <iostream>
#include "tetr.hpp"
#include "screen.hpp"
#include "omp.h"
#include <ctime>
int main() {
    const std::string inputFileName_main = "input_main.txt";
    const std::string inputFileName_tetr = "input_tetr.txt";
    std::ifstream inputFile_tetr(inputFileName_tetr.c_str(), std::ios_base::in);
    if (!inputFile_tetr.is_open()) {
        throw std::invalid_argument("Error! Cannot open file " + inputFileName_tetr + "!\n");
    }
    std::vector < Tetr* > tetraedrs;
    std::string tmpString;
    while (std::getline(inputFile_tetr, tmpString)) {
        tetraedrs.push_back(new Tetr(tmpString));
    }
    Screen screen(inputFileName_main);
    Screen screen2(inputFileName_main);
    unsigned int start_time =  clock();
    screen.Draw(tetraedrs);
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    start_time =  clock();
    screen2.Draw2(tetraedrs);
    end_time = clock();
    unsigned int search_time2 = end_time - start_time;
    std::cout<<search_time<<" : "<<search_time2<<std::endl;
    screen.img->save_bmp("Pikcha.bmp");
    screen2.img->display();
    for (int i=0; i<tetraedrs.size();i++){
        delete tetraedrs[i];
    }
    return 0;
}
