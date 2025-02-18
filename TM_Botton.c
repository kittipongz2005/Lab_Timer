#define ADC0_pin 36
hw_timer_t * timer = NULL; /* create a hardware timer */
int led = 32; /* LED pin */

void IRAM_ATTR onTimer(){
  digitalWrite(led, !digitalRead(led));
}

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);  
  /* Use 1st timer of 4 */
  /* 1 tick takes 1/(80MHZ/80) = 1us so we set divider 80 and count up */
  timer = timerBegin(0, 80, true);
  /* Attach onTimer function to our timer */
  timerAttachInterrupt(timer, &onTimer, true);
  /* Set alarm to call onTimer function every second */
  /* Repeat the alarm (third parameter) */
  timerAlarmWrite(timer, 1000000, true);
  /* Start an alarm */
  timerAlarmEnable(timer);
}
// ค่า ADC ที่ได้จากการกดปุ่ม S1 - S5 ได้จากการปรับค่าตามค่าใน Serial Monitor
void loop() {
  int adcValue = analogRead(ADC0_pin);  // อ่านค่าจากขา 36

  Serial.println(adcValue);  // ปริ้นค่าลง Serial Monitor
    if (adcValue >=4021 & adcValue <=4035  ) {  // กดปุ่ม S1
      timerAlarmWrite(timer, 250000, true);  // 2 Hz (กระพริบ 2 ครั้งต่อวินาที)
    } 
    else if (adcValue >=3240 & adcValue <=3260  ) {  // กดปุ่ม S2
      timerAlarmWrite(timer, 100000, true);  // 5 Hz (กระพริบ 5 ครั้งต่อวินาที)
    } 
    else if (adcValue >=2600 & adcValue <=2620  ) {  // กดปุ่ม S3
      timerAlarmWrite(timer, 50000, true); // 10 Hz (กระพริบ 10 ครั้งต่อวินาที)
    } 
    else if (adcValue >=1840 & adcValue <=1860  ) {  // กดปุ่ม S4
      timerAlarmWrite(timer, 20000, true);  // 25 Hz (กระพริบ 25 ครั้งต่อวินาที) 
    } 
    else if (adcValue >=1120 & adcValue <=1160  ) {  // กดปุ่ม S5
      timerAlarmWrite(timer, 16667, true); // 30 Hz (กระพริบ 30 ครั้งต่อวินาที)
    }
    else  {  // ไม่กดปุ่ม
      timerAlarmWrite(timer, 1000000, true);
    }
}