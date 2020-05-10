#pragma once
#include "functions.hpp"
#include <vector>
#include <iostream>
class Tetr{
public:
    std::vector <unsigned char> color;
    std::vector <std::vector <int> > coord;
    Tetr(){
        color={255,0,0};
        coord.push_back({0,0,1}); coord.push_back({0,1,0});coord.push_back({1,0,0});coord.push_back({0,0,0});
    }
    Tetr(std::vector <std::vector <int> >& vect,std::vector <unsigned char>& col){
        coord=vect;
        color=col;
    }
    Tetr(std::string tmpString){
        std::stringstream strStream;
        strStream << tmpString;
        char garb;int x1=0,x2=0,x3=0;
        for (int i=0;i<4;i++){
            x1=0;x2=0;x3=0;
            strStream >> x1 >> garb >> x2 >> garb >> x3 ;
            coord.push_back({x1,x2,x3});
        }
        strStream >> x1 >> garb >> x2 >> garb >> x3 >> garb;
        color.push_back(x1);  color.push_back(x2); color.push_back(x3);
    }
    double Check_edge(int xyz[3],double abc[3], int n1, int n2, int n3){
        int v1[3]={coord[n1][0],coord[n1][1],coord[n1][2]};
        int v2[3]={coord[n2][0],coord[n2][1],coord[n2][2]};
        int v3[3]={coord[n3][0],coord[n3][1],coord[n3][2]};
        return intersect_triangle(xyz,abc,v1,v2,v3);
    }
    std::pair < double, std::vector <unsigned char> > Check_all(int xyz[3],double abc[3]){
        double d1=Check_edge(xyz,abc,0,1,2);double d2=Check_edge(xyz,abc,0,1,3);double d3=Check_edge(xyz,abc,0,2,3);double d4=Check_edge(xyz,abc,1,2,3);
        double mind;
        if (d1>0) mind=d1;else if (d2>0) mind=d2;else if (d3>0) mind=d3; else mind=d4;
        if (d1>0 && d1<mind) {mind=d1;} if (d2>0 && d2<mind) {mind=d2;} if (d3>0 && d3<mind) {mind=d3;} if (d4>0 && d4<mind) {mind=d4;}
        return make_pair(mind,color);
    }
};
