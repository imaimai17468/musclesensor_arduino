// define-----------------------------------------------------------------------------------

#define MAX_SIZE 2000 // 受け取るデータ数

// -----------------------------------------------------------------------------------------
// global-----------------------------------------------------------------------------------

int i = 0;                  // カウント変数
unsigned long t = 0;        // ループ毎の時間を保持する変数
unsigned long dis_t = 0;    // スタートからの時間を保持する変数
unsigned long delay_t = 0;  // サンプリング周期を調整するための遅延時間を保持する変数
int value = 0;              // センサの値を保持する変数
char moji;                  // シリアル通信の入力用変数

// -----------------------------------------------------------------------------------------
// setup------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
}

// -----------------------------------------------------------------------------------------
// main-------------------------------------------------------------------------------------

void loop() {
  // シリアルモニタで入力（Enterなど）を与えられたらスタート
  if ((moji = Serial.read()) != -1) {
    unsigned long start_t = micros();

    for(i = 0; i < MAX_SIZE; i++){
      t = micros();           // ループ開始時の時間を受け取る
      dis_t = t - start_t;    // プログラムが開始してから毎ループの開始までの時間を計算
      value = analogRead(0);  // センサの値を受け取る

      // 時間情報も出力する場合はコメントアウトを解除する
      // サンプリング周期1msは十分な精度なため通常は時間情報を送信しない
      // 送信する時間の桁数(現在は小数点以下三桁)を増やすとシリアル通信にかかる時間が多くなるため注意      
      // Serial.print(dis_t / 1000000.0, 3);
      // Serial.print(",");

      // センサの値を出力
      Serial.println(value);

      // サンプリング周期 1 ms を保つための遅延させる時間を算出
      delay_t = micros() - t + (dis_t % 1000);
      delayMicroseconds(1000 - delay_t);
    }
    Serial.println("EOF");
  }
}
// -----------------------------------------------------------------------------------------
