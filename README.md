[![Build Status](https://travis-ci.org/ComplexNetTSP/Bstream.svg?branch=master)](https://travis-ci.org/ComplexNetTSP/Bstream) [![codecov](https://codecov.io/gh/ComplexNetTSP/Bstream/branch/master/graph/badge.svg)](https://codecov.io/gh/ComplexNetTSP/Bstream)

# Bstream

## install 

Bstream requires Python 3.4, 3.5, or 3.6. If you do not already have a Python 
environment configured on your computer, please see the instructions for 
installing the full scientific Python stack.

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

Clone the repository from github and commpile install with setup.py

```bash
git clone https://github.com/ComplexNetTSP/Bstream.git
cd Bstream
python setup.py build test
```

## documentation 
[Documentation](https://complexnettsp.github.io/Bstream/)

## Internal structure
