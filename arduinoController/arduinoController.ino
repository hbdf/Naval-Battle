enum cells {
  E5 = 2,
  E4,
  E3,
  E2,
  E1,
  D5,
  D4,
  D3,
  D2,
  D1,
  C5,
  C4,
  C3,
  C2,
  C1,
  B5,
  B4,
  B3,
  B2,
  BB
};

int board[6][6];

void setup() {
  memset(board, 0, sizeof board);
  Serial.begin(9600);
  pinMode(E5, INPUT);
  pinMode(E4, INPUT);
  pinMode(E3, INPUT);
  pinMode(E2, INPUT);
  pinMode(E1, INPUT);
  pinMode(D5, INPUT);
  pinMode(D4, INPUT);
  pinMode(D3, INPUT);
  pinMode(D2, INPUT);
  pinMode(D1, INPUT);
  pinMode(C5, INPUT);
  pinMode(C4, INPUT);
  pinMode(C3, INPUT);
  pinMode(C2, INPUT);
  pinMode(C1, INPUT);
  pinMode(B5, INPUT);
  pinMode(B4, INPUT);
  pinMode(B3, INPUT);
  pinMode(B2, INPUT);
  pinMode(BB, INPUT);
}


void loop() {
  bool mudou = false;
  for (int i = 2; i <= 21; i++) {
    int val = i - 2;
    int x = (4 - (val / 5));
    int y = (4 - (val % 5));
    if(digitalRead(i) != board[x][y]) {
      //save_change(x, y)
      board[x][y] ^= 1;
      
      if(board[x][y]) continue;
      mudou = true;
      char num[3] = {0};
      num[1] = '0';
      int ind = 0;
      int aux = i;
      while(aux) {
        num[ind++] = (aux % 10) + '0';
        aux /=10;
      }
      int xx = num[0];
      num[0] = num[1];
      num[1] = xx;
      Serial.print(x);
      Serial.print("-");
      Serial.println(y);
    }
  }
  if(mudou) {
    Serial.println("END");
  }
  delay(500);
}
