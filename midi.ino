// PIND from DIGITAL PINS 2 to 7
#define WIRE_A 2
#define WIRE_B 3
#define WIRE_C 4
#define WIRE_D 5
#define WIRE_E 6
#define WIRE_F 7

// PINB from DIGITAL PINS 8 to 13
#define WIRE_G 8
#define WIRE_H 9

#define WIRE_1 10
#define WIRE_2 11
#define WIRE_3 12
#define WIRE_4 13

// PINC from ANALOG PINS 0 to 3
#define WIRE_5 A0
#define WIRE_6 A1
#define WIRE_7 A2
#define WIRE_8 A3

int noteVelocity = 0x45;
int noteCmd = 0x90; //The lower nibble is the channel


byte PIND_shifter, PINB_shifter;
bool shift_B; // to switch between the two OUTPUT registers

//The pitches start from C2 (MIDI NUMBER 36) and go till C7 (MIDI NUMBER 96). The extra 3 are filler.
int pitches_table [8][8] = {
  {36, 37, 38, 39, 40, 41, 42, 43},
  {44, 45, 46, 47, 48, 49, 50, 51},
  {52, 53, 54, 55, 56, 57, 58, 59},
  {60, 61, 62, 63, 64, 65, 66, 67},
  {68, 69, 70, 71, 72, 73, 74, 75},
  {76, 77, 78, 79, 80, 81, 82, 83},
  {84, 85, 86, 87, 88, 89, 90, 91},
  {92, 93, 94, 95, 96, 97, 98, 99}
};

bool key_state_table [8][8] = {
  {false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false},
  {false, false, false, false, false, false, false, false}
}; //array to hold our button states

int iteration_for_press_consideration = 5;

void setup() {

  pinMode(WIRE_A, OUTPUT);
  pinMode(WIRE_B, OUTPUT);
  pinMode(WIRE_C, OUTPUT);
  pinMode(WIRE_D, OUTPUT);
  pinMode(WIRE_E, OUTPUT);
  pinMode(WIRE_F, OUTPUT);
  pinMode(WIRE_G, OUTPUT);
  pinMode(WIRE_H, OUTPUT);

  pinMode(WIRE_1, INPUT_PULLUP);
  pinMode(WIRE_2, INPUT_PULLUP);
  pinMode(WIRE_3, INPUT_PULLUP);
  pinMode(WIRE_4, INPUT_PULLUP);
  pinMode(WIRE_5, INPUT_PULLUP);
  pinMode(WIRE_6, INPUT_PULLUP);
  pinMode(WIRE_7, INPUT_PULLUP);
  pinMode(WIRE_8, INPUT_PULLUP);

  //  Serial.begin(9600);
  //  Serial.begin(115200); // hairlessMIDI baudrate
  Serial.begin(31250); // MIDI Standard baudrate

  /*  FOR REFERENCE
      ===============================================================
      PORTB = [X, X, WIRE_4, WIRE_3, WIRE_2, WIRE_1, WIRE_H, WIRE_G]
      PORTC = [X, X, X, X, WIRE_8, WIRE_7, WIRE_6, WIRE_5]
      PORTD = [WIRE_F, WIRE_E, WIRE_D, WIRE_C, WIRE_B, WIRE_A, X, X]
      ===============================================================
  */

  // A-H, all outputs are HIGH
  PORTD = PORTD | 0b11111100;
  PORTB = PORTB | 0b00000011;

  // Only WIRE_A set to LOW
  PORTD = PORTD & 0b11111011;

  // OUTPUT PIN shifters
  PIND_shifter = 0b11111101;
  PINB_shifter = 0b11111111;

  shift_B = false;
}


void loop() {

  if (PIND_shifter == 0b01111111) {
    PIND_shifter = 0b11111101;
    shift_B = true;
  }

  else if (PINB_shifter == 0b11111101) {
    PINB_shifter = 0b11111111;
    shift_B = false;
  }

  if (shift_B == false) {
    // Shifting bit to left, making sure that the right two its are 11.
    PIND_shifter  = PIND_shifter  << 1;
    PIND_shifter  = PIND_shifter  | 0b00000011;

    // Making all  output pins HIGH
    PORTD = PORTD | 0b11111100;
    PORTB = PORTB | 0b00000011;

    // Updating PORTD, 0 moved to left
    PORTD = PORTD & PIND_shifter;
  }
  else {
    // Shifting bit to left, making sure that the right two bits are 11.

    if (PINB_shifter != 0b11111111) PINB_shifter  = ~(~PINB_shifter  << 1);
    else PINB_shifter  = PINB_shifter  << 1;

    PINB_shifter  = PINB_shifter  | 0b11111100;

    // Making all  output pins HIGH
    PORTD = PORTD | 0b11111100;
    PORTB = PORTB | 0b00000011;

    // Updating PORTB, 0 moved to left
    PORTB = PORTB & PINB_shifter;
  }

  // OUTPUT DEBUG STUFF
  // =====================
  //  Serial.print("PIND_shifter: ");
  //  Serial.println(PIND_shifter, BIN);
  //  Serial.print("PINB_shifter: ");
  //  Serial.println(PINB_shifter, BIN);
  //  Serial.print("PORTD: ");
  //  Serial.println(PORTD, BIN);
  //  Serial.print("PORTB: ");
  //  Serial.println(PORTB, BIN);


  char row, column;

  // This is switch case because only one will be activated at one time
  if (!shift_B) {
    switch (PORTD & 0xFC) {
      case 0xF8:
        row = 'A';
        break;
      case 0xF4:
        row = 'B';
        break;
      case 0xEC:
        row = 'C';
        break;
      case 0xDC:
        row = 'D';
        break;
      case 0xBC:
        row = 'E';
        break;
      case 0x7C:
        row = 'F';
        break;
    }
  }
  else {
    switch (PORTB & 0x03) {
      case 0x02:
        row = 'G';
        break;
      case 0x01:
        row = 'H';
        break;
    }
  }


  //   INPUT DEBUG STUFF
  //   =====================
  //  Serial.print("PINB: ");
  //  Serial.println(PINB, BIN);
  //  Serial.print("PINC: ");
  //  Serial.println(PINC, BIN);

  //  delay(500);

  pinMode(WIRE_1, INPUT_PULLUP);
  pinMode(WIRE_2, INPUT_PULLUP);
  pinMode(WIRE_3, INPUT_PULLUP);
  pinMode(WIRE_4, INPUT_PULLUP);
  pinMode(WIRE_5, INPUT_PULLUP);
  pinMode(WIRE_6, INPUT_PULLUP);
  pinMode(WIRE_7, INPUT_PULLUP);
  pinMode(WIRE_8, INPUT_PULLUP);


  // This is not switch case because more than one column may be activated of the same row. Switch case break would make it skip the later key presses.
  if ((PINB & 0x3C) == 0x38) {
    column = '1';
    //    Serial.print("PINB & 0x3C: ");
    //    Serial.println(PINB & 0x3C, HEX);
    printRowColumn(row, column);
    checkState(row, column, false);
  }
  else {
    column = '1';
    checkState(row, column, true);
  }

  if ((PINB & 0x3C) == 0x34) {
    column = '2';
    printRowColumn(row, column);
    checkState(row, column, false);
  }
  else {
    column = '2';
    checkState(row, column, true);
  }

  if ((PINB & 0x3C) == 0x2C) {
    column = '3';
    printRowColumn(row, column);
    checkState(row, column, false);
  }
  else {
    column = '3';
    checkState(row, column, true);
  }

  if ((PINB & 0x3C) == 0x1C) {
    column = '4';
    printRowColumn(row, column);
    checkState(row, column, false);
  }
  else {
    column = '4';
    checkState(row, column, true);
  }

  if ((PINC & 0x0F) == 0x0E) {
    column = '5';
    printRowColumn(row, column);
    checkState(row, column, false);
  }
  else {
    column = '5';
    checkState(row, column, true);
  }

  if ((PINC & 0x0F) == 0x0D) {
    column = '6';
    printRowColumn(row, column);
    checkState(row, column, false);
  }
  else {
    column = '6';
    checkState(row, column, true);
  }

  if ((PINC & 0x0F) == 0x0B) {
    column = '7';
    printRowColumn(row, column);
    checkState(row, column, false);
  }
  else {
    column = '7';
    checkState(row, column, true);
  }

  if ((PINC & 0x0F) == 0x07) {
    column = '8';
    printRowColumn(row, column);
    checkState(row, column, false);
  }
  else {
    column = '8';
    checkState(row, column, true);
  }

}

int findPitch(char row, char column) {

  int row_number;
  switch (row) {
    case 'A':
      row_number = 0;
      break;
    case 'B':
      row_number = 1;
      break;
    case 'C':
      row_number = 2;
      break;
    case 'D':
      row_number = 3;
      break;
    case 'E':
      row_number = 4;
      break;
    case 'F':
      row_number = 5;
      break;
    case 'G':
      row_number = 6;
      break;
    case 'H':
      row_number = 7;
      break;
  }

  int column_number = (column - '0') - 1; // converting from char to int, and then subtracting 1 because my column count starts from 1
  return (pitches_table[row_number][column_number]);
}

void noteOn(char row, char column) {

  int pitch = findPitch(row, column);
  //  Serial.print("pitch: ");
  //  Serial.println(pitch);

  Serial.write(noteCmd);//Serial.write() to send byte without formatting
  Serial.write(pitch);
  Serial.write(noteVelocity);
}

void noteOff(char row, char column) {
  int pitch = findPitch(row, column);

  Serial.write(noteCmd);//Serial.write() to send byte without formatting
  Serial.write(pitch);
  Serial.write(0x00);
}


void printRowColumn(char row, char column) {
  //    Serial.print(row);
  //    Serial.println(column);
}


void checkState(char row, char column, bool released) {

  //  Serial.print(row);
  //  Serial.print(column);
  //  Serial.print(": ");
  //  Serial.println(key_state_table[row][column]);


  if (released == true && key_state_table[row][column] == true) {
    //    Update state
    key_state_table[row][column] = false;

    //    turn the note off when key released
    noteOff(row, column);

    //    Serial.print(row);
    //    Serial.print(column);
    //    Serial.println(" released");
  }

  //  check if key already pressed (as in its being kept pressed)
  else if (released == false && key_state_table[row][column] == false) {

    //    if key pressed for the first time, then  send note, else ignore
    key_state_table[row][column] = true;
    noteOn(row, column);

    //    Serial.print(row);
    //    Serial.print(column);
    //    Serial.println(" pressed");
  }

  else if (released == false && key_state_table[row][column] == true) {

    //    Ignore if still pressed

    //    Serial.print(row);
    //    Serial.print(column);
    //    Serial.println(" still pressed");
  }

}
