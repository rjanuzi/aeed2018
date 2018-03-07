/*
 * @author Rafael B. Januzi
 * @date 06/03/2018
 */

#include <stdio.h>
#include <stdlib.h>

/* Functions Prototypes */
int binary_search_iterative(int* array, int len, int x);
int binary_search_recursive(int* array, int l_index, int r_index, int x);

int main( void )
{

	printf("Hello World!\n");
	
	return 0;
}

/*
 * Executes the binary search iterative algorithm.
 * 
 * @param int* array: Sorted array to execute the search.
 * @param int len: The array's length.
 * @param int x: The element to look for.
 *
 * @return The position of the element x in the array if exists.
 * -1 if do not exists.
 */
int binary_search_iterative(int* array, int len, int x)
{
	//TODO
	return -1;
}

/*
 * Executes the binary search recursive algorithm.
 * 
 * @param int* array: Sorted array to execute the search.
 * @param int l_index: The most left index to consider.
 * @param int r_index: The most right index to consider.
 * @param int x: The element to look for.
 *
 * @return The position of the element x in the array if exists.
 * -1 if do not exists.
 */
int binary_search_recursive(int* array, int l_index, int r_index, int x)
{
	//TODO
	return -1;
}
