# Container
Container is a very simple container made using C language 
## Instalation 
You need to install a Cgroup tool before 
```bash
sudo apt-get install libcgroup1 cgroup-tools
```
## Run your Container
Then run and execute the container.c file using the following commands
```bash
gcc -o container container.c
sudo ./container
```
if you dont have gcc installed run the following commands
```bash
sudo apt update
sudo apt install build-essential
```

## Test your Container
### Memory limit test
For testing the momory limit of your container you can run and execute hungry.c file in the the container's shell 
```bash
gcc -o hungry hungry.c
./hungry
```

Or you can run the python script hungry.py using the following command
```bash
python3 hungry.py
```

## Authors and acknowledgment
KHYATTI ALI
EL GHAZI ILYASS
