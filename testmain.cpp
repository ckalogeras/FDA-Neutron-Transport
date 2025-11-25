#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readin.cpp"
#include "elevel.h"
//#include "csvinterator.cpp"  

using namespace std;

//String of file name to be entered for energy levels
std::string efoldername;
//The cross-sectional width of the x-, y- and z-axes for the object that is being measured.
float secwidth; //cm

int main() { 
    //Create a vector for multiple energy classes/levels
    std::vector<Elevel> HotSauce;
    cout << "Enter the file directory containing the energy levels and ending with '/' ." << endl;
    cin >> efoldername;
    //Set cross-sectional width
    cout << "Enter the cross-sectional width for the x-, y- and z-axes in cm:" << endl;
    cin >> secwidth; //cm
    //Create a vector for the excurrent flux from the object (the last slice for each energy level)
    std::vector<std::vector<std::vector<float>>> LastDab;

    //Create a temporary class for reading the energy folders director
    Readin enerfolder;
    enerfolder.fold_dir(efoldername);
    
    //Run a loop for reading the energy density and cross-section and computing the flux files
    for (int n = 0; n<enerfolder.foldernames.size(); n++){
        //Make sure files are saved as Microsoft Excel Comma Separated Values File (.csv)
        std::string sigmadirec = enerfolder.foldernames[n] + "/testdat/";
        std::string densdirec = enerfolder.foldernames[n] + "/density/";
        std::string fluxdirec = enerfolder.foldernames[n] + "/flux/";

        //Create Energy class
        Elevel energylvl;
        //Create temporary class for reading cross-section data files
        Readin sigmafile;
        //Create temporary class for reading density data files
        Readin densfile;
        //Create temporary class for writing flux calculated data files
        Readin fluxfile;

        //Create vector with all filenames in directory
        sigmafile.file_dir(sigmadirec);
        densfile.file_dir(densdirec);

        //Create a vector for multiple Slabs
        std::vector<Slab> WholeChaloopa;
        //create loop for creating multiple slabs
        if(sigmafile.filenames.size() == densfile.filenames.size()){
            for (int i=0; i<sigmafile.filenames.size(); i++){
                if ( i == 0 ){
                    Slab slice;
                    //Iterator for SigmaT and Density values
                    sigmafile.read_file(sigmafile.filenames[i], slice.sigma_t);
                    //slice.print_mat(slice.sigma_t);
                    densfile.read_file(densfile.filenames[i], slice.rho);
                    //slice.print_mat(slice.rho);
                    //Load universal values to each slab
                    slice.a = slice.sigma_t[i].size()*secwidth; //X-MAX LENGTH CM
                    slice.b = slice.sigma_t.size()*secwidth; //Y-MAX LENGTH CM
                    slice.c = sigmafile.filenames.size()*secwidth; //Z-MAX LENGTH CM
                    slice.del = secwidth; //DELTA VALUE FOR THE SLABS (100x100um as rec in K. Takahashi)
                    cout << "Enter the incident neutron flux level for " ;
                    cout << enerfolder.foldernames[n] << endl;
                    cin >> slice.N0;
                    //Test the calculation for the flux
                    slice.calc_act1();
                    cout << "slice " << endl;
                    cout << i << endl;
                    slice.print_mat(slice.flux_act);
                    WholeChaloopa.push_back(slice);            
                }
                if ( i != 0 ){
                    Slab slice;
                    //Iterator for SigmaT and Density values
                    sigmafile.read_file(sigmafile.filenames[i], slice.sigma_t);
                    //slice.print_mat(slice.sigma_t);
                    densfile.read_file(densfile.filenames[i], slice.rho);
                    //Load universal values to each slab
                    slice.a = slice.sigma_t[i].size()*secwidth; //X-MAX LENGTH CM
                    slice.b = slice.sigma_t.size()*secwidth; //Y-MAX LENGTH CM
                    slice.c = sigmafile.filenames.size()*secwidth; //Z-MAX LENGTH CM
                    slice.del = secwidth; //DELTA VALUE FOR THE SLABS
                    //Test the calculation for the flux
		    //
		    //
		    //[NEXT STEP WOULD BE TO IMPLEMENT A FUNCTION THAT CAN SELECT WHICH CALCULATION TYPE TO USE]
		    //TOGGLE FUNCTION BETWEEN SIMPLE DIFFUSION
		    //TOGGLE FUNCTION BETWEEN SIMPLE DIFFUSION WITH ASSUMED DOWNSCATTERING AND THERMAL ABSORPTION - scathigh1 functions
		    //
		    //
                    //cout << "did this work" << endl;
                    slice.calc_act2(WholeChaloopa[i-1].flux_act);
                    cout << "slice " << endl;
                    cout << i << endl;
                    slice.print_mat(slice.flux_act);
                    WholeChaloopa.push_back(slice);
                }
            }
        }
        else if(sigmadirec.size() > densdirec.size()){
            cout << "ERROR: You have more cross-section files than density files you goof" << endl;
        }
        else if (sigmadirec.size() < densdirec.size()){
            cout << "ERROR: You have more density files than cross-section files you goof" << endl;
        }       
        //Store flux vector in the appropriate energy level
        energylvl.fluxcross = WholeChaloopa;
        WholeChaloopa.clear();
        cout << "All cross-sections calculated: ";
        cout << energylvl.fluxcross.size() << endl;

        //Store last slice from flux vector into excurrent flux vector
        LastDab.push_back(energylvl.fluxcross[energylvl.fluxcross.size()-1].flux_act);

        std::string fname;
        cout << "What do you want to name the files? " << endl;
        cin >> fname;

        //Write flux vector information to file directories
        for (int f=0; f<energylvl.fluxcross.size(); f++){
            fluxfile.write_file(f, fname, fluxdirec, energylvl.fluxcross[f].flux_act);
        }
    }
    //Write excurrent flux vector to file directory
    std::string outname;
    cout << "What do you want to name the files? " << endl;
    cin >> outname;
    std::string totaldirec = efoldername + "/excurrent/";

    for (int f=0; f<LastDab.size(); f++){
        Readin fluxfile;
        Slab slice;
        std::vector<std::vector<float>> fluxout = LastDab[f];
        slice.print_mat(LastDab[f]);
        fluxfile.write_file(f, outname, totaldirec, fluxout);
    }


    /*
    //Create a vector for multiple Slabs
    std::vector<Slab> WholeChaloopa;
    //create loop for creating multiple slabs
    if(sigmafile.filenames.size() == densfile.filenames.size()){
        for (int i=0; i<sigmafile.filenames.size(); i++){
            if ( i == 0 ){
                Slab slice;
                //Load universal values to each slab
                slice.a = 0.09; //X-MAX LENGTH CM
                slice.b = 0.22; //Y-MAX LENGTH CM
                slice.c = 0.14; //Z-MAX LENGTH CM
                slice.del = 0.01; //DELTA VALUE FOR THE SLABS (100x100um as rec in K. Takahashi)
                //Iterator for SigmaT and Density values
                sigmafile.read_file(sigmafile.filenames[i], slice.sigma_t);
                //slice.print_mat(slice.sigma_t);
                densfile.read_file(densfile.filenames[i], slice.rho);
                //slice.print_mat(slice.rho);
                //Test the calculation for the flux
                slice.calc_act1();
                cout << "slice " << endl;
                cout << i << endl;
                slice.print_mat(slice.flux_act);
                WholeChaloopa.push_back(slice);            
            }
            if ( i != 0 ){
                Slab slice;
                //Load universal values to each slab
                slice.a = 0.09; //X-MAX LENGTH CM
                slice.b = 0.22; //Y-MAX LENGTH CM
                slice.c = 0.14; //Z-MAX LENGTH CM
                slice.del = 0.01; //DELTA VALUE FOR THE SLABS
                //Iterator for SigmaT and Density values
                sigmafile.read_file(sigmafile.filenames[i], slice.sigma_t);
                //slice.print_mat(slice.sigma_t);
                densfile.read_file(densfile.filenames[i], slice.rho);
                //Test the calculation for the flux
                cout << "did this work" << endl;
                slice.calc_act2(WholeChaloopa[i-1].flux_act);
                cout << "slice " << endl;
                cout << i << endl;
                slice.print_mat(slice.flux_act);
                WholeChaloopa.push_back(slice);
            }
        }
        //cout << WholeChaloopa.size() << endl;
    }
    else if(sigmadirec.size() > densdirec.size()){
        cout << "ERROR: You have more cross-section files than density files you goof" << endl;
    }
    else if (sigmadirec.size() < densdirec.size()){
        cout << "ERROR: You have more density files than cross-section files you goof" << endl;
    }

    //Store flux vector in the appropriate energy level
    energylvl.fluxcross = WholeChaloopa;
    WholeChaloopa.clear();
    cout << energylvl.fluxcross.size() << endl;

    std::string fname;
    cout << "What do you want to name the files? " << endl;
    cin >> fname;
    //Write flux vector information to file directories
   for (int f=0; f<energylvl.fluxcross.size(); f++){
        fluxfile.write_file(f, fname, fluxdirec, energylvl.fluxcross[f].flux_act);
    } 

/*
    //Create slabs for cross-sections
    Slab testdab;
    testdab.a = 0.9; //x-max length cm
    testdab.b = 2.2; //y-max length cm
    testdab.c = 1.4; //z-max length cm
    testdab.del = 0.1; //the delta value for the slabs
    int limit = testdab.c*testdab.del; //file limit to be loaded in

    int l = 0; //for setting start point of file stream
    
    //Test an Iterator for SigmaT and Density
    sigmafile.read_file(sigmafile.filenames[0], testdab.sigma_t);
    testdab.print_mat(testdab.sigma_t);
    densfile.read_file(densfile.filenames[0], testdab.rho);
    testdab.print_mat(testdab.rho);

    //Test the calculation for the flux
    testdab.calc_act();
    testdab.print_mat(testdab.flux_act);
    //} */
    return 0;
}
