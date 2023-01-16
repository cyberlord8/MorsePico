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
int morseLED = LED_BUILTIN;  //onboard Pico LED
int morseSND = 12;           //pin for speaker
//variables to convert WPM to millisecond timing
int WPM = 25;                //set default words per minute
int multiplier = 1200 / WPM; //multiplier for morse symbol spacing (PARIS method)
int interspaceLength = 1 * multiplier; // spacing for inter morse symbol spacing
int DITLength = 1 * multiplier; //length of a DIT
int DAHLength = 3 * multiplier; //length of a DAH
int charSpacingLength = 3 * multiplier; //spacing between morse symbol groups (characters)
int wordSpacingLength = 7 * multiplier; //spacing between morse symbol groups (words)

bool stringComplete = false;
String inputString;  // a string to hold incoming data

void setup() {
  // put your setup code here, to run once:
  pinMode(morseSND, OUTPUT);  //speaker goes on this pin
  pinMode(morseLED, OUTPUT);  //onboard LED
  Serial.begin(9600);

  while (!Serial.available()) {
    delay(50);
  } //not sure this is working

  Serial.println();
  Serial.println();
  Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  Serial.println("                   MorsePICO");
  Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  Serial.println("~ Command mode");
  Serial.println("Current commands:");
  Serial.println("~WPM - lists current or sets new WPM speed (~WPM or ~WPM 13)");
  Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  Serial.print("Current WPM: ");
  Serial.println(WPM);
  flashSentence("MorsePICO");// send "MorsePico" in Morse code
  Serial.println();
  Serial.println("Ready!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (stringComplete) { //if serial read has completed
    Serial.println("");
    Serial.println(inputString);
    if (inputString.startsWith("~")) { //check for command character
      inputString.toUpperCase();
      inputString.remove(0, 1); //remove the '~'
      if (inputString.startsWith("WPM")) {
        inputString.remove(0, 4); //remove "WPM" and the space
        inputString.trim(); //trim any white space
        if (inputString.toInt() == 0) { //if no value was supplied
          Serial.print("Current WPM: ");
          Serial.println(WPM); //print the current WPM
          return;
        }
        WPM = inputString.toInt(); // set WPM to value supplied
        Serial.print("Set WPM to: ");
        Serial.println(WPM);
        //calculate the spacing variables based on supplied WPM
        multiplier = 1200 / WPM;
        interspaceLength = 1 * multiplier;
        DITLength = 1 * multiplier;
        DAHLength = 3 * multiplier;
        charSpacingLength = 3 * multiplier;
        wordSpacingLength = 7 * multiplier;
      }// if WPM command
    } else { // else not a command it's stuff we need to send as morse code
      flashSentence(inputString);
      Serial.println("");
    }//else it's stuff we need to send as Morse code
    //reset variables
    inputString = "";
    stringComplete = false;
  }  //if read serial console complete
}  //loop()

void flashLetter(char letter) {
  //this isn't elegant but it gets the job done
  Serial.print(letter);
  if (letter == 'A') { //if character is 'A' (morse symbols ._ )
    flashDIT(); //send DIT
    flashDAH(); //send DAH
  } else if (letter == 'B') { //if character is 'B' (morse symbols _... ) etc...
    flashDAH(); //send DAH etc...
    flashDIT(); //send DIT etc...
    flashDIT(); //send DIT etc...
    flashDIT(); //send DIT etc...
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
  for (int i = 0; i < word.length(); i++) { //for each character in the word...
    flashLetter(word.charAt(i)); //send morse symbols for character
    delay(wordSpacingLength - charSpacingLength); //add inter word spacing
  }  //for each character in word
}  //flashWord()

void flashSentence(String text) {
  int splitCount = countSplitCharacters(text, ' '); //get count of words in sentence
  String wordArray[splitCount + 1]; //make an array to store words
  int startIndex = 0;
  int endIndex = 0;
  for (int i = 0; i < splitCount + 1; i++) {
    //find the start and end index of the words by finding the space characters
    if (startIndex > 0) { //if we've set the startIndex before
      startIndex = text.indexOf(' ', endIndex); //find the new startIndex
    }
    endIndex = text.indexOf(' ', startIndex + 1); //get the endIndex
    if (endIndex < 0) { //if endIndex was not found
      endIndex = text.length(); //set endIndex to end of text
    }
    //parse the word from the string using indexes, don't forget to increment the startIndex
    String word = text.substring(startIndex++, endIndex); //get the word between the indices and increment the startIndex
    word.toUpperCase();   //convert to uppercase
    wordArray[i] = word;  //add word to array
  } //for each word in sentance
  //now send the words in the array
  for (int i = 0; i < splitCount + 1; i++) {
    flashWord(wordArray[i]);
  }  //for each word in array
  delay(wordSpacingLength); //add inter word spacing
}  //flashSentence()

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } //if we have a newline then we're done reading serial for now
    if (stringComplete == false) {
      inputString += inChar;
    } //if no newline then append the char to the string
  } //while stuff ready to read from serial console
}  //serialEvent()

int countSplitCharacters(String text, char splitChar) {
  //why doesn't String() have a count() method!!??
  int returnValue = 0;
  int index = 0;
  while (index > -1) {
    index = text.indexOf(splitChar, index + 1);
    if (index > -1) returnValue++;
  }
  return returnValue;
}  //countSplitCharacters

void flashDIT() {
  digitalWrite(morseSND, HIGH); //set sound high
  digitalWrite(morseLED, HIGH); //set LED high
  delay(DITLength); //morse DIT symbol length 
  digitalWrite(morseSND, LOW); //set sound low
  digitalWrite(morseLED, LOW); //set LED low
  delay(interspaceLength); //spacing between morse symbols
}  //flashDIT()

void flashDAH() {
  digitalWrite(morseSND, HIGH); //set sound high
  digitalWrite(morseLED, HIGH); //set LED high
  delay(DAHLength); //morse DAH symbol length 
  digitalWrite(morseSND, LOW); //set sound low
  digitalWrite(morseLED, LOW); //set LED low
  delay(interspaceLength); //spacing between morse symbols
}  //flashDAH()
