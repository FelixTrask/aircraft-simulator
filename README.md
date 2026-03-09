# Aircraft Simulator

This project is a simple aircraft attribute simulator, given values such as mass, wingspan, wing area, thrust, etc. it will output values such as the lift, drag, and TWR of the plane. There's also two graphs created for lift/velocity and drag/velocity, however the lift/velocity graph is dysfunctional.

The program is written in C++, and it uses GLFW, ImGUI and ImPlot to render the windows.

---

## How To Use:

CMakeLists are included. Make sure that you have ***cmake*** and ***make*** installed.

Also make sure that you have ***GLFW binaries installed on your computer***.

Once you clone the repository, open it in your terminal. You should create a folder called `build`, and `cd` into it. 

Next, you should run
```bash
cmake ..
```
on the folder, and the necessary build files will be generated. After running:
```bash
make
```
you'll be able to start the program using
```bash
./simulator
```

Example values for the simulator can be found below, or you can input your own.

## EXAMPLE VALUES:

**Drone**
```
Mass (kg): 5
Wingspan (m): 2
Wing Area (m²): 0.6
Thrust (N): 80
CD0: 0.03
Oswald Efficiency: 0.8
Velocity (m/s): 18
```

**Light Plane**
```
Mass (kg): 1100
Wingspan (m): 11
Wing Area (m²): 16.2
Thrust (N): 2700
CD0: 0.025
Oswald Efficiency: 0.8
Velocity (m/s): 60
```

**Jet**
```
Mass (kg): 70000
Wingspan (m): 35.8
Wing Area (m²): 124.6
Thrust (N): 240000
CD0: 0.02
Oswald Efficiency: 0.85
Velocity (m/s): 230
```

**Impossible plane**
```
Mass: 500
Wingspan: 10
Wing Area: 20
Thrust: 100
CD0: 0.04
Oswald Efficiency: 0.7
Velocity: 10
```

## TODO:
- Fix the lift/velocity graph