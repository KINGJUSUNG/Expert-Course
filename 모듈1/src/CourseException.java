
public abstract class CourseException extends Exception {
	private static final long serialVersionUID = 1L;

	public CourseException(String name) {
		super(name);
	}
	
	public abstract <T> void doExcept(Course<T> course);
}
