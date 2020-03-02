#include "safty_queue.hpp"

void SaftyQueue::push(std::string object)
{
    std::lock_guard<std::mutex>lck{m_mtx};
    m_safeQueue.push(object);
    m_condVar.notify_one();
}

std::string SaftyQueue::pop()
{
    std::unique_lock<std::mutex> lck{m_mtx};
    m_condVar.wait(lck, [this]
                   {
                      return !m_safeQueue.empty();
                    });
    std::string res = m_safeQueue.front();
    m_safeQueue.pop();
    return res;
}