#include "options.h"

#include <glib.h>

#include <limits>
#include <stdexcept>

#include "wav_generator_defines.h"

static constexpr double kMinFrequencyHz = 20.0;
static constexpr double kMaxFrequencyHz = kSampleRateHz / 2.0;

static constexpr int kMaxLengthSeconds = std::numeric_limits<uint32_t>::max() / (kSampleRateHz * kBytesPerSample);

Options::Options(const int argc, char** argv) {
  ParseOptions(argc, argv);
}

void Options::ParseOptions(int argc, char** argv) {
  const GOptionEntry entries[] = {
    {"frequency", 'f', 0, G_OPTION_ARG_DOUBLE, &frequency_hz_, "Set the frequency in Hz (20 to 24000)", "FREQ"},
    {"length", 'l', 0, G_OPTION_ARG_INT, &length_s_, "Set the length in seconds (1 to 29826)", "LENGTH"},
    {nullptr}
  };

  GOptionContext* context = g_option_context_new("FILEPATH");
  g_option_context_add_main_entries(context, entries, nullptr);

  g_option_context_set_ignore_unknown_options(context, false);
  GError* error = nullptr;

  if (!g_option_context_parse(context, &argc, &argv, &error)) {
    g_option_context_free(context);
    throw std::runtime_error(error->message);
  }

  if (argc > 1) {
    output_filepath_ = argv[1];
  } else {
    throw std::runtime_error("An output filepath must be provided.\n");
  }

  if (frequency_hz_ == 0.0 || length_s_ <= 0) {
    g_option_context_free(context);
    throw std::runtime_error(std::string("--frequency and --length are mandatory"));
  }

  if (frequency_hz_ < kMinFrequencyHz || frequency_hz_ > kMaxFrequencyHz) {
    g_option_context_free(context);
    throw std::runtime_error(std::string("Frequency must be between ") + std::to_string(kMinFrequencyHz) +
                                         "Hz and " + std::to_string(kMaxFrequencyHz) + "Hz");
  }

  if (length_s_ > kMaxLengthSeconds) {
    g_option_context_free(context);
    throw std::runtime_error(std::string("Length must be less than ") + std::to_string(kMaxLengthSeconds) + " seconds");
  }

  g_option_context_free(context);
}
