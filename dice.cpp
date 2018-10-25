
#include <iostream>
#include <cstdlib> // for std::and() and std::srand()
#include <ctime> // for std::time()

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (RAND_MAX + 1.0);  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}
// this function returns the result of each roll in an array
int * dice(int range)
{
    using namespace std;
    static int *dice_num = new int[range] ; // this is how to declare an array with unknown size
    for (int count=0; count <= range-1; ++count)
    {
        int randomNum = getRandomNumber(1,6);
        dice_num[count]= randomNum;
    }
    return dice_num;
}
// this dice function returns the number of times each value appears in an array
int * dice_count(int range)
{
    using namespace std;
    static int dice_result[6]= {} ;
    for (int count=1; count <= range-1; ++count)
    {
        int randomNum = getRandomNumber(1,6);
        switch(randomNum)
        {
            case 1 : dice_result[0] += 1;
                break;
            case 2 : dice_result[1] += 1;
                break;
            case 3 : dice_result[2] += 1;
                break;
            case 4 : dice_result[3] += 1;
                break;
            case 5 : dice_result[4] += 1;
                break;
            case 6 : dice_result[5] += 1;
                break;
        }

        //cout << randomNum << "\t";
        // If we've printed 5 numbers, start a new row
        //if (count % 10 == 0)
        //    cout << "\n";
    }
    return dice_result;
}

int main()
{

    using namespace std;
    srand(static_cast<unsigned int>(std::time(0))); // set initial seed value to system clock

    //Question 1: print out the frequency of each number
    int range1 = 1000;
    int *dice_result= dice_count(range1);
    cout<<"Question 1"<<"\n";
    for (int count = 0; count <= 5; ++count)
    {
        float freq = (float)dice_result[count]/ (float)range1;
        cout << " the frequency of dicing a " << count+1 << " is: "<< freq <<"\n";
    }


    //Question 2: print out the frequency for getting high and low numbers
    int range2 = 10000;
    int eql_count = 0;
    cout<<"Question 2"<<'\n';
    for (int count = 0;count<range2;++count)
    {
        int *result= dice_count(100);
        float low_freq = (float)(result[0]+result[1]+result[2])/(float)range2;
        float high_freq = (float)(result[3]+result[4]+result[5])/(float)range2;
        if (low_freq == high_freq)
            eql_count += 1;
    }
    cout << "there are "<< eql_count <<" times that low and high have the exact same frequency"<<"\n";

    //roll a pair of dice 100,000 times see what each total value come up
    int val_count[11]= {};
    int turns = 100000;
    cout<<"Question 3"<<'\n';
    for (int count = 0; count < turns; ++count) // run this experiment 100,000 times
    {
        //int dice_nums[6]= {};
        int *result = dice(2); //dice a pair each turn
        int pair_sum = result[0] + result[1];
        switch(pair_sum)
        {
            case 2 : val_count[0] += 1;
                break;
            case 3 : val_count[1] += 1;
                break;
            case 4 : val_count[2] += 1;
                break;
            case 5 : val_count[3] += 1;
                break;
            case 6 : val_count[4] += 1;
                break;
            case 7 : val_count[5] += 1;
                break;
            case 8 : val_count[6] += 1;
                break;
            case 9 : val_count[7] += 1;
                break;
            case 10 : val_count[8] += 1;
                break;
            case 11 : val_count[9] += 1;
                break;
            case 12 : val_count[10] += 1;
                break;
        }
    }
    for (int i=0;i <11;++i)
    {
        float freq3 = (float) val_count[i]/ (float) turns;
        cout <<"the sum, "<<i+2<<", shows"<< freq3 <<" times."<<"\n";
    }
    return 0;
}
