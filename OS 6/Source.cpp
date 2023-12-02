#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

const int NUM_PHILOSOPHERS = 5; 

mutex forks[NUM_PHILOSOPHERS]; // массив вилок из 5 мьютоксов (Используем для синхронизации доступа философов к вилкам. 
//Каждая вилка защищается своим мьютексом, чтобы только один философ мог взять вилку (захватить мьютекс) в определенный момент времени)

void philosopher(int index)
{
    int left_fork = index; // индекс левой вилки для текущего философа
    int right_fork = (index + 1) % NUM_PHILOSOPHERS; // определяет номер правой вилки для текущего философа. 

    while (true)
    {
        // Думать
        cout << "Philosopher " << index << " is thinking." << endl; // выводит кто из философов думает

        // Взять вилки
        unique_lock<mutex> left_lock(forks[left_fork]); // создает уникальный блокировщик для левой вилки, который блокирует мьютекс этой вилки.
        cout << "Philosopher " << index << " picks up fork " << left_fork << " (left)." << endl; // выводит кто из философ взял левую вилку.

        unique_lock<mutex> right_lock(forks[right_fork]); //создает уникальный блокировщик для правой вилки, который блокирует мьютекс этой вилки.
        cout << "Philosopher " << index << " picks up fork " << right_fork << " (right)." << endl; // выводит кто из философ взял правую вилку.

        // Есть
        cout << "Philosopher " << index << " is eating." << endl; // выводит кто из философ ест.

        // Отпустить вилки
        cout << "Philosopher " << index << " puts down fork " << left_fork << " (left)." << endl; // выводит кто из философ отпустил левую вилку.
        left_lock.unlock(); // освобождают мьютексы левой вилки, позволяя другим философам взять эту вилку.

        cout << "Philosopher " << index << " puts down fork " << right_fork << " (right)." << endl; // выводит кто из философ отпустил правую вилку.
        right_lock.unlock(); // освобождают мьютексы правой вилки, позволяя другим философам взять эту вилку.
    }
}

int main()
{
    thread philosophers[NUM_PHILOSOPHERS]; // объявляется массив потоков для каждого философа

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosophers[i] = thread(philosopher, i); // Здесь для каждого i создается поток, который будет выполнять логику философа.
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosophers[i].join(); // Этот цикл ожидает завершения всех потоков. Пока все потоки не завершат свое выполнение, программа не продолжит свою работу дальше
    }

    return 0;
}
