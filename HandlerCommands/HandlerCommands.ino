/**
   Constats for return after handler command
*/
const String HELP_COMMAND = "Hi, list commands:\nblink <count> - Blink pin 13 :) \nversion - view version handler\npicture - print PICTURE WOOWOWOWOOW";
const String VERSION_COMMAND = "Version handler: 0.2";
const String UNDEFINED_COMMAND = "Undefined command «";


/**

*/
String commands[20];
int countCommands = 0;

bool isMessage;
String message [20];
int countSpace = 0;


void setup() {
  isMessage = false;
  pinMode(13, 1);
  Serial.begin(9600);
  registerCommand("help");
  registerCommand("blink");
  registerCommand("version");
  registerCommand("picture");
  registerCommand("print");
  registerCommand("mul");
  registerCommand("div");
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
        Serial.println(HELP_COMMAND);
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
      case 5:{
        Serial.println(message[1].toInt()*message[2].toInt());
      }
      break;
       case 6:{
        Serial.println(message[1].toInt()/message[2].toInt());
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
