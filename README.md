# Philosophers 42

## Description

A solution loops clock thread âï¸, main thread and philosophers threads ð´. Main thread are constantly comparing all thread timestamp and current time aritmetic difference against - time to die ð.
Clock thread âï¸ is updating current time, needed, for threads ð´, for aritmetic logic. 

In main.c the allocate_philosophers() returns a pointer array of t_philosopher structs.  Structs are used to pass into start_philosopher_threads() where each initiated ð¦ thread has a proper struct.

wait_for_dead() checks if any of threads timestamps and current time aritmetic difference is bigger that death time ð and checks if all philosophers have eaten number of times ð´.

lock_all stops all philosopher threads by mutex lock mutex->global ð. Global mutex lock are in each philosopher thread, for purpose of preventing data races and for having control from the main thread.

lock_all will wait for all threads to jump into global mutex lock ð, because this methon does not use thread_join(). *Yes this method does not use thread_join()*. Experiments proven ð¬ that we can end child threads by locking them and quiting main.

So before proceeding to freeing memory it is important that threads, would be lockedð.
lock_all then locks clock thread âï¸ð.

Eventualy we proceed to terminate_all ð, which will delocate all allocated memory including mutexes, structs and contents of structs, pointer array.
We believe that return does terminate process, clean, and those philosopher thread souls â¨, disapears.


## Images

Here a simplified version displaying mutex lock in action
![alt text](https://drive.google.com/uc?export=view&id=1v9BvocnlpaMWtbdD679kMtw3AB6mSgbj)

Faster
![alt text](https://drive.google.com/uc?export=view&id=1V_Jc8A015CjqWHXLNShgUq5yTK6N8I5Z)

Example of structs sharing same memory
![alt text](https://drive.google.com/uc?export=view&id=1Wmjgiu3wpJVxAUxFjIJAUZnoo2xlnevI)
