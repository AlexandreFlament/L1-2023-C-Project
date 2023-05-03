# L1-2023-C-Project


## Compiling
Use the following command in the terminal: "gcc main.c shapes.c area.c"


## Running
If you do not have an "Application.exe" file, compile the project as seen before.  
If you have the executable file, run it and follow the program instructions.


## How To use it

### The Options
Upon running the program, you will be presented with a list of options, each doing their own magic as explained further down.  
To select an option, just write the letter associated with said option (Upper and Lower case letter work).
```
Please select an action:
    A. Add a shape
    B. Display the list of shapes
    C. Delete a shape
    D. Draw the shapes
    E. Help
    F. Exit
 >> Your choice:
 ```

### Option A
Used to add shapes to the list of shapes. Once selected, it will present you with a list of shapes to choose from.
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
Selecting one of them will prompt you to fill out the information of said shape.  
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
Used to remove a shape from the shape list. To use it call it and give it the ID of the shape you want to remove.  
```
Which shaped would you like to removed ? (Use the ID of the shape) ...
```

### Option D
Used to display a grid with the shapes drawn on it.  
```
. . . . . . . . . . . . . . . . . . .
. . . . . . . X X X X X . . . . . . .
. . . . . X X . . . . . X X . . . . .
. . . X X . . . . . # . . . X X . . .
. . . X . . . . . . . . . . . X . . .
. . X . . . # . . . . . # . . . X . .
. . X . . . . . . . . . . . . . X . .
. X . . # . . . . # . . . . # . . X .
. X . . . . . . . . . . . . . . . X .
. X X X X X X X X X X X X X X X X X .
. X . . . . . . . . . . . . . . . X .
. X . . . # . . . . . . . . . . . X .
. . X . . . . . . . . . . . # . X . .
. . X . . . . . . . # . . . . . X . .
. . . X . . # . . . . . . . . X . . .
. . . X X . . . . . . . . . X X . . .
. . . . . X X . . . . . X X . . . . .
. . . . . . . X X X X X . . . . . . .
. . . . . . . . . . . . . . . . . . .
```

### Option E
Used to display information to help the user.  
```
How to see the shapes ? 
There are two ways to do that, seing them as a list or displaying them on a list.
To see the list of shapes, choose option B from where you will see everything you need to know about the shapes you added, including their ID which will be useful when removing a shape.
To display a grid with the shapes drawn on it, choose option D, it will display every shape you added or 'No shape to display' if you didn't add any.

How to remove a shape ? 
First, get the ID of the shape you want to remove from the list of shapes (Option B).
Then, using option C, write the ID of the shape and it will be removed.
Note that there will be no warning or whatever of the sort if the ID is wrong or doesn't exist.

How to exit ? 
Either using option F or with ctrl+c
```

### Option F
Will stop the program, deleting all shapes and layers.


## How does it work ?

### Shapes

There exist a structure for a each of the available shapes **(POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON)** and functions associated to it **(create_X, delete_X, print_X)**  
```c
typedef struct {
    int x;
    int y;
} Point;
```
`create_X` dynamically allocates memory to create a shape using `malloc` and sets the value of the structure associated to it with the arguments given to the function.  
```c
Point *create_point(int px, int py) {
    Point *point = malloc(sizeof(Point));
    if (point != NULL) {
        point->x = px;
        point->y = py;
    }
    return point;
}
```
`delete_X` free the memory allocated to a shape using `free`.  
```c
void delete_point(Point *p) {
    free(p);
}
```
`print_X` displays the shape in the terminal in the same format as seen in Option B. Note that there is a '\n       ' as it becomes useful later on when using the function.
```c
void print_point(Point *p) {
    printf("POINT   | P : %i %i\n       ", p->x, p->y);
}
```
```
POINT   | P : 0 0
       
```

### The Shape Structure

Compared to the previous shapes, the `Shape` structure is the one that is used to store the shapes for future uses such as displaying.
```c
typedef struct {
    int id;
    SHAPE_TYPE shape_type;
    void *ptrShape;
} Shape;
```

The id is obtained through a function that increment the `global_id` (which is positive and starts at 0) and returns it, meaning that the first id would be 1.
```c
unsigned int global_id = 0;

unsigned int get_next_id() {
    global_id++;
    return global_id;
}
```

The `shape_type` identifies what the `Shape` in the structure is, and is the list of all the shapes that are defined.
```c
typedef enum { POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON} SHAPE_TYPE;
```

And finally, the `ptrShape` is a pointer that directs to the stored shape.  
   
#### Operations on a Shape

Just as for individual shapes, there exist a `create_X_shape` that's in charge of creating a shape for a given type.  
It dynamically allocates memory for a `Shape`, then calls the function to create the shape of type X, who is then associated with the `ptrShape` of the shape. In addition, if isid is 1, an ID will be assigned to the shape using the `get_next_id` function, else it's 0.
```c
Shape *create_point_shape(int x, int y, int isid) {
    Shape *shp = create_empty_shape(POINT, isid);
    Point *p = create_point(x,y);
    shp->ptrShape = p;
    return shp;   
}
```
To delete a shape, `delete_shape` which is used the same for any type, using free() to free the memory allocated to the shape.
```c
void delete_shape(Shape *shp) {
    free(shp);
}
```
And finally, `print_shape` which is the same for any shape again.  
Using a switch case, it detects what is the type of the shape and which `print_x` to call, then adds the ID of the shape to the displayed result.
```c
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

### Area

To store the list of shape aswell as display the grid on which shapes are drawn, we use the `area` structure which is composed of it's width, height, a 2D Array of 1 and 0 to signify whether a pixel is used or not, an array of `Shapes` and finaly the number of shapes in the area.
```c
struct area {
    unsigned int width;
    unsigned int height;
    BOOL** mat;
    Shape* shapes[SHAPE_MAX]; 
    int nb_shape;
};
typedef struct area Area;
```

Several operations can be done on an `area`.  

- Creating an `area`.  
    - Dynamically allocates memory for the structure itself 
    ```c
    Area *ar = malloc(sizeof(Area));
    ```
    - As well as for the Array of `BOOL`  
    ```c
    BOOL **mat = (BOOL**) malloc(sizeof(BOOL*)*height);
    for (int i = 0; i<height; i++) {
        mat[i] = (BOOL*) malloc(sizeof(BOOL)*width);
    }
    ```
    Note that the Array of shapes is static and defined at the creation of the structure through the `SHAPE_MAP` constant which is currently set at 100.  

- Adding a shape to the `area`.  
    Simply adds the `Shape` to the array of shapes and increments by 1 the number of shapes `n`.

- Clearing the `area`.  
    Sets all the elements in the `BOOL` array to `0`.

- Erasing the `area`.  
    Calls `clear_area` and frees all the shapes in the array of shapes using the `delete_shape` function.

- Deleting the `area`.  
    Calls the `erase_area` function and frees the area.

- Draw the `area`.  
    Will first clear the `area` and then draw all the shapes on it. To do so it loops through the `Shapes` and transforms them through the `create_shape_to_pixel` function and then loops through the returned array of `Pixel` to set to 1 the positions of each pixels if they are withing the bounds of the `area`.
    ```c
    clear_area(area);

    int nb_pixels;
    Pixel **pixels;
    for (int shpnb = 0; shpnb<area->nb_shape; shpnb++) {
        pixels = create_shape_to_pixel(area->shapes[shpnb], &nb_pixels);
        for (int pix = 0; pix<nb_pixels; pix++) {
            if (area->height > pixels[pix]->py && pixels[pix]->py >= 0 && area->width > pixels[pix]->px && area->width >= 0) {
                area->mat[pixels[pix]->py][pixels[pix]->px] = 1;
            }
        }
        delete_pixel_shape(pixels, nb_pixels);
    }
    ```

- Print the `area`.  
    Will print the area to the terminal, for each `0` it will print a `.` and for each `1` it wil print an `X`.  
    Note that it will not necessarily print all of the `Shapes` in the area if they were not drawn using the `draw_area` function.

- Remove a `Shape` from the `area`.
    Will go through the area shapes and use the `delete_shape` function on the `Shape` it's at if it's `ID` is the same as the one we want to delete. Once the `Shape` is free'd, we decrement by 1 the position of all the following `Shapes` and decrement by 1 the number of shapes variable.
    ```c
    for (int i = 0; i<area->nb_shape; i++) {
        if (area->shapes[i]->id == shapeid) {
            int j=i;
            delete_shape(area->shapes[i]);
            for (; j < area->nb_shape; j++) {
                area->shapes[j] = area->shapes[j + 1];
            }
            free(area->shapes[j]);
            area->nb_shape--;
            return;
        }
    }
    ```

### Pixel

`Pixel` is a structure used to store "active pixels" at a certain coordinates x and y.  
```c
struct pixel {
    int px;
    int py;
};
typedef struct pixel Pixel;
```
Same as for `area`, `shape` and other structures, we create them through a `create_pixel` function which dynamically allocates memory for a `Pixel` structure and assigns value to x and y based on what value where given in the call of the function. It then returns a pointer to a `Pixel`.  
Deleting them is done through the `delete_pixel` function which simply frees the `Pixel`.  

### Shape to Pixel
In order for a `Shape` to be drawn on an `area` board, we first need to transform it into an array of `Pixel` which is done through different function for each `Shape`.  

- For a `Point` we simply take it's x and y coordinates and put it into a `Pixel` which is then set as the first element of an array which is of size 1 and return said array.
- For a `Line` we us an [algorithm made by Nicolas Flasque](https://perso.halim.info/Cours/pixel_tracer/Tracee_lignes_entre_deux_points_EN.pdf) which is based on a
method using only integers and not floats.  
    The general idea is that to calculate the position of the `Pixel` that a `Line` will occupy, we take as
parameters the start coordinates (x1,y1) and the end coordinates (x2,y2). The pixels of the line are
calculated by shifting between the two positions: (dx,dy).
- For the `Square`, `Rectangle` and `Polygon` we reuse the `pixel_line` function made previously in order to draw the lines between each of their `Point` and add them in one single array which is then returned.
- For a `Circle` we use the [Midpoint circle algorithm](https://en.wikipedia.org/wiki/Midpoint_circle_algorithm).  
To draw a circle, the idea is to generate the pixels of a single octant (1/8), and to deduce the rest by
symmetry. Thanks to this, the number of calculations to be done is reduced.  
The algorithm calculates the points of the circle using only integer values. Thus, the points are not
always exactly on the circle but as close as possible. The algorithm follows a decision process to
determine the next point to be drawn, using an evaluation of the distance between the last drawn
point and the actual circle to determine whether the next point should be diagonal, horizontal or
vertical.  
As we don't know the number of `Pixel` in advance we do the calculation once in order to create allocate memory for the array of `Pixel` before redoing it later to add the `Pixels`.
    ```c
    int x = 0;
    int y = circle->radius;
    int d = circle->radius-1;
    *nb_pixels = 0;

    while (y >= x) {
        *nb_pixels += 8;

        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        } else if (d < 2 * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        } else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }


    Pixel **pixels = malloc(sizeof(Pixel)*(*nb_pixels));
    ```
    ```c
    while (y >= x) {
        px = create_pixel(circle->center->x + x, circle->center->y + y);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->x + y, circle->center->y + x);
        pixels[(*nb_pixels)++] = px;

        px = create_pixel(circle->center->x - x, circle->center->y + y);
        pixels[(*nb_pixels)++] = px;

        .
        .
        .

        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        } else if (d < 2 * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        } else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }
    ```

For each created array of `Pixels`, there is a need to delete them when they have been used, from the come the `delete_pixel_shape` which goes through the array of `Pixel` and frees them, to finnaly free the array itself once it's done with all the `Pixels`.  

Finnaly, to decide which function to choose based on a given shape we use the `create_shape_to_pixel` function which look at the the `Shape SHAPE_TYPE` and returns the result of the corresponding function call using a switch case.  
```c
case POINT:
    return pixel_point(shape, nb_pixels);
    break;
```

### Add Up of Everything

#### Main

After each scanf the `clear_buffer` function is used in order to clear `stdin`, the input buffer. It works by using the `getchar` function until the character obtained is `EOF` (End Of File) or `\n`.  
```c
void clear_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
```

When starting the algorithm for the first time we create an initial `area` of size 20x20 and clear it to initialize all it's elements to 0. 
```
Area *ar = create_area(20, 20);
clear_area(ar);
```

The algorithm then loops until the `running` variable becomes 0 which is obtained through the option F.  
```c
while (running == 1) {

    .
    .
    .
    
}
```

During the loop, it will display the options and ask which one the users want to choose through a `scanf`. Following that, it will act accordingly by determinating what to do with a `switch case`.  
```c
choice = 'Z';
    printf("Please select an action:\n");
    printf("    A. Add a shape\n");
    printf("    B. Display the list of shapes\n");
    printf("    C. Delete a shape\n");
    printf("    D. Draw the shapes\n");
    printf("    E. Help\n");
    printf("    F. Exit\n");
    printf(" >> Your choice: ");
    scanf("%c", &choice);
    clear_buffer();
    printf("\n");

    switch (choice) {
        case 'F':
        case 'f':
            running = 0;
            break;
        
        case 'A':
        case 'a':
            optionA(shape_list);
            printf("\n");
            break;
            
        case 'B':
        case 'b':
            if (shape_list->shp == NULL) {
                printf("No shape to display\n\n");
                break;
            }
            printf("\n");
            print_shape_node(shape_list);
            printf("\n");
            break;

        case 'C':
        case 'c':
            int chosenid = 0;
            printf("Which shaped would you like to removed ? (Use the ID of the shape) ");
            scanf("%i", &chosenid);
            clear_buffer();
            remove_shape(ar, chosenid);
            printf("\n");
            break;

        case 'D':
        case 'd':
            draw_area(ar);
            print_area(ar);
            printf("\n\n");
            break;

        case 'E':
        case 'e':
            // Prints information on how to use this algorithm
            break;

        default:
            break;
}
```

In the case that option B or E (Display the list of shapes / Help) is choosen, we wait for the user input to move on with redisplaying the options.  
```c
if (choice == 'B' || choice == 'b' || choice == 'D' || choice == 'd') {
    printf("Press enter to continue...");
    scanf("%c", &c);
    clear_buffer();
}
```

#### Option A function

The first thing that is done is to ask the user what shape he wants to add amongst the available shapes. If he gave a choice that is not among the possible choices, the program will redisplay and reask for his choice until it's correct. To do so, we check if his choice is between 1 and 7.
```c
while (choice < 1 || choice > 7 ) {
    printf("    Please select an action:\n");
    printf("        1. Add a point\n");
    printf("        2. Add a line\n");
    printf("        3. Add a circle\n");
    printf("        4. Add a square\n");
    printf("        5. Add a rectangle\n");
    printf("        6. Add a polygon\n");
    printf("        7. Return to previous menu\n");
    printf("     >> Your choice: ");
    scanf("%i", &choice);
    clear_buffer();
    printf("\n");
}
```

Once the user choice is confirmed, we act accordingly by asking the necessary parameters for the `Shape`, filling the created empty shape with the given parameters and adding it to the `area` through the `add_shape_to_area` function.  
```c
switch (choice) {
    case 1:
        printf("         >> Enter the x and y coordinates: ");
        scanf("%i %i", &x, &y);
        clear_buffer();
        add_shape_to_area(ar, create_point_shape(x,y, 1));
        break;
    
    .
    .
    .
    
    default:
        break;
}
```

#### Option B
First, if the number of `Shapes` in the `area` is 0, we print that there is no shape to display and break to get out of the switch case.
```c
if (ar->nb_shape == 0) {
    printf("No shape to display\n\n");
    break;
}
```
However if there are more than 0 shapes, we go through the list of shapes and use the `print_shape` function to print every `Shape`.
```c
for (int i = 0; i < ar->nb_shape; i++) {
    print_shape(ar->shapes[i]);
    printf("\n");
}
```

#### Option C
We ask the user for which `Shape` he wants to remove through the `ID` he is asked to give, we then call the `remove_shape` function with the ID the user gave.
```c
int chosenid = 0;
printf("Which shaped would you like to removed ? (Use the ID of the shape) ");
scanf("%i", &chosenid);
clear_buffer();
remove_shape(ar, chosenid);
printf("\n");
```

#### Option D
We first update the area through the `draw_area` function then print it on screen with `print_area`.
```c
draw_area(ar);
print_area(ar);
printf("\n\n");
```

#### Option E
We simply use `printf` to display information about the algorimth and how to use it on the screen.