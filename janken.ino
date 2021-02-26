#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(10, 11); // RX, TX

int a = 0;
int b = 0;
int koin = 0;
int koin1 = 0;
int sutato = 0;
int maisu = 0;
int kaisu = 0;
int kaisu4 = 0;
int konpyuta = 0;
int rure = 0;
int rure2 = 0;
int rure4 = 0;
int harai = 0;
int gu = 0;
int tyoki = 0;
int pa = 0;
int koe = 0;
int zyoutai = 0;
int koinbotan = 0;
int sensa = 0;

void setup() {
  delay(2000); //モジュール起動の待機時間
  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module
  mp3_set_volume (20);
  for (int i = 22; i <= 25; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 25; i <= 30; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  for (int i = 30; i <= 38; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 40; i <= 50; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(39, INPUT_PULLUP);
}

void loop() {
  if (zyoutai == 0) {
    digitalWrite(30, LOW);
    analogWrite(2, 50);
    analogWrite(3, 0);
    analogWrite(4, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
    zyoutai = 1;
  }
  if (zyoutai == 1) {
    kaisu = kaisu + 1;
    delay(5);
    if (kaisu == 1) {
      analogWrite(3, 50);
      analogWrite(4, 50);
      analogWrite(5, 0);
      analogWrite(6, 0);
      digitalWrite(22, HIGH); // グーボタン点灯
      digitalWrite(24, LOW);
    }
    if (kaisu == 301) {
      analogWrite(3, 50);
      analogWrite(4, 0);
      analogWrite(5, 50);
      analogWrite(6, 0);
      digitalWrite(23, HIGH); // チョキボタン点灯
      digitalWrite(22, LOW);
    }
    if (kaisu == 601) {
      analogWrite(3, 0);
      analogWrite(4, 0);
      analogWrite(5, 50);
      analogWrite(6, 50);
      digitalWrite(24, HIGH); // パーボタン点灯
      digitalWrite(23, LOW);
    }
    if (kaisu == 901) {
      kaisu = 0;
    }
  }
  if (zyoutai == 1) {
    koin = digitalRead(29);
    if (koin == LOW) {
      koinbotan = 1;
    }
    if (koinbotan == 1) {
      digitalWrite(30, HIGH); // スタートボタン点灯
      digitalWrite(22, LOW); // グーボタン消灯
      digitalWrite(23, LOW); // チョキボタン消灯
      digitalWrite(24, LOW); // パーボタン消灯
      koin1 = 1;
      zyoutai = 2;
    }
  }
  if (zyoutai == 2) {
    sutato = digitalRead(25);
    if (sutato == LOW && koin1 == 1) { // スタートボタン押した？
      mp3_play(1);
      digitalWrite(30, LOW); // スタートボタン消灯
      digitalWrite(22, HIGH); // グーボタン点灯
      digitalWrite(23, HIGH); // チョキボタン点灯
      digitalWrite(24, HIGH); // パーボタン点灯
      konpyuta = random(1, 4); // コンピューターの手を決める
      koinbotan = 0;
      maisu = 1;
      zyoutai = 3;
    }
  }
  if (zyoutai == 3) {
    gu = digitalRead(26);
    if (gu == LOW) {
      mp3_stop();
      if ( koe == 0) {
        mp3_play(2);
      }
      else {
        mp3_play(4);
      }
      digitalWrite(23, LOW); // チョキボタン消灯
      digitalWrite(24, LOW); // パーボタン消灯
      if (konpyuta == 1) { // あいこ
        analogWrite(3, 50); // グー①
        analogWrite(4, 50); // グー②
        analogWrite(5, 0); // チョキ
        analogWrite(6, 0); // パー
        digitalWrite(37, HIGH); // あいこ
        delay(500);
        digitalWrite(22, HIGH); // グーボタン点灯
        digitalWrite(23, HIGH); // チョキボタン点灯
        digitalWrite(24, HIGH); // パーボタン点灯
        digitalWrite(37, LOW); // あいこ
        koe = 1;
        mp3_play(3);
        konpyuta = random(1, 4);
      }
      else if (konpyuta == 2) { // かち
        analogWrite(3, 50); // グー①
        analogWrite(4, 0); // グー②
        analogWrite(5, 50); // チョキ
        analogWrite(6, 0); // パー
        digitalWrite(35, HIGH);
        delay(500);
        mp3_play(5);
        delay(800);
        digitalWrite(22, LOW);
        zyoutai = 4;
        koe = 0;
        kaisu = 30;
      }
      else  { // まけ (konpyuta == 3)
        analogWrite(3, 0); // グー①
        analogWrite(4, 0); // グー②
        analogWrite(5, 50); // チョキ
        analogWrite(6, 50); // パー
        digitalWrite(36, HIGH);
        delay(500);
        mp3_play(8);
        delay(500);
        digitalWrite(22, LOW);
        digitalWrite(36, LOW);
        zyoutai = 1;
        koe = 0;
        kaisu = 0;
      }
    }
  }
  if (zyoutai == 3) {
    tyoki = digitalRead(27);
    if (tyoki == LOW) {
      mp3_stop();
      if ( koe == 0) {
        mp3_play(2);
      }
      else {
        mp3_play(4);
      }

      digitalWrite(22, LOW);
      digitalWrite(24, LOW);
      if (konpyuta == 1) { // まけ
        analogWrite(3, 50); // グー①
        analogWrite(4, 50); // グー②
        analogWrite(5, 0); // チョキ
        analogWrite(6, 0); // パー
        digitalWrite(36, HIGH);
        delay(500);
        mp3_play(8);
        delay(500);
        digitalWrite(23, LOW);
        digitalWrite(36, LOW);
        zyoutai = 1;
        koe = 0;
        kaisu = 30;
      }
      else if (konpyuta == 2) { // あいこ
        analogWrite(3, 50); // グー①
        analogWrite(4, 0); // グー②
        analogWrite(5, 50); // チョキ
        analogWrite(6, 0); // パー
        digitalWrite(37, HIGH);
        delay(500);
        digitalWrite(22, HIGH); // グーボタン点灯
        digitalWrite(23, HIGH); // チョキボタン点灯
        digitalWrite(24, HIGH); // パーボタン点灯
        digitalWrite(37, LOW); // あいこ
        koe = 1;
        mp3_play(3);
        konpyuta = random(1, 4);
      }
      else  { // かち (konpyuta == 3)
        analogWrite(3, 0); // グー①
        analogWrite(4, 0); // グー②
        analogWrite(5, 50); // チョキ
        analogWrite(6, 50); // パー
        digitalWrite(35, HIGH);
        delay(500);
        mp3_play(5);
        delay(800);
        digitalWrite(23, LOW);
        zyoutai = 4;
        koe = 0;
        kaisu = 0;
      }
    }
  }
  if (zyoutai == 3) {
    pa = digitalRead(28);
    if (pa == LOW) {
      mp3_stop();
      if ( koe == 0) {
        mp3_play(2);
      }
      else {
        mp3_play(4);
      }
      digitalWrite(22, LOW);
      digitalWrite(23, LOW);
      if (konpyuta == 1) { // かち
        analogWrite(3, 50); // グー①
        analogWrite(4, 50); // グー②
        analogWrite(5, 0); // チョキ
        analogWrite(6, 0); // パー
        digitalWrite(35, HIGH);
        delay(500);
        mp3_play(5);
        delay(800);
        digitalWrite(24, LOW);
        zyoutai = 4;
        koe = 0;
        kaisu = 30;
      }
      else if (konpyuta == 2) { // まけ
        analogWrite(3, 50); // グー①
        analogWrite(4, 0); // グー②
        analogWrite(5, 50); // チョキ
        analogWrite(6, 0); // パー
        digitalWrite(36, HIGH);
        delay(500);
        mp3_play(8);
        delay(500);
        digitalWrite(24, LOW);
        digitalWrite(36, LOW);
        zyoutai = 1;
        koe = 0;
        kaisu = 60;
      }
      else  { // あいこ (konpyuta == 3)
        analogWrite(3, 0); // グー①
        analogWrite(4, 0); // グー②
        analogWrite(5, 50); // チョキ
        analogWrite(6, 50); // パー
        digitalWrite(37, HIGH);
        delay(500);
        digitalWrite(22, HIGH); // グーボタン点灯
        digitalWrite(23, HIGH); // チョキボタン点灯
        digitalWrite(24, HIGH); // パーボタン点灯
        digitalWrite(37, LOW); // あいこ
        koe = 1;
        mp3_play(3);
        konpyuta = random(1, 4);
      }
    }
  }
  if (zyoutai == 4) { 
    rure2 = random(1, 10);
    digitalWrite(35, LOW);
    digitalWrite(31, HIGH);
    for (rure = 0; rure < rure2 + 27; rure++) {
      mp3_play(6);
      digitalWrite(((rure % 9) + 41), HIGH);
      if (rure4 == 0) {
        digitalWrite(38, HIGH);
      } else {
        digitalWrite(35, HIGH);
      }
      delay(50);
      if (rure4 == 0) {
        digitalWrite(38, LOW);
        rure4 = 1;
      } else {
        digitalWrite(35, LOW);
        rure4 = 0;
      }
      delay(50);
      digitalWrite(((rure % 9) + 41), LOW);
    }
    if (rure4 == 0) {
      digitalWrite(35, HIGH);
    } else {
      digitalWrite(38, HIGH);
      rure4 = 0;
    }
    mp3_play(7);
    rure = rure2 + 40;
    digitalWrite(rure, HIGH);
    delay(500);
    maisu = 0;
    harai = 0;
    if (rure2 == 1) {
      a = 5;
    }
    if (rure2 == 2) {
      a = 2;
    }
    if (rure2 == 3) {
      a = 3;
    }
    if (rure2 == 4) {
      a = 2;
    }
    if (rure2 == 5) {
      a = 1;
    }
    if (rure2 == 6) {
      a = 2;
    }
    if (rure2 == 7) {
      a = 3;
    }
    if (rure2 == 8) {
      a = 2;
    }
    if (rure2 == 9) {
      a = 1;
    }
    zyoutai = 5;
    digitalWrite(31, LOW); //パトライト消灯
  }
  if (zyoutai == 5) {
    for (;;) {
      sensa = digitalRead(39);
      digitalWrite(40, HIGH);
      b = b + 1;
      if (b == 1000) {
        digitalWrite(40, LOW);
      }
      if (sensa == HIGH) {
        a = a - 1 ;
        delay(25);
      }
      if (a == 0) {
        digitalWrite(40, LOW);
        digitalWrite(rure, LOW);
        digitalWrite(35, LOW);
        digitalWrite(38, LOW);
        zyoutai = 1;
        b = 0;
        break;
      }
    }
  }
  if (zyoutai >= 3) {
    kaisu4 = kaisu4 + 1;
    if (kaisu4 == 1) {
      analogWrite(3, 50); // グー①
      analogWrite(4, 50); // グー②
      analogWrite(5, 0);
      analogWrite(6, 0);
      delay(50);
    } else if (kaisu4 == 2) {
      analogWrite(3, 50); // グー①
      analogWrite(4, 0);
      analogWrite(5, 50); // チョキ
      analogWrite(6, 0);
      delay(50);
    } else {
      analogWrite(3, 0);
      analogWrite(4, 0);
      analogWrite(5, 50); // チョキ
      analogWrite(6, 50); // パー
      kaisu4 = 0;
      delay(50);
    }
  }
}
