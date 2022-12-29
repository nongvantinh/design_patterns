#ifndef WEATHER_STATION_OBSERVER_H
#define WEATHER_STATION_OBSERVER_H
/*
 * The Observer Pattern provides an object design where subjects and observers are loosely coupled:
 *	-	The only thing the subject knows about an observer is that it implements a certain interface.
 *	-	We can add new observers at any time.
 *	-	We never need to modify the subject to add new types of observers.
 *	-	We can reuse subjects or observers independently of each other.
 *	-	Changes to either the subject or an observer will not affect the other.
 */
#include <list>
#include <algorithm>
#include <memory>
#include <string>
namespace weather_station_observer
{
    using String = std::string;

    class IObserver
    {
    public:
        virtual void update(float p_temperature, float p_humidity, float p_pressure) = 0;
        virtual ~IObserver(){};
    };

    class ISubject
    {
    public:
        virtual void register_observer(std::shared_ptr<IObserver> p_observer) = 0;
        virtual void remove_observer(std::shared_ptr<IObserver> p_observer) = 0;
        virtual void notify_observers() = 0;
        virtual ~ISubject(){};
    };

    class IDisplayElement
    {
    public:
        virtual String display() = 0;
        virtual ~IDisplayElement(){};
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

    //---------------------------------------------------CurrentConditionsDisplay-----------------------------------------------------//
    class CurrentConditionsDisplay : public IObserver, IDisplayElement, std::enable_shared_from_this<CurrentConditionsDisplay>
    {
    public:
        CurrentConditionsDisplay();
        // Inherited via IObserver
        void update(float p_temperature, float p_humidity, float p_pressure) override;
        // Inherited via IDisplayElement
        String display() override;

    private:
        float m_temperature;
        float m_humidity;
        float m_pressure;
    };
    //---------------------------------------------------CurrentConditionsDisplay-----------------------------------------------------//

    //---------------------------------------------------StatisticsDisplay-----------------------------------------------------//
    class StatisticsDisplay : public IObserver, IDisplayElement
    {
    public:
        StatisticsDisplay();
        // Inherited via IObserver
        void update(float p_temperature, float p_humidity, float p_pressure) override;
        // Inherited via IDisplayElement
        String display() override;
        int get_num_readings() const;

    private:
        float m_min_temperature;
        float m_max_temperature;
        float m_temperature_sum;
        int m_num_readings;
    };
    //---------------------------------------------------StatisticsDisplay-----------------------------------------------------//

    //---------------------------------------------------ForecastDisplay-----------------------------------------------------//
    class ForecastDisplay : public IObserver, IDisplayElement
    {
    public:
        ForecastDisplay();
        // Inherited via IObserver
        void update(float p_temperature, float, float p_pressure) override;
        // Inherited via IDisplayElement
        String display() override;

    private:
        float m_current_pressure;
        float m_last_pressure;
    };
    //---------------------------------------------------ForecastDisplay-----------------------------------------------------//

    //---------------------------------------------------HeatIndexDisplay-----------------------------------------------------//
    class HeatIndexDisplay : public IObserver, IDisplayElement
    {
    public:
        HeatIndexDisplay();
        // Inherited via IObserver
        void update(float p_temperature, float p_humidity, float) override;
        // Inherited via IDisplayElement
        String display() override;
        float compute_heat_index(float p_temperature, float p_humidity);

    private:
        float m_heat_index;
    };
    //---------------------------------------------------HeatIndexDisplay-----------------------------------------------------//
}

#endif //! WEATHER_STATION_OBSERVER_H