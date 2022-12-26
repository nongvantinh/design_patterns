// Strive for loosely coupled designs between objects that interact
#include "2.weather_station_observer_pattern.h"
//---------------------------------------------------WeatherData-----------------------------------------------------//
WeatherData::WeatherData() : m_temperature(0.0f), m_humidity(0.0f), m_pressure(0.0f) {}

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
CurrentConditionsDisplay::CurrentConditionsDisplay() : m_weather_data(nullptr), m_humidity(0.0f), m_temperature(0.0f) {}

// Inherited via IObserver
void CurrentConditionsDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
    m_temperature = p_temperature;
    m_humidity = p_humidity;
    display();
}

// Inherited via IDisplayElement
void CurrentConditionsDisplay::display()
{
    std::cout << "Current conditions: " << m_temperature << "F degrees and " << m_humidity << "% humidity" << std::endl;
}
//---------------------------------------------------CurrentConditionsDisplay-----------------------------------------------------//

//---------------------------------------------------StatisticsDisplay-----------------------------------------------------//
StatisticsDisplay::StatisticsDisplay() : m_min_temperature(INT_MAX), m_max_temperature(INT_MIN), m_temperature_sum(0.0f), m_num_readings(0) {}

// Inherited via IObserver
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

    display();
}

// Inherited via IDisplayElement
void StatisticsDisplay::display()
{
    std::cout << "Avg/Max/Min temperature = " << m_temperature_sum / m_num_readings << "/" << m_max_temperature << "/" << m_min_temperature << std::endl;
}
//---------------------------------------------------StatisticsDisplay-----------------------------------------------------//

//---------------------------------------------------ForecastDisplay-----------------------------------------------------//
ForecastDisplay::ForecastDisplay() : m_weather_data(), m_current_pressure(29.29f), m_last_pressure(0.0f) {}

// Inherited via IObserver
void ForecastDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
    m_last_pressure = m_current_pressure;
    m_current_pressure = p_pressure;
    display();
}

// Inherited via IDisplayElement
void ForecastDisplay::display()
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
//---------------------------------------------------ForecastDisplay-----------------------------------------------------//

//---------------------------------------------------HeatIndexDisplay-----------------------------------------------------//
HeatIndexDisplay::HeatIndexDisplay() : m_heat_index(0.0f) {}

// Inherited via IObserver
void HeatIndexDisplay::update(float p_temperature, float p_humidity, float p_pressure)
{
    // temperature.
    float t = p_temperature;
    // relative humidity.
    float rh = p_humidity;
    m_heat_index = (float)((16.923 + (0.185212 * t)) +
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

// Inherited via IDisplayElement
void HeatIndexDisplay::display()
{
    std::cout << "Heat index is: " << m_heat_index << std::endl;
}
//---------------------------------------------------HeatIndexDisplay-----------------------------------------------------//

int main()
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