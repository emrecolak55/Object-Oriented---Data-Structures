#include <iostream>
#include <fstream>
#include "Neurons.h"
#define MAX_SIZE 30
using namespace std;


int biggest_layer(int*);

int main(int argc, char* argv[]) {

	int temp[MAX_SIZE];
	int num = 0;

	ifstream openfile (argv[1]);
		if (openfile.is_open()){
    		while ( openfile >> temp[num]  ){ // If I read to 'arg' array directly It causes errors due to its bigger size ( MAX_SIZE )
					num ++;
   			}
    	openfile.close();
  		}
	else cout << "Unable to open file";


	int arg[num]; 
	for(int i =0; i<num ; i++)
		arg[i] = temp[i];


	int biggest_layer_number = biggest_layer( arg );

	Layer *lptr;
	int layer_num = arg[0];
	
	Network network(layer_num);


	for(int i=0;i<layer_num; i++){ // Creating layers
		int neuron_number = arg[i+1];
			try{
			lptr = new Layer(arg[i + layer_num + 1], neuron_number);
		}
		catch(const char* a){
			cout << a;     // write throw message and exit
			return 0;
		}
		
		network.insert_to_list(lptr,i); // If there's no error, fill layer 0 with x values
	}

	float** W= new float*[biggest_layer_number]; // 2 dimensional array // Should be square matrix
		for(int i=0;i<biggest_layer_number;i++)
			W[i] = new float[biggest_layer_number];
	
	float* B = new float[biggest_layer_number]; 
	



	for (int i=0; i<biggest_layer_number ; i++){ // Fill matrix with 0.1
		for(int j=0; j<biggest_layer_number;j++){
			W[i][j] = 0.1;
		}
	}
	
	for(int k=0;k<biggest_layer_number; k++){ // Fill matrix with 0.1
		B[k]= 0.1;
	}


	try{ // Checks whether x values match or not
			network.fill_firstlayer( &arg[ 1 + 2*layer_num ] , arg[1] , num-(1 + 2*layer_num ));
	}
	catch(const char* s){
		cout << s; // If there is error, exit // If there's not, It fills layer 0 in network class
		return 0;
	}
	


	for(int i=1 ; i<layer_num ; i++){ // Starting from layer 1
		for(int j=0 ; j< arg[i+1] ; j++){ // Calculate for each neuron
			double zvalue = 0;
			for(int n=0 ; n<arg[ i]; n++){ // "Layer i - 1 's neuron number" times
				zvalue += W[j][n] * network.get_activated(i-1, n)/1.0;  // math part
			}

			network.set_zvalue(zvalue + B[j], i , j); // add B[j] and send to func 
			network.set_activated(i , j); // calculate the activated
		}
	}


	for(int i = 0 ; i<layer_num; i++){ // Print out activated values
		cout << "Layer" << i << endl;
		for(int j =0 ; j< arg[i+1]; j++){
			cout << network.get_activated(i,j) << endl;
		}
	}

	delete [] W;
	delete [] B;

//	delete lptr;

	return 0;
}

int biggest_layer( int *arg){
	
	int biggest_layer_number = arg[1];
	for(int i=0;i<arg[0] -1;i++){
		if(  arg[i+2] > biggest_layer_number ) {
			biggest_layer_number = arg[i+2];
		}
	}
	return biggest_layer_number;
	
}

