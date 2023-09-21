// 55.2.MathGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, MixLevel = 4};
enum enOpertionType {Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5};

struct stQuestion
{
    short FisrtNumber = 0;
    short SecondNUmber = 0;
    enQuestionsLevel QuestLevel;
    enOpertionType OpType;
    short PlayerAnswer = 0;
    short CorrectAnswer = 0;
    bool AnswerResult = false;
};

struct stQiz
{
    short NumberOfQuestions = 0;
    stQuestion QuestionsList[100];
    enQuestionsLevel QuestLevel;
    enOpertionType OpType;
    short NumerOfCorrectAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool isPass = false;
};


int ReadNumberOfQuestions()
{
    int NumberOfQuestions = 0;

    do
    {
        cout << "\n Enter the number of questions 1-10: ";
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 0 || NumberOfQuestions > 10);

    return NumberOfQuestions;
}

enQuestionsLevel ReadQuesionsLevel()
{
    int QuestionsLevel = 1;

    do
    {
        cout << "\n Enter the Questions Level: [1]Easy, [2]Med, [3]Hard, [4]Mix: ";
        cin >> QuestionsLevel;

    } while (QuestionsLevel < 1 || QuestionsLevel > 4);

    return (enQuestionsLevel)QuestionsLevel;
}

enOpertionType ReadOperationType()
{
    int OperstionType = 1;

    do
    {
        cout << "\n Enter the Operation type: [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix: ";
        cin >> OperstionType;

    } while (OperstionType < 1 || OperstionType > 5);

    return (enOpertionType)OperstionType;
}

int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

float SimpleCalculator(float Number1, float Number2, enOpertionType OperationType) {

    switch (OperationType)
    {
    case  enOpertionType::Add: //chaeck if user enter OperationType == enOperationType::Add which +
        return Number1 + Number2;
    case  enOpertionType::Sub:
        return Number1 - Number2;
    case  enOpertionType::Mul:
        return Number1 * Number2;
    case  enOpertionType::Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

float ReadPlayerAnswer()
{
    float PlayerAnswer = 0;

    do
    {
         cin >> PlayerAnswer;

    } while (PlayerAnswer < 0);

    return PlayerAnswer;
}

void SetScreenColor(bool AnswerResult)
{
    if (AnswerResult)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

void CorrectQuestionAnswer(stQiz &Quiz, short QuestionNumber)
{
    if (Quiz.QuestionsList[QuestionNumber].PlayerAnswer != Quiz.QuestionsList[QuestionNumber].CorrectAnswer)
    {
        Quiz.QuestionsList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;

        cout << "Worng Answer :-( \n";           
        cout << "The right answer is: ";
        
        cout << Quiz.QuestionsList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }

    else
    {
        Quiz.QuestionsList[QuestionNumber].AnswerResult = true;
        Quiz.NumerOfCorrectAnswers++;

        cout << "Right Answer :-) \n";
        
        cout << "\n";
    }
    cout << endl;
    SetScreenColor(Quiz.QuestionsList[QuestionNumber].AnswerResult);
   
}

enOpertionType GetOpType()
{
    int RandomOpType = RandomNumber(1, 4);

    return (enOpertionType)RandomOpType;
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOpertionType OpType)
{
    stQuestion Question;
 
    if (QuestionLevel == enQuestionsLevel::MixLevel)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }
    
    if (OpType == enOpertionType::Mix)
    {
        OpType = GetOpType();
    }

    //the argument is enOpertionType, and the stQuiz enOpertionType is defined but in stQuestion is not so we do it here
    Question.OpType = OpType;

    //Question level come from either the player or the random metheod
    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:

        Question.FisrtNumber = RandomNumber(1, 10);
        Question.SecondNUmber = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.FisrtNumber, Question.SecondNUmber, Question.OpType);
        Question.QuestLevel = QuestionLevel;

        return Question;

    case enQuestionsLevel::MedLevel:

        Question.FisrtNumber = RandomNumber(10, 50);
        Question.SecondNUmber = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.FisrtNumber, Question.SecondNUmber, Question.OpType);
        
        Question.QuestLevel = QuestionLevel;
        return Question;

    case enQuestionsLevel::HardLevel:

        Question.FisrtNumber = RandomNumber(50, 100);
        Question.SecondNUmber = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.FisrtNumber, Question.SecondNUmber, Question.OpType);
        Question.QuestLevel = QuestionLevel;
        return Question;
    }

    return Question;
}

//Generate questions and fill the stQuiz QuestionList array
void GenerateQuestions(stQiz &Quiz)
{
    //< 0 because array starts from 0
    for (short NoQuestion = 0; NoQuestion < Quiz.NumberOfQuestions; NoQuestion++)
    {
        Quiz.QuestionsList[NoQuestion] = GenerateQuestion(Quiz.QuestLevel, Quiz.OpType);
    }
}

string GetTheOpTypeSynbol(enOpertionType OpType)
{
    switch (OpType)
    {
    case enOpertionType::Add:
        return "+";
     case enOpertionType::Sub:
        return "-";
     case enOpertionType::Mul:
        return "*";
     case enOpertionType::Div:
        return "/";
     default:
        return "Mix";
     }
}

void PrintTheQuestion(stQiz Quiz, short QuestionNumber)
{
    cout << "\n";
    //print each question from the array
    cout << "Question [" << QuestionNumber+1 << "/" << Quiz.NumberOfQuestions << "]\n";
    cout << "\n" << Quiz.QuestionsList[QuestionNumber].FisrtNumber;
    cout << "\n" << Quiz.QuestionsList[QuestionNumber].SecondNUmber << " ";
    cout << GetTheOpTypeSynbol(Quiz.QuestionsList[QuestionNumber].OpType);
    cout << "\n______\n";
}

void AskAndCorrectQuestionListAnswers(stQiz &Quiz)
{
    //ask aand print the questions

    for (short Question = 0; Question < Quiz.NumberOfQuestions; Question++)
    {
        PrintTheQuestion(Quiz, Question);

        Quiz.QuestionsList[Question].PlayerAnswer = ReadPlayerAnswer();
        CorrectQuestionAnswer(Quiz, Question);
    }
    //return true if ok isPass will be true
    Quiz.isPass = (Quiz.NumerOfCorrectAnswers >= Quiz.NumberOfWrongAnswers);
}

string isPlayerWin(bool Pass)
{
    if (Pass)
        return "Pass :)";
    else
        return "Fail :(";
}

string GetQuestionLevel(enQuestionsLevel QuestionLevel)
{
    string arrQuestionsLevel[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrQuestionsLevel[QuestionLevel - 1];
}


void PrintQuizResults(stQiz Quiz)
{
    cout << "\n___________________________________";
    cout << "\nFinal reults ";
    cout << isPlayerWin(Quiz.isPass);
    cout << "\n___________________________________";
    cout << "\nQuiestions Level " << GetQuestionLevel(Quiz.QuestLevel);
    cout << "\nOperation Type " << GetTheOpTypeSynbol(Quiz.OpType);
    cout << "\nNumber of Wrong answers " << Quiz.NumberOfWrongAnswers;
    cout << "\nNumber of Correct answers " << Quiz.NumerOfCorrectAnswers;
    cout << "\n___________________________________";
}
   
void PlayMathGame()
{
    stQiz Quiz;

    Quiz.NumberOfQuestions = ReadNumberOfQuestions();
    Quiz.QuestLevel = ReadQuesionsLevel();
    Quiz.OpType = ReadOperationType();

    //cout << Quiz.OpLevel;
    
    GenerateQuestions(Quiz);

    AskAndCorrectQuestionListAnswers(Quiz);
    PrintQuizResults(Quiz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{

    char PlayAgain = 'Y'; 
    do {

        ResetScreen();   
        PlayMathGame();   
        cout << endl << "Do you want to play again? Y/N? ";    
        cin >> PlayAgain; 

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}


int main()
{ 
    //Seeds the random number generator in C++, called only once   
    srand((unsigned)time(NULL));

    StartGame();
   
 
     
    return 0;
}
 