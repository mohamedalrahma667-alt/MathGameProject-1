
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionLevels { Easy = 1, Med = 2, Hard = 3,Mix = 4 };

enum enOpType {Add = 1, Sub = 2,Mul = 3,Div = 4, MixOp = 5};

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enQuestionLevels QuestionLevel;
    enOpType OpType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
 
    stQuestion QuestionList[100];
    short NumberOfQuestion;
    enQuestionLevels QuesLevels;
    enOpType OpType;
    short NumberOfRightAnswer  = 0;
    short NumberOfWrongAnswer = 0;
    bool IsPass = false;

};

short ReadNumberOfQuestions()
{
    short NumberOfQuestion = 0;
    do
    {

        cout << "How Many Questions do want to Answer ? ";
        cin >> NumberOfQuestion;


    } while (NumberOfQuestion < 1 || NumberOfQuestion > 10);
    return NumberOfQuestion;
}

enQuestionLevels ReadQuestionLevels()
{
    short Ques = 0;
    do
    {
        cout << "\nEnter Questions Level [1]Easy, [2]Med, [3]Hard, [4]Mix ? ";
        cin >> Ques;
    } while (Ques < 1 || Ques > 4);
    return (enQuestionLevels) Ques;
}

enOpType ReadOpType()
{
    short OpType = 0;
    do
    {
        cout << "\nEnter Opertion Type : [1] Add, [2]Sub, [3]Mul, [4]Div, [5] Mix ? ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);
    return (enOpType) OpType;
}

int RandomNumber(int From, int To)
{

    int RandomNum = 0;
    RandomNum = rand() % (To - From + 1) + From;
    return RandomNum;

}

enOpType GetOpType()
{

       return (enOpType)RandomNumber(1, 4);
}

int SimpleCalculator(int Number1, int Number2, enOpType OpType)
{
    switch (OpType)
    {
    case enOpType::Add:
        return Number1 + Number2;
    case enOpType::Sub:
        return Number1 - Number2;
    case enOpType::Mul:
        return Number1 * Number2;
    case enOpType::Div:
        return  Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enQuestionLevels QuestionLevel,enOpType OpType)
{
    stQuestion Question;
    if (QuestionLevel == enQuestionLevels::Mix)
    {
        QuestionLevel = (enQuestionLevels)RandomNumber(1, 3);
    }
    if (OpType == enOpType::MixOp)
    {
        OpType = GetOpType();
    }
    Question.OpType = OpType;
    switch (QuestionLevel)
    {
    case enQuestionLevels::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case enQuestionLevels::Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case enQuestionLevels::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);

        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }

}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0;Question < Quizz.NumberOfQuestion;Question++)
    {

        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuesLevels,Quizz.OpType);
    }
}

string GetOpTypeSympol(enOpType OpType)
{
    switch (OpType)
    {
    case enOpType::Add:
        return "+";
        break;
    case enOpType::Sub:
        return "-";
        break;
    case enOpType::Mul:
        return "*";
        break;
    case enOpType::Div:
        return "/";
        break;
    case enOpType::MixOp:
        return "MIX";
        break;
    }


}

int ReadPlayerAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
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
    }
}

void CorrectAnswer(stQuizz& Quizz,short Question)
{

    if (Quizz.QuestionList[Question].PlayerAnswer != Quizz.QuestionList[Question].CorrectAnswer)
    {
        Quizz.QuestionList[Question].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;

        cout << "\nWrong Answer is :-(\n";
        cout << "\nThe Right Answer : ";
        cout << Quizz.QuestionList[Question].CorrectAnswer;
        cout << "\n";
    }
    else
    {
        Quizz.QuestionList[Question].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;

        cout << "\nRight Answer :-)\n";
    }
    cout << endl;

    SetScreenColor(Quizz.QuestionList[Question].AnswerResult);

}

void PrintTheQuestion(stQuizz& Quizz, short Question)
{

    cout << "\nQuestion [" << Question + 1 << "/" << Quizz.NumberOfQuestion << "]" << "\n\n";
    cout << Quizz.QuestionList[Question].Number1 << "\n";
    cout << Quizz.QuestionList[Question].Number2 << " " << GetOpTypeSympol(Quizz.QuestionList[Question].OpType);
    cout << "\n_____________________\n";
   

}

string GetTextOfPass(bool IsPass)
{
    if (IsPass)
        return "Pass:-)";
    else
        return "Fail:-(";
    
}

string GetQuesstionLevelsText(enQuestionLevels QuestionLevels)
{

    string ArraQuestionLevels[4] = { "Easy","Med","Hard","Mix" };

    return ArraQuestionLevels[QuestionLevels - 1];
}

string GetOpTypeText(enOpType OpType)
{
    switch (OpType)
    {
    case enOpType::Add:
        return "Add";
    case enOpType::Sub:
        return "Sub";
    case enOpType::Mul:
        return "Mul";
    case enOpType::Div:
        return "Div";
    case enOpType::MixOp:
        return "MixOp";
    }
}

void AskAndCorrectQuizzQuestions(stQuizz& Quizz)
{

    for (short Question = 0;Question < Quizz.NumberOfQuestion;Question++)
    {
        PrintTheQuestion(Quizz,Question);

        Quizz.QuestionList[Question].PlayerAnswer = ReadPlayerAnswer();

        CorrectAnswer(Quizz,Question);
    }
    Quizz.IsPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
    
}

void PrintFinalResult(stQuizz Quizz)
{

    cout << "\n________________________________________\n";
    cout << "    Final Results is " << GetTextOfPass(Quizz.IsPass);
    cout << "\n________________________________________\n";


    cout << "\nNumber Of Questions         : " << Quizz.NumberOfQuestion;
    cout << "\nQuestions Level             : " << GetQuesstionLevelsText(Quizz.QuesLevels);
    cout << "\nOpType                      : " << GetOpTypeText(Quizz.OpType);
    cout << "\nNumber Of Right Answer      : " << Quizz.NumberOfRightAnswer;
    cout << "\nNumber  Of Wrong Answer     : " << Quizz.NumberOfWrongAnswer;
    cout << "\n\n________________________________________\n";

}

void PlayMathGame()
{
    stQuizz Quizz;

    Quizz.NumberOfQuestion = ReadNumberOfQuestions();
    Quizz.QuesLevels = ReadQuestionLevels();
    Quizz.OpType = ReadOpType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuizzQuestions(Quizz);
    PrintFinalResult(Quizz);

}

void ResetScreen()
{

    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {

        ResetScreen();
        PlayMathGame();

        cout << endl << "Do you want to play again ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');

   



}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();
    
}

