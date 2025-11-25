#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <vector>

#ifndef READIN_H
#define READIN_H


using namespace std;

class Readin {
    public:
        size_t pathmax = 256;
        std::vector<std::string> filenames;
        std::vector<std::string> foldernames;
        //friend std::istream& operator >>(std::istream& fin, Readin readin);

        void file_dir(std::string& dirname);

        void fold_dir(std::string& dirname);

        void read_file(std::string& filename, std::vector<std::vector<float>>& outarr);
        //Parse file into rows to send to iterator for cleanup

        void write_file(int& f, std::string& fname, std::string& dirname, std::vector<std::vector<float>>& outvec);
        //create a file in appropriate directory and write vector to it


    private:
        int val;
        char cha;
        std::string str;
        std::vector<float> nocomvec;
        std::vector<std::vector<float>>nocomarr;
};

#endif /* READIN_H */