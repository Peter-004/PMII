// Your name here: Opemipo Peter Adebayo
// Your NetID here: opa15
//
// IMPORTANT NOTE:
// In your submission, you are only allowed to make modifications where it is indicated, 
// and you must provide your implementation in those designated areas. 
// You are not permitted to make changes to the code in any other location.
//
#ifndef HW2B_H
#define HW2B_H

#include <vector>
#include <stdexcept>

class Event {
public:
    int location_id;
    int event_id;
    int timestamp;
    std::string detail;

    Event(int location_id, int event_id, int timestamp, const std::string& text)
        : location_id(location_id), event_id(event_id), timestamp(timestamp), detail(text) {}

    bool operator<(const Event& other) const {
        return timestamp < other.timestamp; 
    }
    
    bool operator>(const Event& other) const {
        return timestamp > other.timestamp; 
    }
    
    friend std::ostream& operator<< (std::ostream& out, const Event& e) ;
};

std::ostream& operator<< (std::ostream& out, const Event& e) {
    out << e.location_id << "," << e.event_id << "," << e.timestamp << "," << e.detail ;
    return out;
}


template <typename T>
class MinHeap {
public:
    std::vector<T> heap;

    /**
     *minHeapify helps maintain the min-heap property
     * @param i the starting index
     */
    void minHeapify(int i) {
        // Provide your implementation here
        //
        int smallest = i;
        int leftIndex = 2*i + 1;
        int rightIndex = 2*i + 2;
        if(leftIndex < heap.size() && heap[leftIndex] < heap[i] ){
            smallest = leftIndex;
        }
        else{
            smallest = i;
        }
        if(rightIndex < heap.size() && heap[rightIndex] < heap[smallest] ){
            smallest = rightIndex;
        }
        if( smallest != i){
            std::swap(heap[smallest],heap[i]);
            //swap(heap[smallest], heap[i]);
            minHeapify(smallest);
        }
        // End of your implementation
    }

public:
    /**
     * Constructor for an empty Heap
     */
    MinHeap() {

    }

    /**
     * Constructor for a heap initialized with a vector
     * @param arr the vector that represents the minHeap
     */
    MinHeap(const std::vector<T>& arr) {//BuildMinHeap
        heap = arr;
        int n = heap.size();
        for (int i = (n / 2) - 1; i >= 0; i--) {
            minHeapify(i);
        }
    }

    /**
     * insert method inserts a new value to the minHeap, while maintaining the property
     * @param value the value to be inserted into the minHeap
     */
    void insert(const T& value) {
        // Provide your implementation here
        heap.push_back(value);
        //Change this from buildminheap to reduce runtime
        int i = heap.size()-1;
        while(i != 0 && heap[(i-1)/2]>heap[i]) {
            std::swap(heap[i],heap[(i-1)/2]);
            i = (i-1)/2;//parent index
        }
        // End of your implementation
    }

    /**
     * getMin returns the minimum value of the minHeap
     * @return the root of the minHeap
     */
    T getMin() {
        if (!isEmpty()) {
            return heap[0];
        }
        throw std::runtime_error("Heap is empty.");
    }

    /**
     * removes the current minimum of the minHeap
     * @return the root of the minHeap
     */
    T extractMin() {
        if (isEmpty()) {
            throw std::runtime_error("Heap is empty.");
        }

        // Provide your implementation here
        // Don't forget to return the extracted Min item
        T minimano = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        minHeapify(0);
        return minimano;
        //Delete the root

        // End of your implementation
    }

    bool isEmpty() {
        return heap.empty();
    }

};

/**
 * getFirstNEvents gets the first n events from the vector
 * @param all_events the vector containing all events and details
 * @param n the number to be extracted
 * @return the events vector extracted
 */
std::vector<Event> getFirstNEvents(std::vector<std::vector<Event>>& all_events, int n) {
    std::vector<Event> first_n_events;
    MinHeap<Event> min_heap;

    // Provide your implementation here
    std::vector<int> index(all_events.size(),0);

    for(int i = 0;i<all_events.size();i++) {
        if(!all_events[i].empty()) {
            min_heap.insert(all_events[i][0]);
        }
    }
    while(!min_heap.isEmpty() && first_n_events.size() < n) {
        Event event1 = min_heap.extractMin();
        int locationID = event1.location_id;
        first_n_events.push_back(event1);

        index[locationID]++;

        if(index[locationID] < all_events[locationID].size()) {
            min_heap.insert(all_events[locationID][index[locationID]]);
        }
    }
    //first_n_events.push_back(Event(1,2,3,"maryland"));
    // End of your implementation
    return first_n_events;
}

#endif // HW2B_H
