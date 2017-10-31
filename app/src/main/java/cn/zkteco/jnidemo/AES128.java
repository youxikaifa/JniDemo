package cn.zkteco.jnidemo;

/**
 * Created by Administrator on 2017/10/31.
 */

public class AES128 {

    static {
        System.loadLibrary("aes128");
    }

    public static native String getStringFromC();

    public static native byte[] aes128_ecb_encrypt(byte[] original, int original_len, byte[] key);

    public static native byte[] aes128_ecb_decrypt(byte[] password, int password_len, byte[] key);

}
