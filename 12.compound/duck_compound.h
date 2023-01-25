#ifndef DUCK_COMPOUND_H
#define DUCK_COMPOUND_H
#include <string>
#include <memory>
#include <vector>
#include <sstream>

namespace duck_compound
{
	using String = std::string;

	int QuackCounter::m_number_of_quacks = 0;

	class IObserver
	{
	public:
		virtual String update(std::shared_ptr<IQuackObservable> p_duck) = 0;
	};

	class IQuackable
	{
	public:
		virtual String quack() = 0;
	};

	class IQuackObservable
	{
	public:
		virtual void register_observer(std::shared_ptr<IObserver> p_observer) = 0;
		virtual String notify_observers() = 0;
	};

	class AbstractDuckFactory
	{
	public:
		virtual std::shared_ptr<IQuackable> create_mallard_duck() = 0;
		virtual std::shared_ptr<IQuackable> create_redhead_duck() = 0;
		virtual std::shared_ptr<IQuackable> create_duck_call() = 0;
		virtual std::shared_ptr<IQuackable> create_rubber_duck() = 0;
	};

	class DuckCall : public IQuackable, IQuackObservable
	{
	public:
		DuckCall() : m_observable(this) {}

		String quack() override
		{
			notify_observers();
			return "Kwak";
		}

		void register_observer(std::shared_ptr<IObserver> p_observer) override
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers() override
		{
			return m_observable->notify_observers();
		}

	private:
		IQuackObservable *m_observable;
	};

	class Flock : public IQuackable, IQuackObservable
	{
	public:
		Flock() : m_observable(this) {}

		void add(std::shared_ptr<IQuackable> p_quacker)
		{
			quackers.push_back(p_quacker);
		}

		String quack() override
		{
			std::ostringstream oss;
			for (std::shared_ptr<IQuackable> quacker : quackers)
			{
				oss << quacker->quack() << "\n";
				oss << notify_observers();
			}

			return oss.str();
		}

		void register_observer(std::shared_ptr<IObserver> p_observer) override
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers() override
		{
			return m_observable->notify_observers();
		}

	private:
		std::vector<std::shared_ptr<IQuackable>> quackers;
		IQuackObservable *m_observable;
	};

	class Goose
	{
	public:
		Goose() {}
		String honk() { return "Honk"; }
	};

	class GooseAdapter : public IQuackable, IQuackObservable
	{
	public:
		GooseAdapter(std::shared_ptr<Goose> p_goose) : m_goose(p_goose), m_observable(this) {}

		String quack() override
		{
			notify_observers();
			return m_goose->honk();
		}

		void register_observer(std::shared_ptr<IObserver> p_observer) override
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers() override
		{
			return m_observable->notify_observers();
		}

	private:
		std::shared_ptr<Goose> m_goose;
		IQuackObservable *m_observable;
	};

	class MallardDuck : public IQuackable, IQuackObservable
	{
	public:
		MallardDuck() : m_observable(this) {}

		String quack() override
		{
			notify_observers();
			return "Quack";
		}

		void register_observer(std::shared_ptr<IObserver> p_observer) override
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers() override
		{
			return m_observable->notify_observers();
		}

	private:
		IQuackObservable *m_observable;
	};

	class Observable : public IQuackObservable
	{
	public:
		Observable(std::shared_ptr<IQuackObservable> p_duck) : m_duck(p_duck) {}

		void register_observer(std::shared_ptr<IObserver> p_observer) override
		{
			m_observers.push_back(p_observer);
		}

		String notify_observers() override
		{
			std::ostringstream oss;
			for (std::shared_ptr<IObserver> p_observer : m_observers)
			{
				oss << p_observer->update(m_duck);
				oss << "\n";
			}

			return oss.str();
		}

	private:
		std::vector<std::shared_ptr<IObserver>> m_observers;
		std::shared_ptr<IQuackObservable> m_duck;
	};

	class QuackCounter : public IQuackable, IQuackObservable
	{
	public:
		QuackCounter(std::shared_ptr<IQuackable> p_duck) : m_duck(p_duck), m_observable(this) {}

		String quack() override
		{
			notify_observers();
			++m_number_of_quacks;
			return m_duck->quack();
		}

		void register_observer(std::shared_ptr<IObserver> p_observer) override
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers() override
		{
			return m_observable->notify_observers();
		}

		static int get_quack_count() { return m_number_of_quacks; }

	private:
		std::shared_ptr<IQuackable> m_duck;
		static int m_number_of_quacks;
		IQuackObservable *m_observable;
	};

	class Quackologist : public IObserver
	{
	public:
		Quackologist() {}

		String update(std::shared_ptr<IQuackObservable> p_duck) override
		{
			return "Quackologist: the p_duck just quacked";
		}
	};

	class RedheadDuck : public IQuackable, IQuackObservable
	{
	public:
		RedheadDuck() : m_observable(this) {}

		String quack() override
		{
			notify_observers();
			return "Quack";
		}

		void register_observer(std::shared_ptr<IObserver> p_observer) override
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers() override
		{
			return m_observable->notify_observers();
		}

	private:
		IQuackObservable *m_observable;
	};

	class RubberDuck : public IQuackable, IQuackObservable
	{
	public:
		RubberDuck() : m_observable(this) {}

		String quack() override
		{
			notify_observers();
			return "Squeak";
		}

		void register_observer(std::shared_ptr<IObserver> p_observer) override
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers() override
		{
			return m_observable->notify_observers();
		}

	private:
		IQuackObservable *m_observable;
	};

	class CountingDuckFactory : public AbstractDuckFactory
	{
	public:
		std::shared_ptr<IQuackable> create_mallard_duck() override
		{
			return std::make_shared<QuackCounter>(std::make_shared<MallardDuck>());
		}

		std::shared_ptr<IQuackable> create_redhead_duck() override
		{
			return std::make_shared<QuackCounter>(std::make_shared<RedheadDuck>());
		}

		std::shared_ptr<IQuackable> create_duck_call() override
		{
			return std::make_shared<QuackCounter>(std::make_shared<DuckCall>());
		}

		std::shared_ptr<IQuackable> create_rubber_duck() override
		{
			return std::make_shared<QuackCounter>(std::make_shared<RubberDuck>());
		}
	};
}
#endif // !DUCK_COMPOUND_H