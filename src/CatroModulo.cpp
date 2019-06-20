#include "CatroModulo.hpp"

Plugin *pluginInstance;


void init(Plugin *p) {
	pluginInstance = p;

	// Add all Models defined throughout the pluginInstance
	p->addModel(modelCM1Module);
	p->addModel(modelCM2Module);
	p->addModel(modelCM3Module);
	p->addModel(modelCM4Module);
	p->addModel(modelCM5Module);
	p->addModel(modelCM6Module);
	p->addModel(modelCM7Module);
	p->addModel(modelCM8Module);
	p->addModel(modelCM9Module);
	p->addModel(modelCM10Module);

	// Any other pluginInstance initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}

//horizontal slider
// void CM_Slider_big_red::onDragMove(const event::DragMove &e) {
//     //std::swap(e.mouseDelta.x , e.mouseDelta.y);
//     //e.mouseDelta.y = -e.mouseDelta.y;
// 	//e.mouseDelta = math::Vec(0 - e.mouseDelta.y, e.mouseDelta.x);
//     Knob::onDragMove(e);
// }