# Pacman
Pacman in C++ using SFML

This is a generic pacman-like game. I say generic, because you can easily substitute
your algorithms for: map generation, pacman behavior, ghosts behavior, level difficulty.

# Launch
In order to launch program you firstly need to build it
```bash
mkdir build
cd build
cmake ..
make pacman_app
```

And then link textures for executable file
```bash
cd bin
ln -s ../../assets/ assets
```

Now you can run the program
```bash
./pacman
```
