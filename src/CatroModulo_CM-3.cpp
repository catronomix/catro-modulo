#include "CatroModulo.hpp"
#include "dsp/digital.hpp"

//Catro-Module CM3: 

//defining 
const int PARAM_PATTERN = 16;
const int PARAM_MORPH = 17;
const int PARAM_LENGTH = 18;
const int PARAM_TRYME = 19;
const int PARAM_SCAN = 20;
const int PARAM_SELECT = 21;
const int PARAM_Q = 22;
const int PARAM_SEQ = 23;
const int PARAM_RESET = 24;
const int PARAM_STEP = 25;
const int INPUT_PATTERN = 16;
const int INPUT_STEP = 17;
const int INPUT_MORPH = 18;
const int INPUT_RESET = 19;
const int INPUT_LENGTH = 20;
const int INPUT_SELECT = 21;
SchmittTrigger recordTrigger[16];
float iselect = 0.0f;	
float recsel = 0.0f;

//SELECT sequencer
struct CM_SelSeq {
	private:
	SchmittTrigger stepTrigger;
	SchmittTrigger resetTrigger;
	int patterns[16][16] = {};
	bool dostep = true;
	
	public:
	int astep = 0;
	bool patternized = false;


	CM_SelSeq(){} 

	//sequencer built-in patterns
 	void patternize(){

		int pat0[16] =  {0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7};
		int pat1[16] =  {0,7,6,5,4,3,2,1,0,7,6,5,4,3,2,1};
		int pat2[16] =  {0,-1,1,-1,2,-1,3,-1,4,-1,5,-1,6,-1,7,-1};
		int pat3[16] =  {0,-1,7,-1,6,-1,5,-1,4,-1,3,-1,2,-1,1,-1};
 
		int pat4[16] =  {0,2,6,4,1,3,7,5,0,2,6,4,1,3,7,5};
		int pat5[16] =  {0,2,4,6,1,3,5,7,0,2,4,6,1,3,5,7};
		int pat6[16] =  {0,2,1,3,2,4,3,5,4,6,5,7,6,0,7,1};
		int pat7[16] =  {0,3,1,4,2,5,3,6,4,7,5,0,6,1,7,2};
 
		int pat8[16] =  {0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0};
		int pat9[16] =  {0,1,2,3,4,3,2,1,0,1,2,3,4,3,2,1};
		int pat10[16] = {0,1,2,3,2,1,0,1,2,3,2,1,0,1,2,3};
		int pat11[16] = {0,4,1,5,2,6,3,7,4,0,5,1,6,2,7,3};

		int pat12[16] = {0,1,2,3,1,2,3,4,2,3,4,5,3,4,5,6};
		int pat13[16] = {0,1,2,1,2,3,2,3,4,3,4,5,4,5,6,5};
		int pat14[16] = {7,5,6,4,5,3,4,2,1,3,2,4,3,5,4,6};
		int pat15[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


		for (int i = 0; i < 16; i++){
		 patterns[0][i] = pat0[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[1][i] = pat1[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[2][i] = pat2[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[3][i] = pat3[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[4][i] = pat4[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[5][i] = pat5[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[6][i] = pat6[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[7][i] = pat7[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[8][i] = pat8[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[9][i] = pat9[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[10][i] = pat10[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[11][i] = pat11[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[12][i] = pat12[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[13][i] = pat13[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[14][i] = pat14[i];
		}
		for (int i = 0; i < 16; i++){
		 patterns[15][i] = pat15[i];
		}
		patternized = true;
	}

	void reset(float ireset){
		if (resetTrigger.process(ireset)) {
			astep = 0;
			dostep = true;
		}
	}

	void step(float istep, float len){
		if (stepTrigger.process(istep)) {
			if(astep < len && len <= 16){astep++;}else{astep = 0;}
			dostep = true;
		}
	}

	//Main sequencer function
	float sequence(int pat){
		if (dostep == true){
			if (pat == 15){
				recsel = rand() % 8;
			}else{
				recsel = patterns[pat][astep];
			}
			dostep = false;
		}
		return recsel;
	}

};

//CV recorder order: scan, mix, output
struct CM_Recorder {
	float store[8][8] = {};
	float call[8] = {};
	float out[8] = {};
	float lastselect = -1.0;
	float lastscan = -1.0;
	SchmittTrigger randomTrigger;

	CM_Recorder(){}

	void reset(){
		lastselect = -1.0;
	}
	
	void randomize(){
		srand(time(NULL));
	}

	//Save
	float save(int i, int j){
		return store[i][j];
	}

	//Load
	void load(int i, int j, float val){
		store[i][j] = val;
	}

	//store recording
	void record(float *eyeval, int i){
		for (int j = 0; j < 8; j++) {
			store[i][j] = eyeval[j];
		}
		reset();
	}

	//randomize recordings
	void tryme(float dotry){
		if (randomTrigger.process(dotry)){
			for (int i = 0; i < 8; i++){
				for (int j = 0; j < 8; j++) {
					rand(); rand(); //call random twice to get more random
					store[i][j] = ((double) rand() / (RAND_MAX)); 
				}
			}
			reset();
		}
	}

	//selector scanning
	void scan(float select, float scanner){
		if (scanner == 0.0){
			if (select > 7.5){
				select = 0.0;
			}else{
			select = roundf(select);
			}
		}
		if (scanner != lastscan){
			reset();
		}

		if (select != lastselect){
			for (int i = 0; i < 8; i++) {
				if (select < (i + 1.0)){
					if (i == 7){
						for (int j = 0; j < 8; j++) {
							call[j] = (store[i][j] * (1.0f - (select - i)) + (store[0][j] * (select - i)));
						}
						i = 9;
					}else{
						for (int j = 0; j < 8; j++) {
							call[j] = (store[i][j] * (1.0f - (select - i)) + (store[i+1][j] * (select - i)));
						}
						i = 9;
					}
				}
			}	
			lastselect = select;
		}
		lastscan = scanner;
	}

	//mix amount is between -1.0 and 1.0
	void mix(float *eyeval, float amount){
		if (amount >= 0.0f){
			for (int i = 0; i < 8; i++) {
				out[i] = (eyeval[i] * (1.0f - amount) + call[i] * amount);
			}
		}else{
			for (int i = 0; i < 8; i++) {
				out[i] = (eyeval[i] * call[i] * (0.0 - amount)) + (eyeval[i] * (1.0f + amount));
			}
		}
	}

	float output(int index){
		return out[index] * 10.0f;
	}
};

CM_SelSeq sequencer;
CM_Recorder recorder;

struct CM3Module : Module {
	enum ParamIds {
		NUM_PARAMS = 26
	};
	enum InputIds {
		NUM_INPUTS = 22
	};
	enum OutputIds {
		NUM_OUTPUTS = 8
	};
	enum LightIds {
		NUM_LIGHTS = 0
	};
	
	CM3Module() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;


	json_t *toJson() override {

		json_t *rootJ = json_object();

		json_t *recordsJ = json_array();
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				json_array_append_new(recordsJ, json_real(recorder.save(i,j)));
			}
		}
		json_object_set_new(rootJ, "recorder", recordsJ);
	
		return rootJ;
	}


	void fromJson(json_t *rootJ) override {
		// running
		json_t *recorderJ = json_object_get(rootJ, "recorder");
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				recorder.load(i, j, json_real_value(json_array_get(recorderJ, 8 * i + j)));
			}
		}

	}

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - onReset, onRandomize, onCreate, onDelete: implements special behavior when user clicks these from the context menu
};

void CM3Module::step() {

	//mix params and inputs
	float morph = (inputs[INPUT_MORPH].active) ? inputs[INPUT_MORPH].value * 0.1f + params[PARAM_MORPH].value : params[PARAM_MORPH].value;
	float seq_active = 1.0 - params[PARAM_SEQ].value;
	float seq_reset = (inputs[INPUT_RESET].value || params[PARAM_RESET].value);
	float seq_step = (inputs[INPUT_STEP].value || params[PARAM_STEP].value);
	float seq_pattern = roundf((inputs[INPUT_PATTERN].active) ? inputs[INPUT_PATTERN].value * 0.1f * params[PARAM_PATTERN].value : params[PARAM_PATTERN].value);
	float seq_len = roundf((inputs[INPUT_LENGTH].active) ? inputs[INPUT_LENGTH].value * 0.1f * params[PARAM_LENGTH].value : params[PARAM_LENGTH].value);
	float doscan = (params[PARAM_SCAN].value && params[PARAM_SEQ].value);

	//process tryme button
	recorder.tryme(params[PARAM_TRYME].value);

	//process sequencer
	if (seq_active == 1.0){
		sequencer.reset(seq_reset);
		sequencer.step(seq_step, seq_len);
		if (sequencer.patternized == true) {iselect = sequencer.sequence(seq_pattern);}
	}

	//process eyes
	float eyeval[8] = {};
	for (int i = 0; i < 8; i++) {
		float in = 1.0f;
		float eye = params[i+8].value;
		if (inputs[i+8].active){
			in = inputs[i+8].value * 0.1f;
		}
		eyeval[i] = clamp(in * eye, -1.0f, 1.0f);
	}


	//record when requested
		for (int i = 0; i < 8; i++) {
			if (recordTrigger[i].process((inputs[i].value || params[i].value))){
				recorder.record(eyeval, i);
			}
		}

	//process recorder to output
	
	if (seq_active == 0.0){
		iselect = (inputs[INPUT_SELECT].active) ? inputs[INPUT_SELECT].value * 0.1f * params[PARAM_SELECT].value : params[PARAM_SELECT].value;
	}
	recorder.scan(iselect, doscan);
	recorder.mix(eyeval,morph);
	for (int i = 0; i < 8; i++) {
		if (recsel != -1.0){
			outputs[i].value = recorder.output(i);
		}else{
			outputs[i].value = 0.0f;
		}
	}

}

struct CM3ModuleWidget : ModuleWidget {
	CM3ModuleWidget(CM3Module *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/CM-3.svg")));

		addChild(Widget::create<ScrewSilver>(Vec(30, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 60, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(30, 365)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 60, 365)));

		int y = 0; //initialize reusable counter
		sequencer.patternize(); //initialize sequencer patterns
		recorder.randomize(); //seed rng

		//REC BUTTONS
		float recbuttons[16] = {178.8 , 89.5 ,
							    212.4 , 119.9 ,
							    242.7 , 153.4 ,
							    212.4 , 186.9 ,
							    178.8 , 217.2 ,
							    145.3 , 186.9 ,
							    115.0 , 153.4 ,
							    145.3 , 119.9 };
		y = 0;
		for(int i = 0; i < 16; i += 2){
			addParam(ParamWidget::create<CM_Recbutton>(Vec(recbuttons[i],recbuttons[i+1] - 0.5), module, y, 0.0f, 1.0f, 0.0f));
			y++;
		}

		//REC INPUTS
		float recin[16] = { 185.5 , 127.8 ,
							196.5 , 149.0 ,
							217.4 , 160.0 ,
							196.5 , 171.0 ,
							185.5 , 192.3 ,
							174.5 , 171.0 ,
							153.2 , 160.0 ,
							174.5 , 149.0 };
		y = 0;
		for(int i = 0; i < 16; i += 2){
			addInput(Port::create<CM_Input_small>(Vec(recin[i],recin[i+1] - 0.5), Port::INPUT, module, y));
			y++;
		}


		//BIGEYES
		float bigeyes[16] = {54.9 , 94.9 ,
							32.7 , 146.6 ,
							54.9 , 198.4 ,
							84.5 , 250.1 ,
							290.7 , 94.9 ,
							312.9 , 146.6 ,
							290.7 , 198.4 ,
							261.1 , 250.1};
		y = 0;

		for(int i = 0; i < 16; i += 2){
			
			addParam(ParamWidget::create<CM_Knob_bigeye>(Vec(bigeyes[i],bigeyes[i+1] - 0.5), module, y + 8, -1.0f, 1.0f, 0.0f));
			//addChild(Widget::create<CM_Indicator_bigeye>(Vec(vbigeyes[i]-1,vbigeyes[i+1]-2))); //TODO: rotating indicator that shows output
			y++;
		}

		//EYE INPUTS
		float eyein[16] = {104.7 , 117.5 ,
							84.1 , 159.3 ,
							104.7 , 201.1 ,
							130.7 , 243.4 ,
							266.0 , 117.5 ,
							287.1 , 159.3 ,
							266.0 , 201.1 ,
							240.3 , 243.4};
		y = 0;
		for(int i = 0; i < 16; i += 2){
			addInput(Port::create<CM_Input_small>(Vec(eyein[i],eyein[i+1] - 0.5), Port::INPUT, module, y + 8));
			y++;
		}

		//EYE OUTPUTS
		float eyeout[16] = {30.2 , 97.1 ,
							6.4 , 158.8 ,
							30.2 , 220.5 ,
							63.6 , 281.4 ,
							340.0 , 97.1 ,
							363.5 , 158.8 ,
							340.0 , 220.5 ,
							304.5 , 281.4};
		y = 0;
		for(int i = 0; i < 16; i += 2){
			addOutput(Port::create<CM_Output_small>(Vec(eyeout[i],eyeout[i+1] - 0.5), Port::OUTPUT, module, y));
			y++;
		}

		//OTHER ELEMENTS
		addParam(ParamWidget::create<CM_Knob_small_def>(Vec(33.4 , 34.7), module, PARAM_PATTERN, 0.0f, 15.0f, 0.0f));
		addParam(ParamWidget::create<CM_Slider_big_red>(Vec(156.5 , 17.9), module, PARAM_MORPH, -1.0f, 1.0f, 0.0f));
		addParam(ParamWidget::create<CM_Knob_small_def>(Vec(326.0 , 34.7), module, PARAM_LENGTH, 0.0f, 15.0f, 7.0f));
		addParam(ParamWidget::create<CM_TryMe_button>(Vec(17.0 , 322.1), module, PARAM_TRYME, 0.0f, 1.0f, 0.0f));
		addParam(ParamWidget::create<CM_Switch_small>(Vec(137.8 , 309.0), module, PARAM_SCAN, 0.0f, 1.0f, 0.0f));
		addParam(ParamWidget::create<CM_Knob_huge_red_os>(Vec(161.5 , 286.0), module, PARAM_SELECT, 0.0f, 7.99999f, 0.0f));
		//addParam(ParamWidget::create<CM_Knob_small_def>(Vec(232.2 , 304.5), module,PARAM_Q, 0.1f, 0.9f, 0.5f)); //maybe implement later?
		addParam(ParamWidget::create<CM_Switch_small>(Vec(366. , 309.0), module,  PARAM_SEQ, 0.0f, 1.0f, 1.0f));
		addParam(ParamWidget::create<CM_I_def_tinybuttonR>(Vec(263.0 , 38.7), module, PARAM_RESET, 0.0f, 1.0f, 0.0f));
		addParam(ParamWidget::create<CM_I_def_tinybuttonL>(Vec(107.0 , 38.7), module, PARAM_STEP, 0.0f, 1.0f, 0.0f));



		addInput(Port::create<CM_Input_def>(Vec(15.7 , 60.1), Port::INPUT, module, INPUT_PATTERN));
		addInput(Port::create<CM_Input_def>(Vec(116.2 , 38.7), Port::INPUT, module, INPUT_STEP));
		addInput(Port::create<CM_Input_def>(Vec(183.5 , 45.4), Port::INPUT, module, INPUT_MORPH));
		addInput(Port::create<CM_Input_def>(Vec(250.8 , 38.7), Port::INPUT, module, INPUT_RESET));
		addInput(Port::create<CM_Input_def>(Vec(352.3 , 61.4), Port::INPUT, module, INPUT_LENGTH));
		addInput(Port::create<CM_Input_def>(Vec(183.5 , 259.0), Port::INPUT, module, INPUT_SELECT));
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCM3Module = Model::create<CM3Module, CM3ModuleWidget>("CatroModulo", "CatroModulo_CM-3", "CM-3", SEQUENCER_TAG);
