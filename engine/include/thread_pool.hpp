
#pragma once

#include <functional> 
#include <queue> 
#include <vector> 
#include <thread> 
#include <atomic> 
#include <condition_variable> 
#include <mutex> 
#include <utility> 
#include <iostream> 

namespace jthread { 
    
    class thread_pool { 
    public: 
    
        thread_pool(); //initialized to hardware concurrency for num threads 
        thread_pool(int num_threads);

        ~thread_pool(); 
        
        template <typename F> 
        void enqueue_task(F&& task);

        void wait(); 
        

    private: 

        void run_worker(); 
        
        std::queue<std::function<void()>> m_task_queue;
        std::vector<std::thread> m_workers; 
        int m_num_threads; 
        std::atomic<bool> m_stop; 
        std::condition_variable m_cv; 
        std::mutex m_queue_mutex; 

        std::atomic<int> m_active_tasks = 0; 
    };
}


using jthread::thread_pool; 

thread_pool::thread_pool() : m_num_threads(std::thread::hardware_concurrency()), m_stop(false) { 
    m_workers.reserve(m_num_threads);
    for (int i = 0; i < m_num_threads; ++i) { 
        m_workers.emplace_back(&thread_pool::run_worker, this);
    }
}

thread_pool::thread_pool(int num_threads) : m_num_threads(num_threads), m_stop(false) { 
    m_workers.reserve(m_num_threads);
    for (int i = 0; i < m_num_threads; ++i) { 
        m_workers.emplace_back(&thread_pool::run_worker, this);
    }
}

thread_pool::~thread_pool() { 
    m_stop.store(true, std::memory_order_relaxed);
    m_cv.notify_all(); //wake up workers 
    
    for (auto& worker: m_workers) { 
        worker.join(); 
    }
}

template <typename F> 
void thread_pool::enqueue_task(F&& task) {
    {
        std::lock_guard<std::mutex> lock(m_queue_mutex);
        //foward keeps the arguments as original reference type (r value or l value)
        m_task_queue.push(std::function<void()>(std::forward<F>(task))); 
        m_active_tasks.fetch_add(1, std::memory_order_release);
    }
    m_cv.notify_one(); 
}

void thread_pool::run_worker() { 
    while (true) {
        std::function<void()> task; 
        {
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            //wait for notification from cv that task is ready (will unlock and relock the mutex) 
             m_cv.wait(lock, [this] { return m_stop.load(std::memory_order_relaxed) || !m_task_queue.empty(); });

            //return when stopped and all tasks complete 
            if (m_stop.load(std::memory_order_relaxed) && m_task_queue.empty())  
                return; 

            task = std::move(m_task_queue.front());
            m_task_queue.pop();
        }
        task(); 
        m_active_tasks.fetch_sub(1, std::memory_order_acquire);
    }
}

void thread_pool::wait() { 
    while (m_active_tasks.load(std::memory_order_acquire) > 0) { 
        std::this_thread::yield(); 
    }
}



