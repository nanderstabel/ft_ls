# ft_ls
ft_ls is a [42-network](https://www.codam.nl/en/the-42-network) project which involves recreating the ```ls``` command which is a command-line utility that lists the content of one or more directories on the standard output. The ```ls``` command supports a variety of options and a bunch of them are present in this project as well. The ```ls``` command is one of the first commands you learn as a beginner programmer. 

For more information about this project, see [ft_ls.en.pdf](https://github.com/nanderstabel/ft_ls/blob/master/ft_ls.en.pdf).

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

## Challange
Allowed functions for the mandatory part are ```write```, ```opendir```, ```readdir```, ```closedir```, ```stat```, ```lstat```, ```getpwuid```, ```getgrgid```, ```listxattr```, ```getxattr```, ```time```, ```ctime```, ```readlink```, ```malloc```, ```free```, ```perror```, ```strerror``` and ```exit```. Everything else is forbidden. Other functions can be used for bonus, but their use must be justified.

## Takeaways
- Because of the many functions I was unfamiliar with before starting this project I had to practice with them. There is nothing wrong with practicing ofcourse, but the result was that some parts of my program became quite messy and I had to rewrite the code a couple of times. This made me realize the importance of planning ahead and of working in a structured way.
- During this project I have gotten a better understanding of allocating and free-ing memory.
- I got familiar with working with the operating systems API's.

## Sources
- [ls man-page](https://www.man7.org/linux/man-pages/man1/ls.1.html)
