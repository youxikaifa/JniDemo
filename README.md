# JniDemo

## 在获取类型时注意

以“L”开头，以“；”结束，中间对应的是该类型的路径
```
String： Ljava/lang/String；
Object： Ljava/lang/Object；
```
自定义类 Person 对应  
```
package perfecter.jni.Person;
Person ： Lperfecter/jni/MyObj；
"."换成“/”
```

数组表示
```
数组表示的时候以“[” 为标志，一个“[”表示一个维度
int [ ]：[I
Long[ ][ ]： [[J
Object[ ][ ][ ]： [[[Ljava/lang/Object；
```
其实不知道怎么生成签名的可以直接用命令行去查看，具体做法是在生成的类的class目录下执行 `javap –s Person`.
