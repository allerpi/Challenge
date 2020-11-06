#include "ComputerConnections.h"
#include "SiteAccesses.h"

using namespace std;

int main() {
    cout << endl;
    Register r("new_data.csv");
    ofstream printy("../4_answers.txt", ios::trunc);
    cout << "Analysing data..." << setw(33);

    //////////////////////// QUESTION 1 ////////////////////////
    // get dates
    set<string> dates;
    r.get_all_dates(dates);

    // get top 5 sites of all dates
    vector< vector<SiteAccesses>* > top_sites;
    for(string day : dates) {
        top_sites.push_back(r.top(5, day));
    }

    vector<int> traffic;

    // count amount of times a site appears
    map<string,int> appearances;
    string curr_site = "";
    for(int i = 0; i < top_sites.size(); i++) {
        for(int j = 0; j < top_sites[i]->size(); j++) {
            
            // to calculate average
            traffic.push_back((*top_sites[i])[j].get_amt());

            curr_site = (*top_sites[i])[j].get_hname();
            if(appearances.count(curr_site) > 0) {
                appearances[curr_site] += 1;
            }
            else {
                appearances[curr_site] = 1;
            }
        }
    }

    // write out answer
    printy << "1. The following websites appear all " << dates.size() << " days:" << endl;
    bool count = false;
    for(auto& x : appearances) {
        if(x.second == dates.size()) {
            printy << x.first << endl;
            count = true;
        }
    }
    if(!count) {
        printy << "None" << endl;
    }
    printy << endl;

    //////////////////////// QUESTION 2 ////////////////////////
    Search<SiteAccesses> searchy_boi;
    vector<string> tally;
    int cursed_size = top_sites.size() - 1;
    
    // searches last two days for website name
    for(auto& x : appearances) {
        SiteAccesses dummy(x.first, x.second);
        int found_in_last_day = searchy_boi.seq((*top_sites[cursed_size]), dummy, &SiteAccesses::is_equal_hname_dest);
        int found_in_second_to_last_day = searchy_boi.seq((*top_sites[cursed_size - 1]), dummy, &SiteAccesses::is_equal_hname_dest);
        if(found_in_last_day > -1 && found_in_second_to_last_day > -1 && x.second < dates.size()) {
            tally.push_back(x.first);
        }
    }

    // writes out answer
    printy << "2. The following websites appear on subsequent days until the last:" << endl;
    count = false;
    for(string webpage : tally) {
        printy << webpage << endl;
        count = true;
    }
    if(!count) {
        printy << "None" << endl;
    }
    printy << endl;

    //////////////////////// QUESTION 3 ////////////////////////
    // calculate average
    int average = 0;
    for (int i = 0; i < traffic.size(); i++) {
        average += traffic[i];
    }
    average /= top_sites[0]->size() * top_sites.size();

    // save any website that exceeds average on any given day
    set<string> sus_sites;
    for(int i = 0; i < top_sites.size(); i++) {
        for(int j = 0; j < top_sites[i]->size(); j++) {
            if((*top_sites[i])[j].get_amt() > average) {
                sus_sites.insert((*top_sites[i])[j].get_hname());
            }
        }
    }

    // write out answer
    printy << "3. The following websites have an unusually high amount of traffic:" << endl;
    string ans3 = "";
    count = false;
    for(set<string>::iterator it = sus_sites.begin(); it != sus_sites.end(); it++) {
        ans3 += *it + "\n";
        count = true;
    }
    if(count) {
        printy << ans3;
    }
    else {
        printy << "None";
    }

    //////////////////////// THE END ////////////////////////
    for(int i = 0; i < top_sites.size(); i++) {
        delete top_sites[i];
    }

    cout << "DATA ANALYSED\n" << endl;
    cout << "Answers may be checked in 4_answers.txt\nSuccess!" << endl;
    
    printy.close();
    cout << endl;
}
