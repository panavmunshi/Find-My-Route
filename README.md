## This project has been cloned from my College GitHub account with permission from the professors.
# Group Members
* Abhay Narayanan
* Anuraag Agarwal
* Panav Munshi
* Rohan Batra

# Final Project Demo Link
The following link contains our final project video demo. This was hosted by Anuraag, Panav, and Rohan. Our fourth member, Abhay, wasn't able to join us for this demo as he was travelling.

**URL**: https://www.youtube.com/watch?v=JFZ9TFTGcIU&feature=youtu.be

# Introduction
The primary goal for this project was to find the most distance-efficient route from a given city to a destination city with a flight dataset. The CSV dataset contains a variety of information including the distance between airports, elapsed time, departure airport, arrival airport, flight time, scheduled timings, and frequency of every flight. We use some of these parameters in our calculations: airport codes are used to form vertices of the graph, edges store flight information between airports such as distance and a string representing additional details.

Three primary algorithms were used:

- Breadth-First Search Traversal
- A* Search Algorithm (further extended with Landmark Path algorithm)
- Dijkstra's Algorithm

# Instructions
Due to Git-LFS size constraints, we couldn't upload our datasets directly as CSVs. Therefore, we repackaged the dataset into zip files. 
In order to run our program, the user must unzip these files, which could be done by calling the `unzip` command on the linux terminal, or other utilities depending on the operating system the user is running in on. 

The following are the steps to run the program:
- Start a linux shell in the cloned source directory of the project.
- run `make remake` to generate the executable for the program, which is called `finalproj`.
- Enter `./finalproj` in the shell to start the C++ executable.
- The program will ask you to enter location of the .csv datasets. We recommend using the 2008.csv dataset as it is the latest one; however, the user can enter `default` to use the 1987.csv dataset.
- The program will take about a minute or two, depending on the processing capabilities of the host machine, to proceess the data into the Graph datastructure as the dataset has more than million entries.
- Once processed, the terminal will display three options:
  * Enter '1': Shortest Flight route from Point A to Point B w.r.t. distance. (Using Dijkstra's Algorithm)
  * Enter '2': Shortest Flight route from Point A to Point B through Point C w.r.t. distance. (Using Landmark Path and A* search)
  * Enter '3': Least number of stops from Point A to Point B (Using BFS - this may result in a longer route w.r.t. distance). 
- The user can choose any of these options to proceed with the execution of the program.
- Whichever option the user decides to choose, they will have to enter the three-letter airport code in **UPPERCASE** (this can be found in the airportcode.txt file in the root directory) whenever the program asks them to enter the airport they want to use.
- The output of the search will be printed onto the terminal screen, with the list of flights from one airport to another appearing under the '------------>' edge that connects the two airports. 
- After running the searches, the program will prompt the user if they want to run another search. If they wish to do so, the can enter `x` into the input prompt. If not, any entry (except newline/enter-key stroke) will proceed to exit the program.

We suggest the user to look into airportcode.txt before running the program. A few examples of airport codes are:
- CMI (Champaign),
- ORD (Chicago),
- SFO (San Francisco),
- and so on.

# Running Test Cases
We have compiled a small suite of test cases that could be run on our graph. To run them, do the following.
**NOTE:** The test case relies on 1987.csv. Therefore, unzip the 1987.zip and then proceed to run the test cases. 

- Run `make clean && make test` in the linux shell. This will create the test executable. 
- Run `./test` to run the test executable file. 
- The output on the terminal screen will mention if the test cases passed or not. 

# Dataset
The following is the website from where we obtained our dataset. Though we haven't tested them all, we are confident that our program will work with all of listed datasets. 

**URL**: https://dataverse.harvard.edu/dataset.xhtml?persistentId=doi:10.7910/DVN/HG7NV7

# Credits
The following are few websites that helped us implement all of our algorithms. We thank them for all the resources they've shared and for the wonderful explanations they have provided for them. 
- http://geeksforgeeks.org/
- https://www.redblobgames.com/
- https://stackoverflow.com/
- http://www.cplusplus.com/
- https://en.cppreference.com/w/
- and countless other computer science websites!
