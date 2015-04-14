#ifndef ____CPP_SERIALIZER_DEF_H__
#define ____CPP_SERIALIZER_DEF_H__

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

#define  SERIALIZE_STRUCT_TRAITS_MEMBER_VALIDATE() 

#define SERIALIZE_STRUCT_TRAITS_MEMBER_REQUIRED(name) \
  SERIALIZE_STRUCT_TRAITS_MEMBER(name) \
  SERIALIZE_STRUCT_TRAITS_MEMBER_VALIDATE()

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
  SERIALIZE_STRUCT_TRAITS_MEMBER_VALIDATE()

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