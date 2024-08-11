//update on shooting timeout diagnose
//#include <EEPROM.h>
#define screen_enable
#define pcb_industry2
//#define ble_enable
//#define record_time
#define SCREEN_ADDRESS 0x3C                    ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SH110X //SSD1306

#ifdef SSD1306
  #include <Adafruit_SSD1306.h>
  Adafruit_SSD1306 display(128, 64, &Wire, -1);  // I2C / TWI
#endif
#ifdef SH110X
  #include <Adafruit_SH110X.h>
  Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1);
#endif

#ifdef screen_enable
const unsigned char PROGMEM str_guandan[] ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x01,0xFF,0x00,0x00,0x00,0x03,0x78,0xC0,0x00,0x00,0x0C,0xAF,0x20,0x00,0x00,0x1F,
0xDF,0xF0,0x00,0x00,0x3F,0xFF,0xF8,0x00,0x00,0x7F,0xFF,0xFC,0x00,0x00,0x7F,0xFF,0xFC,0x00,0x00,0xFD,0xFF,0xBE,0x00,0x00,0xFF,0xEF,0xFE,0x00,0x00,0xFF,0xC7,0xFE,
0x20,0x00,0xFF,0x83,0xFE,0x30,0x08,0xCF,0xC7,0x9F,0x78,0x0C,0xB7,0xEF,0x6F,0x78,0x1C,0x7B,0x86,0xE7,0xFC,0x1E,0x7F,0xB9,0xFB,0x7C,0x3F,0xFD,0x7F,0xFC,0xFC,0x3F,
0xFE,0x7F,0xFF,0xFC,0x3F,0xFF,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFF,0xF8,0x1F,0xFF,0xFF,0xFF,0xF8,0x1F,0xFF,0xFF,
0xFF,0xF0,0x0F,0xFF,0xFF,0xFF,0xF0,0x0F,0xFF,0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xFF,0xC0,0x03,0xFF,0xFF,0xFF,0xC0,0x03,0xFF,0xFF,0xFF,0x80,
0x01,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x7F,0xFF,0xFC,0x00,0x00,0x1F,0xFF,0xF8,0x00,0x00,0x0F,0xFF,0xE0,0x00,0x00,0x01,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //40x40
static const unsigned char PROGMEM str_doudizhu[] ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x03,0xFF,0xC0,0x00,0x00,0x1F,0xFF,0xF8,0x00,0x00,0x3F,0x81,0xFC,0x00,0x00,0xFC,0x00,0x3F,0x00,0x01,0xF0,
0x00,0x0F,0x80,0x03,0xE0,0x02,0x07,0xC0,0x07,0xC0,0x03,0x03,0xE0,0x0F,0x80,0x03,0x01,0xF0,0x0F,0x00,0xF3,0x00,0xF0,0x1F,0x00,0x73,0x00,0xF8,0x1E,0x00,0x63,0x00,
0x78,0x3E,0x00,0x83,0x00,0x7C,0x3E,0x01,0xE3,0x00,0x7C,0x3C,0x00,0xF3,0x70,0x3C,0x3C,0x00,0xC7,0xF0,0x3E,0x7C,0x01,0xBF,0x00,0x3E,0x7C,0x00,0x73,0x00,0x3E,0x7C,
0x01,0xC3,0x00,0x3E,0x7C,0x07,0x03,0x00,0x3E,0x7E,0x1E,0x03,0x00,0x7E,0x7E,0x1C,0x03,0x00,0x7E,0x7E,0x00,0x03,0x00,0x7E,0x3F,0x00,0x03,0x00,0xFC,0x3F,0x00,0x03,
0x00,0xFC,0x3F,0x80,0x03,0x01,0xFC,0x3F,0xC0,0x03,0x03,0xFC,0x3F,0xE0,0x02,0x07,0xFC,0x1F,0xF0,0x00,0x0F,0xF8,0x1F,0xFC,0x00,0x3F,0xF8,0x0F,0xFF,0x81,0xFF,0xF0,
0x07,0xFF,0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xFF,0xC0,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x03,
0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM str_tao[] ={0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x01,0xFF,0x80,0x00,0x00,0x03,0xFF,0xC0,0x00,0x00,0x07,0xFF,0xE0,0x00,0x00,0x0F,
0xFF,0xF0,0x00,0x00,0x1F,0xFF,0xF8,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x7F,0xFF,0xFE,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x01,0xFF,0xFF,0xFF,0x80,0x03,0xFF,0xFF,0xFF,
0xC0,0x07,0xFF,0xFF,0xFF,0xE0,0x0F,0xFF,0xFF,0xFF,0xF0,0x1F,0xFF,0xFF,0xFF,0xF0,0x1F,0xFF,0xFF,0xFF,0xF8,0x3F,0xFF,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFF,0xFC,0x7F,
0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFE,0x3F,0xFF,0xFF,
0xFF,0xFC,0x3F,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFF,0xF8,0x0F,0xFF,0xFF,0xFF,0xF0,0x0F,0xFF,0xFF,0xFF,0xF0,0x07,0xFF,0xFF,0xFF,0xE0,0x01,0xFF,0x7E,0xFF,0x80,
0x00,0xFC,0x7E,0x7E,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x01,0xFF,0x80,0x00,0x00,0x01,0xFF,0x80,0x00,0x00,0x03,0xFF,0xC0,0x00,0x00,0x03,
0xFF,0xC0,0x00,0x00,0x07,0xFF,0xE0,0x00};
const unsigned char PROGMEM str_xin[] ={0x00,0x00,0x00,0x00,0x00,0x01,0xF8,0x00,0x0F,0x80,0x07,0xFE,0x00,0x3F,0xE0,0x0F,0xFF,0x00,0x7F,0xF0,0x1F,0xFF,0x80,0xFF,0xF8,0x3F,0xFF,0xC1,0xFF,0xFC,0x7F,0xFF,
0xC1,0xFF,0x7E,0x7F,0xFF,0xE3,0xFF,0xBE,0xFF,0xFF,0xF7,0xFF,0xDF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,
0xF7,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0xFE,0x7F,
0xFF,0xFF,0xFF,0xFE,0x3F,0xFF,0xFF,0xFF,0xFC,0x1F,0xFF,0xFF,0xFF,0xF8,0x0F,0xFF,0xFF,0xFF,0xF0,0x07,0xFF,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xFF,0xC0,0x01,0xFF,0xFF,
0xFF,0x80,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x7F,0xFF,0xFE,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x1F,0xFF,0xF8,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x07,0xFF,0xE0,0x00,
0x00,0x03,0xFF,0xC0,0x00,0x00,0x01,0xFF,0x80,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
static const unsigned char PROGMEM str_mei[] ={0x00,0x00,0xFF,0x00,0x00,0x00,0x03,0xFF,0xC0,0x00,0x00,0x07,0xFF,0xE0,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0x1F,0xFF,0xF8,0x00,0x00,0x1F,
0xFF,0xFC,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x1F,0xFF,0xF8,
0x00,0x00,0x1F,0xFF,0xF8,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x00,0xE7,0xFF,0xE7,0x80,0x07,0xFB,0xFF,0xDF,0xE0,0x1F,0xFD,0xFF,0xBF,0xF8,0x3F,0xFF,0xFF,0xFF,0xF8,0x3F,
0xFF,0xFF,0xFF,0xFC,0x7F,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFE,0x3F,0xFF,0xFF,0xFF,0xFC,0x3F,0xFF,0xBD,0xFF,0xFC,
0x1F,0xFF,0x3C,0xFF,0xF8,0x0F,0xFE,0x3E,0x7F,0xF0,0x03,0xF8,0x7E,0x1F,0xC0,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x01,0xFF,0x80,0x00,0x00,0x03,
0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char PROGMEM str_fang[] ={0x00,0x00,0x80,0x00,0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x03,0xE0,0x00,0x00,0x00,0x07,0xF0,0x00,0x00,0x00,0x0F,0xF8,0x00,0x00,0x00,0x1F,0xFC,0x00,0x00,0x00,0x1F,
0xFE,0x00,0x00,0x00,0x3F,0xFF,0x00,0x00,0x00,0x7F,0xFF,0x80,0x00,0x00,0xFF,0xFF,0xC0,0x00,0x01,0xFF,0xFF,0xE0,0x00,0x03,0xFF,0xFF,0xF0,0x00,0x07,0xFF,0xFF,0xF0,
0x00,0x0F,0xFF,0xFF,0xF8,0x00,0x1F,0xFF,0xFF,0xFC,0x00,0x3F,0xFF,0xFF,0xFE,0x00,0x7F,0xFF,0xFF,0xFF,0x00,0x7F,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,
0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xFF,0xFF,0xC0,0xFF,0xFF,0xFF,0xFF,0x80,0x7F,0xFF,0xFF,0xFF,0x80,0x3F,0xFF,0xFF,0xFF,0x00,0x1F,0xFF,0xFF,0xFE,0x00,0x0F,0xFF,0xFF,
0xFC,0x00,0x07,0xFF,0xFF,0xF8,0x00,0x03,0xFF,0xFF,0xF0,0x00,0x03,0xFF,0xFF,0xE0,0x00,0x01,0xFF,0xFF,0xC0,0x00,0x00,0xFF,0xFF,0xC0,0x00,0x00,0x7F,0xFF,0x80,0x00,
0x00,0x3F,0xFF,0x00,0x00,0x00,0x1F,0xFE,0x00,0x00,0x00,0x0F,0xFC,0x00,0x00,0x00,0x07,0xF8,0x00,0x00,0x00,0x03,0xF0,0x00,0x00,0x00,0x01,0xE0,0x00,0x00,0x00,0x00,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char PROGMEM str_play[] ={0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x3F,0xC0,0x00,0x00,0x00,0x3F,0xF0,0x00,0x00,0x00,0x3F,0xFC,
0x00,0x00,0x00,0x3F,0xFF,0x00,0x00,0x00,0x3F,0xFF,0xC0,0x00,0x00,0x3F,0xFF,0xF0,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x3F,0xFF,0xFF,0x00,0x00,0x3F,0xFF,0xFF,0xC0,
0x00,0x3F,0xFF,0xFF,0xF0,0x00,0x3F,0xFF,0xFF,0xFC,0x00,0x3F,0xFF,0xFF,0xFF,0x00,0x3F,0xFF,0xFF,0xFF,0xC0,0x3F,0xFF,0xFF,0xFF,0xF0,0x3F,0xFF,0xFF,0xFF,0xFC,0x3F,
0xFF,0xFF,0xFF,0xFE,0x3F,0xFF,0xFF,0xFF,0xFE,0x3F,0xFF,0xFF,0xFF,0xF8,0x3F,0xFF,0xFF,0xFF,0xE0,0x3F,0xFF,0xFF,0xFF,0x80,0x3F,0xFF,0xFF,0xFE,0x00,0x3F,0xFF,0xFF,
0xF8,0x00,0x3F,0xFF,0xFF,0xE0,0x00,0x3F,0xFF,0xFF,0x80,0x00,0x3F,0xFF,0xFE,0x00,0x00,0x3F,0xFF,0xF8,0x00,0x00,0x3F,0xFF,0xE0,0x00,0x00,0x3F,0xFF,0x80,0x00,0x00,
0x3F,0xFE,0x00,0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x3F,0xE0,0x00,0x00,0x00,0x3F,0x80,0x00,0x00,0x00,0x3E,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char PROGMEM str_continue[] ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x0F,0x80,0x00,0x00,0x00,
0x0F,0xC0,0x00,0x00,0x00,0x0F,0xE0,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,0x00,0x0F,0xF8,0x00,0x5D,0xEF,0xFF,0xFC,0x00,0x5D,0xEF,0xFF,0xFE,0x00,0x5D,0xEF,0xFF,0xFF,
0x00,0x5D,0xEF,0xFF,0xFF,0x80,0x5D,0xEF,0xFF,0xFF,0xC0,0x5D,0xEF,0xFF,0xFF,0xE0,0x5D,0xEF,0xFF,0xFF,0xF0,0x5D,0xEF,0xFF,0xFF,0xF8,0x5D,0xEF,0xFF,0xFF,0xFC,0x5D,
0xEF,0xFF,0xFF,0xFE,0x5D,0xEF,0xFF,0xFF,0xFE,0x5D,0xEF,0xFF,0xFF,0xFC,0x5D,0xEF,0xFF,0xFF,0xF8,0x5D,0xEF,0xFF,0xFF,0xF0,0x5D,0xEF,0xFF,0xFF,0xE0,0x5D,0xEF,0xFF,
0xFF,0xC0,0x5D,0xEF,0xFF,0xFF,0x80,0x5D,0xEF,0xFF,0xFF,0x00,0x5D,0xEF,0xFF,0xFE,0x00,0x5D,0xEF,0xFF,0xFC,0x00,0x00,0x00,0x0F,0xF8,0x00,0x00,0x00,0x0F,0xF0,0x00,
0x00,0x00,0x0F,0xE0,0x00,0x00,0x00,0x0F,0xC0,0x00,0x00,0x00,0x0F,0x80,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char PROGMEM str_setup[] ={0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x7C,0x3E,0x00,0x00,0x00,0xFC,0x3E,0x00,0x00,0x01,0xFE,0x7E,0x00,0x00,0x01,0xFF,0xFE,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,
0xFF,0xFE,0x80,0x00,0x01,0xFE,0x3E,0xFC,0x00,0x3F,0xF0,0x0E,0xFC,0x00,0x3F,0xE7,0xE2,0xFE,0x00,0x7F,0xCF,0xFA,0xFE,0x00,0x7F,0x9F,0xFC,0xFE,0x00,0x7F,0xBF,0xFC,
0xFE,0x00,0x3F,0x3F,0xFC,0xF8,0x00,0x0F,0x3F,0xFE,0xF0,0x00,0x0F,0x3F,0xFE,0xD0,0x00,0x0F,0x3F,0xFE,0x80,0x00,0x0F,0x3F,0xFC,0xA4,0x00,0x78,0x3F,0xFC,0x76,0x00,
0x7C,0x1F,0xF9,0x7A,0x0C,0x7C,0xEF,0xF0,0xFA,0x0F,0x7D,0xF3,0xE0,0xFC,0x0F,0xFF,0xF0,0x0C,0xFC,0x0F,0xC7,0xF2,0x3C,0x00,0x07,0x03,0xE3,0xFC,0x00,0x0E,0x00,0xE3,
0xFC,0x00,0x34,0x00,0xFB,0xFF,0x80,0xF0,0x00,0x7D,0xFC,0x00,0xF8,0x00,0x7C,0x38,0x00,0xF8,0x00,0x7C,0x10,0x00,0xFC,0x00,0xFC,0x00,0x00,0x1E,0x00,0xF0,0x00,0x00,
0x0E,0x01,0xE0,0x00,0x00,0x0F,0x83,0xE0,0x00,0x00,0x1F,0x8F,0xF0,0x00,0x00,0x3F,0xE3,0xE0,0x00,0x00,0x1F,0x78,0x00,0x00,0x00,0x0C,0x7C,0x40,0x00,0x00,0x00,0x7C,
0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x00};
const unsigned char *Ico_table[5] = { str_guandan, str_doudizhu, str_tao, str_xin, str_mei };
const unsigned char *Ico_table2[3] = { str_play, str_continue, str_setup };
uint8_t mode_selection = 2;
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
void menu_setup(void);

KEY_TABLE menu[] = {
  { 0, 4, 1, 0, 5, (*menu_1) },
  { 1, 0, 2, 0, 5, (*menu_1) },
  { 2, 1, 3, 0, 5, (*menu_1) },
  { 3, 2, 4, 0, 5, (*menu_1) },
  { 4, 3, 0, 0, 5, (*menu_1) },
  { 5, 7, 6, 0, 8, (*menu_2) },
  { 6, 5, 7, 0, 8, (*menu_2) },
  { 7, 6, 5, 0, 9, (*menu_2) },
  { 8, 5, 5, 5, 5, (*menu_running) },
  { 9, 10, 10, 5, 5, (*menu_setup) },
  { 10, 9, 9, 5, 5, (*menu_setup) },
};

void random_mode();

//touch panel setup
  #define touchpad1 5
  #define touchpad2 A3
  #define touchpad3 7
  #define touchpad4 6
  uint8_t touchcount1 = 0;
  uint8_t touchcount2 = 0;
  uint8_t touchcount3 = 0;
  uint8_t touchcount4 = 0;
  uint8_t button_on = 0;

#define random_mode_go
#ifdef random_mode_go
#define AC 0  //anti clockwise
#define CW 1  //clockwise
uint8_t randomsq[108];
#endif

#ifdef pcb_industry2
  #define motora1 3  //timer2
  #define motora2 4
  #define outer_sensor 2  //replace by interrupt 0
  #define cardin A1
  #define steperEN 10  //previous was pin3
  #define steperDIR 8
  #define volread A2
  #define LEDPIN 13
#endif

#ifdef pcb_industry1
  #define motora1 3  //timer2
  #define motora2 4
  #define outer_sensor 2  //replace by interrupt 0
  #define cardin A5
  #define steperEN 5  //previous was pin3
  #define steperDIR 10
  #define volread A0
  #define MS1 6
  #define MS2 7
  #define PDN 8
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
  long initime;
  const int basestep = 10560;
  volatile uint8_t flag = STOP;  //电机状态
  uint8_t mode_type = 0;
  #define mode_1by1 1
  #define mode_random 2
  bool fast_break = 1;
  bool goon;
  //volatile bool shooted = 0;
  bool startover = 0;  //flag to indicate any error and break many loops
  volatile bool check_point = 0;
  volatile bool loaded = 0;
  volatile bool rotating = 0;
  //volatile bool time0out =0;
  //volatile int await_ms=0;
  uint8_t players = 0;
  uint8_t maxfqy;
  uint16_t bat;
  volatile uint8_t cardout = 0;
  uint8_t totalcards = 0;
  uint8_t holdcards = 0;
  uint8_t motorspeed = 0;
  //byte index_acc; //to indicate the position in the speed table
String SW_V = "240807";
#ifdef record_time
uint8_t t = 0;
uint8_t duration[216];
#endif


void setup() {
#ifdef screen_enable
  pinMode(touchpad1, INPUT);
  pinMode(touchpad2, INPUT);
  pinMode(touchpad3, INPUT);
  pinMode(touchpad4, INPUT);
#endif
#ifdef ble_enable
  Serial.begin(9600);
#endif
  TWBR = 12;
  pinMode(motora1, OUTPUT);
  pinMode(motora2, OUTPUT);
  pinMode(steperEN, OUTPUT);  //en
  pinMode(volread, INPUT);
  pinMode(9, OUTPUT);  //steper PB0
#ifdef pcb_industry1
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(PDN, OUTPUT);
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(PDN, LOW);
#endif
  pinMode(cardin, INPUT);
  pinMode(outer_sensor, INPUT);
  pinMode(steperDIR, OUTPUT);  //dir
  pinMode(LEDPIN, OUTPUT);
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
  flashing(1000, 500, 2);
#ifdef SSD1306
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.setTextColor(SSD1306_WHITE);
#endif
#ifdef SH110X
  display.begin(SCREEN_ADDRESS, true); // Address 0x3C default
  display.setTextColor(SH110X_WHITE);
#endif
#ifdef screen_enable
  display.setTextSize(2);  // Draw 1X-scale text
  display.clearDisplay();
  for (byte i = 0; i < 65; i = i + 2) {
    display.fillRect(10, i - 2, 40, 40, 0);
    display.drawBitmap(10, i, Ico_table[3], 40, 40, 1);
    display.fillRect(78, i - 42, 40, 42, 0);
    display.drawBitmap(78, i - 40, Ico_table[2], 40, 40, 1);
    display.display();
  }
  for (byte i = 0; i < 41; i = i + 2) {
    display.fillRect(10, i - 2, 40, 40, 0);
    display.drawBitmap(10, i, Ico_table[1], 40, 40, 1);
    display.fillRect(78, i + 22, 40, 42, 0);
    display.drawBitmap(78, i + 24, Ico_table[2], 40, 40, 1);
    display.display();
  }
  for (byte i = 0; i < 64; i = i + 2) {
    display.fillRect(10, i + 39, 40, 40, 0);
    display.drawBitmap(10, i + 40, Ico_table[1], 40, 40, 1);
    display.fillRect(78, i, 40, 40, 0);
    display.drawBitmap(78, i, Ico_table[0], 40, 40, 1);
    display.display();
  }
  draw_bat();
  display.setCursor(5, 24);
  display.println(F("GOODLUCK"));
  display.display();
  delay(1000);
  menu_1();
#endif
}

void flashing(int i, int j, int k) {
  for (int x = 0; x < k; x++) {
    digitalWrite(LEDPIN, 1);
    delay(j);
    digitalWrite(LEDPIN, 0);
    delay(i);
  }
}

void out_sensor_change() {
  loaded = !loaded;
  //no matter what's previous status, start to accel
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
        if (mode_type == mode_1by1) { step_count = 0;}
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
  mode_type = 0;
#ifdef record_time
  for (int i = 0; i < t; i++) {
    Serial.println(duration[i]);
    delay(5);
  }
  t = 0;
#endif
  delay(200);
  digitalWrite(motora1, 0);
  digitalWrite(motora2, 0);
}

void softload() {
  uint8_t i = 255;
  uint8_t j = 255;
  digitalWrite(motora2, 1);
  while (loaded == 0) {
    if (i > 0) { i = i - 5; }
    analogWrite(motora1, i);
    j = j - 1;
    if (j == 0) { return; }
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
  //shooted = !loaded;
  //to reset the check step here for mod0

  if (loaded) {
#ifdef record_time
    duration[t] = 0;  //0 to indicate already loaded
    t++;
#endif
    digitalWrite(motora2, 1);  //soft start dc motor
    digitalWrite(motora1, 0);
  } else {
    softload();
    if (loaded == 0) {
      FC_print(1);
      return;
    }
  }
  shoot_check(250, 2);
  if (startover) { return; }
  uint16_t maxfqy_check=time0count*200/slip_step*2; //to calculate proper maxfqy to support continues smooth running
  if(maxfqy_check>maxfqy){maxfqy=maxfqy_check;} //need further diagnose  - in case gap is large and repeated
  slip_step = loopstep - (high_accel_step + low_accel_step);
  check_step = slip_step - 30000 / maxfqy * 3;  //180ms how take how many steps, per player step -
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
  //rotating = 1;
  flag = LOW_ACCEL;
  check_point = 0;
  TIMSK1 |= (1 << OCIE1A);  //start to rotate
  while (check_point == 0);  //to reach the check point
  flag = COUNTRESET;
  //loaded = 1;                                     //don't decel and stop
  check_step = low_accel_step + high_accel_step + 3;  //reset the check point, step+1转high, step+2转flag check,step+3进入check flag;
}

void lastcard_compensate() {
  check_step = check_step + 200;  //slip_step - 10000 / maxfqy * players;  //180ms how take how many steps, per player step -
}

void remaincard() {
  digitalWrite(motora1, fast_break);
  digitalWrite(motora2, fast_break);
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
  digitalWrite(motora1, fast_break);
  digitalWrite(motora2, fast_break);
  FC_print(6);
}

void shoot_check(uint8_t j, uint8_t k) {
  TIMSK0 &= (~(1 << TOIE0));
  time0count = 0;
  TIMSK0 |= (1 << TOIE0);
  while (loaded) {
    if (time0count > j) {  //
      FC_print(k);
      return;
    }
  }
#ifdef record_time
  duration[t] = time0count;
  t++;
#endif
  //loaded = 0;
}

void load_check(uint16_t j, uint8_t k) {
  TIMSK0 &= (~(1 << TOIE0));
  time0count = 0;
  TIMSK0 |= (1 << TOIE0);
  while (loaded == 0) {
    if (time0count > j) {  //
      FC_print(k);
      return;
    }
  }
#ifdef record_time
  duration[t] = time0count;
  t++;
#endif
}

void card_shoot() {
  digitalWrite(motora1, 0);
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
#ifdef record_time
  duration[t] = time0count;
  t++;
#endif
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
    mode_type = 0;
  } else if (mode_type == mode_random) {
    random_mode();
  } else if (startover) {
    startover = 0;
    delay(500);
  }
#ifdef ble_enable
  else if (Serial.available() > 0) {
    modeset();
    if (startover) { return; }
  }
#endif
#ifdef screen_enable
  ButtonCheck();
#endif
}

void batcheck() {
  bat = analogRead(volread);
  if (bat > 470) {
    bat = 470;
  } else if (bat < 330) {
    bat = 330;
  }
  bat = bat - 330;
  bat = map(bat, 0, 140, 0, 4);
  /*
byte bat1;
if (bt==1023) {Serial.println("FC20");return;} //99 stand for failure, 002 MCU REF V is grounded
else if (bt>870){Serial.println("FC21");return;} //99 stand for failure, 001 bat is over charged  *0.5055 ceo stand for 8.5v
else if (bt<650){Serial.println("FC22");return;}//99 stand for failure, 000 bat is low stand for 6.5v, measurement result 686 indicate6.5v 
else if (bt>850){bt=850; bt=bt-650; bat1=map(bt,0,200,0,100);} //bt*5/1023/0.5055=real / 4.2/real *255  (105494-4v)
else {bt=bt-650; bat1=map(bt,0,200,0,100);}
if (bat1<bat){bat=bat1;}*/
}

void FC_print(byte i) {
#ifdef ble_enable
  switch (i) {
    case 0:
      stoprun();
      startover = 1;
      Serial.println((String) "FC00" + (holdcards + totalcards - cardout) + "CARDS MISSING");  //FC00:SOCKET EMPTY
      break;
    case 1:
      stoprun();
      startover = 1;
      Serial.println((String) "FC01 REMAIN CARDS=" + (holdcards + totalcards - cardout));  //FC01: LOAD FAILED
      break;
    case 2:
      stoprun();
      startover = 1;
      Serial.println((String) "FC02 REMAIN CARDS=" + (holdcards + totalcards - cardout));  //FC02:SHOOT TIMEOUT
      break;
    case 5:
      startover = 0;
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
      startover = 1;
      Serial.println("FC10");  //FC10:It's not a valid command/improper setup
      break;
  }
#endif
#ifdef screen_enable
  stoprun();
  startover = 1;
  display.clearDisplay();
  switch (i) {
    case 0:
      display.setCursor(15, 24);
      display.println(F("FC00"));
      break;  //display.setCursor(5, 24);display.println(string(holdcards + totalcards - cardout));display.setCursor(45, 24);display.println(F("MISSING"));
    case 1:
      display.setCursor(15, 24);
      display.println(F("FC01"));
      break;
    case 2:
      display.setCursor(15, 24);
      display.println(F("FC02"));
      break;
    case 6:
      display.setCursor(15, 24);
      display.println(F("ENJOY!"));
      break;
    default: break;
  }
  display.display();
#endif
}

void ButtonCheck() {
  while (1) {
    if (digitalRead(touchpad1)) {
      //Serial.println("Button1 On");
      button_on = 0;  //up
      touchcounting(touchpad1);
      break;
    }
    if (digitalRead(touchpad2)) {
      //Serial.println("Button2 On");
      button_on = 2;  //down
      touchcounting(touchpad2);
      break;
    }
    if (digitalRead(touchpad3)) {
      //Serial.println("Button3 On");
      button_on = 3;
      touchcounting(touchpad3);
      break;
    }
    if (digitalRead(touchpad4)) {
      //Serial.println("Button4 On");
      button_on = 1;  //gogo
      touchcounting(touchpad4);
      break;
    }
    delay(10);
  }
}

//touch measurement to use "touchcounting"
void touchcounting(uint8_t j) {
  uint16_t i = 0;
  uint8_t k = 0;
  uint8_t touch_threshold = 150;  //intially 1s, dynamic control, in case keeping touch, this number will be smaller and smaller therefore the touchcounting will be faster
  while (digitalRead(j)) {
    delay(2);
    i++;
    if (i > touch_threshold) {
      touchevent(button_on);  //no accumulated touch count, each time reaches the threshold
      i = 0;
      if (touch_threshold < 20) {
        touch_threshold = 20;
      } else {
        k++;
        if (touch_threshold > 20) {
          touch_threshold = touch_threshold - k * k;
        }
      }
    }
  }
}

void touchevent(uint8_t i) {

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
  if (funIndex < 5) {
    switch (i) {
      case 0:
        totalcards = 108;
        holdcards = 0;
        players = 4;
        maxfqy = 30;
        break;
      case 1:
        totalcards = 54;
        holdcards = 3;
        players = 3;
        maxfqy = 30;
        break;
      case 2:
        totalcards = 54;
        holdcards = 0;
        players = 3;
        maxfqy = 30;
        break;
      case 3:
        totalcards = 108;
        holdcards = 8;
        players = 4;
        maxfqy = 80;
        break;
      case 4:
        totalcards = 52;
        holdcards = 0;
        players = 4;
        maxfqy = 36;
        break;
    }
    speed_table_lookup();
    loopstep = basestep / players;
    slip_step = loopstep - (high_accel_step + low_accel_step);  // slip until that step, not pure slip step
    motorspeed = 255;
    fast_break = 1;
  } else if (funIndex == 5) {
    goon = 0;
    cardout = 0;
    mode_type = mode_selection;
  } else if (funIndex == 6) {
    goon = 1;
    mode_type = mode_selection;
  } else if (funIndex == 9) {
    mode_selection = mode_random;
  } else if (funIndex == 10) {
    mode_selection = mode_1by1;
  }
}

void menu_1() {  //mode selection
  display.clearDisplay();
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
  display.clearDisplay();
  display.setCursor(15, 24);
  display.println(F("RUNNING"));
  //draw_bat();
  display.display();
}

void menu_setup() {
  display.clearDisplay();
  draw_bat();
  switch (funIndex) {
    case 9:
      display.setCursor(1, 22);
      display.println(F("MODE_RANDOM"));
      break;
    case 10:
      display.setCursor(1, 22);
      display.println(F("MODE_1BY1"));
      break;
  }
  display.display();
}

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
  initime = millis();
  t_start = initime;
  int halfround = int(players / 2);
  int half_step = loopstep / 2;
  int delta;
  uint8_t dir;
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
    loaded = !digitalRead(outer_sensor);
    //shooted=!loaded;
    if (!loaded) {  //if not load, to load
      softload();
      if (loaded == 0) { FC_print(1); }
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
    /*if (digitalRead(cardin) == 1)  //in case no more card, stop rolling imediately
  {
    FC_print(0);
    return;
  }*/
    load_check(250, 1);
    if (startover) {
      return;
    }
  } else {
    softload();
    if (loaded == 0) { FC_print(1); }
    if (startover) {
      return;
    }
  }
  digitalWrite(motora1, HIGH);
  byte j;
  byte k;
  for (byte i = cardout; i < totalcards; i++) {
    //if (digitalRead(cardin) == 1)  //in case no more card, stop rolling imediately
    // {
    //    FC_print(0);
    //    return;
    // }
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
    if (startover){return;}
    cardout++;
    //Serial.print(cardout);
    if (startover) {
      return;
    } else if (cardout == totalcards) {
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
    bool dir = command[5];
    digitalWrite(steperDIR, dir);
    uint8_t speed_coe = command[6];  //basespeed= 180 - speed_coe*7; //need calibration, typical5, for sample C =7 for a trial
    mode_type = command[7];
    fast_break = command[8];  //in case 0
    motorspeed = speed_coe;   //to update acc to break mode
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