
public class FullException extends CourseException {
	public static final long serialVersionUID = 1L;
	
	public FullException() {
		super("더 이상 좌석이 없습니다.");
	}
	
	public <T> void doExcept(Course<T> course) {
		int newCount = course.getCount() + 1;		
		T[] students = (T[])(new Object[newCount]);
		System.out.println("좌석이 부족하여 정원을 " + newCount + "명으로 늘립니다.");
		System.arraycopy(course.getStudents(), 0, students, 0, course.getCount());
		course.setStudents(students);
	}
}
