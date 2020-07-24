# nonsense_lab::Compile / Run guide

## Compile

Oh, **Compile**. What a nice word.

All of the codes in this repository is written in C++, and so, for the \*nix users and also the **Windows** users who cannot run the Windows Application normally may install a holy software -- **g++**.

### Linux

In Linux (eg. Ubuntu), you may type this in your terminal:

`sudo apt-get install g++`

### Mac OS

In Mac OS, you may type this in your terminal:

`g++`.

If your computer hasn't `g++` installed, a cute little alert box will pop up, which says:

```
The "g++" command requires the command line developer tools...
```

Choose **Install** to get only the command line tools.

After installation, type `g++` in the Terminal, press the <kbd>Return</kbd> key, and you may see this in your terminal:

```
clang: error: no input files
```

And there you go.

### Windows

Go [here](https://osdn.net/projects/mingw/releases/). Click, download and install the **mingw-get-setup.exe**.

Mark the following packages for installation:

```
mingw32-base-bin
mingw32-binutils-bin
mingw32-gcc-bin
mingw32-gcc-lic
mingw32-gcc-g++-bin
```

Then, click `Installations -> Apply Changes`, and your dear `g++` might be installed soon.

Don't forget to [Install the MinGW Tools for C/C++](https://rose-hulman.edu/class/csse/resources/MinGW/installation.htm).



Nearly all of the codes are written in C++17 (and above), and if you are sure you installed the right and newest version of `g++`, you may type this in your terminal (Or for Windows Users, the Command Prompt):

`g++ -o [output-filename] [input-filename] -std=c++2a`

The command above tells the `g++` compiler to use the newest standard -- "C++ 20", to check and compile your code. You replace the words in the brackets with these name:

`[output-filename]`: replace it with any name you want. That's the name of the executable application.

`[input-filename]`: replace it with the source code file you downloaded from **nonsense-lab**. 



## Run

After compiling, it's the time for the users to enjoy the applications provided by **nonsense-lab**.

### Linux & Mac OS

type this in your terminal:

```
./[output-filename]
```

**Note**: Replace `[output-filename]` to the name you have just set.

For example, if I compile **GR** like this:

```
g++ -o gr gr.cpp -std=c++2a
```

then, I just need to type this in my terminal:

```
./gr
```

and then, I can enjoy **GR**.

Know that?

### Windows

TYPE THE OUTPUT FILENAME DIRECTLY IN THE COMMAND PROMPT. IT'S THAT SIMPLE.

