#include "home_theather_facade.h"

#include "Catch.hpp"

using namespace home_theather_facade;

TEST_CASE("FacadeHomeTheaterFixture", "[]")
{
    std::shared_ptr<Amplifier> amp = std::make_shared<Amplifier>("Top-O-Line Amplifier");
    std::shared_ptr<Tuner> tuner = std::make_shared<Tuner>("Top-O-Line Tuner", amp);
    std::shared_ptr<DvdPlayer> dvd = std::make_shared<DvdPlayer>("Top-O-Line DVD Player", amp);
    std::shared_ptr<CdPlayer> cd = std::make_shared<CdPlayer>("Top-O-Line CD Player", amp);
    std::shared_ptr<Projector> projector = std::make_shared<Projector>("Top-O-Line Projector", dvd);
    std::shared_ptr<TheaterLights> lights = std::make_shared<TheaterLights>("Theater Ceiling Lights");
    std::shared_ptr<Screen> screen = std::make_shared<Screen>("Theater Screen");
    std::shared_ptr<PopcornPopper> popper = std::make_shared<PopcornPopper>("Popcorn Popper");
    std::shared_ptr<HomeTheaterFacade> homeTheater = std::make_shared<HomeTheaterFacade>(amp, tuner, dvd, cd, projector, screen, lights, popper);
    std::ostringstream expected_watch_movie_output;
    std::ostringstream expected_end_movie_output;
    std::ostringstream expected_listen_to_cd_output;
    std::ostringstream expected_end_cd_output;
    std::ostringstream expected_listen_to_radio_output;
    std::ostringstream expected_end_radio_output;

    SECTION("TestHomeTheaterMovie")
    {
        expected_watch_movie_output << "Get ready to watch a movie...\n";
        expected_watch_movie_output << "Popcorn Popper on\n";
        expected_watch_movie_output << "Popcorn Popper popping popcorn!\n";
        expected_watch_movie_output << "Theater Ceiling Lights dimming to 10%\n";
        expected_watch_movie_output << "Theater Screen going down\n";
        expected_watch_movie_output << "Top-O-Line Projector on\n";
        expected_watch_movie_output << "Top-O-Line Projector in widescreen mode (16x9 aspect ratio)\n";
        expected_watch_movie_output << "Top-O-Line Amplifier on\n";
        expected_watch_movie_output << "Top-O-Line Amplifier setting DVD player to Top-O-Line DVD Player\n";
        expected_watch_movie_output << "Top-O-Line Amplifier surround sound on (5 speakers, 1 subwoofer)\n";
        expected_watch_movie_output << "Top-O-Line Amplifier setting volume to 5\n";
        expected_watch_movie_output << "Top-O-Line DVD Player on\n";
        expected_watch_movie_output << "Top-O-Line DVD Player playing \"Toy Story\"\n";

        expected_end_movie_output << "Shutting movie theater down...\n";
        expected_end_movie_output << "Popcorn Popper off\n";
        expected_end_movie_output << "Theater Ceiling Lights on\n";
        expected_end_movie_output << "Theater Screen going up\n";
        expected_end_movie_output << "Top-O-Line Projector off\n";
        expected_end_movie_output << "Top-O-Line Amplifier off\n";
        expected_end_movie_output << "Top-O-Line DVD Player stopped \"Toy Story\"\n";
        expected_end_movie_output << "Top-O-Line DVD Player eject\n";
        expected_end_movie_output << "Top-O-Line DVD Player off\n";

        REQUIRE(expected_watch_movie_output.str() == homeTheater->watch_movie("Toy Story"));
        REQUIRE(expected_end_movie_output.str() == homeTheater->end_movie());
    }

    SECTION("TestHomeTheaterMovie")
    {
        expected_listen_to_cd_output << "Get ready for an audio experence...\n";
        expected_listen_to_cd_output << "Theater Ceiling Lights on\n";
        expected_listen_to_cd_output << "Top-O-Line Amplifier on\n";
        expected_listen_to_cd_output << "Top-O-Line Amplifier setting volume to 5\n";
        expected_listen_to_cd_output << "Top-O-Line Amplifier setting CD player to Top-O-Line CD Player\n";
        expected_listen_to_cd_output << "Top-O-Line Amplifier stereo mode on\n";
        expected_listen_to_cd_output << "Top-O-Line CD Player on\n";
        expected_listen_to_cd_output << "Top-O-Line CD Player playing \"Dark Side of the Moon\"\n";

        expected_end_cd_output << "Shutting down CD...\n";
        expected_end_cd_output << "Top-O-Line Amplifier off\n";
        expected_end_cd_output << "Top-O-Line Amplifier setting CD player to Top-O-Line CD Player\n";
        expected_end_cd_output << "Top-O-Line CD Player eject\n";
        expected_end_cd_output << "Top-O-Line CD Player off\n";

        REQUIRE(expected_listen_to_cd_output.str() == homeTheater->listen_to_cd("Dark Side of the Moon"));
        REQUIRE(expected_end_cd_output.str() == homeTheater->end_cd());
    }

    SECTION("TestHomeTheaterRadio")
    {
        expected_listen_to_radio_output << "Tuning in the airwaves...\n";
        expected_listen_to_radio_output << "Top-O-Line Tuner on\n";
        expected_listen_to_radio_output << "Top-O-Line Tuner setting frequency to 92.500000\n";
        expected_listen_to_radio_output << "Top-O-Line Amplifier on\n";
        expected_listen_to_radio_output << "Top-O-Line Amplifier setting volume to 5\n";
        expected_listen_to_radio_output << "Top-O-Line Amplifier setting tuner to Top-O-Line Tuner\n";

        expected_end_radio_output << "Shutting down the tuner...\n";
        expected_end_radio_output << "Top-O-Line Tuner off\n";
        expected_end_radio_output << "Top-O-Line Amplifier off\n";

        REQUIRE(expected_listen_to_radio_output.str() == homeTheater->listen_to_radio(92.5));
        REQUIRE(expected_end_radio_output.str() == homeTheater->end_radio());
    }
}