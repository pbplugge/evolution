### A C++ Genetic programs / algorithms library.

For experimenting with Genetic programs / algorithms.

__Features__

* Easy to understand object oriented c++ code
* Usable as shared library, python notebook examples included
* Can handle genetic programs as well as genetic algorithms
* Multi-threading
* Multi objective
* Hall of fame
* Statistics
* Very fast


__How does it work?__

Clone the repository.
Go to the directory and execute build.sh
It should compile without errors or warnings.
Put the created _evolution.so in the notebooks directory.
Start python notebook in the notebooks directory.

You can also use only C++ instead of python.
Just check out main.cpp to see how simple that is.
But either way you will need to create some C++ code simmilar to the code in the src/experiments directory.


__Why__

For my own project i could not find a library that does what i need it to do.
A python library would be too slow for my purposes. But i want to use python for my analysis.
The existing libraries i found could not evolve parameters inside nodes/components that influence them.
So i decided to write my own library.

My design goal is an easy to use general purpose genetic evolution library.
You will need to be able to code some C++ but i made it very simple.
With easy to follow examples and python notebooks 


__What is next?__

I want to take evolutionary programming to the extreme.
Not only a system that can do genetic evolutionary algorithms but parallel and recurrent systems forming bigger systems.
The theory is if good components are chosen any application can generated.

Some things i want to do first is check for double algorithms.
Evolutionary programs/algorithms that are already attempted don't need to be re-calculated.
For bigger systems and systems where the simulation time takes longer we don't want to simulate repeatedly.

