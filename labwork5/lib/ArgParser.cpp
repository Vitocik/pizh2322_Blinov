#include "ArgParser.h"
#include <sstream>
#include <algorithm>

namespace ArgumentParser {

    // ===== BaseArgument =====
    BaseArgument::BaseArgument(const std::string& long_name) : long_name(long_name) {}

    BaseArgument& BaseArgument::Positional() {
        is_positional = true;
        return *this;
    }

    BaseArgument& BaseArgument::Default(const std::string& val) {
        has_default = true;
        default_value = val;
        return *this;
    }

    BaseArgument& BaseArgument::MultiValue(size_t min) {
        is_multi = true;
        min_count = min;
        return *this;
    }

    BaseArgument& BaseArgument::StoreValue(std::string& ref) {
        store_callback = [&ref](const std::string& val) { ref = val; };
        return *this;
    }

    BaseArgument& BaseArgument::StoreValue(bool&) {
        throw std::logic_error("StoreValue<bool> not supported for this argument");
    }

    BaseArgument& BaseArgument::StoreValues(std::vector<std::string>& ref) {
        store_callback = [&ref](const std::string& val) { ref.push_back(val); };
        return *this;
    }

    BaseArgument& BaseArgument::Help(const std::string& desc) {
        description = desc;
        return *this;
    }

    // ===== StringArgument =====
    bool StringArgument::Parse(const std::string& value) {
        values.push_back(value);
        if (store_callback) store_callback(value);
        return true;
    }

    const std::string& StringArgument::GetValue(size_t index) const {
        return values.at(index);
    }

    // ===== IntArgument =====
    bool IntArgument::Parse(const std::string& value) {
        try {
            int v = std::stoi(value);
            values.push_back(v);
            if (store_callback) store_callback(value);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    int IntArgument::GetValue(size_t index) const {
        return values.at(index);
    }

    IntArgument& IntArgument::StoreValues(std::vector<int>& ref) {
        store_callback = [&ref](const std::string& val) {
            ref.push_back(std::stoi(val));
            };
        return *this;
    }

    // ===== FlagArgument =====
    bool FlagArgument::Parse(const std::string&) {
        value = true;
        if (store_callback) store_callback("true");
        return true;
    }

    bool FlagArgument::GetValue() const {
        return value;
    }

    BaseArgument& FlagArgument::StoreValue(bool& ref) {
        store_callback = [&ref](const std::string&) { ref = true; };
        return *this;
    }

    // ===== ArgParser =====
    ArgParser::ArgParser(const std::string& desc) : description(desc) {}

    BaseArgument& ArgParser::Register(BaseArgument* arg) {
        if (!arg->long_name.empty()) arguments[arg->long_name] = arg;
        if (arg->short_name) short_to_long[arg->short_name] = arg->long_name;
        if (arg->is_positional) positionals.push_back(arg);
        return *arg;
    }

    IntArgument& ArgParser::AddIntArgument(const std::string& name) {
        return static_cast<IntArgument&>(Register(new IntArgument(name)));
    }

    IntArgument& ArgParser::AddIntArgument(const char* name) {
        return AddIntArgument(std::string(name));
    }

    IntArgument& ArgParser::AddIntArgument(char short_name, const std::string& name) {
        auto* arg = new IntArgument(name);
        arg->short_name = short_name;
        return static_cast<IntArgument&>(Register(arg));
    }

    IntArgument& ArgParser::AddIntArgument(char short_name, const std::string& name, const std::string& desc) {
        auto* arg = new IntArgument(name);
        arg->short_name = short_name;
        arg->description = desc;
        return static_cast<IntArgument&>(Register(arg));
    }

    StringArgument& ArgParser::AddStringArgument(const std::string& name) {
        return static_cast<StringArgument&>(Register(new StringArgument(name)));
    }

    StringArgument& ArgParser::AddStringArgument(const char* name) {
        return AddStringArgument(std::string(name));
    }

    StringArgument& ArgParser::AddStringArgument(char short_name, const std::string& name) {
        auto* arg = new StringArgument(name);
        arg->short_name = short_name;
        return static_cast<StringArgument&>(Register(arg));
    }

    StringArgument& ArgParser::AddStringArgument(char short_name, const std::string& name, const std::string& desc) {
        auto* arg = new StringArgument(name);
        arg->short_name = short_name;
        arg->description = desc;
        return static_cast<StringArgument&>(Register(arg));
    }

    FlagArgument& ArgParser::AddFlag(char short_name, const std::string& name, const std::string& desc) {
        auto* arg = new FlagArgument(name);
        arg->short_name = short_name;
        arg->description = desc;
        arg->is_flag = true;
        return static_cast<FlagArgument&>(Register(arg));
    }

    FlagArgument& ArgParser::AddFlag(const std::string& name, const std::string& desc) {
        return AddFlag(0, name, desc);
    }

    FlagArgument& ArgParser::AddHelp(char short_name, const std::string& name, const std::string& desc) {
        help_name = name;
        auto& flag = AddFlag(short_name, name, desc);
        help_flag = &flag;
        flag.store_callback = [&](const std::string&) {
            help_requested = true;
            };
        return flag;
    }

    BaseArgument* ArgParser::FindArgument(const std::string& token) {
        if (token.size() > 2 && token[0] == '-' && token[1] == '-') {
            auto eq = token.find('=');
            std::string name = token.substr(2, eq - 2);
            if (arguments.count(name)) return arguments[name];
        }
        else if (token.size() == 2 && token[0] == '-') {
            char ch = token[1];
            if (short_to_long.count(ch)) return arguments[short_to_long[ch]];
        }
        return nullptr;
    }

    bool ArgParser::ParseArgument(BaseArgument* arg, const std::string& value) {
        if (!arg) return false;
        return arg->Parse(value);
    }

    bool ArgParser::Parse(const std::vector<std::string>& args) {
        size_t pos_idx = 0;
        size_t i = 0;

        // Skip app name if it's not an argument
        if (!args.empty() && args[0][0] != '-') {
            i = 1;
        }

        for (; i < args.size(); ++i) {
            const std::string& token = args[i];

            // Check for help flag
            if (help_flag && token == "--" + help_flag->long_name) {
                help_requested = true;
                return true;
            }

            if (token.size() > 2 && token[0] == '-' && token[1] == '-') {
                // Long argument (--param=value or --param value)
                size_t eq_pos = token.find('=');
                std::string name = token.substr(2, eq_pos - 2);

                if (!arguments.count(name)) return false;

                BaseArgument* arg = arguments[name];
                std::string value;

                if (eq_pos != std::string::npos) {
                    value = token.substr(eq_pos + 1);
                }
                else if (arg->is_flag) {
                    value = "";
                }
                else if (i + 1 < args.size() && args[i + 1][0] != '-') {
                    value = args[++i];
                }
                else {
                    return false;
                }

                if (!ParseArgument(arg, value)) return false;
            }
            else if (token.size() > 1 && token[0] == '-' && token[1] != '-') {
                // Short argument (-p=value or -p value or -abc for flags)
                size_t eq_pos = token.find('=');

                if (eq_pos != std::string::npos) {
                    // Format: -p=value
                    char short_name = token[1];
                    std::string value = token.substr(eq_pos + 1);

                    if (!short_to_long.count(short_name)) return false;
                    BaseArgument* arg = arguments[short_to_long[short_name]];
                    if (!ParseArgument(arg, value)) return false;
                }
                else {
                    // Either -p value or -abc (flags)
                    if (token.size() == 2) {
                        // Single short option: -p value
                        char short_name = token[1];
                        if (!short_to_long.count(short_name)) return false;
                        BaseArgument* arg = arguments[short_to_long[short_name]];
                        if (arg->is_flag) {
                            if (!ParseArgument(arg, "")) return false;
                        }
                        else {
                            if (i + 1 >= args.size() || args[i + 1][0] == '-') return false;
                            if (!ParseArgument(arg, args[++i])) return false;
                        }
                    }
                    else {
                        // Multiple short flags: -abc
                        for (size_t j = 1; j < token.size(); ++j) {
                            char short_name = token[j];
                            if (!short_to_long.count(short_name)) return false;
                            BaseArgument* arg = arguments[short_to_long[short_name]];
                            if (!arg->is_flag) return false;
                            if (!ParseArgument(arg, "")) return false;
                        }
                    }
                }
            }
            else if (pos_idx < positionals.size()) {
                BaseArgument* arg = positionals[pos_idx];

                if (arg->is_multi) {
                    if (!ParseArgument(arg, token)) return false;
                }
                else {
                    if (!ParseArgument(arg, token)) return false;
                    pos_idx++;
                }
            }
        }

        // Check required positional arguments
        while (pos_idx < positionals.size()) {
            BaseArgument* arg = positionals[pos_idx++];
            if (!arg->has_default) return false;
            ParseArgument(arg, std::any_cast<std::string>(arg->default_value));
        }

        // Check required named arguments
        for (const auto& [name, arg] : arguments) {
            if (arg->is_flag) continue;

            size_t count = 0;
            if (auto* str_arg = dynamic_cast<StringArgument*>(arg)) {
                count = str_arg->values.size();
            }
            else if (auto* int_arg = dynamic_cast<IntArgument*>(arg)) {
                count = int_arg->values.size();
            }

            if (count == 0 && arg->has_default) {
                ParseArgument(arg, std::any_cast<std::string>(arg->default_value));
                count = 1;
            }

            if (count == 0) return false;
            if (arg->is_multi && count < arg->min_count) return false;
        }

        return true;
    }

    bool ArgParser::Parse(int argc, char** argv) {
        std::vector<std::string> args(argv + 1, argv + argc);
        return Parse(args);
    }

    std::string ArgParser::HelpDescription() const {
        std::stringstream ss;
        ss << description << "\n";

        if (!help_name.empty() && help_flag != nullptr) {
            ss << help_flag->description << "\n\n";
        }

        for (const auto& [name, arg] : arguments) {
            // Хелп-флаг будет выведен отдельно в конце
            if (name == help_name) continue;

            if (arg->short_name) ss << "-" << arg->short_name << ", ";
            else ss << "    ";
            ss << "--" << name;

            if (!arg->is_flag) {
                if (dynamic_cast<const IntArgument*>(arg)) {
                    ss << "=<int>";
                }
                else {
                    ss << "=<string>";
                }

                if (arg->is_multi) {
                    ss << " [repeated, min args = " << arg->min_count << "]";
                }
            }

            ss << ",  " << arg->description;

            if (arg->is_flag && arg == help_flag) {
                ss << " Display this help and exit";
            }

            if (arg->has_default) {
                ss << " [default = " << std::any_cast<std::string>(arg->default_value) << "]";
            }

            ss << "\n";
        }

        if (help_flag) {
            ss << "-";
            if (help_flag->short_name) ss << help_flag->short_name << ", ";
            else ss << "    ";
            ss << "--" << help_name << " Display this help and exit\n";
        }

        return ss.str();
    }


    std::string ArgParser::GetStringValue(const std::string& name, size_t index) const {
        auto* arg = dynamic_cast<StringArgument*>(arguments.at(name));
        return arg->GetValue(index);
    }

    int ArgParser::GetIntValue(const std::string& name, size_t index) const {
        auto* arg = dynamic_cast<IntArgument*>(arguments.at(name));
        return arg->GetValue(index);
    }

    bool ArgParser::GetFlag(const std::string& name) const {
        auto* arg = dynamic_cast<FlagArgument*>(arguments.at(name));
        return arg->GetValue();
    }

    bool ArgParser::Help() const {
        return help_requested;
    }

} // namespace ArgumentParser
