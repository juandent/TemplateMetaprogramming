

#include <iostream>
#include <locale>
#include <format>


namespace locale_experimenting
{
	class CostarricanBoolNames : public std::numpunct_byname<char>	
	{
	public:
		CostarricanBoolNames(const std::string& name) : std::numpunct_byname<char>(name) {}

	protected:
		std::string do_truename() const override
		{
			return "verdadero";
		}
		std::string do_falsename() const override
		{
			return "falso";
		}
		std::string do_grouping() const override
		{
			return ",";
		}
	};

	class CostarricanMoney : public std::moneypunct_byname<char>
	{
	public:
		CostarricanMoney(const std::string& name) : std::moneypunct_byname<char>(name) {}

	protected:
		std::string do_curr_symbol() const override
		{
			return "¢";
		}
		char do_decimal_point() const override
		{
			return '.';
		}
		char do_thousands_sep() const override
		{
			return ',';
		}
	
	};

	void main()
	{
		std::locale locMoney{ std::cin.getloc(), new CostarricanMoney{"en_us"}};
		std::cout << std::format(locMoney, "{0:f} {0:Lf}", 3400.77);

		//std::parse

		constexpr auto*  fmt = "{}";
		std::format(fmt, 50);
	}
}


#if 0

namespace 
{
	// to deal with unneeded positive sign!!
	class costaRicaNumPunct : public std::moneypunct_byname<char>
	{
	public:
		explicit costaRicaNumPunct(const std::string& name)
			: std::moneypunct_byname<char>("en-US")      ///   "sp-CR")
		{}
	protected:
		virtual std::string do_positive_sign() const override {
			return "";
		}
		virtual std::string do_curr_symbol() const override {
			return "¢";
		}
		virtual int do_frac_digits() const override
		{
			return 2;
		}
		virtual char_type do_thousands_sep() const override {
			return ',';
		}
		virtual char_type do_decimal_point() const override {
			return '.';
		}
	};

#define PLAYING_WITH_LOCALES
#include <sstream>
	using namespace ::std;

	struct MoneytaryHelper
	{
	private:
		costaRicaNumPunct* m_posSignEliminator;
		locale m_usLoc;
		locale m_crLoc;
		ostringstream m_usOs;
		ostringstream m_crOs;
		istringstream m_usIs;
		istringstream m_crIs;

		const money_put<char>& m_usMoney_put;
		const money_put<char>& m_crMoney_put;

		const num_put<char>& m_usNumber_put;
		const num_put<char>& m_crNumber_put;
	public:
		MoneytaryHelper()
			: m_posSignEliminator{ new costaRicaNumPunct{ "" } },
#ifndef PLAYING_WITH_LOCALES
			m_usLoc{ "en-US" }, m_crLoc{ locale{"sp-ES"}.combine<numpunct<char>>(locale{"sp-CR"}), //, m_posSignEliminator
			},
#else
			m_usLoc{ "en-US" }, m_crLoc{ m_usLoc, m_posSignEliminator },
#endif
			m_usMoney_put{ use_facet<money_put<char>>(m_usLoc) }, m_crMoney_put{ use_facet<money_put<char>>(m_crLoc) },
			m_usNumber_put{ use_facet<num_put<char>>(m_usLoc) }, m_crNumber_put{ use_facet<num_put<char>>(m_crLoc) }
		{
			m_usOs << showbase;
			m_usOs.imbue(m_usLoc);

			m_crOs << showbase;
			m_crOs.imbue(m_crLoc);

			m_usIs.imbue(m_usLoc);
			m_crIs.imbue(m_crLoc);


#ifdef PLAYING_WITH_LOCALES
			//m_crLoc = m_crLoc.combine<numpunct<char>>(locale{"sp-ES"});
			//m_crOs.imbue(m_crLoc);
			//m_crIs.imbue(m_crLoc);
#endif
		}
		string putNumberAsCR(Money money, int width)
		{
			m_crOs.str("");
			m_crOs << right << setw(width);
			auto value = money.rep() / (long double)money.scale_;
			m_crNumber_put.put(m_crOs, m_crIs, ' ', value);
			auto temp = m_crOs.str();
			return temp;
		}
		string putColones(Money money, int width)
		{
			m_crOs.str("");
			m_crOs << right << setw(width);
#if 0	// plain
			auto temp = std::to_string(money.getAsLongDouble());
#else
			m_crMoney_put.put(m_crOs, false, m_crOs, ' ', 100 * money.getAsLongDouble()); //   money.rep()
			auto temp = m_crOs.str();
#endif
			return temp;
		}
		string putDollars(Money money, int width)
		{
			m_usOs.str("");
			m_usOs << right << setw(width);
#if 0 // plain
			auto temp = std::to_string(money.getAsLongDouble());
#else
			m_usMoney_put.put(m_usOs, false, m_usOs, ' ', 100 * money.getAsLongDouble());	// money.rep());
			auto temp = m_usOs.str();
#endif
			return temp;
		}
		Money getColones(const std::string& asColones)
		{
			m_crIs.str(asColones);
			auto readVal = 0.0L;
			m_crIs >> get_money(readVal);
			return Money(readVal);
		}
		Money getDollars(const std::string& asDollars)
		{
			m_crIs.str(asDollars);
			auto readVal = 0.0L;
			m_crIs >> get_money(readVal);
			return Money(readVal);
		}
	};
}

#endif
