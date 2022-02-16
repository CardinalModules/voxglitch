#include <componentlibrary.hpp>

struct Scalar110Widget : ModuleWidget
{
  Scalar110Widget(Scalar110* module)
  {
    setModule(module);
    setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/scalar110_front_panel.svg")));

    float button_group_x  = 10.0;
    float button_group_y  = 100.0;
    float button_spacing  = 10.0;

    addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10, 40)), module, Scalar110::STEP_INPUT));

    // Drum buttons
    for(unsigned int i=0; i<NUMBER_OF_STEPS; i++)
    {
      addParam(createParamCentered<LEDButton>(mm2px(Vec(button_group_x + (button_spacing * i), button_group_y)), module, Scalar110::DRUM_BUTTONS + i));
      addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(button_group_x + (button_spacing * i), button_group_y)), module, Scalar110::DRUM_BUTTON_LIGHTS + i));
      addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(button_group_x + (button_spacing * i), button_group_y - 6)), module, Scalar110::STEP_LOCATION_LIGHTS + i));
    }

    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(50,50)), module, Scalar110::TRACK_SELECT_KNOB));

    addParam(createParamCentered<Trimpot>(mm2px(Vec(100,50)), module, Scalar110::ENGINE_PARAMS));
    addParam(createParamCentered<Trimpot>(mm2px(Vec(120,50)), module, Scalar110::ENGINE_PARAMS + 1));
    addParam(createParamCentered<Trimpot>(mm2px(Vec(140,50)), module, Scalar110::ENGINE_PARAMS + 2));

  }

  void appendContextMenu(Menu *menu) override
  {
    Scalar110 *module = dynamic_cast<Scalar110*>(this->module);
    assert(module);
  }


};
