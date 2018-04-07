#include <SerialCommand.h>

#define PWM1 13
#define DIR11 12
#define DIR12 11

#define PWM2 10
#define DIR21 9
#define DIR22 8

String in = "";
int v1 = 0, v2 = 0 ;
bool d1 = 0, d2 =0, i1 = 0, i2 =0, brk=0;


SerialCommand sCmd;     // The SerialCommand object

void setup()
{
	pinMode(PWM1, OUTPUT);

	pinMode(DIR11, OUTPUT);
	pinMode(DIR12, OUTPUT);

	pinMode(PWM2, OUTPUT);	

	pinMode(DIR21, OUTPUT);
	pinMode(DIR22, OUTPUT);

	Serial.begin(115200);

	  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("P",   set_pwm);          // Turns LED on
  sCmd.addCommand("D",   set_dir);         // Turns LED off
  sCmd.addCommand("I",   set_inv);        // Echos the string argument back
  sCmd.addCommand("B",   set_brk);  // Converts two arguments to integers and echos them back
  sCmd.addCommand("help",   help);
  sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched
  Serial.println("Ready");
  Serial.println("");

}

void help() {
	Serial.println("--- Help text ---");
	Serial.println("P X Y	-> set PWM of controller X to Y, from 0 to 100 (%)");
	Serial.println("D X Y	-> set direction of controller X to Y, 1 or 0");
	Serial.println("I X Y	-> invert direction setting of controller X to Y, 0 or 1");
	Serial.println("B	-> Break to ground");
	Serial.println("help	-> Display help text.");
	Serial.println("");
}

void unrecognized() {
	v1 = 0;
	v2 = 0;

	apply();
}

void set_brk() {
	brk = 1;
	v1 = 0;
	v2 = 0;

	apply();
}

void set_pwm() {
	char *arg;
	arg = sCmd.next();

	if(1 == atoi(arg)){
		arg = sCmd.next();
		v1 = map(atoi(arg), 0, 100, 0, 255);
	}
	else if(2 == atoi(arg)) {
		arg = sCmd.next();
		v2 = map(atoi(arg), 0, 100, 0, 255);
	}

	apply();
}

void set_dir() {
	char *arg;
	arg = sCmd.next();

	if(1 == atoi(arg)){
		arg = sCmd.next();
		d1 = atoi(arg);
		if(i1) {
			d1 = !d1;
		}
	}
	else if (2 == atoi(arg)) {
		arg = sCmd.next();
		d2 = atoi(arg);
		if(i2) {
			d2 = !d2;
		}
	}

	apply();
}

void set_inv() {
	char *arg;
	arg = sCmd.next();

	if(1 == atoi(arg)){
		arg = sCmd.next();
		i1 = atoi(arg);
	}
	else if (2 == atoi(arg)) {
		arg = sCmd.next();
		i2 = atoi(arg);
	}

	apply();
}

void apply() {
	Serial.println("P1	D1	I1:");
	Serial.print(v1); Serial.print("	");
	Serial.print(d1); Serial.print("	");
	Serial.println(i1);
	Serial.println(" ");

	Serial.println("P2	D2	I2:");
	Serial.print(v2); Serial.print("	");
	Serial.print(d2); Serial.print("	");
	Serial.println(i2);

	Serial.print("BREAK: ");
	Serial.println(brk);
	Serial.println(" ");
	Serial.println(" ");

	if(!brk){
		digitalWrite(DIR11, d1);
		digitalWrite(DIR12, !d1);

		digitalWrite(DIR21, d2);
		digitalWrite(DIR22, !d2);
	}
	else {
		digitalWrite(DIR11, 0);
		digitalWrite(DIR12, 0);

		digitalWrite(DIR21, 0);
		digitalWrite(DIR22, 0);
		brk = 0;
	}

	analogWrite(PWM1, v1);
	analogWrite(PWM2, v2);	
}

void loop() {

	sCmd.readSerial();
}