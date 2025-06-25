#pragma once
#include <string>

class IAssetProcessor
{
public:
    virtual ~IAssetProcessor() = default;
    virtual bool CanProcess(const std::string &path) const = 0;
    virtual bool Process(const std::string &path) = 0;
    // Procesare avansată: validare, fallback, compresie, conversie
    virtual bool Validate(const std::string &path) { return true; }
    virtual void Fallback(const std::string &path) {}
};