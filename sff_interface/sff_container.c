//
// Created by zhanglei on 19-3-15.
//
#ifndef SFF_SSF_COMMON_H
#include "../sff_common.h"

#endif
const zend_function_entry factory_container_struct[] = {
        PHP_ME(SffContainer, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
        PHP_ME(SffContainer, setConfig, container_config_struct,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, receiveHook, recieve_data_hook,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, processStartHook, process_start_hook,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, processStopHook, process_stop_hook,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, run, NULL,  ZEND_ACC_PUBLIC)
        PHP_ME(SffContainer, __destruct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_DTOR)
        PHP_FE_END
};




//初始化容器配置
PHP_METHOD (SffContainer, __construct)
{
    //初始化这一个结构体
    super_container_init();


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

//运行容器
PHP_METHOD (SffContainer, run)
{

    //安装信号处理器
    container_instance.signal_factory->add_signal_handle(SIGPIPE,SIG_IGN);

    container_instance.signal_factory->add_signal_handle(SIGHUP,SIG_IGN);

    container_instance.signal_factory->add_signal_handle(SIGTERM,SIG_IGN);

    container_instance.signal_factory->add_signal_handle(SIGUSR1,SIG_IGN);

    container_instance.signal_factory->add_signal_handle(SIGUSR2,SIG_IGN);

    //守护进程开启
    if(container_instance.daemon == SFF_TRUE)
    {
        container_instance.process_factory->start_daemon();
    }

    //运行监控
    container_instance.run();
}


//释放掉内存
PHP_METHOD (SffContainer, __destruct)
{
    php_printf("%s\n","container destroy");
    container_instance.destroy();
}

void factory_container_init()
{
    //加载所需要的配置类
    INIT_CLASS_ENTRY(factory_container, "SffContainer", factory_container_struct);
    factory_container_entry = zend_register_internal_class_ex(&factory_container, NULL);

    //声明默认模块属性

}