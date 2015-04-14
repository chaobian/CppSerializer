# CppSerializer
C++ Serializer Library
Welcome!

Sample:


SERIALIZE_STRUCT_BEGIN(MyStruct2)
SERIALIZE_STRUCT_MEMBER(int, width)
SERIALIZE_STRUCT_MEMBER(int, height)
SERIALIZE_STRUCT_END()

typedef std::map<std::string, MyStruct2> MyStruct2Map;
typedef std::map<int, MyStruct2> IntMyStruct2Map;

SERIALIZE_STRUCT_BEGIN(MyStruct)
SERIALIZE_STRUCT_MEMBER(MyStruct2, wrapper)
SERIALIZE_STRUCT_MEMBER(std::list<int>, items)
SERIALIZE_STRUCT_MEMBER(MyStruct2Map, dicts)
SERIALIZE_STRUCT_MEMBER(IntMyStruct2Map, dicts2)
SERIALIZE_STRUCT_MEMBER(int, width)
SERIALIZE_STRUCT_MEMBER(int, height)
SERIALIZE_STRUCT_MEMBER(std::string, description)
SERIALIZE_STRUCT_MEMBER_REQUIRED(int, key)
SERIALIZE_STRUCT_END()

MyStruct v;
if (CxxJsonDeserialize(json, MyStruct, &v))
{
     printf("%s\r\n", v.description.c_str());
}
