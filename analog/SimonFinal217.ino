

int activeSequence[16] = {0};
int lengthOfTheActiveSequence = 0;
int positionInSequence;
int inputInSequence;
bool gameActive;

int colourSelect;
int finalResults;
int finalResultsCounter;

//lighting
bool shouldBeLit;
//waiting between each light
bool shouldBeDark;
//sequence is displayed
bool shouldBeDisplayBetweenRounds;

//Invoke ButtonController to change the color of buttons
bool shouldBeRed;
bool shouldBeDisplayed;

bool isStarted;
bool isSwitchOn = false;

//FOR PHYSICAL Only
bool shouldBeClick;
bool isPlaying = false;

class SpriteRenderer
{
  public:
    void setColorHigh()
    {
      digitalWrite(sNumber, HIGH);
    }
    void setColorLow()
    {
      digitalWrite(sNumber, LOW);
    }

    int bNumber; //buttonNumber
    int sNumber; //sequenceNumber
    int bValue = 0; //buttonValue
    int sState = 0;
    int p = 0;

};


SpriteRenderer colour[16];

int startButton = 8;
int startButtonLED = 9;
int startButtonValue = 0;

int toggleSwitch = 10;
int toggleSwitchValue = 0;


//Time for lighting
float stayLit = 200;
float stayLitCounter;

//Waiting time between each light
float waitBetweenLights = 100;
float waitBetweenCounter;

//Waiting time between each
float waitBetweenRounds = 500;
float waitBetweenRoundsCounter;

//Waiting time between end_game & end_score_display
float waitBetweenGames = 1500;
float waitBetweenGamesCounter;


void setup() {
  // put your setup code here, to run once:
  //  colour[0].bNumber = 5;
  //  colour[1].bNumber = 6;
  //  colour[2].bNumber = 7;
  for (int i = 0, j = 22; j <= 52; i++)
  {
    colour[i].bNumber = j;
    pinMode(colour[i].bNumber, INPUT);
    j = j + 2;
  }

  //  colour[0].sNumber = 11;
  //  colour[1].sNumber = 12;
  //  colour[2].sNumber = 13;
  for (int i = 0, j = 23; j <= 53; i++)
  {
    colour[i].sNumber = j;
    pinMode(colour[i].sNumber, OUTPUT);
    j = j + 2;
  }

  for (int i = 0; i < 16; i++) {
    colour[i].bValue = 0;
    colour[i].sState = 0;

  }

  //  pinMode(colour[0].bNumber, INPUT);
  //  pinMode(colour[1].bNumber, INPUT);
  //  pinMode(colour[2].bNumber, INPUT);
  //
  //  pinMode(colour[0].sNumber, OUTPUT);
  //  pinMode(colour[1].sNumber, OUTPUT);
  //  pinMode(colour[2].sNumber, OUTPUT);

  pinMode(startButton, INPUT);
  pinMode(startButtonLED, OUTPUT);
  pinMode(startButtonLED, OUTPUT);

  pinMode(toggleSwitch, INPUT);

  Serial.begin(9600);
  isStarted = true;

}


void loop() {

  toggleSwitchValue = digitalRead(toggleSwitch);
  Serial.println(toggleSwitchValue);
  if (toggleSwitchValue == HIGH) {
    Serial.println("toggle works");
    isSwitchOn = true;
  }



  if (toggleSwitchValue != LOW) {


    //  colour[0].bValue = digitalRead(colour[0].bNumber);
    //  colour[1].bValue = digitalRead(colour[1].bNumber);
    //  colour[2].bValue = digitalRead(colour[2].bNumber);
    for (int i = 0; i < 16; i++)
    {
      colour[i].bValue = digitalRead(colour[i].bNumber);

    }
    //  colour[0].sState = digitalRead(colour[0].sNumber);
    //  colour[1].sState = digitalRead(colour[1].sNumber);
    //  colour[2].sState = digitalRead(colour[2].sNumber);
    for (int i = 0; i < 16; i++)
    {
      colour[i].sState = digitalRead(colour[i].bNumber);

    }

    startButtonValue = digitalRead(startButton);




    //Game Start
    if (isSwitchOn) {
      //Serial.println("GAME");
      if (isStarted == true) {
        digitalWrite(startButtonLED, HIGH);
      }
      //delay(100);
      if ( startButtonValue == HIGH) {

        StartPhysicalGame();
        isStarted = false;
      }


    }
    //Get the length of the active sequence
    for (int i = 0; i < 16; i++) {
      if (activeSequence[i] != 0) {
        lengthOfTheActiveSequence = i + 1;
        if (lengthOfTheActiveSequence >= 16) {
          lengthOfTheActiveSequence = 16;
        }
      }
    }



    if (shouldBeRed)
    {
      for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 16; i++) {
          colour[i].setColorHigh();
        }
        delay(25);
        for (int i = 0; i < 16; i++) {
          colour[i].setColorLow();
        }
        delay(25);
      }
      //      for (int i = 0; i < 16; i++) {
      //        colour[i].setColorHigh();
      //      }
      delay(waitBetweenGamesCounter);
      for (int i = 0; i < 16; i++) {
        colour[i].setColorLow();
      }

      shouldBeRed = false;
      shouldBeDisplayed = true;
    }


    if (shouldBeDisplayed) {
      EndScoreDisplay();

    }

    if (shouldBeLit)
    {
      //light process
      colour[(activeSequence[positionInSequence] - 23) / 2].setColorHigh();
      delay(stayLitCounter);

      shouldBeClick = true;
      shouldBeLit = false;


    }


    if (shouldBeDark)
    {
      //waiting between each light
      colour[(activeSequence[positionInSequence] - 23) / 2].setColorLow();
      delay(waitBetweenCounter);
      Serial.println("shouldBeDark works");

      if (positionInSequence <= lengthOfTheActiveSequence)
      {
        positionInSequence++;
        shouldBeClick = true;
        shouldBeDark = false;

        Serial.println("shouldBeDark goes smoothly");
      }

    }


    if (shouldBeDisplayBetweenRounds)
    {
      delay(waitBetweenRoundsCounter);

      colourSelect = ColourSelect();
      Serial.println("check if positionInSequence is right");
      Serial.println(positionInSequence);

      activeSequence[positionInSequence] = 2 * colourSelect + 23;
      Serial.println(activeSequence[positionInSequence]);

      positionInSequence = 0;

      shouldBeLit = true;
      shouldBeDisplayBetweenRounds = false;
      colour[(activeSequence[positionInSequence] - 23) / 2].setColorLow();

      for (int i = 0; i < 16; i++) {
        if (activeSequence[i] != 0) {
          activeSequence[i] = 88;
        }
      }
      for (int i = 0; i < 16; i++) {
        if (activeSequence[i] != 0) {
          colourSelect = ColourSelect();
          activeSequence[i] = 2 * colourSelect + 23;
        }
      }




    }


    if (shouldBeClick)
    {
      colour[(activeSequence[positionInSequence] - 23) / 2].setColorHigh();


      gameActive = true;
      Serial.println("shouldbeclickworks");
      Serial.println(positionInSequence);
      Serial.println(lengthOfTheActiveSequence);

      //      for (int i = 0; i < 16; i++) {
      //        Serial.println(activeSequence[i]);
      //      }

      //Game Play


      for (int i = 0; i < 16; i++)
      {
        if (colour[i].sState == HIGH)
        {
          if (colour[i].bValue == HIGH) {
            ColourPressed(colour[i].bNumber);
          }


        }
      }


      if (positionInSequence >= lengthOfTheActiveSequence)
      {


        Serial.println(lengthOfTheActiveSequence);

        if (colour[(activeSequence[positionInSequence - 1] - 23) / 2].bValue == 0) {

          inputInSequence = 0;

          isPlaying = true;
          shouldBeClick = false;

        }

      }


    }

    if (isPlaying) {


      //Default Button Pressinf
      for (int i = 0; i < 16; i++) {
        if (colour[i].bValue == HIGH) {
          colour[i].setColorHigh();

        } else {
          colour[i].setColorLow();

        }
      }

      //Serial.println("game start");

      for (int i = 0; i < 16; i++)
      {
        if (colour[i].bValue == HIGH) {
          ColourPressed(colour[i].bNumber);
        }


      }
    }
  } else if (toggleSwitchValue == 0) {
    Serial.println("toggle shut dom");
    digitalWrite(startButtonLED, LOW);
    for (int i = 0; i < 16; i++) {
      colour[i].setColorLow();
    }

    for (int i = 0; i < 16; i++) {
      activeSequence[i] = 0;
    }

    positionInSequence = 0;
    inputInSequence = 0;

    shouldBeLit = false;
    shouldBeDark = false;
    shouldBeDisplayBetweenRounds = false;
    shouldBeClick = false;
    isPlaying = false;

    shouldBeRed = false;
    shouldBeDisplayed = false;

    isSwitchOn = true;
    isStarted = true;


  }
}



void StartPhysicalGame()
{
  Serial.println("middle");

  for (int i = 0; i < 16; i++) {
    colour[i].setColorLow();
  }

  for (int i = 0; i < 16; i++) {
    activeSequence[i] = 0;
  }

  positionInSequence = 0;
  inputInSequence = 0;

  shouldBeLit = false;
  shouldBeDark = false;
  shouldBeDisplayBetweenRounds = false;
  shouldBeClick = false;
  isPlaying = false;

  shouldBeRed = false;
  shouldBeDisplayed = false;

  //randomly generate colourSelect
  colourSelect = ColourSelect();
  activeSequence[positionInSequence] = 2 * colourSelect + 23;
  positionInSequence = positionInSequence + 1;
  colourSelect = ColourSelect();
  activeSequence[positionInSequence] = 2 * colourSelect + 23;
  positionInSequence = positionInSequence - 1;

  stayLitCounter = stayLit;
  waitBetweenCounter = waitBetweenLights;
  waitBetweenRoundsCounter = waitBetweenRounds;
  waitBetweenGamesCounter = waitBetweenGames;
  shouldBeLit = true;

  digitalWrite(startButtonLED, LOW);



}


int ColourSelect()
{
  int randomGenerator;
  randomGenerator = random(0, 16);
  for (int j = 0, p = 0; j != 1;)
  {

    for (int i = 0; i < lengthOfTheActiveSequence; i++)
    {
      if ((2 * randomGenerator + 23) == activeSequence[i])
      {
        randomGenerator = random(0, 16);
        p++;

      }
    }

    if (p == 0)
    {
      j = 1;
    }
    else
    {
      p = 0;
    }

  }

  return randomGenerator;

}


void ColourPressed(int whichButton)
{
  if (gameActive)
  {
    if (isPlaying)
    {
      //Serial.println("isplaying");
      //delay(300);

      if ((activeSequence[inputInSequence] - 1) == whichButton)
      {
        Serial.println(activeSequence[inputInSequence]);

        inputInSequence++;

        if (inputInSequence >= lengthOfTheActiveSequence)
        {
          //positionInSequence = 0;
          inputInSequence = 0;

          shouldBeDisplayBetweenRounds = true;
          finalResults = lengthOfTheActiveSequence;
          isPlaying = false;
          gameActive = false;
          Serial.println("game end");
          delay(200);
          for (int i = 0; i < 16; i++) {

            colour[i].setColorLow();


          }
        }
      } else if ((activeSequence[inputInSequence] - 1) != whichButton && (activeSequence[inputInSequence - 1] - 1) != whichButton) {
        finalResults = lengthOfTheActiveSequence;
        shouldBeRed = true;
        //finalResultsCounter = 0;
        gameActive = false;
        isPlaying = false;
      }

    }

    if (shouldBeClick)
    {

      if ((activeSequence[inputInSequence] - 1) == whichButton)
      {
        inputInSequence++;
        colour[(activeSequence[positionInSequence] - 23) / 2].setColorLow();
        Serial.println("clickworks");
        //
        //        if (inputInSequence >= lengthOfTheActiveSequence)
        //        {
        //          //inputInSequence = 0;
        //          Serial.println("click is over");
        //
        //          //delay(200);
        //
        //        }

        shouldBeDark = true;

        shouldBeClick = false;

      }
    }
  }
}

void EndScoreDisplay() {
  //  Serial.println("display works");
  //  Serial.println(finalResults);
  digitalWrite(startButtonLED, HIGH);
  isSwitchOn = true;

  for (int i = 0; i < finalResults - 1; i++) {
    digitalWrite(23 + i * 2, HIGH);

  }


}
