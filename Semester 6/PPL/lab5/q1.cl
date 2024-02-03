__kernel void dec_to_oct(__global int *decimal, __global int *octal)
{
	// Get the index of the current work item
	int i = get_global_id(0);
	int dec = decimal[i];
	int oct = 0;
	int j = 1;
 
    while (dec != 0) {
        oct += (dec % 8) * j;
        dec /= 8;
        j *= 10;
    }
 
    octal[i] = oct;
 
}