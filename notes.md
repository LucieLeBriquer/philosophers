# Correction
## Mandatory Part
### Error Handling
This project has to be coded in C, following the Norm.<br/>
Any crash, undefined behavior, memory leak, or norm error means 0 to the project.<br/>
On shom slow hardware, the project might not work properly.<br/>
If some tests don't work on your machine try to discuss it honestly before counting it as false.

### Philo code
- Check the code of Philo for the following things and ask for explanation.
- Check if there is one thread per philosopher.
- Check there's only one fork per philosopher.
- Check if there is a mutex per fork and that it's used to check the fork value and/or change it.
- Check the output should never produce a scrambled view.
- Check how the death of a philosopher is checked and if there is a mutex to protect that a philosopher dies and start eating at the same time.

### Philo test
- Do not test with more than 200 philosophers
- Do not test with `time_to_die` or `time_to_eat` or `time_to_sleep` under 60ms
- Test with `1 800 200 200`, the philosopher should not eat and should die!
- Test with `5 800 200 200`, no one should die!
- Test with `5 800 200 200 7`, no one should die and the simulation should stop when all the philosopher has eaten at least 7 times each.
- Test with `4 410 200 200`, no one should die!
- Test with `4 310 200 100`, a philosopher should die!
- Test with 2 philosophers and check the different times (a death delayed by more than 10ms is unacceptable).
- Test with your values to check all the rules. Check if a philosopher dies at the right time, if they don't steal forks, etc.