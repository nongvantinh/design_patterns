#ifndef VACATION_BUILDER_H
#define VACATION_BUILDER_H
#include <string>
#include <memory>
#include <vector>
#include <sstream>

namespace vacation_builder
{
	using String = std::string;

	class Reservation
	{
	public:
		void set_arrival_date(int p_year, int p_month, int p_day)
		{
			m_arrival_date = std::to_string(p_year) + std::to_string(p_month) + std::to_string(p_day);
		}

		String arrival_date() { return m_arrival_date; }
		void set_nights(int p_nights) { m_nights = p_nights; }
		int nights() { return m_nights; }

	private:
		String m_arrival_date;
		int m_nights;
	};

	class Accommodation
	{
	public:
		void set_reservation(std::shared_ptr<Reservation> p_reservation) { m_reservation = p_reservation; }
		std::shared_ptr<Reservation> reservation() { return m_reservation; }
		virtual String location() = 0;
		String to_string()
		{
			std::ostringstream display;
			display << "You're staying at " << m_name;
			if (m_reservation != nullptr)
			{
				display << "\nYou have a reservation for arrival date: " << m_reservation->arrival_date() << ", staying for " << m_reservation->nights() << " m_nights";
			}
			if (location() != "")
			{
				display << " in " << location();
			}
			display << "\n";
			return display.str();
		}

	protected:
		String m_name;
		std::shared_ptr<Reservation> m_reservation;
	};

	class Hotel : public Accommodation
	{
	public:
		Hotel() { m_name = "Hotel"; }
		Hotel(String p_name) { m_name = p_name; }
		void set_room_number(int p_site_number) { m_room_number = p_site_number; }

		int room_number() { return m_room_number; }

		String location() override
		{
			if (m_room_number == 0)
				return "";
			else
				return "Room number " + m_room_number;
		}

	private:
		int m_room_number;
	};

	class Tent : public Accommodation
	{
	public:
		Tent() { m_name = "Tent"; }
		Tent(String p_name) { m_name = p_name; }
		void set_site_number(int p_site_number) { m_site_number = p_site_number; }
		int site_number() { return m_site_number; }
		String location() override
		{
			if (m_site_number == 0)
				return "";
			else
				return "Site number " + m_site_number;
		}

	private:
		int m_site_number;
	};

	class Vacation
	{
	public:
		void set_name(String p_name) { m_name = p_name; }
		void set_accommodations(std::vector<std::shared_ptr<Accommodation>> m_accommodations) { m_accommodations = m_accommodations; }
		void set_events(std::vector<String> p_events) { m_events = p_events; }

		String to_string()
		{
			std::ostringstream display;
			display << "---- " + m_name + " ----\n";
			for (std::shared_ptr<Accommodation> a : m_accommodations)
			{
				display << a;
			}
			for (String e : m_events)
			{
				display << e + "\n";
			}
			return display.str();
		}

	private:
		String m_name;
		std::vector<std::shared_ptr<Accommodation>> m_accommodations;
		std::vector<String> m_events;
	};

	class VacationBuilder
	{
	public:
		virtual VacationBuilder *add_accommodation() = 0;
		virtual VacationBuilder *add_accommodation(String p_name) = 0;
		virtual VacationBuilder *add_accommodation(String p_name, int p_year, int p_month, int p_day, int p_nights, int p_location) = 0;
		virtual VacationBuilder *add_event(String p_event) = 0;

		std::shared_ptr<Vacation> get_vacation()
		{
			std::shared_ptr<Vacation> vacation = std::make_shared<Vacation>();
			vacation->set_name(m_name);
			vacation->set_accommodations(m_accommodations);
			vacation->set_events(m_events);
			return vacation;
		}

	protected:
		String m_name;
		std::vector<std::shared_ptr<Accommodation>> m_accommodations;
		std::vector<String> m_events;
	};

	class OutdoorsVacationBuilder : public VacationBuilder
	{
	public:
		OutdoorsVacationBuilder() { m_name = "Outdoorsy Vacation Builder"; }
		VacationBuilder *add_accommodation() override
		{
			m_accommodations.push_back(std::make_shared<Tent>());
			return this;
		}

		VacationBuilder *add_accommodation(String p_name) override
		{
			m_accommodations.push_back(std::make_shared<Tent>(p_name));
			return this;
		}

		VacationBuilder *add_accommodation(String p_name, int year, int month, int day, int m_nights, int location) override
		{
			std::shared_ptr<Reservation> m_reservation = std::make_shared<Reservation>();
			m_reservation->set_arrival_date(year, month, day);
			m_reservation->set_nights(m_nights);

			std::shared_ptr<Tent> tent = std::make_shared<Tent>(p_name);
			tent->set_reservation(m_reservation);
			tent->set_site_number(location);
			m_accommodations.push_back(tent);
			return this;
		}

		VacationBuilder *add_event(String p_event) override
		{
			m_events.push_back("Hike: " + p_event);
			return this;
		}
	};

	class CityVacationBuilder : public VacationBuilder
	{
	public:
		CityVacationBuilder() { m_name = "City Vacation Builder"; }

		VacationBuilder *add_accommodation() override
		{
			m_accommodations.push_back(std::make_shared<Hotel>());
			return this;
		}

		VacationBuilder *add_accommodation(String p_name) override
		{
			m_accommodations.push_back(std::make_shared<Hotel>(p_name));
			return this;
		}

		VacationBuilder *add_accommodation(String p_name, int year, int month, int day, int m_nights, int location) override
		{
			std::shared_ptr<Reservation> m_reservation = std::make_shared<Reservation>();
			m_reservation->set_arrival_date(year, month, day);
			m_reservation->set_nights(m_nights);

			std::shared_ptr<Hotel> hotel = std::make_shared<Hotel>(p_name);
			hotel->set_reservation(m_reservation);
			hotel->set_room_number(location);
			m_accommodations.push_back(hotel);
			return this;
		}

		VacationBuilder *add_event(String p_event) override
		{
			m_events.push_back("See the " + p_event + " show");
			return this;
		}
	};
}
#endif // !VACATION_BUILDER_H