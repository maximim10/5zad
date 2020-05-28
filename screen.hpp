#include <cmath>
#include <vector>
#include <cmath>
class Screen{
public:
    cimg_library::CImg <unsigned char>* img;
    int xyz[3];
    double norm[3];
    double up[3];
    double third[3];
    int alpha;
    int w;
    int lim;
    int h;
    int dist;
    double scale;
    bool overlay;
    Screen (const std::string inputFileName_main){
        std::ifstream inputFile_main(inputFileName_main.c_str(), std::ios_base::in);
        if (!inputFile_main.is_open()) {
            throw std::invalid_argument("Error! Cannot open file " + inputFileName_main + "!\n");
        }
        std::string tmpString;
        std::getline(inputFile_main, tmpString);
        std::stringstream strStream;
        strStream << tmpString;
        strStream >> xyz[0]>>xyz[1]>>xyz[2];
        std::cout << "1= "<<xyz[0]<<" "<<xyz[1]<<" "<<xyz[2]<<std::endl; std::getline(inputFile_main, tmpString);
        strStream << tmpString;
        strStream >> norm[0]>>norm[1]>>norm[2];
        std::cout << "2= "<<norm[0]<<" "<<norm[1]<<" "<<norm[2]<<std::endl; std::getline(inputFile_main, tmpString);
        strStream << tmpString;
        strStream >> up[0]>>up[1]>>up[2];
        std::cout << "3= "<<up[0]<<" "<<up[1]<<" "<<up[2]<<std::endl; std::getline(inputFile_main, tmpString);
        strStream << tmpString;
        strStream >> dist >> lim >> alpha;
        std::cout << "4= "<<dist<<" "<<lim<<" "<<alpha<<std::endl; std::getline(inputFile_main, tmpString);
        strStream << tmpString;
        strStream >> w>>h;
        std::cout << "w,h= "<<w<<" "<<h;
        double leng=std::sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);
        norm[0]=norm[0]/leng; norm[1]=norm[1]/leng; norm[2]=norm[2]/leng;
        leng=std::sqrt(up[0]*up[0]+up[1]*up[1]+up[2]*up[2]);
        up[0]=up[0]/leng; up[1]=up[1]/leng; up[2]=up[2]/leng;
        third[0]=norm[1]*up[2]-norm[2]*up[1]; third[1]=norm[2]*up[0]-norm[0]*up[2]; third[2]=norm[0]*up[1]-norm[1]*up[0];
        leng=std::sqrt(third[0]*third[0]+third[1]*third[1]+third[2]*third[2]);
        third[0]=third[0]/leng; third[1]=third[1]/leng; third[2]=third[2]/leng;
        scale = (dist * std::tan(asin(1)*2*alpha/360)) / (static_cast<double>(h)/2);
        img=new cimg_library::CImg <unsigned char> (h,w,1,3);
    }
    void Draw(std::vector <Tetr*> & tetraedrs){
        std::vector <unsigned char> cur_col;
        double norm_pl[3]={norm[0]*dist,norm[1]*dist,norm[2]*dist};
        double cur_direction[3];
        std::pair <double, std::vector <unsigned char> > time_color;
        for (int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                cur_direction[0]=norm_pl[0]+up[0]*(static_cast<double>(h)/2-i)*scale+third[0]*(static_cast<double>(w)/2-j)*scale;
                cur_direction[1]=norm_pl[1]+up[1]*(static_cast<double>(h)/2-i)*scale+third[1]*(static_cast<double>(w)/2-j)*scale;
                cur_direction[2]=norm_pl[2]+up[2]*(static_cast<double>(h)/2-i)*scale+third[2]*(static_cast<double>(w)/2-j)*scale;
                double tmin=-1.0; cur_col.clear();
                for (unsigned int k=0;k<tetraedrs.size();k++){
                    time_color=tetraedrs[k]->Check_all(xyz,cur_direction);
                    if ((tmin<0)&& (time_color.first>0)){
                        tmin=time_color.first;
                        cur_col=time_color.second;
                    }
                    else if ((tmin>=time_color.first) && (tmin<=time_color.first)) {overlay=true;}
                    if (time_color.first>0 && time_color.first<tmin){
                        tmin=time_color.first;
                        cur_col=time_color.second;
                    }
                }
                unsigned char mass[3];
                if(cur_col.size()==0){
                    mass[0]=140;
                    mass[1]=255;
                    mass[2]=255;
                }else{
                    mass[0] = cur_col[0];
                    mass[1] = cur_col[1];
                    mass[2] = cur_col[2];
                }
                img->draw_point(i, j, mass);
            }
        }
    }
    void Draw2(std::vector <Tetr*> & tetraedrs){
        std::vector <unsigned char> cur_col;
        double norm_pl[3]={norm[0]*dist,norm[1]*dist,norm[2]*dist};
        double cur_direction[3];
        std::pair <double, std::vector <unsigned char> > time_color;
        #pragma omp parallel for
        for (int i=0;i<h;i++){
            #pragma omp parallel for private(cur_col,cur_direction, time_color)
            for(int j=0;j<w;j++){
                cur_direction[0]=norm_pl[0]+up[0]*(static_cast<double>(h)/2-i)*scale+third[0]*(static_cast<double>(w)/2-j)*scale;
                cur_direction[1]=norm_pl[1]+up[1]*(static_cast<double>(h)/2-i)*scale+third[1]*(static_cast<double>(w)/2-j)*scale;
                cur_direction[2]=norm_pl[2]+up[2]*(static_cast<double>(h)/2-i)*scale+third[2]*(static_cast<double>(w)/2-j)*scale;
                double tmin=-1.0; cur_col.clear();
                for (unsigned int k=0;k<tetraedrs.size();k++){
                    time_color=tetraedrs[k]->Check_all(xyz,cur_direction);
                    if ((tmin<0)&& (time_color.first>0)){
                        tmin=time_color.first;
                        cur_col=time_color.second;
                    }
                    else if ((tmin>=time_color.first) && (tmin<=time_color.first)) {overlay=true;}
                    if (time_color.first>0 && time_color.first<tmin){
                        tmin=time_color.first;
                        cur_col=time_color.second;
                    }
                }
                unsigned char mass[3];
                if(cur_col.size()==0){
                    mass[0]=140;
                    mass[1]=255;
                    mass[2]=255;
                }else{
                    mass[0] = cur_col[0];
                    mass[1] = cur_col[1];
                    mass[2] = cur_col[2];
                }
                img->draw_point(i, j, mass);
            }
        }
    }
};
