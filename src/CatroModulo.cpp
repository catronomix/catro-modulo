#include "CatroModulo.hpp"

Plugin *plugin;


void init(Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	// Add all Models defined throughout the plugin
	p->addModel(modelCM1Module);
	p->addModel(modelCM2Module);
	p->addModel(modelCM3Module);
	p->addModel(modelCM4Module);
	p->addModel(modelCM5Module);
	p->addModel(modelCM6Module);
	p->addModel(modelCM7Module);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}

void CM_Slider_big_red::onDragMove(EventDragMove& e) {
    std::swap(e.mouseRel.x, e.mouseRel.y);
    e.mouseRel.y = -e.mouseRel.y;
    Knob::onDragMove(e);
}