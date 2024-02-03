#include <stdio.h>
#include <CL/cl.h>
#include<stdlib.h>

//Max source size of the kernel string
#define MAX_SOURCE_SIZE (0x100000)
int main(void)
{
	// Create the two input vectors
	int i;
	int LIST_SIZE;
	printf("Enter how many elements: ");
	scanf("%d",&LIST_SIZE);

	int *decimal = (int*) malloc (sizeof (int) * LIST_SIZE);
	
	//Initialize the input vectors
	printf("Enter the elements\n");
	for(i = 0; i < LIST_SIZE; i++)
	{
		scanf("%d",&decimal[i]); 
	}
	
	// Load the kernel source code into the array source_str
	FILE *fp;
	char *source_str;
	size_t source_size;
	fp = fopen("q1.cl", "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		getchar();
		exit(1);
	}

	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose( fp );

	//1 Get platform and device information
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_ALL, 1,&device_id,&ret_num_devices);
	

	//2 Create an OpenCL context
	cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
	

	//3 Create a command queue
	cl_command_queue command_queue = clCreateCommandQueue(context, device_id, NULL, &ret);
	
	//4 Create memory buffers on the device for each vector A, B and C
	cl_mem decimal_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,LIST_SIZE * sizeof(int), NULL, &ret);
	cl_mem octal_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,LIST_SIZE * sizeof(int), NULL, &ret);
	

	//5 Copy the lists A and B to their respective memory buffers
	ret = clEnqueueWriteBuffer(command_queue, decimal_mem_obj, CL_TRUE, 0,LIST_SIZE * sizeof(int), decimal, 0, NULL, NULL);

	
	//6 Create a program from the kernel source
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source_str, (const size_t *)&source_size, &ret);
	

	//7 Build the program
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	

	//8 Create the OpenCL kernel object
	cl_kernel kernel = clCreateKernel(program, "dec_to_oct", &ret);
	

	//9 Set the arguments of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&decimal_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&octal_mem_obj);
	

	//10 Execute the OpenCL kernel on the array
	size_t global_item_size = LIST_SIZE;
	size_t local_item_size = 1;
	

	//11 Execute the kernel on the device
	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);
	ret = clFinish(command_queue);
	
	//12 Read the memory buffer C on the device to the local variable C
	int *octal = (int*)malloc(sizeof(int)*LIST_SIZE);
	ret = clEnqueueReadBuffer(command_queue, octal_mem_obj, CL_TRUE, 0,LIST_SIZE * sizeof(int), octal, 0, NULL, NULL);
	
	// Display the result to the screen
	printf("Decimal\t\tOctal\n");
	for(i = 0; i < LIST_SIZE; i++)
		printf("%d\t\t%d\n", decimal[i],octal[i]);
	
	//13 Clean up
	ret = clFlush(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(decimal_mem_obj);
	ret = clReleaseMemObject(octal_mem_obj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);
	free(decimal);
	free(octal);
	getchar();
	return 0;
	}