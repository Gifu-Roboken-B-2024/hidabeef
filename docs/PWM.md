# hidabeef Library: PWM API Document


## PWM class

``` cpp
hidabeef::PWM pwm_instance(TIM_HandleTypeDef *htim, std::uint32_t channel, std::uint32_t default_compare);
```
This method can create `PWM` instance.  

@param TIM_HandleTypeDef *htim  
  timer reference that were provided by "Src/tim.h"

@param std::uint32_t channel  
  select a channel like `TIM_CHANNEL_1`

@param std::uint32_t default_compare  
  default compare (outputs when `pwm_instance.start()` were executed)

``` cpp
hidabeef::PWM_Status hidabeef::PWM::Status init();
```

```cpp
hidabeef::PWM_Status hidabeef::PWM::start();
```

```cpp
hidabeef::PWM_Status hidabeef::PWM::set(std::uint32_t compare);
```
