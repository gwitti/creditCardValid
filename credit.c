#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool checksum(long n);

int getLength(long original_n);

char *getCardType(long n);

int main(void)
{
    long card;
    {
        card = get_long("Number: ");
        if (checksum(card))
        {
            char *cardType = getCardType(card);
            printf("%s\n", cardType);
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

bool checksum(long n)
{
    // the Luhn's algorithm implementation
    int count = 0;
    int sum = 0;
    while (n != 0)
    {
        // getting last-to-second digits
        long last_digit = n % 10;
        n = n / 10;
        count++;
        if (count % 2 == 0)
        {
            last_digit = last_digit * 2;
            while (last_digit != 0)
            {
                sum += last_digit % 10;
                last_digit /= 10;
            }
        }
        else
        {
            sum += last_digit;
        }
    }
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int getLength(long original_n)
{
    char length[20];
    sprintf(length, "%ld", original_n);
    return strlen(length);
}

char *getCardType(long n)
{
    long original_n = n;
    char *cardType;
    long first_digit = n;
    while (first_digit >= 10)
    {
        // actually firs ditit, not disits
        first_digit = first_digit / 10;
    }
    if ((first_digit == 4) && (getLength(original_n) == 13 || getLength(original_n) == 16))
    {
        return "VISA";
    }
    while (n >= 100)
    {
        // getting first 2 digits
        n = n / 10;
    }
    int first_digits = n;
    if ((first_digits == 51 || first_digits == 52 || first_digits == 53 || first_digits == 54 || first_digits == 55) &&
        getLength(original_n) == 16)
    {
        cardType = "MASTERCARD";
    }
    else if ((first_digits == 34 || first_digits == 37) && getLength(original_n) == 15)
    {
        cardType = "AMEX";
    }
    else
    {
        cardType = "INVALID";
    }

    return cardType;
}