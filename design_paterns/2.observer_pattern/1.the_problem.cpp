#include "Catch.hpp"

#include <iostream>


/*
* We are coding to concrete implementations, not interfaces.
* For every new display element we need to alter code.
* We have no way to add (or remove) display elements at run time.
* We haven't encapsulated the part that changes.
*/

class CurrentConditionsDisplay
{
public:

	void update(float p_temperature, float p_humidity, float p_pressure) 
	{
		m_temperature = p_temperature;
		m_humidity = p_humidity;
		display();
	}

	void display() 
	{
		std::cout << "Current condition: " << m_temperature << "F degrees and " << m_humidity << "% humidity\n";
	}

private:
	float m_temperature;
	float m_humidity;
};

class ThirdPartyDisplay
{
public:
	void update(float p_temperature, float p_humidity, float p_pressure) 
	{
	}

	void display() 
	{
	}

};

class StatisticsDisplay
{
public:
	void update(float p_temperature, float p_humidity, float p_pressure) 
	{
	}

	void display() 
	{
	}

};

class ForecastDisplay
{
public:
	void update(float p_temperature, float p_humidity, float p_pressure) 
	{
	}

	void display() 
	{
	}
};


class WeatherData
{
public:
	float get_temperature() const { return m_temperature; }
	float get_humidity() const { return m_humidity; }
	float get_pressure() const { return m_pressure; }

	void measurements_changed()
	{
		float temp = get_temperature();
		float humidity = get_humidity();
		float pressure = get_pressure();

		m_current_conditions_display->update(temp, humidity, pressure);
		m_statistics_display->update(temp, humidity, pressure);
		m_forecast_display->update(temp, humidity, pressure);
	}

	void set_measurements(float p_temperature, float p_humidity, float p_pressure)
	{
		m_temperature = p_temperature;
		m_humidity = p_humidity;
		m_pressure = p_pressure;
		measurements_changed();
	}

private:
	float m_temperature;
	float m_humidity;
	float m_pressure;

	std::shared_ptr<CurrentConditionsDisplay> m_current_conditions_display;
	std::shared_ptr<StatisticsDisplay> m_statistics_display;
	std::shared_ptr<ForecastDisplay> m_forecast_display;
};

//
//TEST_CASE("We are coding to concrete implementations, not interfaces", "[observer_pattern]")
//{
//	std::shared_ptr<WeatherData> weatherData = std::make_shared<WeatherData>();
//	std::shared_ptr<CurrentConditionsDisplay> currentDisplay = std::make_shared<CurrentConditionsDisplay>(weatherData);
//	std::shared_ptr<StatisticsDisplay> statisticsDisplay = std::make_shared<StatisticsDisplay>(weatherData);
//	std::shared_ptr<ForecastDisplay> forecastDisplay = std::make_shared<ForecastDisplay>(weatherData);
//	weatherData->set_measurements(80, 65, 30.4f);
//	weatherData->set_measurements(82, 70, 29.2f);
//	weatherData->set_measurements(78, 90, 29.2f);
//}
