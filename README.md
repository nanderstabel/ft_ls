# ft_ls
ft_ls is a [42-network](https://www.codam.nl/en/the-42-network) project which involves recreating the ```ls``` command which is a command-line utility that lists the content of one or more directories on the standard output. The ```ls``` command supports a variety of options and a bunch of them are present in this project as well. The ```ls``` command is one of the first commands you learn as a beginner programmer. 

## Compiling
Run ```make```, an executable called ```ft_ls``` should compile directly. Please submit an issue if you run into any.

## How to use?
After creating the executable file, ft_ls can be used like this:

```./ft_ls [OPTIONS] [FILES]```

It is not obligatory to specify an option or a file. If no file is specified ```ft_ls``` will list the current directory.

## Options
- **-a**: do not ignore entries starting with .
- **-d**: list directories themselves, not their contents
- **-f**: do not sort
- **-g**: like -l, but do not list owner
- **-l**: use a long listing format
- **-m**: fill width with a comma seperated list of entries
- **-r**: reverse order while sorting
- **-R**: list subdirectories recursively
- **-t**: sort by time, newest first
- **-T**: assume tab stops at each COLS instead of 8

## Takeaways
- A solid way of input input validation is very important to prevent your program to make unexpected errors when it is given invalid input.
- During this project I learned about the concept of time complexity, and that it is important to know that different algorithms can have different time complexities. To choose the most suitable algorithm, it is important to think about what you want your program to accomplish. Do you want to make it work only for a small amount of information? Then bruteforcing is almost always a sufficiënt solution. However if your program needs to work fast for a lot of data, then you should probably look into more efficiënt algorithms.
- Recursion can be a confusing concept for a beginner programmer, but during this project I got a lot more acquainted with recursive thinking and how it can benefit your program. When used in the right way it can be a very elegant method that can offer a lot of creative solutions.
- One of my learning objectives was to become more confident in using pointers, and I learned how useful they are.
- I also wanted to practice with using structs, and just like learning to use pointers during this project I found out how useful structs are to make information accessible throughout the whole of your program.

## Sources
- [ls man-page](https://www.man7.org/linux/man-pages/man1/ls.1.html)
