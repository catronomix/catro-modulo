#include "rack.hpp"
#include "CM_helpers.hpp"
#include "ctime"

using namespace rack;


// Forward-declare the Plugin, defined in Template.cpp
extern Plugin *pluginInstance;

// Forward-declare each Model, defined in each module source file
extern Model *modelCM1Module;
extern Model *modelCM2Module;
extern Model *modelCM3Module;
extern Model *modelCM4Module;
extern Model *modelCM5Module;
extern Model *modelCM6Module;
extern Model *modelCM7Module;
extern Model *modelCM8Module;
extern Model *modelCM9Module;
extern Model *modelCM10Module;

//interface elements
struct CM_Knob_small_def : SvgKnob {
	CM_Knob_small_def() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-knob_small_def.svg")));
        shadow->opacity = 0;

	}
};

struct CM_Knob_small_def_half : CM_Knob_small_def {
	CM_Knob_small_def_half() {
		minAngle = -0.5*M_PI;
		maxAngle = 0.5*M_PI;
	}
};

struct CM_Knob_small_def_half_16 : CM_Knob_small_def_half {
	CM_Knob_small_def_half_16() {
		snap = true;
	}
};

struct CM_Knob_small_red : SvgKnob {
	CM_Knob_small_red() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-knob_small_red.svg")));
        shadow->opacity = 0;

	}
};

struct CM_Knob_big_def : SvgKnob {
	CM_Knob_big_def() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-knob_big_def.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Knob_big_attn : SvgKnob {
	CM_Knob_big_attn() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-knob_big_attn.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Knob_big_offset : SvgKnob {
	CM_Knob_big_offset() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-knob_big_offset.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Knob_big_def_tt : CM_Knob_big_def {
	CM_Knob_big_def_tt() {
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
	}
};

struct CM_Knob_big_def_tts : CM_Knob_big_def {
	CM_Knob_big_def_tts() {
		minAngle = -0.75*M_PI;
		maxAngle = 0.75*M_PI;
		snap = true;
	}
};

struct CM_Knob_big_red : SvgKnob {
	CM_Knob_big_red() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-knob_big_red.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Knob_huge_red : SvgKnob {
	CM_Knob_huge_red() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-knob_huge_red.svg")));
        shadow->opacity = 0;
	}
};
struct CM_Knob_huge_red_os : CM_Knob_huge_red {
	CM_Knob_huge_red_os() {
		minAngle = 0.0*M_PI;
		maxAngle = 2.0*M_PI;
	}
};

struct CM_Knob_bigeye : SvgKnob {
	CM_Knob_bigeye() {
		minAngle = -1.0*M_PI;
		maxAngle = 1.0*M_PI;
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-knob_bigeye.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Pot1_small : SvgScrew {
	CM_Pot1_small() {
		sw->setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-pot1_small.svg")));
		box.size = sw->box.size;
	}
};

struct CM_Pot1_big : SvgScrew {
	CM_Pot1_big() {
		sw->setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-pot1_big.svg")));
		box.size = sw->box.size;

	}
};

struct CM_Input_def : SvgPort {
	CM_Input_def() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_def.svg")));
        shadow->opacity = 0;
	}
};

struct CM_I_def_tinybuttonL : SvgSwitch {
	CM_I_def_tinybuttonL() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_def_tinybuttonL.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_def_tinybuttonL_dn.svg")));
	}
};

struct CM_I_def_tinybuttonR :SVGSwitch {
	CM_I_def_tinybuttonR() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_def_tinybuttonR.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_def_tinybuttonR_dn.svg")));
	}
};

struct CM_Input_small : SvgPort {
	CM_Input_small() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_small.svg")));
        shadow->opacity = 0;
	}
};

struct CM_I_small_tinybuttonL : SvgSwitch {
	CM_I_small_tinybuttonL() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_small_tinybuttonL.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_small_tinybuttonL_dn.svg")));
	}
};

struct CM_Input_bpm : SvgPort {
	CM_Input_bpm() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_bpm.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Input_ext : SvgPort {
	CM_Input_ext() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-input_ext.svg")));
        shadow->opacity = 0;
	}
};


struct CM_Output_def : SvgPort {
	CM_Output_def() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-output_def.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Output_def_dark : SvgPort {
	CM_Output_def_dark() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-output_def)dark.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Output_small : SvgPort {
	CM_Output_small() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-output_small.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Output_bpm : SvgPort {
	CM_Output_bpm() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-output_bpm.svg")));
        shadow->opacity = 0;
	}
};

struct CM_Switch_small : SvgSwitch {
	CM_Switch_small() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-TS_small_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-TS_small_1.svg")));
	}
};

struct CM_Switch_smallh : SvgSwitch {
	CM_Switch_smallh() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-TS_smallh_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-TS_smallh_1.svg")));
	}
};

struct CM_TryMe_button : SvgSwitch {
	CM_TryMe_button() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-tryme_button.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-tryme_button_dn.svg")));
	}
};

struct CM_Recbutton : SvgSwitch {
	CM_Recbutton() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-recbutton.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-recbutton_dn.svg")));
	}
};

struct CM_Button_small_red : SvgSwitch {
	CM_Button_small_red() {
		momentary = true;
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-button_small_red.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-button_small_red_dn.svg")));
	}
};

struct CM_Slider_big_red : SvgSlider {
	CM_Slider_big_red() {
		horizontal = true;
		minHandlePos = Vec(-4, 0);
		maxHandlePos = Vec(58, 0);
		setBackgroundSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-slider_big_red_bg.svg")));
		setHandleSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-slider_big_red.svg")));
	}
	//void onDragMove(const event::DragMove &e) override;

};

struct CM_Switch_small_3 : SvgSwitch {
	CM_Switch_small_3() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-TS_small_3_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-TS_small_3_1.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-TS_small_3_2.svg")));
	}
};

struct CM_Ledbutton_mini : SvgSwitch {
	CM_Ledbutton_mini() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-ledbutton_mini_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM-ledbutton_mini_1.svg")));
	}
};

struct CM_8_normalizebutton : SvgSwitch {
	CM_8_normalizebutton() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM8_normoff.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM8_normon.svg")));
	}
};



//mechanisms

//SELECT sequencer
struct CM_SelSeq {
	private:
	dsp::SchmittTrigger stepTrigger;
	dsp::SchmittTrigger resetTrigger;
	int patterns[16][16] = {};
	bool dostep;
	float recsel;
	int astep;

	public:
	bool patternized;

	CM_SelSeq(){
		dostep = true;
		recsel = 0.0f;
		astep = 0;
		patternized = false;
		patternize();
	}
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
			astep = -1;
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
		if (dostep == true && astep >= 0){
			if (pat == 15){
				recsel = cm_gauss(4.0, 4.0);
			}else{
				recsel = patterns[pat][astep];
			}
			dostep = false;
		}else if (astep == -1){
			recsel = patterns[pat][0];
			dostep = true;
		}
		return recsel;
	}

};

//CV recorder order: scan, mix, output
struct CM_Recorder {
	private:
	float store[8][8] = {};
	float call[8] = {};
	float out[8] = {};
	float lastselect = -1.0;
	float lastscan = -1.0;
	dsp::SchmittTrigger randomTrigger;

	public:

	CM_Recorder(){
		randomize();
	}

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
					// rand(); rand(); //call random twice to get more random // might be too slow...
					store[i][j] = 2.0 * ((double) rand() / (RAND_MAX)) - 1.0;
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

	float callget(int eye){
		return call[eye];
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

//BPM system
struct CM_BpmClock {
	private:

	float clk_bpm;
	float bpm_cv;
	float phase;
	float pw;
	float freq;
	dsp::SchmittTrigger resetTrigger;
	dsp::SchmittTrigger trackingTrigger[3];
	float bpm_out[3] = {};
	float clk_out[3] = {};
	int resetframes = 0;


	//ext input detector
	dsp::SchmittTrigger externalClockTrigger;
	float extTime = 0.0f;
	float extLasttime[2] = {};
	// float extRate = 0.0f;
	// int extCount = 0;
	// float exthistory[4] = {};
	 int rateLock = 0;
	float extRateLocked = 0.0f;
	// float ret = 0.0f;

	public:

	CM_BpmClock(){
		clk_bpm = 0.0f;
		bpm_cv = 0.0f;
		phase = 0.0f;
		pw = 0.5f;
		freq = 1.0f;
	}

	//between 0 and 1000
	void setbpm(float bpm){
		clk_bpm = std::max(bpm, 0.0f);
		bpm_cv = bpmtocv(bpm);
		// freq = clk_bpm / 30.0; //double freq! -for halfstep
	}
	void setcv(float cv){
		setbpm(cvtobpm(cv));
	}
	
	float addcv(float cv){
		setbpm(clk_bpm + cvtobpm(cv));
		return bpm_cv;
	}

	float getcv(){
		return bpm_cv;
	}

	float getbpm(){
		return clk_bpm;
	}

	void step(float dt){
		pulsegen();
		freq = clk_bpm / 15.0f; //double freq! -for halfstep
		float deltaPhase = fminf(freq * dt, 0.5f); //delta is halftime
		phase += deltaPhase;
		if (phase >= 1.0f){phase -= 1.0f;}

	}

  	void setReset(float reset) {
		if (resetTrigger.process(reset)) {
			phase = 0.0f;
			trackingTrigger[0].reset();
			trackingTrigger[1].reset();
			trackingTrigger[2].reset();
			clk_out[0] = 1.0;
			clk_out[1] = 1.0;
			clk_out[2] = 1.0;
			resetframes = 1;
		}
	}

	float track(int out){
		if (resetframes == 0){
			return clk_out[out];
		}else if (resetframes < 22){
			resetframes++;
			return 0.0;
		}else{
			resetframes = 0;
			return clk_out[out];
		}
		
	}

	//TODO: make this compatible with 1V/oct
	// Previously it used to give Hz and not 1V/oct
	
	float bpmtocv(float bpm){
		return ((float)log(bpm / 60.0f) / (float)log(2)) - 1.0f;
		//return bpm / 60.0f;
	}

	float cvtobpm(float cv){
		return 120.0f * (float)pow(2, cv);
		//return cv * 60.0f;
	}

	float exttrack(float ext, float interval){
		if (externalClockTrigger.process(ext)){
			extLasttime[1] = extLasttime[0];
			extLasttime[0] = extTime;
			if (extLasttime[0] > 0 && abs(extLasttime[0] - extLasttime[1]) < 0.001){
				extRateLocked = (6.0f / ((extLasttime[0] + extLasttime[1] + interval) * 5.0f));
				if (rateLock == 0){
					setReset(1.0f);
					rateLock = 1;
				}
			}else{
				rateLock = 0;
			}
			extTime = 0.0f;
		}
		extTime += interval;
		
		return (extRateLocked > 0) ? extRateLocked : 0.0f;
	}

	void extreset(bool go){
		if (go){
		externalClockTrigger.reset();
		extreset();
		}
	}

	void extreset(){
		extTime = 0.0f;
		extLasttime[0] = 0.0f;
		extLasttime[1] = 0.0f;
		extRateLocked = 0.0f;
		// extCount = 0;
		 rateLock = 0;
		// extRateLocked = 0.0f;
	}

	private:

	bool compar(int num, float valone, const float valar[]){
		for (int i=0; i < num; i++){
					if (valar[i] != valone){
						return false;
					}
				}
				return true;
	}

	float sqr(){
		float sqr = phase < pw ? 1.0f : -1.0f;
		return sqr;
	}

	void pulsegen(){
		if (trackingTrigger[0].process(sqr())){
			clk_out[0] = !(clk_out[0]);
		}
		if (trackingTrigger[1].process(clk_out[0])){
			clk_out[1] = !(clk_out[1]);
		}
		if (trackingTrigger[2].process(clk_out[1])){
			clk_out[2] = !(clk_out[2]);
		}
	}
};

//simple stepper (count start at 0)
struct CM_stepper {
	private:
	int step_active = 0;
	int step_max = 8;
	bool isreset = false;
	int cooldown = 0;

	public:

	CM_stepper(){}

	void reset(){
		isreset = true;
	}

	//advance step, return to 0 on reaching max;
	int step(int max){
		step_max = max;
		if (step_active < step_max && isreset == false){
			step_active++;
		}else{
			step_active = 0;
			isreset = false;
		}
		return step_active;
	}
};

//LCD display (from cf modules)
struct NumDisplayWidget : TransparentWidget {

  float *value;
  std::shared_ptr<Font> font;

	NumDisplayWidget() {
		font = APP->window->loadFont(asset::plugin(pluginInstance, "res/Segment7Standard.ttf"));
	};

	void draw(const DrawArgs &args) override {
		// Background
		NVGcolor backgroundColor = nvgRGB(0x25, 0x2f, 0x24);
		NVGcolor borderColor = nvgRGB(0x10, 0x10, 0x10);
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, 0.0, 0.0, box.size.x, box.size.y, 4.0);
		nvgFillColor(args.vg, backgroundColor);
		nvgFill(args.vg);
		nvgStrokeWidth(args.vg, 1.0);
		nvgStrokeColor(args.vg, borderColor);
		nvgStroke(args.vg);

		nvgFontSize(args.vg, 16);
		nvgFontFaceId(args.vg, font->handle);
		nvgTextLetterSpacing(args.vg, 2.2);

		std::string to_display = std::to_string(*value).substr(0,5);
		while(to_display.length()< 5 ) to_display = ' ' + to_display;

		Vec textPos = Vec(3.0f, 17.0f);

		NVGcolor textColor = nvgRGB(0xff, 0xf4, 0x00);
		nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
		nvgText(args.vg, textPos.x, textPos.y, "~~~~~", NULL);
		nvgText(args.vg, textPos.x, textPos.y, ".....", NULL);
		nvgText(args.vg, textPos.x, textPos.y, "\\\\\\\\\\", NULL);

		nvgFillColor(args.vg, textColor);
		nvgText(args.vg, textPos.x, textPos.y, to_display.c_str(), NULL);
	}
};

//TEXT LCD display
struct TxtDisplayWidget : TransparentWidget {

  std::string *txt;
  std::shared_ptr<Font> font;

	TxtDisplayWidget() {
		font = APP->window->loadFont(asset::plugin(pluginInstance, "res/Segment7Standard.ttf"));
	};

	void draw(const DrawArgs &args) override {
		// Background
		NVGcolor backgroundColor = nvgRGB(0x25, 0x2f, 0x24);
		NVGcolor borderColor = nvgRGB(0x10, 0x10, 0x10);
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, 0.0, 0.0, box.size.x, box.size.y, 4.0);
		nvgFillColor(args.vg, backgroundColor);
		nvgFill(args.vg);
		nvgStrokeWidth(args.vg, 1.0);
		nvgStrokeColor(args.vg, borderColor);
		nvgStroke(args.vg);

		nvgFontSize(args.vg, 16);
		nvgFontFaceId(args.vg, font->handle);
		nvgTextLetterSpacing(args.vg, 2.2);

		std::string to_display = *txt;
		while(to_display.length()< 3 ) to_display = ' ' + to_display;

		Vec textPos = Vec(3.0f, 17.0f);

		NVGcolor textColor = nvgRGB(0xff, 0xf4, 0x00);
		nvgFillColor(args.vg, nvgTransRGBA(textColor, 16));
		nvgText(args.vg, textPos.x, textPos.y, "~~~", NULL);
		nvgText(args.vg, textPos.x, textPos.y, "...", NULL);
		nvgText(args.vg, textPos.x, textPos.y, "\\\\\\", NULL);

		nvgFillColor(args.vg, textColor);
		nvgText(args.vg, textPos.x, textPos.y, to_display.c_str(), NULL);
	}
};

//recorder buttons for CM3
struct CM3_RecBall : TransparentWidget {

	float *recball_x;
	float *recball_y;

	CM3_RecBall() {
		recball_x = nullptr;
		recball_y = nullptr;
	};

	void draw(const DrawArgs &args) override {
		//position
		if (recball_x && recball_y) {
			box.pos.x = *recball_x;
			box.pos.y = *recball_y;
		} else {
			box.pos.x = 178.1;
			box.pos.y = 89.5;
		}
		// circle
		NVGcolor yellow = nvgRGB(0xff, 0xf4, 0x00);
		nvgBeginPath(args.vg);
		nvgCircle(args.vg, 7.0, 7.0, 8.0);
		nvgFillColor(args.vg, yellow);
		nvgFill(args.vg);
	}
};

//bigeye indicators
struct CM3_EyePatch : TransparentWidget {

	float *eyepatch_val;
	float dd;
	float rr;

	CM3_EyePatch(float x, float y, float d, float r) {
		box.pos.x = x;
		box.pos.y = y;
		dd = d;
		rr = r;
	};

	void draw(const DrawArgs &args) override {

		//position
		 float relx = -dd * -sin(*eyepatch_val * M_PI);
		 float rely = dd * -cos(*eyepatch_val * M_PI);

		// circle
		nvgBeginPath(args.vg);
		nvgCircle(args.vg, relx, rely, rr);
		nvgFillColor(args.vg, rack::color::WHITE);
		nvgFill(args.vg);

	}
};

//yellow led in CM9
struct CM9_LedIndicator : SvgWidget {

	float *posx = nullptr;
	float *posy = nullptr;

	CM9_LedIndicator() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/CM9_ledinc.svg")));
		wrap();
	};

	void draw(const DrawArgs &args) override {
		if (posx && posy) {
			box.pos.x = *posx;
			box.pos.y = *posy;
		} else {
			box.pos.x = 178.1;
			box.pos.y = 89.5;
		}
		SVGWidget::draw(args);
	}
};

//Operator mode switch
struct CM_OP : Button {

	int *opmode = nullptr;
	const float opcoords[8] = {10.2, 15.4, 10.2, 5.1, 5.4, 10.5, 15.6, 10.5};

	CM_OP(float x, float y) {
		box.pos.x = x;
		box.pos.y = y;
	};

	void draw(const DrawArgs &args) override {
		// Background
		NVGcolor backgroundColor = nvgRGB(0xff, 0xf4, 0x00);
		nvgBeginPath(args.vg);
		nvgCircle(args.vg, opcoords[*opmode], opcoords[*opmode + 4], 2.5f);
		nvgFillColor(args.vg, backgroundColor);
		nvgFill(args.vg);		
	}

	void onDragStart(const event::DragStart& e) override {
		*opmode = (*opmode < 3) ? (*opmode + 1) : 0;
	}
	
	int getopmode(){
		return *opmode;
	}
};

//yellow big led indicator
struct BigLedIndicator : TransparentWidget {

  bool *lit;

	BigLedIndicator() {};

	void draw(const DrawArgs &args) override {
		// Background
		NVGcolor backgroundColor = nvgRGB(0x25, 0x2f, 0x24);
		NVGcolor borderColor = nvgRGB(0x10, 0x10, 0x10);
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, 0.0, 0.0, box.size.x, box.size.y, 5.0);
		nvgFillColor(args.vg, backgroundColor);
		nvgFill(args.vg);
		nvgStrokeWidth(args.vg, 1.5);
		nvgStrokeColor(args.vg, borderColor);
		nvgStroke(args.vg);
		if (*lit == true){
			nvgBeginPath(args.vg);
			nvgRoundedRect(args.vg, 4.0, 4.0, box.size.x - 8.0, box.size.y - 8.0, 4.0);
			nvgFillColor(args.vg, nvgRGB(0xff, 0xf4, 0x00));
			nvgFill(args.vg);
		}
	}
};
