#ifndef WEATHER_STATION_OBSERVER_PATTERN_H
#define WEATHER_STATION_OBSERVER_PATTERN_H
#include <list>
#include <iostream>
#include <algorithm>
#include <memory>

/*
 * The Observer Pattern provides an object design where subjects and observers are loosely coupled:
 *	-	The only thing the subject knows about an observer is that it implements a certain interface.
 *	-	We can add new observers at any time.
 *	-	We never need to modify the subject to add new types of observers.
 *	-	We can reuse subjects or observers independently of each other.
 *	-	Changes to either the subject or an observer will not affect the other.
 */

class IObserver
{
public:
    virtual void update(float p_temperature, float p_humidity, float p_pressure) = 0;
};

class ISubject
{
public:
    virtual void register_observer(std::shared_ptr<IObserver> p_observer) = 0;
    virtual void remove_observer(std::shared_ptr<IObserver> p_observer) = 0;
    virtual void notify_observers() = 0;
};

class IDisplayElement
{
public:
    virtual void display() = 0;
};

class WeatherData : public ISubject
{
public:
    WeatherData();

    // Inherited via ISubject
    void register_observer(std::shared_ptr<IObserver> p_observer) override;
    void remove_observer(std::shared_ptr<IObserver> p_observer) override;
    void notify_observers() override;

    float get_temperature() const;
    float get_humidity() const;
    float get_pressure() const;
    void measurements_changed();
    void set_measurements(float p_temperature, float p_humidity, float p_pressure);

private:
    std::list<std::shared_ptr<IObserver>> m_observers;
    float m_temperature;
    float m_humidity;
    float m_pressure;
};

class CurrentConditionsDisplay : public IObserver, IDisplayElement
{
public:
    CurrentConditionsDisplay();
    // Inherited via IObserver
    void update(float p_temperature, float p_humidity, float p_pressure) override;
    // Inherited via IDisplayElement
    void display() override;

private:
    float m_temperature;
    float m_humidity;
    std::shared_ptr<ISubject> m_weather_data;
};

class StatisticsDisplay : public IObserver, IDisplayElement
{
public:
    StatisticsDisplay();
    // Inherited via IObserver
    void update(float p_temperature, float p_humidity, float p_pressure) override;
    // Inherited via IDisplayElement
    void display() override;

private:
    float m_min_temperature;
    float m_max_temperature;
    float m_temperature_sum;
    int m_num_readings;
    std::shared_ptr<ISubject> m_weather_data;
};

class ForecastDisplay : public IObserver, IDisplayElement
{
public:
    ForecastDisplay();
    // Inherited via IObserver
    void update(float p_temperature, float p_humidity, float p_pressure) override;
    // Inherited via IDisplayElement
    void display() override;

private:
    float m_current_pressure;
    float m_last_pressure;
    std::shared_ptr<ISubject> m_weather_data;
};

class HeatIndexDisplay : public IObserver, IDisplayElement
{
public:
    HeatIndexDisplay();
    // Inherited via IObserver
    void update(float p_temperature, float p_humidity, float p_pressure) override;
    // Inherited via IDisplayElement
    void display() override;

private:
    float m_heat_index;
    std::shared_ptr<ISubject> m_weather_data;
};

#endif //! WEATHER_STATION_OBSERVER_PATTERN_H