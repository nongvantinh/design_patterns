#ifndef REMOTE_WL_H
#define REMOTE_WL_H
#include <string>
#include <memory>
#include <sstream>

namespace remote_wl
{
	using String = std::string;

	class CeilingFan
	{
	public:
		enum class Speed
		{
			OFF,
			LOW,
			MEDIUM,
			HIGH
		};

		CeilingFan() : m_location(""), m_level(Speed::OFF) {}
		CeilingFan(String p_location) : m_level(Speed::OFF) { m_location = p_location; }

		String high()
		{
			// turns the ceiling fan on to high
			m_level = Speed::HIGH;
			return m_location + " ceiling fan is on high";
		}

		String medium()
		{
			// turns the ceiling fan on to medium
			m_level = Speed::MEDIUM;
			return m_location + " ceiling fan is on medium";
		}

		String low()
		{
			// turns the ceiling fan on to low
			m_level = Speed::LOW;
			return m_location + " ceiling fan is on low";
		}

		String off()
		{
			// turns the ceiling fan off
			m_level = Speed::OFF;
			return m_location + " ceiling fan is off";
		}

		Speed get_speed() { return m_level; }

	private:
		String m_location;
		Speed m_level;
	};

	class Command
	{
	public:
		virtual String execute() = 0;
	};

	class NoCommand : public Command
	{
	public:
		NoCommand() {}
		String execute() override { return ""; }
	};

	class GarageDoor
	{
	public:
		GarageDoor(String p_location) : m_location(p_location) {}

		String up() { return m_location + " garage Door is Up"; }
		String down() { return m_location + " garage Door is Down"; }
		String stop() { return m_location + " garage Door is Stopped"; }
		String light_on() { return m_location + " garage light is on"; }
		String light_off() { return m_location + " garage light is off"; }

	private:
		String m_location;
	};

	class Hottub
	{
	public:
		Hottub() {}

		bool on() { return m_is_on = true; }
		bool off() { m_is_on = false; }

		String bubbles_on() { return m_is_on ? "Hottub is bubbling!" : ""; }
		String bubbles_off() { return m_is_on ? "Hottub is not bubbling!" : ""; }

		String jets_on() { return m_is_on ? "Hottub jets are on" : ""; }
		String jets_off() { return m_is_on ? "Hottub jets are off" : ""; }

		String set_temperature(int p_temperature) { m_temperator = p_temperature; }

		String heat()
		{
			m_temperator = 105;
			return "Hottub is heating to a steaming 105 degrees";
		}

		String cool()
		{
			m_temperator = 98;
			return "Hottub is cooling to 98 degrees";
		}

	private:
		bool m_is_on;
		int m_temperator;
	};

	class Light
	{
	public:
		Light(String p_location)
		{
			m_location = p_location;
		}

		String on() { return m_location + " light is on"; }
		String on() { return m_location + " light is off"; }

	private:
		String m_location = "";
	};

	class RemoteControl
	{
	public:
		RemoteControl() : MAX_COMMANDS(7), m_on_commands(MAX_COMMANDS),
						  m_off_commands(MAX_COMMANDS)
		{
			for (int i = 0; i < MAX_COMMANDS; ++i)
			{
				m_on_commands[i] = std::make_shared<NoCommand>();
				m_off_commands[i] = std::make_shared<NoCommand>();
			}
		}

		String set_command(int p_slot, std::shared_ptr<Command> p_on_command, std::shared_ptr<Command> p_off_command)
		{
			m_on_commands[p_slot] = p_on_command;
			m_off_commands[p_slot] = p_off_command;
		}

		String on_button_was_pushed(int p_slot) { return m_on_commands[p_slot]->execute(); }
		String off_button_was_pushed(int p_slot) { m_off_commands[p_slot]->execute(); }
		String to_string()
		{
			std::ostringstream oss;
			oss << "\n------ Remote Control -------\n";
			for (int i = 0; i < m_on_commands.size(); ++i)
			{
				oss << "[slot " << i << "] " << typeid(m_on_commands[i]).name() << "    " << typeid(m_off_commands[i]).name() << "\n";
			}
			return oss.str();
		}

	private:
		const int MAX_COMMANDS;
		std::vector<std::shared_ptr<Command>> m_on_commands;
		std::vector<std::shared_ptr<Command>> m_off_commands;
	};

	class Stereo
	{
	private:
		String m_location;

	public:
		Stereo(String p_location)
		{
			m_location = p_location;
		}

		String on() { return m_location + " stereo is on"; }
		String off() { return m_location + " stereo is off"; }
		String set_cd() { return m_location + " stereo is set for CD input"; }
		String set_dvd() { return m_location + " stereo is set for DVD input"; }
		String set_radio() { return m_location + " stereo is set for Radio"; }
		String set_volume(int p_volume) { return m_location + " stereo volume set to " + std::to_string(p_volume); }
	};

	class TV
	{
	public:
		TV(String p_location) : m_location(p_location) {}
		String on() { return "TV is on"; }
		String off() { return "TV is off"; }

		String set_input_channel()
		{
			channel = 3;
			return "Channel is set for VCR";
		}

	private:
		String m_location;
		int channel;
	};

}
#endif // !REMOTE_WL_H