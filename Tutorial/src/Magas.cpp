#include "Tutorial.hpp"


struct Magas : Module {
	enum ParamIds {
		PITCH1_PARAM,
		PITCH2_PARAM,
		PITCH3_PARAM,
		PITCH4_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		PITCH1_INPUT,
		PITCH2_INPUT,
		PITCH3_INPUT,
		PITCH4_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SINE1_OUTPUT,
		SINE2_OUTPUT,
		SINE3_OUTPUT,
		SINE4_OUTPUT,
		NUM_OUTPUTS
	};

	float phase1 = 0.0;
	float phase2 = 0.0;
	float phase3 = 0.0;
	float phase4 = 0.0;

	Magas() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
	void step() override;

	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - reset, randomize: implements special behavior when user clicks these from the context menu
};


void Magas::step() {
	// Implement a simple sine oscillator
	float deltaTime1 = 1.0 / engineGetSampleRate();
	float deltaTime2 = 1.0 / engineGetSampleRate();
	float deltaTime3 = 1.0 / engineGetSampleRate();
	float deltaTime4 = 1.0 / engineGetSampleRate();

	// Compute the frequency from the pitch parameter and input
	float pitch1 = params[PITCH1_PARAM].value;
	pitch1 += inputs[PITCH1_INPUT].value;
	pitch1 = clampf(pitch1, -4.0, 4.0);
	float freq1 = 440.0 * powf(2.0, pitch1);

	float pitch2 = params[PITCH2_PARAM].value;
	pitch2 += inputs[PITCH2_INPUT].value;
	pitch2 = clampf(pitch2, -4.0, 4.0);
	float freq2 = 440.0 * powf(2.0, pitch2);

	float pitch3 = params[PITCH3_PARAM].value;
	pitch3 += inputs[PITCH3_INPUT].value;
	pitch3 = clampf(pitch3, -4.0, 4.0);
	float freq3 = 440.0 * powf(2.0, pitch3);

	float pitch4 = params[PITCH4_PARAM].value;
	pitch4 += inputs[PITCH4_INPUT].value;
	pitch4 = clampf(pitch4, -4.0, 4.0);
	float freq4 = 440.0 * powf(2.0, pitch4);



	// Accumulate the phase
	phase1 += freq1 * deltaTime1;
	if (phase1 >= 1.0)
		phase1 -= 1.0;

	phase2 += freq2 * deltaTime2;
	if (phase2 >= 1.0)
		phase2 -= 1.0;

	phase3 += freq3 * deltaTime3;
	if (phase3 >= 1.0)
		phase3 -= 1.0;

	phase4 += freq4 * deltaTime4;
	if (phase4 >= 1.0)
		phase4 -= 1.0;

	// Compute the sine output
	float sine1 = sinf(2 * M_PI * phase1);
	outputs[SINE1_OUTPUT].value = 5.0 * sine1;

	float sine2 = sinf(2 * M_PI * phase2);
	outputs[SINE2_OUTPUT].value = 5.0 * sine2;

	float sine3 = sinf(2 * M_PI * phase3);
	outputs[SINE3_OUTPUT].value = 5.0 * sine3;

	float sine4 = sinf(2 * M_PI * phase4);
	outputs[SINE4_OUTPUT].value = 5.0 * sine4;
}


MagasW::MagasW() {
	Magas *module = new Magas();
	setModule(module);
	box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Bg4.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 365)));

	addParam(createParam<PirosPoti>(Vec(28, 20), module, Magas::PITCH1_PARAM, -3.0, 3.0, 0.0));

	addInput(createInput<PJ301MPort>(Vec(10, 65), module, Magas::PITCH1_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(55, 65), module, Magas::SINE1_OUTPUT));


	addParam(createParam<PirosPoti>(Vec(28, 115), module, Magas::PITCH2_PARAM, -3.0, 3.0, 0.0));

	addInput(createInput<PJ301MPort>(Vec(10, 160), module, Magas::PITCH2_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(55, 160), module, Magas::SINE2_OUTPUT));


	addParam(createParam<PirosPoti>(Vec(28, 210), module, Magas::PITCH3_PARAM, -3.0, 3.0, 0.0));

	addInput(createInput<PJ301MPort>(Vec(10, 255), module, Magas::PITCH3_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(55, 255), module, Magas::SINE3_OUTPUT));


	addParam(createParam<PirosPoti>(Vec(28, 305), module, Magas::PITCH4_PARAM, -3.0, 3.0, 0.0));

	addInput(createInput<PJ301MPort>(Vec(10, 350), module, Magas::PITCH4_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(55, 350), module, Magas::SINE4_OUTPUT));

}
