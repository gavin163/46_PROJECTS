 // WordChecker.cpp
//
// ICS 46 Spring 2020
// Project #4: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include "WordChecker.hpp"
#include <algorithm>


WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{



    std::vector<std::string > suggestions;
    std::string azlist="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    //solution ::: swap 
    for (int i=0; i<word.size()-1;i++)
    {
        std::string tempword = word;
        std::swap(tempword[i],tempword[i+1]);
        if ( wordExists(tempword) and std::find(suggestions.begin(),suggestions.end(), tempword) == suggestions.end())
        {
            suggestions.push_back(tempword);
        }
    }


    // solution :::  insertion
    for (int i =0; i<word.size();++i)
    {
        for (int j=0;j<word.size(); ++j)
        {
            std::string sub_1 = word.substr(0,i);
            std::string sub_2 = word.substr(i);
            std::string tempword = sub_1 + azlist[j] +sub_2;
         
            if ( wordExists(tempword) and std::find(suggestions.begin(),suggestions.end(), tempword) == suggestions.end())
            {
                suggestions.push_back(tempword);
            }
        }
    }


    // solution ::: delete
    for (int i =0; i<word.size(); ++i)
    {
        std::string tempword = word;
        tempword.erase(i,1);
        if ( wordExists(tempword) and std::find(suggestions.begin(),suggestions.end(), tempword) == suggestions.end())
        {
            suggestions.push_back(tempword);
        }

    }



    //solution :::  replacing ::: replace each char in the word

    for (int i=0; i<word.size() ; ++i)
    {
        for (int j=0 ; j< azlist.size() ; j++)
        {
            std::string tempword = word;

            tempword[i] = azlist[j];
            if ( wordExists(tempword) and std::find(suggestions.begin(),suggestions.end(), tempword) == suggestions.end())
            {
                suggestions.push_back(tempword);
            }

        }
    } 


    //solution :::: spliting

    for (int i=0 ;i< word.size(); ++i)
    {
        std::string tempword = word;
        std::string sub_1 = word.substr(0,i);
        std::string sub_2 = word.substr(i);
        tempword = sub_1 + " " + sub_2;
        
        if ( wordExists(tempword) and std::find(suggestions.begin(),suggestions.end(), tempword) == suggestions.end())
        {
            suggestions.push_back(tempword);
        }

        
    }





    return suggestions;
}

