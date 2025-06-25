

#include <string>

class Utils
{
public:
    static bool EndsWith(const std::string &str, const std::string &suffix)
    {
        return str.size() >= suffix.size() &&
               str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    static bool StartsWith(const std::string &str, const std::string &prefix)
    {
        return str.size() >= prefix.size() &&
               str.compare(0, prefix.size(), prefix) == 0;
    }

    static bool IsValidPath(const std::string &path)
    {
        // Check if the path is not empty and does not contain invalid characters
        return !path.empty() && path.find_first_of("<>:\"/\\|?*") == std::string::npos;
    }

    static std::string GetFileExtension(const std::string &path)
    {
        size_t pos = path.find_last_of('.');
        if (pos == std::string::npos || pos == 0 || pos == path.size() - 1)
            return "";
        return path.substr(pos + 1);
    }

    static std::string GetFileName(const std::string &path)
    {
        size_t pos = path.find_last_of("/\\");
        if (pos == std::string::npos)
            return path; // No directory part, return the whole path
        return path.substr(pos + 1);
    }
};