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

    for(unsigned int i=0; i<NUMBER_OF_STEPS; i++)
    {
      addParam(createParamCentered<LEDButton>(mm2px(Vec(button_group_x + (button_spacing * i), button_group_y + 10)), module, Scalar110::STEP_SELECT_BUTTONS + i));
      addChild(createLightCentered<MediumLight<GreenLight>>(mm2px(Vec(button_group_x + (button_spacing * i), button_group_y + 10)), module, Scalar110::STEP_SELECT_BUTTON_LIGHTS + i));

      addParam(createLightParamCentered<VCVLightBezel<>>(mm2px(Vec(button_group_x + (button_spacing * i), button_group_y)), module, Scalar110::DRUM_PADS + i, Scalar110::DRUM_PAD_LIGHTS + i));
      addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(button_group_x + (button_spacing * i), button_group_y - 6)), module, Scalar110::STEP_LOCATION_LIGHTS + i));
    }

    addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(50,50)), module, Scalar110::TRACK_SELECT_KNOB));
    addParam(createParamCentered<EngineKnob>(mm2px(Vec(50,80)), module, Scalar110::ENGINE_SELECT_KNOB));


    float offset = 120;

    for(unsigned int i=0; i<4; i++)
    {
      ParameterKnob* parameter_knob = createParamCentered<ParameterKnob>(mm2px(Vec(offset + (i * 20),50)), module, Scalar110::ENGINE_PARAMS + i);
  		parameter_knob->parameter_number = i;
  		addParam(parameter_knob);
    }

    for(unsigned int i=4; i<8; i++)
    {
      ParameterKnob* parameter_knob = createParamCentered<ParameterKnob>(mm2px(Vec(offset + ((i-4) * 20),70)), module, Scalar110::ENGINE_PARAMS + i);
  		parameter_knob->parameter_number = i;
  		addParam(parameter_knob);
    }

    /*
    ParameterKnob* parameter_knob_1 = createParamCentered<ParameterKnob>(mm2px(Vec(offset + 20,50)), module, Scalar110::ENGINE_PARAMS + 1);
		parameter_knob_1->parameter_number = 1;
		addParam(parameter_knob_1);

    addParam(createParamCentered<ParameterKnob>(mm2px(Vec(offset,50)), module, Scalar110::ENGINE_PARAMS));
    addParam(createParamCentered<ParameterKnob>(mm2px(Vec(offset + 20,50)), module, Scalar110::ENGINE_PARAMS + 1));
    addParam(createParamCentered<ParameterKnob>(mm2px(Vec(offset + 40,50)), module, Scalar110::ENGINE_PARAMS + 2));
    addParam(createParamCentered<ParameterKnob>(mm2px(Vec(offset + 60,50)), module, Scalar110::ENGINE_PARAMS + 3));
    addParam(createParamCentered<ParameterKnob>(mm2px(Vec(offset,70)), module, Scalar110::ENGINE_PARAMS + 4));
    addParam(createParamCentered<ParameterKnob>(mm2px(Vec(offset + 20,70)), module, Scalar110::ENGINE_PARAMS + 5));
    addParam(createParamCentered<ParameterKnob>(mm2px(Vec(offset + 40,70)), module, Scalar110::ENGINE_PARAMS + 6));
    addParam(createParamCentered<ParameterKnob>(mm2px(Vec(offset + 60,70)), module, Scalar110::ENGINE_PARAMS + 7));
    */
    addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(210, 114.702)), module, Scalar110::AUDIO_OUTPUT_LEFT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(220, 114.702)), module, Scalar110::AUDIO_OUTPUT_RIGHT));

    for(unsigned int i=0; i<NUMBER_OF_PARAMETERS; i++)
    {
      float x_position = 110.2 + ((i%4) * 20);
      float y_position = 37 + ((i/4) * 20);

      LabelDisplay *label_display = new LabelDisplay(i);
      label_display->box.pos = mm2px(Vec(x_position, y_position));;
      label_display->module = module;
      addChild(label_display);
    }


      LCDWidget *lcd_widget = new LCDWidget(module);
      // lcd_widget->module = module;
      lcd_widget->box.pos = mm2px(Vec(LCD_DISPLAY_X, LCD_DISPLAY_Y));
      addChild(lcd_widget);

      /*
    FileSelectWidget *file_select_widget = new FileSelectWidget();
    file_select_widget->module = module;
    file_select_widget->box.pos = mm2px(Vec(LCD_DISPLAY_X + 2, LCD_DISPLAY_Y + 5));
    addChild(file_select_widget);
    */

  }

  void appendContextMenu(Menu *menu) override
  {
    Scalar110 *module = dynamic_cast<Scalar110*>(this->module);
    assert(module);

    FolderSelect *folder_select = new FolderSelect();
    folder_select->text = "Load samples from folder";
    folder_select->module = module;
    menu->addChild(folder_select);
  }

};
