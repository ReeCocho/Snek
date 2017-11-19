#include "ThreadPool.hpp"

namespace snk
{
	WorkerThread::WorkerThread()
	{
		m_thread = std::thread(&WorkerThread::work, this);
	}

	WorkerThread::~WorkerThread()
	{
		if (m_thread.joinable())
		{
			wait();

			{
				std::lock_guard<std::mutex> lock(m_jobs_mutex);
				m_destroying = true;
				m_condition.notify_one();
			}

			m_thread.join();
		}
	}

	void WorkerThread::addJob(std::function<void(void)> job)
	{
		std::lock_guard<std::mutex> lock(m_jobs_mutex);
		m_jobs.push(move(job));
		m_condition.notify_one();
	}

	void WorkerThread::wait()
	{
		std::unique_lock<std::mutex> lock(m_jobs_mutex);
		m_condition.wait(lock, [this]() { return m_jobs.empty(); });
	}

	void WorkerThread::work()
	{
		while (true)
		{
			std::function<void(void)> job;
			{
				std::unique_lock<std::mutex> lock(m_jobs_mutex);
				m_condition.wait(lock, [this] { return !m_jobs.empty() || m_destroying; });

				if (m_destroying)
					break;

				job = m_jobs.front();
			}

			job();

			{
				std::lock_guard<std::mutex> lock(m_jobs_mutex);
				m_jobs.pop();
				m_condition.notify_one();
			}
		}
	}



	ThreadPool::ThreadPool()
	{
		
	}

	ThreadPool::ThreadPool(size_t threadCount)
	{
		for (size_t i = 0; i < threadCount; i++)
			workers.push_back(new WorkerThread());
	}

	ThreadPool::~ThreadPool()
	{
		wait();

		for (size_t i = 0; i < workers.size(); i++)
			delete workers[i];
	}



	void ThreadPool::wait()
	{
		for (size_t i = 0; i < workers.size(); i++)
			workers[i]->wait();
	}
}