package cn.rexih.android.testnativereference;

import cn.rexih.android.testnativereference.entity.Service;


/**
 * @author huangwr
 * @version %I%, %G%
 * @package cn.rexih.android.testnativereference
 * @file JniManager
 * @date 2018/12/9
 */
public class JniManager {

    static {
        System.loadLibrary("native-lib");
    }
    private static class JniManagerHolder {
        static JniManager instance = new JniManager();
    }

    public static JniManager getInstance(){
        return JniManagerHolder.instance;
    }

    public native void testInitLocalRef(Service entity);

    public native void testLocalRefOverflow();

    public native void testDeleteLocalRef();

    public native void testEnsureLocalCapacity();

    public native void testPushLocalFrame();

    public native Service testGetWeakGlobalRef(Service repl);

    public native boolean testIsSameObject();

    public native Service initWeakGlobalRef(Service entity);

    public native void testReferenceType(Service entity);

    public native String echo(String text);

    public native String testChinese();

    public native void testObjectArray(Object[] objArray);

    public native int testRegionArray(char[] carr);

    public native int testArrayReleaseMode(int[] test, int option);




}
