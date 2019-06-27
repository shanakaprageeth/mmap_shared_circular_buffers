# MMAP shared circular buffer

This example provides a single producer single consumer shared circular buffer.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

gcc, make

### Installing

Please use following commands to compile master and slave tests
``` 
make compile_master
make compile_slave
``` 

## Running the tests

First create the required mmap file handlers using following command
``` 
make create_files
``` 
or use run_master template to execute the master code
``` 
make run_master
``` 
Afterwards start the slave using 
``` 
make run_slave
``` 

## License
[MIT](https://choosealicense.com/licenses/mit/)
