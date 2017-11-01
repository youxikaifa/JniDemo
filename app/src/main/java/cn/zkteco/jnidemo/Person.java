package cn.zkteco.jnidemo;

import android.util.Log;

/**
 * Created by Administrator on 2017/11/1.
 */

public class Person {
    public String name;
    public int age;

    public Person() {
    }

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        Log.v("Person","------------>call get method");
        return name;
    }

}
