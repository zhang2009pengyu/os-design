# os-design
-----2017.12.5-----
初步设计： 
  1.进程调度：创建三个链队列，分别为：NotCreated（事件队列），Waiting（等待队列）和Finish（完成队列）。在处理机上运行的进程将处于Running状态。
            先来先服务算法；时间片轮转算法。
  2.内存分配：使用链队列作为数据结构。每个节点存储进程控制块PCB信息。
            最先适应分配算法；最优适应分配算法；最坏适应分配算法。
            内存回收，判断是否可以合并。
  3.磁盘调度：先来先服务算法，最短寻道时间优先算法，电梯算法。

-----2017.12.10-----
完成任务1.时间片调度
正在进行：任务1先来先服务（有bug）

-----2017.12.20-----
完成任务1.先来先服务
完成任务2.最先适应分配算法；最优适应分配算法；最坏适应分配算法；回收
完成任务3.先来先服务算法，最短寻道时间优先算法
未进行大量数据测试

-----2017.12.25-----
中期检查。
设计的扩展功能：
    1、67合并
    2、67合并的界面与动画效果（MFC）
        列表显示链表，用方块表示cpu执行，edit显示内存工作

-----2017.12.25晚-----
添加功能：
    1、mfc实现先来先服务和时间片调度算法
    
设计的拓展功能：
    1、添加时间事件
    
-----2017.12.26-----
添加功能：
    1、添加内存空间分配、回收与回收的合并
    
添加的拓展功能：
    1、抢占式进程调度
    
-----2017.12.27-----
添加功能：
    1、优先级调度（抢占式）
     
-----2017.12.28-----
添加功能：
    1、内存碎片的压缩
    2、优化界面（最终版）
    3、磁盘调度的界面与完善
    
最终
     



