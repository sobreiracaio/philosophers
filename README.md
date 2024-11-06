# Philosophers

This project simulates the dining philosophers problem using threads and mutexes.

Five philosophers dine together at the same table. Each philosopher has their own plate at the table. There is a fork between each plate. The dish served is a kind of spaghetti which has to be eaten with two forks. Each philosopher can only alternately think and eat. Moreover, a philosopher can only eat their spaghetti when they have both a left and right fork. Thus two forks will only be available when their two nearest neighbors are thinking, not eating. After an individual philosopher finishes eating, they will put down both forks. The problem is how to design an algorithm that manages to keep the philosophers alive (dont't let them starve).

This project provides a solution to this problem by creating a simulation of the dining philosophers scenario. It utilizes threads to represent each philosopher and mutexes to represent the forks they use to eat. The program ensures that the philosophers follow a set of rules to avoid deadlocks and provide fairness in resource allocation.

## Compilation

To run this project, go to the "src" directory and build the project by using the Makefile provided by typing:

   ```
   make
   ```

This will compile the source files and generate an executable named `philo`.

## Run

Once you have built the project, you can run it with the following command:

```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

- `<number_of_philosophers>`: Number of philosophers sitting around the table.
- `<time_to_die>`: Maximum time interval in milliseconds that a philosopher can survive until starve and die.
- `<time_to_eat>`: Time in milliseconds a philosopher takes to it.
- `<time_to_sleep>`: Time in milliseconds the philosopher spends sleeping after eating.
- `[number_of_times_each_philosopher_must_eat]` (optional): Number of times each philosopher must eat before the simulation ends. It's optional, if not provided, the simulation will continue indefinitely until a philosopher starve, or not depending on parameters.

Example usage:

```
./philo 5 800 200 200
```

This command will run the simulation with 5 philosophers, a time to die of 800 milliseconds, a time to eat of 200 milliseconds, and a time to sleep of 200 milliseconds. In this example, the simulation will continue indefinitely and any philosopher will die.
