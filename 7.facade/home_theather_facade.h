#ifndef HOME_THEATHER_FACADE
#define HOME_THEATHER_FACADE
#include <string>
#include <memory>
#include <sstream>
namespace home_theather_facade
{
	using String = std::string;

	class Amplifier;

	class CdPlayer
	{
	public:
		CdPlayer(String p_description, std::shared_ptr<Amplifier> p_amplifier) : m_description(p_description),m_current_track(0), m_amplifier(p_amplifier) {}
		String get_description() { return m_description; }
		String on() { return m_description + " on\n"; }
		String off() { return m_description + " off\n"; }
		String eject()
		{
			m_title = "";
			return m_description + " eject\n";
		}

		String play(String p_title)
		{
			m_title = p_title;
			m_current_track = 0;
			return m_description + " playing \"" + m_title + "\"\n";
		}

		String play(int p_track)
		{
			if ("" == m_title)
			{
				return m_description + " can't play track " + std::to_string(m_current_track) + ", no cd inserted\n";
			}
			else
			{
				m_current_track = p_track;
				return m_description + " playing track " + std::to_string(m_current_track) + "\n";
			}
		}

		String stop()
		{
			m_current_track = 0;
			return m_description + " stopped\n";
		}

		String pause()
		{
			return m_description + " paused \"" + m_title + "\"\n";
		}

	private:
		String m_description;
		int m_current_track;
		std::shared_ptr<Amplifier> m_amplifier;
		String m_title;
	};

	class DvdPlayer
	{
	public:
		DvdPlayer(String p_description, std::shared_ptr<Amplifier> p_amplifier) : m_description(p_description), m_amplifier(p_amplifier) {}
		String get_description() { return m_description; }
		String on() { return m_description + " on\n"; }
		String off() { return m_description + " off\n"; }
		String eject()
		{
			m_movie = "";
			return m_description + " eject\n";
		}

		String play(String p_movie)
		{
			m_movie = p_movie;
			m_current_track = 0;
			return m_description + " playing \"" + m_movie + "\"\n";
		}

		String play(int p_track)
		{
			if (m_movie == "")
			{
				return m_description + " can't play track " + std::to_string(p_track) + " no m_dvd inserted\n";
			}
			else
			{
				m_current_track = p_track;
				return m_description + " playing track " + std::to_string(m_current_track) + " of \"" + m_movie + "\"\n";
			}
		}

		String stop()
		{
			m_current_track = 0;
			return m_description + " stopped \"" + m_movie + "\"\n";
		}

		String pause() { return m_description + " paused \"" + m_movie + "\"\n"; }
		String set_two_channel_audio() { return m_description + " set two channel audio\n"; }
		String set_surround_audio() { return m_description + " set surround audio\n"; }

	private:
		String m_description;
		int m_current_track;
		std::shared_ptr<Amplifier> m_amplifier;
		String m_movie;
	};

	class PopcornPopper
	{
	public:
		PopcornPopper(String p_description) : m_description(p_description) {}
		String get_description() { return m_description; }

		String on() { return m_description + " on\n"; }
		String off() { return m_description + " off\n"; }
		String pop() { return m_description + " popping popcorn!\n"; }

	private:
		String m_description;
	};

	class Projector
	{
	public:
		Projector(String p_description, std::shared_ptr<DvdPlayer> p_dvdPlayer) : m_description(p_description), m_dvd_player(p_dvdPlayer) {}
		String get_description() { return m_description; }
		String on() { return m_description + " on\n"; }
		String off() { return m_description + " off\n"; }
		String wide_screen_mode() { return m_description + " in widescreen mode (16x9 aspect ratio)\n"; }
		String tv_mode() { return m_description + " in tv mode (4x3 aspect ratio)\n"; }

	private:
		String m_description;
		std::shared_ptr<DvdPlayer> m_dvd_player;
	};

	class Screen
	{
	public:
		Screen(String p_description) : m_description(p_description) {}
		String up() { return m_description + " going up\n"; }
		String down() { return m_description + " going down\n"; }
		String get_description() { return m_description; }

	private:
		String m_description;
	};

	class TheaterLights
	{
	public:
		TheaterLights(String p_description) : m_description(p_description) {}
		String on() { return m_description + " on\n"; }
		String off() { return m_description + " off\n"; }
		String dim(int p_level) { return m_description + " dimming to " + std::to_string(p_level) + "%\n"; }
		String get_description() { return m_description; }

	private:
		String m_description;
	};

	class Tuner
	{
	public:
		Tuner(String p_description, std::shared_ptr<Amplifier>) : m_description(p_description) {}
		String on() { return m_description + " on\n"; }
		String off() { return m_description + " off\n"; }

		String set_frequency(double p_frequency)
		{
			m_frequency = p_frequency;
			return m_description + " setting frequency to " + std::to_string(m_frequency) + "\n";
		}

		String set_am() { return m_description + " setting AM mode\n"; }
		String set_fm() { return m_description + " setting FM mode\n"; }
		String get_description() { return m_description; }

	private:
		String m_description;
		double m_frequency;
	};

	class Amplifier
	{
	public:
		Amplifier(String p_description) : m_description(p_description) {}
		String get_description() { return m_description; }
		String on() { return m_description + " on\n"; }
		String off() { return m_description + " off\n"; }
		String set_stereo_sound() { return m_description + " stereo mode on\n"; }
		String set_surround_sound() { return m_description + " surround sound on (5 speakers, 1 subwoofer)\n"; }
		String set_volume(int p_level) { return m_description + " setting volume to " + std::to_string(p_level) + "\n"; }
		String set_tuner(std::shared_ptr<Tuner> p_tuner)
		{
			m_tuner = p_tuner;
			return m_description + " setting tuner to " + m_tuner->get_description() + "\n";
		}

		String set_dvd(std::shared_ptr<DvdPlayer> p_dvd)
		{
			m_dvd = p_dvd;
			return m_description + " setting DVD player to " + m_dvd->get_description() + "\n";
		}

		String set_cd(std::shared_ptr<CdPlayer> p_cd)
		{
			m_cd = p_cd;
			return m_description + " setting CD player to " + m_cd->get_description() + "\n";
		}

	private:
		String m_description;
		std::shared_ptr<Tuner> m_tuner;
		std::shared_ptr<DvdPlayer> m_dvd;
		std::shared_ptr<CdPlayer> m_cd;
	};

	class HomeTheaterFacade
	{
	public:
		HomeTheaterFacade(std::shared_ptr<Amplifier> p_amplifier, std::shared_ptr<Tuner> p_tuner, std::shared_ptr<DvdPlayer> p_dvd,
						  std::shared_ptr<CdPlayer> p_cd, std::shared_ptr<Projector> p_projector, std::shared_ptr<Screen> p_screen,
						  std::shared_ptr<TheaterLights> p_lights, std::shared_ptr<PopcornPopper> p_popper)
			: m_amplifier(p_amplifier), m_tuner(p_tuner), m_dvd(p_dvd),
			  m_cd(p_cd), m_projector(p_projector),
			  m_lights(p_lights), m_screen(p_screen), m_popper(p_popper) {}

		String watch_movie(String p_movie)
		{
			std::ostringstream watch_movie_string;

			watch_movie_string << "Get ready to watch a movie...\n";
			watch_movie_string << m_popper->on();
			watch_movie_string << m_popper->pop();
			watch_movie_string << m_lights->dim(10);
			watch_movie_string << m_screen->down();
			watch_movie_string << m_projector->on();
			watch_movie_string << m_projector->wide_screen_mode();
			watch_movie_string << m_amplifier->on();
			watch_movie_string << m_amplifier->set_dvd(m_dvd);
			watch_movie_string << m_amplifier->set_surround_sound();
			watch_movie_string << m_amplifier->set_volume(5);
			watch_movie_string << m_dvd->on();
			watch_movie_string << m_dvd->play(p_movie);

			return watch_movie_string.str();
		}

		String end_movie()
		{
			std::ostringstream end_movie_string;

			end_movie_string << "Shutting movie theater down...\n";
			end_movie_string << m_popper->off();
			end_movie_string << m_lights->on();
			end_movie_string << m_screen->up();
			end_movie_string << m_projector->off();
			end_movie_string << m_amplifier->off();
			end_movie_string << m_dvd->stop();
			end_movie_string << m_dvd->eject();
			end_movie_string << m_dvd->off();

			return end_movie_string.str();
		}

		String listen_to_cd(String p_cd_title)
		{
			std::ostringstream listen_to_cd_string;

			listen_to_cd_string << "Get ready for an audio experence...\n";
			listen_to_cd_string << m_lights->on();
			listen_to_cd_string << m_amplifier->on();
			listen_to_cd_string << m_amplifier->set_volume(5);
			listen_to_cd_string << m_amplifier->set_cd(m_cd);
			listen_to_cd_string << m_amplifier->set_stereo_sound();
			listen_to_cd_string << m_cd->on();
			listen_to_cd_string << m_cd->play(p_cd_title);

			return listen_to_cd_string.str();
		}

		String end_cd()
		{
			std::ostringstream end_cd_string;

			end_cd_string << "Shutting down CD...\n";
			end_cd_string << m_amplifier->off();
			end_cd_string << m_amplifier->set_cd(m_cd);
			end_cd_string << m_cd->eject();
			end_cd_string << m_cd->off();

			return end_cd_string.str();
		}

		String listen_to_radio(double p_frequency)
		{
			std::ostringstream listen_to_radio_string;

			listen_to_radio_string << "Tuning in the airwaves...\n";
			listen_to_radio_string << m_tuner->on();
			listen_to_radio_string << m_tuner->set_frequency(p_frequency);
			listen_to_radio_string << m_amplifier->on();
			listen_to_radio_string << m_amplifier->set_volume(5);
			listen_to_radio_string << m_amplifier->set_tuner(m_tuner);

			return listen_to_radio_string.str();
		}

		String end_radio()
		{
			std::ostringstream end_radio_string;

			end_radio_string << "Shutting down the tuner...\n";
			end_radio_string << m_tuner->off();
			end_radio_string << m_amplifier->off();

			return end_radio_string.str();
		}

	private:
		std::shared_ptr<Amplifier> m_amplifier;
		std::shared_ptr<Tuner> m_tuner;
		std::shared_ptr<DvdPlayer> m_dvd;
		std::shared_ptr<CdPlayer> m_cd;
		std::shared_ptr<Projector> m_projector;
		std::shared_ptr<TheaterLights> m_lights;
		std::shared_ptr<Screen> m_screen;
		std::shared_ptr<PopcornPopper> m_popper;
	};

}
#endif // !HOME_THEATHER_FACADE