#include "AssetWatcher.hpp"
#include <filesystem>
#include <chrono>
#include <thread>
#include <atomic>
#include <unordered_map>
#include <functional>
#include <mutex>

namespace fs = std::filesystem;

AssetWatcher::AssetWatcher(const std::string &directory)
    : directory(directory), running(false) {}

AssetWatcher::~AssetWatcher()
{
    Stop();
}

void AssetWatcher::Start()
{
    if (running)
        return;
    running = true;
    watcherThread = std::thread([this]()
                                { WatchLoop(); });
}

void AssetWatcher::Stop()
{
    running = false;
    if (watcherThread.joinable())
        watcherThread.join();
}

void AssetWatcher::OnChange(const std::function<void(const std::string &)> &callback)
{
    std::lock_guard<std::mutex> lock(cbMutex);
    this->callback = callback;
}

void AssetWatcher::WatchLoop()
{
    using namespace std::chrono_literals;
    std::unordered_map<std::string, fs::file_time_type> lastWriteTimes;

    while (running)
    {
        for (const auto &entry : fs::recursive_directory_iterator(directory))
        {
            if (!entry.is_regular_file())
                continue;
            auto path = entry.path().string();
            auto lastWrite = fs::last_write_time(entry);

            if (lastWriteTimes.count(path))
            {
                if (lastWriteTimes[path] != lastWrite)
                {
                    lastWriteTimes[path] = lastWrite;
                    std::lock_guard<std::mutex> lock(cbMutex);
                    if (callback)
                        callback(path);
                }
            }
            else
            {
                lastWriteTimes[path] = lastWrite;
            }
        }
        std::this_thread::sleep_for(500ms);
    }
}