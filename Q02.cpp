#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Purchase
{
public:
    int purchaseNum;
    double totalPrice;
    string itemDetails;
    int statusCode;

    Purchase(double price, string details)
    {
        totalPrice = price;
        itemDetails = details;
        purchaseNum = 0;
        statusCode = 0;
    }

    Purchase()
    {
        purchaseNum = 0;
        totalPrice = 0;
        itemDetails = "";
        statusCode = 0;
    }
};

class LinkedNode
{
public:
    Purchase record;
    LinkedNode *nextPtr;
    LinkedNode(Purchase p)
    {
        record = p;
        nextPtr = NULL;
    }
};

class PurchaseStack
{
    public:
    LinkedNode *topElement;
    int numberCounter;

    PurchaseStack()
    {
        topElement = NULL;
        numberCounter = 1;
    }

    void addItem(Purchase p)
    {
        if (p.itemDetails.length() > 20)
        {
            p.itemDetails = p.itemDetails.substr(0, 17) + "...";
        }

        if (p.totalPrice >= 0)
        {
            p.statusCode = 1;
            if (p.totalPrice >= 1500)
            {
                p.totalPrice = p.totalPrice * 0.7;
            }
            else if (p.totalPrice >= 1000)
            {
                p.totalPrice = p.totalPrice * 0.85;
            }
            else if (p.totalPrice >= 500)
            {
                p.totalPrice = p.totalPrice * 0.95;
            }
        }
        else
        {
            p.statusCode = 0;
        }

        p.purchaseNum = numberCounter++;
        LinkedNode *newElement = new LinkedNode(p);
        newElement->nextPtr = topElement;
        topElement = newElement;
    }

    Purchase removeItem()
    {
        if (topElement == NULL)
        {
            Purchase blank;
            return blank;
        }

        LinkedNode *temporary = topElement;
        Purchase p = temporary->record;
        topElement = topElement->nextPtr;
        delete temporary;

        p.totalPrice = p.totalPrice * -1;
        p.itemDetails = p.itemDetails + " [REVERSED]";
        p.statusCode = 2;

        return p;
    }

    void showAll()
    {
        LinkedNode *current = topElement;
        while (current != NULL)
        {
            cout << "[purchaseNum=" << current->record.purchaseNum << ", totalPrice=" << fixed << setprecision(2)
                 << current->record.totalPrice << ", itemDetails=\"" << current->record.itemDetails
                 << "\", statusCode=" << current->record.statusCode << "]" << endl;
            current = current->nextPtr;
        }
    }
};

class CharacterStack
{
private:
    char storage[100];
    int topPos;

public:
    CharacterStack() { topPos = -1; }

    void insert(char c) { storage[++topPos] = c; }

    char extract() { return storage[topPos--]; }

    char peek() { return storage[topPos]; }

    bool checkEmpty() { return topPos == -1; }
};

class NumberStack
{
private:
    double storage[100];
    int topPos;

public:
    NumberStack() { topPos = -1; }

    void insert(double val) { storage[++topPos] = val; }

    double extract() { return storage[topPos--]; }

    double peek() { return storage[topPos]; }
};

int calculatePrecedence(char operation)
{
    if (operation == '+' || operation == '-')
        return 1;
    if (operation == '*' || operation == '/')
        return 2;
    return 0;
}

bool checkOperator(char character)
{
    return character == '+' || character == '-' || character == '*' || character == '/';
}

string convertToPostfix(string normalForm)
{
    CharacterStack tempStack;
    string reverseForm = "";

    for (int index = 0; index < normalForm.length(); index++)
    {
        char symbol = normalForm[index];

        if (symbol == ' ')
            continue;

        if ((symbol >= '0' && symbol <= '9') || symbol == '.')
        {
            reverseForm += symbol;
        }
        else if (symbol == '(')
        {
            if (reverseForm.length() > 0 && reverseForm[reverseForm.length() - 1] != ' ')
                reverseForm += ' ';
            tempStack.insert(symbol);
        }
        else if (symbol == ')')
        {
            if (reverseForm.length() > 0 && reverseForm[reverseForm.length() - 1] != ' ')
                reverseForm += ' ';
            while (!tempStack.checkEmpty() && tempStack.peek() != '(')
            {
                reverseForm += tempStack.peek();
                reverseForm += ' ';
                tempStack.extract();
            }
            if (!tempStack.checkEmpty())
                tempStack.extract();
        }
        else if (checkOperator(symbol))
        {
            if (reverseForm.length() > 0 && reverseForm[reverseForm.length() - 1] != ' ')
                reverseForm += ' ';
            while (!tempStack.checkEmpty() && tempStack.peek() != '(' &&
                   calculatePrecedence(tempStack.peek()) >= calculatePrecedence(symbol))
            {
                reverseForm += tempStack.peek();
                reverseForm += ' ';
                tempStack.extract();
            }
            tempStack.insert(symbol);
        }
    }

    if (reverseForm.length() > 0 && reverseForm[reverseForm.length() - 1] != ' ')
        reverseForm += ' ';

    while (!tempStack.checkEmpty())
    {
        reverseForm += tempStack.peek();
        reverseForm += ' ';
        tempStack.extract();
    }

    while (reverseForm.length() > 0 && reverseForm[reverseForm.length() - 1] == ' ')
    {
        reverseForm = reverseForm.substr(0, reverseForm.length() - 1);
    }

    return reverseForm;
}

double calculatePostfix(string reverseForm)
{
    NumberStack tempStack;
    string digitString = "";

    for (int index = 0; index <= reverseForm.length(); index++)
    {
        char symbol = (index < reverseForm.length()) ? reverseForm[index] : ' ';

        if (symbol == ' ')
        {
            if (digitString != "")
            {
                double numericValue = 0;
                int dotPosition = -1;

                for (int position = 0; position < digitString.length(); position++)
                {
                    if (digitString[position] == '.')
                    {
                        dotPosition = position;
                        break;
                    }
                }

                if (dotPosition == -1)
                {
                    for (int position = 0; position < digitString.length(); position++)
                    {
                        numericValue = numericValue * 10 + (digitString[position] - '0');
                    }
                }
                else
                {
                    for (int position = 0; position < dotPosition; position++)
                    {
                        numericValue = numericValue * 10 + (digitString[position] - '0');
                    }
                    double fractionPart = 0;
                    double divisor = 0.1;
                    for (int position = dotPosition + 1; position < digitString.length(); position++)
                    {
                        fractionPart += (digitString[position] - '0') * divisor;
                        divisor *= 0.1;
                    }
                    numericValue += fractionPart;
                }
                tempStack.insert(numericValue);
                digitString = "";
            }
        }
        else if ((symbol >= '0' && symbol <= '9') || symbol == '.')
        {
            digitString += symbol;
        }
        else if (checkOperator(symbol))
        {
            double secondOperand = tempStack.extract();
            double firstOperand = tempStack.extract();
            double answer = 0;

            if (symbol == '+')
                answer = firstOperand + secondOperand;
            else if (symbol == '-')
                answer = firstOperand - secondOperand;
            else if (symbol == '*')
                answer = firstOperand * secondOperand;
            else if (symbol == '/')
                answer = firstOperand / secondOperand;

            tempStack.insert(answer);
        }
    }

    return tempStack.peek();
}

int main()
{
    srand(time(0));

    Purchase salesList[7] = {
        Purchase(1200, "order: red backpack"),
        Purchase(450, "order: wool mittens"),
        Purchase(-300, "return: damaged sweater"),
        Purchase(1700, "order: suede boots"),
        Purchase(800, "order: athletic sneakers"),
        Purchase(-150, "return: incorrect size jeans"),
        Purchase(2000, "order: luxury parka extra warm")};

    PurchaseStack myStack;

    cout << "added purchases:" << endl;

    int positions[4];
    positions[0] = 0;
    positions[1] = 1;
    positions[2] = 3;
    positions[3] = 2;

    for (int count = 0; count < 4; count++)
    {
        Purchase sale = salesList[positions[count]];
        double initialPrice = sale.totalPrice;
        string initialDetails = sale.itemDetails;

        myStack.addItem(sale);

        cout << (count + 1) << ". " << initialDetails << " (" << initialPrice << ")";

        if (initialPrice >= 0)
        {
            if (initialPrice >= 1500)
            {
                cout << "reduction 30% → final: " << fixed << setprecision(2)
                     << (initialPrice * 0.7) << endl;
            }
            else if (initialPrice >= 1000)
            {
                cout << "reduction 15% → final: " << fixed << setprecision(2)
                     << (initialPrice * 0.85) << endl;
            }
            else if (initialPrice >= 500)
            {
                cout << "reduction 5% → final: " << fixed << setprecision(2)
                     << (initialPrice * 0.95) << endl;
            }
            else
            {
                cout << "no reduction" << endl;
            }
        }
        else
        {
            cout << endl;
        }
    }

    cout << endl
         << "intermediate formula computation:" << endl;
    string normalExpression = "(100 + 20) * 0.9 - 5";
    cout << "normal form: " << normalExpression << endl;

    string reverseExpression = convertToPostfix(normalExpression);
    cout << "reverse form: " << reverseExpression << endl;

    double finalAnswer = calculatePostfix(reverseExpression);
    cout << "computed answer: " << fixed << setprecision(2) << finalAnswer << endl;

    cout << endl
         << "extract (delete) one purchase:" << endl;
    Purchase extractedSale = myStack.removeItem();
    cout << "extracted purchase: " << extractedSale.itemDetails << endl;
    cout << "price changed from " << (extractedSale.totalPrice * -1) << " to +"
         << extractedSale.totalPrice << endl;
    cout << "status updated to " << extractedSale.statusCode << endl;

    cout << endl
         << "remaining stack content:" << endl;
    cout << "first → ";
    myStack.showAll();
    cout << "last →" << endl;

    return 0;
}