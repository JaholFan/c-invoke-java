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
	jmethodID mid;
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
    /* 3. intantiate object*/
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
err:
	(*jvm)->DestroyJavaVM(jvm);
_return:
	return ret;
    
}
