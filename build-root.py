import os

os.system("mkdir proc")
os.system("mkdir bin")
os.system("mkdir dev")
os.system("mkdir lib")
os.system("mkdir lib64")
os.system("mkdir usr")

os.system("sudo cp -r /bin/* ./bin/")
print("bin is created")
os.system("sudo cp -r /lib/* ./lib/")
print("lib is created")
os.system("sudo cp -dev/* ./dev")
print("dev is created")
os.system("sudo cp -r /lib64/* ./lib64/")
print("lib64 is created")
os.system("sudo cp -r /usr/* ./usr")
print("usr is created")
