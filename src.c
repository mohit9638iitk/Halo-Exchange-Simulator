#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Global variables
double *top, *bottom, *left, *right; //These are 1D array and will receive the nieghbouring data in them.
int n;
MPI_Datatype row;
MPI_Datatype column;
char *rightbuffer;
char *leftbuffer;
char *topbuffer;
char *bottombuffer;
double data[1024][1024];
double temp[1024][1024];
void s_to_right(int option,int src,int p_sqrt,int flag){
    int dest=src+1;
	if(option==1){ //Multiple MPI_Sends
		if(flag)
		{
			for(int i=0;i<n;i++)
			{
				MPI_Send(&data[i][n-1],1,MPI_DOUBLE,dest,src,MPI_COMM_WORLD);
			}
		}
		else
		{
			MPI_Status state;
			for(int i=0;i<n;i++)
			{
				MPI_Recv(&right[i],1,MPI_DOUBLE,dest,MPI_ANY_TAG,MPI_COMM_WORLD,&state);
			}
		}
    }
    else if(option==2){ //MPI_Pack
		if(flag)
		{

			char buffer[8*n];
			int position=0;
			for(int i=0; i<n;i++)
				MPI_Pack(&data[i][n-1],1,MPI_DOUBLE,buffer,8*n,&position, MPI_COMM_WORLD);
			
			MPI_Send(buffer, position, MPI_PACKED, dest, src, MPI_COMM_WORLD);
		}
		else
		{
			rightbuffer = (char *)malloc(8*n);
			MPI_Status state;
			MPI_Recv(rightbuffer, 8*n, MPI_PACKED, dest, MPI_ANY_TAG, MPI_COMM_WORLD,&state);
		}
    }
    else{ //MPI derived datatypes
		if(flag)
		{
		
			MPI_Send(&data[0][n-1],1,column,dest,src,MPI_COMM_WORLD);
		}
		else
		{
			MPI_Status state;
			MPI_Recv(right, n, MPI_DOUBLE, dest, MPI_ANY_TAG, MPI_COMM_WORLD,&state);
		}
    }
}
void s_to_bottom( int option,int src,int p_sqrt,int flag){
	int dest=(((src/p_sqrt)+1)*(p_sqrt))+(src%p_sqrt);
	if(option==1){ //Multiple MPI_Sends
		if(flag)
		{
			for(int i=0;i<n;i++)
			{
				MPI_Send(&data[n-1][i],1,MPI_DOUBLE,dest,src,MPI_COMM_WORLD);
			}
		}
		else
		{
			MPI_Status state;
			for(int i=0;i<n;i++)
			{
				MPI_Recv(&bottom[i],1,MPI_DOUBLE,dest,MPI_ANY_TAG,MPI_COMM_WORLD,&state);
			}
		}
    }
    else if(option==2){ //MPI_Pack
		if(flag)
		{
		
			char buffer[8*n];
			int position=0;
			for(int i=0; i<n;i++)
				MPI_Pack(&data[n-1][i],1,MPI_DOUBLE,buffer,8*n,&position, MPI_COMM_WORLD);
		
			MPI_Send(buffer, position, MPI_PACKED, dest, src, MPI_COMM_WORLD);
		}
		else
		{
			MPI_Status state;
			bottombuffer = (char *)malloc(8*n);
			MPI_Recv(bottombuffer, 8*n, MPI_PACKED, dest, MPI_ANY_TAG, MPI_COMM_WORLD,&state);
		}
    }
    else{ //MPI derived datatypes
		if(flag)
		{
			MPI_Send(data[n-1],1,row,dest,src,MPI_COMM_WORLD);
		}
		else
		{
			MPI_Status state;
			MPI_Recv(bottom, 1, row, dest, MPI_ANY_TAG, MPI_COMM_WORLD,&state);
		}
    }
}
void s_to_left(int option,int src,int p_sqrt,int flag){
	int dest=src-1;
	if(option==1){ //Multiple MPI_Sends
		if(flag)
		{
			for(int i=0;i<n;i++)
			{
				MPI_Send(&data[i][0],1,MPI_DOUBLE,dest,src,MPI_COMM_WORLD);
			}
		}
		else
		{
			MPI_Status state;			
			for(int i=0;i<n;i++)
			{
				MPI_Recv(&left[i],1,MPI_DOUBLE,dest,MPI_ANY_TAG,MPI_COMM_WORLD,&state);
			}
		}
    }
    else if(option==2){ //MPI_Pack
		if(flag)
		{
			char buffer[8*n];
		
			int position=0;
			for(int i=0; i<n;i++)
				MPI_Pack(&data[i][0],1,MPI_DOUBLE,buffer,8*n,&position, MPI_COMM_WORLD);
			MPI_Send(buffer, position, MPI_PACKED, dest, src, MPI_COMM_WORLD);
		}
		else
		{	
			MPI_Status state;
			leftbuffer = (char *)malloc(8*n);
			MPI_Recv(leftbuffer, 8*n, MPI_PACKED, dest, MPI_ANY_TAG, MPI_COMM_WORLD,&state);
		}
    }
    else{ //MPI derived datatypes
		if(flag)
		{		
			MPI_Send(&data[0][0],1,column,dest,src,MPI_COMM_WORLD);
		}
		else
		{
			MPI_Status state;
			MPI_Recv(left, n, MPI_DOUBLE, dest, MPI_ANY_TAG, MPI_COMM_WORLD,&state);
		}
    }
}
void s_to_top(int option,int src,int p_sqrt,int flag){
	int dest=(((src/p_sqrt)-1)*(p_sqrt))+(src%p_sqrt);
	if(option==1){ //Multiple MPI_Sends
		if(flag)
		{
		
			for(int i=0;i<n;i++)
			{
				MPI_Send(&data[0][i],1,MPI_DOUBLE,dest,src,MPI_COMM_WORLD);
			}
		}
		else
		{
			MPI_Status state;
			for(int i=0;i<n;i++)
			{
				MPI_Recv(&top[i],1,MPI_DOUBLE,dest,MPI_ANY_TAG,MPI_COMM_WORLD,&state);
			}
		}
    }
    else if(option==2){ //MPI_Pack
		if(flag)
		{
		
			char buffer[8*n];
			int position=0;
			for(int i=0; i<n;i++)
				MPI_Pack(&data[0][i],1,MPI_DOUBLE,buffer,8*n,&position, MPI_COMM_WORLD);
		
			MPI_Send(buffer, position, MPI_PACKED, dest, src, MPI_COMM_WORLD);
		}
		else
		{
			topbuffer = (char *)malloc(8*n);
			MPI_Status state;
			MPI_Recv(topbuffer, 8*n, MPI_PACKED, dest, MPI_ANY_TAG, MPI_COMM_WORLD,&state);
		}
    }
    else{ //MPI derived datatypes
		if(flag)
		{
			MPI_Send(data[0],1,row,dest,src,MPI_COMM_WORLD);
		}
		else
		{
			MPI_Status state;
			MPI_Recv(top, 1, row, dest, MPI_ANY_TAG, MPI_COMM_WORLD,&state);
		}
    }
}

void right_unpack(){
	int position = 0;
	for(int i =0;i<n;i++)
		MPI_Unpack(rightbuffer,8*n,&position,&right[i],1,MPI_DOUBLE,MPI_COMM_WORLD);
}
void left_unpack(){
	int position = 0;
	for(int i =0;i<n;i++)
		MPI_Unpack(leftbuffer,8*n,&position,&left[i],1,MPI_DOUBLE,MPI_COMM_WORLD);
}
void top_unpack(){
	int position = 0;
	for(int i =0;i<n;i++)
		MPI_Unpack(topbuffer,8*n,&position,&top[i],1,MPI_DOUBLE,MPI_COMM_WORLD);
}
void bottom_unpack(){
	int position = 0;
	for(int i =0;i<n;i++)
		MPI_Unpack(bottombuffer,8*n,&position,&bottom[i],1,MPI_DOUBLE,MPI_COMM_WORLD);
}

int main(int argc, char *argv[]){
	MPI_Init(NULL,NULL);
	int myrank,size;
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	n = atoi(argv[1]); // number of data elements. N = nxn
	int num_steps = atoi(argv[2]);
	int option = 1; // 1: Multiple MPI_Sends; 2: MPI_Pack; 3: MPI derived datatypes;
	// double data[n][n]; we can't allocate data[1024][1024] in function 
	double startime,endtime, max_time;
	int divide;
	
	// Creating MPI Derived data types if option==3 
	MPI_Type_contiguous(n,MPI_DOUBLE,&row); // For sending a row of 2d matrix
	MPI_Type_commit(&row);
	MPI_Type_vector(n,1,1024,MPI_DOUBLE,&column); //For sending columns of 2d matrix
	MPI_Type_commit(&column);
	top = (double *)malloc(n*sizeof(double));
	bottom = (double *)malloc(n*sizeof(double));
	left = (double *)malloc(n*sizeof(double));
	right = (double *)malloc(n*sizeof(double));
   	Label: startime = MPI_Wtime();
	// Initializing the 1D arrays. These will receive the values throughs message passing.
	// Initializing the 2D data matrix 
	for(int i =0; i<n; i++){
		for(int j =0; j<n ; j++){
		data[i][j] = myrank;
		}
	}

	int p_sqrt = sqrt(size); // No. of Porcesses, size = p_sqrt x p_sqrt
	
	for(int itr=0; itr<num_steps;itr++){ //RUNNING it num_steps time
		// Corner Processes
		if(myrank==0){ //Top-Left corner process 
			
			
			s_to_right( option,myrank,p_sqrt,1);
			s_to_bottom( option,myrank,p_sqrt,1); 
				
			s_to_right( option,myrank,p_sqrt,0);
			s_to_bottom( option,myrank,p_sqrt,0);
	
			if(option==2){
				right_unpack();
				bottom_unpack();
			}
		 
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
				{
					temp[k][l]=data[k][l];
				}
			}
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(i==0)
					{
						if(j==0)
						{
							data[i][j]=(temp[i][j+1]+temp[i+1][j])/2;
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+right[i])/3;
							}
							else
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+temp[i][j+1])/3;
							}
						}
					}
					else
					{
						if(i==n-1)
						{
							if(j==0)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j+1]+bottom[j])/3;
							}
							else
							{
								if(j==n-1)
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+right[j]+bottom[j])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i][j+1]+bottom[j])/4;
								}
							}
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i+1][j]+right[i])/4;
							}
							else
							{
								if(j==0)
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j+1])/3;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
								}
							}
						}
					}
				}
			}
		}
		else if(myrank==p_sqrt-1){ //Top-Right corner process
				 
			s_to_bottom(option,myrank,p_sqrt,1);
			s_to_left(option,myrank,p_sqrt,1);
			s_to_bottom(option,myrank,p_sqrt,0);
			s_to_left(option,myrank,p_sqrt,0);
			
			if(option==2){
				bottom_unpack();
				left_unpack();
			}
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
				{
					temp[k][l]=data[k][l];
				}
			}
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(i==0)
					{
						if(j==0)
						{
							data[i][j]=(temp[i][j+1]+temp[i+1][j]+left[i])/3;
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j])/2;
							}
							else
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+temp[i][j+1])/3;
							}
						}
					}
					else
					{
						if(i==n-1)
						{
							if(j==0)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j+1]+left[i]+bottom[j])/4;
							}
							else
							{
								if(j==n-1)
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+bottom[j])/3;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i][j+1]+bottom[j])/4;
								}
							}
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i+1][j])/3;
							}
							else
							{
								if(j==0)
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j+1]+left[i])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
								}
							}
						}
					}
				}
			}
		}
		else if(myrank==size-p_sqrt){ //Bottom-Left corner process
			s_to_top(option,myrank,p_sqrt,1);
			s_to_right(option,myrank,p_sqrt,1);
			s_to_top(option,myrank,p_sqrt,0);
			s_to_right(option,myrank,p_sqrt,0);
			
			if(option==2){
				top_unpack();
				right_unpack();
			}
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
				{
					temp[k][l]=data[k][l];
				}
			}
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(i==0)
					{
						if(j==0)
						{
							data[i][j]=(temp[i+1][j]+temp[i][j+1]+top[j])/3;
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+top[j]+right[i])/4;
							}
							else
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+temp[i][j+1]+top[j])/4;
							}
						}
					}
					else
					{
						if(i==n-1)
						{
							if(j==0)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j+1])/2;
							}
							else
							{
								if(j==n-1)
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+right[i])/3;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i][j+1])/3;
								}
							}
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i+1][j]+right[i])/4;
							}
							else
							{
								if(j==0)
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j+1])/3;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
								}
							}
						}
					}
				}
			}
		}
		else if(myrank==size-1){ ////Bottom-Right corner process
			
			s_to_left(option,myrank,p_sqrt,1);
			s_to_top(option,myrank,p_sqrt,1);
			s_to_left(option,myrank,p_sqrt,0);
			s_to_top(option,myrank,p_sqrt,0);
			if(option==2){
				left_unpack();
				top_unpack();
			}
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
				{
					temp[k][l]=data[k][l];
				}
			}
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(i==0)
					{
						if(j==0)
						{
							data[i][j]=(temp[i+1][j]+temp[i][j+1]+top[j]+left[i])/4;
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+top[j])/3;
							}
							else
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+temp[i][j+1]+top[j])/4;
							}
						}
					}
					else
					{
						if(i==n-1)
						{
							if(j==0)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j+1]+left[i])/3;
							}
							else
							{
								if(j==n-1)
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1])/2;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i][j+1])/3;
								}
							}
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i+1][j])/3;
							}
							else
							{
								if(j==0)
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j+1]+left[i])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
								}
							}
						}
					}
				}
			}
		}
		// Top row processes
		else if(myrank<p_sqrt){
			
			s_to_right(option,myrank,p_sqrt,1);
			s_to_bottom(option,myrank,p_sqrt,1);
			s_to_left(option,myrank,p_sqrt,1);
			s_to_right(option,myrank,p_sqrt,0);
			s_to_bottom(option,myrank,p_sqrt,0);
			s_to_left(option,myrank,p_sqrt,0);
			if(option==2){
				right_unpack();
				bottom_unpack();
				left_unpack();
			}
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
				{
					temp[k][l]=data[k][l];
				}
			}
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(i==0)
					{
						if(j==0)
						{
							data[i][j]=(temp[i+1][j]+temp[i][j+1]+left[i])/3;
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+right[i])/3;
							}
							else
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+temp[i][j+1])/3;
							}
						}
					}
					else
					{
						if(i==n-1)
						{
							if(j==0)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j+1]+left[i]+bottom[j])/4;
							}
							else
							{
								if(j==n-1)
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+right[i]+bottom[j])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i][j+1]+bottom[j])/4;
								}
							}
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i+1][j]+right[i])/4;
							}
							else
							{
								if(j==0)
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j+1]+left[i])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
								}
							}
						}
					}
				}
			}
		}
		// Right-most column processes
		else if((myrank+1)%p_sqrt==0){
			
			
			s_to_bottom(option,myrank,p_sqrt,1);
			s_to_left(option,myrank,p_sqrt,1);
			s_to_top(option,myrank,p_sqrt,1);
			s_to_bottom(option,myrank,p_sqrt,0);
			s_to_left(option,myrank,p_sqrt,0);
			s_to_top(option,myrank,p_sqrt,0);
			if(option==2){
				bottom_unpack();
				left_unpack();
				top_unpack();
				
			}
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
				{
					temp[k][l]=data[k][l];
				}
			}
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(i==0)
					{
						if(j==0)
						{
							data[i][j]=(temp[i+1][j]+temp[i][j+1]+top[j]+left[i])/4;
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+top[j])/3;
							}
							else
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+temp[i][j+1]+top[j])/4;
							}
						}
					}
					else
					{
						if(i==n-1)
						{
							if(j==0)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j+1]+left[i]+bottom[j])/4;
							}
							else
							{
								if(j==n-1)
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+bottom[j])/3;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i][j+1]+bottom[j])/4;
								}
							}
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i+1][j])/3;
							}
							else
							{
								if(j==0)
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j+1]+left[i])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
								}
							}
						}
					}
				}
			}
		}
		// Bottom row processes
		else if(myrank>(size-p_sqrt)){
			
			s_to_left(option,myrank,p_sqrt,1);
			s_to_top(option,myrank,p_sqrt,1); 
			s_to_right(option,myrank,p_sqrt,1);
			s_to_left(option,myrank,p_sqrt,0);
			s_to_top(option,myrank,p_sqrt,0); 
			s_to_right(option,myrank,p_sqrt,0);
			if(option==2){
				top_unpack();
				left_unpack();
				right_unpack();
			}
		
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
				{
					temp[k][l]=data[k][l];
				}
			}
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(i==0)
					{
						if(j==0)
						{
							data[i][j]=(temp[i+1][j]+temp[i][j+1]+top[j]+left[i])/4;
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+top[j]+right[i])/4;
							}
							else
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+temp[i][j+1]+top[j])/4;
							}
						}
					}
					else
					{
						if(i==n-1)
						{
							if(j==0)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j+1]+left[i])/3;
							}
							else
							{
								if(j==n-1)
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+right[i])/3;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i][j+1])/3;
								}
							}
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i+1][j]+right[i])/4;
							}
							else
							{
								if(j==0)
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j+1]+left[i])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
								}
							}
						}
					}
				}
			}
		}
		// Left-most column processes
		else if(myrank%p_sqrt==0){
			
			s_to_top(option,myrank,p_sqrt,1);
			s_to_right(option,myrank,p_sqrt,1);
			s_to_bottom(option,myrank,p_sqrt,1);
			s_to_top(option,myrank,p_sqrt,0);
			s_to_right(option,myrank,p_sqrt,0);
			s_to_bottom(option,myrank,p_sqrt,0);
			if(option==2){
				bottom_unpack();
				top_unpack();
				right_unpack();
			}
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
				{
					temp[k][l]=data[k][l];
				}
			}
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(i==0)
					{
						if(j==0)
						{
							data[i][j]=(temp[i+1][j]+temp[i][j+1]+top[j])/3;
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+top[j]+right[i])/4;
							}
							else
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+temp[i][j+1]+top[j])/4;
							}
						}
					}
					else
					{
						if(i==n-1)
						{
							if(j==0)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j+1]+bottom[j])/3;
							}
							else
							{
								if(j==n-1)
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+right[i]+bottom[j])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i][j+1]+bottom[j])/4;
								}
							}
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i+1][j]+right[i])/4;
							}
							else
							{
								if(j==0)
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j+1])/3;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
								}
							}
						}
					}
				}
			}
		}
		// Center processes
		else{
			
			s_to_right(option,myrank,p_sqrt,1);
			s_to_bottom(option,myrank,p_sqrt,1);
			s_to_left(option,myrank,p_sqrt,1);
			s_to_top(option,myrank,p_sqrt,1);
			s_to_right(option,myrank,p_sqrt,0);
			s_to_bottom(option,myrank,p_sqrt,0);
			s_to_left(option,myrank,p_sqrt,0);
			s_to_top(option,myrank,p_sqrt,0);
			if(option==2){
				bottom_unpack();
				left_unpack();
				right_unpack();
				top_unpack();
			}
			for(int k=0;k<n;k++)
			{
				for(int l=0;l<n;l++)
				{
					temp[k][l]=data[k][l];
				}
			}
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					if(i==0)
					{
						if(j==0)
						{
							data[i][j]=(temp[i+1][j]+temp[i][j+1]+top[j]+left[i])/4;
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+top[j]+right[i])/4;
							}
							else
							{
								data[i][j]=(temp[i][j-1]+temp[i+1][j]+temp[i][j+1]+top[j])/4;
							}
						}
					}
					else
					{
						if(i==n-1)
						{
							if(j==0)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j+1]+left[i]+bottom[j])/4;
							}
							else
							{
								if(j==n-1)
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+bottom[j]+right[i])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i][j+1]+bottom[j])/4;
								}
							}
						}
						else
						{
							if(j==n-1)
							{
								data[i][j]=(temp[i-1][j]+temp[i][j-1]+temp[i+1][j]+right[i])/4;
							}
							else
							{
								if(j==0)
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j+1]+left[i])/4;
								}
								else
								{
									data[i][j]=(temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1])/4;
								}
							}
						}
					}
				}
			}
		}
		
		
	}
	// Calculating and printing the time taken by the slowest process.
    endtime = MPI_Wtime() - startime;
	MPI_Reduce (&endtime, &max_time, 1, MPI_DOUBLE, MPI_MAX, size-1, MPI_COMM_WORLD);
	if (myrank == size-1) printf ("%lf\n", max_time);

     /*if(myrank==size-1)
	 {
	 	for(int i=0;i<n;i++)
	 	{
	 		for(int j=0;j<n;j++)
	 		{
	 			printf("%lf ",data[i][j]);
	 		}
	 		printf("\n");
	 	}
	 } 
    */
    //For running all modes of communication 
    if(option!=3){
        option++;
        goto Label;
    }
	// Freeing space
	MPI_Type_free(&row);
	MPI_Type_free(&column);
    free(top); free(bottom); free(left); free(right);

    MPI_Finalize();
    return 0;
}
