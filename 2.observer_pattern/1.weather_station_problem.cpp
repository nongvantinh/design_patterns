// We are coding to concrete implementations, not interfaces.
#include "1.weather_station_problem.h"

#include <iostream>

void CurrentConditionsDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
    m_temperature = p_temperature;
    m_humidity = p_humidity;
    display();
}

void CurrentConditionsDisplay::display()
{
    std::cout << "Current condition: " << m_temperature << "F degrees and " << m_humidity << "% humidity\n";
}

void ThirdPartyDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
}

void ThirdPartyDisplay::display()
{
}

void StatisticsDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
}

void StatisticsDisplay::display()
{
}

void ForecastDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
}

void ForecastDisplay::display()
{
}

float WeatherData::get_temperature() const { return m_temperature; }
float WeatherData::get_humidity() const { return m_humidity; }
float WeatherData::get_pressure() const { return m_pressure; }

void WeatherData::measurements_changed()
{
    float temp = get_temperature();
    float humidity = get_humidity();
    float pressure = get_pressure();

    m_current_conditions_display->update(temp, humidity, pressure);
    m_statistics_display->update(temp, humidity, pressure);
    m_forecast_display->update(temp, humidity, pressure);
}

void WeatherData::set_measurements(float p_temperature, float p_humidity, float p_pressure)
{
    m_temperature = p_temperature;
    m_humidity = p_humidity;
    m_pressure = p_pressure;
    measurements_changed();
}

int main()
{
	std::shared_ptr<WeatherData> weatherData = std::make_shared<WeatherData>();
	std::shared_ptr<CurrentConditionsDisplay> currentDisplay = std::make_shared<CurrentConditionsDisplay>(weatherData);
	std::shared_ptr<StatisticsDisplay> statisticsDisplay = std::make_shared<StatisticsDisplay>(weatherData);
	std::shared_ptr<ForecastDisplay> forecastDisplay = std::make_shared<ForecastDisplay>(weatherData);
	weatherData->set_measurements(80, 65, 30.4f);
	weatherData->set_measurements(82, 70, 29.2f);
	weatherData->set_measurements(78, 90, 29.2f);
}
