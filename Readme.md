## jni的引用类型（`native-lib.cpp`）
- 所有jobject及其子类都是jni的引用类型，其对象的分配在java的gc堆上，但是引用分配在native method stack上，引用指向gc堆的内存地址

- jni的引用类型有四种，local ref/global ref/global weak ref/invalid ref

    - 通常jni接口方法的入参和方法体中实例化的jobject都是local ref
    - 通过NewGlobalRef转换为global ref，不会被gc回收
    - 通过NewGlobalRef转换为global weak ref，可以被gc回收
    - NULL是invalid ref

- ensureLocalCapacity和pushLocalFrame也不能让本次j2n的local ref总数超过限制，所以在频繁创建local ref的场景中，例如循环，要及时删除不是用的local ref
- 通过VMDebug打印引用表观察引用情况
## isCopy和数组的Release模式（`native-lib-array.cpp`）

```
0
	Actual: the array object is un-pinned.
	Copy: data is copied back. The buffer with the copy is freed.
JNI_COMMIT
	Actual: does nothing.
	Copy: data is copied back. The buffer with the copy is not freed.
JNI_ABORT
	Actual: the array object is un-pinned. Earlier writes are not aborted.
	Copy: the buffer with the copy is freed; any changes to it are lost.

```