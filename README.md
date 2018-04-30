[![Build Status](https://travis-ci.org/ComplexNetTSP/Bstream.svg?branch=master)](https://travis-ci.org/ComplexNetTSP/Bstream) [![codecov](https://codecov.io/gh/ComplexNetTSP/Bstream/branch/master/graph/badge.svg)](https://codecov.io/gh/ComplexNetTSP/Bstream)

# Bstream
For more information about **Bstream** please refer to  the [Documentation](https://complexnettsp.github.io/Bstream/).

## Build Bstream from Source
You can clone Bstream from [GitHub](https://github.com/ComplexNetTSP/Bstream) with git.

### Requirements
You will need the following software to build Bstream as a Python package from source:

* A modern C++ compiler (C++17), e.g.: g++ (>= 4.8) or clang++ (>= 3.7)
* Python (>= 3.5)
* Boost (>= 1.54) library installed
* Pybind11 library installed
* cmake (>= 3.9) 

### Install the development version with conda

Before installing the development version, you may need to install 
the following package:

```bash
conda install -c conda-forge boost pybind11
```

Clone the repository from github and install with cmake

```bash
git clone https://github.com/ComplexNetTSP/Bstream.git
cd Bstream
mkdir build
cd build
cmake .. -DBOOST_ROOT=/path/to/conda/include
make
make test
```

or clone the repository from github and compile install with python setuptool

```bash
git clone https://github.com/ComplexNetTSP/Bstream.git
cd Bstream
python setup.py build test
```

## Internal structure
