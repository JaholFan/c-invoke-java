
public class Test{
    private String sex;
    private int age; 
    public static void main(String[] args){
        System.out.println("hello world");
    }
    public int my_print(String str){
        System.out.println(""+str+" sex:"+sex+" age:"+age);
        return 0;
    }
    public int my_print(int val){
        System.out.println("data="+val);
        return 0;
    }
}
