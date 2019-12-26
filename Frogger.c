#include "LPC17xx.H"
#include "GLCD.h"
#include "GLCD_UTILS.h"
#include "Math.h"
#include <stdlib.h>
//#define PINSEL_EINT0    20
//#define PINSEL_EINT1    22  
//#define SBIT_EINT0      0
//#define SBIT_EINT1      1  
//#define SBIT_EXTMODE0   0
//#define SBIT_EXTMODE1   1
//#define SBIT_EXTPOLAR0  0
//#define SBIT_EXTPOLAR1  1
//------------------------------------------------------------
int i;
int j;
int cxbody = 130;
int cybody = 230;
int wbody = 10;
int moveRow, moveCol;
int right = 0x20000000;
int left = 0x04000000;
int up = 0x08000000;
int down = 0x10000000;
int ix,iy;
int row,col;
int cx;
int cy;
char lives = '4';
int h1,h2,h3,h4,h5=0;
unsigned char youwin[] = "You Win!";
unsigned char youlose[] = "You Lose!";
int turtle = 0;
int logs = 0;

//------------------------------------------------------------
void drawFrog(int cxbody, int cybody, int wbody, unsigned short color){
	GLCD_SetTextColor(color);
	for(j = (cxbody-wbody/2); j <= (cxbody+wbody/2); j++){
		for(i = (cybody-wbody/2); i <= (cybody+wbody/2); i++){
			if (sqrt(pow((j-cxbody),2) + pow((i-cybody),2) <= (wbody/2))){                           
				GLCD_PutPixel(j,i);
			}
		}
	}
}
//------------------------------------------------------------
int dispArr[13][13] = {
0,7,0,0,7,0,7,0,0,7,0,7,0,
1,5,5,1,1,5,5,1,1,5,5,1,1,
1,1,1,4,4,4,1,1,1,4,4,4,1,
1,5,5,1,1,5,5,1,1,1,5,5,1,
1,4,4,4,1,1,4,4,4,1,1,1,1,
1,1,5,5,1,1,1,5,5,1,1,5,5,
6,6,6,6,6,6,6,6,6,6,6,6,6,
2,2,2,3,2,2,2,2,2,2,2,2,2,
8,8,2,2,2,2,2,2,2,2,2,2,2,
2,2,2,2,3,2,2,2,2,2,2,2,2,
2,2,2,2,2,2,2,8,8,2,2,2,2,
2,2,2,2,2,2,2,2,2,2,2,3,2,
6,6,6,6,6,6,6,6,6,6,6,6,6,};

//------------------------------------------------------------
// Draw Board Functions
//------------------------------------------------------------
void drawSafe(row,col){
	GLCD_SetTextColor(Olive);
	for(ix = col*20;ix < ((col*20)+20);ix++){
		for(iy = row*24; iy < ((row*24)+24); iy++){
			GLCD_PutPixel(ix,iy);
		}
	}
}
//------------------------------------------------------------
void drawHouse(row,col){
	GLCD_SetTextColor(LightGrey);
	for(ix = col*20;ix < ((col*20)+20);ix++){
		for(iy = row*24; iy < ((row*24)+24); iy++){
			GLCD_PutPixel(ix,iy);
		}
	}
}
//------------------------------------------------------------
void drawWater(row,col){
	GLCD_SetTextColor(Blue);
	for(ix = col*20;ix < ((col*20)+20);ix++){
		for(iy = (row*18)+6; iy < ((row*18)+24); iy++){
			GLCD_PutPixel(ix,iy);
		}
	}
}
//------------------------------------------------------------
void drawRoad(row,col){
 GLCD_SetTextColor(DarkGrey);
 for(ix = col*20;ix < ((col*20)+20);ix++){
  for(iy = (row*18)+6; iy < ((row*18)+24); iy++){
   GLCD_PutPixel(ix,iy);
  }
 }
}
//------------------------------------------------------------
void drawCar(row,col){
	GLCD_SetTextColor(DarkGrey);
	for(ix = col*20;ix < ((col*20)+20);ix++){
		for(iy = (row*18)+6; iy < ((row*18)+8); iy++){
			GLCD_PutPixel(ix,iy);
		}
		GLCD_SetTextColor(Red);
		for(iy = (row*18)+8; iy < (row*18)+22; iy++){
			GLCD_PutPixel(ix,iy);
		}
		GLCD_SetTextColor(DarkGrey);
		for(iy = (row*18)+22; iy < (row*18)+24; iy++){
			GLCD_PutPixel(ix,iy);
		}
	}
}
//------------------------------------------------------------
void drawLog(row,col){
	GLCD_SetTextColor(Blue);
	for(ix = col*20;ix < ((col*20)+20);ix++){
		for(iy = (row*18)+6; iy < ((row*18)+8); iy++){
			GLCD_PutPixel(ix,iy);
		}
		GLCD_SetTextColor(Maroon);
		for(iy = (row*18)+8; iy < (row*18)+22; iy++){
			GLCD_PutPixel(ix,iy);
		}
		GLCD_SetTextColor(Blue);
		for(iy = (row*18)+22; iy < (row*18)+24; iy++){
			GLCD_PutPixel(ix,iy);
		}
	}
}
//------------------------------------------------------------
void drawTurtle(row,col){
	GLCD_SetTextColor(Blue);
	for(ix = col*20;ix < ((col*20)+20);ix++){
		for(iy = (row*18)+6; iy < ((row*18)+8); iy++){
			GLCD_PutPixel(ix,iy);
		}
		GLCD_SetTextColor(Green);
		for(iy = (row*18)+8; iy < (row*18)+22; iy++){
			GLCD_PutPixel(ix,iy);
		}
		GLCD_SetTextColor(Blue);
		for(iy = (row*18)+22; iy < (row*18)+24; iy++){
			GLCD_PutPixel(ix,iy);
		}
	}
}
//------------------------------------------------------------
void drawRow(row,col){
	GLCD_SetTextColor(Olive);
	for(ix = col*20;ix < ((col*20)+20);ix++){
		for(iy = (row*18)+6; iy < ((row*18)+24); iy++){
			GLCD_PutPixel(ix,iy);
		}
	}
}
//------------------------------------------------------------
void drawTruck(row,col){
	GLCD_SetTextColor(DarkGrey);
	for(ix = col*20;ix < ((col*20)+20);ix++){
		for(iy = (row*18)+6; iy < ((row*18)+8); iy++){
			GLCD_PutPixel(ix,iy);
		}
		GLCD_SetTextColor(DarkGreen);
		for(iy = (row*18)+8; iy < (row*18)+22; iy++){
			GLCD_PutPixel(ix,iy);
		}
		GLCD_SetTextColor(DarkGrey);
		for(iy = (row*18)+22; iy < (row*18)+24; iy++){
			GLCD_PutPixel(ix,iy);
		}
	}
}
//------------------------------------------------------------
void houses(){
			//0,7,0,0,7,0,7,0,0,7,0,7,0,
	if((20<=cxbody) &&(20+20>=cxbody)){
		h1 = 1;
		cxbody = 130;
		cybody = 230;
	}
	if((80<=cxbody) &&(80+20>=cxbody)){
		h2 = 1;
		cxbody = 130;
		cybody = 230;
	}
	if((120<=cxbody) &&(120+20>=cxbody)){
		h3 = 1;
		cxbody = 130;
		cybody = 230;
	}
	if((180<=cxbody) &&(180+20>=cxbody)){
		h4 = 1;
		cxbody = 130;
		cybody = 230;
	}
	if((220<=cxbody) &&(220+20>=cxbody)){
		h5 = 1;
		cxbody = 130;
		cybody = 230;
	}
}
//------------------------------------------------------------
void drawBackground(){
	for(row = 0; row < 13; row++){
		for(col = 0; col < 13; col++){
				cx = col*20;
				cy = row*18;
			if(dispArr[row][col]== 0){
				drawSafe(row,col);
			}
			if(dispArr[row][col]== 1){
				drawWater(row,col);
				if((cx<=cxbody) &&(cx+20>=cxbody) && (cy<=cybody) && (cy+18>=cybody)){
					cxbody = 130;
					cybody = 230;
					lives = lives - 1;
				}
			}
			if(dispArr[row][col]== 2){
				drawRoad(row,col);
			}
			if(dispArr[row][col]== 3){
				drawCar(row,col);
				if((cx<=cxbody) &&(cx+18>=cxbody) && (cy<=cybody) && (cy+20>=cybody)){
					cxbody = 130;
					cybody = 230;
					lives = lives -1;
				}
			}
			if(dispArr[row][col]== 4){
				drawLog(row,col);
				if((cx<=cxbody) &&(cx+20>=cxbody) && (cy<=cybody) && (cy+18>=cybody)){
					if(cxbody<=220){
						logs = 1;			
					}
				}
			}
			if(dispArr[row][col]== 5){
				drawTurtle(row,col);
				cx = col*20;
				cy = row*18;
				if((cx<=cxbody) &&(cx+20>=cxbody) && (cy<=cybody) && (cy+18>=cybody)){
					if(cxbody>=20){
						turtle = 1;
					}
				}
			}
			if(dispArr[row][col]== 6){
				drawRow(row,col);
			}
			if(dispArr[row][col]== 7){
				drawHouse(row,col);
				cx = col*20;
				cy = row*24;
				if((cx<=cxbody) &&(cx+20>=cxbody) && (cy<=cybody) && (cy+24>=cybody)){
					houses();
				}
					//0,7,0,0,7,0,7,0,0,7,0,7,0,
			}
			if(dispArr[row][col]== 8){
				drawTruck(row,col);
				cx = col*20;
				cy = row*18;
				if((cx<=cxbody) &&(cx+18>=cxbody) && (cy<=cybody) && (cy+20>=cybody)){
					cxbody = 130;
					cybody = 230;
					lives = lives - 1;
				}
			}
		}
	}
}

//------------------------------------------------------------
//void EINT0_IRQHandler(void)
//{

//    LPC_SC->EXTINT = (1<<SBIT_EINT0);  /* Clear Interrupt Flag */

//    LPC_GPIO2->FIOPIN ^= (1<< LED1);   /* Toggle the LED1 everytime INTR0 is generated */

//}
void moveFrog(){
	if ((LPC_GPIO1->FIOPIN & right) == 0){
		if(cxbody<=240){
			cxbody = cxbody + 20;
		}
	}
	if ((LPC_GPIO1->FIOPIN & left) == 0){
		if(cxbody>=20){
			cxbody = cxbody - 20;
		}
	}
	if ((LPC_GPIO1->FIOPIN & up) == 0){
		if(cybody>=18){
			if(dispArr[row-1][col] == 0){
			cybody = cybody;
			}
			else{
			cybody = cybody - 18;
			}
		}
	}
	if ((LPC_GPIO1->FIOPIN & down) == 0){
		if(cybody<=221){
			cybody = cybody + 18;
		}
	}
}
//------------------------------------------------------------
void moveOddRows(){
	for(moveRow = 1; moveRow < 12; moveRow = moveRow + 2){
		for(moveCol = 0; moveCol <13; moveCol++){
			dispArr[moveRow][moveCol] = dispArr[moveRow][moveCol+1];
			if ((moveCol+1) == 13){
				dispArr[moveRow][moveCol] = dispArr[moveRow][moveCol-12];
			}
		} 
	}
}
//------------------------------------------------------------
void moveEvenRows(){
	for(moveRow = 2; moveRow < 12; moveRow = moveRow +2){
		for(moveCol = 12; moveCol >-1; moveCol--){
			dispArr[moveRow][moveCol] = dispArr[moveRow][moveCol-1];
			if((moveCol-1) == -1){
				dispArr[moveRow][moveCol] = dispArr[moveRow][moveCol+12];
			}
		} 
	}
}
//------------------------------------------------------------
int main(){
	LPC_GPIO1->FIODIR = 0x000000FF;
	GLCD_Init();
	GLCD_Clear(Black);
	GLCD_SetTextColor(Green);
	while(1){
		drawBackground();
		drawFrog(cxbody,cybody,wbody,Magenta);
		moveOddRows();
		moveFrog();
		moveEvenRows();
		GLCD_DisplayChar(1,18,lives);
		if(lives == '0'){
			GLCD_DisplayString(6,0,youlose);
			return(0);
		}
		if(h1 == 1){
			drawFrog(30,12,10,Magenta);
		}
		if(h2 == 1){
			drawFrog(90,12,10,Magenta);
		}
		if(h3 == 1){
			drawFrog(130,12,10,Magenta);
		}
		if(h4 == 1){
			drawFrog(190,12,10,Magenta);
		}
		if(h5 == 1){
			drawFrog(230,12,10,Magenta);
		}
		if((h1 && h2 && h3 && h4 && h5) == 1){
			GLCD_DisplayString(6,0,youwin);
			return(0);
		}
		if(turtle == 1){
			cxbody = cxbody-20;
		}
		if(logs == 1){
			cxbody = cxbody+20;
		}
		turtle = 0;
		logs = 0;  
	}
}
