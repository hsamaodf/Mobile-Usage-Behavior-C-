#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> tokenise(std::string csvLine, char separator)
{
    //This string stores our tokens
    std::vector<std::string> tokens;
    //This int delineates the position of our tokens
    signed int start, end;
    std::string token;
    //Defines start as the first part of the csvLine that is not a separator starting from position 0
    start = csvLine.find_first_not_of(separator, 0);
    //Starting our do/while loop here
    do{
        //end defined as first separator after start
        end = csvLine.find_first_of(separator, start);
        //if statement: if start is the length of the csvLine then start is the end. We can break the loop here
        if (start == csvLine.length() || start == end) break;
        //if statement: if end is more than or equal to 0, we have a token!
        if (end >= 0) token = csvLine.substr(start, end - start);
        //else statement: if none of these conditions are met,
        else token = csvLine.substr(start, csvLine.length() - start);
        //saving our token
        tokens.push_back(token);
        //on to the next one
        start = end + 1;

    }while(end != std::string::npos);

    return tokens;

}
//Enum class sets osType to only have 2 categories: Android and iOS
enum class os 
{ 
    Android,
    iOS
};
//Enum class sets gender to only have 2 categories: Male and Female (yes, yes, there are other genders.. but for this dataset only 2 are listed)
enum class gender
{
    Male,
    Female
};

class userBehaviour
{
    public:

        userBehaviour(int userID,
                      std::string deviceModel,
                      os os,
                      int usageTime,
                      float screenOnTime,
                      int batteryDrain,
                      int noOfApps,
                      int dataUsage,
                      int age,
                      gender gender,
                      int behaviorClass)
        : userID(userID),
          usageTime(usageTime),
          deviceModel(deviceModel),
          os(os),
          gender(gender),
          dataUsage(dataUsage),
          screenOnTime(screenOnTime),
          batteryDrain(batteryDrain),
          noOfApps(noOfApps),
          age(age),
          behaviorClass(behaviorClass) 
        {
           
        }
         int userID;
         std::string deviceModel;
         os os;
         int usageTime;
         float screenOnTime;
         int batteryDrain;
         int noOfApps;
         int dataUsage;
         int age;
         gender gender;
         int behaviorClass;

};

int main()
{
    std::ifstream csvFile{"UBData.csv"};
    std::string data;
    std::string field;
    std::vector<std::string> tokens;
    //For summary of valid line count
    signed int validLineCount = 0;
    const int expectedLineCount = 700;
    int fieldCount = 0;
    int actualLineCount;

    //If the file can be opened prints "File Open"
    if (csvFile.is_open())
    {
        std::cout << "File Open" << std::endl;
        //While loop continuously reads lines of data from csv file
        while(std::getline(csvFile, data))
        {
            //Prints lines of data
            std::cout << "Read data" << data << std::endl;
            //Lines of data converted into tokens using ',' as a separator
            tokens = tokenise(data, ',');
            fieldCount++;
            //check number of tokens. If >5 data is missing from line- faulty line- data cannot be processed
            if (tokens.size() !=11)
            {
                std::cout << "Data error - Faulty request" << std::endl;
                validLineCount--;
                continue;
            }
            //If tokens =5 data is good and can be processed
            //Strings for Data Usage, Screen-on-Time and Battery Drain, etc. converted to various data tyoes (floats) using std::stod, etc.
            try{
                int userID = std::stoi(tokens [0]);
                int usageTime = std::stoi(tokens [3]);
                float screenOnTime = std::stof(tokens [4]);
                int batteryDrain = std::stoi(tokens [5]);
                int noOfApps = std::stoi(tokens [6]);
                int dataUsage = std::stoi(tokens [7]);
                int age = std::stoi(tokens [8]);
                int behaviorClass = std::stoi(tokens [10]);
                 //Prints "Data Usage:Screen on Time:Battery Drain:etc."
                std::cout << userID << ":" << usageTime << ":" << screenOnTime << ":" << batteryDrain << ":" << noOfApps << ":" << dataUsage << ":" << age << ":" << behaviorClass << std::endl;
            //Try/Catch- If there is an error with a line of data and an exception is thrown, error tokens are printed and on to the next line in the dataset
            }catch(std::exception& e){
                std::cout << "Error- Data inadmissible" << tokens[0] << std::endl;
                std::cout << "Error- Data inadmissible" << tokens[3] << std::endl;
                std::cout << "Error- Data inadmissible" << tokens[4] << std::endl;
                std::cout << "Error- Data inadmissible" << tokens[5] << std::endl;
                std::cout << "Error- Data inadmissible" << tokens[6] << std::endl;
                std::cout << "Error- Data inadmissible" << tokens[7] << std::endl;
                std::cout << "Error- Data inadmissible" << tokens[8] << std::endl;
                std::cout << "Error- Data inadmissible" << tokens[10] << std::endl;
                continue;
            }
            //Prints tokens
            for (std::string& t : tokens)
            {
                std::cout << t << std::endl;
                }
            }
        //Closes csv file
        csvFile.close();

        //Summary of parsed data
        int actualLineCount = int (fieldCount) + int (validLineCount);
        std::cout << "Total successfully parsed lines:" << actualLineCount << " out of " << expectedLineCount << std::endl;
    }
    //If file cannot be opened prints "Error- File could not be opened"
    else
    {
        std::cout << "Error - File could not be opened" << std::endl;
    }

    return 0;
};