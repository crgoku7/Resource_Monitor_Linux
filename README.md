# Resource_Monitor_Linux
A GUI based resource monitor for linux developed in C++.

The implementation makes use of the [**/proc**](https://man7.org/linux/man-pages/man5/proc.5.html) filesystem to obtain kernel & system information.
## Features in the Resource Monitor
 - **CPU Usage Monitoring**
   
    Display real-time CPU utilization statistics for individual CPUs in the system and overall system usage.
- **Processes Information**
  
    Monitor active processes, including their memory usage. Provide ability to kill selected active processes.
- **Memory Usage Monitoring**
  
    Report on total, used, and free memory in the system.
- **Network Activity Monitoring**
  
    Track the amount of data being sent and recieved.

## Use of /proc filesystem
The /proc filesystem is a pseudo-filesystem which provides an interface to internal kernel data structures. These kernel data structures store data about the current state of the system. For example, the Process Control Block (PCB) is a kernel data structure for a process created by kernel to store the process information.

### The /proc filesystem contains virtual files that store information on different aspects of the system-
 - [**/proc/stat**](https://www.linuxhowtos.org/System/procstat.htm)

    This file contains the overall statistics of information about kernel activity. The information about the usage of individual CPUs & the overall usage is obtained from here.
 - [**/proc/\<pid\>/status**](https://www.kernel.org/doc/html/latest/filesystems/proc.html#process-specific-subdirectories)

    The /proc directory contains one subdirectory for each process running on the system, which is named after the process ID (PID). The \'status\' file in each subdirectory contains the process status in human readable form. The status information includes name of the process, state \(running or sleeping\), PPID, virtual memory size etc.
 - [**/proc/meminfo**](https://man7.org/linux/man-pages/man5/proc_meminfo.5.html)

    This file reports the statistics about memory usage on the system. The statistics include Total usable RAM, memory available for starting new applications, without swapping etc.
 - [**/proc/net/dev**](https://www.kernel.org/doc/html/latest/filesystems/proc.html#networking-info-in-proc-net)

    This file contains the information about the network devices along with the statistics of the network traffic \(data transmitted & recieved in kB\) since the boot time.
 - [**kill -9 \<pid\>**](https://www.man7.org/linux/man-pages/man1/kill.1.html)

    This command is part of the [**procps**](https://gitlab.com/procps-ng/procps) command line set, which are also implemented using the /proc filesystem. This command with the \'signal\' set to 9, kills the process specified by the PID.

 ## Installation

 ## Usage
