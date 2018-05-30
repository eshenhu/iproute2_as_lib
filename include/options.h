#ifndef _IPROUTE2_OPTIONS_H_
#define _IPROUTE2_OPTIONS_H_

#include <list>
#include <map>
#include <string.h>
#include <memory>

namespace iproute2_lib {

class InfElement
{
public:
    virtual std::string to_string() const = 0;
};

class Cmd : public InfElement
{
public:
    Cmd() = default;
public:
    std::string to_string() const override
    {
        return std::string("ip");
    };
};

class CmdOptJsonSupport : public InfElement
{
public:
    std::string to_string() const override
    {
        return std::string("-json");
    }
};

class OptObject : public InfElement
{
public:
    enum class OptObjectTypeE : unsigned int
    {
        OBJECT_LINK,
        OBJECT_ADDR
    };
public:
    OptObject() = delete;
    OptObject(OptObjectTypeE type):m_type(type){};

public:
    std::string to_string() const override
    {
        const std::map<OptObjectTypeE, const std::string> to_stringMap = 
        {
            {OptObjectTypeE::OBJECT_LINK, "link"},
            {OptObjectTypeE::OBJECT_ADDR, "address"}
        };
        auto iter = to_stringMap.find(m_type);
        return iter->second;
    };
public:
    OptObjectTypeE m_type;
};

class OptFamily : public InfElement
{
    enum class OptFamilyTypeE : unsigned int
    {
        FAMILY_INET,
        FAMILY_INET6,
        FAMILY_IPX,
        FAMILY_DNET,
        FAMILY_MPLS,
        FAMILY_BRIDGE,
        FAMILY_LINK
    };
public:
    OptFamily() = delete;
    OptFamily(OptFamily::OptFamilyTypeE type):m_type(type){};

public:
    OptFamilyTypeE m_type;
public:
    std::string to_string() const override
    {
        const std::map<OptFamilyTypeE, const std::string> to_stringMap = 
        {
            {OptFamilyTypeE::FAMILY_INET, "inet" },
            {OptFamilyTypeE::FAMILY_INET6,"inet6"},
            {OptFamilyTypeE::FAMILY_IPX,  "ipx"  },
            {OptFamilyTypeE::FAMILY_DNET, "dnet" },
            {OptFamilyTypeE::FAMILY_MPLS, "mpls" },
            {OptFamilyTypeE::FAMILY_BRIDGE,"bridge"},
            {OptFamilyTypeE::FAMILY_LINK, "link" }
        };
        auto iter = to_stringMap.find(m_type);
        return iter->second;
    };
};

struct OptionsArgs
{
    int argc;
    char** argv; 
};
const struct OptionsArgs null_options_args = 
{
    0, NULL
};

class Options 
{
public:
    Options(OptObject::OptObjectTypeE e):
    _object(e)
    {
    };

public:
    std::list<std::shared_ptr<InfElement>>& get_cmd_opt_list()
    {
        return _cmd_opt_list;
    };
    std::list<std::shared_ptr<InfElement>>& get_obj_opt_list()
    {
        return _object_opt_list;
    };
    OptObject& get_object()
    {
        return _object;
    };

    struct OptionsArgs format_one_line() 
    {
        struct OptionsArgs args;
        int size = 1 + _cmd_opt_list.size() + 1 + _object_opt_list.size();
        char** argv = (char**)malloc(sizeof(char*) * size);
        if (argv == NULL)
            return null_options_args;

        args.argc = size;
        args.argv = argv;
        int i = 0;
        argv[i++] = strdup(_cmd.to_string().c_str());

        for (auto& ele : _cmd_opt_list)
            argv[i++] = strdup(ele->to_string().c_str());

        argv[i++] = strdup(_object.to_string().c_str());

        for (auto& ele : _object_opt_list)
            argv[i++] = strdup(ele->to_string().c_str());
        
        return args;
    }
private:
    Cmd _cmd;
    std::list<std::shared_ptr<InfElement>> _cmd_opt_list;
    OptObject _object;    
    std::list<std::shared_ptr<InfElement>> _object_opt_list;
};

class FactoryOptions
{
public:
    FactoryOptions() = delete;
public:
    static Options make_ip_addr_basic()
    {
        Options opt(OptObject::OptObjectTypeE::OBJECT_ADDR);
        std::shared_ptr<InfElement> opt_json = std::make_shared<CmdOptJsonSupport>();
        opt.get_cmd_opt_list().push_back(std::move(opt_json));
        return opt;
    };
};
}
#endif // !1 _I{PROUTE2_OPTIONS_H_
