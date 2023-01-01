#ifndef REMOTE_CONTROL_COMMAND_H
#define REMOTE_CONTROL_COMMAND_H
#include <string>
#include <sstream>
#include <memory>
#include <vector>

namespace remote_control_command
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

		CeilingFan(String p_location) : m_location(p_location), p_level(Speed::OFF) {}

		String high()
		{
			// turns the ceiling fan on to high
			p_level = Speed::HIGH;
			return m_location + " ceiling fan is on high";
		}

		String medium()
		{
			// turns the ceiling fan on to medium
			p_level = Speed::MEDIUM;
			return m_location + " ceiling fan is on medium";
		}

		String low()
		{
			// turns the ceiling fan on to low
			p_level = Speed::LOW;
			return m_location + " ceiling fan is on low";
		}

		String off()
		{
			// turns the ceiling fan off
			p_level = Speed::OFF;
			return m_location + " ceiling fan is off";
		}

		Speed get_speed() const { return p_level; }

	private:
		String m_location;
		Speed p_level;
	};

	class GarageDoor
	{
	public:
		GarageDoor(String p_location) : m_location(p_location) {}

		String up() { return "Garage door is up"; }
		String down() { return "Garage door is down"; }
		String stop() { return "Garage door movement is stopped"; }
		String light_on() { return "Garage door light is on"; }
		String light_off() { return "Garage door light is off"; }

	private:
		String m_location;
	};

	class Hottub
	{
	public:
		Hottub() {}
		String on()
		{
			m_is_on = true;
			return "on";
		}
		String off()
		{
			m_is_on = false;
			return "off";
		}

		String bubbles_on() { return m_is_on ? "Hottub is bubbling!" : ""; }
		String bubbles_off() { return !m_is_on ? "Hottub is not bubbling!" : ""; }
		String jets_on() { return m_is_on ? "Hottub jets are on" : ""; }
		String jets_off() { return !m_is_on ? "Hottub jets are off" : ""; }

		int set_temperature(int p_temperature)
		{
			m_temperature = p_temperature;
			return m_temperature;
		}

		String heat()
		{
			m_temperature = 105;
			return "Hottub is heating to a steaming 105 degrees";
		}

		String cool()
		{
			m_temperature = 98;
			return "Hottub is cooling to 98 degrees";
		}

	private:
		bool m_is_on;
		int m_temperature;
	};

	class Remote
	{
	public:
		const int MAX_COMMANDS = 7;
		Remote() : m_on_commands(MAX_COMMANDS), m_off_commands(MAX_COMMANDS)
		{
			std::shared_ptr<Command> no_command = std::make_shared<NoCommand>();
			for (int i = 0; i < MAX_COMMANDS; ++i)
			{
				m_on_commands[i] = no_command;
				m_off_commands[i] = no_command;
			}
		}

		void set_command(int p_slot, std::shared_ptr<Command> p_on_command, std::shared_ptr<Command> p_off_command)
		{
			m_on_commands[p_slot] = p_on_command;
			m_off_commands[p_slot] = p_off_command;
		}

		String on_button_was_pushed(int p_slot) { return m_on_commands[p_slot]->execute(); }
		String off_button_was_pushed(int p_slot) { return m_off_commands[p_slot]->execute(); }

		String to_string()
		{
			std::ostringstream oss;
			oss << "\n------ Remote Control -------\n";
			for (int i = 0; i < m_on_commands.size(); ++i)
			{
				oss << "[m_slot " << i << "] " << typeid(m_on_commands[i]).name() << "    " << typeid(m_off_commands[i]).name() << "\n";
			}
			return oss.str();
		}

	private:
		std::vector<std::shared_ptr<Command>> m_on_commands;
		std::vector<std::shared_ptr<Command>> m_off_commands;
	};

	class SimpleRemoteControl
	{
	public:
		SimpleRemoteControl() {}
		std::shared_ptr<Command> set_command(std::shared_ptr<Command> p_command)
		{
			m_slot = p_command;
			return m_slot;
		}

		String button_was_pressed() { return m_slot->execute(); }

	private:
		std::shared_ptr<Command> m_slot;
	};

	class Stereo
	{
	public:
		Stereo(String p_location) : m_location(p_location) {}

		String on() { return m_location + " m_stereo is on"; }
		String off() { return m_location + " m_stereo is off"; }
		String set_cd() { return m_location + " m_stereo is set for CD input"; }
		String set_dvd() { return m_location + " m_stereo is set for DVD input"; }
		String set_radio() { return m_location + " m_stereo is set for Radio"; }
		// code to set the volume
		// valid range: 1-11 (after all 11 is better than 10, right?)
		String set_volume(int p_volume) { return m_location + " Stereo volume set to " + std::to_string(p_volume); }

	private:
		String m_location;
	};

	class Light
	{
	public:
		Light(String p_location) : m_location(p_location) {}
		String on() { return m_location + " light is on"; }
		String off() { return m_location + " light is off"; }

	private:
		String m_location;
	};

	class CeilingFanOffCommand : public Command
	{
	public:
		CeilingFanOffCommand(std::shared_ptr<CeilingFan> p_ceiling_fan) : m_ceiling_fan(p_ceiling_fan) {}
		String execute() { return m_ceiling_fan->off(); }

	private:
		std::shared_ptr<CeilingFan> m_ceiling_fan;
	};

	class CeilingFanOnCommand : public Command
	{
	public:
		CeilingFanOnCommand(std::shared_ptr<CeilingFan> p_ceiling_fan) : m_ceiling_fan(p_ceiling_fan) {}
		String execute() { return m_ceiling_fan->high(); }

	private:
		std::shared_ptr<CeilingFan> m_ceiling_fan;
	};

	class GarageDoorDownCommand : public Command
	{
	public:
		GarageDoorDownCommand(std::shared_ptr<GarageDoor> p_garage_door) : m_garage_door(p_garage_door) {}
		String execute() { return m_garage_door->down(); }

	private:
		std::shared_ptr<GarageDoor> m_garage_door;
	};

	class GarageDoorUpCommand : public Command
	{
	public:
		GarageDoorUpCommand(std::shared_ptr<GarageDoor> p_garage_door) : m_garage_door(p_garage_door) {}
		String execute() { return m_garage_door->up(); }

	private:
		std::shared_ptr<GarageDoor> m_garage_door;
	};

	class HottubOffCommand : public Command
	{
	public:
		HottubOffCommand(std::shared_ptr<Hottub> p_hottub) : m_hottub(p_hottub) {}
		String execute() { return m_hottub->off(); }

	private:
		std::shared_ptr<Hottub> m_hottub;
	};

	class HottubOnCommand : public Command
	{
	public:
		HottubOnCommand(std::shared_ptr<Hottub> p_hottub) : m_hottub(p_hottub) {}
		String execute()
		{
			return m_hottub->on() +
				   "\n" + m_hottub->heat() +
				   "\n" + m_hottub->bubbles_on();
		}

	private:
		std::shared_ptr<Hottub> m_hottub;
	};

	class LightOffCommand : public Command
	{
	public:
		LightOffCommand(std::shared_ptr<Light> p_light) : m_light(p_light) {}
		String execute() { return m_light->off(); }

	private:
		std::shared_ptr<Light> m_light;
	};

	class LightOnCommand : public Command
	{
	public:
		LightOnCommand(std::shared_ptr<Light> p_light) : m_light(p_light) {}
		String execute() { return m_light->on(); }

	private:
		std::shared_ptr<Light> m_light;
	};

	class LivingroomLightOffCommand : public Command
	{
	public:
		LivingroomLightOffCommand(std::shared_ptr<Light> p_light) : m_light(p_light) {}
		String execute() { return m_light->off(); }

	private:
		std::shared_ptr<Light> m_light;
	};

	class LivingroomLightOnCommand : public Command
	{
	public:
		LivingroomLightOnCommand(std::shared_ptr<Light> p_light) : m_light(p_light) {}
		String execute() { return m_light->on(); }

	private:
		std::shared_ptr<Light> m_light;
	};

	class NoCommand : public Command
	{
	public:
		NoCommand() {}
		String execute() { return ""; }
	};

	class StereoOffCommand : public Command
	{
	public:
		StereoOffCommand(std::shared_ptr<Stereo> p_stereo) : m_stereo(p_stereo) {}
		String execute() { return m_stereo->off(); }

	private:
		std::shared_ptr<Stereo> m_stereo;
	};

	class StereoOnWithCDCommand : public Command
	{
	public:
		StereoOnWithCDCommand(std::shared_ptr<Stereo> p_stereo) : m_stereo(p_stereo) {}
		String execute() { return m_stereo->on() + "\n" + m_stereo->set_cd() + "\n" + m_stereo->set_volume(11); }

	private:
		std::shared_ptr<Stereo> m_stereo;
	};

}
#endif // !REMOTE_CONTROL_COMMAND_H