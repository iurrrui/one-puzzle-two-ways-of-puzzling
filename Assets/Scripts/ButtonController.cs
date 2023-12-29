using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButtonController : MonoBehaviour
{
    private SpriteRenderer theSprite;
    private GameManager theGM;
    //private Animator animator;
    //private bool isPressed;

    public int thisButtonNumber;


    void Start()
    {
        //animator = GetComponent<Animator>();
        theSprite = GetComponent<SpriteRenderer>();
        theGM = FindObjectOfType<GameManager>();
    }


    void Update()
    {

        //animator.SetBool("isPressed", isPressed);

        if (theGM.shouldBeAllWhite)
        {
            theSprite.color = new Color(0, 0, 0, 1f);
        }

        if (theGM.shouldBeWhite && theGM.activeSequence.Contains(thisButtonNumber))
        {
            theSprite.color = new Color(0, 0, 0, 1f);
        }

        if (theGM.shouldBeRed)
        {
            theSprite.color = new Color(255, 255, 255, 1f);
        }



        if (theGM.shouldBeGreen && theGM.activeSequence.Contains(thisButtonNumber))
        {
            theSprite.color = new Color(0, 0, 0, 1f);
        }

        if (theGM.shouldBeBlack && theGM.activeSequence.Contains(thisButtonNumber))
        {
            theSprite.color = new Color(255, 255, 255, 1f);
        }

    }


    private void OnMouseDown()
    {
        theSprite.color = new Color(255, 255, 255, 1f);
        //isPressed = true;
    }


    private void OnMouseUp()
    {
        theSprite.color = new Color(0, 0, 0, 1f);
        //isPressed = false;
        theGM.ColourPressed(thisButtonNumber);

    }

}
