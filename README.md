# wordlist-rewriter
This command line utility is made to rewrite wordlists based on certain conditions. For example you can only allow numbers from a certain wordlist. Or maybe not allow them.
It is mainly intended for those who want to make wordlists with certain criterias from a wordlist that has lines which do not meet those criterias. it's intended for bruteforcing targeted wordlists. I don't know if you can use it for other things.

## Dependencies
only python 3. for the python version
make and gcc if you want to compile the C version (you probably won't have to, there's a compiled binary already)

## Differences
The python version is the most bug free and the most tested. It's also the first to get new features and bug fixes. But at the cost of speed. The binary version is way faster. So in read world scenarios, it is the more useful one. (note that this project is for fun and for sharpening my skills buy training. that's all)

## Installation
first clone
```bash
git clone https://github.com/medanisjbara/wordlist-rewriter
```
for the python version
```bash
sudo cp wordlist-rewriter/rewrite.py /usr/bin/rewrite
sudo chmod +x /usr/bin/rewrite
```
for the C compiled binary
```bash
sudo cp wordlist-rewriter/rewrite /usr/bin/
```
If you want to compile it yourself.
```bash
make
sudo cp wordlist-rewriter/rewrite /usr/bin/
```

## Usage

type `rewrite -h` for help


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change. Mainly because I would like to learn about why those changes should be made.
If there's something you didn't like or you have a suggestion. Please open an issue as it'll help making this command line utility better.(and maybe help it get a bit more popular. I had zero interactions since day one even tho I thought that what I did was cool).
