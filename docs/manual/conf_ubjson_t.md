## conf\_ubjson\_t
### 概述
![image](images/conf_ubjson_t_0.png)

conf json对象。

示例

```c
char filename[MAX_PATH + 1] = {0};
path_prepend_temp_path(filename, "test.ubjson");

const char *ubjson_data1 = "{"
"\"root\":{"
"\"name\":\"awplc\","
"\"age\":18,"
"\"weight\":60.5"
"}"
"}";

// 将JSON保存为UBJSON
tk_object_t *json = conf_json_load_from_buff(ubjson_data1, strlen(ubjson_data1), FALSE);
ENSURE(conf_ubjson_save_as(json, filename) == RET_OK);
ENSURE(file_exist(filename) == TRUE);

// 从文件加载
tk_object_t *ubjson = conf_ubjson_load(filename, FALSE);

// 获取数据。
ENSURE(tk_str_eq(tk_object_get_prop_str(ubjson, "root.name"), "awplc"));
ENSURE(tk_object_get_prop_int(ubjson, "root.age", 0) == 18);
ENSURE(tk_object_get_prop_double(ubjson, "root.weight", 0) == 60.5);

// 设置数据
ENSURE(tk_object_set_prop_int(ubjson, "root.age", 20) == RET_OK);
ENSURE(tk_object_get_prop_int(ubjson, "root.age", 0) == 20);

// 保存到文件
ENSURE(conf_ubjson_save_as(ubjson, filename) == RET_OK);
ENSURE(file_exist(filename) == TRUE);

// 销毁对象
TK_OBJECT_UNREF(ubjson);
```
----------------------------------
### 函数
<p id="conf_ubjson_t_methods">

| 函数名称 | 说明 | 
| -------- | ------------ | 
| <a href="#conf_ubjson_t_conf_ubjson_create">conf\_ubjson\_create</a> | 创建一个空的conf对象。 |
| <a href="#conf_ubjson_t_conf_ubjson_load">conf\_ubjson\_load</a> | 从指定URL加载UBJSON对象。 |
| <a href="#conf_ubjson_t_conf_ubjson_load_from_buff">conf\_ubjson\_load\_from\_buff</a> | 从内存加载UBJSON对象。 |
| <a href="#conf_ubjson_t_conf_ubjson_save_as">conf\_ubjson\_save\_as</a> | 将doc对象保存到指定URL。 |
| <a href="#conf_ubjson_t_conf_ubjson_save_to_buff">conf\_ubjson\_save\_to\_buff</a> | 将obj保存为UBJSON格式到内存。 |
#### conf\_ubjson\_create 函数
-----------------------

* 函数功能：

> <p id="conf_ubjson_t_conf_ubjson_create">创建一个空的conf对象。

* 函数原型：

```
tk_object_t* conf_ubjson_create ();
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | tk\_object\_t* | 返回配置对象。 |
#### conf\_ubjson\_load 函数
-----------------------

* 函数功能：

> <p id="conf_ubjson_t_conf_ubjson_load">从指定URL加载UBJSON对象。

* 函数原型：

```
tk_object_t* conf_ubjson_load (const char* url, bool_t create_if_not_exist);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | tk\_object\_t* | 返回配置对象。 |
| url | const char* | 路径(通常是文件路径)。 |
| create\_if\_not\_exist | bool\_t | 如果不存在是否创建。 |
#### conf\_ubjson\_load\_from\_buff 函数
-----------------------

* 函数功能：

> <p id="conf_ubjson_t_conf_ubjson_load_from_buff">从内存加载UBJSON对象。

* 函数原型：

```
tk_object_t* conf_ubjson_load_from_buff (const void* buff, uint32_t size, bool_t create_if_not_exist);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | tk\_object\_t* | 返回配置对象。 |
| buff | const void* | 数据。 |
| size | uint32\_t | 数据长度。 |
| create\_if\_not\_exist | bool\_t | 如果不存在是否创建。 |
#### conf\_ubjson\_save\_as 函数
-----------------------

* 函数功能：

> <p id="conf_ubjson_t_conf_ubjson_save_as">将doc对象保存到指定URL。

* 函数原型：

```
ret_t conf_ubjson_save_as (tk_object_t* obj, const char* url);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | ret\_t | 返回RET\_OK表示成功，否则表示失败 |
| obj | tk\_object\_t* | doc对象。 |
| url | const char* | 保存的位置。 |
#### conf\_ubjson\_save\_to\_buff 函数
-----------------------

* 函数功能：

> <p id="conf_ubjson_t_conf_ubjson_save_to_buff">将obj保存为UBJSON格式到内存。

* 函数原型：

```
ret_t conf_ubjson_save_to_buff (tk_object_t* obj, wbuffer_t* wb);
```

* 参数说明：

| 参数 | 类型 | 说明 |
| -------- | ----- | --------- |
| 返回值 | ret\_t | 返回RET\_OK表示成功，否则表示失败 |
| obj | tk\_object\_t* | doc对象。 |
| wb | wbuffer\_t* | 返回结果(不要初始化，使用完成后要调用wbuffer\_deinit)。 |
