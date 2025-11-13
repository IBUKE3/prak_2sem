#include <stdio.h>
#include <assert.h>

#include "mystring.h"

int main(void) {
	    int n;
	        assert(strtoint("1111", 2, & n) != -1 && n == 15);
		    assert(strtoint("", 2, &n) == -1 && n == 15);
		        assert(strtoint("21", 8, &n) != -1 && n == 17);
			    assert(strtoint("A", 16, &n) != -1&&n==10);
			    assert(strtoint("1111111111111111111111111111111", 2, &n) != -1 && n == 2147483647);
			    printf("%d", n);     
	    assert(strtoint("1234", 2, &n) == -1 && n == 2147483647);
		    assert(strtoint("0ff", 16, &n) != -1 && n==255);
			        assert(strtoint("ffFFffFFdd", 16, &n) == -1 && n == 255);
					    printf("PASS\n");
					        return 0;
}
            
