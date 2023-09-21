// 54.2.MathGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<cstdlib>
using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard =3, Mix = 4};
enum enOperationType { ADD = 1, SUB = 2, MUL = 3, DIV = 4, MIX = 5};

struct stQuestionInfo
{
    short QuestionsNumber = 0;
    short FirstNumber = 0;
    short SecondNumber = 0;
    enQuestionsLevel QuestionsLevel;
    enOperationType OperationType;
    short PlayerAnswer = 0;
    string PlayerAnswerValidation = " ";
    short RightAnswer = 0;
};
struct stGameResults
{
    string FinalResult = " ";
    short QuestionsNumber;
    enQuestionsLevel QuestionsLevel;
    enOperationType OperationType;
    short NoOfRightAnswers = 0;
    short NoOfWrongAnswers = 0;
};


void ResetScreen()
{
    system("cls");
    system("color 0F");
}

short RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

//get the constant enum
enQuestionsLevel ReadQuestionLevel()
{
    short Choice = 1;
    do
    {
        cout << "\nYour Choice: [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice >4);

    //convert short to enGameChoice enum
    return (enQuestionsLevel)Choice;
}

enOperationType ReadOperationType()
{
    short Choice = 1;
    do
    {
        cout << "\nYour Choice: [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 5);

    //convert short to enGameChoice enum
    return (enOperationType)Choice;
}

short GenerateNumbers(stQuestionInfo &QuestionInfo)
{
    if (QuestionInfo.QuestionsLevel == enQuestionsLevel::Mix)
        return RandomNumber(0, 1000);

    //if switch condition = case thing. var = constant
    switch(QuestionInfo.QuestionsLevel)

    {
    case enQuestionsLevel::Easy:
        return RandomNumber(0, 10);
     case enQuestionsLevel::Med:
        return RandomNumber(10, 100);
     case enQuestionsLevel::Hard:
        return RandomNumber(100, 1000);
     }
}

string PrintOperationType(stQuestionInfo &QuestionInfo)
{
    string i = "+";
    //if switch condition = case thing. var = constant
    switch (QuestionInfo.OperationType)

    {
    case enOperationType::ADD:
        i = "+";
        return i;
    case enOperationType::SUB:
        i = "-";
        return i;
    case enOperationType::MUL:
        i = "*";
        return i;
    case enOperationType::DIV:
        i = "/";
        return i;
    case enOperationType::MIX:
        
        switch (RandomNumber(1, 4))
        {
        case enOperationType::ADD:
            i = "+";
            return i;
        case enOperationType::SUB:
            i = "-";
            return i;
        case enOperationType::MUL:
            i = "*";
            return i;
        case enOperationType::DIV:
            i = "/";
            return i;

        }
    }
        
    
}

short ReadPlayerAnswer()
{
    short Answer = 0;
    cout << "\n";
    cin >> Answer;
    return Answer;
}

void PrintTheQuestions(stQuestionInfo &QuestionInfo, stGameResults &GameResults)
{
    string OperationType = PrintOperationType(QuestionInfo);

    cout << "\n" << QuestionInfo.FirstNumber;
    cout << "\n" << QuestionInfo.SecondNumber << " " << OperationType;
    cout << "\n" << "____________";

    QuestionInfo.PlayerAnswer = ReadPlayerAnswer();
    cout << "\n The right answer is: ";

    //if switch condition = case thing. var = constant
    if (OperationType == "+")
    {
        QuestionInfo.RightAnswer = QuestionInfo.FirstNumber + QuestionInfo.SecondNumber;
        cout << "\n" << QuestionInfo.RightAnswer;
    }
    else if (OperationType == "-")
    {
        QuestionInfo.RightAnswer = QuestionInfo.FirstNumber - QuestionInfo.SecondNumber;
        cout << "\n" << QuestionInfo.RightAnswer;
    }
    else if (OperationType == "*")
    {
        QuestionInfo.RightAnswer = QuestionInfo.FirstNumber * QuestionInfo.SecondNumber;
        cout << "\n" << QuestionInfo.RightAnswer;
    }
    else
    {
        if (QuestionInfo.SecondNumber < 0)
            cout << "\n" << 0;
        else
        {
            QuestionInfo.RightAnswer = QuestionInfo.FirstNumber / QuestionInfo.SecondNumber;
            cout << "\n" << QuestionInfo.RightAnswer;
        }
    }

    //Increase right Answers counters
    if (QuestionInfo.PlayerAnswer == QuestionInfo.RightAnswer)
    {
        GameResults.NoOfRightAnswers++;
    }
    else
    {
        GameResults.NoOfWrongAnswers++;
    }

}

 

 

string PlayerAnswerValidation(stQuestionInfo QuestionInfo)
{

    if (QuestionInfo.RightAnswer == QuestionInfo.PlayerAnswer)
    {
        return "\nYour Answer is Right!! :-)"; 
    }
    else
    {
        return "\nYour Answer is Wrong!! :-(";
    }
}

void SetAnswerScreenColor(stQuestionInfo QuestionInfo)
{
    

    if (QuestionInfo.PlayerAnswer == QuestionInfo.RightAnswer)
    {
        system("color 2F"); //turn screen to Green
    }
     
    else if (QuestionInfo.PlayerAnswer != QuestionInfo.RightAnswer) 
    {
        system("color 4F"); //turn screen to Red   
        cout << "\a";
    }
    else
    {
        system("color 6F"); //turn screen to Yellow
       
    }

}

string WhatFinalResult(short RightAnswersTimes, short WrongAnswersTimes)
{
    if (RightAnswersTimes > WrongAnswersTimes)
        return "\nYou successed! :-)";  
    else
        return "\nYou Faild :-(";
}

void GetQuestionLevel(enQuestionsLevel QuestionLevel)
{
    string QuestionsLevel[4] = { "Easy", "Med", "Hard", "Mix" };

    cout << QuestionsLevel[QuestionLevel - 1];
}

stGameResults FillGameResults(short NoOfQuestions, stQuestionInfo QuestionInfo, stGameResults GameResults)
{
  
 
    if (GameResults.NoOfRightAnswers > GameResults.NoOfWrongAnswers)
        cout << "\nYou successed! :-)";
    else
        cout << "\nYou Faild :-(";

    GameResults.FinalResult = WhatFinalResult(GameResults.NoOfRightAnswers, GameResults.NoOfWrongAnswers);
    GameResults.QuestionsNumber = NoOfQuestions;
    GameResults.NoOfRightAnswers = GameResults.NoOfRightAnswers;
    GameResults.NoOfWrongAnswers = GameResults.NoOfWrongAnswers;
    GameResults.QuestionsLevel = QuestionInfo.QuestionsLevel;
    
     
    return GameResults;
}

//Fill stGameResults variables in every Round and return the number of player wins computer wins and draw times 
stGameResults PlayGame(short HowManyQuestions)
{
    stQuestionInfo QuestionInfo;
    stGameResults GameResults;

    short RightAnswersTimes = 0, WrongAnswersTimes = 0;
    QuestionInfo.QuestionsLevel = ReadQuestionLevel();
    QuestionInfo.OperationType = ReadOperationType();

    for (short Question = 1; Question <= HowManyQuestions; Question++)
    {
        cout << "\nQuestion [" << Question << " / " << HowManyQuestions << "]\n";
        //Fill struct vars
        QuestionInfo.QuestionsNumber = Question;
        
        QuestionInfo.FirstNumber = GenerateNumbers(QuestionInfo);
        QuestionInfo.SecondNumber = GenerateNumbers(QuestionInfo);
         
        PrintTheQuestions(QuestionInfo, GameResults);

        cout << PlayerAnswerValidation(QuestionInfo);
        SetAnswerScreenColor(QuestionInfo);

        

        
    }
    return FillGameResults(HowManyQuestions, QuestionInfo, GameResults);
}
 
short ReadHowManyQestions()
{

    short NumberOfQuestions = 1;

    do
    {
        cout << " \nWelcome, How many questions do you want to answer : ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 0);

    return NumberOfQuestions;
}

string Tabs(int NumperOFTabs)
{
    string t = " ";

    for (int i = 1; i <= NumperOFTabs; i++)
    {
        t = t + '\t';
        cout << t;
    }
    return t;
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(3) << "\n__________________________________________________________";
    cout << Tabs(3) << "\nFinal Result  : " << GameResults.FinalResult;
    cout << Tabs(3) << "\n__________________________________________________________\n";
    cout << Tabs(3) << "\nNumber of questions         : " << GameResults.QuestionsNumber;
    cout << Tabs(3) << "\nQuestions level             : "; 
    GetQuestionLevel(GameResults.QuestionsLevel);
    cout << Tabs(3) << "\nNumber of right answers     : " << GameResults.NoOfRightAnswers;
    cout << Tabs(3) << "\nNumber of wrong answers     : " << GameResults.NoOfWrongAnswers;
    cout << Tabs(3) << "\n___________________________________________________________\n";

 }

void StartGame()
{

    char PlayAgain = 'Y';

    do
    {
        ResetScreen();

        stGameResults GameResults = PlayGame(ReadHowManyQestions());
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}


int main()
{
    //Seeds the random number generator in C++, called only once   
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}