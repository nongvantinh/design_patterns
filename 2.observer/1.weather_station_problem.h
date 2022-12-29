/*
 * We are coding to concrete implementations, not interfaces. For every new display element we need to alter code.
 * We have no way to add (or remove) display elements at run time. We haven't encapsulated the part that changes.
 */

#ifndef WEATHER_STATION_PROBLEM_H
#define WEATHER_STATION_PROBLEM_H

#include <memory>
#include <string>
namespace weather_station_problem
{
	using String = std::string;
	class CurrentConditionsDisplay;
	class StatisticsDisplay;
	class ForecastDisplay;
	class WeatherData
	{
	public:
		WeatherData();

		float get_temperature() const;
		float get_humidity() const;
		float get_pressure() const;
		void measurements_changed();
		void set_measurements(float p_temperature, float p_humidity, float p_pressure);

		void set_current_conditions_display(std::shared_ptr<CurrentConditionsDisplay> p_display);
		void set_statistics_display(std::shared_ptr<StatisticsDisplay> p_display);
		void set_forecast_display(std::shared_ptr<ForecastDisplay> p_display);

	private:
		float m_temperature;
		float m_humidity;
		float m_pressure;

		std::shared_ptr<CurrentConditionsDisplay> m_current_conditions_display;
		std::shared_ptr<StatisticsDisplay> m_statistics_display;
		std::shared_ptr<ForecastDisplay> m_forecast_display;
	};

	class CurrentConditionsDisplay
	{
	public:
		CurrentConditionsDisplay();
		void update(float p_temperature, float p_humidity, float p_pressure);
		String display();

	private:
		float m_temperature;
		float m_humidity;
		float m_pressure;
	};

	class StatisticsDisplay
	{
	public:
		StatisticsDisplay();
		void update(float p_temperature, float p_humidity, float p_pressure);
		String display();
		int get_num_readings() const;

	private:
		float m_min_temperature;
		float m_max_temperature;
		float m_temperature_sum;
		int m_num_readings;
	};

	class ForecastDisplay
	{
	public:
		ForecastDisplay();
		void update(float p_temperature, float p_humidity, float p_pressure);
		String display();

	private:
		float m_current_pressure;
		float m_last_pressure;
	};
}
#endif //! WEATHER_STATION_PROBLEM_H
