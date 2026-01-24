/*
It's the slow crawl of rush hour. At any point of time, each vehicle is either stopped or is moving at the extremely slow speed of 1 meter per second. Lately, vehicles come equipped with a simple "black box" that records all vehicle speed changes. In this problem, speeds change instantaneously.
The road is modeled as the real line (units in meters). So a car is identified with its position on the line. Also, cars are 4.4 meters long.
Given the initial positions of two cars that are driving along the real line in the positive direction and a transcript of their speed changes, do these cars ever collide? While such a collision would be very slow speed (a "bumper tap"), any collision could result in erroneous readings from the black box in the future so the portions of the transcripts after a collision might not make sense.

Input
There is only one test case. The first line contains two integers 0 ≤ X1, X2 ≤ 106 indicating the initial positions of the rears of the two vehicles in meters. You are guaranteed either X1+5 ≤ X2 or X2+5 ≤ X1. Initially (at time 0), the two cars are stopped.
The second line begins with a number 0 ≤ N1 ≤ 105 indicating the number of times the speed of the first car changed. 
The rest of the line contains N1 integers 0 < T1 < T2 < . . . < Tn1 ≤ 106 indicating the times
(in seconds) the first vehicle changed speeds. So at time T1 it begins driving at 1 m/s, at time T2 it stops, at time T3 it begins driving at 1 m/s, and so on.
The last line begins with a number 0 ≤ N2 ≤ 105 and is followed by N2 integers 0 < T0 1 < T0 2 < . . . < T0 n2 ≤ 106 that describe the times the second vehicle starts and stops.

Output
If the vehicles collide, output the message bumper tap at time S on a single line where S is the
number of seconds from time 0 that the vehicles first collide, rounded up to the nearest second. If the vehicles do not collide, output the message safe and sound on a single line.

0 5
3 1 4 5
3 1 4 6

bumper tap at time 6

10 0
2 1 2
1 1

bumper tap at time 8

2 1
1 1
3 4 7 10
safe and sound
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

int main(){
    double X1, X2;
    cin >> X1 >> X2;
    int N1;
    cin >> N1;
    vector<double> events1(N1);
    for (int i = 0; i < N1; i++){
        cin >> events1[i];
    }
    int N2;
    cin >> N2;
    vector<double> events2(N2);
    for (int i = 0; i < N2; i++){
        cin >> events2[i];
    }
    //-----------------------------------------------------------
    // determine which car trailing
    // X1 + 5 <= X2 or X2 + 5 <= X1.
    // If X1 + 5 <= X2 then car1 is behind (trailing).
    bool trailingIsCar1;
    if (X1 + 5 <= X2) 
    {
        trailingIsCar1 = true;
    } 
    else 
    {
        trailingIsCar1 = false;
    }
    
    int speed1 = 0, speed2 = 0;
    double pos1 = X1, pos2 = X2;
    
    double currentTime = 0.0;
    
    //transcript pointers
    int idx1 = 0, idx2 = 0;
    
    const double carLength = 4.4;
    const double INF = INT_MAX;
    
    while (true) 
    {
        // determine next event time for each car
        double nextEvent1 = idx1 < N1 ? events1[idx1] : INF;
        double nextEvent2 = idx2 < N2 ? events2[idx2] : INF;
        double nextTime = min(nextEvent1, nextEvent2);
        
        // time interval for which speeds remain constant
        double dt = (nextTime == INF ? INF : nextTime - currentTime);
        
        // collision condition: trailing car's front >= leader's rear.

        if (dt > 0 && dt != INF) 
        {
            if (trailingIsCar1 && speed1 > speed2) // car1 can hit car2 peeche se 
            {
                double gap = pos2 - (pos1 + carLength);
                // If gap <= 0 then collision already occurred
                if (gap <= 0) 
                {
                    cout << "bumper tap at time " << (int)ceil(currentTime) << "\n";
                    return 0;
                }
                double collisionTime = currentTime + gap; // since closing speed is 1 m/s.
                if (collisionTime <= nextTime) 
                {
                    cout << "bumper tap at time " << (int)ceil(collisionTime) << "\n";
                    return 0;
                }
            } 
            else if (!trailingIsCar1 && speed2 > speed1) // car2 can hit car1 peeche se 
            {
                double gap = pos1 - (pos2 + carLength);
                if (gap <= 0) 
                {
                    cout << "bumper tap at time " << (int)ceil(currentTime) << "\n";
                    return 0;
                }
                double collisionTime = currentTime + gap;
                if (collisionTime <= nextTime) 
                {
                    cout << "bumper tap at time " << (int)ceil(collisionTime) << "\n";
                    return 0;
                }
            }
        } 
        else if (dt == INF) // No more events -----> constant speed reached for both cars
        {
            if (trailingIsCar1 && speed1 > speed2) // car1 is defintely hitting car2 peeche se
            {
                double gap = pos2 - (pos1 + carLength);
                if (gap <= 0) 
                {
                    cout << "bumper tap at time " << (int)ceil(currentTime) << "\n";
                    return 0;
                }
                double collisionTime = currentTime + gap;
                cout << "bumper tap at time " << (int)ceil(collisionTime) << "\n";
                return 0;
            } 
            else if (!trailingIsCar1 && speed2 > speed1) // car2 is defintely hitting car1 peeche se
            {
                double gap = pos1 - (pos2 + carLength);
                if (gap <= 0) 
                {
                    cout << "bumper tap at time " << (int)ceil(currentTime) << "\n";
                    return 0;
                }
                double collisionTime = currentTime + gap;
                cout << "bumper tap at time " << (int)ceil(collisionTime) << "\n";
                return 0;
            } 
            else 
            {
                cout << "safe and sound" << "\n";
                return 0;
            }
        }
        
        // update the positions of the cars
        pos1 += speed1 * dt;
        pos2 += speed2 * dt;
        currentTime = nextTime;
        
        // process events that occur at currentTime.
        if (nextTime == nextEvent1) 
        {
            // Toggle car1's speed.
            speed1 = 1 - speed1;
            idx1++;
        }
        if (nextTime == nextEvent2) 
        {
            // Toggle car2's speed.
            speed2 = 1 - speed2;
            idx2++;
        }
    }
    
    return 0;
}
