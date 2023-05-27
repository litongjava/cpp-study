#include <switch.h>

SWITCH_MODULE_LOAD_FUNCTION(mod_baidutts_load);
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_baidutts_shutdown);

extern "C" {
SWITCH_MODULE_DEFINITION(mod_baidutts, mod_baidutts_load, mod_baidutts_shutdown, NULL)
;
}
;

SWITCH_MODULE_LOAD_FUNCTION(mod_baidutts) {
  switch_application_interface_t *app_interface;

  *module_interface = switch_loadable_module_create_module_interface(pool, modname);

  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "baidutts_load\n");

  return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_baidutts_shutdown) {
  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "baidutts_shutdown\n");
  return SWITCH_STATUS_SUCCESS;
}
