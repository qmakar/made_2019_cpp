//
//  Threads.h
//  09_cpp
//
//  Created by qmakar on 14.01.2020.
//  Copyright © 2020 qmakar. All rights reserved.
//

#ifndef Threads_h
#define Threads_h

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <queue>

class ThreadPool {
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> queue;
    std::mutex m;
    std::condition_variable condition;
    std::atomic_bool run;
    
public:
    ThreadPool(int threads);
    template<class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
    ~ThreadPool();
};

ThreadPool::ThreadPool(int num){
    run = true;
    for(int i = 0; i < num; ++i){
        threads.emplace_back(
                             [&]()
                             {
                                 while(true)
                                 {
                                     std::function<void()> task;
                                     
                                     {
                                         std::unique_lock<std::mutex> mut(m);
                                         condition.wait(mut, [&]()
                                                        {
                                                            return !queue.empty() || !run;
                                                        }
                                                        );
                                         if (queue.empty()){
                                             return;
                                         }
                                         task = queue.front();
                                         queue.pop();
                                     }
                                     
                                     task();
                                 }
                             }
                             );
    }
}

template<class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
    auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>
                                (std::bind(func, (args)...));
    
    auto result = task->get_future();
    {
        std::unique_lock<std::mutex> lock(m);
        queue.emplace(
                      [task]()
                      {
                          (*task)();
                      }
                      );
    }
    condition.notify_one();
    return result;
    
}

ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(m);
        run = false;
    }
    condition.notify_all();
    for (auto& thread: threads){
        thread.join();
    }
}

int simple_function(int a){
    int sum = 0;
    for (int i = 0; i < a; i++){
        sum += i;
    }
    return sum;
}

struct functor{
    int elem_;
    functor operator()(int a, int b, int c) {
        functor nn;
        nn.elem_ = a + b + c + 10;
        return nn;
    }
};


#endif /* Threads_h */
