
public class Student extends Person {
	public static final String TYPE = "모든학생";
	
	protected String major;
	
	public Student(String name, String major) {
		super(name);
		this.major = major;
	}
	
	public void setMajor(String major) {
		this.major = major;
	}
	
	public String getMajor() {
		return major;
	}
	
	public String toString() {
		return super.toString()  + " : " + major;
	}
}
