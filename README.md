# L1-2023-C-Project


## Compiling
Use the following command in the terminal: "gcc main.c shapes.c storage.c"


## Running
If you do not have an "Application.exe" file, compile the project as seen before.  
If you have the executable file, run it and follow the program instructions.


## How To use it

### The options
Upon running the program, you will be presented with a list of options, each doing their own magic as explained further down.  
To select an option, just write the letter associated with said option (Upper and Lower case letter work).
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
Used to display all the shapes you previously added.
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


## How does it work ?

### Shapes

There exist a structure for a each of the available shapes **(POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON)** and functions associated to it **(create_X, delete_X, print_X)**  
```
typedef struct {
    int x;
    int y;
} Point;
```
`create_X` dynamically allocates memory for created shape using malloc and sets the value of the structure associated to it with the arguments given to the function.  
```
Point *create_point(int px, int py) {
    Point *point = malloc(sizeof(Point));
    if (point != NULL) {
        point->x = px;
        point->y = py;
    }
    return point;
}
```
`delete_X` free the memory allocated to a shape using free().  
```
void delete_point(Point *p) {
    free(p);
}
```
`print_X` displays the shape in the terminal in the same format as seen in Option B. Note that there is a '\n       ' as it becomes useful later on when using the function.
```
void print_point(Point *p) {
    printf("POINT   | P : %i %i\n       ", p->x, p->y);
}
```
```
POINT   | P : 0 0
       
```

### The shape structure

#### Structure

Compared to the previous shapes, the shape structure is the one that is used to store the shapes for future use such as displaying.
```
typedef struct {
    int id;
    SHAPE_TYPE shape_type;
    void *ptrShape;
} Shape;
```

The id is obtained through a function that increment the global_id (Positive and starts at 0) and returns it, meaning that the first id would be 1.
```
unsigned int global_id = 0;

unsigned int get_next_id() {
    global_id++;
    return global_id;
}
```

The shape_type identifies what the shape in the structure is and is the list of all the shapes that are defines.
```
typedef enum { POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON} SHAPE_TYPE;
```

And finnaly, the ptrShape is a pointer that directs to the stored shape.  
   
#### Operations on a shape

Just as for individual shape, there exist a `create_X_shape` that's in charge of creating a shape for a given type.  
It dynamically memory for a shape, then calls the function to create the shape of type X, who is then associated with the ptrShape of the shape.
```
Shape *create_point_shape(int x, int y) {
    Shape *shp = create_empty_shape(POINT);
    Point *p = create_point(x,y);
    shp->ptrShape = p;
    return shp;   
}
```
To delete a shape, `delete_shape` that is the same for any type, using free() to free the memory allocated to the shape.
```
void delete_shape(Shape *shp) {
    free(shp);
}
```
And finally, `print_shape` that is the same for any shape again.  
Using a switch case, it detects what is the type of the shape and which `print_x` to call then adds the ID of the shape to the displayed result.
```
void print_shape(Shape *shp) {
    switch (shp->shape_type) {
    case POINT:
        print_point(shp->ptrShape);
        break;
    case LINE:
        print_line(shp->ptrShape);
        break;
    .
    .
    .
    default:
        printf("Invalid shape");
        break;
    }
    printf(" | ID: %i", shp->id);
}
```
