#ifndef UNDO_H
#define UNDO_H
#include <string>
#include <vector>
#include <memory>
#include <sstream>

namespace undo
{
	using String = std::string;

	class Command
	{
	public:
		virtual String execute() = 0;
		virtual String undo() = 0;
	};

	class Light
	{
	public:
		Light(String p_location)
		{
			m_location = p_location;
		}

		String on()
		{
			m_level = 100;
			return "Light is on";
		}

		String off()
		{
			m_level = 0;
			return "Light is off";
		}

		String dim(int p_level)
		{
			m_level = p_level;
			if (m_level == 0)
			{
				off();
			}
			return "Light is dimmed to " + std::to_string(m_level) + "%";
		}

		int getLevel()
		{
			return m_level;
		}

	private:
		String m_location;
		int m_level;
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

		CeilingFan(String p_location)
		{
			m_location = p_location;
			m_speed = Speed::OFF;
		}

		String high()
		{
			m_speed = Speed::HIGH;
			return m_location + " ceiling fan is on high";
		}

		String medium()
		{
			m_speed = Speed::MEDIUM;
			return m_location + " ceiling fan is on medium";
		}

		String low()
		{
			m_speed = Speed::LOW;
			return m_location + " ceiling fan is on low";
		}

		String off()
		{
			m_speed = Speed::OFF;
			return m_location + " ceiling fan is off";
		}

		Speed get_speed()
		{
			return m_speed;
		}

	private:
		String m_location;
		CeilingFan::Speed m_speed;
	};

	class RemoteControlWithUndo
	{
	public:
		RemoteControlWithUndo() : MAX_COMMANDS(7), m_on_commands(MAX_COMMANDS), m_off_commands(MAX_COMMANDS)
		{
			for (int i = 0; i < MAX_COMMANDS; ++i)
			{
				m_on_commands[i] = std::make_shared<NoCommand>();
				m_off_commands[i] = std::make_shared<NoCommand>();
			}
			m_undo_command = std::make_shared<NoCommand>();
		}

		void set_command(int p_slot, std::shared_ptr<Command> on_command, std::shared_ptr<Command> off_command)
		{
			m_on_commands[p_slot] = on_command;
			m_off_commands[p_slot] = off_command;
		}

		void on_button_was_pushed(int p_slot)
		{
			m_on_commands[p_slot]->execute();
			m_undo_command = m_on_commands[p_slot];
		}

		void off_button_was_pushed(int p_slot)
		{
			m_off_commands[p_slot]->execute();
			m_undo_command = m_off_commands[p_slot];
		}

		void undo_button_was_pushed()
		{
			m_undo_command->undo();
		}

		String to_string()
		{
			std::ostringstream oss;
			oss << "\n------ Remote Control -------\n";
			for (size_t i = 0; i < m_on_commands.size(); ++i)
			{
				oss << "[p_slot " << i << "] " << typeid(m_on_commands[i]).name() << "    " << typeid(m_off_commands[i]).name() << "\n";
			}
			oss << "[undo] " << typeid(m_undo_command).name() << "\n";
			return oss.str();
		}

	private:
		const int MAX_COMMANDS;
		std::vector<std::shared_ptr<Command>> m_on_commands;
		std::vector<std::shared_ptr<Command>> m_off_commands;
		std::shared_ptr<Command> m_undo_command;
	};
	class CeilingFanHighCommand : public Command
	{
	public:
		CeilingFanHighCommand(std::shared_ptr<CeilingFan> p_ceiling_fan)
		{
			m_ceiling_fan = p_ceiling_fan;
		}

		String execute()
		{
			m_prev_speed = m_ceiling_fan->get_speed();
			return m_ceiling_fan->high();
		}

		String undo()
		{
			switch (m_prev_speed)
			{
			case CeilingFan::Speed::HIGH:
				return m_ceiling_fan->high();
			case CeilingFan::Speed::MEDIUM:
				return m_ceiling_fan->medium();
			case CeilingFan::Speed::LOW:
				return m_ceiling_fan->low();
			case CeilingFan::Speed::OFF:
				return m_ceiling_fan->off();
			default:
				break;
			}

			return "";
		}

	private:
		std::shared_ptr<CeilingFan> m_ceiling_fan;
		CeilingFan::Speed m_prev_speed;
	};

	class CeilingFanLowCommand : public Command
	{
	public:
		CeilingFanLowCommand(std::shared_ptr<CeilingFan> p_ceiling_fan)
		{
			m_ceiling_fan = p_ceiling_fan;
		}

		String execute()
		{
			m_prev_speed = m_ceiling_fan->get_speed();
			return m_ceiling_fan->low();
		}

		String undo()
		{
			switch (m_prev_speed)
			{
			case CeilingFan::Speed::HIGH:
				return m_ceiling_fan->high();
			case CeilingFan::Speed::MEDIUM:
				return m_ceiling_fan->medium();
			case CeilingFan::Speed::LOW:
				return m_ceiling_fan->low();
			case CeilingFan::Speed::OFF:
				return m_ceiling_fan->off();
			default:
				break;
			}
		}

	private:
		std::shared_ptr<CeilingFan> m_ceiling_fan;
		CeilingFan::Speed m_prev_speed;
	};

	class CeilingFanMediumCommand : public Command
	{
	public:
		CeilingFanMediumCommand(std::shared_ptr<CeilingFan> p_ceiling_fan)
		{
			m_ceiling_fan = p_ceiling_fan;
		}

		String execute()
		{
			m_prev_speed = m_ceiling_fan->get_speed();
			return m_ceiling_fan->medium();
		}

		String undo()
		{
			switch (m_prev_speed)
			{
			case CeilingFan::Speed::HIGH:
				return m_ceiling_fan->high();
			case CeilingFan::Speed::MEDIUM:
				return m_ceiling_fan->medium();
			case CeilingFan::Speed::LOW:
				return m_ceiling_fan->low();
			case CeilingFan::Speed::OFF:
				return m_ceiling_fan->off();
			default:
				break;
			}

			return "";
		}

	private:
		std::shared_ptr<CeilingFan> m_ceiling_fan;
		CeilingFan::Speed m_prev_speed;
	};

	class CeilingFanOffCommand : public Command
	{
	public:
		CeilingFanOffCommand(std::shared_ptr<CeilingFan> p_ceiling_fan)
		{
			m_ceiling_fan = p_ceiling_fan;
		}

		String execute()
		{
			m_prev_speed = m_ceiling_fan->get_speed();
			return m_ceiling_fan->off();
		}

		String undo()
		{
			switch (m_prev_speed)
			{
			case CeilingFan::Speed::HIGH:
				return m_ceiling_fan->high();
			case CeilingFan::Speed::MEDIUM:
				return m_ceiling_fan->medium();
			case CeilingFan::Speed::LOW:
				return m_ceiling_fan->low();
			case CeilingFan::Speed::OFF:
				return m_ceiling_fan->off();
			default:
				break;
			}
			return "";
		}

	private:
		std::shared_ptr<CeilingFan> m_ceiling_fan;
		CeilingFan::Speed m_prev_speed;
	};

	class DimmerLightOffCommand : public Command
	{
	public:
		DimmerLightOffCommand(std::shared_ptr<Light> p_light)
		{
			m_light = p_light;
			m_prev_level = 100;
		}

		String execute()
		{
			m_prev_level = m_light->getLevel();
			return m_light->off();
		}

		String undo()
		{
			return m_light->dim(m_prev_level);
		}

	private:
		std::shared_ptr<Light> m_light;
		int m_prev_level;
	};

	class DimmerLightOnCommand : public Command
	{
	public:
		DimmerLightOnCommand(std::shared_ptr<Light> p_light)
		{
			m_light = p_light;
		}

		String execute()
		{
			m_prev_level = m_light->getLevel();
			return m_light->dim(75);
		}

		String undo()
		{
			return m_light->dim(m_prev_level);
		}

	private:
		std::shared_ptr<Light> m_light;
		int m_prev_level;
	};

	class LightOffCommand : public Command
	{
	public:
		LightOffCommand(std::shared_ptr<Light> p_light)
		{
			m_light = p_light;
		}

		String execute()
		{
			m_level = m_light->getLevel();
			return m_light->off();
		}

		String undo()
		{
			return m_light->dim(m_level);
		}

	private:
		std::shared_ptr<Light> m_light;
		int m_level;
	};

	class LightOnCommand : public Command
	{
	public:
		LightOnCommand(std::shared_ptr<Light> p_light)
		{
			m_light = p_light;
		}

		String execute()
		{
			m_level = m_light->getLevel();
			return m_light->on();
		}

		String undo()
		{
			return m_light->dim(m_level);
		}

	public:
		std::shared_ptr<Light> m_light;
		int m_level;
	};

	class NoCommand : public Command
	{
		String execute() { return ""; }
		String undo() { return ""; }
	};
}
#endif // !UNDO_H