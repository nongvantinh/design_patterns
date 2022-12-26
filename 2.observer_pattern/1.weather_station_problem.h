/*
 * We are coding to concrete implementations, not interfaces. For every new display element we need to alter code.
 * We have no way to add (or remove) display elements at run time. We haven't encapsulated the part that changes.
 */

#ifndef WEATHER_STATION_PROBLEM_H
#define WEATHER_STATION_PROBLEM_H

#include <memory>

class CurrentConditionsDisplay
{
public:
	void update(float p_temperature, float p_humidity, float p_pressure);
	void display();

private:
	float m_temperature;
	float m_humidity;
};

class ThirdPartyDisplay
{
public:
	void update(float p_temperature, float p_humidity, float p_pressure);
	void display();
};

class StatisticsDisplay
{
public:
	void update(float p_temperature, float p_humidity, float p_pressure);
	void display();
};

class ForecastDisplay
{
public:
	void update(float p_temperature, float p_humidity, float p_pressure);
	void display();
};

class WeatherData
{
public:
	float get_temperature() const;
	float get_humidity() const;
	float get_pressure() const;

	void measurements_changed();
	void set_measurements(float p_temperature, float p_humidity, float p_pressure);

private:
	float m_temperature;
	float m_humidity;
	float m_pressure;

	std::shared_ptr<CurrentConditionsDisplay> m_current_conditions_display;
	std::shared_ptr<StatisticsDisplay> m_statistics_display;
	std::shared_ptr<ForecastDisplay> m_forecast_display;
};
#endif //! WEATHER_STATION_PROBLEM_H
