#include <stdio.h>
#include <assert.h>

#include "mystring.h"

int main(void) {
	    char str1[] = "apple", str2[] = "banana";
	        assert(strcmp(str1, str2) < 0);
		    assert(strcmp("A", "A") == 0);
		        assert(strcmp("12345", "123") > 0);

			    printf("PASS\n");
			        return 0;
}
