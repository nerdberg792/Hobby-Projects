#include<ncurses.h>
#include<stdlib.h>
#include<unistd.h>

#define WIDTH 100 
#define HEIGHT 100 
#define DELAY 200000

int grid[HEIGHT][WIDTH] ; 
int temp[HEIGHT][WIDTH] ; 

void initialize_ncurses(){
	initscr() ; 
	noecho() ;
	curs_set(FALSE) ; 
	keypad(stdscr , TRUE) ; 
	timeout(0) ; 
}
void display_grid() {
	clear() ; 
	for(int y = 0 ; y < HEIGHT ; y++){
		for(int x = 0 ; x < WIDTH ; x++){
			if(grid[y][x]){
				mvprintw(y , x , "O" ) ; 
			}else{
				mvprintw(y , x , "." ) ; 
			}
		}
	}
	mvprintw(HEIGHT , 0 , "Press 'q' to quit , 'p' to pause , 'r' to randomize.") ; 
	refresh() ; 
}
int count_neighbors(int y , int x){
	int count = 0 ; 
	for(int dy = -1 ; dy <= 1 ; dy++){
		for(int dx = -1 ; dx <=1 ; dx++){
			if(dy==0&&dx==0)continue ; 
			int ny = (y+dy+HEIGHT)%HEIGHT ; 
			int nx = (x+dx+WIDTH)%WIDTH ; 
			count+= grid[ny][nx] ; 
		}
	 
	}
	return count ; 
}
void update_grid(){
	for(int y = 0 ; y < HEIGHT ; y++){
		for(int x = 0 ; x<WIDTH ; x++){
			int neighbors = count_neighbors( y , x ) ; 
			if(grid[y][x]&&(neighbors<2 || neighbors>3)){
				temp[y][x] = 0 ; 
			}
			else if(!grid[y][x]&&neighbors == 3 ){
				temp[y][x] = 1 ; 
			}
			else {
				temp[y][x] = grid[y][x] ; 
			}
		}
	}
	for(int y = 0 ; y <HEIGHT ; y++){
		for(int x = 0 ; x < WIDTH ; x++){
			grid[y][x] = temp[y][x] ; 
		}
	}
}
void randomize_grid(){
	for(int y = 0 ; y < HEIGHT ; y++){
		for(int x = 0 ; x<WIDTH ; x++){
			grid[y][x] = rand()%2 ; 
		}
	}
}
int main(){
	initialize_ncurses() ; 
	int running = 1; 
	randomize_grid() ; 
	while(1){
		display_grid() ; 
		if(running){
			update_grid() ; 
		}
		int ch = getch() ; 
		switch(ch){
			case 'q' :
				endwin() ; 
				return 0 ; 
			case 'p' : 
				running = !running ; 
				break ; 
			case 'r' : 
				randomize_grid() ; 
				break ; 
		}
		usleep(DELAY) ; 
	}
	endwin() ; 
	return 0 ; 
}



