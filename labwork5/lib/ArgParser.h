#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <functional>
#include <variant>
#include <any>
#include <stdexcept>

namespace ArgumentParser {

    class BaseArgument {
    public:
        std::string long_name;
        char short_name = 0;
        std::string description;
        bool is_flag = false;
        bool is_positional = false;
        bool is_multi = false;
        size_t min_count = 0;
        bool has_default = false;
        std::any default_value;
        std::function<void(const std::string&)> store_callback;

        BaseArgument(const std::string& long_name);
        virtual ~BaseArgument() {}

        virtual BaseArgument& Positional();
        virtual BaseArgument& Default(const std::string& val);
        virtual BaseArgument& MultiValue(size_t min = 0);
        virtual BaseArgument& StoreValue(std::string& ref);
        virtual BaseArgument& StoreValue(bool& ref);
        virtual BaseArgument& StoreValues(std::vector<std::string>& ref);
        virtual BaseArgument& StoreValues(std::vector<int>& ref);
        virtual BaseArgument& Help(const std::string& desc);

        virtual bool Parse(const std::string& value) = 0;
    };

    class StringArgument : public BaseArgument {
    public:
        std::vector<std::string> values;

        using BaseArgument::BaseArgument;
        bool Parse(const std::string& value) override;
        const std::string& GetValue(size_t index = 0) const;
    };

    class IntArgument : public BaseArgument {
    public:
        std::vector<int> values;

        using BaseArgument::BaseArgument;
        bool Parse(const std::string& value) override;
        int GetValue(size_t index = 0) const;
        BaseArgument& StoreValues(std::vector<int>& ref) override;
    };

    class FlagArgument : public BaseArgument {
    public:
        bool value = false;

        using BaseArgument::BaseArgument;
        bool Parse(const std::string& value) override;
        bool GetValue() const;
        BaseArgument& StoreValue(bool& ref) override;
    };

    class ArgParser {
    public:
        ArgParser(const std::string& description = "");

        IntArgument& AddIntArgument(const std::string& name);
        IntArgument& AddIntArgument(const char* name);
        IntArgument& AddIntArgument(char short_name, const std::string& name);
        IntArgument& AddIntArgument(char short_name, const std::string& name, const std::string& desc);

        StringArgument& AddStringArgument(const std::string& name);
        StringArgument& AddStringArgument(const char* name);
        StringArgument& AddStringArgument(char short_name, const std::string& name);
        StringArgument& AddStringArgument(char short_name, const std::string& name, const std::string& desc);

        FlagArgument& AddFlag(char short_name, const std::string& name, const std::string& desc = "");
        FlagArgument& AddFlag(const std::string& name, const std::string& desc = "");
        FlagArgument& AddHelp(char short_name, const std::string& name, const std::string& desc = "");

        bool Parse(int argc, char** argv);
        bool Parse(const std::vector<std::string>& args);
        bool Help() const;
        std::string HelpDescription() const;

        std::string GetStringValue(const std::string& name, size_t index = 0) const;
        int GetIntValue(const std::string& name, size_t index = 0) const;
        bool GetFlag(const std::string& name) const;

    private:
        std::string description;
        std::unordered_map<std::string, BaseArgument*> arguments;
        std::unordered_map<char, std::string> short_to_long;
        std::vector<BaseArgument*> positionals;
        FlagArgument* help_flag = nullptr;
        std::string help_name;
        bool help_requested = false;

        BaseArgument& Register(BaseArgument* arg);
        BaseArgument* FindArgument(const std::string& token);
        bool ParseArgument(BaseArgument* arg, const std::string& value);
    };

} // namespace ArgumentParser
