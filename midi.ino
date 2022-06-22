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

byte PIND_shifter, PINB_shifter;
bool shift_B; // to switch between the two OUTPUT registers


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

  Serial.begin(9600);

  /*  FOR REFERENCE
      ===============================================================
      PORTB = [X, X, WIRE_4, WIRE_3, WIRE_2, WIRE_1, WIRE_H, WIRE_G]
      PORTC = [X, X, X, X, WIRE_8, WIRE_7, WIRE_6, WIRE_5]
      PORTD = [WIRE_F, WIRE_E, WIRE_D, WIRE_C, WIRE_B, WIRE_A, X, X]
      ===============================================================
  */

  // A-H, all outputs are HIGH
  PORTD = PIND | 0b11111100;
  PORTD = PIND | 0b00000011;

  // Only WIRE_A set to LOW
  PORTD = PORTD | 0b11111100;
  PORTB = PORTD | 0b00000011;
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
    PORTB = PORTD | 0b00000011;

    // Updating PORTD, 0 moved to left
    PORTD = PORTD & PIND_shifter;
  }
  else {
    // Shifting bit to left, making sure that the right two its are 11.
    PINB_shifter  = PINB_shifter  << 1;

    if (PINB_shifter == 0b11111100) PINB_shifter = 0b11111101;

    PINB_shifter  = PINB_shifter  | 0b11111100;

    // Making all  output pins HIGH
    PORTD = PORTD | 0b11111100;
    PORTB = PORTD | 0b00000011;

    // Updating PORTB, 0 moved to left
    PORTB = PORTB & PINB_shifter;
  }

  //    Serial.print("PIND_shifter: ");
  //    Serial.println(PIND_shifter, BIN);
  //    Serial.print("PORTD: ");
  //    Serial.println(PORTD, BIN);
  //      Serial.print("PORTB: ");
  //      Serial.println(PORTB, BIN);


  String row, column;

  if ((PORTD & 0b11111100) == 0b11111000) {
    row = "A";
    if ((PINB & 0b00111100) == 0b00111000) {
      column = "1";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00110100) {
      column = "2";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00101100) {
      column = "3";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00011100) {
      column = "4";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001110) {
      column = "5";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001101) {
      column = "6";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001011) {
      column = "7";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00000111) {
      column = "8";
      Serial.println(row + column);
    }
  }

  if ((PORTD & 0b11111100) == 0b11110100) {
    row = "B";
    if ((PINB & 0b00111100) == 0b00111000) {
      column = "1";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00110100) {
      column = "2";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00101100) {
      column = "3";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00011100) {
      column = "4";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001110) {
      column = "5";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001101) {
      column = "6";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001011) {
      column = "7";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00000111) {
      column = "8";
      Serial.println(row + column);
    }
  }

  if ((PORTD & 0b11111100) == 0b11101100) {
    row = "C";
    if ((PINB & 0b00111100) == 0b00111000) {
      column = "1";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00110100) {
      column = "2";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00101100) {
      column = "3";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00011100) {
      column = "4";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001110) {
      column = "5";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001101) {
      column = "6";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001011) {
      column = "7";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00000111) {
      column = "8";
      Serial.println(row + column);
    }
  }

  if ((PORTD & 0b11111100) == 0b11011100) {
    row = "D";
    if ((PINB & 0b00111100) == 0b00111000) {
      column = "1";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00110100) {
      column = "2";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00101100) {
      column = "3";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00011100) {
      column = "4";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001110) {
      column = "5";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001101) {
      column = "6";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001011) {
      column = "7";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00000111) {
      column = "8";
      Serial.println(row + column);
    }
  }

  if ((PORTD & 0b11111100) == 0b10111100) {
    row = "E";
    if ((PINB & 0b00111100) == 0b00111000) {
      column = "1";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00110100) {
      column = "2";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00101100) {
      column = "3";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00011100) {
      column = "4";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001110) {
      column = "5";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001101) {
      column = "6";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001011) {
      column = "7";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00000111) {
      column = "8";
      Serial.println(row + column);
    }
  }

  if ((PORTD & 0b11111100) == 0b01111100) {
    row = "F";
    if ((PINB & 0b00111100) == 0b00111000) {
      column = "1";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00110100) {
      column = "2";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00101100) {
      column = "3";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00011100) {
      column = "4";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001110) {
      column = "5";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001101) {
      column = "6";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001011) {
      column = "7";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00000111) {
      column = "8";
      Serial.println(row + column);
    }
  }

  if ((PORTB & 0b00000011) == 0b00000010) {
    row = "G";
    if ((PINB & 0b00111100) == 0b00111000) {
      column = "1";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00110100) {
      column = "2";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00101100) {
      column = "3";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00011100) {
      column = "4";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001110) {
      column = "5";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001101) {
      column = "6";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001011) {
      column = "7";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00000111) {
      column = "8";
      Serial.println(row + column);
    }
  }

  if ((PORTB & 0b00000011) == 0b00000001) {
    row = "H";
    if ((PINB & 0b00111100) == 0b00111000) {
      column = "1";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00110100) {
      column = "2";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00101100) {
      column = "3";
      Serial.println(row + column);
    }
    if ((PINB & 0b00111100) == 0b00011100) {
      column = "4";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001110) {
      column = "5";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001101) {
      column = "6";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00001011) {
      column = "7";
      Serial.println(row + column);
    }
    if ((PINC & 0b00001111) == 0b00000111) {
      column = "8";
      Serial.println(row + column);
    }
  }
}
