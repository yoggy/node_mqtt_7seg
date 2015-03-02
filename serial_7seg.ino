//
//  serial_7seg.ino
//
//  see also... 
//    https://www.switch-science.com/catalog/742/
//    http://morecatlab.akiba.coocan.jp/lab/index.php/aruino/7segduino/
//

// download & install SSeg library
// http://morecatlab.akiba.coocan.jp/lab/wp-content/uploads/2011/12/SSeg-20111211.zip
#include <Sseg.h>

Sseg mySseg = Sseg(4, 8, 11, 13, 14, 2, 10, 12, 3, 6, 7, 9);

uint8_t patterns[] = {
  NUM_PAT_0,
  NUM_PAT_1,
  NUM_PAT_2,
  NUM_PAT_3,
  NUM_PAT_4,
  NUM_PAT_5,
  NUM_PAT_6,
  NUM_PAT_7,
  NUM_PAT_8,
  NUM_PAT_9,
  0b00000000  // blank
};

int buf[4];
int buf_idx = 0;

void setup()
{
  mySseg.setKcommon();
  mySseg.begin();

  Serial.begin(9600);

  // clear display (set blank)
  buf[0] = 10;
  buf[1] = 10;
  buf[2] = 10;
  buf[3] = 10;
  buf_idx = 0;
  update7seg();
}

void update7seg() {
  mySseg.writeRawData(patterns[buf[0]], patterns[buf[1]], patterns[buf[2]], patterns[buf[3]]);
  buf_idx = 0;
}

void loop()
{
  if (Serial.available() > 0) {
    int c = Serial.read();
    if (0x30 <= c && c <= 0x39) {
      buf[buf_idx] = c - 0x30;
      if (buf_idx < 4) buf_idx ++;
    }
    else if (c == 0x20) {
      buf[buf_idx] = 10; // blank
      if (buf_idx < 4) buf_idx ++;
    }
    else if (c == 0x0a) {
      update7seg();
    }
  }
  mySseg.update();
}

