#ifndef DUCK_COMPOUND_H
#define DUCK_COMPOUND_H
#include <string>
#include <memory>
#include <vector>

namespace duck_compound
{
	using String = std::string;
	class IObserver
	{
	public:
		String update(std::shared_ptr<IQuackObservable> p_duck);
	};

	class IQuackable
	{
	public:
		String quack();
	};

	class IQuackObservable
	{
	public:
		void register_observer(std::shared_ptr<IObserver> observer);
		String notify_observers();
	};

	class AbstractDuckFactory
	{
	public:
		virtual std::shared_ptr<IQuackable> create_mallard_duck() = 0;
		virtual std::shared_ptr<IQuackable> create_redhead_duck() = 0;
		virtual std::shared_ptr<IQuackable> create_duck_call() = 0;
		virtual std::shared_ptr<IQuackable> create_rubber_duck() = 0;
	};

	class CountingDuckFactory : AbstractDuckFactory
	{
	public:
		CountingDuckFactory() {}
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

	class DuckCall : IQuackable, IQuackObservable
	{
	public:
		DuckCall() : m_observable(std::make_shared<IObserver>(this)) {}

		String quack()
		{
			notify_observers();
			return "Kwak";
		}

		void register_observer(std::shared_ptr<IObserver> observer)
		{
			m_observable->register_observer(observer);
		}

		String notify_observers() { return m_observable->notify_observers(); }

	private:
		std::shared_ptr<IObserver> m_observable;
	};

	class Flock : IQuackable, IQuackObservable
	{
	public:
		Flock()
		{
			m_observable = std::make_shared<IObserver>(this);
		}

		void add(IQuackable p_quacker)
		{
			quackers->add(p_quacker);
		}

		String quack()
		{
			StringBuilder sb = new StringBuilder();

			foreach (IQuackable quacker in quackers)
			{
				sb->Append(quacker->quack());
				sb->Append("\n");
				sb->Append(notify_observers());
			}

			return sb->ToString();
		}

		void register_observer(std::shared_ptr<IObserver> p_observer)
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers()
		{
			return m_observable->notify_observers();
		}

	private:
		std::vector<IQuackable> quackers;
		std::shared_ptr<IObserver> m_observable;
	};

	class Goose
	{
	public:
		Goose() {}
		String honk() { return "Honk"; }
	};

	class GooseAdapter : IQuackable, IQuackObservable
	{
	public:
		GooseAdapter(std::shared_ptr<Goose> p_goose) : m_goose(p_goose), m_observable(std::make_shared<IObserver>(this)) {}

		String quack()
		{
			notify_observers();
			return m_goose->honk();
		}

		void register_observer(std::shared_ptr<IObserver> p_observer)
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers()
		{
			return m_observable->notify_observers();
		}

	private:
		std::shared_ptr<Goose> m_goose;
		std::shared_ptr<IObserver> m_observable;
	};

	class MallardDuck : IQuackable, IQuackObservable
	{
	public:
		MallardDuck()
		{
			m_observable = std::make_shared<IObserver>(this);
		}

		String quack()
		{
			notify_observers();
			return "Quack";
		}

		void register_observer(std::shared_ptr<IObserver> p_observer)
		{
			m_observable->register_observer(p_observer);
		}

		String notify_observers()
		{
			return m_observable->notify_observers();
		}

	private:
		std::shared_ptr<IObserver> m_observable;
	};

	class Observable : IQuackObservable
	{
	public:
		Observable(std::shared_ptr<IQuackObservable> p_duck)
		{
			m_duck = p_duck;
		}

		void register_observer(std::shared_ptr<IObserver> p_observer)
		{
			m_observers->add(p_observer);
		}

		String notify_observers()
		{
			StringBuilder sb = new StringBuilder();
			for (std::shared_ptr<IObserver> observer in m_observers)
			{
				sb->Append(observer->update(m_duck));
				sb->Append("\n");
			}

			return sb->ToString();
		}

	private:
		std::vector<IObserver> m_observers;
		std::shared_ptr<IQuackObservable> m_duck;
	};

	class QuackCounter : IQuackable, IQuackObservable
	{
	public:
		static int get_quack_count() { return m_number_of_quacks + 1; }
		static int get_quack_count(int p_number_of_quacks) { m_number_of_quacks = p_number_of_quacks; }
		QuackCounter(IQuackable m_duck)
		{
			m_duck = m_duck;
			m_observable = std::make_shared<IObserver>(this);
		}

		String quack()
		{
			notify_observers();
			m_number_of_quacks++;
			return m_duck->quack();
		}

		void register_observer(std::shared_ptr<IObserver> observer)
		{
			m_observable->register_observer(observer);
		}

		String notify_observers()
		{
			return m_observable->notify_observers();
		}

	private:
		std::shared_ptr<IQuackable> m_duck;
		static int m_number_of_quacks;
		std::shared_ptr<IObserver> m_observable;
	};

	class Quackologist : IObserver
	{
	public:
		Quackologist() {}

		String update(std::shared_ptr<IQuackObservable> p_duck)
		{
			return "Quackologist: the " + p_duck->GetType()->Name + " just quacked";
		}
	};

	class RedheadDuck : IQuackable, IQuackObservable
	{
	public:
		RedheadDuck()
		{
			m_observable = std::make_shared<IObserver>(this);
		}

		String quack()
		{
			notify_observers();
			return "Quack";
		}

		void register_observer(IObserver observer)
		{
			m_observable->register_observer(observer);
		}

		String notify_observers()
		{
			return m_observable->notify_observers();
		}

	private:
		std::shared_ptr<IObserver> m_observable;
	};

	class RubberDuck : IQuackable, IQuackObservable
	{
	public:
		RubberDuck()
		{
			m_observable = std::make_shared<IObserver>(this);
		}

		String quack()
		{
			notify_observers();
			return "Squeak";
		}

		void register_observer(IObserver observer)
		{
			m_observable->register_observer(observer);
		}

		String notify_observers()
		{
			return m_observable->notify_observers();
		}

	private:
		std::shared_ptr<IObserver> m_observable;
	};

}
#endif // !DUCK_COMPOUND_H