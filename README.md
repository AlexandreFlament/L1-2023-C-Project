# L1-2023-C-Project

## Compiling
Use the following command in the terminal: "gcc main.c shapes.c storage.c"

## Running
If you do not have an "Application.exe" file, compile the project as seen before.  
If you have an executable file, run it and follow the program instructions (Only A/B/F as of now)

## How To use it

### The options
Upon running the program, you will be presented with a list of options, each doing their own magic as explained further down.  
To select an option, just write the letter associated with said option (Upper and Lower case letter work). The menu looks as follows:  
```
Please select an action:
    A. Add a shape
    B. Display the list of shapes
    C. Delete a shape (WIP)
    D. Draw the shapes (WIP)
    E. Help (WIP)
    F. Exit
 >> Your choice:
 ```

### Option A
Used to add shapes to the list of shapes. Once selected it will present you with a list of shapes to chose from.
```
>> Your choice: A
    Please select an action:
        1. Add a point
        2. Add a line
        3. Add a circle
        4. Add a square
        5. Add a rectangle
        6. Add a polygon
        7. Return to previous menu
     >> Your choice: 
```
Selecting one will ask you to fill out the information of said shape.  
`For a Polygon:`
```
The program will stop once the first and last point are the same
         >> Enter the x and y coordinates the point 0: 0 0
         >> Enter the x and y coordinates the point 1: 2 2
         >> Enter the x and y coordinates the point 2: 5 5
         >> Enter the x and y coordinates the point 3: 0 0
```

### Option B
Used to display all the shapes you previously added. Will display like so:
```
POINT   | P : 0 0
        | ID: 1
SQUARE  | P : 7 6
        | L : 5
        | ID: 2
POLYGON | N : 4
        | P0: 0 0
        | P1: 2 2
        | P2: 5 5
        | P3: 0 0
        | ID: 3
```

### Option C
Not implemented yet.  

### Option D
Not implemented yet.  

### Option E
Not implemented yet.  

### Option F
Will stop the program, deleting all shapes and layers.
