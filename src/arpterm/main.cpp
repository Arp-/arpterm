

#include <gtkmm.h>
#include "arpterm/main_window.hpp"

int main(int argc, char *argv[])
{
  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

	arpterm::MainWindow window;
  window.set_default_size(800, 600);

  return app->run(window);
}

