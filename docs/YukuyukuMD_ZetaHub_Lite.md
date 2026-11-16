# hidabeef Library: PWM API Document


## PWM class

``` cpp
hidabeef::PWM pwm_instance(TIM_HandleTypeDef *htim, std::uint32_t channel, std::uint32_t default_compare);
```

  static constexpr std::size_t kPortCount = 4;

  PWM_Status attach(std::uint8_t port, PWM &forward, PWM &backward, float multiplier);

  YukuyukuMD_ZetaHub_LiteInitResult init();
  YukuyukuMD_ZetaHub_LiteInitResult start();

  PWM_Status set(std::uint8_t port, std::int32_t value);

  struct StatusTypeDef {};
