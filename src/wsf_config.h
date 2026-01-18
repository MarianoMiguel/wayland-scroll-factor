#ifndef WSF_CONFIG_H
#define WSF_CONFIG_H

#include <stdbool.h>

#define WSF_FACTOR_DEFAULT 1.0
#define WSF_FACTOR_MIN 0.05
#define WSF_FACTOR_MAX 5.0

struct wsf_config_values {
	double factor;
	double scroll_vertical_factor;
	double scroll_horizontal_factor;
	double pinch_zoom_factor;
	double pinch_rotate_factor;
	bool has_factor;
	bool has_scroll_vertical;
	bool has_scroll_horizontal;
	bool has_pinch_zoom;
	bool has_pinch_rotate;
};

struct wsf_effective_factors {
	double scroll_vertical;
	double scroll_horizontal;
	double pinch_zoom;
	double pinch_rotate;
	bool used_legacy_factor;
};

enum wsf_config_status {
	WSF_CONFIG_OK = 0,
	WSF_CONFIG_MISSING = 1,
	WSF_CONFIG_INVALID = 2,
	WSF_CONFIG_ERROR = 3
};

bool wsf_debug_enabled(void);
const char *wsf_config_path(void);
void wsf_config_values_init(struct wsf_config_values *values);
int wsf_config_read(struct wsf_config_values *out_values, bool debug);
int wsf_effective_factors(struct wsf_effective_factors *out_factors, bool debug);
int wsf_config_write(double factor, bool debug);
int wsf_config_write_updates(const struct wsf_config_values *updates, bool debug);

#endif
