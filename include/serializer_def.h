#ifndef ____CPP_SERIALIZER_DEF_H__
#define ____CPP_SERIALIZER_DEF_H__
#include <string>
#include <exception>

#ifdef NDEBUG
#define THROW_SERIALIZER_EXCEPTION(struct_name, field_name) \
  throw serializer_exception(struct_name, field_name)
#else
#define THROW_SERIALIZER_EXCEPTION(struct_name, field_name) \
throw serializer_exception(struct_name, field_name, __FILE__, __LINE__)
#endif

enum serializer_error
{
  serializer_error_succeed = 0,
  serializer_error_not_found = 1,
  serializer_error_invalid_format =2,
  serializer_error_invalid_type = 3,
};

typedef void(*serializer_log_function)(
  const char * struct_name,
  const char * const & field_name,
  const char * file_name,
  int file_line,
  serializer_error err);

// Microsoft Compiler
#ifdef _MSC_VER
__declspec(selectany) serializer_log_function g_serializer_log_function;
inline serializer_log_function set_serializer_log(serializer_log_function log)
{
  serializer_log_function old = g_serializer_log_function;
  g_serializer_log_function = log;
  return old;
}

inline void serializer_log(const char * struct_name,
  const char * const & field_name,
  const char * file_name,
  int file_line,
  serializer_error err)
{
  if (g_serializer_log_function)
  {
    g_serializer_log_function(struct_name, field_name, file_name, file_line, err);
  }
}

#else
#endif

#ifdef NDEBUG
#define CXX_SERIALIZER_LOG(struct_name, field_name, err) \
  serializer_log(struct_name, field_name, "", 0, err)
#else
#define CXX_SERIALIZER_LOG(struct_name, field_name) \
  serializer_log(struct_name, field_name, __FILE__, __LINE__, err)
#endif

class serializer_exception : public std::exception
{
public:
  serializer_exception(const char * const & struct_name, const char * const & field_name)
    : serializer_exception(struct_name, field_name, NULL, 0){
    if (struct_name)
    {
      struct_name_ = struct_name;
    }

    if (field_name)
    {
      field_name_ = field_name;
    }
  }

  serializer_exception(
    const char * const & struct_name, 
    const char * const & field_name,
    const char * const & message,
    int line)
    : exception("serializer_exception"),
    line_(line){
    if (struct_name)
    {
      struct_name_ = struct_name;
    }

    if (field_name)
    {
      field_name_ = field_name;
    }

    if (message)
    {
      message_ = message;
    }
  }

  ~serializer_exception()
  {
  }

  const char* Struct() const
  {
    return struct_name_.c_str();
  }

  const char* Field() const
  {
    return field_name_.c_str();
  }

  const char* Message() const
  {
    return message_.c_str();
  }

  const int Line() const
  {
    return line_;
  }

protected:
private:
  std::string struct_name_;
  std::string field_name_;
  int line_;
  std::string message_;
};

#ifndef NO_JSON_SERIALIZE
#include "json_serializer.h"
#else
#define JSON_SERIALIZE_STRUCT_TRAITS_BEGIN(struct_name)
#endif

#define SERIALIZE_STRUCT_TRAITS_BEGIN(struct_name) \
  struct struct_name; \
  JSON_SERIALIZE_STRUCT_TRAITS_BEGIN(struct_name);


#define SERIALIZE_STRUCT_TRAITS_END()

#define SERIALIZE_STRUCT_TRAITS_MEMBER(name) 

#define  SERIALIZE_STRUCT_TRAITS_MEMBER_VALIDATE(name) 

#define SERIALIZE_STRUCT_TRAITS_MEMBER_REQUIRED(name) \
  SERIALIZE_STRUCT_TRAITS_MEMBER(name) \
  SERIALIZE_STRUCT_TRAITS_MEMBER_VALIDATE(name)

#define SERIALIZE_STRUCT_BEGIN(struct_name) \
  SERIALIZE_STRUCT_TRAITS_BEGIN(struct_name) \
  struct  struct_name \
  {\

#define SERIALIZE_STRUCT_END() \
  SERIALIZE_STRUCT_TRAITS_END() \
  };

#define SERIALIZE_STRUCT_MEMBER(type, name) \
  type name; \
  SERIALIZE_STRUCT_TRAITS_MEMBER(name)

// the name is required.
#define SERIALIZE_STRUCT_MEMBER_REQUIRED(type, name) \
  SERIALIZE_STRUCT_MEMBER(type, name) \
  SERIALIZE_STRUCT_TRAITS_MEMBER_VALIDATE(name)

/*
supported value types
1. int, int6, int16, int32, int64
2. uint, uint6, uint16, uint32, uint64
3. float double
4. bool
supported STL iterators:
1. std::vector
2. std::map
3. std::list
*/

#endif