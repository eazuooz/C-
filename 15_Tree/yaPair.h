#pragma once
#include <iostream>


namespace ya
{
	template <typename T1, typename T2>
	class pair
	{
	public:
		pair() : first(T1()), second(T2())
		{

		}
		pair(T1& f, T2& s) : first(f), second(s)
		{

		}
		template <typename U1, typename U2>
		pair(U1&& f, U2&& s) : first(std::forward<U1>(f)), second(std::forward<U2>(s))
		{

		}
		template <typename U1, typename U2>
		pair(const pair<U1, U2>& other) : first(other.first), second(other.second)
		{

		}
		template <typename U1, typename U2>
		pair(const pair<U1, U2>&& other) : first(std::forward(other.first)), second(std::forward(other.second))
		{

		}
		~pair() = default;

	public:
		void swap(pair& other)
		{
			std::swap(first, other.first);
			std::swap(second, other.second);
		}

	public:
		pair& operator =(const pair& other)
		{
			first = other.first;
			second = other.second;
			return *this;
		}
		pair& operator =(pair&& other)
		{
			first = std::move(other.first);
			second = std::move(other.second);
			return *this;
		}
		template<typename U1, typename U2>
		pair& operator=(const pair<U1, U2>& other) {
			first = other.first;
			second = other.second;
			return *this;
		}
		template<typename U1, typename U2>
		pair& operator=(pair<U1, U2>&& other) {
			first = std::forward<T1>(other.first);
			second = std::forward<T2>(other.second);
			return *this;
		}

		inline bool operator==(const pair& other) const
		{
			return (first == other.first && second == other.second);
		}
		inline bool operator!=(const pair& other) const
		{
			return !(*this == other);
		}
		inline bool operator< (const pair& other) const
		{
			return (first < other.first || (first == other.first && second < other.second));
		}
		inline bool operator<=(const pair& other) const
		{
			return !(other < *this);
		}
		inline bool operator> (const pair& other) const
		{
			return (other < *this);
		}
		inline bool operator>=(const pair& other) const
		{
			return !(*this < other);
		}

	public:
		T1 first;
		T2 second;
	};





}