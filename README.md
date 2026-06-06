&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;<img width="300" height="300" alt="Untitled\_design\_1\_-removebg-preview" src="https://github.com/user-attachments/assets/c83234c9-99d2-4c24-aa02-97874ef1eb81" />

 # &emsp;&emsp;&emsp;&emsp;Hello World! Welcome to RayView!


# RayView?

RayView is meant to be a modular and efficient solution to displaying PPM images of all shapes and sizes. This was primarily started as a way to quickly view PPM files I generated while playing around with Ray-Tracing algorithms. Because of this, I mainly focused on tailoring everything to my use case, which will probably lead to some issues if anyone else tries to use this. So please, don't be shy to create a pull request telling me off because of some quirky change I made to better suit myself as this project is meant to be a useful tool to any who need it.

# Features

### Unrestricted image height and width
No restrictions are placed on the height and width a PPM file can have, simply ensure their values are in the correct position in the file and the program will run.

### Arbitrary file extension
As recommended by the [Netpbm](https://netpbm.sourceforge.net/) wiki, any file extension is accepted as long as the format is correct. However be warned, only the .TXT and .PPM file extensions have been thoroughly tested as of now, but this will likely change in the near future.

# Compilation

### Linux
Compiling RayView for linux is simple. First, clone the repo.\
`git clone https://github.com/LKagee/RayView`

Once in the 'src' directory, compile the project using gcc (Please note that while other compilers may work, only gcc has been tested for this project.\
`gcc main.c -lSDL2 -o rayview`

SDL2 will need to be installed to compile this project, if on windows, please follow this [tutorial](https://wiki.libsdl.org/SDL2/Installation) on how to get an SDL binary. For Arch-linux users, simply use pacman to install SDL2.\
`sudo pacman -S sdl2`

When executing this project, atleast one argument, `<file>`, is expected as the path for the ppm file to be viewed. A few examples are given in this repository.

### spheres.ppm
<img width="640" height="280" alt="Screenshot 2026-06-05 230239" src="https://github.com/user-attachments/assets/814ac9cd-6eb1-4462-b5a3-129458a5f3cc" />

### grid.ppm
<img width="640" height="280" alt="Screenshot 2026-06-05 230626" src="https://github.com/user-attachments/assets/98adbdae-bfe5-40aa-8b8d-0b345aff4258" />

### random.ppm
<img width="640" height="280" alt="Screenshot 2026-06-05 230732" src="https://github.com/user-attachments/assets/7f908ffb-c3e8-4290-90f6-83ef72e4c428" />

To execute with spheres.ppm as the `<file>` argument, assuming we are in the 'src' directory, simply type. \
`./rayview ../spheres.ppm > output.txt`

For now, redirecting file output to a .TXT or some other file is necessary because the program spits out alot of debug information that will clutter the screen if its not directed somewhere. THIS WILL BE CHANGED SOON.

