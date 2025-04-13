#include <iostream>
#include <limits>  // For numeric_limits
#include <queue>
#include <sstream>
#include <vector>

#include "common.h"

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}

    // Helper function to create a linked list from a vector
    static ListNode *createLinkedList(const vector<int> &values) {
        if (values.empty()) return nullptr;

        ListNode *head = new ListNode(values[0]);
        ListNode *current = head;

        for (size_t i = 1; i < values.size(); i++) {
            current->next = new ListNode(values[i]);
            current = current->next;
        }

        return head;
    }

    // Helper function to print a linked list
    static void printLinkedList(ListNode *head) {
        ListNode *current = head;
        while (current) {
            cout << current->val;
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }

    // Helper function to free memory allocated for a linked list
    static void deleteLinkedList(ListNode *head) {
        ListNode *current = head;
        while (current) {
            ListNode *next = current->next;
            delete current;
            current = next;
        }
    }
};

class MultiwayMerge {
    // Custom comparator for priority queue to order ListNode pointers by their
    // values
    struct CompareNodes {
        bool operator()(ListNode *a, ListNode *b) {
            return a->val > b->val;  // Min-heap
        }
    };

public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) return nullptr;

        // Create a min-heap using our custom comparator
        priority_queue<ListNode *, vector<ListNode *>, CompareNodes> pq;

        // Add the first node from each list to the priority queue
        for (ListNode *list: lists) {
            if (list) pq.push(list);
        }

        // Create a dummy head for the result list
        ListNode dummy(0);
        ListNode *tail = &dummy;

        // Process nodes until the priority queue is empty
        while (!pq.empty()) {
            // Get the smallest node
            ListNode *smallest = pq.top();
            pq.pop();

            // Add it to our result list
            tail->next = smallest;
            tail = tail->next;

            // If this node has a next node, add it to the priority queue
            if (smallest->next) {
                pq.push(smallest->next);
            }
        }

        return dummy.next;
    }
};

int main() {
    MultiwayMerge solution;

    cout << "=== Multiway Merge of K Sorted Lists ===" << endl;
    cout << "Enter the number of lists: ";
    int k;
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(),
               '\n');  // Clear the entire input buffer

    vector<ListNode *> lists;

    for (int i = 0; i < k; i++) {
        cout << "Enter list " << i + 1
             << " (space-separated integers, end with Enter): ";
        string line;
        getline(cin, line);

        vector<int> values;
        istringstream iss(line);
        int val;
        while (iss >> val) {
            values.push_back(val);
        }

        lists.push_back(ListNode::createLinkedList(values));
        cout << "List " << i + 1 << ": ";
        ListNode::printLinkedList(lists.back());
    }

    // Merge the lists
    ListNode *mergedList = solution.mergeKLists(lists);

    cout << "\nMerged List: ";
    ListNode::printLinkedList(mergedList);

    // Clean up memory
    ListNode::deleteLinkedList(mergedList);

    return 0;
}