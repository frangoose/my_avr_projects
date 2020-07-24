//Version 1.0
//10/30/19

#include "Snake.h"

Node* head = NULL;
Node* apple = NULL;

void Snake_Init(Direction direction, uint8_t start_length)
{
	NOKIA_Fill_Display(CLR_PIXEL);
	NOKIA_Draw_Rect(0,0,LCD_WIDTH-1,LCD_HEIGHT-1,SET_PIXEL); //draw walls
	
	head = (Node*) malloc(sizeof(Node));
	head->x_position = LCD_WIDTH/2;
	head->y_position = LCD_HEIGHT/2;
	head->next = NULL;
	
	for(uint8_t i = 0; i < start_length; i++)
	{
		Snake_Grow(direction);
	}
	Snake_Apple(3*(LCD_WIDTH/4), LCD_HEIGHT/2);
}

void Snake_AddSegment(Node** head_ptr, uint8_t x_pos, uint8_t y_pos)
{
	Node* new_node = (Node*) malloc(sizeof(Node));
	new_node->x_position = x_pos;
	new_node->y_position = y_pos;
	new_node->next = *head_ptr;
	*head_ptr = new_node;
	NOKIA_Set_Pixel(new_node->x_position,new_node->y_position,SET_PIXEL);
}

void Snake_DelSegment(Node* head_node)
{
	Node* temp_node = head_node;
	while(temp_node->next->next != NULL)
	{
		temp_node = temp_node->next;
	}
	NOKIA_Set_Pixel(temp_node->x_position,temp_node->y_position,CLR_PIXEL);
	free(temp_node->next);
	temp_node->next = NULL;
}

void Snake_Grow(Direction direction)
{
	switch(direction)
	{
		case LEFT: Snake_AddSegment(&head, head->x_position - 1, head->y_position); break;
		case UP: Snake_AddSegment(&head, head->x_position, head->y_position - 1); break;
		case RIGHT: Snake_AddSegment(&head, head->x_position + 1, head->y_position); break;
		case DOWN: Snake_AddSegment(&head, head->x_position, head->y_position + 1); break;
		default: break;
	}
}

void Snake_Move(Direction direction)
{
	Snake_DelSegment(head);
	switch(direction)
	{
		case LEFT: Snake_AddSegment(&head, head->x_position - 1, head->y_position); break;
		case UP: Snake_AddSegment(&head, head->x_position, head->y_position - 1); break;
		case RIGHT: Snake_AddSegment(&head, head->x_position + 1, head->y_position); break;
		case DOWN: Snake_AddSegment(&head, head->x_position, head->y_position + 1); break;
		default: break;
	}
}

uint8_t Snake_Contact()
{
	uint8_t ret_val = 0;
	Node* current_node = head->next;
	if(head->x_position < 1 || head->x_position > LCD_WIDTH - 2)
	{
		ret_val = 1;
	}
	if(head->y_position < 1 || head->y_position > LCD_HEIGHT - 2)
	{
		ret_val = 1;
	}
	while(current_node->next != NULL)
	{
		if(head->x_position == current_node->x_position)
		{
			if(head->y_position == current_node->y_position)
			{
				ret_val = 1;
			}
		}
		current_node = current_node->next;
	}
	return ret_val;
}

Direction Snake_ChangeDir(Direction* direction)
{
	*direction += 1;
	*direction %= 4;
	return *direction;
}

void Snake_Apple(uint8_t x_pos, uint8_t y_pos)
{
	apple->next = NULL;
	apple->x_position = x_pos;
	apple->y_position = y_pos;
	NOKIA_Set_Pixel(apple->x_position,apple->y_position,SET_PIXEL);
}

uint8_t Snake_Eat_Apple() // Work In Progress, does not return true
{
	uint8_t ret_val = 0;
	if(head->x_position == apple->x_position)
	{
		if(head->y_position == apple->y_position)
		{
			Snake_Apple(apple->x_position + 1, apple->y_position + 2);
			ret_val = 1;
		}
	}
	return ret_val;
}

void Snake_End()
{
	while(head->next != NULL)
	{
		Snake_DelSegment(head);
	}
	free(head);
	free(apple);
}