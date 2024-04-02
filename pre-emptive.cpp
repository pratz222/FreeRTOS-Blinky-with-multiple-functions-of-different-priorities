/* PROGRAM: pre-emptive scheduling of 2 tasks on ESP32 */ 


#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu =0;
#else
static const BaseType_t app_cpu =1;
#endif

const char msg[]= "Its all about the mindset";

static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;

void Task1(void *parameter) {
  // TASK iss to count number of chracterrs in a string and then print
  int msg_len = strlen(msg);

  while(1) {
    Serial.println();
    for (int i=0;i<msg_len; i++) {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}


void Task2(void *parameter) {
  /*T0ask is to print * at regular intervals to show that 
    it preempts Task1 based on priority */
    
  while(1){
    Serial.print('*');
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}


void setup() {

  Serial.begin(300);

  //wait for some time
  vTaskDelay(1000/portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("FreeRTOS Pre-emptive Scheduling of Tasks");

  //Print self priority
  Serial.print("Setup & loop Task running on Core");
  Serial.print(xPortGetCoreID());
  Serial.print("with priority");
  Serial.println(uxTaskPriorityGet(NULL));

  //Task to RUN Forever
  xTaskCreatePinnedToCore(
                Task1,
                "Task-1",
                1024,
                NULL,
                1,
                &task_1,
                app_cpu);
                
   xTaskCreatePinnedToCore(
                Task2,
                "Task-2",
                1024,
                NULL,
                2,
                &task_2,
                app_cpu);

}

void loop() {

    //suspend higher priority task for some intervals
    for(int i=0;i<3;i++) {
      vTaskSuspend(task_2);
      vTaskDelay(2000/portTICK_PERIOD_MS);
      vTaskResume(task_2);
      vTaskDelay(2000/portTICK_PERIOD_MS);
    }

     //Delete lower priority Task
     if(task_1 != NULL) {
      vTaskDelete(task_1);
      task_1 = NULL;
     }
}
