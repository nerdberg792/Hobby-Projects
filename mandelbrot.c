#include<SDL2/SDL.h> 
#include<stdio.h> 
#include<complex.h>

#define WIDTH 800 
#define HEIGHT 600 
#define MAX_ITR 1000 


int mandelbrot(double real , double image){
	double complex z = 0 + 0*I ; 
	double complex c = real + image*I ; 
	int itr ; 
	for(itr = 0 ; itr < MAX_ITR ; itr++){
		if(cabs(z) > 2){
			return itr ; 
		}
		z = z*z + c ; 
	} 
	return MAX_ITR ; 
}

int main(){
	SDL_Init(SDL_INIT_VIDEO) ; 
	SDL_Window* window = SDL_CreateWindow("Mandelbrot Set" , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED, WIDTH , HEIGHT , SDL_WINDOW_SHOWN) ; 
	SDL_Renderer* renderer = SDL_CreateRenderer(window , -1  , SDL_RENDERER_ACCELERATED) ; 
	double minReal = -2.0 , maxReal = 1.0 ; 
	double minImag = -1.5 , maxImag = 1.5 ; 
	for(int x = 0 ; x < WIDTH ; x++){
		for(int y = 0 ; y < HEIGHT ; y++){
			double real = minReal + (maxReal - minReal)*x/WIDTH ; 
			double imag = minImag + (maxImag - minImag)*y/HEIGHT ; 
			int itr = mandelbrot(real , imag) ; 
			int color = (itr == MAX_ITR)?0 : (itr*255/MAX_ITR) ; 
			SDL_SetRenderDrawColor(renderer , color , color+100%MAX_ITR , color , 255) ; 
			SDL_RenderDrawPoint(renderer , x , y ) ; 
		}
	}
 	SDL_RenderPresent(renderer) ; 
	SDL_Delay(5000) ;  
	SDL_DestroyRenderer(renderer) ; 
	SDL_DestroyWindow(window) ; 
	SDL_Quit() ; 
}
