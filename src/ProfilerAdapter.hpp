#pragma once
#include <memory>
#include <types.hpp> //Intercept types

class ScopeInfo {
public:
    virtual ~ScopeInfo() = default;
};

//This storage will be held between enter and leave of a scope. And can store information about this specific event, like start time
class ScopeTempStorage {
public:
    virtual ~ScopeTempStorage() = default;
};

enum class AdapterType {
    ArmaDiag,
    Brofiler,
    Chrome,
    Tracy,
    invalid
};

class ProfilerAdapter {
public:
    virtual ~ProfilerAdapter() = default;

    virtual void perFrame() = 0;

    virtual std::shared_ptr<ScopeInfo> createScope(intercept::types::r_string name, intercept::types::r_string filename, uint32_t fileline) = 0;

    virtual std::shared_ptr<ScopeTempStorage> enterScope(std::shared_ptr<ScopeInfo> scope) = 0;
    virtual void leaveScope(std::shared_ptr<ScopeTempStorage> tempStorage) = 0;
    virtual void setThisArgs(std::shared_ptr<ScopeTempStorage> tempStorage, intercept::types::game_value thisArgs) {}

    virtual void addLog(intercept::types::r_string message) {}
    virtual void setCounter(intercept::types::r_string name, float val) {};


    virtual void cleanup() {}

    bool IsScheduledSupported() const { return supportsScheduled; }
    AdapterType getType() const { return type; }
protected:
    bool supportsScheduled = false;
    AdapterType type = AdapterType::invalid;
};