/**
   Constants for return after handler command
*/
const String VERSION_COMMAND = "Version handler: 0.4";
const String UNDEFINED_COMMAND = "Undefined command «";

/**
 * Constants info message
 */
const String READY_SYSTEM="-*-*-*-*-*-*- SYSTEM READY -*-*-*-*-*-*-";
/**
 * Debug mode
 */
int debugMode = 0;
 

bool started = false;
/**

*/
String commands[20];
String commandsDescription[20];
int countCommands = 0;

bool isMessage;
String message [20];
int countSpace = 0;


void debug(String message){
  if (debugMode==1) Serial.println(message);
}

void setup() {
    Serial.begin(9600);
  isMessage = false;
  pinMode(13, 1);
  registerCommand("help","- view all commands");
  registerCommand("blink","<count> - Blink pin 13");
  registerCommand("version","- view version handler");
  registerCommand("picture","");
  registerCommand("print","<messages[]> - print array messages");
  registerCommand("mul","<operand> <operand> - print mul two operands");
  registerCommand("div","");
  if (!started){
    Serial.println(READY_SYSTEM);
    started=true;
  }
}


void registerCommand(String name, String description) {
  if (getIDCommand(name) == -1) {
    commands[countCommands] = name;
    commandsDescription[countCommands] = description;
    countCommands++;
    debug("Register command: " + name);
  } else {
    debug("This " + name + " already registered");
  }
}


int getIDCommand(String name) {
  for (int i = 0; i < countCommands; i++) {
    if (commands[i].equalsIgnoreCase(name)) return i;
  }
  return -1;
}

void printWritedCommand() {
  Serial.print(":/");
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
        for (int i=0;i<countCommands;i++){
          Serial.println(String(i+1)+") "+commands[i]+" "+commandsDescription[i]);
        }
      }
      break;
    case 1: {
        if (message[1] == "") message[1] = "1";
        for (int i = 0; i < message[1].toInt(); i++) {
          digitalWrite(13, 1);
          delay(250);
          digitalWrite(13, 0);
          delay(100);
        }
        Serial.println("I blinked");
      }
      break;
    case 2: {
        Serial.println(VERSION_COMMAND);
      }
      break;
    case 3: {
        /* String text = "";
          String t = "";
          for (int i=0;i<=12;i++){
           text+=" ";
           for (int j=0;j<=1;j++){
             t+="*";
             Serial.print(text+t);
           }

           Serial.println("");
          }
          t="";
          for (int i=12;i>=0;i--){
           text[i-1]="";
           for (int j=1;j>=0;j--){
              t+="*";
             Serial.print(text+t);
           }

           Serial.println("");
          }
          Serial.println("end print");*/
      }
      break;
    case 4: {
        for (int i = 1; i <= countSpace; i++) Serial.print(message[i] + " ");
        Serial.println("");
      }
      break;
    case 5: {
        Serial.println(message[1].toInt()*message[2].toInt());
      }
      break;
    case 6: {
        Serial.println(message[1].toInt() / message[2].toInt());
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
      if (message[countSpace] != "")
        countSpace++;
    } else {
      message[countSpace] = message[countSpace] + char(codeLetter);
    }
  } else if (isMessage && Serial.available() <= 0) {
    isMessage = false;
    hablerCommands();
    cleanBuf();
  }
  delay(3);
}
