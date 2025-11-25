#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <ios>
#include <iostream>
//#include "readin.cpp"

using namespace std;


//    friend std::istream& operator >>(std::istream& fin, CSVIterator& csvi);
 //   //check if streaming the file sends char by char and how to get whole row instead
  //  std::string filerow; //vector for the string row from Readin class
//    std::vector<int> rowvec; //vector for row of values to be inserted into
std::vector<float> Row_Iterator(std::string filerow){
    std::vector<float> rowvec;
    auto vecinstr = std::back_inserter(rowvec);
    std::vector<float> retvec;
    auto itr = filerow.begin();
    std::string segment;
    float numb;
    //for (int i=0; i<filerow.size(); i++){
    //    std::cout << filerow[i];
    //}
    while (itr != filerow.end()) {
        if ( *itr != ',' ){
            segment.push_back(*itr); //value is not a comma, send to back of string segment
            itr++; //move file row iterator forward by 1
        }
        else if ( *itr == ',' ){
            itr++;  //value is comma, move iterator forward and skip
            numb = std::stof(segment); //convert segment to a float
            segment.clear();
            *vecinstr = numb; //insert number to back of vector iterator
            ++vecinstr; //increase row vector iterator by 1
        }
    }
    if ( itr == filerow.end() ){
        //end of row has been reached
        numb = std::stof(segment); //convert segment to a float
        segment.clear();
        *vecinstr = numb; //insert number to back of vector iterator
        ++vecinstr; //increase row vector iterator by 1
    }
    /*for (int i=0; i<rowvec.size(); i++){
            std::cout << rowvec[i]<< endl;
    }*/
    return rowvec;
};

//     public:
//     typedef std::input_iterator_tag iter_cat;
//     typedef Readin value_type;
//     std::size_t difftype;
//     typedef Readin* pointer;
//     typedef Readin& reference;

//     CSVIterator(std::istream& fin) :m_str(fin.good()?&fin:nullptr) {
//         ++(*this);
//     }
//     CSVIterator() :m_str(nullptr) {}

//     //Pre Increment
//     CSVIterator& operator++() {
//         if (m_str){
//             if (!((*m_str) >> m_row)){
//                 m_str = nullptr;
//             }
//         }
//         return *this;
//     }

//     //Post Increment
//     CSVIterator operator++(int){
//         CSVIterator tmp(*this);
//         ++(*this);
//         return tmp;
//     }
//     CSVRow const& operator*() const{
//         return m_row;
//     }
//     CSVRow const* operator->() const{
//         return &m_row;
//     }
//     bool operator == (CSVIterator const& rhs) {
//         return ((this == &rhs) || ((this ->m_str == nullptr) && (rhs.m_str == nullptr)));
//     }
//     bool operator != (CSVIterator const& rhs) {
//         return !((*this) == rhs);
//     }

//     private:
//         std::istream* m_str;
//         Readin m_row;
