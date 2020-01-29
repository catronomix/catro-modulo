#include "CatroModulo.hpp"

//Catro-Modulo CM3: PreSetSeq

struct CM3Module : Module {

	enum ParamIds {
		ENUMS(PARAM_REC, 8), 
		ENUMS(PARAM_EYE, 8), 
		PARAM_PATTERN,
		PARAM_MORPH,
		PARAM_LENGTH,
		PARAM_TRYME,
		PARAM_SCAN,
		PARAM_SELECT,
		PARAM_Q,
		PARAM_SEQ,
		PARAM_RESET,
		PARAM_STEP,
		NUM_PARAMS,
	};
	enum InputIds {
		ENUMS(INPUT_REC, 8), 
		ENUMS(INPUT_EYE, 8), 
		INPUT_PATTERN,
		INPUT_STEP,
		INPUT_MORPH,
		INPUT_RESET,
		INPUT_LENGTH,
		INPUT_SELECT,
		INPUT_BPM,
		INPUT_TRYME,
		NUM_INPUTS
	};
	enum OutputIds {
		ENUMS(OUTPUT_EYE, 8), 
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	//initializations
	std::string display_pat = "";
	std::string display_len = "";
	std::string strings_pat[16] = {"SEQ", "REV", "S0Q", "R0V", "NZN", "CUC", "ZZ1", "ZZ2", "U7D", "U4D", "U3D", ">-<", "/\\/", ".-.", "\\/\\", "RND"};
	std::string strings_len[16] = {" 01", " 02", " 03", " 04", " 05", " 06", " 07", " 08", " 09", " 10", " 11", " 12", " 13", " 14", "15", "16"};
	dsp::SchmittTrigger recordTrigger[16];
	float iselect = 0.0f;	
	float recsel = 0.0f;
	int ballsel = 0;
	float recball_x;
	float recball_y;
	float recball_xarray[8] = {178.8 , 212.4 , 242.7 , 212.4 , 178.8 , 145.3 , 115.0 , 145.3};
	float recball_yarray[8] = {89.5 , 119.9 , 153.4 , 186.9 , 217.2 , 186.9 , 153.4 , 119.9 };
	float eyepatch_val[8] = {};	

	CM_SelSeq sequencer;
	CM_Recorder recorder;
	CM_BpmClock bpmclock;

	
	CM3Module() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		int y = 0;
		for(int i = 0; i < 16; i += 2){
			configParam(CM3Module::PARAM_REC + y, 0.0f, 1.0f, 0.0f, "record values in slot " + std::to_string(y + 1));
			configParam(CM3Module::PARAM_EYE + y, -1.0f, 1.0f, 0.0f, "value " + std::to_string(y + 1), "", 0.0f, 100.0f);
			y++;
		}
		
		configParam(CM3Module::PARAM_PATTERN, 0.0f, 15.0f, 0.0f, "pattern select", "", 0.0f, 1.0f, 1.0f);
		configParam(CM3Module::PARAM_MORPH, -1.0f, 1.0f, 0.0f, "(multiplied < source > recording)");
		configParam(CM3Module::PARAM_LENGTH, 0.0f, 15.0f, 7.0f, "pattern lenght", "", 0.0f, 1.0f, 1.0f);
		configParam(CM3Module::PARAM_TRYME, 0.0f, 1.0f, 0.0f, "randomize (!)");
		configParam(CM3Module::PARAM_SCAN, 0.0f, 1.0f, 0.0f, "enable scan/blend");
		configParam(CM3Module::PARAM_SELECT, 0.0f, 7.99999f, 0.0f, "select recording for output");
		configParam(CM3Module::PARAM_SEQ, 0.0f, 1.0f, 1.0f, "enable sequencer", "", 0.0f, -1.0f, 1.0f);
		configParam(CM3Module::PARAM_RESET, 0.0f, 1.0f, 0.0f, "reset");
		configParam(CM3Module::PARAM_STEP, 0.0f, 1.0f, 0.0f, "step");

		recball_x = recball_xarray[0];
		recball_y = recball_yarray[0];
		}
	
	void process(const ProcessArgs &args) override;


	json_t *dataToJson() override {

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


	void dataFromJson(json_t *rootJ) override {
		// running
		json_t *recorderJ = json_object_get(rootJ, "recorder");
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				recorder.load(i, j, json_real_value(json_array_get(recorderJ, 8 * i + j)));
			}
		}

	}

	// For more advanced Module features, read Rack's engine.hpp header file
	// - dataToJson, dataFromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - onReset, onRandomize, onCreate, onDelete: implements special behavior when user clicks these from the context menu
};

void CM3Module::process(const ProcessArgs &args) {

	//process tryme button
	recorder.tryme((params[PARAM_TRYME].getValue() || inputs[INPUT_TRYME].getVoltage()) * 10.0);

	//mix params and inputs
	float morph = (inputs[INPUT_MORPH].isConnected()) ? inputs[INPUT_MORPH].getVoltage() * 0.1f + params[PARAM_MORPH].getValue() : params[PARAM_MORPH].getValue();
	float seq_active = 1.0 - params[PARAM_SEQ].getValue();
	float seq_reset = (inputs[INPUT_RESET].getVoltage() || params[PARAM_RESET].getValue());
	float seq_pattern = clamp(roundf((inputs[INPUT_PATTERN].isConnected()) ? inputs[INPUT_PATTERN].getVoltage() * 0.1f * params[PARAM_PATTERN].getValue() : params[PARAM_PATTERN].getValue()), 0.0, 15.0);
	float seq_len = clamp(roundf((inputs[INPUT_LENGTH].isConnected()) ? inputs[INPUT_LENGTH].getVoltage() * 0.1f * params[PARAM_LENGTH].getValue() : params[PARAM_LENGTH].getValue()), 0.0, 15.0);
	float doscan = (params[PARAM_SCAN].getValue() && params[PARAM_SEQ].getValue());

	//check for bpm cv
	float seq_step = 0;
	if (inputs[INPUT_BPM].isConnected()){
		bpmclock.setcv(inputs[INPUT_BPM].getVoltage());
	}
	
	bpmclock.setReset(inputs[INPUT_RESET].getVoltage() || params[PARAM_RESET].getValue());
		
	if (inputs[INPUT_BPM].isConnected()){
		bpmclock.step(args.sampleTime);
		seq_step = bpmclock.track(1);
	}else{
		seq_step = (inputs[INPUT_STEP].getVoltage() || params[PARAM_STEP].getValue());
	}


	//process eyes
	float eyeval[8] = {};
	for (int i = 0; i < 8; i++) {
		float in = 1.0f;
		float eye = params[i+PARAM_EYE].getValue();
		if (inputs[i+PARAM_EYE].isConnected()){
			in = inputs[i+PARAM_EYE].getVoltage() * 0.1f;
		}
		eyeval[i] = clamp(in * eye, -1.0f, 1.0f);
	}

	//record when requested
		for (int i = 0; i < 8; i++) {
			if (recordTrigger[i].process((inputs[INPUT_REC+i].getVoltage() || params[PARAM_REC+i].getValue()))){
				recorder.record(eyeval, i);
			}
		}

	//process sequencer
	if (seq_active == 1.0){
		sequencer.reset(seq_reset);
		sequencer.step(seq_step, seq_len);
		if (sequencer.patternized == true) {
			iselect = sequencer.sequence(seq_pattern);
		}
	}else{
		iselect = clamp((inputs[INPUT_SELECT].isConnected()) ? inputs[INPUT_SELECT].getVoltage() * 0.1f * params[PARAM_SELECT].getValue() : params[PARAM_SELECT].getValue(), 0.0, 7.99999f);
	}
	recorder.scan(iselect, doscan);
	recorder.mix(eyeval,morph);
	for (int i = 0; i < 8; i++) {
		if (iselect != -1.0){
			outputs[OUTPUT_EYE + i].setVoltage(recorder.output(i));
		}else{
			outputs[OUTPUT_EYE + i].setVoltage(0.0f);
		}
		
	}

	//set eyepatches
	for (int i = 0; i < 8; i++) {
		eyepatch_val[i] = recorder.callget(i);
	}
	
	//set displays
	display_pat = (seq_active) ? strings_pat[int(seq_pattern)] : "OFF";
	display_len = strings_len[int(seq_len)];

	//recball
	if (iselect != -1.0){
		ballsel = (int(iselect + 0.5) > 7) ? 0 : int(iselect + 0.5);
		recball_x = recball_xarray[ballsel] + 9.0;
		recball_y = recball_yarray[ballsel] + 9.0;
	}else{
		recball_x = recball_xarray[0];
		recball_y = recball_yarray[0];
	}
	
}

struct CM3ModuleWidget : ModuleWidget {

	CM3ModuleWidget(CM3Module *module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-3.svg")));

		addChild(createWidget<ScrewSilver>(Vec(10, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 20, 0)));
		addChild(createWidget<ScrewSilver>(Vec(30, 365)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 40, 365)));

		int y = 0; //initialize reusable counter

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
			addParam(createParam<CM_Recbutton>(Vec(recbuttons[i],recbuttons[i+1] - 0.5), module, CM3Module::PARAM_REC + y));
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
			addInput(createInput<CM_Input_small>(Vec(recin[i],recin[i+1] - 0.5), module, CM3Module::INPUT_REC + y));
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
			
			addParam(createParam<CM_Knob_bigeye>(Vec(bigeyes[i],bigeyes[i+1] - 0.5), module, CM3Module::PARAM_EYE + y));
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
			addInput(createInput<CM_Input_small>(Vec(eyein[i],eyein[i+1] - 0.5), module, CM3Module::INPUT_EYE + y));
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
			addOutput(createOutput<CM_Output_small>(Vec(eyeout[i],eyeout[i+1] - 0.5), module, CM3Module::OUTPUT_EYE + y));
			y++;
		}

		//OTHER ELEMENTS
		addParam(createParam<CM_Knob_small_def_half_16>(Vec(33.4 , 34.7), module, CM3Module::PARAM_PATTERN));
		addParam(createParam<CM_Slider_big_red>(Vec(156.5 , 17.9), module, CM3Module::PARAM_MORPH));
		addParam(createParam<CM_Knob_small_def_half_16>(Vec(326.0 , 34.7), module, CM3Module::PARAM_LENGTH));
		addParam(createParam<CM_TryMe_button>(Vec(15.0 , 320.1), module, CM3Module::PARAM_TRYME));
		addParam(createParam<CM_Switch_small>(Vec(137.8 , 309.0), module, CM3Module::PARAM_SCAN));
		addParam(createParam<CM_Knob_huge_red_os>(Vec(161.3 , 286.0), module, CM3Module::PARAM_SELECT));
		//addParam(createParam<CM_Knob_small_def>(Vec(232.2 , 304.5), module,PARAM_Q, 0.1f, 0.9f, 0.5f)); //maybe implement later?
		addParam(createParam<CM_Switch_small>(Vec(366. , 309.0), module, CM3Module::PARAM_SEQ));
		addParam(createParam<CM_I_def_tinybuttonR>(Vec(263.0 , 38.7), module, CM3Module::PARAM_RESET));
		addParam(createParam<CM_I_def_tinybuttonL>(Vec(85.4 , 38.7), module, CM3Module::PARAM_STEP));



		addInput(createInput<CM_Input_def>(Vec(15.7 , 60.1), module, CM3Module::INPUT_PATTERN));
		addInput(createInput<CM_Input_def>(Vec(94.0 , 38.7), module, CM3Module::INPUT_STEP));
		addInput(createInput<CM_Input_bpm>(Vec(127.5 , 38.7), module, CM3Module::INPUT_BPM));
		addInput(createInput<CM_Input_def>(Vec(183.5 , 45.4), module, CM3Module::INPUT_MORPH));
		addInput(createInput<CM_Input_def>(Vec(250.8 , 38.7), module, CM3Module::INPUT_RESET));
		addInput(createInput<CM_Input_def>(Vec(352.3 , 61.4), module, CM3Module::INPUT_LENGTH));
		addInput(createInput<CM_Input_def>(Vec(183.5 , 259.0), module, CM3Module::INPUT_SELECT));
		addInput(createInput<CM_Input_def>(Vec(42.2 , 320.8), module, CM3Module::INPUT_TRYME));

		//LCD display pattern
		if (module)
		{
			TxtDisplayWidget *dispat = new TxtDisplayWidget();
			dispat->box.pos = Vec(29.9, 11.0);
			dispat->box.size = Vec(38.0, 20.4);
			dispat->txt = &module->display_pat;
			addChild(dispat);
		}

		//LCD display length
		if (module)
		{
			TxtDisplayWidget *dislen = new TxtDisplayWidget();
			dislen->box.pos = Vec(322.4, 11.0);
			dislen->box.size = Vec(38.0, 20.4);
			dislen->txt = &module->display_len;
			addChild(dislen);
		}

		//selector indicator yellow
		if (module){
			CM3_RecBall *recball = new CM3_RecBall();
			recball->box.size = Vec(32.0, 32.0);
			recball->recball_x = &module->recball_x;
			recball->recball_y = &module->recball_y;
			addChild(recball);
		}

		//eyepatches: indicate the actual output
		if (module)
		{
			float dd = 20.5; //distance from origin
			float rr = 2.5;  //radius of circle
			CM3_EyePatch *eyepatch[8] = {
				new CM3_EyePatch(77.4, 117.4, dd, rr),
				new CM3_EyePatch(55.2, 169.1, dd, rr),
				new CM3_EyePatch(77.4, 220.9, dd, rr),
				new CM3_EyePatch(107.0, 272.6, dd, rr),
				new CM3_EyePatch(313.2, 117.4, dd, rr),
				new CM3_EyePatch(335.4, 169.1, dd, rr),
				new CM3_EyePatch(313.2, 220.9, dd, rr),
				new CM3_EyePatch(283.6, 272.6, dd, rr)};
			for (int i = 0; i < 8; i++)
			{
				eyepatch[i]->eyepatch_val = &module->eyepatch_val[i];
				addChild(eyepatch[i]);
			}
		}
	};
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per pluginInstance, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelCM3Module = createModel<CM3Module, CM3ModuleWidget>("CatroModulo_CM-3");
