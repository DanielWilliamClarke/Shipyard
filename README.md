# Shipyard

Red black tree algorithm that stores Ship data

Originally year 2 Computer Science Assignment from 2011/2012

> The main aim of this project is to refactor the red black tree algorithm, cover with unit tests, and visualise
> - https://www.techiedelight.com/c-program-print-binary-tree/
> - https://github.com/YoussefRaafatNasry/bst-ascii-visualization

> This repo can then be a landing zone for data strcture, sorting and other algorithm implementations  

## Install Conan packages

For now update profile.txt to contain the Build Config mode [`Debug` or `Release]

```Powershell
# Install Deps
cd build/x64-Debug
conan install --build=missing --profile ../../profile.txt ../..

# then run cmake
cmake ..
```

then build using `make` or visual studio


