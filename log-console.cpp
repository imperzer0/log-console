//
// Created by imper on 7/16/21.
//

#include "log-console"

log_console::log_console(int output_stream_socket) : output_stream(::fdopen(output_stream_socket, "wb"))
{ }

log_console::log_console(FILE* output_stream) : output_stream(output_stream)
{ }

const std::pair<log_console&, std::true_type>& log_console::operator<<(const std::remove_cvref_t<decltype(l_location)>& location)
{
	print(
			(this->location ? std::string() : std::string("\n")) + color_l_location + location.first
			+ color_l_location_separator + "::" + color_l_location + location.second.first
			+ color_l_location_separator + "::" + color_l_location + std::to_string(location.second.second)
			+ color::reset + "\n+-->"
	);
	this->time = false;
	this->location = true;
	return *new std::remove_cvref_t<decltype(operator<<(l_location))>{*this, std::true_type()};
}

const std::pair<log_console&, std::true_type>& log_console::operator<<(const std::remove_cvref_t<decltype(l_time)>& time)
{
	print(
			(this->time ? std::string() : std::string("\n")) + color_l_time + time.first
			+ color_l_time_separator + "::" + color_l_time + time.second
			+ color::reset + "\t"
	);
	this->time = true;
	this->location = false;
	return *new std::remove_cvref_t<decltype(operator<<(l_time))>{*this, std::true_type()};
}

log_console& log_console::operator<<(const std::string& str)
{
	print(str);
	this->time = false;
	this->location = false;
	return *this;
}

log_console& log_console::operator<<(const char* str)
{
	print(str);
	this->time = false;
	this->location = false;
	return *this;
}

log_console& log_console::operator<<(bool boolean)
{
	print((boolean ? std::string(color_bool_true) + " true" : std::string(color_bool_false) + " false") + color::reset);
	this->time = false;
	this->location = false;
	return *this;
}

template <typename type>
enable_if_t<std::is_floating_point_v<type>, log_console&> log_console::operator<<(type num)
{
	print(color_float_t + std::string(" ") + std::to_string(num) + color::reset);
	this->time = false;
	this->location = false;
	return *this;
}

template <typename type>
enable_if_t<std::is_integral_v<type>, log_console&> log_console::operator<<(type num)
{
	print(color_int_t + std::string(" ") + std::to_string(num) + color::reset);
	this->time = false;
	this->location = false;
	return *this;
}

log_console::~log_console()
{
	::fclose(output_stream);
}

void log_console::print(const std::string& str) const
{
	::fwrite(str.c_str(), sizeof(char), str.size(), output_stream);
}

struct termios* log_console::stdin_defaults = nullptr;
struct termios* log_console::stdout_defaults = nullptr;
struct termios* log_console::stderr_defaults = nullptr;

void log_console::setting_stdin()
{
	if (log_console::stdin_defaults == nullptr)
	{
		log_console::stdin_defaults = new termios;
	}
	::tcgetattr(0, log_console::stdin_defaults);
	struct termios settings = *log_console::stdin_defaults;
	settings.c_lflag &= (~ICANON);
	settings.c_lflag &= (~ECHO);
	settings.c_cc[VTIME] = 0;
	settings.c_cc[VMIN] = 1;
	::tcsetattr(0, TCSANOW, &settings);
}

void log_console::setting_stdout()
{
	if (log_console::stdout_defaults == nullptr)
	{
		log_console::stdout_defaults = new termios;
	}
	::tcgetattr(1, log_console::stdout_defaults);
	struct termios settings = *log_console::stdout_defaults;
	settings.c_lflag &= (~ICANON);
	settings.c_lflag &= (~ECHO);
	settings.c_cc[VTIME] = 0;
	settings.c_cc[VMIN] = 1;
	::tcsetattr(1, TCSANOW, &settings);
}

void log_console::setting_stderr()
{
	if (log_console::stderr_defaults == nullptr)
	{
		log_console::stderr_defaults = new termios;
	}
	::tcgetattr(2, log_console::stderr_defaults);
	struct termios settings = *log_console::stderr_defaults;
	settings.c_lflag &= (~ICANON);
	settings.c_lflag &= (~ECHO);
	settings.c_cc[VTIME] = 0;
	settings.c_cc[VMIN] = 1;
	::tcsetattr(2, TCSANOW, &settings);
}

void log_console::reset_all()
{
	if (log_console::stdin_defaults != nullptr)
	{
		::tcsetattr(0, TCSANOW, log_console::stdin_defaults);
		log_console::stdin_defaults = nullptr;
	}
	
	if (log_console::stdout_defaults != nullptr)
	{
		::tcsetattr(1, TCSANOW, log_console::stdout_defaults);
		log_console::stdout_defaults = nullptr;
	}
	
	if (log_console::stderr_defaults != nullptr)
	{
		::tcsetattr(1, TCSANOW, log_console::stderr_defaults);
		log_console::stderr_defaults = nullptr;
	}
}

// static operators

inline const std::pair<log_console&, std::true_type>& operator<<(const std::pair<log_console&, std::true_type>& logger, const std::string& str)
{
	std::string copy;
	for (char i : str)
	{
		copy += i;
		if (i == '\n')
		{
			copy += "+-->";
		}
	}
	logger.first.print(copy);
	logger.first.time = false;
	logger.first.location = false;
	return logger;
}

const std::pair<log_console&, std::true_type>& operator<<(const std::pair<log_console&, std::true_type>& logger, const char* str)
{
	std::string copy;
	for (; *str; ++str)
	{
		copy += *str;
		if (*str == '\n')
		{
			copy += "+-->";
		}
	}
	logger.first.print(copy);
	logger.first.time = false;
	logger.first.location = false;
	return logger;
}

inline const std::pair<log_console&, std::true_type>& operator<<(const std::pair<log_console&, std::true_type>& logger, const decltype(l_location)& location)
{
	logger.first.print(
			(logger.first.time ? std::string() : std::string("\n")) + log_console::color_l_location + location.first
			+ log_console::color_l_location_separator + "::" + log_console::color_l_location + location.second.first + "()"
			+ log_console::color_l_location_separator + "::" + log_console::color_l_location + std::to_string(location.second.second)
			+ color::reset + "\n+-->"
	);
	logger.first.time = false;
	logger.first.location = true;
	return logger;
}

inline log_console& operator<<(const std::pair<log_console&, std::true_type>& logger, const decltype(l_time)& time)
{
	logger.first.print(
			(logger.first.location ? std::string() : std::string("\n")) + log_console::color_l_time + time.first
			+ log_console::color_l_time_separator + "  " + log_console::color_l_time + time.second
			+ color::reset + "\t"
	);
	logger.first.time = true;
	logger.first.location = false;
	return logger.first;
}

inline const std::pair<log_console&, std::true_type>& operator<<(const std::pair<log_console&, std::true_type>& logger, bool boolean)
{
	logger.first.print((boolean ? std::string(log_console::color_bool_true) + " true" : std::string(log_console::color_bool_false) + " false") + color::reset);
	logger.first.time = false;
	logger.first.location = false;
	return logger;
}

template <typename type>
inline enable_if_t<std::is_integral_v<type>, const std::pair<log_console&, std::true_type>&> operator<<(const std::pair<log_console&, std::true_type>& logger, type num)
{
	logger.first.print(log_console::color_int_t + std::string(" ") + std::to_string(num) + color::reset);
	logger.first.time = false;
	logger.first.location = false;
	return logger;
}

template <typename type>
inline enable_if_t<std::is_floating_point_v<type>, const std::pair<log_console&, std::true_type>&> operator<<(const std::pair<log_console&, std::true_type>& logger, type num)
{
	logger.first.print(log_console::color_float_t + std::string(" ") + std::to_string(num) + color::reset);
	logger.first.time = false;
	logger.first.location = false;
	return logger;
}