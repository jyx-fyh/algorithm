//
// Created by ButcherX on 23-11-17.
//
#include<iostream>
#include<string>
using std::string;
void moveToRelay(int n);
void moveToDestination(int n)
{
    if(n == 1)
    {
        std::cout<< "move to Destination" << std::endl;
        return;
    }
    moveToRelay(n-1);
    moveToDestination(1);
    moveToDestination(n-1);
}

void moveToRelay(int n)
{
    if(n == 1)
    {
        std::cout<< "move to Relay" << std::endl;
        return;
    }
    moveToDestination(n - 1);
    moveToRelay(1);
    moveToRelay(n-1);
}

void hanoi(int n)
{
    moveToRelay(n - 1);
    moveToDestination(1);
    moveToDestination(n-1);
}
//=================================
void move(int n, char from, char to)
{
    if(n == 1)
    {
        std::cout <<"move from " << from << " to " << to << std::endl;
        return;
    }
    char other = 'b' - (from-'b') - (to-'b');
    move(n - 1, from, other);
    move(1, from, to);
    move(n - 1, other, to);
}


void hanoi1(int n)
{
    move(n - 1, 'a', 'b');
    move(1, 'a', 'c');
    move(n - 1, 'b', 'c');
}
int main()
{
    hanoi1(3);
}