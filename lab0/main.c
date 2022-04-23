#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int CheckForB1(int b1){
    if ((b1 < 2) || (b1 > 16))  return 0;
    else return 1;
}

int CheckForB2(int b2){
    if ((b2 < 2) || (b2 > 16)) return 0;
    else return 1;
}

int CheckPoint(char* x){
    int lenstr = strlen(x);
    int SumPoint = 0;
    for (int i = 0; i < lenstr; ++i){
        if ((x[i] == '.') || (x[i] == ',')){
            x[i] = '.';
            ++SumPoint;
        }
    }
    return SumPoint;
}

int Rubbish(char* x){
    int lenstr = strlen(x);
    if (CheckPoint(x) == 1){
        if ((x[0] == '.') || (x[lenstr - 1] == '.')) return 0;
    }
    if (CheckPoint(x) > 1) return 0;
    for (int i = 0; i < lenstr; ++i){
        if ((x[i] == '(') || (x[i] == ')') || (x[i] == '=')) return 0;
    }
    return 1;
}

int CheckElements(char* x, int b1){
    int lenstr = strlen(x);
    for (int i = 0; i < lenstr; ++i){
        if (('0' <= x[i]) && (x[i] <= '9')){
            if ((x[i] - '0') >= b1) return 0;
        }
        else if (('A' <= x[i]) && (x[i] <= 'F')){
            if ((x[i] - 'A' + 10) >= b1) return 0;
        }
        else if (('a' <= x[i]) && (x[i] <= 'f')){
            if ((x[i] - 'a' + 10) >= b1) return 0;
            x[i] = x[i] - 32; //перезаписать прописные буквы на заглавные
        }
        else if ((x[i] > 'F') || (x[i] > 'f')) return 0;
    }
    return 1;
}

int Check(char* x, int b1, int b2){ //проверка x на b1
    if ((CheckForB1(b1) == 0) || (CheckForB2(b2) == 0)) return 0;
    CheckPoint(x);
    if (Rubbish(x) == 0) return 0;
    if (CheckElements(x, b1) == 0) return 0;
    return 1;

}

int FindPoint(char* x){
    int point = 0;
    int lenstr = strlen(x);
    for (int i = 0; i < lenstr; ++i){
        if (x[i] == '.')
            point = i;
    }
    return point;
}

long double Xto10Sys(char* x, int b1){
    float len_x = strlen(x);
    float ArrayXinTen[14];
    for (int i = 0, j = 0; i < len_x; ++i, ++j){
        if (('0' <= x[i]) && (x[i] <= '9'))
            ArrayXinTen[j] = x[i] - '0';
        else if (('A' <= x[i]) && (x[i] <= 'F'))
            ArrayXinTen[j] = x[i] - 'A' + 10;
        else
            --j;
    }
    long double FinalXinTen = 0;
    int point = FindPoint(x);
    if (point > 0){
        for (int i = 0, j = point - 1; i < len_x - 1; ++i, --j)
            FinalXinTen = FinalXinTen + ArrayXinTen[i] * pow(b1, j);
    }
    else {
        for (int i = 0, j = len_x - 1; i < len_x; ++i, --j)
            FinalXinTen = FinalXinTen + ArrayXinTen[i] * pow(b1, j);
    }
    return FinalXinTen;
}

void RealPart(long double Xin10, char* RealB2, int b2){
    long long int intXinTen = (long long int)Xin10;
    if (intXinTen == 0){
        RealB2[0] = '0';
        RealB2[1] = '\0';
        return;
    }
    for (int i = 0; ; ++i, intXinTen /= b2){
        if (intXinTen == 0){
            RealB2[i] = '\0';
            break;
        }
        if ((0 <= intXinTen % b2) && (intXinTen % b2 <= 9))
            RealB2[i] = (intXinTen % b2) + '0';
        else if ((10 <= intXinTen % b2) && (intXinTen % b2 <= 15))
            RealB2[i] = (intXinTen % b2) + 'A' - 10;
    }
}

void RevercePlace(char* RealB2, char* RealPartB2){
    long long int lenstr = strlen(RealB2);
    for (int i = 0, j = lenstr - 1; ; ++i, --j){
        if (i >= lenstr){
            RealPartB2[i] = '\0';
            break;
        }
        RealPartB2[i] = RealB2[j];
    }
}

void FractPart(long double Xin10, char* FractPartB2, int b2){
    long double fract = Xin10 - (float)(long long int)Xin10;
    for (int i = 0; i < 14; ++i){
        if (fract == 0.0){
            FractPartB2[i] = '0';
            FractPartB2[i + 1] = '\0';
            break;
        }
        long long int chislo = (long long int)(fract *= b2);
        if ((0 <= chislo) && (chislo <= 9))
            FractPartB2[i] = chislo + '0';
        else if ((10 <= chislo) && (chislo <= 15))
            FractPartB2[i] = chislo + 'A' - 10;
        fract = fract - (float)(int)fract;
    }
    FractPartB2[14] = '\0';
}

int main()
{
    int b1, b2;
    if (scanf("%d%d", &b1, &b2) != 2) return 0;
    char x[14];
    if (scanf("%13s", x) != 1) return 0;
    if (Check(x, b1, b2) == 0){
        printf("bad input\n");
        exit(0);
    }
    else {
        long double Xin10 = Xto10Sys(x, b1);
        char RealB2[50];
        RealPart(Xin10, RealB2, b2);

        char RealPartB2[50];
        RevercePlace(RealB2, RealPartB2);

        if (FindPoint(x) == 0){
            printf("%s\n", RealPartB2);
            exit(0);
        }
        else {
            char FractPartB2[50];
            FractPart(Xin10, FractPartB2, b2);
            printf("%s.%s", RealPartB2, FractPartB2);
            exit(0);
        }
    }
}
