#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 80
#define HEIGHT 24

#define EMPTY '_'
#define PIXEL '*'

char picture[HEIGHT][WIDTH];

void clearPicture() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            picture[y][x] = EMPTY;
        }
    }
}

void displayPicture() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", picture[y][x]);
        }
        printf("\n");
    }
}

void setPixel(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        picture[y][x] = PIXEL;
    }
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
    if (steps == 0) {
        setPixel(x1, y1);
        return;
    }

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        setPixel((int)(x + 0.5f), (int)(y + 0.5f));
        x += xInc;
        y += yInc;
    }
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y1); // Top
    drawLine(x1, y2, x2, y2); // Bottom
    drawLine(x1, y1, x1, y2); // Left
    drawLine(x2, y1, x2, y2); // Right
}

void drawCircle(int cx, int cy, int radius) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int dx = x - cx;
            int dy = y - cy;
            float distance = (float)(dx * dx + dy * dy);
            if (distance >= (radius - 0.75f) * (radius - 0.75f) && 
                distance <= (radius + 0.75f) * (radius + 0.75f)) {
                setPixel(x, y);
            }
        }
    }
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

// Helper function to safely clear the input buffer and prevent terminal freezing
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int choice;

    clearPicture();

    printf("2D Graphics Editor\n");
    printf("Canvas size: %d x %d\n", WIDTH, HEIGHT);
    printf("Use coordinates x y.\n");
    printf("x range: 0 to %d\n", WIDTH - 1);
    printf("y range: 0 to %d\n", HEIGHT - 1);

    while (1) {
        printf("\nMenu\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Circle\n");
        printf("4. Draw Triangle\n");
        printf("5. Display Picture\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        if (choice == 1) {
            int x1, y1, x2, y2;
            printf("Enter x1 y1 x2 y2 (separated by spaces): ");
            if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4) {
                printf("Error: You must enter exactly 4 numbers.\n");
                clearInputBuffer();
                continue;
            }
            drawLine(x1, y1, x2, y2);
            printf("Line drawn successfully!\n");
        }
        else if (choice == 2) {
            int x1, y1, x2, y2;
            printf("Enter top-left x y and bottom-right x y: ");
            if (scanf("%d %d %d %d", &x1, &y1, &x2, &y2) != 4) {
                printf("Error: You must enter exactly 4 numbers.\n");
                clearInputBuffer();
                continue;
            }
            drawRectangle(x1, y1, x2, y2);
            printf("Rectangle drawn successfully!\n");
        }
        else if (choice == 3) {
            int cx, cy, radius;
            printf("Enter center x y and radius: ");
            if (scanf("%d %d %d", &cx, &cy, &radius) != 3) {
                printf("Error: You must enter exactly 3 numbers.\n");
                clearInputBuffer();
                continue;
            }
            drawCircle(cx, cy, radius);
            printf("Circle drawn successfully!\n");
        }
        else if (choice == 4) {
            int x1, y1, x2, y2, x3, y3;
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            if (scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3) != 6) {
                printf("Error: You must enter exactly 6 numbers.\n");
                clearInputBuffer();
                continue;
            }
            drawTriangle(x1, y1, x2, y2, x3, y3);
            printf("Triangle drawn successfully!\n");
        }
        else if (choice == 5) {
            printf("The picture is:\n");
            displayPicture();
        }
        else if (choice == 0) {
            printf("Exiting program.\n");
            break;
        }
        else {
            printf("Invalid option. Choose a number between 0 and 5.\n");
        }
    }

    return 0;
}