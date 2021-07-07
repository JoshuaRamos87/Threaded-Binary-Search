#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <ctime>
#include <future>
using namespace std;

void displayVector(vector<int>& vec);
void createVec(vector<int>& vec, int& size);
void threadedBinSearch(vector<int>& vec, int& target);
void regBinSearch(vector<int>& vec, int& target);
ostream& operator<<(ostream& out, future<int>& fu);
void displayTime(std::chrono::system_clock::time_point& start, std::chrono::system_clock::time_point& end);

int binSearch(vector<int>& vec, int left, int right, int target)
{
    while(left <= right)
	{
		int mid = (left+right)/2;
		if(target < vec[mid])
			right = mid - 1;
		else if(target > vec[mid])
			left = mid + 1;
		else if(target == vec[mid])
			return mid;
	}
    return -1;
}

int main()
{
    vector<int> vec;
    int target = 0;
    int size = 0;

//----Setup-------    
    cout << "enter in the size\n";
    cin >> size;
    cout << "enter in the target\n";
    cin >> target;
    createVec(vec,size);
//----------------
    
    threadedBinSearch(vec,target);
    regBinSearch(vec,target);
    return 0;
}

/*
runs single threaded binary search and displays process time
*/
void regBinSearch(vector<int>& vec, int& target)
{
    auto startTime = std::chrono::system_clock::now();
        binSearch(vec,0,vec.size(),target);
    auto endTime = std::chrono::system_clock::now();
    displayTime(startTime,endTime);
}

template <typename T>
void displayVector(vector<T>& vec)
{
    for(auto &i : vec)
        cout << i;
}

ostream& operator<<(ostream& out, future<int>& fu)
{
    return out << fu.get() << " ";
}

void createVec(vector<int>& vec, int& size)
{
    for(int i = 0; i < size; ++i)
        vec.push_back(i);
}

/*
runs multi threaded binary search and displays process time; threads based on users processors thread count
*/
void threadedBinSearch(vector<int>& vec, int& target)
{
    int threadCount = 2;//thread::hardware_concurrency();
    int mid = (vec.size()-1)/ threadCount;
    int begin = 0;
    int end = 0;

    vector<future<int>> fut_vec(threadCount);
    auto startTime = std::chrono::system_clock::now();
        for(int i = 0; i < threadCount; ++i)
        {
            begin = mid*i;
            end = mid*i+mid-1;
            if(i+1 == threadCount)
                end = vec.size()-1;
            fut_vec[i] = async(launch::async, binSearch,ref(vec),begin,end,target);
        }
    auto endTime = std::chrono::system_clock::now();
    
    displayVector(fut_vec);
    displayTime(startTime,endTime);
}

/*
Displays the time between the start and end intervals passed; used for calculating processing time of code
*/
void displayTime(std::chrono::system_clock::time_point& start, std::chrono::system_clock::time_point& end)
{
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}