#pragma once

#include <thread>
#include <functional>
#include <vector>
#include <array>
#include <condition_variable>
#include <set>
#include <map>

struct Task 
{
	Task(std::function<void(std::shared_ptr<void>)> func, std::shared_ptr<void> data);
	std::function<void(std::shared_ptr<void>)> func;
	std::shared_ptr<void> data;
};

class PriorityThreadManager
{
public:
	PriorityThreadManager(unsigned int threadsAmount = std::thread::hardware_concurrency());
	~PriorityThreadManager();

	void addTask(std::function<void(std::shared_ptr<void>)> func, unsigned int priority, std::shared_ptr<void> data);

	void stop();
	
	static const unsigned int MAX_PRIORITIES_AMOUNT = 10;

private:
	void threadRun();

	/// <summary>
	/// Updates the current priority variable to be an available task.
	/// Returns whether cur priority is outside of the priorities array.
	/// 
	/// Note: must already lock the tasks mutex.
	/// </summary>
	/// <returns>Tasks can be fetched</returns>
	bool updateCurPriority();



private:
	unsigned int _curPriority;
	bool _running;

	std::vector<std::thread> _threads;
	
	std::map<unsigned int, std::vector<Task>> _tasks;
	std::mutex _tasksMutex;
	std::condition_variable _taskCv;

	std::set<unsigned int> _activePriorities;  
};

