#include <stdlib.h>

#include "snake.h"

queue snake;
int snake_dir;

void init_snake(void)
{
    struct node *nodes[SNAKE_MIN_LENGTH];
    int i, x, y;

    x = 5;
    y = 5;

    for (i = 0; i < SNAKE_MIN_LENGTH; i++) {
        nodes[i] = (struct node *) malloc(sizeof(struct node));

        nodes[i]->x = x + i;
        nodes[i]->y = y;

        queue_push(&snake, nodes[i]);
    }

    snake_dir = RIGHT;
}

void empty_snake(void)
{
    struct node *p;

    do {
        free((p = queue_pop(&snake)));
    } while (p);
}

void update_snake(void)
{
    struct node *tail = queue_pop(&snake);
    struct node *head = snake.last;

    switch (snake_dir) {
        case UP:
            tail->x = head->x;
            tail->y = head->y - 1;
            tail->next = NULL;
            queue_push(&snake, tail);

            break;
        case DOWN:
            tail->x = head->x;
            tail->y = head->y + 1;
            tail->next = NULL;
            queue_push(&snake, tail);

            break;
        case LEFT:
            tail->x = head->x - 1;
            tail->y = head->y;
            tail->next = NULL;
            queue_push(&snake, tail);

            break;
        case RIGHT:
            tail->x = head->x + 1;
            tail->y = head->y;
            tail->next = NULL;
            queue_push(&snake, tail);

            break;
    }
}

void insert_snake_node(int x, int y)
{
    struct node *new = (struct node *) malloc(sizeof(struct node));
    new->x = x;
    new->y = y;

    switch (snake_dir) {
        case UP:
            new->y--;
            break;
        case DOWN:
            new->y++;
            break;
        case LEFT:
            new->x--;
            break;
        case RIGHT:
            new->x++;
            break;
    }

    new->next = NULL;

    queue_push(&snake, new);
}

int snake_has_eaten(int apple_x, int apple_y)
{
    int x, y;

    x = snake.last->x;
    y = snake.last->y;

    return x == apple_x && y == apple_y;
}

int check_snake_location(int arena_width, int arena_height)
{
    int x, y;

    x = snake.last->x;
    y = snake.last->y;

    return (x > arena_width || x < 1
        || y > arena_height || y < 1);
}

int check_snake_collision(void)
{
    struct node *p = snake.first;
    struct node *head = snake.last;
    int x, y;

    x = head->x;
    y = head->y;

    for (; p; p = p->next) {

        if (p == head) {
            continue;
        }

        int cx, cy;
        cx = p->x;
        cy = p->y;

        if (x == cx && y == cy) {
            return 1;
        }
    }

    return 0;
}
