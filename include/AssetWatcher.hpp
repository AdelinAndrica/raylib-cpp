#pragma once
#include <string>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>

class AssetWatcher
{
public:
    explicit AssetWatcher(const std::string &directory);
    ~AssetWatcher();

    void Start();
    void Stop();
    void OnChange(const std::function<void(const std::string &)> &callback);

private:
    void WatchLoop();

    std::string directory;
    std::thread watcherThread;
    std::atomic<bool> running;
    std::function<void(const std::string &)> callback;
    std::mutex cbMutex;
};