//#include <iostream>
#include <cmath>

// Murat Emre Çolak 150180061 Hatice Köse

	class Neuron{
		
		protected:
		double value; // z
		double activated_value; // a
		
		public:
			virtual void activate() =0;
			virtual void assign_value(double) =0;
			virtual void fill_values(double) =0; // It is only called for Layer 0 
			virtual double get_activated() =0;
			Neuron();
			virtual	~Neuron();
	};
	class SigmoidNeuron:public Neuron{
		
		public:
			void activate();
			void assign_value(double);
			void fill_values(double);
			double get_activated();
			SigmoidNeuron();
			~SigmoidNeuron();
	};
	class ReluNeuron:public Neuron{
		
		public:
			void activate();
			void assign_value(double);
			void fill_values(double);
			double get_activated();
			ReluNeuron();
			~ReluNeuron();
	};
	class LReluNeuron:public Neuron{
		
		public:
			void activate();
			void assign_value(double);
			void fill_values(double);
			double get_activated();
			LReluNeuron();
			~LReluNeuron();
	};
	class Layer{
		Neuron *neuronlist;
		
		public:
			void set_activated(int neuron_num){ // Calculates activated value
				neuronlist[neuron_num].activate();
			}
			void set_zvalue(double zvalue, int neuron_num){ // Assigns z value
				neuronlist[neuron_num].assign_value(zvalue);
			}
			double send_activated(int neuron_num){ // returns activated value
				return neuronlist[neuron_num].get_activated();	
			}
			Neuron& return_neuron(int neuron_num){ // returns neuron
				return neuronlist[neuron_num];
			}
			void insert_to_list(const Neuron *nptr, int i){ // inserts given neuron to layer's neuron list
				neuronlist[i] = *nptr;
			}
			Layer(int,int);
			Layer();
			~Layer();
	};
	class Network{
		Layer *layerlist;
					
			public:
			void fill_firstlayer(int*, int,int);	
			void set_activated(int layer_num, int neuron_num){
				layerlist[layer_num].set_activated(neuron_num);
			}
			void set_zvalue(double zvalue,int layer_num, int neuron_num){
				layerlist[layer_num].set_zvalue(zvalue, neuron_num);
			}
			double get_activated(int layer_num, int neuron_num){ 
				return layerlist[layer_num].send_activated(neuron_num);	
			}
		//	Neuron& get_neuron(int layer_num, int neuron_num){
		//		return layerlist[layer_num].return_neuron(neuron_num);
		//	}
		//	Layer& returnlayer(int layer_num){
		//		return layerlist[layer_num];
		//	}
			void insert_to_list(const Layer* lptr, int i){
				layerlist[i] = *lptr;
			}
			Network(int);
			Network();
			~Network();
			
	};
	
	///////////////////////////////////  FUNCTIONS  //////////////////////////////////////////////
							
	/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	
	
	Neuron::Neuron(){
		
	}
	Neuron::~Neuron(){
		//	cout << "GENERALNEURON DESTRUCTOR" << endl;
	} 
	
	
	
	
	/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////

	
	
	SigmoidNeuron::SigmoidNeuron(){
	
	}
	SigmoidNeuron::~SigmoidNeuron(){
		//	cout << "SIGMOID DESTRUCTOR"<< endl;
	}
	void SigmoidNeuron::activate(){
		const double E = exp(1.0);
		activated_value = 1 / (1 + pow(E, (-1)*value));
	}
	void SigmoidNeuron::assign_value(const double _value){
		value = _value;
	}
	void SigmoidNeuron::fill_values(const double _value){
		value = _value;
		activated_value = _value;
	}
	double SigmoidNeuron::get_activated(){
		return activated_value;
	}
	
		
	/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	
	ReluNeuron::ReluNeuron(){
	
	}
	ReluNeuron::~ReluNeuron(){
		//	cout << "RELU DESTRUCTOR"<< endl;
	}
	void ReluNeuron::activate(){

	
		if (value > 0){
			activated_value = value;
		}
		else {
			activated_value = 0;
		}
	
	}
	void ReluNeuron::assign_value(const double _value){
		value = _value;
	}
	void ReluNeuron::fill_values(const double _value){
		value = _value;
		activated_value = _value;
	}
	double ReluNeuron::get_activated(){
		return activated_value;
	}
	
		/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	
	LReluNeuron::LReluNeuron(){
	
	}
	LReluNeuron::~LReluNeuron(){
		//	cout << "LRELU DESTRUCTOR"<< endl;
	}
	void LReluNeuron::activate(){
	
			if (0.1*value > value){
			activated_value = 0.1* value;
		}
		else {
			activated_value = value;
		}
	}
	void LReluNeuron::assign_value(const double _value){
		value = _value;
	}
	void LReluNeuron::fill_values(const double _value){ 
		value = _value;
		activated_value = _value;
	}
	double LReluNeuron::get_activated(){
		return activated_value;
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	
	Layer::Layer(){
		
	}
	Layer::~Layer(){
		delete [] neuronlist;	
		//	cout << "LAYER DESTRUCTOR"<< endl;
	}
	
	Layer::Layer(int type, int neuron_number){ // Creates layer with given type ( 0 1 2 )
		if(type < 0 || type > 2) throw "Unidentified activation function!";
		
		if(type == 0){
			neuronlist = new SigmoidNeuron[neuron_number];
		}
		if(type == 1){
			neuronlist = new LReluNeuron[neuron_number];
		}
		if(type == 2){
			neuronlist = new ReluNeuron[neuron_number];
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////////
	
	Network::Network(){
	
	
	}
	Network::~Network(){
			delete [] layerlist;
		//	cout << "NETWORK DESTRUCTOR"<< endl;

	}
	Network::Network(int x){
		layerlist = new Layer[x];

	}
	
	void Network::fill_firstlayer(int *xvalues, int layer_zero_neuron_number , int difference){
		
		if(layer_zero_neuron_number != difference) throw "Input shape does not match!"; // If they dont match
				
		for(int i=0 ; i< difference ; i++){ // If they match, fill the values
			Neuron *ntemp = &layerlist[0].return_neuron(i);
			ntemp->fill_values(xvalues[i]);			
		}

				
	}	
