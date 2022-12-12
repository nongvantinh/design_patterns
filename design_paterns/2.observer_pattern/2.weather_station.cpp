#include "Catch.hpp"

#include <list>
#include <iostream>
#include <algorithm>

/*
* The Observer Pattern provides an object design where subjects and observers are loosely coupled:
*	-	The only thing the subject knows about an observer is that it implements a certain interface.
*	-	We can add new observers at any time.
*	-	We never need to modify the subject to add new types of observers.
*	-	We can reuse subjects or observers independently of each other.
*	-	Changes to either the subject or an observer will not affect the other.
*/
class Observer;
class Subject
{
public:
	virtual void register_observer(std::shared_ptr<Observer> p_observer) = 0;
	virtual void remove_observer(std::shared_ptr<Observer> p_observer) = 0;
	virtual void notify_observers() = 0;
};

class Observer
{
public:
	virtual void update(float p_temperature, float p_humidity, float p_pressure) = 0;
};

class DisplayElement
{
public:
	virtual void display() = 0;
};

class WeatherData : public Subject
{
public:
	WeatherData() :m_temperature(0.0f), m_humidity(0.0f), m_pressure(0.0f) {}

	// Inherited via Subject
	virtual void register_observer(std::shared_ptr<Observer> p_observer) override
	{
		m_observers.push_back(p_observer);
	}

	virtual void remove_observer(std::shared_ptr<Observer> p_observer) override
	{
		m_observers.erase(std::find(m_observers.begin(), m_observers.end(), p_observer));
	}

	virtual void notify_observers() override
	{
		for (auto& observer : m_observers)
		{
			observer->update(m_temperature, m_humidity, m_pressure);
		}
	}

	float get_temperature() const { return m_temperature; }
	float get_humidity() const { return m_humidity; }
	float get_pressure() const { return m_pressure; }

	void measurements_changed()
	{
		notify_observers();
	}

	void set_measurements(float p_temperature, float p_humidity, float p_pressure)
	{
		m_temperature = p_temperature;
		m_humidity = p_humidity;
		m_pressure = p_pressure;
		measurements_changed();
	}

private:
	std::list<std::shared_ptr<Observer>> m_observers;
	float m_temperature;
	float m_humidity;
	float m_pressure;
};

class CurrentConditionsDisplay : public Observer, DisplayElement
{
public:
	CurrentConditionsDisplay() :m_weather_data(nullptr), m_humidity(0.0f), m_temperature(0.0f) {
	}

	// Inherited via Observer
	virtual void update(float p_temperature, float p_humidity, float p_pressure) override
	{
		m_temperature = p_temperature;
		m_humidity = p_humidity;
		display();
	}

	// Inherited via DisplayElement
	virtual void display() override
	{
		std::cout << "Current conditions: " << m_temperature << "F degrees and " << m_humidity << "% humidity" << std::endl;
	}

private:
	float m_temperature;
	float m_humidity;
	std::shared_ptr<Subject> m_weather_data;
};

class StatisticsDisplay : public Observer, DisplayElement
{
public:
	StatisticsDisplay() :m_min_temperature(INT_MAX), m_max_temperature(INT_MIN), m_temperature_sum(0.0f), m_num_readings(0) {	}

	// Inherited via Observer
	virtual void update(float p_temperature, float p_humidity, float p_pressure) override
	{
		m_temperature_sum += p_temperature;
		++m_num_readings;

		if (m_max_temperature < p_temperature)
		{
			m_max_temperature = p_temperature;
		}

		if (p_temperature < m_min_temperature)
		{
			m_min_temperature = p_temperature;
		}

		display();
	}

	// Inherited via DisplayElement
	virtual void display() override
	{
		std::cout << "Avg/Max/Min temperature = " << m_temperature_sum / m_num_readings << "/" << m_max_temperature << "/" << m_min_temperature << std::endl;
	}

private:
	float m_min_temperature;
	float m_max_temperature;
	float m_temperature_sum;
	int m_num_readings;
};

class ForecastDisplay : public Observer, DisplayElement
{
public:
	ForecastDisplay() :m_weather_data(), m_current_pressure(29.29f), m_last_pressure(0.0f) {}

	// Inherited via Observer
	virtual void update(float p_temperature, float p_humidity, float p_pressure) override
	{
		m_last_pressure = m_current_pressure;
		m_current_pressure = p_pressure;
		display();
	}

	// Inherited via DisplayElement
	virtual void display() override
	{
		std::cout << "Forecast: ";
		if (m_current_pressure > m_last_pressure)
		{
			std::cout << "Improving weather on the way!" << std::endl;
		}
		else if (m_current_pressure == m_last_pressure)
		{
			std::cout << "More of the same" << std::endl;
		}
		else if (m_current_pressure < m_last_pressure)
		{
			std::cout << "Watch out for cooler, rainy weather" << std::endl;
		}
	}
private:
	float m_current_pressure;
	float m_last_pressure;
	std::shared_ptr<Subject> m_weather_data;
};

class HeatIndexDisplay : public Observer, DisplayElement
{
public:
	HeatIndexDisplay() :m_heat_index(0.0f){}

	// Inherited via Observer
	virtual void update(float p_temperature, float p_humidity, float p_pressure) override
	{
		// temperature.
		float t = p_temperature;
		// relative humidity.
		float rh = p_humidity;
		m_heat_index = (float)
			(
				(16.923 + (0.185212 * t)) +
				(5.37941 * rh) -
				(0.100254 * t * rh) +
				(0.00941695 * (t * t)) +
				(0.00728898 * (rh * rh)) +
				(0.000345372 * (t * t * rh)) -
				(0.000814971 * (t * rh * rh)) +
				(0.0000102102 * (t * t * rh * rh)) -
				(0.000038646 * (t * t * t)) +
				(0.0000291583 * (rh * rh * rh)) +
				(0.00000142721 * (t * t * t * rh)) +
				(0.000000197483 * (t * rh * rh * rh)) -
				(0.0000000218429 * (t * t * t * rh * rh)) +
				(0.000000000843296 * (t * t * rh * rh * rh)) -
				(0.0000000000481975 * (t * t * t * rh * rh * rh)));

		display();
	}

	// Inherited via DisplayElement
	virtual void display() override
	{
		std::cout << "Heat index is: " << m_heat_index << std::endl;
	}

private:
	float m_heat_index;
};

TEST_CASE("Strive for loosely coupled designs between objects that interact", "[observer_pattern]")
{
	std::shared_ptr<WeatherData> weather_data = std::make_shared<WeatherData>();
	std::shared_ptr<CurrentConditionsDisplay> current_display = std::make_shared<CurrentConditionsDisplay>();
	std::shared_ptr<StatisticsDisplay> statistics_display = std::make_shared<StatisticsDisplay>();
	std::shared_ptr<ForecastDisplay> forecast_display = std::make_shared<ForecastDisplay>();
	std::shared_ptr<HeatIndexDisplay> head_index = std::make_shared<HeatIndexDisplay>();

	weather_data->register_observer(current_display);
	weather_data->register_observer(statistics_display);
	weather_data->register_observer(forecast_display);
	weather_data->register_observer(head_index);

	weather_data->set_measurements(80, 65, 30.4f);
	weather_data->set_measurements(82, 70, 29.2f);
	weather_data->set_measurements(78, 90, 29.2f);
}