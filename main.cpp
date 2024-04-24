#include<iostream>
#include<windows.h>
#include<ctime>
#include<string>

using namespace std;

class File 
{
    public:
        char* filename;
        int filesize;
        FILETIME dateModified;
        
        File() 
        {
            filename = nullptr;
            filesize = 0;
        }

        File(const char* fname, size_t fsize, const FILETIME& modified) 
        {
            filesize = fsize;
            filename = new char[strlen(fname) + 1];
            strcpy(filename, fname);
            dateModified = modified;
        }
};

class Node 
{
    public:
        File data;
        Node* next;

        Node() 
        {
            next = nullptr;
        }

        Node(File file) 
        {
            data = file;
            next = nullptr;
        }
};

class Linkedlist 
{
    public:
        Node* head;

        Linkedlist() 
        {
            head = nullptr;
        }

        ~Linkedlist() 
        {
            Node* current = head;
            while (current != nullptr) 
            {
                Node* next = current->next;
                delete current;
                current = next;
            }
            head = nullptr;
        }

        void insert(File file) 
        {
            Node* newNode = new Node(file);
            if (head == nullptr) 
            {
                head = newNode;
            } 
            else 
            {
                Node* temp = head;
                while (temp->next != nullptr) 
                {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }

        void display() 
        {
            Node* current = head;
            while (current != nullptr) 
            {
                cout << current->data.filename << "\t|   (" << current->data.filesize << " bytes)  |\t\tModified: ";
                FILETIME ft = current->data.dateModified;
                SYSTEMTIME st;
                FileTimeToSystemTime(&ft, &st);
                cout << st.wYear << "-" << st.wMonth << "-" << st.wDay << " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond <<"\n"<<endl;
                current = current->next;
            }
        }

        Node* getHead() 
        {
            return head;
        }
};

class SortingAlgorithms 
{
    public:
        clock_t startTime, endTime;
        double totalTime;
        
        void sort(Linkedlist& list, int filecount);
        
        void displayTime() 
        {
            cout << "Total Time:\t" << totalTime << endl;
            cout << "\n\n\n";
        }
};

class SelectionSortByName : public SortingAlgorithms 
{
    public:
        void sort(Linkedlist& list, int filecount)
        {
            startTime = clock();

            Node* start = list.getHead();

            for (int i = 0; i < filecount - 1; i++) 
            {
                Node* minNode = start;
                Node* current = start->next;

                for (int j = i + 1; j < filecount; j++) 
                {
                    if (strcmp(current->data.filename, minNode->data.filename) < 0) 
                    {
                        minNode = current;
                    }
                    current = current->next;
                }

                if (minNode != start) 
                {
                    File temp = start->data;
                    start->data = minNode->data;
                    minNode->data = temp;
                }

                start = start->next;
            }

            list.display();

            endTime = clock();
            totalTime = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;

            displayTime();
        }
};

class SelectionSortBySize : public SortingAlgorithms 
{
    public:
        void sort(Linkedlist& list, int filecount) 
        {
            startTime = clock();

            Node* start = list.getHead();

            for (int i = 0; i < filecount - 1; i++) {
                Node* minNode = start;
                Node* current = start->next;

                for (int j = i + 1; j < filecount; j++) 
                {
                    if (current->data.filesize < minNode->data.filesize) 
                    {
                        minNode = current;
                    }
                    current = current->next;
                }

                if (minNode != start) 
                {
                    File temp = start->data;
                    start->data = minNode->data;
                    minNode->data = temp;
                }

                start = start->next;
            }

            list.display();

            endTime = clock();
            totalTime = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;

            displayTime();
        }
};

class SelectionSortByDate : public SortingAlgorithms 
{
    public:
        void sort(Linkedlist& list, int filecount) 
        {
            startTime = clock();

            Node* start = list.getHead();

            for (int i = 0; i < filecount - 1; i++) 
            {
                Node* minNode = start;
                Node* current = start->next;

                for (int j = i + 1; j < filecount; j++) 
                {
                    if (CompareFileTime(&current->data.dateModified, &minNode->data.dateModified) < 0) 
                    {
                        minNode = current;
                    }
                    current = current->next;
                }

                if (minNode != start) 
                {
                    File temp = start->data;
                    start->data = minNode->data;
                    minNode->data = temp;
                }

                start = start->next;
            }

            list.display();

            endTime = clock();
            totalTime = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;

            displayTime();
        }
};

class InsertionSortByName : public SortingAlgorithms 
{
    public:
        void sort(Linkedlist& list, int filecount) 
        {
            startTime = clock();

            Node* start = list.getHead();

            if (start == nullptr || start->next == nullptr)
                return;

            Node* sorted = nullptr;

            while (start != nullptr) 
            {
                Node* current = start;
                start = start->next;
                if (sorted == nullptr || strcmp(current->data.filename, sorted->data.filename) < 0) 
                {
                    current->next = sorted;
                    sorted = current;
                } 
                else 
                {
                    Node* temp = sorted;
                    while (temp->next != nullptr && strcmp(temp->next->data.filename, current->data.filename) < 0) 
                    {
                        temp = temp->next;
                    }
                    current->next = temp->next;
                    temp->next = current;
                }
            }
            list.head = sorted;

            list.display();

            endTime = clock();
            totalTime = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;

            displayTime();
        }
};

class InsertionSortBySize : public SortingAlgorithms 
{
    public:
        void sort(Linkedlist& list, int filecount) 
        {
            startTime = clock();

            Node* start = list.getHead();

            if (start == nullptr || start->next == nullptr)
                return;

            Node* sorted = nullptr;

            while (start != nullptr) 
            {
                Node* current = start;
                start = start->next;
                if (sorted == nullptr || current->data.filesize <= sorted->data.filesize) 
                {
                    current->next = sorted;
                    sorted = current;
                } 
                else 
                {
                    Node* temp = sorted;
                    while (temp->next != nullptr && temp->next->data.filesize < current->data.filesize) 
                    {
                        temp = temp->next;
                    }
                    current->next = temp->next;
                    temp->next = current;
                }
            }
            list.head = sorted;

            list.display();

            endTime = clock();
            totalTime = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;

            displayTime();
        }
};

class InsertionSortByDate : public SortingAlgorithms 
{
    public:
        void sort(Linkedlist& list, int filecount) 
        {
            startTime = clock();

            Node* start = list.getHead();

            if (start == nullptr || start->next == nullptr)
                return;

            Node* sorted = nullptr;

            while (start != nullptr) 
            {
                Node* current = start;
                start = start->next;
                if (sorted == nullptr || CompareFileTime(&current->data.dateModified, &sorted->data.dateModified) < 0) 
                {
                    current->next = sorted;
                    sorted = current;
                } 
                else 
                {
                    Node* temp = sorted;
                    while (temp->next != nullptr && CompareFileTime(&temp->next->data.dateModified, &current->data.dateModified) < 0) 
                    {
                        temp = temp->next;
                    }
                    current->next = temp->next;
                    temp->next = current;
                }
            }
            list.head = sorted;

            list.display();

            endTime = clock();
            totalTime = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;

            displayTime();
        }
};

class BubbleSortByName : public SortingAlgorithms 
{
    public:
        void sort(Linkedlist& list, int filecount) 
        {
            startTime = clock();

            Node* start = list.getHead();

            for (int i = 0; i < filecount - 1; i++) 
            {
                Node* current = start;
                Node* nextNode = start->next;

                for (int j = 0; j < filecount - i - 1; j++) 
                {
                    if (strcmp(current->data.filename, nextNode->data.filename) > 0) 
                    {
                        File temp = current->data;
                        current->data = nextNode->data;
                        nextNode->data = temp;
                    }
                    current = current->next;
                    nextNode = nextNode->next;
                }
            }

            list.display();

            endTime = clock();
            totalTime = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;

            displayTime();
        }
};

class BubbleSortBySize : public SortingAlgorithms 
{
    public:
        void sort(Linkedlist& list, int filecount) 
        {
            startTime = clock();

            Node* start = list.getHead();

            for (int i = 0; i < filecount - 1; i++) 
            {
                Node* current = start;
                Node* nextNode = start->next;

                for (int j = 0; j < filecount - i - 1; j++) 
                {
                    if (current->data.filesize > nextNode->data.filesize) 
                    {
                        File temp = current->data;
                        current->data = nextNode->data;
                        nextNode->data = temp;
                    }
                    current = current->next;
                    nextNode = nextNode->next;
                }
            }

            list.display();

            endTime = clock();
            totalTime = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;

            displayTime();
        }
};

class BubbleSortByDate : public SortingAlgorithms 
{
    public:
        void sort(Linkedlist& list, int filecount) 
        {
            startTime = clock();

            Node* start = list.getHead();

            for (int i = 0; i < filecount - 1; i++) 
            {
                Node* current = start;
                Node* nextNode = start->next;

                for (int j = 0; j < filecount - i - 1; j++) 
                {
                    if (CompareFileTime(&current->data.dateModified, &nextNode->data.dateModified) > 0) 
                    {
                        File temp = current->data;
                        current->data = nextNode->data;
                        nextNode->data = temp;
                    }
                    current = current->next;
                    nextNode = nextNode->next;
                }
            }

            list.display();

            endTime = clock();
            totalTime = (static_cast<double>(endTime - startTime)) / CLOCKS_PER_SEC;

            displayTime();
        }
};

class ReadFiles 
{
    public:
        void readSortFileName(const std::string& directoryPath, const std::string& sortCriteria) 
        {
            Linkedlist list;
            std::string searchPath = directoryPath + "\\*";
            WIN32_FIND_DATA findFileData;
            HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);
            int filecount = 0;

            if (hFind == INVALID_HANDLE_VALUE) 
            {
                cerr << "Failed to find files in directory: " << directoryPath << "\n";
                return;
            }

            do 
            {
                std::string filename = findFileData.cFileName;
                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
                {
                    FILETIME modifiedTime = findFileData.ftLastWriteTime;
                    File file(filename.c_str(), findFileData.nFileSizeLow, modifiedTime);
                    list.insert(file);
                    filecount++;
                } 
                else if (filename != "." && filename != "..") 
                {
                    // Recurse into subdirectory
                    std::string subDirPath = directoryPath + "\\" + filename;
                    readSortFileName(subDirPath, sortCriteria); // Recursively read files in subdirectory
                }
            } 
            while (FindNextFile(hFind, &findFileData));

            FindClose(hFind);

            if (filecount > 0) 
            {
                cout << "[+]\tProcessing directory:\t" << directoryPath << "\n\n\n";
                cout << "Before Sorting:\n";
                list.display();
                cout << "\n\n\n";

                if (sortCriteria == "name") 
                {
                    cout << "Selection Sort by Name:\n";
                    SelectionSortByName selectionSortByName;
                    selectionSortByName.sort(list, filecount);
                    cout << "Insertion Sort by Name:\n";
                    InsertionSortByName insertionSortByName;
                    insertionSortByName.sort(list, filecount);
                    cout << "Bubble Sort by Name:\n";
                    BubbleSortByName bubbleSortByName;
                    bubbleSortByName.sort(list, filecount);
                } 
                else if (sortCriteria == "size") 
                {
                    cout << "Selection Sort by Size:\n";
                    SelectionSortBySize selectionSortBySize;
                    selectionSortBySize.sort(list, filecount);
                    cout << "Insertion Sort by Size:\n";
                    InsertionSortBySize insertionSortBySize;
                    insertionSortBySize.sort(list, filecount);
                    cout << "Bubble Sort by Size:\n";
                    BubbleSortBySize bubbleSortBySize;
                    bubbleSortBySize.sort(list, filecount);
                } 
                else 
                {
                    cout << "Selection Sort by Date:\n";
                    SelectionSortByDate selectionSortByDate;
                    selectionSortByDate.sort(list, filecount);
                    cout << "Insertion Sort by Date:\n";
                    InsertionSortByDate insertionSortByDate;
                    insertionSortByDate.sort(list, filecount);
                    cout << "Bubble Sort by Date:\n";
                    BubbleSortByDate bubbleSortByDate;
                    bubbleSortByDate.sort(list, filecount);
                }
            }
        }
};


int main() 
{
    ReadFiles fn;
    std::string initialPath = "Drive:\\Path\\To\\Directory";
    int choice;
    cout << "Enter sorting criteria:\n";
    cout << "[+]\tSort by name\t(Press 1)\n";
    cout << "[+]\tSort by size\t(Press 2)\n";
    cout << "[+]\tSort by date\t(Press 3)\n";
    cin >> choice;
    cout<<"\n";
    switch (choice) 
    {
        case 1:
            fn.readSortFileName(initialPath, "name");
            break;
        case 2:
            fn.readSortFileName(initialPath, "size");
            break;
        case 3:
            fn.readSortFileName(initialPath, "date");
            break;
        default:
            cout << "Invalid choice. Sorting by date.\n";
            break;
    }

    return 0;
}