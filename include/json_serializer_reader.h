#ifndef ____CPP_SERIALIZER_JSON_SERIALIZER_READER_H__
#define ____CPP_SERIALIZER_JSON_SERIALIZER_READER_H__
#include "json_serializer.h"
#ifndef SERIALIZER_DATA_IMPL
#error you should only use this head file in your data impl Cxx files.
#endif

#ifdef SERIALIZE_STRUCT_TRAITS_BEGIN
#undef SERIALIZE_STRUCT_TRAITS_BEGIN
#endif

#ifdef SERIALIZE_STRUCT_TRAITS_MEMBER
#undef SERIALIZE_STRUCT_TRAITS_MEMBER
#endif

#ifdef SERIALIZE_STRUCT_BEGIN
#undef SERIALIZE_STRUCT_BEGIN
#define SERIALIZE_STRUCT_BEGIN SERIALIZE_STRUCT_TRAITS_BEGIN
#endif

#ifdef SERIALIZE_STRUCT_MEMBER
#undef SERIALIZE_STRUCT_MEMBER
#define SERIALIZE_STRUCT_MEMBER(type, name) SERIALIZE_STRUCT_TRAITS_MEMBER(name)
#endif

#ifdef SERIALIZE_STRUCT_TRAITS_END
#undef SERIALIZE_STRUCT_TRAITS_END
#define SERIALIZE_STRUCT_TRAITS_END() \
  return true; }
#endif

#ifdef SERIALIZE_STRUCT_END
#undef SERIALIZE_STRUCT_END
#define SERIALIZE_STRUCT_END SERIALIZE_STRUCT_TRAITS_END
#endif

#ifdef SERIALIZE_STRUCT_TRAITS_MEMBER_VALIDATE
#undef SERIALIZE_STRUCT_TRAITS_MEMBER_VALIDATE
#endif

#define SERIALIZE_STRUCT_TRAITS_BEGIN(struct_name) \
  bool JSON_SERIALIZE_TRAITS_NAME(struct_name)::FromJson(CxxJsonValue* json_value, struct_name* x) \
  { \
    bool __is_name_valid__ = false;\


#define  SERIALIZE_STRUCT_TRAITS_MEMBER_VALIDATE() \
  if (!__is_name_valid__) return false;

#define SERIALIZE_STRUCT_TRAITS_MEMBER(name) \
        {\
            __is_name_valid__ = json_value->Get(#name, &x->name);\
        }

#endif