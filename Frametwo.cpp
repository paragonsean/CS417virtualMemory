#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

void lruPageReplacement(vector<int> referenceString, int numFrames) {
    list<int> frames;  // Store current frames
    unordered_map<int, list<int>::iterator> pageMap;  // Map to track page position in the list
    int pageFaults = 0;
    int totalReferences = referenceString.size();

    // Table Header
    cout << "Page Reference#\t\tResult\t\tFrame allocated to" << endl;

    for (int page : referenceString) {
        if (pageMap.find(page) != pageMap.end()) {
            // Page is already in memory -> Move it to most recent position
            frames.erase(pageMap[page]);
            frames.push_back(page);
            pageMap[page] = --frames.end();
            cout << page << "\t\tNo Page Fault\t\t";
        } else {
            // Page fault occurs
            pageFaults++;
            if (frames.size() < numFrames) {
                // If space is available, just add the page
                frames.push_back(page);
            } else {
                // Remove the least recently used (LRU) page
                int lruPage = frames.front();
                frames.pop_front();
                pageMap.erase(lruPage);
                frames.push_back(page);
            }
            pageMap[page] = --frames.end();
            cout << page << "\t\tPage Fault\t\t";
        }

        // Print current frame status
        int i = 0;
        for (int f : frames) {
            if (i == 0) cout << "F0=" << f << " ";
            else if (i == 1) cout << "F1=" << f << " ";
            else if (i == 2) cout << "F2=" << f << " ";
            i++;
        }
        cout << endl;
    }

    // Summary of results
    cout << "\nTotal # of references: " << totalReferences << endl;
    cout << "Total # of page faults: " << pageFaults << endl;
}

int main() {
    // Given reference string
    vector<int> referenceString = {0, 3, 5, 1, 1, 2, 5, 4, 3, 2, 1, 2, 5, 4, 6, 7, 5, 4, 7, 8, 9, 10, 5, 6, 10, 1, 2, 3};
    int numFrames = 3;

    // Run the simulation
    lruPageReplacement(referenceString, numFrames);

    return 0;
}
