[![Build Status](https://travis-ci.org/ComplexNetTSP/Bstream.svg?branch=master)](https://travis-ci.org/ComplexNetTSP/Bstream) [![codecov](https://codecov.io/gh/ComplexNetTSP/Bstream/branch/master/graph/badge.svg)](https://codecov.io/gh/ComplexNetTSP/Bstream)

# Bstream

## Install 

**Bstream** requires Python 3.5, or 3.6. If you do not already have a Python
environment configured on your computer, please see the instructions for 
installing the full scientific Python stack. For more information about **Bstream**
please refer to  the [Documentation](https://complexnettsp.github.io/Bstream/).


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
cmake ..
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
