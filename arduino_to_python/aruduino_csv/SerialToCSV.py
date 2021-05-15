import serial
import time

# ポートの設定
ser = serial.Serial("COM3",
                    baudrate=115200,
                    bytesize=serial.EIGHTBITS,
                    parity=serial.PARITY_NONE,
                    stopbits=serial.STOPBITS_ONE,
                    timeout=1,
                    xonxoff=0,
                    rtscts=0
                    )

# シリアル通信を設定するときに綺麗にリセットする
# Toggle DTR to reset Arduino
ser.setDTR(False)
time.sleep(1)
# toss any data already received, see
ser.flushInput()
ser.setDTR(True)

cnt = 0                     # カウント用変数
set = 3                     # 何セット分計測するか

# カウントダウン表示用関数
def CountDown(start):
    for j in range(start):
        print(start - j)
        time.sleep(1)


# 計測
for i in range(set):

    CountDown(3)
    print("開始")

    d = []  # データ確認用（テスト）

    # データ読み込み
    data = ""
    while(data != "EOF"):
        # データを受信
        data = ser.readline().rstrip().decode()
        d.append(data)
        #print(data)

    CountDown(3)
    print("終了")


    # ファイル名
    filename = "test/data" + str(i) + ".csv"

    # csv形式で保存
    with open(filename, 'w', newline='') as f:
        for j in range(len(d)-1):
            f.write(str("{:.3f}".format(j * 0.001)) + "," + str(d[j]) + '\n')
            #f.write(str(t[j]) + "," + str(v[j]) + '\n')


ser.close()
