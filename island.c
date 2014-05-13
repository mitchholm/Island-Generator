#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bmpfile.c"
#include "nargs.c"

#define VARIATION 256

int starting = 8;
int totalIters = 5;

rgb_pixel_t makePixel(int r, int g, int b){
	return (rgb_pixel_t){(uint8_t)r,(uint8_t)g,(uint8_t)b,(uint8_t)255};
}

void makeBitmap(int size, unsigned short** map, char* name){
	bmpfile_t* b = bmp_create((uint32_t)size, (uint32_t)size, (uint32_t)32);;
	for(int x = 0; x < size; ++x){
		for(int y = 0;y < size; ++y){
			//printf("%3.i ", map[x][y]);
			if(map[x][y] > 100 && map[x][y] <= 120)
				bmp_set_pixel(b,x,y,makePixel(150,map[x][y] + 120,map[x][y] + 120));
			else if(map[x][y] > 120 && map[x][y] <=255)
				bmp_set_pixel(b,x,y,makePixel(40,300 - map[x][y],40));
			else if(map[x][y] >= 256)
				bmp_set_pixel(b,x,y,makePixel(40,55,40));
			else if(map[x][y] <= 100)
				bmp_set_pixel(b,x,y,makePixel(map[x][y] + 100,90,0));
			else
				bmp_set_pixel(b,x,y,makePixel(map[x][y] + VARIATION/2, map[x][y] + VARIATION/2, map[x][y] + VARIATION/2));
			//printf("(%i,%i) value: %i",x,y, map[x][y]);
		}
		//printf("\n");
	}
	bmp_save(b,name);
}

void makeCart(int size, unsigned short** map, char* name){
	bmpfile_t* b = bmp_create((uint32_t)size, (uint32_t)size, (uint32_t)32);;
	for(int x = 0; x < size; ++x){
		for(int y = 0;y < size; ++y){
			if(map[x][y] > 100 && map[x][y] <= 106)
				bmp_set_pixel(b,x,y,makePixel(50,50,50));
			else if(map[x][y] > 166 && map[x][y] <= 169)
				bmp_set_pixel(b,x,y,makePixel(180,210,180));
			else if(map[x][y] > 199 && map[x][y] <= 203)
				bmp_set_pixel(b,x,y,makePixel(180,210,180));
			else if(map[x][y] > 103 && map[x][y] <= 255)
				bmp_set_pixel(b,x,y,makePixel(210,255,210));
			else if(map[x][y] <= 100)
				bmp_set_pixel(b,x,y,makePixel(255,255,150));
			else
				bmp_set_pixel(b,x,y,makePixel(map[x][y] + VARIATION/2, map[x][y] + VARIATION/2, map[x][y] + VARIATION/2));
		}
	}
	bmp_save(b,name);
}

unsigned short** expand(int* sizep, unsigned short** oldMap){
	int size = *sizep * 2 - 1;
	*sizep = *sizep * 2 -1;
	unsigned short** map = (unsigned short**)calloc(size, sizeof(short*));
	for(int i=0; i < size; i++)
		map[i] = (unsigned short*)calloc(size, sizeof(short));
	for(int x = 0; x < size; ++x)
		for(int y = 0; y < size; ++y){
			map[x][y] = oldMap[(x + 1)/2][(y+1)/2];
		}
	for(int x = 1; x < size - 1; x+=2)
		for(int y = 0; y < size -1; y+=2){
			map[x][y] = (map[x-1][y] + map[x+1][y] + rand() % 24 - rand() % 16) / 2;
		}
	for(int x = 0; x < size - 1; x+=2)
		for(int y = 1; y < size -1; y+=2){
			map[x][y] = (map[x][y-1] + map[x][y+1] + rand() % 24 - rand() % 16) / 2;
		}
	for(int x = 1; x < size - 1; x+=2)
		for(int y = 1; y < size -1; y+=2){
			map[x][y] = (map[x][y-1] + map[x][y+1] + map[x-1][y] + map[x+1][y] + rand() % 24 - rand() % 16) / 4;
		}
	free(oldMap);
	return map;
}

// void printHex(int size, short** map){
// 	for(int x = 0; x < size; ++x){
// 		for(int y = 0; y < size; ++y)
// 			printf("%x ", map[x][y]);
// 		printf("\n");
// 	}
// }
// void printB(int size, short** map){
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
	int edges = 0;
	if(isPresent(n,args,"size"))
		starting = argInt(n,args,"size");
	if(isPresent(n,args,"i")){
		int temp = argInt(n,args,"i");
		if(temp < 9)
			totalIters = temp;
		else
			printf("Max iterations: 8, defaulting to 5\n");
	}
	if(isPresent(n,args,"edges")){
		edges = 1;
	}
	int size = starting;
	unsigned short** map = (unsigned short**)calloc(size, sizeof(unsigned short*));
	for(int i=0; i < size; i++)
		map[i] = (unsigned short*)calloc(size, sizeof(unsigned short));
	//This loop seeds the random spots
	if(edges){
		for(int x = 0; x < size; ++x)
			for(int y = 0; y < size; ++y)
				map[x][y] = rand() % VARIATION;
	}
	else{
		for(int x = 0; x < size; ++x)
			for(int y = 0; y < size; ++y)
				if(x > 0 && y > 0 && x != size -1 && y != size -1)
					map[x][y] = 24 + rand() % (VARIATION - 36);
				else
					map[x][y] = 24;
	}
	for(int i = 0; i < totalIters; ++i)
		map = expand(&size, map);
	//printB(size, map);
	char* name ="island.bmp";
	if(isPresent(n,args,"name"))
		name = argString(n,args,"name");
	if(!isPresent(n,args,"cart"))
		makeBitmap(size, map, name);
	else
		makeCart(size, map, name);
}