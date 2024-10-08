# FreeRTOS Blinky with Multiple Functions of Different Priorities

## Overview

This project demonstrates the use of FreeRTOS to create a blinky LED application where multiple tasks with different priorities control the blinking of an LED. The FreeRTOS scheduler is employed to manage these tasks, allowing the LED to blink at different rates based on the assigned priorities. This project showcases the multitasking capabilities of FreeRTOS on microcontroller platforms.

## Functionality

- **Task 1**: Blinks the LED with a delay of 500 milliseconds.
- **Task 2**: Blinks the LED with a delay of 50 milliseconds, demonstrating a higher priority than Task 1.

### Behavior
- The LED will blink with a slower frequency (every 500 ms) when Task 1 is running.
- The LED will blink rapidly (every 50 ms) when Task 2 is scheduled by FreeRTOS, allowing users to observe how tasks with different priorities interact.

## Hardware Setup

1. **Components Required**:
   - **Microcontroller Board**: (e.g., ESP32, Arduino)
   - **LED**: Any standard LED connected to a GPIO pin (or use the built-in LED on the board).

2. **Wiring**:
   - Connect the LED's anode (long leg) to the designated GPIO pin (e.g., LED_BUILTIN) on the microcontroller.
   - Connect the cathode (short leg) to ground.

## Code Explanation

### FreeRTOS Configuration
- The project uses FreeRTOS for multitasking, creating two tasks with different priorities.
- Depending on the configuration (`CONFIG_FREERTOS_UNICORE`), tasks are pinned to either CPU core 0 or core 1.

### Task Functions
- **`toggleLED`**: This function controls the LED's blinking with a delay of 500 milliseconds.
  
  ```cpp
  void toggleLED(void *parameter) {
    while(1){
      digitalWrite(led_pin, HIGH);
      vTaskDelay(500/portTICK_PERIOD_MS);
      digitalWrite(led_pin, LOW);
      vTaskDelay(500/portTICK_PERIOD_MS);
    }
  }
  ```

- **`toggleLED2`**: This function controls a rapid blink with a delay of 50 milliseconds.
  
  ```cpp
  void toggleLED2(void *parameter) {
    while(1){
      digitalWrite(led_pin, HIGH);
      vTaskDelay(50/portTICK_PERIOD_MS);
      digitalWrite(led_pin, LOW);
      vTaskDelay(50/portTICK_PERIOD_MS);
    }
  }
  ```

### Task Creation
- The tasks are created in the `setup()` function using `xTaskCreatePinnedToCore`, assigning priorities accordingly.
  
```cpp
void setup() {
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(
                toggleLED,        //function to be called
                "Toggle LED",     //task name
                1024,             //stack size
                NULL,             //parameter to pass to function
                1,                //Task priority
                NULL,
                app_cpu);

   xTaskCreatePinnedToCore(
                toggleLED2,        //function to be called
                "Toggle LED2",     //task name
                1024,             //stack size
                NULL,             //parameter to pass to function
                2,                //Task priority
                NULL,
                app_cpu);
}
```

### Loop Function
- The `loop()` function is empty as the tasks run indefinitely in their respective while loops.

```cpp
void loop() {
  
}
```

## Conclusion

This project effectively demonstrates the principles of task scheduling and priority management in FreeRTOS. Users can modify the delay values and task priorities to observe how these changes affect the LED blinking behavior, enhancing their understanding of real-time operating systems.
