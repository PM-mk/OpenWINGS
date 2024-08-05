# OpenWINGS

OpenWINGS is a free and open source program that provides a graphical interface to two system modelling methods: WINGS and ALMODES.

Aforementioned methods have been proposed by their original author: [J. Michnik](https://scholar.google.pl/citations?user=6R4KLHcAAAAJ).

This project has been created as a supplement for it's authors' master's thesis.

## Download

**[Latest release](https://github.com/PM-mk/OpenWINGS/releases)**

## Building form source

This repository does not contain the project's dependancies. As such, compiling OpenWINGS from source requires the wxWidgets library to be installed and it's environment variable to be set. Moreover, the remaining dependancies are expected to be installed on path stored in an environemnt variable named "LIB" (eg. $ENV{LIB}/eigen-3.4.0).

Project's CMake configuration only supports compiling OpenWINGS for Windows.

**OpenWINGS has NOT been tested on other platforms.**

To alter dependancy paths or compile OpenWINGS for a different platform, simply edit the main CMakeLists.txt file.

## Used libraries

- [wxWidgets](https://www.wxwidgets.org) - v3.2.4
- [wxMathPlot](https://wxmathplot.sourceforge.io) - v0.2.0
- [Eigen](https://eigen.tuxfamily.org) - v3.4.0

## License

The OpenWINGS project is licensed under the GPL-v3.0 license.