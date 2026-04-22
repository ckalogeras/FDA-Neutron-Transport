
======================================================================
Neutron Transport FDA 1.4 ReadMe
======================================================================

The latest updates to this readme file is located at https://github.com/ckalogeras/FDA-Neutron-Transport-/README.md

This file contains information about the Neutron Transport FDA and it is highly recommended to read this information before running or editing any of the scripts located in this repository.

Author
------------------------------------------------------------------------
Christine Kalogeras
      For any questions, I can be reached through github discussion or by email at christine.kalogeras@gmail.com.

A Master's Project
------------------------------------------------------------------------

This started as a small project for a reactor transport class and grew to become my rough and ready master's project. 
This is a deterministic neutron transport code utilizing Fick's diffusion equation, approximating the transport of neutrons of varying energy levels through different materials. 
While this serves as an example of a finite difference approximation code for multi-energy neutron transport, it should not be used in any capacity for the verification, validation or benchmark of a reactor's operation. 
In this regards, I would highly recommend that you defer to one of the tested and true codes such as MCNP 6.3 developed by the Los Alamos National Laboratory and available from Radiation Safety Information Computational Center located at https://rsicc.ornl.gov/Default.aspx.

System Requirements
------------------------------------------------------------------------
- Excel
  Microsoft Excel with macros-enabled, hopefully to be replaced by a Python-developed GUI.
- C++
  GCC version 13.3.0 with the basic development packages installed; however, the VS Code version of C++ is also adequate
- Python
  Python version 3.2.9, the packages utilized are numpy, csv, os, matplotlib, mpl_toolkits, pylab

Installation and Setup
------------------------------------------------------------------------
You can download or clone the repository.
Download:
  - On your browser, navigate to https://github.com/ckalogeras/FDA-Neutron-Transport
  - Above the list of files, click <> Code.
  - On the dropdown menu, click Download ZIP
Clone:
  - On your browser, navigate to https://github.com/ckalogeras/FDA-Neutron-Transport
  - Above the list of files, click <> Code.
  - On the dropdown menu, copy the https link.
  - Open git Bash
  - Create a folder to deposit the cloned directory in if you have not done so already and change the current working directory to this location.
  - Enter >> git clone https://github.com/ckalogeras/FDA-Neutron-Transport.git

Windows: 
The GCC C++ compiler can be downloaded with msys2 using instructions from the below link. 
The folks there put together a great guide so why not use it.
https://www.mingw-w64.org/getting-started/msys2/
  - To install the C++ basic development packages, open the MSYS UCRT64.
  - Enter >> pacman -S base-devel
  - Accept the default number of packages in the toolchain group by pressing Enter
  - Add path of MinGW-w64 bin folder to Windows PATH environment cause this is Windows
  - Open by typing "Edit environment variables" in the Windows search bar
  - Select Path and Click Edit
  - Click New and type in "C:\msys64\ucrt64\bin"
Python releases for Windows can be downloaded from https://www.python.org/downloads/windows/

Linux: 
Much simpler for C++ and Python, open the terminal and using Bash.
  - Enter >> sudo apt-get install g++
  - sudo apt-get install python3

Usage
------------------------------------------------------------------------
This assumes an understanding of particle transport and finite difference approximation. 
Please read the paper associated with this project if there is any confusion.
The Excel macro is used to mass-create multiple csv files that represent object slices in the x-y plane that the neutrons will interact with. 
Using the excel macro files, the shape, material density and material atomic number can be specified. 
The C++ code utilizes a version of Fick's diffusion equation and a finite difference approximation to calculate the three-dimensional neutron flux and its interactions through a material.
The Python code is utilized to display the calculation output as a three-dimensional heat map.

1) Alter the object shape and material properties via the excel macro files. Each excel file has a certain number of slices represented by the number of sheets in the bottom tab. 
This is based upon the determined thickness of each xy cross-section or the user-chosen value of dz. For example if your object is 10 cm in the z-axis and you are using 100 micrometer as your dz, then you would have 100 sheets per macro file (Let us hope, it is not this many) Each value of the cell represents a x-y-z cubic voxel of the object. 
There are three types of excel macro files that need to be adjusted:
  - atomicnum_multigrid.xlsm
  - density_multigrid.xlsm
  - sigma_multigrid.xlsm
The atomicnum_multigrid.xlsm file contains the atomic number for the material/s of the cross-section. This only needs to be adjusted once, depending on the object being simulated.
The density_multigrid.xlsm file contains the object's material/s density for the cross-section in [g/cm^3]. 
This only needs to be adjusted once, depending on the object being simulated.
The sigma_multigrid.xlsm file contains the total cross-section for the material/s of the cross-section in [atom/cm]. 
If you are simulating multi-energy neutron bombardment, you will need to create multiple versions of this file.
A list of resources for referencing the neutron cross-sectional values can be found in the associated paper.
If you are simulating multiple energy levels, you will need to create sub-folders for the energy levels so that the appropriate cross-sectional data and the universal density data are saved in them.
For example, the folder titled "05ev" contains the density, atomicnumber and the cross-sectional data pertinent to that specific energy level.

2) Alter the macro csv file creation path. In the macro-editing tab, locate the macro called "SaveSheetsasCSV" and double-click on it. 
In the editor, you will see Basic code. Edit the folder path based on your own file system. 
Make sure the final folder created matches the original file. For example, "C:\Path\to\Your\Folder\atomicnum\" or "C:\Path\to\Your\Folder\sigmat". Save the changes to the macros.

3) Run the macro files once your edits are complete. 
Three folder should be created by running these macros filled with the csv files that will be loaded into program.
      - \atomicnum\
      - \density\
      - \sigmat\
If you are running a simulation for multiple energy levels, you will need to run the macro files for every energy folder that is created and ensure that the three folders have been created.

4) Compile the C++ file. Open the Mingw64 terminal window. Navigate to the folder containing all the files cloned or downloaded from Github.
Enter >> cd C:\Path\to\folder\
Once, the terminal is pointed towards the correct directory, compile the file.
Enter >> g++ main.cpp -o main.exe
An executable file named main (or whatever you decided to name it) will be located in the same folder.

5) Run the main file. In the same Mingw64 window, type the following:
Enter >> ./main.exe
Text will appear stating "Enter the file directory containing the energy levels and ending with '/' ."
Type in your response and press the Enter key.
Then, more text will appear "Enter the cross-sectional width for the x-, y- and z-axes in cm:"
Enter this value once. 
It should be the same for all three axes since the model is breaking the object into cubic segments.
For each energy level, you will be prompted with "Enter the incident neutron flux level for [foldername]".
Enter the neutron flux value for this energy level.
Once the model is done calculating the flux through the various slices, you will be prompted to the name the file of the excurrent neutron matrix (the neutron flux of the last segment of the object).
Then, you will be prompted to name the files for the total neutron flux passing through the object.

Future Developments
------------------------------------------------------------------------
Currently, the macro files are set up to utilize a single cubic shape; however, it would be useful to test this out with shapes of varying sizes.

In light of creating unconventional shapes, it would be useful to create a GUI or method of creating multiple slices with the material properties as this would save a lot of time in set up.

Currently, the software is set up to calculate an approximation of the total neutron interactions utilizing the total neutron cross-section. The template for utilizing downscattering, absorption and removal exists in the code and needs to be refined to enable the user to create multiple sigma cross-section files that are appropriately referenced by the code. The output also needs to be adjusted so that neutrons undergoing downscattering appear in other energy flux matrices and absorption and removal properly show up in their respective matrix.  

Contributing
------------------------------------------------------------------------
Pull requests are welcome; however, this project is in the early stages that I doubt much use will happen. For any major changes, please open an issue to discuss what you would like to change or what changes you would like to see.
Please make sure to state your changes or updates as appropriate.

Acknowledgement
------------------------------------------------------------------------
A thank you to Dr. Hyoung-Kim Lee at the University of New Mexico for his insight into neutron and photon transport deterministic modeling and aid in helping me organize my code and explanation.

License
------------------------------------------------------------------------
Apache License 2.0
A permissive license whose main conditions require preservation of copyright and license notices. Contributors provide an express grant of patent rights. Licensed works, modifications, and larger works may be distributed under different terms and without source code.





