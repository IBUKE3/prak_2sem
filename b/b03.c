#include <stdio.h>
#include "stack.h"

int main(void){
	  printf("%d", st_isempty());
	    st_print();
	      st_push('x');
	        st_push('y');
		  st_push('z');
		    st_print();
		      char c = 'e';
		        char* pch = &c;
			  st_pop(pch);
			    putchar(*pch);
			      st_pop(pch);
			        putchar(*pch);
				  return 0;
}
