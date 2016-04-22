/*
 * Flashes given string in morseAlphabet on LED on configurable morsePin, if debug=TRUE also printing out symbols on Serial(- is dot, --- is dash, _ is pause)
 * 
 * Used Hardware: Arduino Uno + LED 
 * 
 * Author: Felix Erlacher
 * 
 */

//should be put in separate .h file, but older Arduino IDE's don't like that...
String morseCodes[] = { 
    ".-", // A
    "-...", // B
    "-.-.", // C
    "-..", // D
    ".", // E
    "..-.", // F
    "--.", // G
    "....", // H
    "..", // I
    ".---", // J
    "-.-", // K
    ".-..", // L
    "--", // M
    "-.", // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.", // R
    "...",  // S
    "-", // T
    "..-", // U
    "...-", // V
    ".--", // W
    "-..-", // X
    "-.--", // Y
    "--..", // Z
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----.", // 9
    "-----", // 0
    " " //space character, used to control interWord break
};

//connect LED to gnd and following pin
static int morsePin = 12; 
static int dotLength = 400;   //basic unit of measurement. Morse definition: One dot flashes for one unit, one dash flashes for 3 units, one unit break between each dot or dash, 3 units break between each char, 7 units break between each word
//debug messages on?
static boolean debug=1;
//message to be morsed
static String message="get me out";

/*
* initial setup code
*/
void setup() {
  Serial.begin(9600);
  pinMode(morsePin, OUTPUT);
  digitalWrite(morsePin,LOW);
  if(debug)
    Serial.println("GOGOGO!");
  
}

/*
* primary function for morseing a single char
*/
void morseChar (char c) {
   if(c==' '){
    morse(" ");
   }else{
    morse(morseCodes[c-97]);
   }
    delay(2*dotLength); //interLetter break, adding 2 to the intersymbol break makes it a 3 dotLength break;
    if(debug)
      Serial.print("__");

}

/*
 * receives string of dots and dashes of single Character or whitespace if word is finished
 */
void morse(String tokens) {
   for (int i = 0; i < tokens.length(); i++) {
       switch (tokens[i]) {
           case '-':
               morseDash();
               delay(dotLength); //intersymbol break
               if(debug)
                Serial.print("_");
               break;
           case '.':
               morseDot();
               delay(dotLength); //intersymbol break
               if(debug)
                Serial.print("_");
               break;
           case ' ':
               delay(2*dotLength); //interWord break, +2 to +1* intersymbolBreak +2 *interLetterBreak +2 *interLetterBreak(whitespace) makes this a break of 7
               if(debug)
                Serial.print("__");
               break;
           default:
           Serial.println("ERROR: No dash nor dot nor space, wrong sign in alphabet?!");
       }
   }
}

/*
*flashes a dash (and possibly prints debug info), nothing more
*/
void morseDash(){
  digitalWrite(morsePin,HIGH);
  delay(3*dotLength);
  digitalWrite(morsePin,LOW);
  if(debug)
    Serial.print("---");
  }

/*
*flashes a dot (and possibly prints debug info), nothing more
*/
void morseDot(){
  digitalWrite(morsePin,HIGH);
  delay(dotLength);
  digitalWrite(morsePin,LOW);
  if(debug)
    Serial.print("-");
  }


/*
* "main"
*/
void loop() {

  for(int i=0;i<message.length();i++){
      morseChar(message[i]);
    }
  delay(7000);
  Serial.println();
}
