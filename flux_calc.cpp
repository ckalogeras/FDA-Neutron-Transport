#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <istream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <fstream>
//#include "matplotlibcpp.h"

using namespace std;
//namespace plt = matplotlibcpp;
// Initiate variables in 2D slab
struct Slab
{
	public:
		float a; //x max
		float b; //y max
		float c; //z max
	//value for cross-sectional slices
		float del; 
	//incident neutron flux (neutrons/cm^2-s)
		float N0;
	// mu_o
		float mu;
	//2D matrix for analytical flux (single energy first)
		std::vector<std::vector<float>> flux_act;
	//3D matrix for analytical flux (single energy)
		std::vector<std::vector<std::vector<float>>> flux_actM;
	// 2D matrix for total cross-sections atom/cm
		std::vector<std::vector<float>> sigma_t;
	// 2D matrix for absorption cross-sections atom/cm
		std::vector<std::vector<float>> sigma_a;
	// 2D matrix for removal cross-sections atom/cm
		std::vector<std::vector<float>> sigma_r;
	// 2D matrix for scattering cross-sections atom/cm
		std::vector<std::vector<float>> sigma_s;
	// 2D matrix for density (g/cm^3) [based on different material compositions]
		std::vector<std::vector<float>> rho;
	// 2D matrix for atomic numbers
		std::vector<std::vector<float>> Amass;
	// 2D matix for Diffusion coefficient
		std::vector<std::vector<float>> Dcoeff;
	



//Basic Point Kinetics Function for the analytical flux of single energy
//At the very end, neutrons of all energies will need to be totaled (about a 100 energy spectrum)
//This function is for the initial layer 
	void calc_act1()
	{
		//Create for loop to run through y-values from 0 to b cm in intervals of 0.01 cm in multiple rows
        for (int j = 0; j<(b/del); j++){
			//Create for loop to run through x-values from 0 to a cm in intervals of 0.01 cm in one row
			for (int i = 0; i<(floor(a/del)); i++){
				//Calculation using Sturm-Liouville simplification and eigenfunction
				//value = N0*exp(-sigma_t[j][i]*rho[j][i]);
				value = N0*exp(-sigma_t[j][i]*del);
				// Push value into vector
				row.push_back(value);
				//cout << flux_act[i] << '\n';
			}
            flux_act.push_back(row);
            row.clear();
		}
	};

//This function is for all the follow on layers and uses the vector for the previous layer
	void calc_act2(std::vector<std::vector<float>>& Nprev)
	{
		for (int j = 0; j<(b/del); j++){
			//Create for loop to run through x-values from 0 to a cm in intervals of 0.01 cm in one row
			for (int i = 0; i<(floor(a/del)); i++){
				//Calculation using Sturm-Liouville simplification and eigenfunction
				//value = Nprev[j][i]*exp(-sigma_t[j][i]*rho[j][i]);
				value = Nprev[j][i]*exp(-sigma_t[j][i]*del);
				// Push value into vector
				row.push_back(value);
				//cout << flux_act[i] << '\n';
			}
            flux_act.push_back(row);
            row.clear();
		}
	};

//Function using a different deterministic method that incorporates downscattering and absorption - this is for the highest energy lvl
//This function is for the initial layer of a slab
	void calc_scathigh1(std::vector<std::vector<float>>& D0)
	{
		//Create for loop to run through y-values from 0 to b cm in intervals of 0.01 cm in multiple rows
        for (int j = 0; j<(b/del); j++){
			//Create for loop to run through x-values from 0 to a cm in intervals of 0.01 cm in one row
			for (int i = 0; i<(floor(a/del)); i++){
				value = -(Dcoeff[j][i]-D0[j][i])*N0*del/(-(Dcoeff[j][i]-D0[j][i])-(sigma_r[j][i]*pow(del,2)));
				row.push_back(value);
			}
			flux_act.push_back(row);
			row.clear();
		}
	};

//This function is for the rest of the highest energy level
	void calc_scathigh2(std::vector<std::vector<float>>& D0, std::vector<std::vector<float>>& Nprev)
	{
		//Create for loop to run through y-values from 0 to b cm in intervals of 0.01 cm in multiple rows
        for (int j = 0; j<(b/del); j++){
			//Create for loop to run through x-values from 0 to a cm in intervals of 0.01 cm in one row
			for (int i = 0; i<(floor(a/del)); i++){
				value = -(Dcoeff[j][i]-D0[j][i])*Nprev[j][i]*del/(-(Dcoeff[j][i]-D0[j][i])-(sigma_r[j][i]*pow(del,2)));
				row.push_back(value);
			}
			flux_act.push_back(row);
			row.clear();
		}
	};

//Function using a different deterministic method that incorporates downscattering and absorption - this is for the middle energy lvls
//This function is for the initial layer of the slab
	void calc_scatmid1(std::vector<std::vector<float>>& D0, std::vector<std::vector<float>>& sigma_s0, float& No0)
	{
		//Create for loop to run through y-values from 0 to b cm in intervals of del cm in multiple rows
		for (int j = 0; j<(b/del); j++){
			//Create for loop to run through x-values from 0 to a cm in intervals of 0.01 cm in one row
			for (int i = 0; i<(floor(a/del)); i++){
				value = ((sigma_s0[j][i]*del*No0 - (Dcoeff[j][i]-D0[j][i])*N0)*del)/(-(Dcoeff[j][i]-D0[j][i])-(sigma_r[j][i]*pow(del,2)));
				row.push_back(value);
			}
			flux_act.push_back(row);
			row.clear();
		}	
	};

//This function is for the rest of the middle energy level
	void calc_scatmid2(std::vector<std::vector<float>>& D0, std::vector<std::vector<float>>& sigma_s0, std::vector<std::vector<float>>& Nprev)
	{
		//Create for loop to run through y-values from 0 to b cm in intervals of entered cm in one row.
		for (int j = 0; j < b/del; j++){
			//Create for loop to run through x-values from 0 to a cm in intervals of entered cm in one row.
			for (int i = 0; i < (floor(a/del)); i++){
				value = ((sigma_s0[j][i]*del*Nprev[j][i] - (Dcoeff[j][i]-D0[j][i])*Nprev[j][i])*del)/(-(Dcoeff[j][i]-D0[j][i])-(sigma_r[j][i]*pow(del,2)));
				row.push_back(value);
			}
			flux_act.push_back(row);
			row.clear();
		}
	};

//Function for calculating removal coefficients
	void calc_sigmar()
	{
		//Create for loops to run through values in the total and scattering sigma matrices
		for (int j = 0; j < sigma_t.size(); j++){
			for (int i = 0; i < sigma_t[j].size(); i++){
			//Calculation for sigma_r
				value = sigma_t[j][i]-sigma_s[j][i];
			//Push value into vector
				row.push_back(value);
			}
			sigma_r.push_back(row);
			row.clear();
		}
	};

//Function for calculating Diffusion coefficient
	void calc_diff()
	{
		//Create for loops to run through values in total and scattering cross-section
		for (int j = 0; j < sigma_t.size(); j++){
			for (int i = 0; i < sigma_t[j].size(); i++){
			//Calculation for diffusion coeff
				value = 1/(3*(sigma_t[j][i] - mu*sigma_s[j][i]));
			//Push value into vector
				row.push_back(value);
			}
			Dcoeff.push_back(row);
			row.clear();
		}
	};
	
	void print_mat(vector<vector<float>> mat)
	{
		for (int n = 0; n < mat.size(); n++) {
			cout << "Row " << n << " [";
			for (int i = 0; i < mat[n].size(); i++) {
				cout << mat[n][i];
				if (i != mat[n].size()-1) {
					cout << ", ";
				}
			}
			cout << "]\n";
		}
	};

	void print_vec(vector<float> vec)
	{
		cout << '['; 
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i];
			if ( i<vec.size()-1 ) {
				cout << ", ";
			}
		}
		cout << ']' << '\n';
	};	

/*//Function for Plotting Functions	- NOT WORKING WONT COMPILE ON WINDOWS
	void plot_both()
	{
	//Output Image Size
		plt::figure_size(1200, 780);
		plt::plot(xvec, flux_act, "b");
		plt::plot(xvec, flux_feap, "g");
		plt::named_plot("Theoretical Flux", xvec, flux_act, "b");
		plt::named_plot("FDA Flux", xvec, flux_feap, "g");
		plt::xlim(0.0, 2.5);
		plt::title("Flux Plot");
		plt::legend();
		plt::save("./flux.png");
	}; */
	//plot each energy spectrum separately, do a ratio of initial to final attenuation for plot 
	//Look at energy spectrum on the external departing edge (don't make it complicated)
	private:
	// Calculation Values
		float value;
		float value2;
	// Calculation Vector
		vector<float> row;

}; 

