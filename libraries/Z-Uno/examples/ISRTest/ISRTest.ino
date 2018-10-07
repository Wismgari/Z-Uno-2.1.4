// LED pin number
#define LED_PIN 13

ZUNO_SETUP_ISR_INT0(int0_handler);
ZUNO_SETUP_ISR_INT1(int1_handler);
ZUNO_SETUP_ISR_ZEROX(int_zeroX_handler);
ZUNO_SETUP_ISR_GPTIMER(gpt_handler);
ZUNO_SETUP_ISR_1MSTIMER(m10ms_handler);


unsigned long g_count_int0 = 0;
unsigned long g_count_int1 = 0;
unsigned long g_count_gpt  = 0;
unsigned long g_count_10ms  = 0;
unsigned long g_count_zerox  = 0;


// For some cases use UART (Serial0/Serial1)
// It's a most comfortable way for debugging
// By default we use built-in USB CDC

#define MY_SERIAL Serial

void m10ms_handler()
{
	g_count_10ms++;
}
void int0_handler()
{
	g_count_int0++;
 
}
void int1_handler()
{
	g_count_int1++;
  digitalToggle(10);
}

void int_zeroX_handler()
{
	g_count_zerox++;
	
}

void gpt_handler()
{
	g_count_gpt++;
  digitalToggle(9);


	//zunoGPTSet(4000);
  //zunoGPTEnable(1); 
}
void setup() {
  pinMode(LED_PIN, OUTPUT);      // set LED pin as output
  pinMode(9, OUTPUT);      // set LED pin as output
  pinMode(10, OUTPUT);      // set LED pin as output
  
  zunoExtIntMode(ZUNO_EXT_INT0, FALLING);
  zunoExtIntMode(ZUNO_EXT_INT1, RISING);
  zunoExtIntMode(ZUNO_EXT_ZEROX, FALLING);
  
  MY_SERIAL.begin(115200);
  MY_SERIAL.println("Sketch is starting...");
  zunoGPTInit(ZUNO_GPT_SCALE1024|ZUNO_GPT_CYCLIC);	
  zunoGPTSet(65000);
  zunoGPTEnable(1); 
}

void loop() {

  MY_SERIAL.print("millis:");
  MY_SERIAL.println(millis());
  MY_SERIAL.print("ZeroX:");
  MY_SERIAL.println(g_count_zerox);
  MY_SERIAL.print("INT0:");
  MY_SERIAL.println(g_count_int0);
  MY_SERIAL.print("INT1:");
  MY_SERIAL.println(g_count_int1);
  MY_SERIAL.print("1MS:");
  MY_SERIAL.println(g_count_10ms);
  MY_SERIAL.print("GPT:");
  MY_SERIAL.println(g_count_gpt);
  
  digitalWrite(LED_PIN, HIGH);   // turn LED on
  delay(1000);                   // wait for 1 second
  digitalWrite(LED_PIN, LOW);    // turn LED off
  delay(1000);                  // wait for 1 second


}
