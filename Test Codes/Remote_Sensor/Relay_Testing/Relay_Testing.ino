#include <MCP23017.h>
#define MCP23017_I2C_ADDRESS 0x22  // I2C address of the MCP23017 IC

const uint8_t Switch1 = 9;   // GPB1 (2) of the MCP23017
const uint8_t Switch2 = 10;  // GPB2 (3) of the MCP23017


int sda = 18;
int scl = 17;

const uint8_t MCP23017_INTB = 9;  // connected to MCP23017 INTB (19) pin
volatile bool switchDidChange = false;  // change status of MCP23017 input pins


MCP23017 mcp23017 = MCP23017(MCP23017_I2C_ADDRESS);  // instance of the connected MCP23017 IC
void setup() {
  Serial.begin(9600);
   Wire.begin(sda,scl);     // initialize I2C serial bus
   mcp23017.init();  // initialize MCP23017 IC
   // Configure MCP23017 I/O pins
   configurePinsWithPinMode();  // familiar pinMode() style
   // Reset MCP23017 ports
   mcp23017.writeRegister(MCP23017Register::GPIO_A, 0x00);
   mcp23017.writeRegister(MCP23017Register::GPIO_B, 0x00);

   configureInterrupts();
}
void loop() {
   readAndWriteWithDigitalReadAndDigitalWrite();
}
void configurePinsWithPinMode() {
   // Configure output pins
  

   mcp23017.pinMode(Switch1, OUTPUT);
   mcp23017.pinMode(Switch2, OUTPUT);

}
void readAndWriteWithDigitalReadAndDigitalWrite() {
   // Read and write individual inputs and outputs
   mcp23017.digitalWrite(Switch1, HIGH);
   mcp23017.digitalWrite(Switch2, HIGH);
   delay(3000);
   mcp23017.digitalWrite(Switch1, LOW);
   mcp23017.digitalWrite(Switch2, LOW);
   

}




void configureInterrupts() {
   // Configure MCP23017 interrupts
   mcp23017.interruptMode(MCP23017InterruptMode::Separated);  // INTA and INTB act independently
   mcp23017.interrupt(MCP23017Port::B, CHANGE);  // trigger an interrupt when an input pin CHANGE is detected on PORTB
   // Set up interrupt connection and attach interrupt service routine
   mcp23017.clearInterrupts();  // reset interrupt system
   pinMode(MCP23017_INTB, INPUT_PULLUP);  // utilize microprocessor's internal pull-up resistor
   attachInterrupt(digitalPinToInterrupt(MCP23017_INTB), mcp23017ChangeDetectedOnPortB, FALLING);  // INTB is active LOW
}

void mcp23017ChangeDetectedOnPortB() {
  Serial.print("SLOTA TYPE 1 = ");
   switchDidChange = true;
}

void readAndWritePortOnInputChange() {
   if (switchDidChange) {
      delay(100);  // allow time for MCP23017 to set interrupt registers
       // copy values from PORTB (switches) to PORTA (LEDs)
      mcp23017.clearInterrupts();  // clear interrupt
      switchDidChange = false;
   }
}
