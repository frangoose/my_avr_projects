//Version 1.0
//10/30/19

#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdlib.h>
#include "Nokia_5110.h"
#include "Timer.h"

typedef struct Node
{
	uint8_t x_position;
	uint8_t y_position;
	struct Node* next;
} Node;

typedef enum
{
	LEFT = 0,
	UP = 1,
	RIGHT = 2,
	DOWN = 3
}Direction;

extern Node* head;
void Snake_Init(Direction direction, uint8_t start_length);
void Snake_AddSegment(Node** head_ptr, uint8_t x_pos, uint8_t y_pos);
void Snake_DelSegment(Node* head_node);
void Snake_Grow(Direction direction);
void Snake_Move(Direction direction);
uint8_t Snake_Contact();
Direction Snake_ChangeDir(Direction* direction);
void Snake_Apple(uint8_t x_pos, uint8_t y_pos);
uint8_t Snake_Eat_Apple();
void Snake_End();

#endif /* SNAKE_H_ */