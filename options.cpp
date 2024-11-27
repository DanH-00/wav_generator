#include "options.h"

#include <glib.h>
#include <stdexcept>

Options::Options(const int argc, char** argv) {
  ParseOptions(argc, argv);
}

void Options::ParseOptions(int argc, char** argv) {
  const GOptionEntry entries[] = {
    {"frequency", 'f', 0, G_OPTION_ARG_DOUBLE, &frequency_hz_, "Set the frequency in Hz", "FREQ"},
    {"length", 'l', 0, G_OPTION_ARG_INT, &length_s_, "Set the length in secons", "LENGTH"},
    {nullptr}
  };

  GOptionContext* context = g_option_context_new("FILEPATH");
  g_option_context_add_main_entries(context, entries, nullptr);

  char **rest = nullptr;
  g_option_context_set_ignore_unknown_options(context, false);

  GError* error = nullptr;

  if (!g_option_context_parse(context, &argc, &argv, &error)) {
    g_option_context_free(context);
    throw std::runtime_error(error->message);
  }

  rest = argv + 1;

  if (argc > 1) {
    output_filepath_ = argv[1];
  } else {
    throw std::runtime_error("An output filepath must be provided.\n");
  }

  // TODO DH Range check frequency_hz_
  if (frequency_hz_ == 0.0 || length_s_ <= 0) {
    g_option_context_free(context);
    throw std::runtime_error(std::string("--frequency and --length are mandatory"));
  }

  g_option_context_free(context);
}
