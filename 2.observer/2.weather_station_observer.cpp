// Strive for loosely coupled designs between objects that interact
#include "2.weather_station_observer.h"

#include "Catch.hpp"

#include <sstream>
#include <sstream>
using namespace weather_station_observer;
//---------------------------------------------------WeatherData-----------------------------------------------------//
WeatherData::WeatherData() : m_observers(), m_temperature(0.0f), m_humidity(0.0f), m_pressure(0.0f) {}

void WeatherData::register_observer(std::shared_ptr<IObserver> p_observer)
{
    m_observers.push_back(p_observer);
}

void WeatherData::remove_observer(std::shared_ptr<IObserver> p_observer)
{
    m_observers.erase(std::find(m_observers.begin(), m_observers.end(), p_observer));
}

void WeatherData::notify_observers()
{
    for (auto &observer : m_observers)
    {
        observer->update(m_temperature, m_humidity, m_pressure);
    }
}

float WeatherData::get_temperature() const { return m_temperature; }
float WeatherData::get_humidity() const { return m_humidity; }
float WeatherData::get_pressure() const { return m_pressure; }

void WeatherData::measurements_changed() { notify_observers(); }

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

// Inherited via IObserver
void CurrentConditionsDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
    m_temperature = p_temperature;
    m_humidity = p_humidity;
    m_pressure = p_pressure;
}

// Inherited via IDisplayElement
String CurrentConditionsDisplay::display()
{
    std::ostringstream oss;
    oss << "Current conditions: " << m_temperature << "F degrees and " << m_humidity << "% humidity";
    return oss.str();
}
//---------------------------------------------------CurrentConditionsDisplay-----------------------------------------------------//

//---------------------------------------------------StatisticsDisplay-----------------------------------------------------//
StatisticsDisplay::StatisticsDisplay() : m_min_temperature(INT_MAX), m_max_temperature(INT_MIN), m_temperature_sum(0.0f), m_num_readings(0) {}

// Inherited via IObserver
void StatisticsDisplay::update(float p_temperature, float, float)
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

// Inherited via IDisplayElement
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
void ForecastDisplay::update(float, float, float p_pressure)
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

//---------------------------------------------------HeatIndexDisplay-----------------------------------------------------//
HeatIndexDisplay::HeatIndexDisplay() : m_heat_index(0.0f)
{
}

// Inherited via IObserver
void HeatIndexDisplay::update(float p_temperature, float p_humidity, float)
{
    m_heat_index = compute_heat_index(p_temperature, p_humidity);
}

float HeatIndexDisplay::compute_heat_index(float p_temperature, float p_humidity)
{
    // temperature.
    float t = p_temperature;
    // relative humidity.
    float rh = p_humidity;
    float heat_index = (float)((16.923 + (0.185212 * t)) +
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

    return heat_index;
}

// Inherited via IDisplayElement
String HeatIndexDisplay::display()
{
    std::ostringstream oss;
    oss << "Heat index is: " << m_heat_index;
    return oss.str();
}
//---------------------------------------------------HeatIndexDisplay-----------------------------------------------------//

TEST_CASE("ObserverWeatherDataDisplayFixture", "[observer]")
{
    std::shared_ptr<WeatherData> weather_data = std::make_shared<WeatherData>();
    std::shared_ptr<CurrentConditionsDisplay> current_conditions_display = std::make_shared<CurrentConditionsDisplay>();
    std::shared_ptr<StatisticsDisplay> statistics_display = std::make_shared<StatisticsDisplay>();
    std::shared_ptr<ForecastDisplay> forecast_display = std::make_shared<ForecastDisplay>();
    std::shared_ptr<HeatIndexDisplay> heat_index_display = std::make_shared<HeatIndexDisplay>();
    weather_data->register_observer(current_conditions_display);
    weather_data->register_observer(statistics_display);
    weather_data->register_observer(forecast_display);
    weather_data->register_observer(heat_index_display);
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

    SECTION("TestHeatIndexDisplay")
    {
        weather_data->set_measurements(80, 65, 31.2f);
        REQUIRE("Heat index is: 82.9554" == heat_index_display->display());
    }
}