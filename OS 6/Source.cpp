#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

const int NUM_PHILOSOPHERS = 5; 

mutex forks[NUM_PHILOSOPHERS]; // ������ ����� �� 5 ��������� (���������� ��� ������������� ������� ��������� � ������. 
//������ ����� ���������� ����� ���������, ����� ������ ���� ������� ��� ����� ����� (��������� �������) � ������������ ������ �������)

void philosopher(int index)
{
    int left_fork = index; // ������ ����� ����� ��� �������� ��������
    int right_fork = (index + 1) % NUM_PHILOSOPHERS; // ���������� ����� ������ ����� ��� �������� ��������. 

    while (true)
    {
        // ������
        cout << "Philosopher " << index << " is thinking." << endl; // ������� ��� �� ��������� ������

        // ����� �����
        unique_lock<mutex> left_lock(forks[left_fork]); // ������� ���������� ����������� ��� ����� �����, ������� ��������� ������� ���� �����.
        cout << "Philosopher " << index << " picks up fork " << left_fork << " (left)." << endl; // ������� ��� �� ������� ���� ����� �����.

        unique_lock<mutex> right_lock(forks[right_fork]); //������� ���������� ����������� ��� ������ �����, ������� ��������� ������� ���� �����.
        cout << "Philosopher " << index << " picks up fork " << right_fork << " (right)." << endl; // ������� ��� �� ������� ���� ������ �����.

        // ����
        cout << "Philosopher " << index << " is eating." << endl; // ������� ��� �� ������� ���.

        // ��������� �����
        cout << "Philosopher " << index << " puts down fork " << left_fork << " (left)." << endl; // ������� ��� �� ������� �������� ����� �����.
        left_lock.unlock(); // ����������� �������� ����� �����, �������� ������ ��������� ����� ��� �����.

        cout << "Philosopher " << index << " puts down fork " << right_fork << " (right)." << endl; // ������� ��� �� ������� �������� ������ �����.
        right_lock.unlock(); // ����������� �������� ������ �����, �������� ������ ��������� ����� ��� �����.
    }
}

int main()
{
    thread philosophers[NUM_PHILOSOPHERS]; // ����������� ������ ������� ��� ������� ��������

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosophers[i] = thread(philosopher, i); // ����� ��� ������� i ��������� �����, ������� ����� ��������� ������ ��������.
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosophers[i].join(); // ���� ���� ������� ���������� ���� �������. ���� ��� ������ �� �������� ���� ����������, ��������� �� ��������� ���� ������ ������
    }

    return 0;
}
