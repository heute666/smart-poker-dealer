//v2 to add encoder and oled on top
//update on shooting timeout diagnose
//#include <EEPROM.h>
#define pcb_industry_v2
//#define ble_enable
//#define record_time
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SH1107               //SH1106 //SSD1306

#ifdef SSD1306
  #include <Adafruit_SSD1306.h>
  #define screen_enable
  Adafruit_SSD1306 display(128, 64, &Wire, -1);  // I2C / TWI
#endif
#ifdef SH1106
  #include <Adafruit_SH110X.h>
  #define screen_enable
  Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1);
#endif
#ifdef SH1107
  #include <Adafruit_SH110X.h>
  #define screen_enable
  Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire, -1);
#endif

#ifdef screen_enable
  const unsigned char PROGMEM str_guandan[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x03, 0x78, 0xC0, 0x00, 0x00, 0x0C, 0xAF, 0x20, 0x00, 0x00, 0x1F,
                                              0xDF, 0xF0, 0x00, 0x00, 0x3F, 0xFF, 0xF8, 0x00, 0x00, 0x7F, 0xFF, 0xFC, 0x00, 0x00, 0x7F, 0xFF, 0xFC, 0x00, 0x00, 0xFD, 0xFF, 0xBE, 0x00, 0x00, 0xFF, 0xEF, 0xFE, 0x00, 0x00, 0xFF, 0xC7, 0xFE,
                                              0x20, 0x00, 0xFF, 0x83, 0xFE, 0x30, 0x08, 0xCF, 0xC7, 0x9F, 0x78, 0x0C, 0xB7, 0xEF, 0x6F, 0x78, 0x1C, 0x7B, 0x86, 0xE7, 0xFC, 0x1E, 0x7F, 0xB9, 0xFB, 0x7C, 0x3F, 0xFD, 0x7F, 0xFC, 0xFC, 0x3F,
                                              0xFE, 0x7F, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF,
                                              0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xFF, 0xC0, 0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x03, 0xFF, 0xFF, 0xFF, 0x80,
                                              0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0xFF, 0xFC, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x0F, 0xFF, 0xE0, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00,
                                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };  //40x40
  static const unsigned char PROGMEM str_doudizhu[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x3F, 0x81, 0xFC, 0x00, 0x00, 0xFC, 0x00, 0x3F, 0x00, 0x01, 0xF0,
                                                      0x00, 0x0F, 0x80, 0x03, 0xE0, 0x02, 0x07, 0xC0, 0x07, 0xC0, 0x03, 0x03, 0xE0, 0x0F, 0x80, 0x03, 0x01, 0xF0, 0x0F, 0x00, 0xF3, 0x00, 0xF0, 0x1F, 0x00, 0x73, 0x00, 0xF8, 0x1E, 0x00, 0x63, 0x00,
                                                      0x78, 0x3E, 0x00, 0x83, 0x00, 0x7C, 0x3E, 0x01, 0xE3, 0x00, 0x7C, 0x3C, 0x00, 0xF3, 0x70, 0x3C, 0x3C, 0x00, 0xC7, 0xF0, 0x3E, 0x7C, 0x01, 0xBF, 0x00, 0x3E, 0x7C, 0x00, 0x73, 0x00, 0x3E, 0x7C,
                                                      0x01, 0xC3, 0x00, 0x3E, 0x7C, 0x07, 0x03, 0x00, 0x3E, 0x7E, 0x1E, 0x03, 0x00, 0x7E, 0x7E, 0x1C, 0x03, 0x00, 0x7E, 0x7E, 0x00, 0x03, 0x00, 0x7E, 0x3F, 0x00, 0x03, 0x00, 0xFC, 0x3F, 0x00, 0x03,
                                                      0x00, 0xFC, 0x3F, 0x80, 0x03, 0x01, 0xFC, 0x3F, 0xC0, 0x03, 0x03, 0xFC, 0x3F, 0xE0, 0x02, 0x07, 0xFC, 0x1F, 0xF0, 0x00, 0x0F, 0xF8, 0x1F, 0xFC, 0x00, 0x3F, 0xF8, 0x0F, 0xFF, 0x81, 0xFF, 0xF0,
                                                      0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x3F, 0xFF, 0xFC, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x03,
                                                      0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  static const unsigned char PROGMEM str_tao[] = { 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x07, 0xFF, 0xE0, 0x00, 0x00, 0x0F,
                                                 0xFF, 0xF0, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x3F, 0xFF, 0xFC, 0x00, 0x00, 0x7F, 0xFF, 0xFE, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x80, 0x03, 0xFF, 0xFF, 0xFF,
                                                 0xC0, 0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x1F, 0xFF, 0xFF, 0xFF, 0xF0, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x7F,
                                                 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF,
                                                 0xFF, 0xFC, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x01, 0xFF, 0x7E, 0xFF, 0x80,
                                                 0x00, 0xFC, 0x7E, 0x7E, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x03,
                                                 0xFF, 0xC0, 0x00, 0x00, 0x07, 0xFF, 0xE0, 0x00 };
  const unsigned char PROGMEM str_xin[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x0F, 0x80, 0x07, 0xFE, 0x00, 0x3F, 0xE0, 0x0F, 0xFF, 0x00, 0x7F, 0xF0, 0x1F, 0xFF, 0x80, 0xFF, 0xF8, 0x3F, 0xFF, 0xC1, 0xFF, 0xFC, 0x7F, 0xFF,
                                          0xC1, 0xFF, 0x7E, 0x7F, 0xFF, 0xE3, 0xFF, 0xBE, 0xFF, 0xFF, 0xF7, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F,
                                          0xFF, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x1F, 0xFF, 0xFF, 0xFF, 0xF8, 0x0F, 0xFF, 0xFF, 0xFF, 0xF0, 0x07, 0xFF, 0xFF, 0xFF, 0xE0, 0x03, 0xFF, 0xFF, 0xFF, 0xC0, 0x01, 0xFF, 0xFF,
                                          0xFF, 0x80, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7F, 0xFF, 0xFE, 0x00, 0x00, 0x3F, 0xFF, 0xFC, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x07, 0xFF, 0xE0, 0x00,
                                          0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  static const unsigned char PROGMEM str_mei[] = { 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xC0, 0x00, 0x00, 0x07, 0xFF, 0xE0, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x1F,
                                                 0xFF, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0xFC, 0x00, 0x00, 0x1F, 0xFF, 0xF8,
                                                 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0xE7, 0xFF, 0xE7, 0x80, 0x07, 0xFB, 0xFF, 0xDF, 0xE0, 0x1F, 0xFD, 0xFF, 0xBF, 0xF8, 0x3F, 0xFF, 0xFF, 0xFF, 0xF8, 0x3F,
                                                 0xFF, 0xFF, 0xFF, 0xFC, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                                 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x7F, 0xFF, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0xFF, 0xBD, 0xFF, 0xFC,
                                                 0x1F, 0xFF, 0x3C, 0xFF, 0xF8, 0x0F, 0xFE, 0x3E, 0x7F, 0xF0, 0x03, 0xF8, 0x7E, 0x1F, 0xC0, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x03,
                                                 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  const unsigned char PROGMEM str_fang[] = { 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x00, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x1F, 0xFC, 0x00, 0x00, 0x00, 0x1F,
                                           0xFE, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0x80, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0x00, 0x01, 0xFF, 0xFF, 0xE0, 0x00, 0x03, 0xFF, 0xFF, 0xF0, 0x00, 0x07, 0xFF, 0xFF, 0xF0,
                                           0x00, 0x0F, 0xFF, 0xFF, 0xF8, 0x00, 0x1F, 0xFF, 0xFF, 0xFC, 0x00, 0x3F, 0xFF, 0xFF, 0xFE, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0xFF,
                                           0xFF, 0xFF, 0xFF, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x3F, 0xFF, 0xFF, 0xFF, 0x00, 0x1F, 0xFF, 0xFF, 0xFE, 0x00, 0x0F, 0xFF, 0xFF,
                                           0xFC, 0x00, 0x07, 0xFF, 0xFF, 0xF8, 0x00, 0x03, 0xFF, 0xFF, 0xF0, 0x00, 0x03, 0xFF, 0xFF, 0xE0, 0x00, 0x01, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x7F, 0xFF, 0x80, 0x00,
                                           0x00, 0x3F, 0xFF, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x00, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x00, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x00, 0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x00,
                                           0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  const unsigned char PROGMEM str_play[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x3F, 0xF0, 0x00, 0x00, 0x00, 0x3F, 0xFC,
                                           0x00, 0x00, 0x00, 0x3F, 0xFF, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xC0, 0x00, 0x00, 0x3F, 0xFF, 0xF0, 0x00, 0x00, 0x3F, 0xFF, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xC0,
                                           0x00, 0x3F, 0xFF, 0xFF, 0xF0, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xC0, 0x3F, 0xFF, 0xFF, 0xFF, 0xF0, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F,
                                           0xFF, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xFE, 0x3F, 0xFF, 0xFF, 0xFF, 0xF8, 0x3F, 0xFF, 0xFF, 0xFF, 0xE0, 0x3F, 0xFF, 0xFF, 0xFF, 0x80, 0x3F, 0xFF, 0xFF, 0xFE, 0x00, 0x3F, 0xFF, 0xFF,
                                           0xF8, 0x00, 0x3F, 0xFF, 0xFF, 0xE0, 0x00, 0x3F, 0xFF, 0xFF, 0x80, 0x00, 0x3F, 0xFF, 0xFE, 0x00, 0x00, 0x3F, 0xFF, 0xF8, 0x00, 0x00, 0x3F, 0xFF, 0xE0, 0x00, 0x00, 0x3F, 0xFF, 0x80, 0x00, 0x00,
                                           0x3F, 0xFE, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x3F, 0xE0, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  const unsigned char PROGMEM str_continue[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x00,
                                               0x0F, 0xC0, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x5D, 0xEF, 0xFF, 0xFC, 0x00, 0x5D, 0xEF, 0xFF, 0xFE, 0x00, 0x5D, 0xEF, 0xFF, 0xFF,
                                               0x00, 0x5D, 0xEF, 0xFF, 0xFF, 0x80, 0x5D, 0xEF, 0xFF, 0xFF, 0xC0, 0x5D, 0xEF, 0xFF, 0xFF, 0xE0, 0x5D, 0xEF, 0xFF, 0xFF, 0xF0, 0x5D, 0xEF, 0xFF, 0xFF, 0xF8, 0x5D, 0xEF, 0xFF, 0xFF, 0xFC, 0x5D,
                                               0xEF, 0xFF, 0xFF, 0xFE, 0x5D, 0xEF, 0xFF, 0xFF, 0xFE, 0x5D, 0xEF, 0xFF, 0xFF, 0xFC, 0x5D, 0xEF, 0xFF, 0xFF, 0xF8, 0x5D, 0xEF, 0xFF, 0xFF, 0xF0, 0x5D, 0xEF, 0xFF, 0xFF, 0xE0, 0x5D, 0xEF, 0xFF,
                                               0xFF, 0xC0, 0x5D, 0xEF, 0xFF, 0xFF, 0x80, 0x5D, 0xEF, 0xFF, 0xFF, 0x00, 0x5D, 0xEF, 0xFF, 0xFE, 0x00, 0x5D, 0xEF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x00,
                                               0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00,
                                               0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  const unsigned char PROGMEM str_setup[] = { 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x7C, 0x3E, 0x00, 0x00, 0x00, 0xFC, 0x3E, 0x00, 0x00, 0x01, 0xFE, 0x7E, 0x00, 0x00, 0x01, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x00, 0x00,
                                            0xFF, 0xFE, 0x80, 0x00, 0x01, 0xFE, 0x3E, 0xFC, 0x00, 0x3F, 0xF0, 0x0E, 0xFC, 0x00, 0x3F, 0xE7, 0xE2, 0xFE, 0x00, 0x7F, 0xCF, 0xFA, 0xFE, 0x00, 0x7F, 0x9F, 0xFC, 0xFE, 0x00, 0x7F, 0xBF, 0xFC,
                                            0xFE, 0x00, 0x3F, 0x3F, 0xFC, 0xF8, 0x00, 0x0F, 0x3F, 0xFE, 0xF0, 0x00, 0x0F, 0x3F, 0xFE, 0xD0, 0x00, 0x0F, 0x3F, 0xFE, 0x80, 0x00, 0x0F, 0x3F, 0xFC, 0xA4, 0x00, 0x78, 0x3F, 0xFC, 0x76, 0x00,
                                            0x7C, 0x1F, 0xF9, 0x7A, 0x0C, 0x7C, 0xEF, 0xF0, 0xFA, 0x0F, 0x7D, 0xF3, 0xE0, 0xFC, 0x0F, 0xFF, 0xF0, 0x0C, 0xFC, 0x0F, 0xC7, 0xF2, 0x3C, 0x00, 0x07, 0x03, 0xE3, 0xFC, 0x00, 0x0E, 0x00, 0xE3,
                                            0xFC, 0x00, 0x34, 0x00, 0xFB, 0xFF, 0x80, 0xF0, 0x00, 0x7D, 0xFC, 0x00, 0xF8, 0x00, 0x7C, 0x38, 0x00, 0xF8, 0x00, 0x7C, 0x10, 0x00, 0xFC, 0x00, 0xFC, 0x00, 0x00, 0x1E, 0x00, 0xF0, 0x00, 0x00,
                                            0x0E, 0x01, 0xE0, 0x00, 0x00, 0x0F, 0x83, 0xE0, 0x00, 0x00, 0x1F, 0x8F, 0xF0, 0x00, 0x00, 0x3F, 0xE3, 0xE0, 0x00, 0x00, 0x1F, 0x78, 0x00, 0x00, 0x00, 0x0C, 0x7C, 0x40, 0x00, 0x00, 0x00, 0x7C,
                                            0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00 };
  const unsigned char *Ico_table[5] = { str_guandan, str_doudizhu, str_tao, str_xin, str_mei };
  const unsigned char *Ico_table2[3] = { str_play, str_continue, str_setup };
  const unsigned char PROGMEM str_coe0[] = "Totalcards";
  const unsigned char PROGMEM str_coe1[] = "Players";
  const unsigned char PROGMEM str_coe2[] = "Holdcards";
  const unsigned char PROGMEM str_coe3[] = "Speed";
  const unsigned char PROGMEM str_coe4[] = "RandomMode";
  const unsigned char *str_coe[5] = { str_coe0, str_coe1, str_coe2, str_coe3, str_coe4 };
#endif
//digital analogwrite conflict; compensate is too much; running time count to debug/ remain card to debug, 4 players in endless loop/ 1st card compensation is not enough
//_1_2在连续发牌和随机中，均正常使用了定时器中断更稳定的驱动主轴stepper，并且通过高速低速两个表实现了更快的转速，及更好的卡滞的兼容性。
//随机模式中，想在旋转过程加载及发牌提升效率，但在中断过程中开启和停止直流电机会造成定时器中断混乱，未能在本版本解决。
//PWM驱动DC电机模式在本版本也不成功，soft start直接产生异常，连续低速发牌死循环。
//EEPROM.const uint8_t coesetup[8] PROGMEM = { 108, 0, 4, 32, 0, 255, 1, 1 };

const unsigned int low_speed_table[256] PROGMEM =  //12v 20.8khz 能驱动约800g；8v 17.8k 驱动800g 开始丢步
  { 62500, 8445, 4528, 3094, 2349, 1893, 1586, 1364, 1197, 1066, 961, 875, 803, 742, 689, 644, 604, 569, 537, 509, 484, 461, 440, 421, 404, 388, 373, 359, 346, 334, 323, 313, 303, 294, 285, 277, 270, 262, 255, 249, 243, 237, 231, 226, 221, 216, 211, 207, 202, 198, 194,
    190, 187, 183, 180, 177, 173, 170, 167, 165, 162, 159, 157, 154, 152, 149, 147, 145, 143, 141, 139, 137, 135, 133, 131, 129, 128, 126, 124, 123, 121, 120, 118, 117, 116, 114, 113, 112, 110, 109, 108, 107, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92,
    91, 91, 90, 89, 88, 87, 87, 86, 85, 84, 84, 83, 82, 81, 81, 80, 79, 79, 78, 78, 77, 76, 76, 75, 75, 74, 73, 73, 72, 72, 71, 71, 70, 70, 69, 69, 68, 68, 67, 67, 66, 66, 65, 65, 65, 64, 64, 63, 63, 62, 62, 62, 61, 61, 60, 60, 60, 59, 59, 59, 58, 58, 58, 57, 57, 57, 56, 56,
    56, 55, 55, 55, 54, 54, 54, 53, 53, 53, 53, 52, 52, 52, 51, 51, 51, 51, 50, 50, 50, 50, 49, 49, 49, 49, 48, 48, 48, 48, 47, 47, 47, 47, 46, 46, 46, 46, 46, 45, 45, 45, 45, 44, 44, 44, 44, 44, 43, 43, 43, 43, 43, 42, 42, 42, 42, 42, 42, 41, 41, 41, 41, 41, 41, 40, 40, 40,
    40, 40, 39, 39, 39, 39, 39, 39, 39, 38, 38, 38, 38, 38 };
const unsigned int high_speed_table[256] PROGMEM =  //通过插值更新
  { 38, 38, 38, 38, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 34, 34, 34, 34, 34, 34, 34, 34,
    34, 34, 34, 34, 34, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31,
    31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
    27, 27, 27, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
    25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 24, 24, 24, 24, 24, 24, 24, 24, 24 };

#ifdef screen_enable
  typedef struct
  {
  unsigned char index;
  unsigned char up;
  unsigned char down;
  unsigned char back;
  unsigned char forward;
  void (*operation)(void);
  } KEY_TABLE;

  unsigned char funIndex = 0;
  void (*current)(void);
  void menu_1(void);
  void menu_2(void);
  void menu_running(void);
  void mode_setup(void);
  void coe_setup(void);

  KEY_TABLE menu[] = {
  { 0, 4, 1, 9, 5, (*menu_1) },
  { 1, 0, 2, 9, 5, (*menu_1) },
  { 2, 1, 3, 9, 5, (*menu_1) },
  { 3, 2, 4, 9, 5, (*menu_1) },
  { 4, 3, 0, 9, 5, (*menu_1) },
  { 5, 7, 6, 0, 8, (*menu_2) },
  { 6, 5, 7, 0, 8, (*menu_2) },
  { 7, 6, 5, 0, 9, (*menu_2) },
  { 8, 5, 5, 0, 5, (*menu_running) },   // to set long push to 20 as sys restart
  { 9, 10, 13, 5, 14, (*mode_setup) },   //cards
  { 10, 11, 9, 5, 14, (*mode_setup) },   //player
  { 11, 12, 10, 5, 14, (*mode_setup) },  //holdhards
  { 12, 13, 11, 5, 14, (*mode_setup) },  //fqy/speed
  { 13, 9, 12, 5, 14, (*mode_setup) },   //random/1by1
  { 14, 16, 15, 0, 9, (*coe_setup) },    //
  { 15, 16, 15, 0, 9, (*coe_setup) },    //
  { 16, 16, 15, 0, 9, (*coe_setup) },    //
  };

  uint8_t mode_coe[5][5] = {
  { 108, 4, 0, 32, 1 },  //initial guandan
  { 54, 3, 3, 30, 1 },   //initial doudizhu
  { 54, 3, 0, 30, 1 },   //initial heitao5
  { 108, 4, 8, 80, 1 },  //initial shengji
  { 108, 8, 0, 60, 1 },  //initial paodekuai
  };
  uint8_t mode_select=0;
  uint8_t coe_select=0;
  //encoder setup
  #define rotator_a 4
  #define rotator_go A1
  #define rotator_b 3
  uint8_t button_on = 0;
  uint8_t encoderflag = 0;
  bool CW_1 = 0;
  bool CW_2 = 0;
  volatile uint8_t encoder_pos = 100;
  void draw_bat();
#endif

#define AC 0  //anti clockwise
#define CW 1  //clockwise
uint8_t randomsq[108];

#ifdef pcb_industry_v2
#define motora1 5  //timer1
#define motora2 6
#define outer_sensor 2  //replace by interrupt 0
#define cardin A3
#define steperEN 10
#define steperDIR 8
#define volread A2
#define LEDPIN 13
#endif

//ISR index
#define STOP 10
#define CHECK 0
#define SLIP 1
#define LOW_ACCEL 2
#define HIGH_ACCEL 3
#define HIGH_DECEL 4
#define LOW_DECEL 5
#define COUNTRESET 9

//basic parameters
volatile int slip_step;  // point to start decel
volatile int loopstep;
volatile int check_step;           //checkpoint for first card angle compensation, and hold card angle ;
volatile uint8_t low_accel_step;   // theoratic accel steps
volatile uint8_t high_accel_step;  // theoratic accel steps
unsigned int t_total;
long t_start;
const int basestep = 10560;
volatile uint8_t flag = STOP;  //电机状态
uint8_t mode_type = 9;
bool dir = CW;
#define mode_1by1 0
#define mode_random 1
bool fast_break = 1; //reserved
bool goon;
bool startover = 0;  //flag to indicate any error and break many loops
volatile bool check_point = 0;
volatile bool loaded = 0;
volatile bool rotating = 0;
uint8_t players = 0;
uint8_t maxfqy;
volatile uint8_t timeout=0;
uint16_t bat;
volatile uint8_t cardout = 0;
uint8_t totalcards = 0;
uint8_t holdcards = 0;
//byte index_acc; //to indicate the position in the speed table
String SW_V = "241001";
#ifdef record_time
  uint8_t t = 0;
  uint8_t duration[216];
#endif


void setup() {
#ifdef screen_enable
  pinMode(rotator_a, INPUT_PULLUP);
  pinMode(rotator_go, INPUT_PULLUP);
  pinMode(rotator_b, INPUT_PULLUP);
#endif
#ifdef ble_enable
  Serial.begin(9600);
#endif
  //TWBR = 12;
  pinMode(motora1, OUTPUT);
  pinMode(motora2, OUTPUT);
  digitalWrite(motora1, 0);
  digitalWrite(motora2, 0);
  pinMode(steperEN, OUTPUT);  //en
  pinMode(volread, INPUT);
  pinMode(9, OUTPUT);  //steper PB0
  pinMode(cardin, INPUT_PULLUP);
  pinMode(outer_sensor, INPUT_PULLUP);
  pinMode(steperDIR, OUTPUT);  //dir
  //pinMode(LEDPIN, OUTPUT);
  digitalWrite(steperEN, 1);
  digitalWrite(steperDIR, 1);
  attachInterrupt(0, out_sensor_change, CHANGE);
  TCCR1A = 0;                  //将整个TCCR1A寄存器设置为0
  TCCR1B = 0;                  //将整个TCCR1B寄存器设置为0
  TIMSK1 &= (~(1 << OCIE1A));  //ISR disable
  //TCCR0A=0;
  //TCCR0B=_BV(CS01)|_BV(CS00); //1/64
  //TIMSK0 &= (~(1 << TOIE0));  //'delay' ISR disable
  //TCNT0=6;
  //cli();//will stop the below delay and system dead
  TCNT1 = 0;                                          //将计数器值初始化为0
  TCCR1B |= (1 << WGM12);                             //打开CTC模式
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);  //设置CS11位为1(8倍预分频)
  //TIMSK1 |= (1 << OCIE1A);
  OCR1A = pgm_read_word_near(low_speed_table + 0);
  //flashing(1000, 500, 2);
#ifdef screen_enable
#ifdef SSD1306
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.setTextColor(SSD1306_WHITE);
#endif
#ifdef SH1107
  display.begin(SCREEN_ADDRESS, true);  // Address 0x3C default
  display.setTextColor(SH110X_WHITE);
  display.setRotation(1);  //need to rotate 90 for SH1107 in this case
#endif
  display.setTextSize(2);  // Draw 1X-scale text
  display.clearDisplay();
  draw_bat();
  display.setCursor(5, 24);
  display.println(F("GOODLUCK"));
  display.display();
  delay(800);
#ifdef SH1107
  for (byte i = 0; i < 32; i++) {
    rot_eyes();
    delay(30);
  }
  attachInterrupt(1, encoder_move, CHANGE);
  eyes_roll();
#endif
  menu_1();
#endif
}

void eyes_roll() {
  uint16_t blink = 0;
  while (digitalRead(rotator_go)) {
    if (encoder_pos > 100) {
      encoder_pos = 100;
      dir = AC;
      blink = 0;
      rot_eyes();
    } else if (encoder_pos < 100) {
      encoder_pos = 100;
      dir = CW;
      blink = 0;
      rot_eyes();
    }
    delay(6);
    blink++;
    if (blink > 1000) {//blink
      blink = 0;
      display.clearDisplay();
      display.fillRoundRect(6, 36, 28, 16, 8, 1);
      display.fillRoundRect(94, 36, 28, 16, 8, 1);
      display.display();
      delay(130);
      display.clearDisplay();
      display.fillRoundRect(6, 41, 28, 6, 3, 1);
      display.fillRoundRect(94, 41, 28, 6, 3, 1);
      display.display();
      delay(130);
      display.clearDisplay();
      display.fillRoundRect(6, 36, 28, 16, 8, 1);
      display.fillRoundRect(94, 36, 28, 16, 8, 1);
      display.display();
      delay(90);
      rot_eyes();
    }
  }
}

void rot_eyes() {
  display.clearDisplay();
  static uint8_t eye1x = 12;
  static uint8_t eye1y = 44;
  static uint8_t eye2x = 100;
  if (dir) {
    if ((eye1y <= 44) && (eye1x < 28)) {
      eye1x++;
      eye2x++;
    } else {
      eye1x--;
      eye2x--;
    }
    if ((eye1x <= 20) && (eye1y < 52)) {
      eye1y--;
    } else {
      eye1y++;
    }
  } else {
    if ((eye1y <= 44) && (eye1x > 12)) {
      eye1x--;
      eye2x--;
    } else {
      eye1x++;
      eye2x++;
    }
    if ((eye1x <= 20) && (eye1y > 36)) {
      eye1y++;
    } else {
      eye1y--;
    }
  }
  display.fillCircle(20, 44, 14, 1);
  display.fillCircle(108, 44, 14, 1);
  display.fillCircle(eye1x, eye1y, 5, 0);
  display.fillCircle(eye2x, eye1y, 5, 0);
  display.display();
}

void flashing(int i, int j, int k) {  //no led flash for v2-1
#ifdef pcb_industry_v1
  for (int x = 0; x < k; x++) {
    digitalWrite(LEDPIN, 1);
    delay(j);
    digitalWrite(LEDPIN, 0);
    delay(i);
  }
#endif
}

void out_sensor_change() {
  loaded = !loaded;
  //no matter what's previous status, start to accel
}

void encoder_move() {
#ifdef screen_enable
  uint8_t alv = digitalRead(rotator_a);
  uint8_t blv = digitalRead(rotator_b);
  if (encoderflag == 0 && alv == LOW) {
    CW_1 = blv;
    encoderflag = 1;
  }
  if (encoderflag && alv) {
    CW_2 = !blv;
    if (CW_1 && CW_2) {
      encoder_pos--;
      }  //emergency stop
    if (CW_1 == false && CW_2 == false) {
      encoder_pos++;
    }
    encoderflag = 0;
  }
#endif
}

ISR(TIMER1_COMPA_vect) {
  //accel mode, index_acc = x; twice_coe=1; index_acc +1 and steps + 1 every two PB0 inverse
  static bool ticks = 1;              //改为静态局部变量
  static bool twice_coe = 1;          //改为静态局部变量
  static uint8_t index_low_acc = 0;   //实时速度在加速表位置
  static uint8_t index_high_acc = 0;  //实时速度在加速表位置
  static int step_count = 0;          //1536; //步数计数
  //初段加速时不需要记步；给一个归零flag;
  if (ticks)  //在ticks=1进行OCR1A赋值得到时长一致的ticks //tick0, 高电平起步才是完整第一步，这里只有半步，暂时没影响，不更改
  {
    PORTB ^= (1 << 1);  //00000010 异或，pin9在第二位
    twice_coe = !twice_coe;
    if (twice_coe) {
      step_count++;
      if (step_count > loopstep) {
        if (mode_type == mode_1by1) { step_count = 0; }
      }
      switch (flag) {
        case CHECK:
          if (step_count == check_step) {  //in case >=, when load quick, and flag -> accel, will activate the checkpoint1 加载时标志位变成accel, 但是step_count大于check，point会置1，跳出第一个等待循环
            check_point = 1;
            if (mode_type == mode_1by1) {
              flag = SLIP;
            } else if (mode_type == mode_random) {
              flag = HIGH_DECEL;
            }
          }
          break;

        case SLIP:
          if (step_count >= slip_step) {  //must be >= could be interrupt by hardware interrupt
                                          //if (loaded) {
                                          //} else {
            if (high_accel_step) {
              flag = HIGH_DECEL;
            } else {
              flag = LOW_DECEL;
            }
            //}
          }
          break;

        case LOW_ACCEL:
          if (index_low_acc == low_accel_step) {
            if (high_accel_step) { flag = HIGH_ACCEL; }  //in case high_accel>0
            else {
              flag = CHECK;  //by highaccel step +1, flag change, and when check the actual step is accel step +2
            }
          } else {
            index_low_acc++;
            OCR1A = pgm_read_word_near(low_speed_table + index_low_acc);
          }
          break;

        case HIGH_ACCEL:
          if (index_high_acc == high_accel_step) {
            flag = CHECK;
          } else {
            index_high_acc++;
            OCR1A = pgm_read_word_near(high_speed_table + index_high_acc);
          }
          break;

        case HIGH_DECEL:
          if (index_high_acc == 0) {
            flag = LOW_DECEL;
          } else {
            index_high_acc--;
            OCR1A = pgm_read_word_near(high_speed_table + index_high_acc);
          }
          break;

        case LOW_DECEL:
          if (index_low_acc == 1) {
            flag = STOP;
          } else {
            index_low_acc--;
            OCR1A = pgm_read_word_near(low_speed_table + index_low_acc);
          }
          break;

        case STOP:
          step_count = 0;
          rotating = 0;
          index_low_acc = 0;
          TIMSK1 &= (~(1 << OCIE1A));
          digitalWrite(steperEN, 1);
          break;

        case COUNTRESET:
          step_count = 0;
          flag = SLIP;
          break;
      }
    }
    ticks = !ticks;
  } else {
    ticks = !ticks;  //在ticks=0 赋值,且初始电平为低电平时长为前后两种拼接
  }
}

void speed_table_lookup() {
  if (maxfqy < pgm_read_word_near(low_speed_table + 255)) {
    if (maxfqy < pgm_read_word_near(high_speed_table + 255)) {
      FC_print(10);
      return;
    } else {
      for (byte i = 255; i >= 0; i--)  //to check the maxfqy first
      {
        if (maxfqy <= pgm_read_word_near(high_speed_table + i)) {
          high_accel_step = i;
          low_accel_step = 255;
          break;
        }
      }
    }
  } else {
    for (byte i = 255; i >= 0; i--)  //to check the maxfqy first
    {
      if (maxfqy <= pgm_read_word_near(low_speed_table + i)) {
        low_accel_step = i;
        high_accel_step = 0;
        break;
      }
    }
  }
}

void stoprun() {
  digitalWrite(motora1, 1);
  digitalWrite(motora2, 1);
  flag = HIGH_DECEL;
  mode_type = 9;
  delay(200);
  digitalWrite(motora1, 0);
  digitalWrite(motora2, 0);
#ifdef record_time
  for (int i = 0; i < t; i++) {
    Serial.println(duration[i]);
    delay(5);
  }
  t = 0;
#endif
}

void softload() {
  uint8_t i = 255;
  uint16_t j = 255;
  digitalWrite(motora2, 1);
  digitalWrite(motora1, 1);
  while (loaded == 0) {
    if (i > 0) { i = i - 5; }
    analogWrite(motora1, i);
    j--;
    if (j < 0) {
      FC_print(1);
      return;
    }
    delay(5);
  }
#ifdef record_time
  duration[t] = j;  //(255-j)*5= actual load time
  t++;
#endif
}

void softshoot() {
  uint8_t i = 155;
  uint16_t j = 50;
  digitalWrite(motora2, 1);
  digitalWrite(motora1, 1);
  while (loaded) {
    if (i > 0) { i = i - 5; }
    analogWrite(motora1, i);
    j--;
    if (j < 0) {
      FC_print(2);
      return;
    }
    delay(5);
  }
#ifdef record_time
  duration[t] = j;  //(255-j)*5= actual load time
  t++;
#endif
}

void firstcard() {                                     //no timeout check yet, no goon mode yet
  if (!goon) { totalcards = totalcards - holdcards; }  //to recaculate totalcard after boardcast, for mod0
  loaded = !digitalRead(outer_sensor);
  if (digitalRead(cardin)) {
    FC_print(0);
    return;
  }
  t_start = millis();
  //shooted = !loaded;
  //to reset the check step here for mod0
  if (loaded) {
#ifdef record_time
    duration[t] = 0;  //0 to indicate already loaded
    t++;
#endif
  } else {
    //softload();
    digitalWrite(motora2, 1);
    digitalWrite(motora1, 0);
    while(!loaded);
    if (startover) {
      return;
    }
  }
  digitalWrite(motora2, 1);
  digitalWrite(motora1, 0);
  shoot_check(250,2);
  //softshoot(); The PWM outputs generated on pins 5 and 6 will have higher-than-expected duty cycles. 
  //This is because of interactions with the millis() and delay() functions, which share the same internal
  //timer used to generate those PWM outputs. This will be noticed mostly on low duty-cycle settings (e.g. 0 - 10)
  //and may result in a value of 0 not fully turning off the output on pins 5 and 6
  if (startover) { return; }
  //smartspeedctrl();
  slip_step = loopstep - (high_accel_step + low_accel_step);
  check_step = slip_step - 33000 / maxfqy * players;  //180ms how take how many steps, per player step -
  if (check_step < 3) { check_step = 3; }
  check_step = check_step + high_accel_step + low_accel_step;  //to set the first card compensate step, in case random, to reset in random mode
  cardout++;
  if (digitalRead(cardin)) {
    FC_print(0);
    return;
  }                          //no 2nd card, quit
  load_check(250, 1);        //2nd card load
  digitalWrite(motora1, 1);  //fastbreak for the 1st
  digitalWrite(steperEN, 0);
  digitalWrite(steperDIR, dir);
  //rotating = 1;
  flag = LOW_ACCEL;
  check_point = 0;
  TIMSK1 |= (1 << OCIE1A);  //start to rotate
  while (check_point == 0)
    ;  //to reach the check point
  flag = COUNTRESET;
  //loaded = 1;                                     //don't decel and stop
  check_step = low_accel_step + high_accel_step + 3;  //reset the check point, step+1转high, step+2转flag check,step+3进入check flag;
}

void lastcard_compensate() {
  check_step = check_step + 200;  //slip_step - 10000 / maxfqy * players;  //180ms how take how many steps, per player step -
}

void remaincard() {
  digitalWrite(motora1, 1);
  digitalWrite(motora2, 1);
  check_step = slip_step - 30000 / maxfqy * players;  //180ms how take how many steps, per player step -
  flag = LOW_ACCEL;
  check_point = 0;
  while (check_point == 0)
    ;
  flag = HIGH_DECEL;
  delay(200);
  digitalWrite(motora1, 0);
  digitalWrite(motora2, 1);
  for (uint8_t i = 0; i < holdcards; i++) {
    if (digitalRead(cardin) == 1) {
      FC_print(0);
      return;
    }
    load_check(180, 1);
    if (startover) { return; }
    shoot_check(200, 1);
    if (startover) { return; }
  }
  digitalWrite(motora1, 1);
  digitalWrite(motora2, 1);
  FC_print(6);
}

void shoot_check(uint8_t j, uint8_t k) {
  //TIMSK0 &= (~(1 << TOIE0));
  //time0count = 0;
  //TIMSK0 |= (1 << TOIE0);
  timeout=0;
  while (loaded) {
    if ( timeout > j) {  //time0count
      FC_print(k);
      return;
    }
    timeout++;
    delay(1);
  }
#ifdef record_time
  duration[t] = timeout;
  t++;
#endif
  //loaded = 0;
}

void load_check(uint16_t j, uint8_t k) {
  //TIMSK0 &= (~(1 << TOIE0));
  //time0count = 0;
  //TIMSK0 |= (1 << TOIE0);
  timeout=0;
  while (loaded == 0) {
    if (timeout > j) {  //
      FC_print(k);
      return;
    }
    timeout++;
    delay(1);
  }
#ifdef record_time
  duration[t] = timeout;
  t++;
#endif
}

void card_shoot() {
  digitalWrite(motora1, 0);
  if (rotator_go==0){FC_print(9);while(rotator_go==0);return;}
  //digitalWrite(motora2, 1);
  shoot_check(250, 2);
  if (startover) { return; }
  cardout++;
  if (flag == STOP) {
    FC_print(2);
    return;
  }
  if ((cardout + 1) < totalcards) {
    ;
  } else if ((cardout + 1) == totalcards) {
    if (holdcards == 0)  //in case the real last card
    { lastcard_compensate(); }
  } else {
    if (holdcards > 0) {
      if (digitalRead(cardin)) {
        FC_print(0);
        return;
      } else {
        remaincard();
        return;
      }
    } else {
      FC_print(6);
      return;
    }
  }
  if (digitalRead(cardin)) {
    FC_print(0);
    return;
  }
  load_check(180, 1);
  if (startover) { return; }
  digitalWrite(motora1, fast_break);
  //digitalWrite(motora2, fast_break);
  if (flag == STOP) {
    //rotating = 1;      //to reset rotating flag
    flag = LOW_ACCEL;  //later to set up speed tuning
    digitalWrite(steperEN, 0);
    TIMSK1 |= (1 << OCIE1A);
    //FC_print(1);
    //return;
  } else {
    flag = LOW_ACCEL;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mode_type == mode_1by1) {
    firstcard();
    ;
    while (mode_type == mode_1by1) {
      while (check_point == 0)
        ;
      card_shoot();
      check_point = 0;
      if (startover) { break; }
    }
    mode_type = 9;
  } else if (mode_type == mode_random) {
    random_mode();
    mode_type = 9;
  } else if (startover) {
    startover = 0;
    delay(100);
  }
#ifdef ble_enable
  else if (Serial.available() > 0) {
    modeset();
    if (startover) { return; }
  }
#endif
#ifdef screen_enable
  RotatorCheck();
#endif
}

void batcheck() {
  bat = analogRead(volread);
  if (bat > 801) {  //860 is real full, 5% compensation acc. to measurement,820 is full
    bat = 801;
  } else if (bat < 701) {  //736 is 7.2v, 5% compensation acc. to measurement
    display.clearDisplay();
    face_lowbat();
    display.display();
    while (1) {
      delay(1000);
    }
  }
  bat = bat - 701;
  bat = map(bat, 0, 100, 0, 4);
}

void FC_print(byte i) {
#ifdef ble_enable
  startover = 1;
  switch (i) {
    case 0:
      stoprun();
      Serial.println((String) "FC00" + (holdcards + totalcards - cardout) + "CARDS MISSING");  //FC00:SOCKET EMPTY
      break;
    case 1:
      stoprun();
      Serial.println((String) "FC01 REMAIN CARDS=" + (holdcards + totalcards - cardout));  //FC01: LOAD FAILED
      break;
    case 2:
      stoprun();
      Serial.println((String) "FC02 REMAIN CARDS=" + (holdcards + totalcards - cardout));  //FC02:SHOOT TIMEOUT
      break;
    case 5:
      flashing(600, 200, 2);
      Serial.println((String) "Mod" + mode_type + " Cd" + totalcards + " H=" + holdcards + " P=" + players + " Spd" + maxfqy + " Bat=" + bat + " SW" + SW_V);
      break;
    case 4:
      stoprun();
      Serial.println((String) "FC04");  //FC04:TOO MUCH LOAD STUCK
      break;
    case 6:
      t_total = millis() - t_start;
      stoprun();
      flashing(500, 500, 3);
      Serial.println((String) "Set In" + t_total + "ms, Enjoy");
      break;
    case 10:
      Serial.println("FC10");  //FC10:It's not a valid command/improper setup
      break;
  }
#endif
#ifdef screen_enable
  stoprun();
  startover = 1;
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(1, 1);
  switch (i) {
    case 0:
      display.println(F("NOCARD"));
      face_error();
      break;  //display.setCursor(5, 24);display.println(string(holdcards + totalcards - cardout));display.setCursor(45, 24);display.println(F("MISSING"));
    case 1:
      display.println(F("LOADSTUCK"));
      face_sad();
      break;
    case 2:
      display.println(F("SHOOTERROR"));
      face_sleepy();
      break;
    case 6:
      display.println(F("ENJOY!"));
      face_happy();
      break;
    case 9:
      display.println(F("PAUSE"));
      face_surprise();
      break;
    default: break;
  }
  display.display();
#endif
}

#ifdef screen_enable
void RotatorCheck() {
  uint8_t longpush = 0;
  while (1) {
    if (digitalRead(rotator_go) == 0) { break; }
    if (encoder_pos > 101) {
      encoder_pos = 100;
      rotaryevent(2);
      button_on = 2;
    } else if (encoder_pos < 99) {
      encoder_pos = 100;
      rotaryevent(0);
      button_on = 0;
    }
  }
  while (digitalRead(rotator_go) == 0) {
    longpush++;
    delay(10);
    if (longpush > 250) { break; }
  }
  if (longpush > 40) {
    rotaryevent(3);
  } else {
    rotaryevent(1);
  }
}

void rotaryevent(uint8_t i) {

  switch (i)  //获取按键对应序号
  {
    case 1:
      setup_save(funIndex);
      funIndex = menu[funIndex].forward;
      break;
    case 3: funIndex = menu[funIndex].back; break;
    case 2: funIndex = menu[funIndex].down; break;
    case 0: funIndex = menu[funIndex].up; break;
  }
  current = menu[funIndex].operation;  //根据需要获取对应需要执行的函数
  (*current)();                        //执行获取到的函数
}

void setup_save(int i) {
  switch (funIndex) {
    case 0: mode_select = funIndex; break;
    case 1: mode_select = funIndex; break;
    case 2: mode_select = funIndex; break;
    case 3: mode_select = funIndex; break;
    case 4: mode_select = funIndex; break;
    case 5: goon = 0; cardout = 0; break;
    case 6: goon = 1; break;
    case 9: coe_select = 0; break;
    case 10: coe_select = 1; break;
    case 11: coe_select = 2; break;
    case 12: coe_select = 3; break;
    case 13: coe_select = 4; break;
    default: break;
  }
}

void menu_1() {  //mode selection
  display.clearDisplay();
  display.setTextSize(1);
  display.drawBitmap(56 + 40 * (button_on - 1), 21, Ico_table[funIndex], 40, 40, 1);
  display.drawBitmap(56 - 40 * (button_on - 1), 21, Ico_table[((funIndex + 4 - button_on) % 5)], 40, 40, 1);
  draw_bat();
  display.display();
  delay(100);
  display.clearDisplay();
  display.drawBitmap(44, 21, Ico_table[funIndex], 40, 40, 1);
  display.drawBitmap(-20, 21, Ico_table[((funIndex + 4) % 5)], 40, 40, 1);
  display.drawBitmap(108, 21, Ico_table[((funIndex + 1) % 5)], 40, 40, 1);
  draw_bat();
  switch (funIndex) {
    case 0:
      display.setCursor(0, 0);
      display.println(F("GUANDAN"));
      break;
    case 1:
      display.setCursor(0, 0);
      display.println(F("DOUDIZHU"));
      break;
    case 2:
      display.setCursor(0, 0);
      display.println(F("BLACK5"));
      break;
    case 3:
      display.setCursor(0, 0);
      display.println(F("FREEMODE1"));
      break;
    case 4:
      display.setCursor(0, 0);
      display.println(F("FREEMODE2"));
      break;
  }
  display.display();
}

void menu_2() {  //action selection
  display.clearDisplay();
  display.setTextSize(1);
  display.drawBitmap(56 + 40 * (button_on - 1), 21, Ico_table2[(funIndex - 5)], 40, 40, 1);
  display.drawBitmap(56 - 40 * (button_on - 1), 21, Ico_table2[((funIndex - 3 - button_on) % 3)], 40, 40, 1);
  draw_bat();
  display.display();
  delay(100);
  display.clearDisplay();
  display.drawBitmap(44, 21, Ico_table2[(funIndex - 5)], 40, 40, 1);
  display.drawBitmap(-20, 21, Ico_table2[((funIndex - 3) % 3)], 40, 40, 1);
  display.drawBitmap(108, 21, Ico_table2[((funIndex - 4) % 3)], 40, 40, 1);
  draw_bat();
  switch (funIndex) {
    case 5:
      display.setCursor(1, 1);
      display.println(F("RUN"));
      break;
    case 6:
      display.setCursor(1, 1);
      display.println(F("CONTINUE"));
      break;
    case 7:
      display.setCursor(1, 1);
      display.println(F("SETUP"));
      break;
  }
  display.display();
}

void draw_bat() {
  batcheck();
  //display.setCursor(96, 0);display.println(bat);
  display.drawRect(111, 2, 15, 8, 1);  //outline
  if (bat > 0) {
    for (byte i = 0; i < bat; i++) { display.fillRect(113 + i * 3, 4, 2, 4, 1); }
  }
  display.drawLine(126, 5, 126, 7, 1);
}

void menu_running() {
  totalcards = mode_coe[mode_select][0];
  holdcards = mode_coe[mode_select][2];
  players = mode_coe[mode_select][1];
  maxfqy = mode_coe[mode_select][3];
  speed_table_lookup();
  loopstep = basestep / players;
  slip_step = loopstep - (high_accel_step + low_accel_step);  // slip until that step, not pure slip step
  startover = 0; //a flag can be reset in BLE mode, need to reset here
  display.clearDisplay();
  face_workhard();
  display.display();
  mode_type = mode_coe[mode_select][4];
  delay(500);
}

void mode_setup() {
  display.clearDisplay();
  display.setTextSize(2);
  char buffer[20];  // 确保缓冲区足够大以容纳字符串
  display.setCursor(2, 2);
  strcpy_P(buffer, (const char *)str_coe[funIndex % 5]);
  display.println(buffer);
  display.setTextColor(SH110X_BLACK, SH110X_WHITE);
  display.setCursor(2, 23);
  strcpy_P(buffer, (const char *)str_coe[(funIndex + 1) % 5]);
  display.println(buffer);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(2, 44);
  strcpy_P(buffer, (const char *)str_coe[(funIndex + 2) % 5]);
  display.println(buffer);
  //display.fillRoundRect(80, 22, 16, 16, 7, 1);
  //draw_bat();
  display.display();
}

void coe_setup() {
  display.clearDisplay();
  display.setTextSize(1);
  if (funIndex == 15) {
    mode_coe[mode_select][coe_select]--;
  } else if (funIndex == 16) {
    mode_coe[mode_select][coe_select]++;
  }
  display.setCursor(3, 3);
  uint8_t mode_num = mode_coe[mode_select][coe_select];
  uint8_t y_pos;
  switch (coe_select) {
    char buffer[20];
    case 0:
      strcpy_P(buffer, (const char *)str_coe[0]);
      display.println(buffer);
      mode_num = constrain(mode_num, 2, 216);
      break;
    case 1:
      strcpy_P(buffer, (const char *)str_coe[1]);
      display.println(buffer);
      mode_num = constrain(mode_num, 2, 8);
      break;
    case 2:
      strcpy_P(buffer, (const char *)str_coe[2]);
      display.println(buffer);
      mode_num = constrain(mode_num, 0, mode_coe[mode_select][0]);
      break;
    case 3:
      strcpy_P(buffer, (const char *)str_coe[3]);
      display.println(buffer);
      mode_num = constrain(mode_num, 28, 99);
      break;
    case 4:
      strcpy_P(buffer, (const char *)str_coe[4]);
      display.println(buffer);
      mode_num = constrain(mode_num, mode_1by1, mode_random);
      break;
  }
  if (mode_num>99){y_pos = 30;}
  else if (mode_num>9){y_pos = 42;}
  else {y_pos = 55;}
  mode_coe[mode_select][coe_select] = mode_num;
  display.setTextSize(4);
  display.setCursor(y_pos, 20);
  display.println(mode_num);
  display.display();
}
#endif

void fisher_yates() {
  randomSeed(analogRead(volread));  //to random the random seed
  byte j = 0;
  byte k = 0;
  byte i = 0;
  byte cardnum[totalcards];
  for (i = 0; i < totalcards; i++) {
    cardnum[i] = i;
  }

  for (i = 0; i < totalcards; i++)  //i initial value and step random may generate more boom
  {
    j = random(i, totalcards);  //will generate a num 0-totalcards-1;
    k = cardnum[i];
    cardnum[i] = cardnum[j];
    cardnum[j] = k;
  }
  j = 0;
  for (i = 0; i < (totalcards - holdcards); i++) {
    randomsq[cardnum[i]] = j;
    j++;
    if (j == players) { j = 0; }
  }
  if (holdcards > 0)  //to allocation the last few cards to the holdcards position;
  {
    for (i = totalcards - holdcards; i < totalcards; i++)  //e.g.54-3, then 51,52,53 possition been allocated
      randomsq[cardnum[i]] = players;
  }
  //for (i = 0; i < totalcards; i++){Serial.print(randomsq[i]);}//debug
}

void startstop() {
  rotating = 1;
  digitalWrite(steperEN, 0);
  flag = LOW_ACCEL;
  TIMSK1 |= (1 << OCIE1A);  //start to rotate
  while (rotating)
    ;  //{delay(500);Serial.print(flag);}
}

void random_mode() {
    if (digitalRead(cardin))  //in case no more card, stop rolling imediately
    {
      FC_print(0);
      return;
    }
  t_start = millis();
  int halfround = int(players / 2);
  int half_step = loopstep / 2;
  int delta;
  loaded = !digitalRead(outer_sensor);  // if 1, no card = shooted, and not loaded
  uint8_t abs_angle;
  if (goon == 0) {
    fisher_yates();                //to get the random sequence
    if (randomsq[0] == players) {  //in case first card at the holdcard position
      check_step = half_step - high_accel_step - low_accel_step;
      //Serial.print(check_step);
      digitalWrite(steperDIR, AC);
      startstop();
      //holdcards--;
    } else if (randomsq[0] > 0) {
      if (randomsq[0] > halfround) {  //in case first card position closer to AC direction
        abs_angle = players - randomsq[0];
        digitalWrite(steperDIR, AC);
      } else {
        abs_angle = randomsq[0];
        digitalWrite(steperDIR, CW);
      }
      check_step = abs_angle * loopstep - high_accel_step - low_accel_step;
      //Serial.print(check_step);
      startstop();  // move to the 1st card position
    }
    if (!loaded) {  //if not load, to load
      //softload();
      digitalWrite(motora2, 1);
      digitalWrite(motora1, 0);
      while(!loaded);
      if (startover) {
        return;
      }
    } else {
      digitalWrite(motora1, 1);
      digitalWrite(motora2, 1);
    }
    digitalWrite(motora1, 0);
    shoot_check(250, 2);
    if (startover) {
      return;
    }
    cardout++;
    if (digitalRead(cardin))  //in case no more card, stop rolling imediately
    {
      FC_print(0);
      return;
    }
    load_check(250, 1);
    if (startover) {
      return;
    }
  } else {
    //softload();
    digitalWrite(motora2, 1);
    digitalWrite(motora1, 0);
    while(!loaded);
    if (startover) {
      return;
    }
  }
  digitalWrite(motora1, HIGH);
  byte j;
  byte k;
  for (byte i = cardout; i < totalcards; i++) {
    if (rotator_go==0){FC_print(9);while(rotator_go==0);return;}
    if (digitalRead(cardin))  //in case no more card, stop rolling imediately
    {
      FC_print(0);
      return;
    }
    j = i - 1;
    k = i + 1;
    delta = randomsq[i] - randomsq[j];
    if (delta == 0) {
      ;
    } else {
      if (delta > 0) {
        if (delta > halfround) {
          abs_angle = players - delta;
          dir = AC;
        } else {
          abs_angle = delta;
          dir = CW;
        }
      } else if (delta < 0) {
        if ((0 - delta) > halfround) {
          abs_angle = players + delta;
          dir = CW;
        } else {
          abs_angle = 0 - delta;
          dir = AC;
        }
      }
      check_step = abs_angle * loopstep - high_accel_step - low_accel_step;
      if (randomsq[i] == players) {
        //holdcards--;
        check_step = check_step + half_step - dir * loopstep;
      }                                                                                      //case AC +half_step
      if (randomsq[j] == players) { check_step = check_step + dir * loopstep - half_step; }  //case AC -half_step to compensate previous half position
      digitalWrite(steperDIR, dir);
      startstop();
    }
    digitalWrite(motora1, 0);
    shoot_check(250, 2);
    if (startover) { return; }
    cardout++;
    //Serial.print(cardout);
    if (cardout == totalcards) {
      FC_print(6);
      return;
    }
    load_check(250, 1);  //to put load in this condition, in case need to rotate, to load during the rotation to save 30ms
    if (startover) { return; }
    if (randomsq[i] == randomsq[k]) {
      ;
    } else {
      digitalWrite(motora1, HIGH);
    }
  }
  digitalWrite(motora1, 0);  //to stop the motor in case
  digitalWrite(motora2, 0);
}

#ifdef ble_enable
void modeset() {
  int command[9];
  for (byte i = 0; i < 9; i++) {
    if (Serial.available()) {
      command[i] = Serial.read();
      delay(5);  //go on p0 total card p1 + hold cards p2 + player p3 + maxfqy p4 + direction p5 + shootspeed p6 + mode p7
    } else {
      FC_print(10);
      return;
    }
  }
  while (Serial.read() >= 0)
    ;  //to clear buffer
  goon = command[0];
  if (goon == 0)  //in case a new round
  {
    cardout = 0;                                 // reset cardout count;
    totalcards = command[1];                     //256max
    if (totalcards > 108) { totalcards = 108; }  //to limit the number to 108 during development
    holdcards = command[2];
    players = command[3];
    maxfqy = command[4];
    speed_table_lookup();
    if (startover) {
      return;
    }
    loopstep = basestep / players;
    slip_step = loopstep - (high_accel_step + low_accel_step);  // slip until that step, not pure slip step
    dir = command[5];
    digitalWrite(steperDIR, dir);
    uint8_t speed_coe = command[6];  //basespeed= 180 - speed_coe*7; //need calibration, typical5, for sample C =7 for a trial
    mode_type = command[7];
    fast_break = command[8];  //in case 0
    batcheck();
    if (dir > 1 || players == 0 || players > 8) {
      FC_print(10);
      return;
    }
    FC_print(5);
  } else if (players == 0)  //in case continue mode activated, no need to reset, but must check previous setup done
  {
    FC_print(10);
    return;
  } else {
    if (startover) {  // to judge if it really needs continue mode
      startover = 0;
      mode_type = command[7];
      FC_print(5);
    } else {
      FC_print(10);
      return;
    }
  }
  if (digitalRead(cardin) == 1) {
    FC_print(0);
    return;
  }
}
#endif