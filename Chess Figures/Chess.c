#define _CRT_SECURE_NO_WARNINGS
#include "CChess.h"
#include "new.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>

void* fabrika(char string[])
{
	int x = 0, y = 0, dummy;
	char str[100] = { 0 };
	int count = sscanf(string, "%s %d %d %d", str, &x, &y, &dummy);
	if (count != 3)
	{
		return NULL;
	}
	if (!strcmp(str, "king"))
	{
		return new(King, x, y);
	}
	else if (!strcmp(str, "bishop"))
	{
		return new(Bishop, x, y);
	}
	else if (!strcmp(str, "knight"))
	{
		return new(Knight, x, y);
	}
	else if (!strcmp(str, "queen"))
	{
		return new(Queen, x, y);
	}
	else if (!strcmp(str, "rook"))
	{
		return new(Rook, x, y);
	}
	return NULL;
}

extern bool checkfig(desk* desk, int x, int y)
{
	if ((0 <= x && x < 8) && (0 <= y && y < 8))
	{
		if (desk->fields[x][y])
		{
			draw(desk->fields[x][y]);
			printf(" %d %d\n", x, y);
			return 0;
		}
	}
	return 1;
}

void CreateDesk(desk* p)
{
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++)
		{
			p->fields[i][j] = NULL;
		}
	}
	return;
}

void VisualDesk(desk* desk) 
{
	for (int i = 0; i < 8; i++)
	{
		printf("\n");
		for (int j = 0; j < 8; j++)
		{
			printf(" ");
			if (desk->fields[i][j])
			{
				draw(desk->fields[i][j]);
			}
			else
			{
				printf("#");
			}
		}
	}
	printf("\n");
}

void checkDesk(desk* desk)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (desk->fields[i][j])
			{
				check(desk->fields[i][j], desk);
			}
		}
	}
}

void KillDesk(desk* desk)
{
	if (!desk) 
	{
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete(desk->fields[i][j]);
		}
	}
}

int main() 
{
	desk desk;
	CreateDesk(&desk);
	FILE* fp;
	fp = fopen("figure.txt", "r+");
	if (!fp)
	{
		printf("File is not found");
		KillDesk(&desk);
		exit(0);
	}
	char string[100]={0};
	assert(fp);
	void* fig;
	while (fgets(string, 100, fp))
	{
		fig = fabrika(string);
		if (!fig) {
			printf("Ivalid string\n");
			printf(string);
		}
		AddAtDesk(fig, &desk);
	}

	VisualDesk(&desk);

	checkDesk(&desk);

	KillDesk(&desk);
}