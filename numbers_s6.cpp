// Header Files
#include "formatted_cmdline_io_v09.h"
#include <fstream>

using namespace std;

// Global Constants
const int NO_BLOCKSIZE = 0;
const int MAX_VALUE = 500;
const int NUM_BLOCKSIZE = 8, DOUBLE_PRECISION = 2;

// Function Prototypes

/*
 Name: sortArray
 Process: sorts array from smallest to largest
 Function Input Parameters: array (int), item number (int)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: data file
 Device Output/Monitor: none
 Dependencies: none
 */
void sortArray( int array[], int numItems );

/*
 Name: findMean
 Process: finds the average value of the data
 Function Input Parameters: array (int), item number (int)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: data file
 Device Output/Monitor: none
 Dependencies: none
 */
double findMean( int array[], int numItems);

/*
 Name: findMedian
 Process: finds median value of data
 Function Input Parameters: array (int), item number (int)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: data file
 Device Output/Monitor: none
 Dependencies: none
 */
double findMedian( int array[], int numItems);

/*
 Name: findMode
 Process: finds the number of modes that occur in the data set
 Function Input Parameters: array (int), item number (int)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: data file
 Device Output/Monitor: none
 Dependencies: none
 */
int findMode( int array[], int numItems);

/*
 Name: displayData
 Process: displays the data processed
 Function Input Parameters: number of items (int), mean (double), median (double), mode (int)
 Function Output Parameters: none
 Function Output Return: none
 Device Input/Keyboard: none
 Device Output/Monitor: none
 Dependencies: formatted command line
 */
void displayData(int counter, double mean, double median, int mode);


// Main Function
int main()
{
    // initialize program/ variables
    ifstream fin;
    int numVal;
    char dummy;
    int dataArray[ MAX_VALUE ];
    int index = 0;
    int counter = 0;
    double mean, median;
    int mode;
    string fileName;
    
       // display title
          // function: printString
       printString( "NUMBER ANALYSIS PROGRAM", NO_BLOCKSIZE, "LEFT" );
       printEndLines(1);
       printString( "=======================", NO_BLOCKSIZE, "LEFT" );
       printEndLines(1);
    
    // acquire data
    
       // prompt for file name
          // function: promptForString
       fileName = promptForString( "Enter File Name: " );
       printEndLines(1);
    
       // clear, open file
       fin.clear();
       fin.open( fileName.c_str() );
    
       // acquire data
    
          // prime loop
             // function: ifstream >>
          fin >> numVal;
    
          // if file is good, create array with loop
          if ( fin.good() )
          {
             // assign initial value to array
             dataArray[ index ] = numVal;
    
             // loop while data is good
             while( fin.good() )
             {
                  // get data from file
                    // function: ifstream >>
                  fin >> dummy >> numVal;
              
                  // assign to array
                  dataArray[ index + 1 ] = numVal;
              
                  // update conditions
                  index ++;
                  counter ++;
             }
          }
    
    // check for valid data
     
       // otherwise, if file not good, display error message
       else if( !fin.good() )
       {
           // display error message
              // function: printString
           printString( "ERROR: Data access failure, program aborted", NO_BLOCKSIZE, "LEFT");
        
           // shut down program
        
              // hold program
                 //function: system/pause
              system( "PAUSE");
        
           // return
           return 0;
       }
    
       // if there are more than 500 values, display error message
       if(counter > MAX_VALUE)
       {
           // display error message
              // function: printString
           printString( "ERROR: Data access failure, program aborted", NO_BLOCKSIZE, "LEFT");
           
           // shut down program
              
              // hold program
                 //function: system/pause
              system( "PAUSE");
           
           // return
           return 0;
       }
    
       // close file
       fin.close();
    
    // find mean, median, and mode
       
       // sort array
          // function: sortArray
       sortArray( dataArray, counter );
    
       // find mean
          // function: findMean
       mean = findMean( dataArray, counter );
    
       // find median
          // function: findMedian
       median = findMedian( dataArray, counter );

    
       // find mode
          // function: findMode
       mode = findMode( dataArray, counter );

    // display data
       // function: displayData
    displayData(counter, mean, median, mode);

    // shut down program
    
       // hold program
          // function: system( "PAUSE" )
       system( "PAUSE" );
    
    // return
    return 0;
    
}

// Function Implementations

void sortArray( int array[], int numItems )
{
    // initialize function/variables
    bool swapped = true;
    int index;
        
    // loop until no more swaps
    while( swapped )
    {
        // set boolean to false and index to zero
        swapped = false;
        index = 0;
            
        // loop until next to last item
        while( index < numItems - 1 )
        {
            // check for first one greater 
            // than second one
            if( array[ index ] > array[ index + 1 ] )
            {
                // swap
                swap( array[ index ], array[ index + 1 ] );
                    
                // set swapped flag
                swapped = true;
            }
                
            // increment the inner loop index
            index++;
        }
    }
}

double findMean( int array[], int numItems)
{
    // initialize function/ variables
    int counter = 0;
    int index = 0;
    int sum = 0;
    double mean;
    
    // prime loop
    sum += array[ index ];
    index ++;
    counter ++;
    
    // loop to acquire sum
    while ( counter < numItems )
    {
        sum += array[ index ];
        index ++;
        counter ++;
    }
    
    // find mean
    mean = double (sum) / numItems;
    
    // return
    return mean;
}

double findMedian( int array[], int numItems)
{
    // initialize function/ variables
    int halfPoint, halfOne, halfTwo;
    double median;
    
    // find median index
    
    // if odd number of items, median index is one more than half
    if( numItems % 2 != 0 )
    {
        halfPoint = (numItems / 2) + 1;
        median = array[ halfPoint ];
    }
        
    // if even number of items, median indexes is half and one more than half
    if( numItems % 2 == 0 )
    {
        halfOne = numItems / 2 ;
        halfTwo = numItems / 2 +1;
    
        // find median value, average of two median index values
        median = ((array[ halfOne -1] + array[ halfTwo -1]) / 2.0);
    }
    // return
    return median;
}

int findMode( int array[], int numItems)
{
    // initialize function/ variables
    int index = 0, modeIndex = 0, indexMode = 0;
    int modeCount[ numItems + 1];
    int mode;
    
    // prime loop 
    modeCount[ modeIndex ] = 0;

    // loop until index is the same as the number of items
    while( index < numItems )
    {
        // if number does not equal the one in the index above it
        if( array[ index ] != array[ index + 1 ] )
        {
            // move to next index of new mode counting array
            modeIndex ++;
            // set value at index to 0
            modeCount[ modeIndex ] = 0;
        }
           
        // otherwise, if array at index is equal to one above it
        else if( array[ index ] == array[ index + 1 ] )
        {
            // increase value of mode count at index
            modeCount[ modeIndex ]++;
        }     
        
        // increase index
        index ++;

    }
       
    // sort array
       // function: sortArray
    sortArray( modeCount, modeIndex);
    
    // prime loop
    mode = 1;
    
    // loop while highest number in the mode counting array is equal to the number at the index below it
    while ( modeCount[ modeIndex -1 ] == modeCount[ modeIndex - 2])
    {
        // increase number of modes
        mode ++;
        
        // decrease index
        modeIndex --;
    }
    
    // return
    return mode;
}

void displayData( int counter, double mean, double median, int mode)
{
    // display subtitle
       // function: printString, printEndLines
    printString( "STATISTICAL PROCESSING DISPLAY", NO_BLOCKSIZE, "LEFT" );
    printEndLines(1);
    printString( "==============================", NO_BLOCKSIZE, "LEFT" );   
    printEndLines(1);
    
    
    // display item count
       // function: printString, printInt, printEndlines
    printString( "Data item count      :", NO_BLOCKSIZE, "LEFT");
    printInt( counter, NUM_BLOCKSIZE, "RIGHT" );
    printEndLines(1);
    
    // display mean
       // function: printString, printDouble, printEndlines
    printString( "Data mean            :", NO_BLOCKSIZE, "LEFT");
    printDouble( mean, DOUBLE_PRECISION, NUM_BLOCKSIZE, "RIGHT" );
    printEndLines(1);
    
    // display median
       // function: printString, printDouble, printEndlines
    printString( "Data median          :", NO_BLOCKSIZE, "LEFT");
    printDouble( median, DOUBLE_PRECISION, NUM_BLOCKSIZE, "RIGHT" );
    printEndLines(1);
    
    // display number of modes
       // function: printString, printInt, printEndlines
    printString( "Data mode            :", NO_BLOCKSIZE, "LEFT");
    printInt( mode, NUM_BLOCKSIZE, "RIGHT" );
    printEndLines(1);
}



