/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pb.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kostya <kostya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:37:05 by kostya            #+#    #+#             */
/*   Updated: 2021/11/09 15:40:25 by kostya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>
#include "phbook.hpp"
#include "color.hpp"

namespace tlucanti
{
	bool isdigit(const std::string &str)
	{
		if (str.empty())
			return false;
		std::size_t i = 0;
		for (; i < str.size(); ++i)
		{
			if (not std::isspace(str[i]))
				break;
		}
		if (str[i] == '-' or str[i] == '+')
			++i;
		for (; i < str.size(); ++i)
			if (not std::isdigit(str[i]))
				return false;
		return true;
	}

	template <typename T>
	struct reversion_wrapper { T& iterable; };

	template <typename T>
	auto begin (reversion_wrapper<T> w) { return std::rbegin(w.iterable); }

	template <typename T>
	auto end (reversion_wrapper<T> w) { return std::rend(w.iterable); }

	template <typename T>
	reversion_wrapper<T> reverse (T&& iterable) { return { iterable }; }

	std::size_t hash(const std::string &str)
	{
		const std::size_t base = 127;
		const std::size_t mod = 4398042316799;
		std::size_t _hash = 0;
		
		for (unsigned char c : reverse(str))
			_hash = ((_hash * base) % mod + c) % mod;
		return (_hash);
	}

	constexpr std::size_t const_hash_req(const char *const str, std::size_t idx)
	{
		const std::size_t base = 127;
		const std::size_t mod = 4398042316799;

		if (str[idx] == 0)
			return 0;
		else
			return ((const_hash_req(str, idx + 1) * base) % mod
				+ static_cast<unsigned char>(str[idx])) % mod;
	}

	constexpr std::size_t const_hash(const char *const str)
	{
		return const_hash_req(str, 0);
	}
}

#define SWITCH(__string) switch(tlucanti::hash(__string))
#define CASE(__string) case (tlucanti::const_hash(__string))

int main()
{
	tlucanti::phbook<8> pb;
	std::cout
		<< "Portable Phone Book v1.0 "_green
		<< tlucanti::color::tlucanti << "[Tlucanti (C)]\n"_reset
		<< "Usage:\n"_white
		<< "  EXIT/exit/E/e"_blue << ": to quit program\n"_white
		<< "  ADD/add/A/a "_blue
		<< "[name] [last name] [nickname] [phone] [secret]"_purple
		<< ":\n"_white
		<< "    to add number to phone book (stores only "_white
		<< "last 8\n"_yellow
		<< "    contacts)\n"_white
		<< "  SEARCH/search/S/s "_green << "[index]"_purple
		<< ": to search contact by index\n"_white
		<< "    also print all availible contacts\n"_white
		<< "-----------------------------------------------------------"_white
		<< std::endl;

	while (true)
	{
		std::cout << " >> "_white;
		std::string line;
		getline(std::cin, line, '\n');
		std::stringstream ss;
		ss << line;
		std::string input;
		ss >> input;
		SWITCH(input)
		{
			CASE("EXIT"):
			CASE("exit"):
			CASE("E"):
			CASE("e"):
			{
				std::cout << "[ OK ]"_green << " exit "_white
					<< "successful"_yellow << std::endl;
				return 0;
			}
			CASE("ADD"):
			CASE("add"):
			CASE("A"):
			CASE("a"):
			{
				std::string fname;
				std::string lname;
				std::string nickname;
				unsigned long long phone = 0;
				std::string secret;
				ss >> fname >> lname >> nickname >> phone;
				if (fname.empty() or lname.empty() or nickname.empty() or phone == 0)
				{
					std::cout << "[FAIL] "_red << "wrong command format\n"_yellow;
					continue;
				}
				ss >> secret;
				pb.add(fname, lname, nickname, phone, secret);
				std::cout << "[ OK ]"_green << " contact added "_white
					<< "successfully\n"_yellow;
				break;
			}
			CASE("SEARCH"):
			CASE("search"):
			CASE("S"):
			CASE("s"):
			{
				std::string idx;
				ss >> idx;
				if (idx.empty())
					pb.search(-1);
				else if (not tlucanti::isdigit(idx))
					std::cout << "[FAIL] "_red << "wrong index format\n"_yellow;
				else
				{
					if (pb.search(std::stoi(idx)))
						std::cout << "[WARN] "_yellow
							<< "index out of phone book range\n"_white;
				}
				break;
			}
			CASE(""):
				continue;
			default:
			{
				std::cout << "[WARN]"_yellow
					<< " unexpected command (ignored)\n"_white;
				continue;
			}
		}
	}
}
