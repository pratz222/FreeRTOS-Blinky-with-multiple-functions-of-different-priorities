#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu =0;
#else
static const BaseType_t app_cpu =1;
#endif

static const int led_pin = LED_BUILTIN;

void toggleLED(void *parameter) {
  while(1){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}   

void toggleLED2(void *parameter) {
  while(1){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(50/portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(50/portTICK_PERIOD_MS);
  }
}

void setup() {
  pinMode(led_pin, OUTPUT);

   //Task to RUN Forever
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

void loop() {

}
