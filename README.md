# Philosophers

![C](https://img.shields.io/badge/language-C-blue.svg)

### Overview

Philosophers is an implementation of the classic **Dining Philosophers Problem**, provided in two versions:
* Using **threads** and **mutexes**.
* Using **processes** and **semaphores**.

The project is part of the 42 curriculum and introduces students to the fundamentals of **concurrent programming** and **synchronization mechanisms** in C.

---
### Dining Philosophers Problem

A group of philosophers sit at a round table with a large bowl of spaghetti in the center. There are **as many forks as philosophers**. Since eating spaghetti with only one fork is impractical, each philosopher must acquire **two forks** before eating.

The philosophers cycle between eating, sleeping, and thinking. They do not communicate with each other. The simulation ends when a philosopher dies of starvation or, optionally, when all philosophers have eaten enough. Needless to say, philosophers should avoid dying!

This problem illustrates the challenges of managing shared resources in concurrent systems:
* **Deadlock**: All philosophers hold one fork and wait indefinitely for the other.
* **Starvation**: Some philosophers never manage to acquire both forks and thus cannot eat.
* **Race conditions**: Without proper synchronization, multiple philosophers may attempt to pick up the same fork or print output simultaneously, causing inconsistent results.

---
### Rules

#### Mandatory Part
* Each philosopher is represented by a separate **thread**.
* There is one fork between each pair of philosophers. To eat, a philosopher must pick up the fork on their left and the fork on their right.
* Each fork is protected by a **mutex**.

#### Bonus Part
* Each philosopher is represented by a separate **process**.
* Forks are abstracted and managed collectively through a **semaphore**.

---
### Implementation Details

#### Data structures
* **Philosopher data**: Each philosopher has a record with their ID, last meal time, meal count, and pointers to forks (threads version) and to the central state.
* **Central data**: Holds an array with all philosophers' data, simulation parameters, and forks.
* Philosophers never interact directly with each other. All coordination is done via the main thread or parent process.

#### Synchronization
* **Threads & Mutexes (Mandatory)**
  * Forks: each fork is protected by a mutex.
  * Output: protected by a mutex.
  * Monitoring: the main thread checks philosophers' last meal times and meal counts, with access protected by mutexes.
  * Termination: the main thread sets a shared flag on death/satisfaction; philosophers poll this flag and stop gracefully.

* **Processes & Semaphores (Bonus)**
	* Forks: controlled by a semaphore initialized to the number of philosophers.
	* Output: protected by a binary semaphore.
	* Monitoring: each philosopher detects their own death and satisfaction and exits with a corresponding status code.
	* Termination: the parent process collects exit statuses and terminates remaining processes if one dies.


#### Optimizations
* Asymmetric fork assignment (threads version): even-numbered philosophers pick left then right; odd-numbered pick right then left.
* Staggered start: philosophers wait briefly before starting their routine - even-numbered wait `time_to_eat / 2`, odd-numbered wait 1 ms.
* Think until hungry: after eating and sleeping, philosophers delay picking up forks until reaching a hunger threshold (`time_to_die * 0.75`).

---
### Installation

**Requirements**: `gcc`, `make`

```
git clone https://github.com/biertisch/philosophers.git
cd philosophers
cd philo && make		# mandatory
cd philo_bonus & make	# bonus
```

---
### Usage
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]		# mandatory
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]	# bonus
```

Example:
```
./philo 5 800 200 200 7
```

---
### About 42

42 is a computer science school founded in Paris in 2013. It follows a project-based, peer-to-peer pedagogy focused on low-level programming and algorithmic thinking.

---
### License & Contact

This repository is open for learning and reuse. Contributions, suggestions, and discussions are welcome — feel free to open an issue or reach out.