# Quadratic equation <img width="40" height="40" alt="image" src="https://github.com/user-attachments/assets/d5ae854c-cf7f-4483-9810-a7060f2e2f90" />
#### What is this for?  
This is code writed by *FID* on *[MIPT](https://eng.mipt.ru/) summer school* to get familiar with writing large progect. 
## Main features
* Sovle the equation
* Parse comand line flags, with scalability
* **Show graphics** using [raylib](https://www.raylib.com/)
* **Parse and bring** the quadratic equation to standart form
* Colorful console output
* Support **unitest**
* Doxygen
## How to use
#### Supported comand line flags
* `--hand` to input coefficents separatly
* `--pars` to input quadratic equations with x instead of just coefficents
* `--file filename.txt` to get input from file instead of comand line
* `-c NUM` to input coefficents NUM times (1 by default)
* `--vis` to show quadratic equations on graphics
* `--help` to get reference
## Examples  
### Simple usage  
<img width="409" height = "45" alt="image" src="https://github.com/user-attachments/assets/21bedf16-41b1-4c3a-a55c-1a1ab63d209c" />  

### With count flag
<img width="447" height="75" alt="image" src="https://github.com/user-attachments/assets/73e30d16-1d0d-4211-aace-3b58e15e1f63" />  

### Parse and bring the quadratic equation  
For enable parser use flag `--pars`  
<img width="427" height="60" alt="image" src="https://github.com/user-attachments/assets/de63f443-2c28-4573-b0ee-ac4e27c7458a" />  
### Show graphics  
Graphics show linear, quadratic equations and their roots  
For enable graphics use flag `--vis`, on graphics show **only** last equations  
<img width="350" height="350" alt="image" src="https://github.com/user-attachments/assets/bd5628e0-bae8-4951-83eb-b5b1bf5f5519" /><img width="20"><img width="350" height="350" alt="image" src="https://github.com/user-attachments/assets/5d26fcff-8cd7-4df6-9809-d452053cbd22" />  
Graphics UI suport scalable grid and hotkeys
#### Supported hot keys
* O - return to (0, 0)
* H - return to vertex of parabola
* X - scale only in OX axis
* Y - scale only in OY axis
* S - set standart scale
* ESC - close program
