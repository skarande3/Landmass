/*
Name: Shravan Karande
Date: 10/11/23
Discription: This assignment explores dynamic arrays, focusing on generating landmasses and terraforming through the strategic application of dirt balls. It involves 3 key steps: initializing a raw array, transforming it into a normalized state, and finally crafting a polished array of characters.
Usage: 
./exe
./exe -s <integer>
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;  

#define RESET   "\033[0m"
#define GREEN   "\033[32m"      	/* Green */
#define BLUE    "\033[34m"      	/* Blue */
#define DARK_BLUE "\033[34m"    	/* Dark Blue */
#define YELLOW  "\033[33m"      	/* Yellow */
#define BROWN   "\033[38;2;165;42;42m"  /* Brown */
#define MAGENTA "\033[35m"      	/* Magenta */ 
#define ORANGE  "\033[38;2;255;165;0m"  /* Orange */

//Prototypes:

int** rawArray(int, int);

void printLand(int**, int, int);

void deAllMemForIntArray(int**, int); 
 
void deAllMemForCharArray(char** ,int);

int dropDirtBall(int**, int, int, int, int, int, int);

double frand(); 

int findMax(int**, int, int);

void normalizeMap(int**, int, int);

void polishLandmass(int**, int, int, int, char**);

void printPolishLandmass(char**, int, int);



//rawArray dynamically allocates a 2D integer array of size width by height, initializing all elements to zero. It returns a pointer to the allocated memory.

int** rawArray(int width, int height) {

	int** ptrArray; 
   
	ptrArray = new int*[height];
 
	for (int i = 0; i < height; i++) {
 
		*(ptrArray+i) = new int[width]; 
	
		//initiate the array to 0. 
		for (int j = 0; j < width; j++) {
           	 
			ptrArray[i][j] = 0;
		}
  	}
	
	return ptrArray;  
}





//printLand prints a 2D array of integers (land) with the specified width and height. It formats the output to align each element within the array, printing each row on a new line.

void printLand(int** land, int width, int height) {

	int row; 
	int coloum; 
        
	//we iterate through the each row and print the row and go to a new line and then print the next row.       
	for (row = 0; row < height; row++) {

		for (coloum = 0; coloum < width; coloum++) {

			cout <<setw(4) <<land[row][coloum]; 

		}
		cout << endl;
	} 

}





//frand generates a random double between 0 (inclusive) and 1 (exclusive) by dividing rand() by RAND_MAX + 1.

double frand()
{
    return (double)rand() / ((double)RAND_MAX+1);
} 





//deAllMemForIntArray basically deallocates memory that was used by the dynamic array of integers.   

void deAllMemForIntArray(int** array, int Height) {
	
	//deallocating individual rows.
	for(int i =0; i < Height; i++) {
		delete[] array[i]; 
	}
	//deallocating integer pointers array.
	delete[] array;
	
	//Reset the pointer to NULL to avoid using it after deallocation.
	array = NULL; 
}




//deAllMemForCharArray basically deallocates memory that was used by the dynamic array of characters.   

void deAllMemForCharArray(char** charArray, int Height) {

	for(int i = 0; i < Height; i++) {
 	       delete[] charArray[i]; 
       }

	delete[] charArray; 

	 
}               




//dropDirtBall simulates the effect of a dirt ball on a 2D landmass. Given parameters like center coordinates, radius, and power, it iterates over the affected area, calculates impact based on distance, and updates the landmass array. The resulting landmass is outputted to "raw_landmass.txt."

int dropDirtBall(int** landmass, int maxWidth, int maxHeight,int centerX, int centerY, int radius, int power){

	// Does a bounds check here. 
	if(centerX < 0 || centerX >= maxWidth ||
	   centerY < 0 || centerY >= maxHeight ||
	   landmass == NULL) {

          return -1;           

	}	 
	
	for(int y = -radius; y <= radius; y++) {

		for(int x = -radius; x <= radius; x++) { 

		// Calculate the coordinates in the landmass array.
		int resultX = centerX + x;
		int resultY = centerY + y; 
		
			// Does a bounds check again
			if(resultY >= 0 && resultY < maxHeight &&
			  resultX >= 0 && resultX < maxWidth) { 
		         
			double distance = sqrt((pow(x, 2)) + (pow(y, 2)));   

				if(distance <= radius){
												
				int impact_value = power - (int)floor(distance);  		
				   
				   // Updates the landmass array with the impact value
		          	   landmass[resultY][resultX] = landmass[resultY][resultX] + impact_value;
				
				}			
			}
		   
		    
		}
 	 	                 
     }
       // Write the resulting landmass to "raw_landmass.txt"
       ofstream outputFile("raw_landmass.txt");

        for (int row = 0; row < maxHeight; row++) { 
    	
	    for (int coloum = 0; coloum < maxWidth; coloum++) {
           
            outputFile << setw(4) << landmass[row][coloum];
            }
	outputFile << endl;
        }
	
	outputFile.close();

	//Return 0 to indicate successful execution
	return 0;
}




//findMax finds the maximum value in the array. 

int findMax(int** map, int width, int height) {
	 
	 // Initilizing maxVal to the first value.
         int maxVal= map[0][0];  
    
	 // Iterates through the array to check if any value is bigger then the first one, if it is, now that's the max value.
	 for (int row = 0; row < height; row++) {

                for (int column = 0; column < width; column++) {

                     if(map[row][column] > maxVal) {

                     maxVal = map[row][column];  
		     }
		}
	}
	// Returns the max value.
	return maxVal; 
}




//The normalizeMap function takes a 2D array representing a map, its width, and height as parameters. It normalizes the values of the map to the range [0, 255] by dividing each element by the maximum value in the map and then multiplying it by 255. 

void normalizeMap(int** map, int width, int height){ 

  int maxVal = findMax(map, width, height); 

	for (int row = 0; row < height; row++) {

                for ( int coloum = 0; coloum < width; coloum++) {

                     int currVal =   map[row][coloum];
                     
		     // Floating point division.        
	             float semiNorVal = float(currVal) / (float)maxVal; 
			
		     float norVal = semiNorVal * 255.0;
			
	             int FinalNorVal = (int)norVal; 

		     map[row][coloum] = FinalNorVal;
		}
	}

	// Norminlized values array is outputted to "normalized_landmass.txt" file. 
        ofstream outputFile("normalized_landmass.txt");

        for (int row = 0; row < height; row++) {
 	       for (int coloum = 0; coloum < width; coloum++) {

        	    outputFile << setw(4) << map[row][coloum];
        	}
        outputFile << endl;
        }

        outputFile.close();

}

 


//polishLandmass processes a 2D landmass array, categorizes points by elevation, assigns character symbols, and outputs the final representation to "final_landmass.txt".

void polishLandmass(int** landmass, int width, int height, int waterline, char** charArray) {

// Max value is found. 
findMax(landmass, width, height);

// Values of the landmass are normalized.
normalizeMap(landmass, width, height);


	int land_zone = 255 - waterline;
	
        //Extra credit, .bmp file	
        ofstream outfileBMP;
        
	outfileBMP.open("bitmap.bmp");
        
	outfileBMP << "P3\n"<< width << " "<< height<< "\n"<<"255\n";

	for (int row = 0; row < height; row++) {

                for (int coloum = 0; coloum < width; coloum++) {
		
		int arrayVal = landmass[row][coloum];

			if (arrayVal < floor(0.5 * waterline)) {
        
	        	charArray[row][coloum] = '#';  // Deep water
       	  			
				outfileBMP << "23 32 78";		
 	
		           } else if ((arrayVal >= floor(0.5 * waterline)) && (arrayVal <= waterline)) {
        	      
				outfileBMP << "45 33 43";   			

			    charArray[row][coloum] = '~';  // Shallow water
            
			      } else if ((arrayVal > waterline) && (arrayVal < (waterline + floor(0.15 * land_zone)))) {
               			
					outfileBMP << "65 23 87";
				
	                        charArray[row][coloum] = '.';  // Coast/beach
           			
	                        } else if ((arrayVal > waterline) && (arrayVal >= (waterline + floor(0.15 * land_zone))) && (arrayVal < (waterline + floor(0.4 * land_zone)))) {
                			outfileBMP << "44 43 66";
				
			            charArray[row][coloum] = '-';  // Plains/grass
           
				 } else if ((arrayVal > waterline) && (arrayVal >= (waterline + floor(0.4 * land_zone))) && (arrayVal < (waterline + floor(0.8 * land_zone)))) {
 					outfileBMP << "26 54 22";

               				 charArray[row][coloum] = '*';  // Forests
		           		
					   } else {

						outfileBMP << "75 64 24";
              				 
				            charArray[row][coloum] = '^';  // Mountains

		        		   }					   
                }
	
	 }
	
	// Polised vlaue char array is outputted to "final_landmass.tcxt" file. 
        ofstream outputFile("final_landmass.txt");
	
        for (int row = 0; row < height; row++) {
        for (int coloum = 0; coloum < width; coloum++) {

            outputFile << charArray[row][coloum];
        }
        outputFile << endl;
        }

        outputFile.close();

	
	
}	

//printPolishLandmass prints a 2D array of characters (land) with the specified width and height. It formats the output to align each element within the array, printing each row on a new line.

void printPolishLandmass(char** land, int width, int height){

        int row;
        int coloum;

        // We iterate through the each row and print the row and go to a new line and then print the next row.        
        for (row = 0; row < height; row++) {
             
		for (coloum = 0; coloum < width; coloum++) {

        		// Extra credit (adds colour to each distint character).
			if(land[row][coloum] == '#') {
		
	       		cout << setw(4) << DARK_BLUE << '#' << RESET;		
		
	       	        } else if(land[row][coloum] == '~') {

               		cout << setw(4) << BLUE << '~' << RESET; 
		 
			} else if(land[row][coloum] == '.') {

              		 cout << setw(4) << ORANGE  << '.' << RESET;

			} else if(land[row][coloum] == '-') {

              		 cout << setw(4) << GREEN << '-' << RESET;

               		 } else if(land[row][coloum] == '*') {

        	         cout << setw(4) <<  YELLOW  << '*' << RESET;
		
              		 } else {

              		 cout << setw(4) <<  MAGENTA << '^' << RESET;

			}

                }
           cout << endl;
      }                                                                                                                                                                           }



//The main function initializes variables for terrain generation, user input, and randomization. It prompts the user for grid dimensions, waterline, dirtball properties, and the number of dirtballs to drop. It then creates a raw land array, drops dirtballs, normalizes the array, polishes the landmass, and prints the final result. Finally, it deallocates memory.
                                                            
int main(int argc, char** argv) {

	// Variable declarations.
	int height; 
	int width; 
	int centerX;
	int centerY; 
	int power;
	int radius; 
	int numDirtBalls; 	
	int waterLine;
        char** charland; 
	
	       
        // User can provide a seed for the random number generator by executing -s (as seen in the usage) or it is set to time(0). 
	if (argc == 3) {
           srand(atoi(argv[2]));
        } else {
          srand(time(0));
        }       

	// User input parameters.
	cout << "Welcome to Shravan's CSE240 Terraformer!!"; 
	cout << endl;
        cout << "Enter grid width: "; 
	cin >> width;
	cout << "Enter grid height: ";                         
        cin >> height;  
	cout << "Enter value for waterline (40-200): ";
	cin >> waterLine; 
	cout << "Enter dirtball radius (minimum 2): ";
 	cin >> radius; 
	cout << "Enter dirtball power rating (minimum = radius): ";
	cin >> power;
	cout << "Enter number of dirtballs to drop: ";
	cin >> numDirtBalls;   

	// Creates a raw array.
	int** array = rawArray(width, height); 
           
	 // Making and allocating memeory for the char array. 
         charland = new char*[height];
   	 for (int i = 0; i < height; i++) {
         charland[i] = new char[width];	
         }  
	
		// While loop for dropping more than 1 dirt ball.
		while(numDirtBalls > 0) {
		
		// Generates random center coordinates.
		centerX = frand() *  width; 
        	centerY = frand() *  height;
	
		dropDirtBall(array, width, height, centerX, centerY, radius, power);		
        
		 numDirtBalls--; 
	        }

	// Print the raw land array on console. 
        printLand(array, width, height);
	cout << endl; 

	// Normalizes the array and prints it to the console. 
	normalizeMap(array, width, height);
	printLand(array, width, height);
	cout << endl; 
 	
	// Polishes the array and prints it to the console.
	polishLandmass(array, width, height, waterLine, charland); 
	printPolishLandmass(charland, width, height);	
	cout << endl; 

	// Deallocates memory for both the arrays to prevent memory leaks.
	deAllMemForIntArray(array, height); 
	deAllMemForCharArray(charland, height);


	return 0; 

}

