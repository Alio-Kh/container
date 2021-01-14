import os

os.system("mkdir proc")
os.system("mkdir bin")
os.system("mkdir dev")
os.system("mkdir lib")
os.system("mkdir lib64")
os.system("mkdir usr")

os.system("sudo cp -r /bin ./bin")
os.system("sudo cp -r /lib ./lib")
os.system("sudo cp -r /dev ./dev")
os.system("sudo cp -r /lib64 ./lib64")
os.system("sudo cp -r /usr ./usr")
