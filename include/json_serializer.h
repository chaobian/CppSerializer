#ifndef ____CPP_SERIALIZER_JSON_SERIALIZER_H__
#define ____CPP_SERIALIZER_JSON_SERIALIZER_H__
#include "rapidjson/document.h"
#include <stdint.h>

typedef rapidjson::GenericValue<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<>> RapidJsonValue;
typedef rapidjson::Document RapidJsonDocument;

//typedef RapidJsonDocument JsonDocument;
//typedef RapidJsonValue JsonValue;

template<class JsonValue = RapidJsonValue, class JsonDocument = RapidJsonDocument>
class CxxJsonValueT
{
public:
  CxxJsonValueT() : dom_()
  {
  }

  CxxJsonValueT(JsonValue* json_value)
  {
    dom_ = json_value;
  }

  bool Get(const char* name, CxxJsonValueT& v)
  {
    JsonValue* json_value = Get_(name);
    if (json_value != NULL)
    {
      v.dom_ = json_value;
      return true;
    }
    else
    {
      v.dom_ = NULL;
      return false;
    }
  }

  template<typename T>
  bool Get(const char* name, T* v)
  {
    JsonValue* json_value = Get_(name);
    if (json_value != NULL && json_value->IsObject())
    {
      CxxJsonValue xxJsonValue(json_value);
      return CxxJsonTraits::FromJson(&xxJsonValue, v);
    }
    else
    {
      return false;
    }
  }

  bool Get(const char* name, uint8_t* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, uint8_t& v)
  {
    uint32_t v32;
    const uint32_t max_value = UINT8_MAX;
    if (Get(name, v32) && v32 <= max_value)
    {
      v = (uint8_t)v32;
      return true;
    }
    else
    {
      v = 0;
      return false;
    }
  }

  bool Get(const char* name, int8_t* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, int8_t& v)
  {
    int32_t v32;
    const int32_t max_value = INT8_MAX;
    const int32_t min_value = INT8_MIN;
    if (Get(name, v32) && v32 <= max_value && v32 >= min_value)
    {
      v = (int8_t)v32;
      return true;
    }
    else
    {
      v = 0;
      return false;
    }
  }

  bool Get(const char* name, uint16_t* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, uint16_t& v)
  {
    uint32_t v32;
    const uint32_t max_value = UINT16_MAX;
    if (Get(name, v32) && v32 <= max_value)
    {
      v = (uint16_t)v32;
      return true;
    }
    else
    {
      v = 0;
      return false;
    }
  }

  bool Get(const char* name, int16_t* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, int16_t& v)
  {
    int32_t v32;
    const int32_t max_value = INT16_MAX;
    const int32_t min_value = INT16_MIN;
    if (Get(name, v32) && v32 <= max_value && v32 >= min_value)
    {
      v = (int16_t)v32;
      return true;
    }
    else
    {
      v = 0;
      return false;
    }
  }

  bool Get(const char* name, int32_t* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, int32_t& v)
  {
    JsonValue* json_value = Get_(name);
    if (json_value != NULL&& json_value->IsInt())
    {
      v = json_value->GetInt();
      return true;
    }
    else
    {
      v = 0;
      return false;
    }
  }

  bool Get(const char* name, uint32_t* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, uint32_t& v)
  {
    JsonValue* json_value = Get_(name);
    if (json_value != NULL && json_value->IsUint())
    {
      v = json_value->GetUint();
      return true;
    }
    else
    {
      v = 0;
      return false;
    }
  }

  bool Get(const char* name, int64_t* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, int64_t& v)
  {
    JsonValue* json_value = Get_(name);
    if (json_value != NULL && json_value->IsInt64())
    {
      v = json_value->GetInt64();
      return true;
    }
    else
    {
      v = 0;
      return false;
    }
  }

  bool Get(const char* name, uint64_t* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, uint64_t& v)
  {
    JsonValue* json_value = Get_(name);
    if (json_value != NULL && json_value->IsUint64())
    {
      v = json_value->GetUint64();
      return true;
    }
    else
    {
      v = 0;
      return false;
    }
  }

  bool Get(const char* name, double* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, double& v)
  {
    JsonValue* json_value = Get_(name);
    if (json_value != NULL && json_value->IsNumber())
    {
      v = json_value->GetDouble();
      return true;
    }
    else
    {
      v = 0;
      return false;
    }
  }

  bool Get(const char* name, std::string* v)
  {
    return Get(name, *v);
  }

  bool Get(const char* name, std::string& v)
  {
    JsonValue* json_value = Get_(name);
    if (json_value != NULL && json_value->IsString())
    {
      v = json_value->GetString();
      return true;
    }
    else
    {
      v.clear();
      return false;
    }
  }

  bool IsValid() const
  {
    return dom_ != NULL;
  }

protected:
  

  JsonValue* Get_(const char* name)
  {
    JsonValue::MemberIterator iter = dom_->FindMember(name);
    if (iter != dom_->MemberEnd())
    {
      return (&(iter->value));
    }
    else
    {
      return NULL;
    }
  }

private:
  JsonValue* dom_;
};

typedef CxxJsonValueT<> CxxJsonValue;

namespace CxxJson
{
  template<typename T>
  bool FromJsonText(const char* json_text, T* x){
    RapidJsonDocument d;
    d.Parse(json_text);
    if (d.HasParseError())
    {
      return false;
    }

    CxxJsonValueT<> xx(&d);
    return CxxJsonTraits::FromJson(&xx, x);
  }
}

#define JSON_SERIALIZE_TRAITS_NAME(struct_name) CxxJsonTraits

#define JSON_SERIALIZE_STRUCT_TRAITS_BEGIN(struct_name) \
  namespace JSON_SERIALIZE_TRAITS_NAME(struct_name) {\
     inline bool FromJson(const char* json_text, struct_name* x) {\
      return CxxJson::FromJsonText<struct_name>(json_text, x);\
     }\
     bool FromJson(CxxJsonValue* json_value, struct_name* x);\
  };\

#define CxxJsonDeserialize(text, struct_name, v) \
 JSON_SERIALIZE_TRAITS_NAME(struct_name)::FromJson(text, v)

#endif