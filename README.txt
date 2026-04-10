
======================================================================
Neutron Transport FDA 1.4 ReadMe
======================================================================

The latest updates to this readme file is located at https://github.com/ckalogeras/FDA-Neutron-Transport-/README.md

This file contains information about the Neutron Transport FDA and it is highly recommended to read this information before running or editing any of the scripts located in this repository.

A Master's Project
------------------------------------------------------------------------

A Master's Project
------------------------------------------------------------------------

This started as a small project for a reactor transport class and grew to become my rough and ready master's project. This is a deterministic neutron transport code utilizing Fick's diffusion equation, approximating the transport of neutrons of varying energy levels through different materials. While this serves as an example of a finite difference approximation code for multi-energy neutron transport, it should not be used in any capacity for the verification, validation or benchmark of a reactor's operation. In this regards, I would highly recommend that you defer to one of the tested and true codes such as MCNP 6.3 developed by the Los Alamos National Laboratory and available from Radiation Safety Information Computational Center located at https://rsicc.ornl.gov/Default.aspx.

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


Usage
------------------------------------------------------------------------

Future Developments
------------------------------------------------------------------------

Contributing
------------------------------------------------------------------------
Pull requests are welcome though this project is in the early stages that I doubt much use will happen. For any major changes, please open an issue to discuss what you would like to change or what changes you would like to see.
Please make sure to state your changes or updates as appropriate.

License
------------------------------------------------------------------------
Apache License 2.0
A permissive license whose main conditions require preservation of copyright and license notices. Contributors provide an express grant of patent rights. Licensed works, modifications, and larger works may be distributed under different terms and without source code.





