## conf\_ini\_t
### 概述
![image](images/conf_ini_t_0.png)

conf ini对象。

示例

```c
char filename[MAX_PATH + 1] = {0};
path_prepend_temp_path(filename, "test.ini");

const char *ini_data1 = "[root]\n"
"name=awplc\n"
"age=18\n"
"weight=60.5\n";
ENSURE(file_write(filename, ini_data1, strlen(ini_data1)) == RET_OK);

// 从文件加载
tk_object_t *ini = conf_ini_load(filename, FALSE);

// 获取数据。
ENSURE(tk_str_eq(tk_object_get_prop_str(ini, "root.name"), "awplc"));
ENSURE(tk_object_get_prop_int(ini, "root.age", 0) == 18);
ENSURE(tk_object_get_prop_double(ini, "root.weight", 0) == 60.5);

// 销毁对象
TK_OBJECT_UNREF(ini);

// 从内存加载
ini = conf_ini_load_from_buff(ini_data1, strlen(ini_data1), FALSE);

// 获取数据
ENSURE(tk_str_eq(tk_object_get_prop_str(ini, "root.name"), "awplc"));
ENSURE(tk_object_get_prop_int(ini, "root.age", 0) == 18);
ENSURE(tk_object_get_prop_double(ini, "root.weight", 0) == 60.5);

// 设置数据
ENSURE(tk_object_set_prop_int(ini, "root.age", 20) == RET_OK);
ENSURE(tk_object_get_prop_int(ini, "root.age", 0) == 20);

// 保存到文件
ENSURE(conf_ini_save_as(ini, filename) == RET_OK);
ENSURE(file_exist(filename) == TRUE);

// 销毁对象
TK_OBJECT_UNREF(ini);
```
----------------------------------
### 函数
<p id="conf_ini_t_methods">

| 函数名称 | 说明 | 
| -------- | ------------ | 
| <a href="#conf_ini_t_conf_ini_create">conf\_ini\_create</a> | 创建一个空的conf对象。 |
| <a href="#conf_ini_t_conf_ini_load">conf\_ini\_load</a> | 从指定URL加载INI对象。 |
| <a href="#conf_ini_t_conf_ini_load_from_buff">conf\_ini\_load\_from\_buff</a> | 从内存加载INI对象。 |
| <a href="#conf_ini_t_conf_ini_save_as">conf\_ini\_save\_as</a> | 将doc对象保存到指定URL。 |
| <a href="#conf_ini_t_conf_ini_save_to_buff">conf\_ini\_save\_to\_buff</a> | 将obj保存为INI格式到内存。 |
#### conf\_ini\_create 函数
-----------------------

* 函数功能：

> <p id="conf_ini_t_conf_ini_create">创建一个空的conf对象。

* 函数原型：

```
tk_object_t* conf_ini_create ();
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | tk\_object\_t* | 返回配置对象。 |
#### conf\_ini\_load 函数
-----------------------

* 函数功能：

> <p id="conf_ini_t_conf_ini_load">从指定URL加载INI对象。

* 函数原型：

```
tk_object_t* conf_ini_load (const char* url, bool_t create_if_not_exist);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | tk\_object\_t* | 返回配置对象。 |
| url | const char* | 路径(通常是文件路径)。 |
| create\_if\_not\_exist | bool\_t | 如果不存在是否创建。 |
#### conf\_ini\_load\_from\_buff 函数
-----------------------

* 函数功能：

> <p id="conf_ini_t_conf_ini_load_from_buff">从内存加载INI对象。

* 函数原型：

```
tk_object_t* conf_ini_load_from_buff (const void* buff, uint32_t size, bool_t create_if_not_exist);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | tk\_object\_t* | 返回配置对象。 |
| buff | const void* | 数据。 |
| size | uint32\_t | 数据长度。 |
| create\_if\_not\_exist | bool\_t | 如果不存在是否创建。 |
#### conf\_ini\_save\_as 函数
-----------------------

* 函数功能：

> <p id="conf_ini_t_conf_ini_save_as">将doc对象保存到指定URL。

* 函数原型：

```
ret_t conf_ini_save_as (tk_object_t* obj, const char* url);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | ret\_t | 返回RET\_OK表示成功，否则表示失败 |
| obj | tk\_object\_t* | doc对象。 |
| url | const char* | 保存的位置。 |
#### conf\_ini\_save\_to\_buff 函数
-----------------------

* 函数功能：

> <p id="conf_ini_t_conf_ini_save_to_buff">将obj保存为INI格式到内存。

* 函数原型：

```
ret_t conf_ini_save_to_buff (tk_object_t* obj, wbuffer_t* wb);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | ret\_t | 返回RET\_OK表示成功，否则表示失败 |
| obj | tk\_object\_t* | doc对象。 |
| wb | wbuffer\_t* | 返回结果(不要初始化，使用完成后要调用wbuffer\_deinit)。 |
