#ifndef CLASSIC_SINGLETON_H
#define CLASSIC_SINGLETON_H
#include <string>
#include <mutex>

namespace classic_singleton
{
	using String = std::string;

	class Singleton
	{
	private:
		Singleton() = default;
		~Singleton() = default;

	public:
		Singleton(const Singleton &) = delete;
		Singleton &operator=(const Singleton &) = delete;

		static Singleton *get_instance()
		{
			static std::once_flag init_instance_flag;
			static Singleton *unique_instance;
			std::call_once(init_instance_flag, [&]()
						   { unique_instance = new Singleton(); });

			return unique_instance;
		}

		// other useful methods here

		String get_description()
		{
			return "I'm a classic Singleton!";
		}
	};
}
#endif // !CLASSIC_SINGLETON_H