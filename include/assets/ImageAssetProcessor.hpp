#pragma once
#include "assets/IAssetProcessor.hpp"

class ImageAssetProcessor : public IAssetProcessor
{
public:
    bool CanProcess(const std::string &path) const override;
    bool Process(const std::string &path) override;
    bool Validate(const std::string &path) override;
    void Fallback(const std::string &path) override;
};