#include <stdio.h>
#include <jni.h>

jint create_vm(JavaVM** jvm, JNIEnv** env) 
{  
    JavaVMInitArgs args;  
    JavaVMOption options[1];  
    args.version = JNI_VERSION_1_6;  
    args.nOptions = 1;  
    options[0].optionString = "-Djava.class.path=./";  
    args.options = options;  
    args.ignoreUnrecognized = JNI_FALSE;  
    return JNI_CreateJavaVM(jvm, (void **)env, &args);  
}

int main(int argc,char**argv)
{
	JavaVM* jvm;
	JNIEnv* env;
	jclass cls;
	jmethodID mid,cid,id_1;
    jstring jstr;
    jobject jobj;
	int ret = 0;
    /* 1. create java virtual machine*/
	ret = create_vm(&jvm,&env);
	if (ret < 0) {
		printf("Can't create Java VM\n");
		goto _return;
	}
    /* 2. get class*/
	cls = (*env)->FindClass(env,"Test");
	if (cls == NULL) {
		printf("Can't find class Test\n");
		ret = -1;
		goto err;
	}
    /************example 1:call static method*************/
    /* 3. intantiate object(skip this step)*/
    /* 4. call method 
     * 4.1 get method
     * 4.2 create parameter
     * 4.3 call method
     */
	mid = (*env)->GetStaticMethodID(env, cls, "main",
									 "([Ljava/lang/String;)V");
	if (mid == NULL) {
		ret = -2;
		printf("Can't get static method\n");
		goto err;
	}
	(*env)->CallStaticVoidMethod(env, cls, mid, NULL);
    /************examle 2:call none static method*********/
    /* 3. intantiate object
     * 3.1 get constructor method
     * 3.2 create parameter
     * 3.3 NewObject
     */
	cid = (*env)->GetMethodID(env, cls, "<init>",
									"()V");
	if (cid == NULL) {
		ret = -3;
		printf("Can't get constructor method\n");
		goto err;
	}
    
    jobj = (*env)->NewObject(env, cls, cid); 
	if (jobj == NULL) {
		ret = -4;
		printf("Can't new object\n");
		goto err;
	}
    
    /* 4. call method 
     * 4.1 get method
     * 4.2 create parameter
     * 4.3 call method
     */
	id_1 = (*env)->GetMethodID(env, cls, "my_print",
									 "(Ljava/lang/String;)I");
	if (id_1 == NULL) {
		ret = -5;
		printf("Can't get method:my_print\n");
		goto err;
	}
    jstr = (*env)->NewStringUTF(env, "Jahol Fan");
	ret = (*env)->CallIntMethod(env, jobj, id_1, jstr);
    if(ret){
		ret = -6;
		printf("Can't call method:my_print\n");
		goto err;
        
    }
err:
	(*jvm)->DestroyJavaVM(jvm);
_return:
	return ret;
    
}
