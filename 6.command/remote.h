#ifndef REMOTE_H
#define REMOTE_H
#include <string>
#include <memory>
#include <sstream>
#include <vector>

namespace remote
{
	using String = std::string;

	class Command
	{
	public:
		virtual String execute() = 0;
	};

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
		String m_location = "";
		Speed m_level;
	};

	class CeilingFanOffCommand : public Command
	{
	public:
		CeilingFanOffCommand(std::shared_ptr<CeilingFan> p_ceiling_fan)
		{
			m_ceiling_fan = p_ceiling_fan;
		}

		String execute() { return m_ceiling_fan->off(); }

	private:
		std::shared_ptr<CeilingFan> m_ceiling_fan;
	};

	class CeilingFanOnCommand : public Command
	{
	public:
		CeilingFanOnCommand(std::shared_ptr<CeilingFan> p_ceiling_fan)
		{
			m_ceiling_fan = p_ceiling_fan;
		}
		String execute() { return m_ceiling_fan->high(); }

	private:
		std::shared_ptr<CeilingFan> m_ceiling_fan;
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

	class GarageDoorDownCommand : public Command
	{
	public:
		GarageDoorDownCommand(std::shared_ptr<GarageDoor> p_garage_door)
		{
			m_garage_door = p_garage_door;
		}

		String execute() { return m_garage_door->up(); }

	private:
		std::shared_ptr<GarageDoor> m_garage_door;
	};

	class GarageDoorUpCommand : public Command
	{
	public:
		GarageDoorUpCommand(std::shared_ptr<GarageDoor> p_garage_door)
		{
			m_garage_door = p_garage_door;
		}

		String execute() { return m_garage_door->up(); }

	private:
		std::shared_ptr<GarageDoor> m_garage_door;
	};

	class Hottub
	{
	public:
		Hottub() {}

		bool on() { return m_is_on = true; }
		bool off() { return m_is_on = false; }

		String bubbles_on() { return m_is_on ? "Hottub is bubbling!" : ""; }
		String bubbles_off() { return m_is_on ? "Hottub is not bubbling!" : ""; }

		String jets_on() { return m_is_on ? "Hottub jets are on" : ""; }
		String jets_off() { return m_is_on ? "Hottub jets are off" : ""; }

		void set_temperature(int p_temperature) { m_temperator = p_temperature; }

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

	class HottubOffCommand : public Command
	{
	public:
		HottubOffCommand(std::shared_ptr<Hottub> p_hottub)
		{
			m_hottub = p_hottub;
		}

		String execute()
		{
			std::ostringstream oss;
			oss << m_hottub->cool();
			oss << m_hottub->off();

			return oss.str();
		}

	private:
		std::shared_ptr<Hottub> m_hottub;
	};

	class HottubOnCommand : public Command
	{
	public:
		HottubOnCommand(std::shared_ptr<Hottub> p_hottub)
		{
			m_hottub = p_hottub;
		}

		String execute()
		{
			std::ostringstream oss;
			oss << m_hottub->on();
			oss << m_hottub->heat();
			oss << m_hottub->bubbles_on();
			return oss.str();
		}

	private:
		std::shared_ptr<Hottub> m_hottub;
	};

	class Light
	{
	public:
		Light(String p_location)
		{
			m_location = p_location;
		}

		String on() { return m_location + " light is on"; }
		String off() { return m_location + " light is off"; }

	private:
		String m_location = "";
	};

	class LightOffCommand : public Command
	{
	public:
		LightOffCommand(std::shared_ptr<Light> p_light)
		{
			m_light = p_light;
		}

		String execute() { return m_light->off(); }

	private:
		std::shared_ptr<Light> m_light;
	};

	class LightOnCommand : public Command
	{
	public:
		LightOnCommand(std::shared_ptr<Light> p_light)
		{
			m_light = p_light;
		}

		String execute() override
		{
			return m_light->on();
		}

	private:
		std::shared_ptr<Light> m_light;
	};

	class LivingroomLightOffCommand : public Command
	{
	public:
		LivingroomLightOffCommand(std::shared_ptr<Light> p_light)
		{
			m_light = p_light;
		}

		String execute() { return m_light->off(); }

	private:
		std::shared_ptr<Light> m_light;
	};

	class LivingroomLightOnCommand : public Command
	{
	public:
		LivingroomLightOnCommand(std::shared_ptr<Light> p_light)
		{
			m_light = p_light;
		}

		String execute()
		{
			return m_light->on();
		}

	private:
		std::shared_ptr<Light> m_light;
	};

	class NoCommand : public Command
	{
		String execute() { return ""; }
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

		void set_command(int p_slot, std::shared_ptr<Command> p_on_command, std::shared_ptr<Command> p_off_command)
		{
			m_on_commands[p_slot] = p_on_command;
			m_off_commands[p_slot] = p_off_command;
		}

		String on_button_was_pushed(int p_slot) { return m_on_commands[p_slot]->execute(); }
		String off_button_was_pushed(int p_slot) {return  m_off_commands[p_slot]->execute(); }
		String to_string()
		{
			std::ostringstream oss;
			oss << "\n------ Remote Control -------\n";
			for (size_t i = 0; i < m_on_commands.size(); ++i)
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

	private:
		String m_location;
	};

	class StereoOffCommand : public Command
	{
	public:
		StereoOffCommand(std::shared_ptr<Stereo> p_stereo)
		{
			m_stereo = p_stereo;
		}

		String execute() { return m_stereo->off(); }

	private:
		std::shared_ptr<Stereo> m_stereo;
	};

	class StereoOnWithCDCommand : public Command
	{
	public:
		StereoOnWithCDCommand(std::shared_ptr<Stereo> p_stereo)
		{
			m_stereo = p_stereo;
		}

		String execute()
		{
			std::ostringstream oss;
			oss << m_stereo->on();
			oss << m_stereo->set_cd();
			oss << m_stereo->set_volume(11);

			return oss.str();
		}

	private:
		std::shared_ptr<Stereo> m_stereo;
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
#endif // !REMOTE_H