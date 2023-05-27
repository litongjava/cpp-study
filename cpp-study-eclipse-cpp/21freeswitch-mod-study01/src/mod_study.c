#include <switch.h>

SWITCH_MODULE_LOAD_FUNCTION(mod_study_load);
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_study_shutdown);

SWITCH_MODULE_DEFINITION(mod_study, mod_study_load, mod_study_shutdown, NULL);

SWITCH_STANDARD_APP(start_study_session_function) {
  switch_channel_t *channel = switch_core_session_get_channel(session);
  char* channel_name = switch_channel_get_name(channel);
  char* channel_uuid = switch_channel_get_uuid(channel);

  switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(session), SWITCH_LOG_DEBUG, "%s %s Start study\n", channel_name,
      channel_uuid);
}

SWITCH_STANDARD_APP(stop_study_session_function) {
  switch_channel_t *channel = switch_core_session_get_channel(session);
  char* channel_name = switch_channel_get_name(channel);
  char* channel_uuid = switch_channel_get_uuid(channel);
  switch_log_printf(SWITCH_CHANNEL_SESSION_LOG(session), SWITCH_LOG_DEBUG, "%s %s Stop study\n", channel_name,
      channel_uuid);
}

SWITCH_MODULE_LOAD_FUNCTION(mod_study_load) {
  switch_application_interface_t *app_interface;

  *module_interface = switch_loadable_module_create_module_interface(pool, modname);

  SWITCH_ADD_APP(app_interface, "start_study", "study", "study", start_study_session_function, "", SAF_MEDIA_TAP);
  SWITCH_ADD_APP(app_interface, "stop_study", "study", "study", stop_study_session_function, "", SAF_NONE);

  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "study_load\n");

  return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_study_shutdown) {
  switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_DEBUG, "study_shutdown\n");
  return SWITCH_STATUS_SUCCESS;
}
