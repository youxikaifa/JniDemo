package cn.zkteco.jnidemo;

import java.util.ArrayList;

/**
 * Created by Administrator on 2017/10/31.
 * 列举java数据类型和class
 */

public class AES128 {

    static {
        System.loadLibrary("aes128");
    }


    public static native byte[] aes128_ecb_encrypt(byte[] original, int original_len, byte[] key);

    public static native byte[] aes128_ecb_decrypt(byte[] password, int password_len, byte[] key);

    public static native int callAaddB(int a,int b);

    public static native boolean getBooleanValue(boolean value);

    public static native char getChar(char c);

    public static native String getStringFromC(String info);

    public static native Person getPersonInfo(Person p);

    public static native ArrayList<Person> getListPerson();


}
