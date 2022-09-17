# wordlist-rewriter
This command line utility is made to rewrite wordlists based on certain conditions. For example you can only allow numbers from a certain wordlist. Or maybe not allow them.
It is mainly intended for those who want to make wordlists with certain criterias from a wordlist that has lines which do not meet those criterias. it's intended for bruteforcing targeted wordlists. I don't know if you can use it for other things.

## Dependencies
* Only python 3. for the python version.
* Make and gcc if you want to compile the C version (you probably won't have to, there's a compiled binary already).
* Nothing if you want to try the binary (included with the source code).

## Differences
* The python version is the most bug free and the most tested. It's also the first to get new features and bug fixes. But at the cost of speed.
* The C file is version is way faster. So in read world scenarios, it is the more useful one.
* The binary included is just the result of compiling the C file.

(note that this project is for fun and for sharpening my skills buy training. that's all)

## Installation
First clone

```bash

git clone https://github.com/medanisjbara/wordlist-rewriter

```
Next cd 

```bash

cd wordlist-rewriter

```

Next (For install the python version)

```baah

make install_py

```

Next (For install the C version)

```baah

make install_c

```
Note by default it will installed to ~/.local/bin so make sure your ~/.local/bin folder is in your $PATH environment variable.

Run this command to put your ~/.local/bin folder is in your $PATH environment variable temporary.

```bash

export PATH=$PATH:$HOME/.local/bin

```

Put this line of code in `~/.bashrc` file or `~/.zshrc` or `~/.profile`,etc (depending on your shell) to put your ~/.local/bin folder is in your $PATH environment variable permanent.

Install it to /usr/ (For install the C version)

```bash

PREFIX=/usr/ make install_c

```

Install it to /usr/ (For install the Python version)

```bash

PREFIX=/usr/ make install_py

```

## Usage

type `rewrite -h` for help

## To-do
* Add functionality to the `-e` flag
* Emplement memory allocations in the C version for more efficient RAM usage.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change. Mainly because I would like to learn about why those changes should be made.
If there's something you didn't like or you have a suggestion. Please open an issue as it'll help making this command line utility better.(and maybe help it get a bit more popular. I had zero interactions since day one even tho I thought that what I did was cool).
