#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <type_traits>
#include <cstdint>
#include <tuple>

/**
 * \brief Структуры для определения типа параметра при вызове функции
 */
namespace details {
    template<typename T>
    struct is_container: std::false_type{};

    template<typename T, typename Alloc>
    struct is_container<std::vector<T, Alloc>>:std::true_type{};

    template<typename T, typename Alloc>
    struct is_container<std::list<T, Alloc>>:std::true_type{};

    template<typename T>
    struct is_str: std::false_type{};
    template<>
    struct is_str<std::string>:std::true_type{};
    template<>
    struct is_str<const std::string>:std::true_type{};

    template<typename ... Args>
    struct is_one_type: std::true_type{};
    template<typename T, typename U, typename ... Args>
    struct is_one_type<T, U, Args...>: std::false_type{};
    template<typename T, typename ...Args>
    struct is_one_type<T, T, Args...>: is_one_type<T, Args...>{};

    template<typename T>
    struct is_tuple: std::false_type{};
    template<>
    struct is_tuple<std::tuple<>>: std::true_type{};
    template<typename T, typename ... Args>
    struct is_tuple<std::tuple<T, Args ...>>: is_one_type<T, Args...>{};
}

/**
 * @brief print_ip - Шаблонная функция печати условного IP-адреса для произвольного целочисленного типа
 * @tparam T - целочисленный тип
 * @param value - условный IP-адрес
 */
template <typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
void print_ip(T value)
{
    auto szT = sizeof(T);
    for(auto i = szT; i > 0 ; i--)
    {
        if(i != szT)
            std::cout << ".";
        std::cout << ((value >> (8*(i-1))) & 0xff);
    }
    std::cout << std::endl;
}

/**
 * @brief print_ip - Шаблонная функция печати условного IP-адреса для строки
 * @tparam T - строка
 * @param value - условный IP-адрес
 */
template <typename T, std::enable_if_t<details::is_str<T>::value, bool> = true>
void print_ip(T value)
{
    std::cout << value << std::endl;
}

/**
 * @brief print_ip - Шаблонная функция печати условного IP-адреса для контейнера
 * @tparam T - контейнер `std::list`, `std::vector`
 * @param value - условный IP-адрес
 */
template <class T, std::enable_if_t<details::is_container<T>::value, bool> = true>
void print_ip(T value)
{
    auto it = value.begin();
    std::cout << *it;
    it++;
    while(it != value.end())
    {
        std::cout << "." << *it;
        it++;
    }
    std::cout << std::endl;
}

/**
 * @brief print_ip - Шаблонная функция печати условного IP-адреса для `std::tuple`
 * @tparam T - `std::tuple`
 * @param value - условный IP-адрес
 */ate <class T, std::enable_if_t<details::is_tuple<T>::value, bool> = true>
void print_ip(T value)
{
    std::apply([](auto &&... args){((std::cout<<args<< '.'), ...);}, value);
    std::cout <<std::endl;
}
