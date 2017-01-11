//
//
//#include "arpterm/pty_handler.hpp"
//#include "arpterm/util/fcntl.hpp"
//#include "arpterm/util/errno.hpp"
//#include "arpterm/util/unistd.hpp"
//#include "arpterm/util/termios.hpp"
//#include "arpterm/util/wait.hpp"
//#include "arpterm/util/hash_map.hpp"
//
//
//#include <cstring>
//#include <cstdlib>
//#include <csignal>
//
//namespace ap = arpterm::pty;
//namespace au = arpterm::util;
//
//typedef int fd_t; // filedescriptor_type
//
//typedef struct {
//	fd_t master_fd;
//	pid_t pid;
//} thread_list_elem_t;
//
////using thread_list_elem_t = std::pair<fd_t, pid_t>;
//
//#define ARPTERM_MAX_THREAD_NUM 1024
////----------------------------------------------------------------------------//
//static au::hash_map<fd_t, pid_t, ARPTERM_MAX_THREAD_NUM> thread_list_;
//
//static std::array<fd_t, ARPTERM_MAX_THREAD_NUM> thread_free_list_;
////-----------------------------------------------------------------------------//
//inline void err_exit(const char* errmsg) {
//	perror(errmsg);
//	exit(1);
//}
////-----------------------------------------------------------------------------//
//inline void errno_save_n_close(fd_t fd) {
//	int saved_errno = errno;
//	close(fd);
//	errno = saved_errno;
//}
////-----------------------------------------------------------------------------//
//static int pty_open() {
//
//	int master_fd = posix_openpt(O_RDWR | O_NOCTTY);
//	if (master_fd == -1) {
//		return -1;
//	}
//
//	if (grantpt(master_fd) == -1) {
//		errno_save_n_close(master_fd);
//		return -1;
//	}
//
//	if (unlockpt(master_fd) == -1) {
//		errno_save_n_close(master_fd);
//		return -1;
//	}
//	return master_fd;
//}
////-----------------------------------------------------------------------------//
//static int get_pts(fd_t master_fd, char* slave_name, size_t sn_len) {
//	char* p = ptsname(master_fd);
//	if (p == nullptr) {
//		errno_save_n_close(master_fd);
//		return -1;
//	}
//	if (strlen(p) < sn_len) {
//		strncpy(slave_name, p, sn_len);
//	} else {
//		close(master_fd);
//		errno = EOVERFLOW;
//		return -1;
//	}
//	return 0;
//}
////-----------------------------------------------------------------------------//
//static void sighup_trap(int sig) {
//	printf("CHILD CHACHED SIGHUP");
//	exit(0);
//}
////-----------------------------------------------------------------------------//
//static int start_new_slave_thread(fd_t master_fd, const char* slave_name, size_t slave_len, struct termios* term) {
//
//	int sid = setsid();
//	if (sid == -1) {
//		err_exit("setsid");
//	}
//	printf("sid: %d\n", sid);
//	close(master_fd);
//	int slave_fd = open(slave_name, O_RDWR);
//	/**
//	 *  termios an winsize is needed for dunno */
//	const struct termios* termios = term;
//	tcsetattr(slave_fd, TCSANOW, term);
//	const struct winsize* slave_ws = nullptr;
//
//	if (dup2(slave_fd, STDIN_FILENO) != STDIN_FILENO) {
//		err_exit("dup_stdin");
//	}
//	if (dup2(slave_fd, STDOUT_FILENO) != STDOUT_FILENO) {
//		err_exit("dup_stdout");
//	}
//	if (dup2(slave_fd, STDERR_FILENO) != STDERR_FILENO) {
//		err_exit("dup_sterr");
//	}
//
//	signal(SIGTERM, &sighup_trap);
//
//	char* args[] = { "/bin/bash", NULL };
//	execv("/bin/bash", args);
//	printf("ENDED BASH_SESSION\n");
//	close(slave_fd); 
//	return 0;
//
//}
////-----------------------------------------------------------------------------//
//int ap::start_pt_master_slave() {
//
//	int master_fd = pty_open();
//	struct termios* term = (struct termios*)malloc(sizeof(struct termios));
//	tcgetattr(master_fd, term);
//
//	if (master_fd == -1) {
//		return -1;
//	}
//	char slave_name[100];
//	int err = get_pts(master_fd, slave_name, sizeof(slave_name));
//	if (err == -1) {
//		err_exit("get_pts");
//	}
//	int pid = fork();
//	if (pid == 0) { // child
//		start_new_slave_thread(master_fd, slave_name, sizeof(slave_name),  term);
//		return 0;
//	} else if (pid > 0) {
//		printf("slave_pid: %d\n", pid);
//		if (-1 == thread_list_.set(master_fd, pid)) {
//			throw std::runtime_error("No more slot for threads");
//		}
//	} else {
//		err_exit("failed to fork");
//	}
//
//
//	return master_fd;
//}
////-----------------------------------------------------------------------------//
//int ap::stop_all() {
//	for (int i = 0; i < ARPTERM_MAX_THREAD_NUM; i++) {
//		const auto& elem = thread_list_[i];
//		if (pid > 0) {
//			waitpid(pid,nullptr, 0);
//		}
//	}
//}
////-----------------------------------------------------------------------------//
//static thread_list_elem_pair*
//get_pair_by_master_fd(fd_t master_fd) {
//	for (int i = 0; i < ARPTERM_MAX_THREAD_NUM; i++) {
//		auto* elem = &(thread_list_[i]);
//		if (elem->master_fd == master_fd) {
//			return pair;
//		}
//	}
//	return nullptr;
//}
////-----------------------------------------------------------------------------//
//// waits for the pid with master_fd to terminate
//int ap::stop_pty(fd_t master_fd) {
//	auto ptr = get_elem_by_master_fd(master_fd);
//	if (ptr == nullptr) {
//		return -1;
//	}
//	if (ptr->pid < 0) {
//		return -1;
//	}
//	waitpid(ptr->pid, nullptr, 0);
//	ptr->master_fd = 0;
//	ptr->pid = 0;
//	return 0;
//}
//
//
