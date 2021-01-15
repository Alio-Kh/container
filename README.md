# Container
This is a very simple container made using C language 

## Instalation 
You need to install a Cgroup tool before 
```bash
sudo apt-get install libcgroup1 cgroup-tools
```

## Run your Container

Before runing your container you should build a new root files system for your container
Run the following command in your prompt for building a new root
```bash
python3 build-root.py
```
>*NB: this command may take much time to run*


To run your container, run and execute the container.c file using the following commands
```bash
gcc -o container container.c
sudo ./container hostname # hostname is an Argument
```
if you dont have gcc installed run the following commands
```bash
sudo apt update
sudo apt install build-essential
```

## Test your Container
#### Memory limit test
For testing the memory limit of your container you can run and execute hungry.c file in the the container's shell 
```bash
gcc -o hungry hungry.c
./hungry
```

Or you can run the python script hungry.py using the following command
```bash
python3 hungry.py
```

## Authors and acknowledgment
KHYATTI ALI &&
EL GHAZI ILYASS

## License
[GNU](https://www.gnu.org/licenses/why-not-lgpl.html)
