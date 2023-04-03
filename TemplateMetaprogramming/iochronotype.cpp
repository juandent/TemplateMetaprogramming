#include <cassert>
#include <locale>
#include <sstream>
#include <format>
#include <chrono>
#include <iostream>
#include <unordered_map>


namespace iochronotype
{
	void main()
	{
		using namespace std::literals;
		auto dur = 42.88ms;
		using namespace std::chrono;
		namespace chr = std::chrono;


		std::locale locCR{ "es-CR" };
		std::locale locG{ "en-US" };


		std::string s1 = std::format("{:%S}", dur);
		std::string s2 = std::format(locCR,"{:L%S}", dur);

		//std::locale::global(locCR);

		year_month_day date{ chr::floor<chr::days>(chr::system_clock::now()) };

		chr::sys_days sd = date;
		chr::sys_seconds ss = sd;
		ss += chr::seconds{ 40 };

		std::string s3 = std::format(locCR,"{:L%c}", ss);

		std::locale locMix{  locCR, locG,std::locale::numeric | std::locale::monetary };

		//std::locale::

		std::string s4 = std::format(locMix, "{:L%S}", dur);
		std::string s5 = std::format(locMix, "{:Lf}", 12345678.34);

	}

	void usingFromStream()
	{
		using namespace std::literals;

		std::chrono::sys_seconds tp;
		std::istringstream sstrm{ "2021-2-28 17:30:00" };

		std::chrono::from_stream(sstrm, "%F %T", tp);
		if(sstrm)
		{
			std::cout << "tp:  " << tp << "\n";
		}
		else
		{
			std::cout << "Error reading into tp failed\n";
		}

		std::chrono::year_month_day f = 2021y / 4 / 5;
		std::chrono::year_month_weekday wf{ f };
		auto wd= wf.weekday();
		std::chrono::year_month m;
		std::chrono::month mm;

		std::locale loc{ "es-CR" };
		//std::locale::global(loc);
		//std::istringstream  srm{ "Monday, April 5, 2021" };
		std::istringstream  srm{ "Jueves 15 Abril 2021" };
		srm.imbue(loc);
		std::chrono::from_stream(srm, "%A %t%e %B %Y", f);
		if(srm)
		{
			std::cout << f << "\n";
		}

		std::chrono::duration<long long, std::milli> dur{ 1200 };
#if 1
		std::istringstream  sm{ "1000ms" };
		//auto mil = 1000ms;

		auto str = std::format("{:%Q%q}", dur);

		std::chrono::from_stream(sm, "%q", dur);


		std::chrono::sys_time<std::chrono::seconds> sstt;
		std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds > ttpp;
		auto st = std::chrono::system_clock::now();
		st = sstt;
		auto sts = std::format("{:%F %T}", st);
		std::istringstream  s{ "1920-10-01 04:15:00.0000" };
		std::chrono::from_stream(s, "%F %T", sstt);
		if(s)
		{
			std::cout << sstt << "\n";
		}


		std::chrono::file_time<std::chrono::microseconds> ft;
		std::istringstream  s1{ "1920-10-01 04:15:00.0000" };
		std::chrono::from_stream(s1, "%F %T", ft);
		if (s1)
		{
			std::cout << ft << "\n";
		}


#endif
	}

	std::chrono::milliseconds parseDuration(std::istream& is) {
		using namespace std::chrono_literals;

		static const std::unordered_map<std::string, std::chrono::milliseconds> suffix{
			{"ms", 1ms}, {"s", 1s}, {"m", 1min}, {"h", 1h} };

		unsigned n{};
		std::string unit;

		if (is >> n >> unit) {
			try {
				return std::chrono::duration_cast<std::chrono::milliseconds>(n * suffix.at(unit));
			}
			catch (const std::out_of_range&) {
				std::cerr << "ERROR: Invalid unit specified\n";
			}
		}
		else
			std::cerr << "ERROR: Could not convert to numeric value\n";

		return {};
	}

	void useParseDuration() {
		std::istringstream sm{ "1234ms" };

		const auto dur{ parseDuration(sm) };

		std::cout << dur << '\n';

	}

	void useParseManip()
	{
		namespace chr = std::chrono;

		chr::sys_days tp;
		chr::hours h;
		chr::minutes m;

		std::istringstream{ "12/24/21 18:00" } >> chr::parse("%D", tp)
			>> chr::parse(" %H", h)
			>> chr::parse(":%M", m);

		std::cout << tp << " at " << h << ' ' << m << '\n';

	}

	void useParseTZ()
	{
		namespace chr = std::chrono;

		chr::local_seconds tp; // local time
		std::string tzAbbrev;
		std::istringstream sstrm{ "3032-4-13 12:00 CST" };
		chr::from_stream(sstrm, "%F %R %Z", tp, &tzAbbrev);
		std::cout << tp << '\n';
		std::cout << tzAbbrev << '\n';
		chr::zoned_time zt{ tzAbbrev, tp };
		std::cout << zt << '\n';
	}
	void useInvalid()
	{
		namespace chr = std::chrono;
		using namespace std::literals;
		using namespace std;

		auto ymd = 1999y / 3 / 31;
		chr::sys_days ymd_days = ymd;

		auto ymd2 = 2000y / 3 / 31;
		chr::sys_days ymd2_days = ymd2;

		auto dif = ymd2_days - ymd_days;

		std::cout << dif << "\n";

		//auto val = 2000y / 2/202

		auto next_month = ymd + chr::months{ 1 };
		chr::sys_days ymd_next = next_month;

		auto ddiff = ymd_next - ymd_days;

		auto next_13 = ymd + chr::months{ 13 };
		chr::sys_days next13_days = next_13;

		if(! next_13.ok())
		{
			next_13 = chr::sys_days{ next_13 };
		}

		// ymd += chr::months{ 13 };
		// if( ! ymd.ok())
		// {
		// 	ymd = chr::sys_days{ ymd };
		// }

		constexpr chr::year_month_day_last ymdl = 2000y / 2 / chr::last;
		constexpr auto ymdl1 = ymdl + chr::months{ 4 };

		constexpr chr::sys_days ymdl1_days = ymdl;
		std::cout << ymdl1_days << "\n";


		chr::sys_days days0 = 2020y / 12 / 31;
		auto days1 = days0 + chr::months{ 4 };	// expected: 2021y /4/31
		auto days2 = days0 + chr::years{ 4 };	// expected: 2024y /12/31

		std::cout << "date:  " << days0 << "\n";
		std::cout << "with time " << chr::sys_seconds{ days0 } << "\n";

		cout << " +4 months: " << days1 << "\n";
		cout << " +4 years: " << days2 << "\n";
		auto leap = 2024y / 2 / 29;
		if(! leap.ok())
		{
			leap = chr::sys_days{ leap };
		}

		{
			chr::sys_days days = 2024y / 2 / 29;

			auto days_4_months = days + chr::months{ 4 };

			chr::year_month_day days_4_ymd = chr::floor<chr::days>(days_4_months);

			chr::utc_time utcNow = chr::utc_clock::from_sys(days);

			auto sysNow = chr::utc_clock::to_sys(utcNow);

			auto comp = sysNow - days;

			assert(comp.count() == 0);

			chr::year_month_day sysYMD = days;

			auto ret = chr::get_leap_second_info(utcNow);


			auto utc_now = chr::utc_clock::now();
			auto now = chr::system_clock::now();
			auto utc_now_sys = chr::utc_clock::to_sys(utc_now);
			auto dif = now - utc_now_sys;

			std::ostringstream os;

			os << dif.count() << std::endl;

			chr::sys_days sdays = 2024y / 2 / 29;
			auto sdays_ = sdays + chr::months{ 2 };
			auto interval = sdays_.time_since_epoch();
			auto ssss = chr::duration_cast<chr::seconds>(interval);

//			chr::duration<long long, chr::seconds> dd = (sdays_*1ms); // HERE!!
	//		decltype(sdays_)* pp;


			{
				auto now = chr::system_clock::now();
				auto now_interval = now.time_since_epoch();
				auto now_seconds = chr::duration_cast<chr::seconds>(now_interval);
				auto future = now + chr::months{ 2 };
				auto interval = future.time_since_epoch();
				auto seconds = chr::duration_cast<chr::seconds>(interval);
				auto diff = seconds - now_seconds;

				auto min = diff.count() / 60.0;
				auto hrs = min / 60.0;
				auto days = hrs / 24.0;


				auto _2months =chr::months{ 2 }.count();
				auto _2 = chr::months{ 2 };
				auto secs = chr::duration_cast<chr::seconds>(_2);
				std::cout << chr::months{2} << "\n";

				int i = 0;
			}
			
			{
				auto now = chr::system_clock::now();
				auto future = now + chr::months{ 2 };
				auto interval = future - now;
				auto seconds = chr::duration_cast<chr::seconds>(interval);


				auto min = seconds.count() / 60.0;
				auto hrs = min / 60.0;
				auto days = hrs / 24.0;
				
				bool match = days == 60.873750000000001;


				auto _2months = chr::months{ 2 }.count();
				auto _2 = chr::months{ 2 };
				auto secs = chr::duration_cast<chr::seconds>(_2);
				std::cout << chr::months{ 2 } << "\n";

				int i = 0;
			}




			int i = 0;
		}
		auto feb29 = chr::month{ 2 } / 29;
		if( ! feb29.ok())
		{
			int i = 0;
			//feb29 = chr::sys_days{ feb29 };
		}
	}
}
