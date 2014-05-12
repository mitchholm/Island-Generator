#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bmpfile.c"
#include "nargs.c"

#define VARIATION 16

int starting = 8;
int totalIters = 5;

void makeBitmap(int size, char** map, char* name){
	bmpfile_t* b = bmp_create((uint32_t)size, (uint32_t)size, (uint32_t)32);
	rgb_pixel_t pGreen = {(uint8_t)0,(uint8_t)180,(uint8_t)0,(uint8_t)255};
	rgb_pixel_t pGrey = {(uint8_t)200,(uint8_t)200,(uint8_t)200,(uint8_t)255};
	rgb_pixel_t pDGreen = {(uint8_t)0,(uint8_t)100,(uint8_t)0,(uint8_t)255};
	rgb_pixel_t pYellow = {(uint8_t)0,(uint8_t)180,(uint8_t)180,(uint8_t)255};
	rgb_pixel_t pBlue = {(uint8_t)180,(uint8_t)0,(uint8_t)0,(uint8_t)255};
	rgb_pixel_t pLBlue = {(uint8_t)250,(uint8_t)0,(uint8_t)0,(uint8_t)255};
	rgb_pixel_t pDGrey = {(uint8_t)100,(uint8_t)100,(uint8_t)100,(uint8_t)255};
	for(int x = 0; x < size; ++x)
		for(int y = 0;y < size; ++y)
			switch(map[x][y]){
				case 4:bmp_set_pixel(b,x,y,pLBlue);
					break;
				case 5:bmp_set_pixel(b,x,y,pYellow);
					break;
				case 6:bmp_set_pixel(b,x,y,pGreen);
					break;
				case 7:bmp_set_pixel(b,x,y,pGreen);
					break;
				case 8:bmp_set_pixel(b,x,y,pGreen);
					break;
				case 9:bmp_set_pixel(b,x,y,pGreen);
					break;
				case 10:bmp_set_pixel(b,x,y,pDGreen);
					break;
				case 11:bmp_set_pixel(b,x,y,pDGreen);
					break;
				case 12:bmp_set_pixel(b,x,y,pDGreen);
					break;
				case 13:bmp_set_pixel(b,x,y,pDGreen);
					break;
				case 14:bmp_set_pixel(b,x,y,pDGreen);
					break;
				case 15:bmp_set_pixel(b,x,y,pGrey);
					break;
				case 16:bmp_set_pixel(b,x,y,pDGrey); break;
				default:
					bmp_set_pixel(b,x,y,pBlue);
					break;
			}
	bmp_save(b,name);
}

char** expand(int* sizep, char** oldMap){
	int size = *sizep * 2 - 1;
	*sizep = *sizep * 2 -1;
	char** map = (char**)calloc(size, sizeof(char*));
	for(int i=0; i < size; i++)
		map[i] = (char*)calloc(size, sizeof(char));
	for(int x = 0; x < size - 1; ++x)
		for(int y = 0; y < size -1; ++y){
			map[x][y] = oldMap[(x + 1)/2][(y+1)/2];
		}
	for(int x = 1; x < size - 1; x+=2)
		for(int y = 0; y < size -1; y+=2){
			map[x][y] = (map[x-1][y] + map[x+1][y] + ((rand()%3))) / 2;
		}
	for(int x = 0; x < size - 1; x+=2)
		for(int y = 1; y < size -1; y+=2){
			map[x][y] = (map[x][y-1] + map[x][y+1] + ((rand()%3))) / 2;
		}
	for(int x = 1; x < size - 1; x+=2)
		for(int y = 1; y < size -1; y+=2){
			map[x][y] = (map[x][y-1] + map[x][y+1] + map[x-1][y] + map[x+1][y] + ((rand()%3))) / 4;
		}
	free(oldMap);
	return map;
}

void printHex(int size, char** map){
	for(int x = 0; x < size; ++x){
		for(int y = 0; y < size; ++y)
			printf("%x ", map[x][y]);
		printf("\n");
	}
}
// void printB(int size, char** map){
// 	for(int x = 0; x < size; ++x){
// 		for(int y = 0; y < size; ++y)
// 			if(map[x][y] >= THRESHOLD2) 
// 				printf("# ");
// 			else if(map[x][y] >= THRESHOLD1) 
// 				printf("? ");
// 			else
// 				printf(" ");
// 		printf("\n");
// 	}
// }

int main(int n, char** args){
	srand(time(NULL));
	//Midpoint displacement theorem
	if(isPresent(n,args,"size"))
		starting = argInt(n,args,"size");
	if(isPresent(n,args,"i")){
		int temp = argInt(n,args,"i");
		if(temp < 9)
			totalIters = temp;
		else
			printf("Max iterations: 8, defaulting to 5\n");
	}
	int size = starting;
	char** map = (char**)calloc(size, sizeof(char*));
	for(int i=0; i < size; i++)
		map[i] = (char*)calloc(size, sizeof(char));
	//This loop seeds the random spots
	for(int x = 0; x < size -1; ++x)
		for(int y = 0; y < size -1; ++y)
			if(x != 0 && y != 0)
				map[x][y] = rand() % VARIATION;
	for(int i = 0; i < totalIters; ++i)
		map = expand(&size, map);
	//printB(size, map);
	char* name ="island.bmp";
	if(isPresent(n,args,"name"))
		name = argString(n,args,"name");
	makeBitmap(size, map, name);
}