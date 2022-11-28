

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

/*bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    std::vector<unsigned int> workerDays;
    for (unsigned int i =0; i < avail.size(); i++) workerDays.push_back(0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerDays, 0);
}



bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<unsigned int> workerDays,
    unsigned int currentDay
)
{
    unsigned int maxDays = avail.size();
    if (currentDay >= maxDays) 
    {
      return true;
    }

    
    
    
    
    
    
    
    int needed = dailyNeed;
    std::vector<Worker_T> daySched;


    for (unsigned int i = 0; i < avail[currentDay].size(); i++)
    {
        if (avail[currentDay][i] && workerDays[i] < maxShifts && needed > 0)
        {
            workerDays[i]++;
            daySched.push_back(i);
            needed--;
        }
        if (needed == 0) 
        {
            sched.push_back(daySched);
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, workerDays, currentDay+1))
            {
              return true;
            }
            else
            {

            }
        }
    }
    return false;
}*/




bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    std::vector<unsigned int> daysPerWorker; //count how many days each worker has worked
    for (unsigned int i = 0; i < avail[0].size(); i++) daysPerWorker.push_back(0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, daysPerWorker);


}
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<unsigned int> daysPerWorker
)
{

  int size = sched.size();
  if (size > 0)
  {
    //return true if we're on the last day and we have our daily need for workers
    if (size >= avail.size() && sched[size-1].size() == dailyNeed) return true;
  }

  std::vector<Worker_T> nextDay;
  if (sched.size() == 0) sched.push_back(nextDay); //add new day schedule if our schedule is empty
  else if (sched[sched.size()-1].size() == dailyNeed) sched.push_back(nextDay); //add new day schedule if we have enough workers for daily need
  int currentDay = sched.size()-1;





  for (unsigned int i = 0; i < avail[currentDay].size(); i++) //go through every worker today
  {
    //if the worker hasn't been added, they're available. and they don't have their maxShifts
    if ((std::find(sched[currentDay].begin(), sched[currentDay].end(), i) == sched[currentDay].end()) && (avail[currentDay][i] == 1) && (daysPerWorker[i] < maxShifts))
    {
      sched[currentDay].push_back(i); //add worker to schedule
      daysPerWorker[i]++; //keep track of how many days theyve worked
      if (scheduleHelper(avail, dailyNeed, maxShifts, sched, daysPerWorker)) return true; //if it passes, then this schedule works as a proper schedule
      sched[currentDay].pop_back(); //doesnt work, check with next worker
      daysPerWorker[i]--;
    }
  }

  if (sched[currentDay].size() == 0) sched.pop_back(); //if we checked all workers and the sched doesn't work, pop back and try different combos for previous day
  return false;

}