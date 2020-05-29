# fillit
Fillit is a [42-network](https://www.codam.nl/en/the-42-network) project which involves discovering and getting acquainted with a recurrent problem in programming: the search of an optimal solution among a very large number of possibilities in a reasonable amount of time. The purpose of this project is to take a file containing a list of tetriminos to sort them in the smallest square possible.
The program takes a file containing a list of Tetrimino's as parameter and prints the square with tetriminos to the standard output.

## Compiling
Run ```make```, an executable called ```fillit``` should compile directly. Please submit an issue if you run into any.

## Tetriminos
<img src="images/Tetriminos.png" width="300"></img>

A Tetrimino is a 4-blocks geometric figure you probably already heard of, thanks to the popular game Tetris. The ```tetriminos``` folder contains three example files with Tetrimino's. The Tetrimino's are represented like this:
```
cat tetriminos/list1
###.
..#.
....
....

....
.###
..#.
....

....
....
####
....

```

## How to use?
After creating the executable file, ```fillit``` can be executed by giving it a Tetrimino-file as parameter e.g.:

```./fillit tetriminos/list1```

In this case, the output looks like shown below. Note that to differentiate the Tetrimino's, all of them are assigned a uppercase letter starting with 'A'.

```
.AAA
BBBA
.B..
CCCC
```

## Specifications
Apart from finding the smallest possible square to fit all Tetrimino's, another requirement is that the algorithm must place all Tetriminos as far as possible in the top-left corner. Tetriminos at the beginning of the given list have precedence over the Tetrimino's that come later in the list.

Fillit is a project that introduces the concepts of **recursion** and **time complexity**, which are important concepts in computer science. The method used in this project is a **Brute Force Algorithm** with some optimization techniques. Bruteforcing basically means trying all possible configurations of Tetriminos until a solution is found. A great benefit of this method is that if there are one or more solutions, it will always find the best solution. A major drawback is that calculation time increases drastically as the amount of given Tetrimino's increases.

The gif below shows an example of how the algorithm finds the solution of ```./fillit tetriminos/list1``` using recursion:

<img src="images/example1.gif" width="100"></img>

It starts with placing the first Tetrimino 'A' in the upper-left corner. Since it succeeded, it moves on to the next Tetrimino 'B' and places it as far in the upper-left corner as possible. Now it's time to place the third Tetrimino 'C', but it fails to do so in the current configuration. The program traces back to the previous Tetrimino 'B' and moves it to the next available spot on the grid. Next, it retries to place Tetrimino 'C', but again it fails to do so. When it tries to move over Tetrimino 'B' again this fails as well, so it needs to trace all the way back to Tetrimino 'A' to move it over to the next spot in the grid. After that Tetrimino's 'B' and 'C' are placed without any reconfigurations.

Everytime the program tried all possible configurations of Tetrimino's it increases the grid-size with 1 and tries all over again until it finds a solution. This way of calculating is fine for a small amount of tetrimino's, but becomes problematic very fast when more Tetrimino's are added to the input list since this algorithm has a **factorial time complexity**. This means that a random list of twenty Tetrimino's can have around 2,432,902,008,176,640,000 (20!) permutations which is obviously a very big amount. However, in the scope of this project this algorithm is more than sufficiënt since it only needs to work for a small number of Tetrimino's.

## Takeaways
- A solid way of input input validation is very important to prevent your program to make unexpected errors when it is given invalid input.
- During this project I learned about the concept of time complexity, and that it is important to know that different algorithms can have different time complexities. To choose the most suitable algorithm, it is important to think about what you want your program to accomplish. Do you want to make it work only for a small amount of information? Then bruteforcing is almost always a sufficiënt solution. However if your program needs to work fast for a lot of data, then you should probably look into more efficiënt algorithms.
- Recursion can be a confusing concept for a beginner programmer, but during this project I got a lot more acquainted with recursive thinking and how it can benefit your program. When used in the right way it can be a very elegant method that can offer a lot of creative solutions.
- One of my learning objectives was to become more confident in using pointers, and I learned how useful they are.
- I also wanted to practice with using structs, and just like learning to use pointers during this project I found out how useful structs are to make information accessible throughout the whole of your program.
