#ifndef SAFTY_QUEUE_HPP
#define SAFTY_QUEUE_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

class SaftyQueue
{
public:
    void push(const std::string object);
    std::string pop();

private:
    std::queue<std::string> m_safeQueue;
    std::condition_variable m_condVar;
    std::mutex m_mtx;
};

#endif // SAFTY_QUEUE_HPP