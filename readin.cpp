//#define _DEFAULT_SOURCE
#include <dirent.h>
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <vector>
#include "readin.h"
#include "csvinterator.cpp"

using namespace std;

void Readin::file_dir(std::string& dirname){
    cout << dirname << endl;
    DIR *d;
    struct dirent *namelist;
    char* filename;
    int f;
    int error = 1;
    while (error == 1) {
        if ((d = opendir(dirname.c_str())) != NULL){
            //*f = scandir(".", &namelist, NULL, alphasort);
            while ((namelist = readdir(d)) != NULL){
                if (!strcmp(namelist->d_name, ".") || !strcmp(namelist->d_name, "..")){
                    //skip
                }
                else {
                    filename = namelist->d_name;
                    filenames.push_back(dirname+filename);
                    //std::cout << filename << std::endl;
                }
            }
            closedir(d);
            //sort the filenames in alphabetical order
            std::sort(filenames.begin(), filenames.end());
            for (int i = 0; i<filenames.size(); i++){
            std::cout << filenames[i] << std::endl;
            }
            error = 0;
        }
        //DIR *d;
        else {
            //int f;
            //f = scandir(".", &namelist, NULL, alphasort);
        
            //scan directory for number of files of NULL type and collect file names
                //in namelist in alphabetical sorted order
            perror("scandir");
            std::cout << "ERROR: I cannot find the directory: " << dirname << "Enter a valid directory path ya goof. Don't forget to put a '\' at the end. \n";
            cin >> dirname;
            //std::cout << "EXIT_FAILURE" << std::endl;
            error = 1;
        }
    }
}

void Readin::fold_dir(std::string& dirname){
    std::string foldername;
    for (auto& p : std::filesystem::recursive_directory_iterator(dirname)){
        if (p.is_directory()){
            foldername = p.path().string();
            std::string fname = foldername;
            fname.erase(fname.begin(), fname.end()-2);
            cout << fname << endl;
            if (fname == "ev"){
                foldernames.push_back(foldername);
            }
        }
    }
        //sort the foldernames in alphabetical order
    std::sort(foldernames.begin(), foldernames.end());
    std::cout << "I worked" << endl;
    for (int i = 0; i<foldernames.size(); i++){
        std::cout << foldernames[i] <<std::endl;
    }

}

void Readin::read_file(std::string& filename, std::vector<std::vector<float>>& outarr){
    int a = 0;
    std::ifstream fin(filename);
    std::string filerow;
    while( std::getline(fin, filerow) ){
        std::vector<float> rowvec = Row_Iterator(filerow);
        //cout << rowvec.size() << endl;
        outarr.push_back(rowvec);
    }
}

void Readin::write_file(int& f, std::string& fname, std::string& dirname, std::vector<std::vector<float>>& outvec){
    //CONVERT THIS INTO AN ITERATOR
    //Create file pointer
    fstream fout;
    //Create existing csv file
    if (f < 10){
        fout.open(dirname + fname + "0" + to_string(f), ios::out | ios::app);
    }
    else {
        fout.open(dirname + fname + to_string(f), ios::out | ios::app);
    }

    for (int j=0; j<outvec.size(); j++ ){
        for ( int i=0; i<outvec[j].size(); i++){
            if( i <outvec[j].size()-1){
                fout << outvec[j][i]  << ", ";
            }
            else if( i == outvec[j].size()-1){
                fout << outvec [j][i] << "\n";
            }
        }
    }
    fout.close();
}

