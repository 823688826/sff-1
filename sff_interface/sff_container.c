//
// Created by zhanglei on 19-3-15.
//
#ifndef SFF_SSF_COMMON_H
#include "../sff_common.h"

#endif
const zend_function_entry factory_container_struct[] = {
        PHP_ME(SffContainer, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        PHP_ME(SffContainer, setConfig, container_config_struct,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, socketConnectHook, container_connect_hook,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, socketCloseHook, container_close_hook,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, receiveHook, recieve_data_hook,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, processStartHook, process_start_hook,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, start, start_index,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, stop, stop_index,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, processStopHook, process_stop_hook,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, report, send_data,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, run, NULL,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, __destruct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
        PHP_FE_END
};




//初始化容器配置
PHP_METHOD (SffContainer, __construct)
{
    //初始化这一个结构体
    super_container_init();

    container_instance.object = getThis();

}

//设置容器的配置选项
PHP_METHOD (SffContainer, setConfig)
{
    zval *config = NULL;//this opetion begin single model
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ARRAY(config)
    ZEND_PARSE_PARAMETERS_END();

    //循环传进来的数组,将数组的值放入结构体之中,并且来检查参数
    zval *config_item;
    zend_string *config_key;
    ZEND_HASH_FOREACH_STR_KEY_VAL(Z_ARRVAL_P(config), config_key, config_item) {
                if (config_key == NULL) {
                    continue;
                }
                container_instance.set_container_config(config_key,config_item);
            } ZEND_HASH_FOREACH_END();

}

//收到数据的时候触发的钩子
PHP_METHOD (SffContainer, receiveHook)
{
    zval *hook = NULL;//this opetion begin single model
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(hook)
    ZEND_PARSE_PARAMETERS_END();

    //查看参数是否是闭包回调
    if(sff_check_zval_function(hook) == SFF_FALSE)
    {
        php_error_docref(NULL, E_WARNING, "receiveHook param must be function");
    }

    //将闭包处理更新到属性中长期存住
    zval return_result;

    zend_update_property(factory_controller_entry,getThis(),CONTAINER_RECV_HOOK,strlen(CONTAINER_RECV_HOOK),hook);

    container_instance.receive_data_hook = zend_read_property(factory_controller_entry,getThis(),CONTAINER_RECV_HOOK,strlen(CONTAINER_RECV_HOOK),0,&return_result);
}

//链接上服务器的时候触发
PHP_METHOD (SffContainer, socketConnectHook)
{
    zval *hook = NULL;//this opetion begin single model
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(hook)
    ZEND_PARSE_PARAMETERS_END();

    //查看参数是否是闭包回调
    if(sff_check_zval_function(hook) == SFF_FALSE)
    {
        php_error_docref(NULL, E_WARNING, "receiveHook param must be function");
    }

    //将闭包处理更新到属性中长期存住
    zval return_result;

    zend_update_property(factory_controller_entry,getThis(),CONTAINER_CONNECT_HOOK,strlen(CONTAINER_CONNECT_HOOK),hook);

    container_instance.connect_hook = zend_read_property(factory_controller_entry,getThis(),CONTAINER_CONNECT_HOOK,strlen(CONTAINER_CONNECT_HOOK),0,&return_result);
}

//关闭套接字的时候触发
PHP_METHOD (SffContainer, socketCloseHook)
{
    zval *hook = NULL;//this opetion begin single model
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(hook)
    ZEND_PARSE_PARAMETERS_END();

    //查看参数是否是闭包回调
    if(sff_check_zval_function(hook) == SFF_FALSE)
    {
        php_error_docref(NULL, E_WARNING, "receiveHook param must be function");
    }

    //将闭包处理更新到属性中长期存住
    zval return_result;

    zend_update_property(factory_controller_entry,getThis(),CONTAINER_CLOSE_HOOK,strlen(CONTAINER_CLOSE_HOOK),hook);

    container_instance.close_hook = zend_read_property(factory_controller_entry,getThis(),CONTAINER_CLOSE_HOOK,strlen(CONTAINER_CLOSE_HOOK),0,&return_result);
}


//启动进程的时候触发的钩子
PHP_METHOD (SffContainer, processStartHook)
{
    zval *hook = NULL;//this opetion begin single model
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(hook)
    ZEND_PARSE_PARAMETERS_END();

    //查看参数是否是闭包回调
    if(sff_check_zval_function(hook) == SFF_FALSE)
    {
        php_error_docref(NULL, E_WARNING, "processStartHook param must be function");
    }

    //将闭包处理更新到属性中长期存住
    zval return_result;

    zend_update_property(factory_controller_entry,getThis(),CONTAINER_RROC_START_HOOK,strlen(CONTAINER_RROC_START_HOOK),hook);

    container_instance.process_start_hook = zend_read_property(factory_controller_entry,getThis(),CONTAINER_RROC_START_HOOK,strlen(CONTAINER_RROC_START_HOOK),0,&return_result);

}

//退出进程的时候触发的钩子
PHP_METHOD (SffContainer, processStopHook)
{
    zval *hook = NULL;//this opetion begin single model
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(hook)
    ZEND_PARSE_PARAMETERS_END();

    //查看参数是否是闭包回调
    if(sff_check_zval_function(hook) == SFF_FALSE)
    {
        php_error_docref(NULL, E_WARNING, "processStopHook param must be function");
    }

    //将闭包处理更新到属性中长期存住
    zval return_result;

    zend_update_property(factory_controller_entry,getThis(),CONTAINER_RROC_STOP_HOOK,strlen(CONTAINER_RROC_STOP_HOOK),hook);

    container_instance.process_stop_hook = zend_read_property(factory_controller_entry,getThis(),CONTAINER_RROC_STOP_HOOK,strlen(CONTAINER_RROC_STOP_HOOK),0,&return_result);
}

//执行数据上报
PHP_METHOD (SffContainer,report)
{
    zval *send_data = NULL;//this opetion begin single model
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(send_data)
    ZEND_PARSE_PARAMETERS_END();

    //开启容器上报必须要打开远程链接
//    php_printf("connect server:%d\n",container_instance.connect_server);
    if(container_instance.connect_server != SFF_TRUE)
    {
        php_error_docref(NULL, E_WARNING, "report data must open server connect");
        RETURN_FALSE
    }

    //检查是否是字符串
    if(Z_TYPE(*send_data) != IS_STRING)
    {
        php_error_docref(NULL, E_WARNING, "report data must be string");
        RETURN_FALSE
    }

    //做数据发送处理
    ssize_t res = container_instance.socket_lib->write(container_instance.socket_lib->sockfd,Z_STRVAL(*send_data),strlen(Z_STRVAL(*send_data)));
    if(res == SFF_FALSE)
    {
        RETURN_FALSE
    }else{
        RETURN_TRUE
    }
}

void killprocess(int signo)
{
    if(signo == SIGTERM)
    {
        //如果说内存池中有数据,循环给内存池中的进程发送终止信号
        if(container_instance.process_pool_manager->mem)
        {
            container_instance.process_pool_manager->send_message(SIGTERM);
        }

        //清理掉server_pid;
        container_instance.log_lib->write_log(container_instance.pidfile, "0", strlen("0"),"w");

        //最后关闭的是自己
        kill(container_instance.container_pid,SIGKILL);
    }
}

//停止程序
PHP_METHOD (SffContainer, stop)
{
    zval *stop_index = NULL;//this opetion begin single model
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(stop_index)
    ZEND_PARSE_PARAMETERS_END();

    if(Z_TYPE(*stop_index) != IS_LONG)
    {
        php_error_docref(NULL, E_WARNING, "stop index must be int");
        RETURN_FALSE
    }

    int index = stop_index->value.lval;
    php_printf("index:%d\n",index);
    process_block* block = container_instance.process_pool_manager->mem->head + index;
    if(!block)
    {
        RETURN_FALSE
    }

    block->state = STOPPED;

    //停止程序
    int res = kill(block->pid,SIGTERM);
    if(res == 0)
    {
        RETURN_TRUE
    }else{
        RETURN_FALSE
    }
}

//启动程序
PHP_METHOD (SffContainer, start)
{
    zval *start_index = NULL;//this opetion begin single model
    ZEND_PARSE_PARAMETERS_START(1, 1)
            Z_PARAM_ZVAL(start_index)
    ZEND_PARSE_PARAMETERS_END();

    if(Z_TYPE(*start_index) != IS_LONG)
    {
        php_error_docref(NULL, E_WARNING, "start index must be int");
        RETURN_FALSE
    }

    int index = start_index->value.lval;
    process_block* block = container_instance.process_pool_manager->mem->head + index;
    if(!block)
    {
        RETURN_FALSE
    }

    //如果进程正在运行之中为了防止程序重复运行必须要杀死原程序
    if(block->state == RUNNING)
    {
        php_error_docref(NULL, E_WARNING, "process has been run,please stop the process");
        RETURN_FALSE
    }else{
        block->state = RUNNING;
    }


    //重新拉起进程
    container_instance.process_factory->spawn(index);

    //停止程序
    RETURN_TRUE
}

//运行容器
PHP_METHOD (SffContainer, run)
{

    //安装信号处理器
    container_instance.signal_factory->add_signal_handle(SIGPIPE,SIG_IGN);

    container_instance.signal_factory->add_signal_handle(SIGHUP,SIG_IGN);

    //收到了sigterm信号,那么需要给所有进程发信号，然后再停止自己
    container_instance.signal_factory->add_signal_handle(SIGTERM,killprocess);

    container_instance.signal_factory->add_signal_handle(SIGUSR1,SIG_IGN);

    container_instance.signal_factory->add_signal_handle(SIGUSR2,SIG_IGN);

    //守护进程开启
    if(container_instance.daemon == SFF_TRUE)
    {
        container_instance.process_factory->start_daemon();

        container_instance.container_pid = getpid();
    }

    //运行完成后记录pid
    char filepid[sizeof(container_instance.container_pid)+1];
    sprintf(filepid, "%d", container_instance.container_pid);
    if(container_instance.pidfile) {
        container_instance.log_lib->write_log(container_instance.pidfile, filepid, strlen(filepid),"w");
    }

    //运行监控
    container_instance.run();
}


//释放掉内存
PHP_METHOD (SffContainer, __destruct)
{
    container_instance.destroy();
}

void factory_container_init()
{
    //加载所需要的配置类
    INIT_CLASS_ENTRY(factory_container, "SffContainer", factory_container_struct);
    factory_container_entry = zend_register_internal_class_ex(&factory_container, NULL);

    //声明默认模块属性

}