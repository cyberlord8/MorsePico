/*

MorseUNO

Morse Code Sketch - Copyright Timothy Millea 2022 - Released under Creative Commons Attribution 4.0 International License

Takes a String variable and flashes on board led and buzzes passive speaker in morse code

INSTRUCTIONS
1. Open Serial Monitor console
2. Make sure New Line is selected a line termination
3. Enter sentence to convert to morse code
4. Press the enter key

Built-in LED will flash morse code and by hooking a buzzer to pin 12 will sound in morse code.
Adding a relay to pin 12 and connecting the relay contacts to a transmitter key jack, the radio will transmit morse code.

*/

//define variables
// int morseLED = 13;  //GIO LED pin
int morseLED = LED_BUILTIN;  //onboard LED
int morseSND = 12;  //pin for speaker
int WPM = 25;       //default 13 words per minute
int multiplier = 1200 / WPM;
int delayInterSpace = 1 * multiplier;
int delayDIT = 1 * multiplier;
int delayDAH = 3 * multiplier;
int delayCharSpacing = 3 * multiplier;
int delayWordSpacing = 7 * multiplier;
bool stringComplete = false;
String inputString;  // a string to hold incoming data

void setup() {
  // put your setup code here, to run once:
  pinMode(morseSND, OUTPUT);  //speaker goes on this pin
  pinMode(morseLED, OUTPUT);  //onboard LED
  Serial.begin(9600);

  Serial.println();
  Serial.println();
  Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  Serial.println("                   MorsePICO");
  Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  Serial.println("~ Command mode");
  Serial.println("Current commands:");
  Serial.println("~WPM - lists current or sets new WPM speed (~WPM or ~WPM 25)");
  Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  Serial.print("Current WPM: ");
  Serial.println(WPM);
  flashSentence("MorsePICO");
  Serial.println();
  Serial.println("Ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (stringComplete) {
    Serial.println("");
    Serial.println(inputString);
    if (inputString.startsWith("~")) {
      //this is a command
      inputString.toUpperCase();
      inputString.remove(0, 1);
      if (inputString.startsWith("WPM")) {
        inputString.remove(0, 4);
        inputString.trim();
        if (inputString.toInt() == 0) {
          Serial.print("Current WPM: ");
          Serial.println(WPM);
          return;
        }
        WPM = inputString.toInt();
        Serial.print("Set WPM to: ");
        Serial.println(WPM);
        multiplier = 1200 / WPM;
        delayInterSpace = 1 * multiplier;
        delayDIT = 1 * multiplier;
        delayDAH = 3 * multiplier;
        delayCharSpacing = 3 * multiplier;
        delayWordSpacing = 7 * multiplier;
      }
    } else {
      flashSentence(inputString);
      Serial.println("");
    }
    inputString = "";
    stringComplete = false;
  }  //if read serial console complete
}  //loop()

void flashLetter(char letter) {
  //this isn't elegant but it gets the job done
  Serial.print(letter);
  if (letter == 'A') {
    flashDIT();
    flashDAH();
  } else if (letter == 'B') {
    flashDAH();
    flashDIT();
    flashDIT();
    flashDIT();
  } else if (letter == 'C') {
    flashDAH();
    flashDIT();
    flashDAH();
    flashDIT();
  } else if (letter == 'D') {
    flashDAH();
    flashDIT();
    flashDIT();
  } else if (letter == 'E') {
    flashDIT();
  } else if (letter == 'F') {
    flashDIT();
    flashDIT();
    flashDAH();
    flashDIT();
  } else if (letter == 'G') {
    flashDAH();
    flashDAH();
    flashDIT();
  } else if (letter == 'H') {
    flashDIT();
    flashDIT();
    flashDIT();
    flashDIT();
  } else if (letter == 'I') {
    flashDIT();
    flashDIT();
  } else if (letter == 'J') {
    flashDIT();
    flashDAH();
    flashDAH();
    flashDAH();
  } else if (letter == 'K') {
    flashDAH();
    flashDIT();
    flashDAH();
  } else if (letter == 'L') {
    flashDIT();
    flashDAH();
    flashDIT();
    flashDIT();
  } else if (letter == 'M') {
    flashDAH();
    flashDAH();
  } else if (letter == 'N') {
    flashDAH();
    flashDIT();
  } else if (letter == 'O') {
    flashDAH();
    flashDAH();
    flashDAH();
  } else if (letter == 'P') {
    flashDIT();
    flashDAH();
    flashDAH();
    flashDIT();
  } else if (letter == 'Q') {
    flashDAH();
    flashDAH();
    flashDIT();
    flashDAH();
  } else if (letter == 'R') {
    flashDIT();
    flashDAH();
    flashDIT();
  } else if (letter == 'S') {
    flashDIT();
    flashDIT();
    flashDIT();
  } else if (letter == 'T') {
    flashDAH();
  } else if (letter == 'U') {
    flashDIT();
    flashDIT();
    flashDAH();
  } else if (letter == 'V') {
    flashDIT();
    flashDIT();
    flashDIT();
    flashDAH();
  } else if (letter == 'W') {
    flashDIT();
    flashDAH();
    flashDAH();
  } else if (letter == 'X') {
    flashDAH();
    flashDIT();
    flashDIT();
    flashDAH();
  } else if (letter == 'Y') {
    flashDAH();
    flashDIT();
    flashDAH();
    flashDAH();
  } else if (letter == 'Z') {
    flashDAH();
    flashDAH();
    flashDIT();
    flashDIT();
  }
  //numeral characters
  else if (letter == '0') {
    flashDAH();
    flashDAH();
    flashDAH();
    flashDAH();
    flashDAH();
  } else if (letter == '1') {
    flashDIT();
    flashDAH();
    flashDAH();
    flashDAH();
    flashDAH();
  } else if (letter == '2') {
    flashDIT();
    flashDIT();
    flashDAH();
    flashDAH();
    flashDAH();
  } else if (letter == '3') {
    flashDIT();
    flashDIT();
    flashDIT();
    flashDAH();
    flashDAH();
  } else if (letter == '4') {
    flashDIT();
    flashDIT();
    flashDIT();
    flashDIT();
    flashDAH();
  } else if (letter == '5') {
    flashDIT();
    flashDIT();
    flashDIT();
    flashDIT();
    flashDIT();
  } else if (letter == '6') {
    flashDAH();
    flashDIT();
    flashDIT();
    flashDIT();
    flashDIT();
  } else if (letter == '7') {
    flashDAH();
    flashDAH();
    flashDIT();
    flashDIT();
    flashDIT();
  } else if (letter == '8') {
    flashDAH();
    flashDAH();
    flashDAH();
    flashDIT();
    flashDIT();
  } else if (letter == '9') {
    flashDAH();
    flashDAH();
    flashDAH();
    flashDAH();
    flashDIT();
  }
  //punctuation characters
  else if (letter == '$') {
    flashDIT();
    flashDIT();
    flashDIT();
    flashDAH();
    flashDIT();
    flashDIT();
    flashDAH();
  } else if (letter == '+') {
    flashDIT();
    flashDAH();
    flashDIT();
    flashDAH();
    flashDIT();
  } else if (letter == ',') {
    flashDAH();
    flashDAH();
    flashDIT();
    flashDIT();
    flashDAH();
    flashDAH();
  } else if (letter == '-') {
    flashDAH();
    flashDIT();
    flashDIT();
    flashDIT();
    flashDIT();
    flashDAH();
  } else if (letter == '.') {
    flashDIT();
    flashDAH();
    flashDIT();
    flashDAH();
    flashDIT();
    flashDAH();
  } else if (letter == '/') {
    flashDAH();
    flashDIT();
    flashDIT();
    flashDAH();
    flashDIT();
  } else if (letter == ':') {
    flashDAH();
    flashDAH();
    flashDAH();
    flashDIT();
    flashDIT();
    flashDIT();
  } else if (letter == ';') {
    flashDAH();
    flashDIT();
    flashDAH();
    flashDIT();
    flashDAH();
    flashDIT();
  } else if (letter == '=') {
    flashDAH();
    flashDIT();
    flashDIT();
    flashDIT();
    flashDAH();
  } else if (letter == '?') {
    flashDIT();
    flashDIT();
    flashDAH();
    flashDAH();
    flashDIT();
    flashDIT();
  } else if (letter == '@') {
    flashDIT();
    flashDAH();
    flashDAH();
    flashDIT();
    flashDAH();
    flashDIT();
  } else if (letter == '!') {
    flashDAH();
    flashDAH();
    flashDAH();
    flashDIT();
  }


}  //flashLetter()

void flashWord(String word) {
  //break word into chars
  for (int i = 0; i < word.length(); i++) {
    flashLetter(word.charAt(i));
    delay(delayWordSpacing - delayCharSpacing);
  }  //for each character in word
}  //flashWord()

void flashSentence(String text) {
  int splitCount = countSplitCharacters(text, ' ');
  String wordArray[splitCount + 1];
  int index1 = 0;
  int index2 = 0;
  for (int i = 0; i < splitCount + 1; i++) {
    //find the start and end index of the words by finding the space character
    if (index1 > 0) {
      index1 = text.indexOf(' ', index2);
    }
    index2 = text.indexOf(' ', index1 + 1);
    if (index2 < 0) {
      index2 = text.length();
    }
    //parse the word from the string
    String word = text.substring(index1++, index2);
    word.toUpperCase();   //convert to uppercase
    wordArray[i] = word;  //add word to array
  }                       //for each word in sentance
  for (int i = 0; i < splitCount + 1; i++) {
    flashWord(wordArray[i]);
  }  //for each word in array
  delay(delayWordSpacing);
}  //flashSentence()

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    }  //if we have a newline then we're done reading serial for now
    if (stringComplete == false) {
      inputString += inChar;
    }  //if no newline then append the char to the string
  }    //while stuff ready to read from serial console
}  //serialEvent()

int countSplitCharacters(String text, char splitChar) {
  int returnValue = 0;
  int index = 0;
  while (index > -1) {
    index = text.indexOf(splitChar, index + 1);
    if (index > -1) returnValue++;
  }
  return returnValue;
}  //countSplitCharacters

void flashDIT() {
  digitalWrite(morseSND, HIGH);
  digitalWrite(morseLED, HIGH);
  delay(delayDIT);
  digitalWrite(morseSND, LOW);
  digitalWrite(morseLED, LOW);
  delay(delayInterSpace);
}  //flashDIT()

void flashDAH() {
  digitalWrite(morseSND, HIGH);
  digitalWrite(morseLED, HIGH);
  delay(delayDAH);
  digitalWrite(morseSND, LOW);
  digitalWrite(morseLED, LOW);
  delay(delayInterSpace);
}  //flashDAH()
