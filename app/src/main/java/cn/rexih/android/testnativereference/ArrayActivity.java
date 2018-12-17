package cn.rexih.android.testnativereference;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import java.util.Arrays;


/**
 * @author huangwr
 * @version %I%, %G%
 * @package cn.rexih.android.testnativereference
 * @file ArrayActivity
 * @date 2018/12/9
 */
public class ArrayActivity extends Activity implements View.OnClickListener {


    private Button btn_array_test_release_mode;
    private Button btn_array_test_string;
    private Button btn_array_test_chinese;
    private Button btn_array_test_object_array;
    private Button btn_array_test_char_array;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_array);
        initView();
    }

    private void initView() {
        btn_array_test_release_mode = (Button) findViewById(R.id.btn_array_test_release_mode);
        btn_array_test_string = (Button) findViewById(R.id.btn_array_test_string);
        btn_array_test_chinese = (Button) findViewById(R.id.btn_array_test_chinese);
        btn_array_test_object_array = (Button) findViewById(R.id.btn_array_test_object_array);
        btn_array_test_char_array = (Button) findViewById(R.id.btn_array_test_char_array);

        btn_array_test_release_mode.setOnClickListener(this);
        btn_array_test_string.setOnClickListener(this);
        btn_array_test_chinese.setOnClickListener(this);
        btn_array_test_object_array.setOnClickListener(this);
        btn_array_test_char_array.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.btn_array_test_release_mode:
            JniManager instance = JniManager.getInstance();
            int[] ints = { 1, 42, 123, 12 };
            System.out.println("raw:" + Arrays.toString(ints));
            int ret = instance.testArrayReleaseMode(ints, 2);
            System.out.println(ret + ":" + Arrays.toString(ints));
            ret = instance.testArrayReleaseMode(ints, 0);
            System.out.println(ret + ":" + Arrays.toString(ints));
            ret = instance.testArrayReleaseMode(ints, 1);
            System.out.println(ret + ":" + Arrays.toString(ints));
            break;
        case R.id.btn_array_test_string:
            System.out.println(JniManager
                    .getInstance()
                    .echo("I'm an echo"));
            break;
        case R.id.btn_array_test_chinese:
            System.out.println(JniManager
                    .getInstance()
                    .testChinese());
            break;
        case R.id.btn_array_test_object_array:
            JniManager
                    .getInstance()
                    .testObjectArray(new String[]{ "File has been sent for download to", "该方法会利用(Unicode) char 数组", "也可能是指向 jni 中的拷贝", " __android_log_print" });
            break;
        case R.id.btn_array_test_char_array:
            char[] carr=new char[]{'1','4','7','2','9'};
            System.out.println("sum is: "+JniManager
                    .getInstance()
                    .testRegionArray(carr));
            break;
        }
    }
}
