// We are coding to concrete implementations, not interfaces.
#include "1.weather_station_problem.h"

#include "Catch.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace weather_station_problem;

//---------------------------------------------------WeatherData-----------------------------------------------------//
WeatherData::WeatherData() : m_temperature(0.0f), m_humidity(0.0f), m_pressure(0.0f) {}
void WeatherData::set_current_conditions_display(std::shared_ptr<CurrentConditionsDisplay> &p_display)
{
    m_current_conditions_display = p_display;
}
void WeatherData::set_statistics_display(std::shared_ptr<StatisticsDisplay> &p_display)
{
    m_statistics_display = p_display;
}

void WeatherData::set_forecast_display(std::shared_ptr<ForecastDisplay> &p_display)
{
    m_forecast_display = p_display;
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
//---------------------------------------------------WeatherData-----------------------------------------------------//

//---------------------------------------------------CurrentConditionsDisplay-----------------------------------------------------//
CurrentConditionsDisplay::CurrentConditionsDisplay()
    : m_temperature(0.0f), m_humidity(0.0f), m_pressure(0.0f) {}

void CurrentConditionsDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
    m_temperature = p_temperature;
    m_humidity = p_humidity;
    m_pressure = p_pressure;
    display();
}

String CurrentConditionsDisplay::display()
{
    std::ostringstream oss;
    oss << "Current conditions: " << m_temperature << "F degrees and " << m_humidity << "% humidity";
    return oss.str();
}
//---------------------------------------------------CurrentConditionsDisplay-----------------------------------------------------//

//---------------------------------------------------StatisticsDisplay-----------------------------------------------------//
StatisticsDisplay::StatisticsDisplay() : m_min_temperature(INT_MAX), m_max_temperature(INT_MIN), m_temperature_sum(0.0f), m_num_readings(0) {}
void StatisticsDisplay::update(float p_temperature, float p_humidity, float p_pressure)
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
}
String StatisticsDisplay::display()
{
    std::ostringstream oss;
    oss << "Avg/Max/Min temperature = " << m_temperature_sum / m_num_readings << "F/" << m_max_temperature << "F/" << m_min_temperature << "F";
    return oss.str();
}
int StatisticsDisplay::get_num_readings() const { return m_num_readings; }

//---------------------------------------------------StatisticsDisplay-----------------------------------------------------//

//---------------------------------------------------ForecastDisplay-----------------------------------------------------//
ForecastDisplay::ForecastDisplay() : m_current_pressure(29.29f), m_last_pressure(0.0f)
{
}

// Inherited via IObserver
void ForecastDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
    m_last_pressure = m_current_pressure;
    m_current_pressure = p_pressure;
}

// Inherited via IDisplayElement
String ForecastDisplay::display()
{
    std::ostringstream oss;
    oss << "Forecast: ";
    if (m_last_pressure < m_current_pressure)
    {
        oss << "Improving weather on the way!";
    }
    else if (m_current_pressure == m_last_pressure)
    {
        oss << "More of the same";
    }
    else if (m_current_pressure < m_last_pressure)
    {
        oss << "Watch out for cooler, rainy weather";
    }
    return oss.str();
}
//---------------------------------------------------ForecastDisplay-----------------------------------------------------//

TEST_CASE("ObserverWeatherDataDisplayFixture", "[observer]")
{
    std::shared_ptr<WeatherData> weather_data = std::make_shared<WeatherData>();
    std::shared_ptr<CurrentConditionsDisplay> current_conditions_display = std::make_shared<CurrentConditionsDisplay>();
    std::shared_ptr<StatisticsDisplay> statistics_display = std::make_shared<StatisticsDisplay>();
    std::shared_ptr<ForecastDisplay> forecast_display = std::make_shared<ForecastDisplay>();
    weather_data->set_current_conditions_display(current_conditions_display);
    weather_data->set_statistics_display(statistics_display);
    weather_data->set_forecast_display(forecast_display);
    SECTION("TestCurrentConditionsDisplay")
    {
        weather_data->set_measurements(80, 65, 30.4f);
        REQUIRE("Current conditions: 80F degrees and 65% humidity" == current_conditions_display->display());
    }

    SECTION("TestForecastDisplay")
    {
        weather_data->set_measurements(81, 63, 31.2f);
        REQUIRE("Forecast: Improving weather on the way!" == forecast_display->display());
        weather_data->set_measurements(81, 63, 29.92f);
        REQUIRE("Forecast: Watch out for cooler, rainy weather" == forecast_display->display());
        weather_data->set_measurements(81, 63, 29.92f);
        REQUIRE("Forecast: More of the same" == forecast_display->display());
    }

    SECTION("TestStatisticsDisplay")
    {
        weather_data->set_measurements(80, 63, 31.2f);
        weather_data->set_measurements(81, 63, 29.92f);
        weather_data->set_measurements(84, 63, 29.92f);

        if (3 == statistics_display->get_num_readings())
        {
            REQUIRE("Avg/Max/Min temperature = 81.6667F/84F/80F" == statistics_display->display());
        }

        if (8 == statistics_display->get_num_readings())
        {
            REQUIRE("Avg/Max/Min temperature = 81.00F/84F/80F" == statistics_display->display());
        }
    }
}