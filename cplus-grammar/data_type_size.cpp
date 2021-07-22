#include<iostream>
#include<limits>

using namespace std;

int main()
{
    char c;
    unsigned char uc;
    unsigned u;
    short s;
    int i;
    float f;

    cout << "bool: " << sizeof(bool) << endl;

    cout << "char: " << sizeof(char) << endl;
    cout << "c(char): " << sizeof(c) << endl;
    cout << "signed char: " << sizeof(signed char) << endl;

    cout << "unsigned char: " << sizeof(unsigned char) << endl;
    cout << "uc(unsigned char): " << sizeof(uc) << endl;

    cout << "signed: " << sizeof(signed) << endl;
    cout << "int: " << sizeof(int) << endl;
    cout << "i: " << sizeof(i) << endl;
    cout << "signed int: " << sizeof(signed int) << endl;

    cout << "unsigned: " << sizeof(unsigned) << sizeof(u) << endl;
    cout << "unsigned int: " << sizeof(unsigned int) << endl;

    cout << "short: " << sizeof(short) << sizeof(s) << endl;
    cout << "signed short: " << sizeof(signed short) << sizeof(s) << endl;
    cout << "short int: " << sizeof(short int) << endl;
    cout << "signed short int: " << sizeof(signed short int) << endl;

    cout << "unsigned short: " << sizeof(unsigned short) << endl;
    cout << "unsigned short int: " << sizeof(unsigned short int) << endl;

    cout << "long: " << sizeof(long) << endl;
    cout << "signed long: " << sizeof(signed long) << endl;
    cout << "long int: " << sizeof(long int) << endl;
    cout << "signed long int: " << sizeof(signed long int) << endl;
    cout << "long long: " << sizeof(long long) << endl;
    cout << "signed long long: " << sizeof(signed long long) << endl;
    cout << "long long int: " << sizeof(long long int) << endl;
    cout << "signed long long int: " << sizeof(signed long long int) << endl;

    cout << "unsigned long: " << sizeof(unsigned long) << endl;
    cout << "unsigned long int: " << sizeof(unsigned long int) << endl;
    cout << "unsigned long long: " << sizeof(unsigned long long) << endl;
    cout << "unsigned long long int: " << sizeof(unsigned long long int) << endl;

    cout << "float: " << sizeof(float) << endl;
    cout << "f: " << sizeof(f) << endl;

    cout << "double: " << sizeof(double) << endl;

    cout << "long double: " << sizeof(long double) << endl;


    cout << endl;
    cout << "max values:" << endl;
    cout << "bool: " << numeric_limits<bool>::max() << endl;
    cout << "bool: " << numeric_limits<bool>::min() << endl;

    cout << "char: " << numeric_limits<char>::max() << endl;
    cout << "char: " << numeric_limits<char>::min() << endl;
    cout << "signed char: " << numeric_limits<signed char>::max() << endl;
    cout << "signed char: " << numeric_limits<signed char>::min() << endl;

    cout << "unsigned char: " << numeric_limits<unsigned char>::max() << endl;
    cout << "unsigned char: " << numeric_limits<unsigned char>::min() << endl;

    cout << "signed: " << numeric_limits<signed>::max() << endl;
    cout << "signed: " << numeric_limits<signed>::min() << endl;
    cout << "int: " << numeric_limits<int>::max() << endl;
    cout << "int: " << numeric_limits<int>::min() << endl;
    cout << "signed int: " << numeric_limits<signed int>::max() << endl;
    cout << "signed int: " << numeric_limits<signed int>::min() << endl;

    cout << "unsigned: " << numeric_limits<unsigned>::max() << endl;
    cout << "unsigned: " << numeric_limits<unsigned>::min() << endl;
    cout << "unsigned int: " << numeric_limits<unsigned int>::max() << endl;
    cout << "unsigned int: " << numeric_limits<unsigned int>::min() << endl;

    cout << "short: " << numeric_limits<short>::max() << endl;
    cout << "short: " << numeric_limits<short>::min() << endl;
    cout << "signed short: " << numeric_limits<signed short>::max() << endl;
    cout << "signed short: " << numeric_limits<signed short>::min() << endl;
    cout << "short int: " << numeric_limits<short int>::max() << endl;
    cout << "short int: " << numeric_limits<short int>::min() << endl;
    cout << "signed short int: " << numeric_limits<signed short int>::max() << endl;
    cout << "signed short int: " << numeric_limits<signed short int>::min() << endl;

    cout << "unsigned short: " << numeric_limits<unsigned short>::max() << endl;
    cout << "unsigned short: " << numeric_limits<unsigned short>::min() << endl;
    cout << "unsigned short int: " << numeric_limits<unsigned short int>::max() << endl;
    cout << "unsigned short int: " << numeric_limits<unsigned short int>::min() << endl;

    cout << "long: " << numeric_limits<long>::max() << endl;
    cout << "long: " << numeric_limits<long>::min() << endl;
    cout << "signed long: " << numeric_limits<signed long>::max() << endl;
    cout << "signed long: " << numeric_limits<signed long>::min() << endl;
    cout << "long int: " << numeric_limits<long int>::max() << endl;
    cout << "long int: " << numeric_limits<long int>::min() << endl;
    cout << "signed long int: " << numeric_limits<signed long int>::max() << endl;
    cout << "signed long int: " << numeric_limits<signed long int>::min() << endl;
    cout << "long long: " << numeric_limits<long long>::max() << endl;
    cout << "long long: " << numeric_limits<long long>::min() << endl;
    cout << "signed long long: " << numeric_limits<signed long long>::max() << endl;
    cout << "signed long long: " << numeric_limits<signed long long>::min() << endl;
    cout << "long long int: " << numeric_limits<long long int>::max() << endl;
    cout << "long long int: " << numeric_limits<long long int>::min() << endl;
    cout << "signed long long int: " << numeric_limits<signed long long int>::max() << endl;
    cout << "signed long long int: " << numeric_limits<signed long long int>::min() << endl;

    cout << "unsigned long: " << numeric_limits<unsigned long>::max() << endl;
    cout << "unsigned long: " << numeric_limits<unsigned long>::min() << endl;
    cout << "unsigned long int: " << numeric_limits<unsigned long int>::max() << endl;
    cout << "unsigned long int: " << numeric_limits<unsigned long int>::min() << endl;
    cout << "unsigned long long: " << numeric_limits<unsigned long long>::max() << endl;
    cout << "unsigned long long: " << numeric_limits<unsigned long long>::min() << endl;
    cout << "unsigned long long int: " << numeric_limits<unsigned long long int>::max() << endl;
    cout << "unsigned long long int: " << numeric_limits<unsigned long long int>::min() << endl;

    cout << "float: " << numeric_limits<float>::max() << endl;
    cout << "float: " << numeric_limits<float>::min() << endl;

    cout << "double: " << numeric_limits<double>::max() << endl;
    cout << "double: " << numeric_limits<double>::min() << endl;

    cout << "long double: " << (numeric_limits<long double>::max)() << endl;
    cout << "long double: " << (numeric_limits<long double>::min)() << endl;


    int *pint;
    float *pfloat;

    cout << "int *: " << sizeof(int *) << endl;
    cout << "const int *: " << sizeof(const int *) << endl;
    cout << "pint: " << sizeof(pint) << endl;
    cout << "signed int *: " << sizeof(signed int *) << endl;
    cout << "unsigned int *: " << sizeof(unsigned int *) << endl;
    cout << "signed *: " << sizeof(signed *) << endl;
    cout << "unsigned *: " << sizeof(unsigned *) << endl;
    cout << "short *: " << sizeof(short *) << endl;
    cout << "signed short *: " << sizeof(signed short *) << endl;
    cout << "unsigned short *: " << sizeof(unsigned short *) << endl;
    cout << "long *: " << sizeof(short *) << endl;
    cout << "signed long *: " << sizeof(signed short *) << endl;
    cout << "unsigned long *: " << sizeof(unsigned short *) << endl;
    cout << "long long *: " << sizeof(short *) << endl;
    cout << "signed long long *: " << sizeof(signed short *) << endl;
    cout << "unsigned long long *: " << sizeof(unsigned short *) << endl;
    cout << "long long int *: " << sizeof(short *) << endl;
    cout << "signed long long int *: " << sizeof(signed short *) << endl;
    cout << "unsigned long long int *: " << sizeof(unsigned short *) << endl;

    cout << "float *: " << sizeof(float *) << endl;
    cout << "pfloat: " << sizeof(pfloat) << endl;
    cout << "double *: " << sizeof(double *) << endl;
    cout << "long double *: " << sizeof(long double *) << endl;
    cout << "bool *: " << sizeof(bool *) << endl;
    cout << "char *: " << sizeof(char *) << endl;
    cout << "signed char *: " << sizeof(signed char *) << endl;
    cout << "unsigned char *: " << sizeof(unsigned char *) << endl;
    cout << "void *: " << sizeof(void *) << endl;
    cout << "const void *: " << sizeof(const void *) << endl;

    return 1;
}



