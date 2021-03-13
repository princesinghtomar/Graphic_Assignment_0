# Assignment 0 (OpenGL)
## Installations :
> sudo apt-get update

> sudo apt-get install cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev libxi-dev

## Build :
> cd folder/where/repository/is/stored

> cd repository/name

> cmake .

> make

> If these steps didn't worked try again after removing CMakeCache.txt if present

## Execute :
> ./executables

## make changes :
- Code is present in `source` folder, So all required changes can be made by changing `main.cpp` and other related files.

## Keys controls :

### Move Camera :

> q : move camera right

> w : move camera left

> e : move camera up

> r : move camera down

> t : move camera backward

> y : move camera forward

### Spin Camera :

> x : spins camera around object

### Teleport Location :

``` 
Key : j :     cameraPos   =   (0.0f,0.0f,3.0f)
              cameraFront =   (0.0f,0.0f,-1.0f)
              cameraUp    =   (0.0f,1.0f,0.0f)
```

``` 
Key : k :     cameraPos   =   (0.0f,3.0f,0.0f)
              cameraFront =   (0.0f,-1.0f,0.0f)
              cameraUp    =   (0.0f,0.0f,1.0f)
```
``` 
Key : l :     cameraPos   =   (3.0f,0.0f,0.0f)
              cameraFront =   (-1.0f,0.0f,0.0f)
              cameraUp    =   (0.0f,1.0f,0.0f)
```
### Move Object :

> a : move object right

> s : move object left

> d : move object up

> f : move object down

> g : move object backward

> h : move object forward

### Spin Object :

> z : spin camera around y-axis