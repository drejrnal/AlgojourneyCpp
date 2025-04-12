//
// Created by luoxiYun on 2025/4/12.
//

#include "common.h"
#include "indexed_priority_queue.h"

class TaskManager {
    struct Task {
        int userId;
        int taskId;
        int priority;
    };

    struct TaskComparator {
        bool operator()(const Task &a, const Task &b) {
            if (a.priority != b.priority) {
                return a.priority < b.priority;
            }
            return a.taskId < b.taskId;
        }
    };

    // key: taskId, value: Task
    indexed_priority_queue<int, Task, TaskComparator> taskQueue;

    // Maintain a separate map for quick access to task information
    unordered_map<int, Task> taskMap;

public:
    TaskManager(vector<vector<int>> &tasks) {
        // Initialize the task manager with the given tasks
        for (const auto &task: tasks) {
            int userId = task[0];
            int taskId = task[1];
            int priority = task[2];
            add(userId, taskId, priority);
        }
    }

    void add(int userId, int taskId, int priority) {
        // Create a task
        Task newTask = {userId, taskId, priority};

        // Store in our map for quick lookup
        taskMap[taskId] = newTask;

        // Add to the priority queue
        taskQueue.push(taskId, newTask);
    }

    void edit(int taskId, int newPriority) {
        // Check if task exists
        if (taskMap.find(taskId) != taskMap.end()) {
            // Update our map
            Task &task = taskMap[taskId];
            task.priority = newPriority;

            // Update in the priority queue
            taskQueue.changeKey(taskId, task);
        }
    }

    void rmv(int taskId) {
        // Remove from our map
        taskMap.erase(taskId);

        // Remove from the priority queue
        taskQueue.remove(taskId);
    }

    int execTop() {
        if (taskQueue.empty()) {
            return -1;
        }

        // Get the top task
        auto topTask = taskQueue.top();
        int taskId = topTask.first;
        int userId = topTask.second.userId;

        // Remove the executed task
        rmv(taskId);

        return userId;
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */

int main() {
    // Example test case
    cout << "=== Task Manager Test ===" << endl;

    // Create tasks: [userId, taskId, priority]
    vector<vector<int>> tasks = {
            {1, 2, 5},   // User 1, Task 2, Priority 5
            {2, 3, 7},   // User 2, Task 3, Priority 7
            {1, 5, 10},  // User 1, Task 5, Priority 10
            {3, 7,
                   10}  // User 3, Task 7, Priority 10 (Same as Task 5, but higher taskId)
    };

    TaskManager *manager = new TaskManager(tasks);

    // Test execTop: Should execute Task 7 (highest priority 10, and higher
    // taskId between tasks with priority 10)
    cout << "Execute top task, user ID: " << manager->execTop()
         << endl;  // Expected: 3

    // Add new task
    manager->add(2, 9, 8);
    cout << "Added task: User 2, Task 9, Priority 8" << endl;

    // Edit task
    manager->edit(5, 15);
    cout << "Edited task 5 to priority 15" << endl;

    // Execute top (should be task 5 now with priority 15)
    cout << "Execute top task, user ID: " << manager->execTop()
         << endl;  // Expected: 1

    // Remove task
    manager->rmv(3);
    cout << "Removed task 3" << endl;

    // Execute top (should be task 9 with priority 8)
    cout << "Execute top task, user ID: " << manager->execTop()
         << endl;  // Expected: 2

    // Execute top (should be task 2 with priority 5)
    cout << "Execute top task, user ID: " << manager->execTop()
         << endl;  // Expected: 1

    // Execute top (no tasks left)
    cout << "Execute top task, user ID: " << manager->execTop()
         << endl;  // Expected: -1

    delete manager;
    return 0;
}