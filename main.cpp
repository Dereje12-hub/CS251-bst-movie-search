// <<Dereje Gudeta>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.



#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "bst.h"
#define Debug 1

using namespace std;

struct MovieData
{
	int PubYear;
	int Num5Stars;
	int Num4Stars;
	int Num3Stars;
	int Num2Stars;
	int Num1Stars;
};

/* trims whitespace from beginning and end of string.
   Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
   Modified: to handle empty strings, and strings of all blanks. */

string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
	  
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}



/*InputMovies
   Inputs the data from the "movies" file, which contains N>0 lines, where
  
   each line contains: id pubYear name */

void writeMovies(string moviesFilename, binarysearchtree<string, MovieData> &bstName , binarysearchtree<int, MovieData> &bstID)
{
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   names;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
		// we have more data, so input publication year and movie name:
		moviesFile >> pubYear;
		getline(moviesFile, names);  // movie name fills rest of input line:

		// trim potential whitespace from both ends of movie name:
		names = trim(names);  

		MovieData* data= new MovieData{pubYear,0,0,0,0,0};

		
		bstID.insert(id, data);
        bstName.insert(names, data);


		// debugging:
	   // cout << id << "," << pubYear << "," << name << endl;

		moviesFile >> id;  // get next ID, or set EOF flag if no more data:
    }
  cout << "Num movies:" << bstID.size() << endl;
}



void giveRating(string reviewsfileName, binarysearchtree<int, MovieData> &bstID)
{
	ifstream reviewsFile(reviewsfileName);
	int reviewID, movieId, rating;
	int numReviews = 0;
	string name;
	
	if (!reviewsFile.good())
	{
		cout << "**Error: unable to open movies file " << reviewsfileName << " , exiting" << endl;
		return;
	}
	
	reviewsFile >> reviewID;
	
while (!reviewsFile.eof())
	{
		reviewsFile >> movieId;
		reviewsFile >> rating;
		
		MovieData** dataID = bstID.search(movieId);
		if (dataID)
		{
			if (rating ==1)
				(*dataID)->Num1Stars++;
			
			if (rating ==2)	
				(*dataID)->Num2Stars++;
				
			if (rating ==3)
				(*dataID)->Num3Stars++;
				
			if (rating ==4)
				(*dataID)->Num4Stars++;
				
			if (rating ==5)
				(*dataID)->Num5Stars++;	
            // else
				// break;
			
	    }
	   reviewsFile >> reviewID;
	   numReviews++;		
	}
	
	cout << "Num reviews: "<< numReviews << endl;
}	//end give rating function		
			
			
//boolian to check character 						
bool checkCharacter(string input)
{
	const char* str = input.c_str();
	int i = 0;
	
	while (str[i])
	{
		if (isalpha(str[i]))
			return true;
		i++;
	}
	return false;
}



// bool checkDigit( int input)
// {
// 	const int* str = int.c_str();
// 	char a = " ";
	
// 	while (str[a])
// 	{ 
// 		if (isdigit(str[a])
// 			return true;
// 		a++	
// 	}
// 			return false;
// }




// function to find size and height		
void display(binarysearchtree<int, MovieData> bst)
{
	bst.inorder();
	cout << bst.size() << " " << bst.height() << endl;
}



// main

int main()
{
	//declaraiton of input, movieName, movieId, and a pointer
	string input, movieName;
	int movieId;
	MovieData** data;
	
  	string moviesFilename; // = "movies1.txt";
  	string reviewsFilename; // = "reviews1.txt";

	cout << "movies file?> " << "movies1.txt" << endl;
    cout << "reviews file?> " << "reviews1.txt" << endl;
		
	srand(1); //search random one number
	binarysearchtree<int, MovieData> bstID;
	binarysearchtree<string, MovieData> bstName;
	
	
	
	if (!Debug)
		cin >> moviesFilename;
	else 
		moviesFilename = "movies1.txt";
	
	
	if (!Debug)
    	cin >> reviewsFilename;
	else 
		reviewsFilename = "reviews1.txt";
	   // cout << endl;
    
	
	string junk;
	if (!Debug)
		getline(cin, junk); // discard EOL following last input:
	
	
     writeMovies(moviesFilename, bstName, bstID);
	 giveRating(reviewsFilename, bstID);
	
	 cout << "\nTree by movie id: size=" << bstID.size() <<  ", height=" << bstID.height();
	 cout << "\nTree by movie name: size=" << bstName.size() << ", height=" << bstName.height() << endl;

	
	
	
	while (true)
	{
		cout << "\nEnter a movie id of name (or # to quit) > ";
		getline(cin, input);
		trim(input);
		
		if (input == "#" )
			break;
		
		if (checkCharacter(input))
		{
			movieName = input;
			data = bstName.search(movieName);
			movieId = -1;
			
		}
		else 
		{
			movieId = atoi(input.c_str());
			movieName = "Unknown";
			data = bstID.search(movieId);
			
		}
		
		if(!data)
		{
			cout << "not found..." << endl;
			continue;
		}
		
		double num_sum = 0.0;
		double den_sum = 1.0;
        double avg_Rating = 0.0;
		num_sum = (5.0 * (*data)->Num5Stars + 4 * (*data)->Num4Stars + 3 * (*data)->Num3Stars + 2 * (*data)->Num2Stars + (*data)->Num1Stars);
		den_sum= ((*data)->Num5Stars + (*data)->Num4Stars + (*data)->Num3Stars + (*data)->Num2Stars + (*data)->Num1Stars);

		avg_Rating = num_sum / den_sum;
       

		cout << "Movie ID: " << movieId << endl
			 << "Movie Name: " << movieName << endl
			 << "Avg rating: " << avg_Rating << endl
			 << "4 stars: " << (*data)->Num4Stars << endl
			 << "3 stars: " << (*data)->Num3Stars << endl
			 << "2 stars: " << (*data)->Num2Stars << endl
			 << "1 stars: " << (*data)->Num1Stars << endl;
			
	}
	
	
  // done:
  return 0;
} //end main 