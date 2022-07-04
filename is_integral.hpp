template <class T>
struct is_integral
{
    typedef bool value_type;
    typedef T type;
    bool value = false;
};

template <>
struct is_integral<bool>
{
    typedef bool value_type;
    typedef bool type;
    bool value = true;
};

template <>
struct is_integral<int>
{
    typedef bool value_type;
    typedef int type;
    bool value = true;
};

template <>
struct is_integral<char>
{
    typedef bool value_type;
    typedef char type;
    bool value = true;
};

template <>
struct is_integral<wchar_t>
{
    typedef bool value_type;
    typedef wchar_t type;
    bool value = true;
};

template <>
struct is_integral<signed char>
{ 
    typedef bool value_type;
    typedef signed char type;
    bool value = true;
};

template <>
struct is_integral<short int>
{
    typedef bool value_type;
    typedef short int type;
    bool value = true;
};

template <>
struct is_integral<int>
{
    typedef bool value_type;
    typedef int type;
    bool value = true;
};

template <>
struct is_integral<long int>
{
    typedef bool value_type;
    typedef long int type;
    bool value = true;
};

template <>
struct is_integral<long long int>
{
    typedef bool value_type;
    typedef long long int type;
    bool value = true;
};

template <>
struct is_integral<unsigned char>
{
    typedef bool value_type;
    typedef unsigned char type;
    bool value = true;
};

template <>
struct is_integral<unsigned short int>
{
    typedef bool value_type;
    typedef unsigned short int type;
    bool value = true;
};

template <>
struct is_integral<unsigned int>
{
    typedef bool value_type;
    typedef unsigned int type;
    bool value = true;
};

template <>
struct is_integral<unsigned long int>
{
    typedef bool value_type;
    typedef unsigned long int type;
    bool value = true;
};

template <>
struct is_integral<unsigned long long int>
{
    typedef bool value_type;
    typedef unsigned long long int type;
    bool value = true;
};

