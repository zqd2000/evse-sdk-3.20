# <a name="目录">目录</a>
+ [多线程相关HAL接口详解](#多线程相关HAL接口详解)
    * [HAL_MutexCreate](#HAL_MutexCreate)
    * [HAL_MutexDestroy](#HAL_MutexDestroy)
    * [HAL_MutexLock](#HAL_MutexLock)
    * [HAL_MutexUnlock](#HAL_MutexUnlock)
    * [HAL_SemaphoreCreate](#HAL_SemaphoreCreate)
    * [HAL_SemaphoreDestroy](#HAL_SemaphoreDestroy)
    * [HAL_SemaphorePost](#HAL_SemaphorePost)
    * [HAL_SemaphoreWait](#HAL_SemaphoreWait)
    * [HAL_ThreadCreate](#HAL_ThreadCreate)
    * [HAL_ThreadDelete](#HAL_ThreadDelete)
    * [HAL_ThreadDetach](#HAL_ThreadDetach)

# <a name="多线程相关HAL接口详解">多线程相关HAL接口详解</a>

## <a name="HAL_MutexCreate">HAL_MutexCreate</a>

原型
---
```
void *HAL_MutexCreate(void);
```

接口说明
---
创建一个互斥量对象, 返回指向所创建互斥量的指针, 用于同步访问, 对于仅支持单线程应用, 可实现为空函数

参数说明
---
void

返回值说明
---
void

-----

## <a name="HAL_MutexDestroy">HAL_MutexDestroy</a>

原型
---
```
void HAL_MutexDestroy(_IN_ void *mutex);
```

接口说明
---
销毁一个互斥量对象, 释放资源

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| mutex   | void *  | 输入    | 互斥量指针

返回值说明
---
void

-----

## <a name="HAL_MutexLock">HAL_MutexLock</a>

原型
---
```
void HAL_MutexLock(_IN_ void *mutex);
```

接口说明
---
锁住一个互斥量

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| mutex   | void *  | 输入    | 互斥量指针

返回值说明
---
void

-----

## <a name="HAL_MutexUnlock">HAL_MutexUnlock</a>

原型
---
```
void HAL_MutexUnlock(_IN_ void *mutex);
```

接口说明
---
解锁一个互斥量

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| mutex   | void *  | 输入    | 互斥量指针

返回值说明
---
void

-----


## <a name="HAL_SemaphoreCreate">HAL_SemaphoreCreate</a>

原型
---
```
void *HAL_SemaphoreCreate(void);
```

接口说明
---
创建一个计数信号量, 此接口实现必须为原子操作, 对于仅支持单线程应用, 可实现为空函数

参数说明
---
void

返回值说明
---
| 值       | 说明
|:---------|:----------------
| NULL     | 创建失败
| !NULL    | 创建成功, 返回信号量句柄

-----

## <a name="HAL_SemaphoreDestroy">HAL_SemaphoreDestroy</a>

原型
---
```
void HAL_SemaphoreDestroy(_IN_ void *sem);
```

接口说明
---
销毁一个由参数`sem`指定的信号量, 此接口实现必须为原子操作, 此函数无返回值

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| sem     | void *  | 输入    | 信号量指针

返回值说明
---
void

-----

## <a name="HAL_SemaphorePost">HAL_SemaphorePost</a>

原型
---
```
void HAL_SemaphorePost(_IN_ void *sem);
```

接口说明
---
在指定的计数信号量上做自增操作, 解除其它线程的等待, 此接口实现必须为原子操作, 对于仅支持单线程应用, 可实现为空函数

参数说明
---
| 参数    | 数据类型| 方向    | 说明
|---------|---------|---------|-------------
| sem     | void *  | 输入    | 信号量句柄

返回值说明
---
void

-----

## <a name="HAL_SemaphoreWait">HAL_SemaphoreWait</a>

原型
---
```
int HAL_SemaphoreWait(_IN_ void *sem, _IN_ uint32_t timeout_ms);
```

接口说明
---
在指定的计数信号量上等待并做自减操作, 对于仅支持单线程应用, 此接口实现必须为原子操作, 可实现为空函数

参数说明
---
| 参数        | 数据类型    | 方向    | 说明
|-------------|-------------|---------|---------------------------------------------------------------------------------
| sem         | void *      | 输入    | 信号量句柄
| timeout_ms  | uint32_t    | 输入    | 信号量等待超时时间, 单位ms, 如果参数为`PLATFORM_WAIT_INFINITE`, 则函数返回只能由获取信号量触发

返回值说明
---
| 值  | 说明
|-----|-------------------------
| 0   | 函数返回是由信号量触发
| -1  | 函数返回是由超时触发

-----


## <a name="HAL_ThreadCreate">HAL_ThreadCreate</a>

原型
---
```
int HAL_ThreadCreate(
            _OU_ void **thread_handle,
            _IN_ void *(*work_routine)(void *),
            _IN_ void *arg,
            _IN_ hal_os_thread_param_t *hal_os_thread_param,
            _OU_ int *stack_used);
```

接口说明
---
按照指定入参创建一个线程

参数说明
---
| 参数                    | 数据类型                        | 方向    | 说明
|-------------------------|---------------------------------|---------|-------------------------------------------------
| thread_handle           | void **                         | 输出    | 指向线程句柄变量的指针
| work_routine            | void *(*work_routine)(void *)   | 输入    | 指向线程执行函数的函数指针
| arg                     | void *                          | 输入    | 传递给运行程序的单个参数
| hal_os_thread_param     | hal_os_thread_param_t *         | 输入    | 指向线程初始化参数的指针
| stack_used              | int *                           | 输出    | 指示平台是否使用栈缓冲区, 0: 未使用. 1: 使用

线程初始化参数定义:
```
typedef struct _hal_os_thread {
    hal_os_thread_priority_t priority;     /* initial thread priority */
    void                    *stack_addr;   /* thread stack address malloced by caller, use system stack by . */
    size_t                   stack_size;   /* stack size requirements in bytes; 0 is default stack size */
    int                      detach_state; /* 0: not detached state; otherwise: detached state. */
    char                    *name;         /* thread name. */
} hal_os_thread_param_t;
```

线程优先级定义:
```
typedef enum {
    os_thread_priority_idle = -3,        /* priority: idle (lowest) */
    os_thread_priority_low = -2,         /* priority: low */
    os_thread_priority_belowNormal = -1, /* priority: below normal */
    os_thread_priority_normal = 0,       /* priority: normal (default) */
    os_thread_priority_aboveNormal = 1,  /* priority: above normal */
    os_thread_priority_high = 2,         /* priority: high */
    os_thread_priority_realtime = 3,     /* priority: realtime (highest) */
    os_thread_priority_error = 0x84,     /* system cannot determine priority or thread has illegal priority */
} hal_os_thread_priority_t;
```

返回值说明
---
| 值  | 说明
|-----|-------------
| -1  | 创建失败
| 0   | 创建成功

-----

## <a name="HAL_ThreadDelete">HAL_ThreadDelete</a>
(在3.0.1+sp1及之后版本中不需要实现)
原型
---
```
void HAL_ThreadDelete(_IN_ void *thread_handle);
```

接口说明
---
删除指定的线程

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|-----------------------------
| thread_handle   | void *  | 输入    | 线程句柄, NULL表示当前线程

返回值说明
---
void

-----

## <a name="HAL_ThreadDetach">HAL_ThreadDetach</a>
(在3.0.1+sp1及之后版本中不需要实现)
原型
---
```
void HAL_ThreadDetach(_IN_ void *thread_handle);
```

接口说明
---
将指定线程设置为分离状态

参数说明
---
| 参数            | 数据类型| 方向    | 说明
|-----------------|---------|---------|-----------------------------
| thread_handle   | void *  | 输入    | 线程句柄, NULL表示当前线程

返回值说明
---
void

-----
