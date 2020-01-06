#include <LedControl.h>
#define VrX A0
#define VrY A1
#define SW 2
#define BUZZER 7
/*
  pin CLK = 10;
  pin CS = 9;
  pin DIN = 8;
*/
LedControl lc = LedControl(10, 8, 9, 1);
int YemX, YemY;
int Sutun[64], Satir[64];
int posX = 0, posY = 0, a = 0;
int xPozisyon = 0, yPozisyon = 0;
int BaslangicX = 4, BaslangicY = 4;
const short messageSpeed = 5;
int bayrak = 1;
int Hiz = 300;
void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  pinMode(VrX, INPUT);
  pinMode(VrY, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(SW), Restart, FALLING);
  showSnakeMessage();
}
void loop()
{
  Yilan();
}
void Yilan() {
  
  if (bayrak == 0)//Bayrak değerimiz 0 olursa döngünün içine girip değişkenlerimizi sıfırladıgımız yer.
  {
    posX = 0;
    posY = 0;
    a = 0;
    xPozisyon = 0;
    yPozisyon = 0;
    BaslangicX = 4;
    BaslangicY = 4;
    Hiz = 300;
    for (int i = 0; i < 64; i++)
    {
      Satir[i] = NULL;
      Sutun[i] = NULL;
    }
    for (int j = 0; j < 8; j++)
    {
      
      for (int k = 0; k < 8; k++)
      {
        lc.setLed(0, j, k, 0);
      }

    }
    bayrak = 1;
    return Yilan();//Değişkenleri sıfırladıktan sonra tekrardan Hareket fonksiyonumuzu döndürüyoruz.
  }
  
  xPozisyon = analogRead(VrX);//Joystick hareketlerini aldığımız yer.
  yPozisyon = analogRead(VrY);
 
  if (xPozisyon < 20) {
    //aşağı
    posY = -1; posX = 0;
  }
  else if (xPozisyon > 850) {
    //yukarı
    posY = 1; posX = 0;
  }
  else if (yPozisyon < 20) {
    //sola
    posX = 1; posY = 0;
  }
  else if (yPozisyon > 850) { //sağa
    posX = -1; posY = 0;
  }
  
  BaslangicX = BaslangicX + posX;
  BaslangicY = BaslangicY + posY;
  
  if (BaslangicX > 7)
  {
    BaslangicX = 0;
  }
  else if (BaslangicX < 0)
  {
    BaslangicX = 7;
  }
  else if (BaslangicY > 7)
  {
    BaslangicY = 0;
  }
  else if (BaslangicY < 0)
  {
    BaslangicY = 7;
  }
  Sutun[0] = BaslangicX;
  Satir[0] = BaslangicY;

  for (int i = 1; i <= a; i++)
  {
    if (BaslangicX == Sutun[i] && BaslangicY == Satir[i])
    {
      delay(1000);
      showGameOverMessage();
      bayrak = 0;
    }
  }
  
  lc.setLed(0, BaslangicX, BaslangicY, 1);
  for (int i = 0; i <= a; i++)
  {
    lc.setLed(0, Sutun[i], Satir[i], 1);
  }
  
  if (BaslangicX == YemX && BaslangicY == YemY)//Yem koordinatlarıyla yılanın koordinatlarının kesişip kesişmediğini kontrol edildiği yer.
  {
    Hiz = Hiz - 5;
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    Yem();//Yem yenilmişse yeni yem için X ve Y koordinatları belirlediğimizyer 
    a++;
  }
  
  lc.setLed(0, YemX, YemY, 1);//Yeni yem için X ve Y koordinatlarını ekranda gösterdiğimiz yer.
  
  delay(Hiz); 
  
  lc.setLed(0, BaslangicX, BaslangicY, 0);
  for (int i = 0; i <= a; i++)
  {
    lc.setLed(0, Sutun[i], Satir[i], 0);
  }
  for (int i = a; i > 0; i--)
  {
    Sutun[i] = Sutun[i - 1];
    Satir[i] = Satir[i - 1];
  }
}
void Yem() {//Rastgele yemler oluşturuyoruz
  //srand((NULL));
  YemX = rand() % 8;
  YemY = rand() % 8;
}
const PROGMEM bool snejkMessage[8][56] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void showSnakeMessage() {//ekrana yazdıran bu iki fonksiyonu hazır aldım.
  for (int d = 0; d < sizeof(snejkMessage[0]) - 7; d++) {
    for (int col = 7; col >= 0; col--) {
      delay(messageSpeed);
      for (int row = 7; row >= 0 ; row--) {
        // this reads the byte from the PROGMEM and displays it on the screen
        lc.setLed(0, col, row, pgm_read_byte(&(snejkMessage[row][col + d ])));
      }
    }
  }
}
const PROGMEM bool gameOverMessage[8][90] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
void showGameOverMessage() {//ekrana yazdıran bu iki fonksiyonu hazır aldım.

  for (int d = 0; d < sizeof(gameOverMessage[0]) - 7; d++) {
    for (int col = 7; col >= 0; col--) {
      delay(messageSpeed);
      for (int row = 7; row >= 0 ; row--) {
        // this reads the byte from the PROGMEM and displays it on the screen
        lc.setLed(0, col, row, pgm_read_byte(&(gameOverMessage[row][col + d ])));
      }
    }
  }
}
