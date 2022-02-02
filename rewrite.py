#!/usr/bin/python3
from sys import argv

infile,outfile,exclude,exfile,minlen,maxlen,nonums= ['']*7
l = []

def strip(input,output,exceptions):
    if not exceptions:
        print('\n\n No option specified, exiting\n\n')
        exit()
    if output=='-':
        def write(lines):
            for line in lines:
                print(line,end='')
    elif output:
        f = open(output,'w')
        write = f.writelines
    else:
        f = open(f'{input}-filtred','w')
        write = f.writelines
    content, clear = [], True
    for line in open(input,errors='ignore'):
        exB = False
        for exception in exceptions:
            if exception(line):
                exB = True
                break
        if exB: continue
        content.append(line)
        WBCF = False
        if len(content)>5000:
            write(content)
            content = []
            WBCF = True
            print('.',end='')
    if not WBCF:
        write(content)
    print('done')

def help():
    print("""USAGE: rewrite [-i] <input> [OPTIONS]

 OPTIONS:

  -o FILE       specify output file. generated wordlist will be saved to FILE
                ex: -o wordlist.txt   will save words to the file wordlist.txt
                if the output file is not specified, the output will be written
                to input-rewritten

  -e FILE       specify an exclude file. everything on the exclude file will not
                be shown in the output file


  -min MIN      set minimum word length to MIN (number)
  -max MAX      set maximum word length to MAX (number)

  -nn           numbers (?d)*\\n will not be allowed
  -nnl LEN      numbers (?d){L}\\n will be allowed
                ex: -nnl 8    all numeric 8 digit numbers won't pass
                ex: -nnl 8 9  all numeric 8 & 9 digit numbers won't pass

                """)


def parse():
    global infile,outfile,exclude,exfile,minlen,maxlen,nonums
    i = 0
    while i<len(argv)-1:
        i+=1
        if argv[i]=='-h':
            help()
            exit()
        if argv[i]=='-i':
            if infile:
                print(argv[i],'was given as input but',infile,'was already specified')
            else:
                i+=1
                infile = argv[i]
                continue
        if argv[i]=='-o':
            i+=1
            outfile = argv[i]
            continue
        if argv[i]=='-e':
            i+=1
            exclude = True
            exfile = argv[i]
            continue
        if argv[i].startswith('-m'):
            i+=1
            if argv[i].isnumeric():
                if argv[i-1]=='-min':
                    minlen = int(argv[i])
                elif argv[i-1]=='-max':
                    maxlen = int(argv[i])
                else:
                    help()
                    exit()
                continue
            else:
                help()
                exit()
        if argv[i]=='-nn':
            nonums = True
            continue
        if argv[i]=='-nnl':
            while True:
                i+=1
                if i==len(argv): break
                if argv[i].isnumeric():
                    l.append(int(argv[i]))
                else:
                    i-=1
                    break
            if not l:
                help()
                exit()
            else:
                continue
        if infile:
            print('Unknown Option',argv[i])
            print('if you mean',argv[i],'as input',infile,'is already specified')
            help()
            exit()
        else:
            infile=argv[i]

def gen():
    exceptions = []
    for n in l:
        exceptions.append(lambda line:line.strip('\n').isnumeric() and len(line.strip('\n'))==n)
    if minlen:
        exceptions.append(lambda line:(len(line.strip('\n')))<minlen)
    if maxlen:
        exceptions.append(lambda line:(len(line.strip('\n')))>maxlen)
    if nonums:
        exceptions.append(lambda line:line.strip('\n').isnumeric())
    if exclude:
        print("exclude function haven't been implemented yet")


    strip(infile,outfile,exceptions)

if __name__=='__main__':
    if len(argv)<2:
        print('rewrite: you must specify a worldlist file')
        print('Try \'rewrite -h\' for more information.')
        exit()
    try:
        parse()
        gen()
    except KeyboardInterrupt:
        print('\n\n ^C Interrupted')
    except IOError:
        print('\n\n IOError received, exiting\n\n')
        exit()
