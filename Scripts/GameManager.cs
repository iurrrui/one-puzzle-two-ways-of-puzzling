using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class GameManager : MonoBehaviour
{

    public SpriteRenderer[] colours;
    public Image startButtonColor;
    public GameObject theGO;

    public List<int> activeSequence;
    public int positionInSequence;
    public int inputInSequence;
    public int resetSequence;
    public bool gameActive;

    private int colourSelect;
    private int finalResults;
    private int finalResultsCounter;


    //Time for lighting
    public float stayLit;
    private float stayLitCounter;

    //Waiting time between each light
    public float waitBetweenLights;
    private float waitBetweenCounter;

    //Waiting time between each 
    public float waitBetweenRounds;
    private float waitBetweenRoundsCounter;

    //Waiting time between end_game & end_score_display
    public float waitBetweenGames;
    private float waitBetweenGamesCounter;


    //lighting
    private bool shouldBeLit;
    //waiting between each light
    private bool shouldBeDark;
    //sequence is displayed
    private bool shouldBeDisplayBetweenRounds;


    //Invoke ButtonController to change the color of buttons
    public bool shouldBeGreen;
    public bool shouldBeWhite;
    public bool shouldBeAllWhite;
    public bool shouldBeRed;
    public bool shouldBeBlack;


    private bool isPhysical;
    private bool isDigital;

    //FOR PHYSICAL Only
    public bool shouldBeClick;
    public bool isPlaying = false;


    void Start()
    {
        startButtonColor = GetComponent<Image>();

    }


    void Update()
    {

        if (isDigital)
        {

            if (shouldBeLit)
            {
                //lighting
                colours[activeSequence[positionInSequence]].color = new Color(255, 255, 255, 1f);
                stayLitCounter -= Time.deltaTime;

                if (stayLitCounter < 0)
                {

                    colours[activeSequence[positionInSequence]].color = new Color(0, 0, 0, 1f);
                    shouldBeLit = false;

                    shouldBeDark = true;
                    waitBetweenCounter = waitBetweenLights;

                    positionInSequence++;

                }
            }


            if (shouldBeDark)
            {
                //waiting between each light
                waitBetweenCounter -= Time.deltaTime;
                shouldBeWhite = false;

                if (positionInSequence >= activeSequence.Count)
                {
                    shouldBeDark = false;
                    gameActive = true;
                }
                else
                {
                    if (waitBetweenCounter < 0)
                    {
                        colours[activeSequence[positionInSequence]].color = new Color(255, 255, 255, 1f);

                        stayLitCounter = stayLit;
                        shouldBeLit = true;
                        shouldBeAllWhite = false;
                        shouldBeDark = false;

                    }
                }
            }


            if (shouldBeDisplayBetweenRounds)
            {
                //sequence is displayed
                shouldBeGreen = true;

                waitBetweenRoundsCounter -= Time.deltaTime;

                if (waitBetweenRoundsCounter < 0)
                {
                    shouldBeGreen = false;
                    shouldBeWhite = true;

                    colourSelect = ColourSelect();
                    activeSequence.Add(colourSelect);

                    resetSequence = activeSequence.Count;
                    activeSequence.Clear();

                    for (int i = 0; i < resetSequence; i++)
                    {
                        colourSelect = ColourSelect();
                        activeSequence.Add(colourSelect);

                    }

                    shouldBeDark = true;
                    shouldBeDisplayBetweenRounds = false;
                    waitBetweenCounter = waitBetweenLights;
                    colours[activeSequence[positionInSequence]].color = new Color(0, 0, 0, 1f);

                    startButtonColor.color = new Color(255, 255, 255, 1f);



                }

            }

        }


        if (shouldBeRed)
        {
            //game is over
            waitBetweenGamesCounter -= Time.deltaTime;

            if (waitBetweenGamesCounter < 0)
            {
                shouldBeAllWhite = true;

                EndScoreDisplay();

            }

        }


        if (isPhysical)
        {

            if (shouldBeLit)
            {
                //light process
                stayLitCounter -= Time.deltaTime;

                if (stayLitCounter < 0)
                {
                    colours[activeSequence[positionInSequence]].color = new Color(0, 0, 0, 1f);
                    shouldBeLit = false;
                    shouldBeDark = true;
                    waitBetweenCounter = waitBetweenLights;

                    if(positionInSequence < activeSequence.Count)
                    {
                       positionInSequence++;
                    }


                }
            }

            if (shouldBeDark)
            {
                //waiting between each light
                waitBetweenCounter -= Time.deltaTime;
                shouldBeWhite = false;

                if (waitBetweenCounter < 0)
                {
                    if (positionInSequence <= activeSequence.Count)
                    {
                        colours[activeSequence[positionInSequence]].color = new Color(255, 0, 0, 1f);
                    }

                    stayLitCounter = stayLit;
                    shouldBeClick = true;
                    shouldBeDark = false;

                    shouldBeAllWhite = false;

                }

            }

            if (shouldBeDisplayBetweenRounds)
            {
                //sequence is displayed
                shouldBeGreen = true;

                waitBetweenRoundsCounter -= Time.deltaTime;

                if (waitBetweenRoundsCounter < 0)
                {
                    shouldBeGreen = false;
                    shouldBeWhite = true;

                    colourSelect = ColourSelect();
                    activeSequence.Add(colourSelect);

                    shouldBeDark = true;
                    shouldBeDisplayBetweenRounds = false;
                    waitBetweenCounter = waitBetweenLights;
                    colours[activeSequence[positionInSequence]].color = new Color(0, 0, 0, 1f);


                }

            }
        }


        if (shouldBeClick)
        {
            //when following the sequence
            gameActive = true;

            if (positionInSequence >= activeSequence.Count)
            {
                isPlaying = true;
                shouldBeClick = false;
            }

        }


    }


    public void StartDigitalGame()
    {
        theGO.SetActive(true);
        isDigital = true;
        isPhysical = false;
        gameActive = false;

        activeSequence.Clear();
        shouldBeGreen = false;
        shouldBeBlack = false;
        shouldBeWhite = false;
        shouldBeRed = false;
        shouldBeAllWhite = true;


        positionInSequence = 0;
        inputInSequence = 0;


        //randomly generate colourSelect
        colourSelect = ColourSelect();

        activeSequence.Add(colourSelect);

        stayLitCounter = stayLit;
        shouldBeDark = true;

        startButtonColor.color = new Color(0, 0, 0, 1f);

    }

    public void StartPhysicalGame()
    {
        theGO.SetActive(true);
        isPhysical = true;
        isDigital = false;
        shouldBeAllWhite = true;

        activeSequence.Clear();
        shouldBeGreen = false;
        shouldBeBlack = false;
        positionInSequence = 0;
        inputInSequence = 0;


        //randomly generate colourSelect
        colourSelect = ColourSelect();

        activeSequence.Add(colourSelect);

        stayLitCounter = stayLit;
        shouldBeDark = true;

    }

    public void ColourPressed(int whichButton)
    {
        if(gameActive)
        {
            if (isDigital)
            {

                if (activeSequence[inputInSequence] == whichButton)
                {
                    Debug.Log("Correct");
                    inputInSequence++;

                    if (inputInSequence >= activeSequence.Count)
                    {
                        positionInSequence = 0;
                        inputInSequence = 0;

                        //colours[activeSequence[positionInSequence]].color = new Color(0, 0, 0, 1f);

                        waitBetweenRoundsCounter = waitBetweenRounds;
                        stayLitCounter = stayLit;

                        shouldBeDisplayBetweenRounds = true;
                        gameActive = false;

                        finalResults = activeSequence.Count;

                    }
                }
                else
                {
                    Debug.Log("Wrong");
                    shouldBeRed = true;
                    waitBetweenGamesCounter = waitBetweenGames;
                    finalResultsCounter = 0;
                    gameActive = false;

                    activeSequence.Clear();

                }
            }


            if (isPhysical && isPlaying)
            {

                if (activeSequence[inputInSequence] == whichButton)
                {
                    Debug.Log("Correct");

                    inputInSequence++;

                    if (inputInSequence >= activeSequence.Count)
                    {
                        positionInSequence = 0;
                        inputInSequence = 0;

                        //colours[activeSequence[positionInSequence]].color = new Color(255, 0, 0, 1f);

                        waitBetweenRoundsCounter = waitBetweenRounds;
                        stayLitCounter = stayLit;

                        shouldBeDisplayBetweenRounds = true;
                        isPlaying = false;
                        gameActive = false;

                        finalResults = activeSequence.Count;

                    }
                }
                else
                {
                    Debug.Log("Wrong");
                    shouldBeRed = true;
                    waitBetweenGamesCounter = waitBetweenGames;
                    finalResultsCounter = 0;
                    gameActive = false;

                    activeSequence.Clear();

                }
            }

            if (isPhysical & shouldBeClick)
            {

                if (activeSequence[inputInSequence] == whichButton)
                {
                    //Debug.Log("Correct");

                    inputInSequence++;
                    shouldBeLit = true;


                    if (inputInSequence >= activeSequence.Count)
                    {
                        //positionInSequence = 0;
                        inputInSequence = 0;

                        colours[activeSequence[positionInSequence]].color = new Color(255, 255, 255, 1f);

                        //waitBetweenRoundsCounter = waitBetweenRounds;
                        stayLitCounter = stayLit;

                        //shouldBeWaitBetweenRounds = true;
                        //gameActive = true;
                        //shouldBeClick = false;
                        //isPlaying = true;
                        //finalResults = activeSequence.Count;

                    }

                }
            }

        }
        

        
    }

    public void EndScoreDisplay()
    {
        //shouldBeAllWhite = true;

        shouldBeBlack = true;
        shouldBeGreen = true;
        activeSequence.Add(finalResultsCounter);
        
        finalResultsCounter++;
        if(finalResultsCounter >= finalResults)
        {
            finalResultsCounter = finalResults;
            shouldBeRed = false;


        }

    }

    public void DeActiveDigital()
    {
        theGO.SetActive(false);

    }

    public void DeActivePhysical()
    {
        theGO.SetActive(false);

    }

    public int ColourSelect()
    {
        int randomGenerator;
        randomGenerator = Random.Range(0, colours.Length);
        for (int j = 0, p = 0; j != 1;)
        {
         
            for (int i = 0; i < activeSequence.Count; i++)
            {
                if (randomGenerator == activeSequence[i])
                {
                    randomGenerator = Random.Range(0, colours.Length);
                    p++;

                }
            }

            if(p == 0)
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
}
