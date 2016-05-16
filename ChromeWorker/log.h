#ifndef WORKER_LOG
#define WORKER_LOG

#include <string>

extern bool write_logs;

void worker_log_init(bool do_write);
void worker_log(const std::string& text);
void worker_log_thread();

#endif // LOG

