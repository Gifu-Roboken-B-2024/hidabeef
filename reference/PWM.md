# Hidabeef Library: PWM

## インスタンスの定義
``` cpp
#include "hidabeef/hidabeef.hpp"
#include "tim.h"

using namespace hidabeef;

PWM pwm_1(&htim1, TIM_CHANNEL_1, 0.0f);
```

`PWM class`を使用してPWMインスタンスを作成します。
事前にCubeMXなどで`PWM Generation`等を設定しておいてください。

引数1: timer
引数2: チャンネル
引数3: 初期値

## 初期化と開始
```cpp
pwm_1.init()
pwm_1.start()
```
`init()`関数を使用することで初期化、`start()`関数を使用することで開始できます。
`init()`する前に`start()`した場合、`hidabeef::PWM_Status::NotInitialized`が返されます。
