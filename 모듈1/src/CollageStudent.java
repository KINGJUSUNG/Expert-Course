
public final class CollageStudent extends Student {
	public final static String TYPE = "대학생";
	private int grade;
	
	public CollageStudent(String name, String major, int grade) {
		super(name, major);
		this.grade = grade;
	}
	
	public void setGrade(int grade) {
		this.grade = grade;
	}
	
	public int getGrade() {
		return this.grade;
	}
	
	public String toString() {
		return super.toString() + " : " + grade + "학년";
	}
}
