# axvisor-on-3a6000
简要描述本项目暂定的最终目标：完成龙芯架构3A6000的axvisor的完整适配，实现同时启动虚拟机linux与arceos
- 一阶段：学习axvisor对裸机uefi启动的适配，从arceos的板级启动开始再到axvisor，目标是完成初步的引导程序
- 二阶段：学习type1.5的hypervisor，目前主要关注的是jailhouse，并由此完成aosc到axvisor的初始化
- 三阶段：针对axvisor的需求进一步完善，启动第一台虚拟机