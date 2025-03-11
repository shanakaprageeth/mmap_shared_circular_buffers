![Build](https://github.com/shanakaprageeth/mmap_shared_circular_buffers/actions/workflows/.ci.yml/badge.svg)
# MMAP shared circular buffer

This example provides a single producer single consumer shared circular buffer.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

gcc, make

### Building

Please use following commands to compile master and slave tests
``` 
mkdir -p build
cd build
cmake ../
cmake --build .
``` 

## Running the tests

First create the required mmap file handlers using following command
``` 
echo "sample text" > SharedMem
echo "sample text" > SharedMemStat
``` 
Execute master
``` 
./build/bin/apps/master_app SharedMemStat SharedMem 
``` 
Afterwards start the slave using 
``` 
./build/bin/apps/slave_app SharedMemStat SharedMem 
``` 

## License
[MIT](https://choosealicense.com/licenses/mit/)

