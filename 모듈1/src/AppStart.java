import java.util.Arrays;

public class AppStart {
	
	public static void showListPerson(Course<?> course) {
		Arrays.toString(course.getStudents());
	}
	
	public static void showListStudent(Course<? super Student> course) {
		Arrays.toString(course.getStudents());
	}
	
	public static void showListCollageStudent(Course<? super CollageStudent> course) {
		Arrays.toString(course.getStudents());
	}
	
	public static void showListWorker(Course<? super Worker> course) {
		Arrays.toString(course.getStudents());
	}
	
	public static void main(String[] args) {
		Course<Student> course = new Course<>("학생과정", 2);
		course.add(new Student("홍길동", "전산과"));
		course.add(new CollageStudent("심청이", "경제학과", 3));
		course.add(new Student("이순신", "멀티미디어학과"));
		System.out.println(Arrays.toString(course.getStudents()));
	}
}





