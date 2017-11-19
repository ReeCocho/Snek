#pragma once

/**
 * @file ThreadPool.hpp
 * @brief Thread pool header file.
 * @author Connor J. Bramham (ReeCocho)
 */

/** Includes */
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <functional>
#include <queue>
#include <condition_variable>

namespace snk
{
	/**
	 * @class WorkerThread
	 * @brief Performs work for a thread pool.
	 * @see ThreadPool
	 */
	class WorkerThread
	{
	public:

		/**
		 * @brief Constructor.
		 */
		WorkerThread();

		/**
		 * @brief Destructor.
		 */
		~WorkerThread();

		/**
		 * @brief Add a job to the worker thread.
		 */
		void addJob(std::function<void(void)> job);

		/**
		 * @brief Wait for the worker to finish working.
		 */
		void wait();

	private:

		/** Is the worker thread being destroyed? */
		bool m_destroying = false;

		/** Thread object. */
		std::thread m_thread;

		/** Job queue. */
		std::queue<std::function<void(void)>> m_jobs;

		/** Job queue mutex. */
		std::mutex m_jobs_mutex;

		/** Condition to wait for. */
		std::condition_variable m_condition;

		/** 
		 * @brief Work method.
		 */
		void work();
	};

	/**
	 * @class ThreadPool
	 * @brief Manages worker threads.
	 * @see WorkerThread
	 */
	class ThreadPool
	{
	public:

		/**
		 * @brief Constructor.
		 */
		ThreadPool();

		/**
		 * @brief Constructor.
		 * @param Number of worker threads.
		 */
		ThreadPool(size_t threadCount);

		/**
		 * @brief Destructor.
		 */
		~ThreadPool();



		/**
		 * @brief Wait for the thread pool to finish working.
		 */
		void wait();

		/**
		 * @brief Get number of worker threads.
		 * @return Number of worker threads.
		 */
		inline size_t getWorkerCount() const
		{
			return workers.size();
		}

		/** Worker threads. */
		std::vector<WorkerThread*> workers = {};	
	};
}