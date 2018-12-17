package cn.rexih.android.testnativereference;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import cn.rexih.android.testnativereference.entity.Service;


public class MainActivity extends Activity implements View.OnClickListener {


    private Button btn_main_test_init;
    private Button btn_main_test_overflow;
    private Button btn_main_test_array;
    private Button btn_main_test_delete_local_ref;
    private Button btn_main_test_ensure_capacity;
    private Button btn_main_test_push_local_frame;
    private Button btn_main_test_global_weak_ref;
    private Button btn_main_test_init_weak_ref;
    private Button btn_main_test_gc;
    private Button btn_main_test_is_same;
    private Button btn_main_test_ref_type;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
    }


    private void initView() {
        btn_main_test_init = (Button) findViewById(R.id.btn_main_test_init);
        btn_main_test_overflow = (Button) findViewById(R.id.btn_main_test_overflow);
        btn_main_test_array = (Button) findViewById(R.id.btn_main_test_array);
        btn_main_test_delete_local_ref = (Button) findViewById(R.id.btn_main_test_delete_local_ref);
        btn_main_test_ensure_capacity = (Button) findViewById(R.id.btn_main_test_ensure_capacity);
        btn_main_test_push_local_frame = (Button) findViewById(R.id.btn_main_test_push_local_frame);
        btn_main_test_global_weak_ref = (Button) findViewById(R.id.btn_main_test_global_weak_ref);
        btn_main_test_init_weak_ref = (Button) findViewById(R.id.btn_main_test_init_weak_ref);
        btn_main_test_gc = (Button) findViewById(R.id.btn_main_test_gc);
        btn_main_test_is_same = (Button) findViewById(R.id.btn_main_test_is_same);
        btn_main_test_ref_type = (Button) findViewById(R.id.btn_main_test_ref_type);

        btn_main_test_init.setOnClickListener(this);
        btn_main_test_overflow.setOnClickListener(this);
        btn_main_test_array.setOnClickListener(this);
        btn_main_test_delete_local_ref.setOnClickListener(this);
        btn_main_test_ensure_capacity.setOnClickListener(this);
        btn_main_test_push_local_frame.setOnClickListener(this);
        btn_main_test_global_weak_ref.setOnClickListener(this);
        btn_main_test_init_weak_ref.setOnClickListener(this);
        btn_main_test_gc.setOnClickListener(this);
        btn_main_test_is_same.setOnClickListener(this);
        btn_main_test_ref_type.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.btn_main_test_init:
            JniManager
                    .getInstance()
                    .testInitLocalRef(new Service());
            break;
        case R.id.btn_main_test_overflow:
            JniManager
                    .getInstance()
                    .testLocalRefOverflow();
            break;
        case R.id.btn_main_test_array:
            Intent intent = new Intent(this, ArrayActivity.class);
            startActivity(intent);
            break;
        case R.id.btn_main_test_delete_local_ref:
            JniManager
                    .getInstance()
                    .testDeleteLocalRef();
            break;
        case R.id.btn_main_test_ensure_capacity:
            JniManager
                    .getInstance()
                    .testEnsureLocalCapacity();
            break;
        case R.id.btn_main_test_push_local_frame:
            JniManager
                    .getInstance()
                    .testPushLocalFrame();
            break;
        case R.id.btn_main_test_init_weak_ref:
            System.out.println(JniManager
                    .getInstance()
                    .initWeakGlobalRef(Service.buildA()));
            break;
        case R.id.btn_main_test_gc:
            System.gc();
            break;
        case R.id.btn_main_test_global_weak_ref:
            System.out.println("try again: " + JniManager
                    .getInstance()
                    .testGetWeakGlobalRef(Service.buildB()));
            break;
        case R.id.btn_main_test_is_same:
            System.out.println("local ref和global ref 是否指向同一个对象:" + JniManager
                    .getInstance()
                    .testIsSameObject());
            break;
        case R.id.btn_main_test_ref_type:
            JniManager.getInstance().testReferenceType(Service.buildB());
            break;
        }
    }


}
