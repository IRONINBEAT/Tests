#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define N 4000

//Очищение строки
void emptyTheString(char* s, int len)
{
	for (int i = 0; i <= len; i++)
		s[i] = '0';
	s[len + 1] = '\0';
}

//Добавляет нулей в конец числа для верного перемещения.
char* plusZeros(char* s, int count)
{
	int index = 0;
	char* sZero = new char[count + strlen(s) + 1];

	for (index; index < strlen(s); index++)
		sZero[index] = s[index];
	for (index; index < strlen(s) + count; index++)
		sZero[index] = '0';
	sZero[count + strlen(s)] = '\0';

	return sZero;
}

//Очищает массив от лишней информации
char* ClearString(char* numbers, int length)
{
	int cz = 0;

	for (int i = 0; i < length; i++)
		if (!(((int)numbers[i] >= '0' && (int)numbers[i] <= '9') || ((int)numbers[i] >= 'A' && (int)numbers[i] < 'Z')))
			cz++;
		else
			break;

	char* c = new char[length - cz];

	for (int i = cz; i < length; i++)
		c[i - cz] = numbers[i];
	c[length - cz] = '\0';
	return c;
}

//Складывает два числа и возвращает сумму. Сначала большая, потом меньшая
char* Plusing(char* firstNumber, char* secondNumber, int firstNumLength, int secondNumLength, int numeralSystem)
{
	int div = 0, difference = firstNumLength - secondNumLength, one, two;
	char* sum = new char[firstNumLength + 1];

	emptyTheString(sum, firstNumLength);

	for (int i = firstNumLength - 1; i >= 0; i--)
	{
		one = (int)firstNumber[i] - '0', two = 0;
		if (firstNumber[i] > '@')
			one = (int)firstNumber[i] - '7';

		if (i - difference >= 0)
			if (secondNumber[i - difference] > '@')
				two = (int)secondNumber[i - difference] - '7';
			else
				two = (int)secondNumber[i - difference] - '0';
		else
			two = 0;

		sum[i + 1] = (char)((one + two + div) % numeralSystem + '0');
		div = (one + two + div) / numeralSystem;

		if (sum[i + 1] > '9')
			sum[i + 1] += 7;
	}
	sum[0] = (div > 0) ? (char)(div + 48) : ' ';
	return sum;
}

//Вывод столбиков промежуточных вычислений и умножения.
void MultImage(char* firstNumber, char* secondNumber, int firstNumLength, int secondNumLength, int numeralSystem)
{
	char* TempSum = new char[firstNumLength + 1];
	char* MainSum = new char[firstNumLength + secondNumLength];
	int count = 0, countZero = 0, minus = 0;


	//Вывод столбика умножения
	printf("Произведение чисел:\n");

	//Вывод 1 числа
	for (int i = 0; i < secondNumLength; i++)
		printf(" ");
	printf("%s\n*\n", firstNumber);

	//Вывод 2 числа
	for (int i = 0; i < firstNumLength; i++)
		printf(" ");
	printf("%s\n", secondNumber);

	//вывод первой черты
	for (int i = 0; i < firstNumLength + secondNumLength; i++)
		printf("_");
	printf("\n");

	emptyTheString(MainSum, firstNumLength + secondNumLength - 1);

	for (int i = secondNumLength - 1; i >= 0; i--) //Проходимся по каждой цифре второго числа
	{
		emptyTheString(TempSum, firstNumLength);
		minus = 0;
		if (secondNumber[i] > '@')
			minus = 7;

		//Подсчёт произведения первого числа на цифру второго
		for (int j = 0; j < (int)secondNumber[i] - '0' - minus; j++)
			if ((int)secondNumber[i] - '0' - minus != 0)
			{
				TempSum = Plusing(TempSum, firstNumber, strlen(TempSum), firstNumLength, numeralSystem);
				TempSum = ClearString(TempSum, strlen(TempSum));
			}
			else
			{
				TempSum[0] = '0';
				TempSum[1] = '\0';
			}
		if (TempSum[0] == '0')
			TempSum[0] = ' ';
		for (int m = secondNumLength + firstNumLength - strlen(TempSum) - count; m > 0; m--)
			printf(" ");
		printf("%s\n", TempSum);
		if (TempSum[0] == ' ')
			TempSum[0] = '0';
		count++;
		MainSum = Plusing(MainSum, plusZeros(TempSum, count), strlen(MainSum), strlen(TempSum) + count - 1, numeralSystem);
	}

	if (secondNumLength > 1) //Вывод ответа, если 2 число содержит больше одного разряда
	{
		//Вывод второй черты
		for (int n = 0; n < firstNumLength + secondNumLength; n++)
			printf("_");
		printf("\n");

		for (int r = 0; r < strlen(MainSum); r++)
			if (!(((int)MainSum[r] > '0' && (int)MainSum[r] <= '9') || ((int)MainSum[r] >= 'A' && (int)MainSum[r] <= 'Z')))
				countZero++;
			else
				break;

		//Вывод результата произведения
		if (strlen(MainSum) - countZero + 1 == firstNumLength + secondNumLength)
			printf(" ");

		puts(&MainSum[countZero]);

	}
}

//Вывод результата
void outputOfResult(char* firstNumber, char* secondNumber, int numeralSystem)
{
	char c, check;

	while (true)
	{
		int firstNumLen, secondNumLen, count_first = 0, count_second = 0;

		do
		{
			printf("Введите систему счисления от 11-ричной до 16-ричной: ");

			if (!scanf_s("%d", &numeralSystem) || getchar() != '\n')
			{
				while (1)
				{
					c = getchar();
					if (c == '\n' || c == EOF)
						break;
				}
				printf("Система счисления не удовлетворяет требованию!\n\n");
			}
			else
			{
				if (numeralSystem >= 11 && numeralSystem <= 16)
					break;
				else
					printf("Система счисления не удовлетворяет требованию!\n\n");
			}


		} while (1);

		do {
			printf("Введите число: ");
			scanf("%s", firstNumber);

			for (int i = 0; i < strlen(firstNumber); i++)
			{
				if ((firstNumber[0] == '0') || !(isdigit(firstNumber[i]) || ((int)firstNumber[i] >= 'A' && (int)firstNumber[i] < ('A' + numeralSystem - 10))))
				{
					printf("Число не принадлежит заданной системе счисления или не является натуральным.\n");
					count_first++;
					break;
				}
				else
					break;
			}
			if (count_first == 0)
				break;
			else count_first = 0;
		} while (1);

		do {
			printf("Введите число: ");
			scanf("%s", secondNumber);
			for (int i = 0; i < strlen(secondNumber); i++)
			{
				if ((secondNumber[0] == '0') || !(isdigit(secondNumber[i]) || ((int)secondNumber[i] >= 'A' && (int)secondNumber[i] < ('A' + numeralSystem - 10))))
				{
					printf("Число не принадлежит заданной системе счисления или не является натуральным.\n");
					count_second++;
					break;
				}
				else
					break;
			}
			if (count_second == 0)
				break;
			else count_second = 0;
		} while (1);

		firstNumLen = strlen(firstNumber);
		secondNumLen = strlen(secondNumber);

		if (firstNumLen >= secondNumLen)
		{
			//Вывод столбика сложения
			printf("Результат сложения:\n %s\n+\n", firstNumber);
			for (int i = 0; i < firstNumLen - secondNumLen; i++)
				printf(" ");
			printf(" %s\n", secondNumber);

			for (int i = 0; i <= firstNumLen; i++)
				printf("_");

			printf("\n%s\n\n", Plusing(firstNumber, secondNumber, firstNumLen, secondNumLen, numeralSystem));
			MultImage(firstNumber, secondNumber, firstNumLen, secondNumLen, numeralSystem);
		}
		else
		{
			printf("Результат сложения:\n %s\n+\n", secondNumber);
			for (int i = 0; i < secondNumLen - firstNumLen; i++)
				printf(" ");
			printf(" %s\n", firstNumber);

			for (int i = 0; i <= secondNumLen; i++)
				printf("_");

			printf("\n%s\n\n", Plusing(secondNumber, firstNumber, secondNumLen, firstNumLen, numeralSystem));
			MultImage(secondNumber, firstNumber, secondNumLen, firstNumLen, numeralSystem);
		}
		printf("\n");
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int numeralSystem = -1;
	char firstNum[N], secondNum[N];

	printf("Программа выводит сложение и умножение двух натуральных чисел, заданных в выбранной системе счисления.\n");
	outputOfResult(firstNum, secondNum, numeralSystem);

	return 0;
}

