#ifndef WORKER_LOG
#define WORKER_LOG

#include <string>

extern bool write_logs;

void worker_log_init(bool do_write);
void network_log(const std::string& text);
void worker_log(const std::string& text);
void worker_log_thread();
bool is_write_logs();

#define WORKER_LOG(text) if(is_write_logs())worker_log(text);
#define NETWORK_LOG(text) if(is_write_logs())network_log(text);


#endif // LOG

