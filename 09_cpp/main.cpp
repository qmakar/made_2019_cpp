//
//  main.cpp
//  09_cpp
//
//  Created by qmakar on 12.01.2020.
//  Copyright © 2020 qmakar. All rights reserved.
//
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <iostream>
#include <queue>
#include <cassert>

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
                                                                return !queue.empty() + !run;
                                                            }
                                                        );
                                         if (!run && queue.empty())
                                             return;
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
    auto task = std::make_shared<std::packaged_task<
                                                    decltype(func(args...))()
                                                    >
                                >
                                (std::bind(func, (args)...));
    
    std::future<decltype(func(args...))> result = task->get_future();
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

int main()
{
    ThreadPool pool(8);
    std::vector<std::future<char>> results;
    
    auto task1 = pool.exec([]() { return "ASDF"; });
    auto res1 = task1.get();
    assert(res1 == "ASDF");
    std::cout << "[]() { return \"ASDF\"; }   --->   " << res1 << std::endl;
    
    auto task2 = pool.exec([]() { return 1; });
    auto res2 = task2.get();
    assert(res2 == 1);
    std::cout << "[]() { return 1; }   --->   " << res2 << std::endl;
    
    auto task3 = pool.exec([](int a) { return a; }, 4);
    auto res3 = task3.get();
    assert(res3 == 4);
    std::cout << "[](int a) { return a; }(4)   --->   " << res3 << std::endl;
    
    int d = 4;
    auto task4 = pool.exec([d] (int a, int b, int c) { return a + b + c + d; }, 1, 2, 3);
    auto res4 = task4.get();
    assert(res4 == 10);
    std::cout << "[d](int a, int b, int c) { return a + b + c + d; }(1,2,3)   --->   " << res4 << std::endl;
    
    for (int i = 0; i < 5; i++){
        results.emplace_back(pool.exec([i]() { return char(int('A') + i); }));
    }
    char check[5] = {'A', 'B', 'C', 'D', 'E'};
    std::cout << "[i]() { return char(int('A') + i); }   --->   " ;
    for (int i = 0;  i < 5; i++){
        char sym = results[i].get();
        assert(sym == check[i]);
        std::cout << sym << " ";
    }
    std::cout << std::endl;
    
    auto task5 = pool.exec(simple_function, 4000);
    auto res5 = task5.get();
    assert(res5 == 7998000);
    std::cout << "simple_function, 4000   --->   " << res5 << std::endl;
    
    auto task6 = pool.exec(functor(), 1,2,3);
    auto res6 = task6.get();
    assert(res6.elem_ == 16);
    std::cout << "functor(), 1,2,3   --->   " << res6.elem_ << std::endl;
    
    std::cout << "\n\nAll tests passed!!!\n\n";
    
    return 0;
}
