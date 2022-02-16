namespace scalar_110
{

struct Track
{
  bool steps[NUMBER_OF_STEPS] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
  unsigned int playback_position = 0;
  Engine *engine;
  StepParams step_parameters[NUMBER_OF_STEPS];

  void step()
  {
    playback_position = (playback_position + 1) % NUMBER_OF_STEPS;

    if (steps[playback_position])
    {
      engine->trigger();
    }
  }

  unsigned int getPosition()
  {
    return(playback_position);
  }

  void setParameters(unsigned int selected_step, StepParams *new_parameters)
  {
    for(unsigned int i=0; i<NUMBER_OF_PARAMETERS; i++)
    {
      this->step_parameters[selected_step].p[i] = new_parameters->p[i];
    }
  }

  void setPosition(unsigned int playback_position)
  {
    if(playback_position < NUMBER_OF_STEPS)
    {
      this->playback_position = playback_position;
    }
  }

  void toggleStep(unsigned int i)
  {
    steps[i] ^= true;
  }

  bool getValue(unsigned int i)
  {
    return(steps[i]);
  }

  void reset()
  {
    playback_position = 0;
  }

  void setEngine(Engine *selected_engine)
  {
    if(engine != NULL) delete engine;
    engine = selected_engine;
  }

  std::pair<float, float> process()
  {
    float left_output;
    float right_output;

    std::tie(left_output, right_output) = this->engine->process(&step_parameters[this->playback_position]);
    return { left_output, right_output };
  }

};

}
