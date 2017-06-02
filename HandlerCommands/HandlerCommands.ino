/**
   Constats for return after handler command
*/
const String HELP_COMMAND = "Hi, list commands:\nblink - try :) \nversion - view version handler";
const String VERSION_COMMAND = "Version handler: 0.1";
const String UNDEFINED_COMMAND = "Undefined command «";


/**

*/
String commands[20];
int countCommands = 0;

bool isMessage;
String message[20];
int countSpace = 0;


void setup() {
  isMessage = false;
  pinMode(13, 1);
  Serial.begin(9600);
  registerCommand("help");
  registerCommand("blink");
  registerCommand("version");

}


void registerCommand(String name) {
  if (getIDCommand(name) == -1) {
    commands[countCommands] = name;
    countCommands++;
    Serial.println("Register command: " + name);
  } else {
    Serial.println("This " + name + " already registered");
  }
}


int getIDCommand(String name) {
  for (int i = 0; i < countCommands; i++) {
    if (commands[i].equalsIgnoreCase(name)) return i;
  }
  return -1;
}

void printWritedCommand() {
  Serial.print("/:");
  for (int i = 0; i <= countSpace; i++) {
    Serial.print(message[i] + " ");
  }
  Serial.println("");
}


void hablerCommands() {
  printWritedCommand();
  switch (getIDCommand(message[0])) {
    //Command help
    case 0: {
        Serial.println(HELP_COMMAND);
      }
      break;
    case 1: {
      if (message[1]=="") message[1]="1";
       for (int i=0;i<message[1].toInt();i++){
        digitalWrite(13,1);
         delay(100);
        digitalWrite(13,0);
        delay(50);
       }
       Serial.println("I blinked");
      }
      break;
    case 2: {
        Serial.println(VERSION_COMMAND);
      }
      break;
    default: Serial.println(UNDEFINED_COMMAND + message[0] + "»");
  }
}
/**
   Clean bufer Message
*/
void cleanBuf() {
  for (int i = 0; i <= countSpace; i++) {
    message[i] = "";
  }
  countSpace = 0;
}

void loop() {
  if (Serial.available() > 0) {
    isMessage = true;
    byte codeLetter = Serial.read();
    if (codeLetter == 32) {
      countSpace++;
    } else {
      message[countSpace] = message[countSpace] + char(codeLetter);
    }
  } else if (isMessage && Serial.available() <= 0) {
    isMessage = false;
    hablerCommands();
    cleanBuf();
  }
  delay(100);
}
