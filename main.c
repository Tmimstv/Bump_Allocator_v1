#include "arena.h"
#include "alloc_lite.h"
#include <stdio.h>
#include <assert.h>


int main(){
	//setup
	Arena myArena;
	if(!arena_init(&myArena, 1)){
		printf("seg error but i cant read this line anyway if that happens\n");
	}
	printf("creation successful\n");
	al_init(&myArena);


	//test/prove  alignment
	printf("--Testing Alignment--");

	for (int i = 0; i < 10; i++){
		void* p = al_alloc(i+1);

		//print pointer + should multiple of 16 by using %
		printf("i is %d, if the next number is \"0\" then the pointer is aligned correctly:  %zu\n", i, ((uintptr_t)p%16));
	}

	//tests running out, im thinking while loop

	int allocations = 0;
	while(true) {
		void* p = al_alloc(512);
		if( p==NULL){
			printf("ran out of memory after %d allocations.\n", allocations);
			break;
		}
		allocations++;
	}


	//cleanup
	arena_destroy(&myArena);
	return 0;
}

