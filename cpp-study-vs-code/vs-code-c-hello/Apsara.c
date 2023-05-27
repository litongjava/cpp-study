//Created at 2009-02-19 by Apsara
/** Initialize logging system
 * Load log level and sink from config file
 * If the file could not be found,use default setting.
 * Throw exception if failed.
 */
void initLoggingSystem(const std::String&configFile="");

/** Uninitialize the logging system.Flush the buffered log if there is any.
 * Throw exceptions if failed
 */
void UninitLoggingSystem();