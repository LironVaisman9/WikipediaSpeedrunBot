#include "PriorityThreadManager.h"
#include <iostream>

PriorityThreadManager::PriorityThreadManager(unsigned int threadsAmount)
	: _curPriority(0), _running(true)
{
	// main thread will run this

	// Create threadsAmount of threads
	_threads.reserve(threadsAmount);
	for (unsigned int i = 0; i < threadsAmount; ++i)
	{
		_threads.emplace_back(&PriorityThreadManager::threadRun, this, i);
	}
}

PriorityThreadManager::~PriorityThreadManager()
{
	stop();
}

void PriorityThreadManager::addTask(std::function<void(std::shared_ptr<void>, const unsigned int)> func, unsigned int priority, std::shared_ptr<void> data)
{
	{
		std::lock_guard<std::mutex> lock(_tasksMutex);
		_tasks[priority].emplace_back(func, data);
		_activePriorities.insert(priority);
	}

	_taskCv.notify_one();
}

void PriorityThreadManager::stop()
{
	{
		std::lock_guard<std::mutex>  lock(_tasksMutex);
		_running = false;
	}

	_taskCv.notify_all();

	for (auto& thread : _threads) 
	{
		if (thread.joinable()) 
		{
			thread.join();
		}
	}
}

void PriorityThreadManager::threadRun(const unsigned int threadID)
{
	while(_running) 
	{
		Task task(nullptr, nullptr);
		{
			std::unique_lock<std::mutex> lock(_tasksMutex);
			_taskCv.wait(lock, [&]() { return !_tasks.empty() || !_running; });

			if (!_running)
			{
				return;
			}

			updateCurPriority();

			if (_tasks[_curPriority].empty())
			{
				continue;
			}

			// Get last task from current priority
			task = _tasks[_curPriority].back();
			_tasks[_curPriority].pop_back();

			// If the priority list is empty after removing one, remove it
			if (_tasks[_curPriority].empty())
			{
				_activePriorities.erase(_curPriority);
				_tasks.erase(_curPriority);
			}
		}
		// Execute the function outside the lock
		task.func(task.data, threadID);
	}
}

bool PriorityThreadManager::updateCurPriority()
{
	if (_activePriorities.empty())
	{
		return false;
	}
	_curPriority = *_activePriorities.begin(); // lowest value in set 

	return true;
}

Task::Task(std::function<void(std::shared_ptr<void>, const unsigned int)> func, std::shared_ptr<void> data) 
	: func(func), data(data)
{}
