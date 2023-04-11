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

### The shape structure

#### Structure

Compared to the previous shapes, the `Shape` structure is the one that is used to store the shapes for future use such as displaying.
```c
typedef struct {
    int id;
    SHAPE_TYPE shape_type;
    void *ptrShape;
} Shape;
```

The id is obtained through a function that increment the `global_id` (Positive and starts at 0) and returns it, meaning that the first id would be 1.
```c
unsigned int global_id = 0;

unsigned int get_next_id() {
    global_id++;
    return global_id;
}
```

The `shape_type` identifies what the `Shape` in the structure is and is the list of all the shapes that are defines.
```c
typedef enum { POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON} SHAPE_TYPE;
```

And finnaly, the `ptrShape` is a pointer that directs to the stored shape.  
   
#### Operations on a shape

Just as for individual shapes, there exist a `create_X_shape` that's in charge of creating a shape for a given type.  
It dynamically allocates memory for a `Shape`, then calls the function to create the shape of type X, who is then associated with the `ptrShape` of the shape.
```c
Shape *create_point_shape(int x, int y) {
    Shape *shp = create_empty_shape(POINT);
    Point *p = create_point(x,y);
    shp->ptrShape = p;
    return shp;   
}
```
To delete a shape, `delete_shape` that is the same for any type, using free() to free the memory allocated to the shape.
```c
void delete_shape(Shape *shp) {
    free(shp);
}
```
And finally, `print_shape` that is the same for any shape again.  
Using a switch case, it detects what is the type of the shape and which `print_x` to call then adds the ID of the shape to the displayed result.
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

### Storing shapes

Shapes are stored in `ShapeNodes` which are composed of a pointer to a `Shape` and their successor (NULL if no successor)
```c
typedef struct ShapeNode {
    struct ShapeNode* next;
    Shape* shp;
} ShapeNode;
```

Through four function, we can manage what is shapes are stored in the memory.  
`create_shape_node` creates an empty node with no shape and successor by dynamically allocating memory for a node.  
```c
ShapeNode *create_shape_node() {
    ShapeNode *node = malloc(sizeof(ShapeNode));
    if (node != NULL) {
        node->next = NULL;
        node->shp = NULL;
    }
    return node;
}
```
`delete_shape_node` delete a given node through the free function.  
```c
void delete_shape_node(ShapeNode *node) {
    free(node);
}
```
`add_shape_to_node` add a node with a shape to an already existing linked list.  
It calls the `create_shape_node` and fills the returned node, then adds it to the linked list by changing the successor of the last node to it's own address.  
```c
void add_shape_to_node(ShapeNode *node, Shape *shp) {
    ShapeNode *shpnode = create_shape_node();
    shpnode->shp = shp;

    if (node->shp == NULL) {
        node->shp = shp;
        return;
    }
    
    ShapeNode *curr = node;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = shpnode;
}
```
`print_shape_node` iterates through the nodes until the `NULL` node and calls the `print_shape` function for each node it goes through that's not `NULL` 
```c
void print_shape_node(ShapeNode *ShpNode) {
    ShapeNode *curr = ShpNode;
    while (curr != NULL) {
        print_shape(curr->shp);
        printf("\n");
        curr = curr->next;
    }
}
```

### Add up of everything

#### main

After each scanf the `clear_buffer` function is used in order to clear `stdin`, the input buffer. It works by using the `getchar` function until the character that was obtained is `EOF` (End Of File) or `\n`.  
```c
void clear_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
```

When starting the algorithm for the first time we create an initial `shape_list` on which we will add all the other shapes contained in `ShapeNodes`. 
```
ShapeNode *shape_list = create_shape_node();
```

The algorithm then loops until the `running` variable becomes 0 which is obtained through the option F.  
```c
while (running == 1) {

    .
    .
    .
    
}
```

During the loop, it will display the options and ask which one the users choose through a `scanf`, following that it acts accordingly by determinating what to do with a `switch case`.  
```c
choice = 'Z';
    printf("Please select an action:\n");
    printf("    A. Add a shape\n");
    printf("    B. Display the list of shapes\n");
    printf("    C. Delete a shape (WIP)\n");
    printf("    D. Draw the shapes (WIP)\n");
    printf("    E. Help (WIP)\n");
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

        default:
            break;
}
```

In the case that option B or E (Display the list of shapes / Help) we wait for the user input to move on with displaying the options.  
```c
if (choice == 'B' || choice == 'b' || choice == 'D' || choice == 'd') {
    printf("Press enter to continue...");
    scanf("%c", &c);
    clear_buffer();
}
```

#### Option A function

The first thing that is done is to ask the user what he shape he wants to add in the available shapes. If he gave a choice that is not among the possible choices, the program will redisplay and reask for his choice until it's correct, to do so we check if his choice is between 1 and 7.
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

Once the user choice is conirmed, we act accordingly by asking the necessary parameters for the `Shape`, filling the created empty shape with the given parameters and adding it at the end of the linked list of shapes `shape_list`.  
```c
switch (choice) {
    case 1:
        printf("         >> Enter the x and y coordinates: ");
        scanf("%i %i", &x, &y);
        clear_buffer();
        add_shape_to_node(shape_list, create_point_shape(x,y));
        break;
    
    .
    .
    .
    
    default:
        break;
}
```
