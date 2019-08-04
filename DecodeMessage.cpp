#include <stdio.h>
#include <time.h>
#include <iostream>

using namespace std;

char *decode(int i);
int remember = 0;

int main()
{
	int num;
	FILE *inputFile, *outputFile;
	char date[30];
	char ch = fgetc(inputFile);
	FILE *file = fopen("Record.log", "a");
	fprintf(file, "0");
	fclose(file);



	if ((inputFile = fopen("Record.log", "r")) == NULL || (outputFile = fopen("Data.log", "a")) == NULL)
	{
			printf("ERROR!!!");
			return 1;
	}

	while (ch != EOF)
	{
			if (ch == '\t')
			{
					fprintf(outputFile, ">>\n");

					fscanf(inputFile, "%d", &num);
					while (num != 0)
					{
							fprintf(outputFile, "%s", decode(num));
							fscanf(inputFile, "%d", &num);
					}
			}
			else
			{
					fgets(date, 30, inputFile);
					fprintf(outputFile, "%c%s", ch, date);
			}

			ch = fgetc(inputFile);
	}

	fclose(inputFile);
	fclose(outputFile);

	return 0;
}

char *decode(int i)
{
	char *ch;

	if (remember == i)
	{
			ch = "";
			return ch;
	}
	else
	{
			remember = 0;
	}

	switch (i)
	{
	case 1:
			ch = "[LC]";
			remember = i;
			break;
	case 2:
			ch = "[RC]";
			remember = i;
			break;
	case 8:
			ch = "[<B]";
			break;
	case 9:
			ch = "[TAB]";
			break;
	case 13:
			ch = "\n";
			break;
	case 16:
			ch = "[SH]";
			remember = i;
			break;
	case 17:
			ch = "[CTR]";
			remember = i;
			break;
	case 18:
			ch = "[ALT]";
			break;
	case 19:
			ch = "[PAUSE]";
			ch = "";
			break;
	case 20:
			ch = "[CAP]";
			break;
	case 27:
			ch = "[ESC]";
			break;
	case 32:
			ch = " ";
			break;
	case 33:
			ch = "[PgUp]";
			break;
	case 34:
			ch = "[PgDn]";
			break;
	case 45:
			ch = "[INS]";
			break;
	case 46:
			ch = "[DEL]";
			break;
	case 47:
			ch = "/";
			break;
	case 48:
			ch = "0";
			break;
	case 49:
			ch = "1";
			break;
	case 50:
			ch = "2";
			break;
	case 51:
			ch = "3";
			break;
	case 52:
			ch = "4";
			break;
	case 53:
			ch = "5";
			break;
	case 54:
			ch = "6";
			break;
	case 55:
			ch = "7";
			break;
	case 56:
			ch = "8";
			break;
	case 57:
			ch = "9";
			break;
	case 65:
			ch = "a";
			break;
	case 66:
			ch = "b";
			break;
	case 67:
			ch = "c";
			break;
	case 68:
			ch = "d";
			break;
	case 69:
			ch = "e";
			break;
	case 70:
			ch = "f";
			break;
	case 71:
			ch = "g";
			break;
	case 72:
			ch = "h";
			break;
	case 73:
			ch = "i";
			break;
	case 74:
			ch = "j";
			break;
	case 75:
			ch = "k";
			break;
	case 76:
			ch = "l";
			break;
	case 77:
			ch = "m";
			break;
	case 78:
			ch = "n";
			break;
	case 79:
			ch = "o";
			break;
	case 80:
			ch = "p";
			break;
	case 81:
			ch = "q";
			break;
	case 82:
			ch = "r";
			break;
	case 83:
			ch = "s";
			break;
	case 84:
			ch = "t";
			break;
	case 85:
			ch = "u";
			break;
	case 86:
			ch = "v";
			break;
	case 87:
			ch = "w";
			break;
	case 88:
			ch = "x";
			break;
	case 89:
			ch = "y";
			break;
	case 90:
			ch = "z";
			break;
	case 91:
			ch = "[STRT]";
			break;
	case 92:
			ch = "\\";
			break;
	case 93:
			ch = "[MNU]";
			break;
	case 96:
			ch = "0";
			break;
	case 97:
			ch = "1";
			break;
	case 98:
			ch = "2";
			break;
	case 99:
			ch = "3";
			break;
	case 100:
			ch = "4";
			break;
	case 101:
			ch = "5";
			break;
	case 102:
			ch = "6";
			break;
	case 103:
			ch = "7";
			break;
	case 104:
			ch = "8";
			break;
	case 105:
			ch = "9";
			break;
	case 106:
			ch = "*";
			break;
	case 107:
			ch = "+";
			break;
	case 109:
			ch = "-";
			break;
	case 110:
			ch = ".";
			break;
	case 111:
			ch = "/";
			break;
	case 112:
			ch = "[f1]";
			break;
	case 113:
			ch = "[f2]";
			break;
	case 114:
			ch = "[f3]";
			break;
	case 115:
			ch = "[f4]";
			break;
	case 116:
			ch = "[f5]";
			break;
	case 117:
			ch = "[f6]";
			break;
	case 118:
			ch = "[f7]";
			break;
	case 119:
			ch = "[f8]";
			break;
	case 120:
			ch = "[f9]";
			break;
	case 121:
			ch = "[f10]";
			break;
	case 122:
			ch = "[f11]";
			break;
	case 123:
			ch = "[f12]";
			break;
	case 124:
			ch = "|";
			break;
	case 144:
			ch = "[NUM]";
			break;
	case 150:
			ch = "-";
			break;
	case 186:
			ch = ";";
			break;
	case 187:
			ch = "=";
			break;
	case 188:
			ch = ",";
			break;
	case 189:
			ch = "-";
			break;
	case 190:
			ch = ".";
			break;
	case 191:
			ch = "/";
			break;
	case 192:
			ch = "`";
			break;
	case 219:
			ch = "[";
			break;
	case 220:
			ch = "\\";
			break;
	case 221:
			ch = "]";
			break;
	case 222:
			ch = "'";
			break;
	default:
			ch = "";
			remember = i;
	}

	return ch;
}
