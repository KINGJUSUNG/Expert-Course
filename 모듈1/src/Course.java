
public class Course<T> {
	private String courseName;
	private T[] students;
	private int count;
	
	@SuppressWarnings("unchecked")
	public Course(String courseName, int capacity) {
		students = (T[])(new Object[capacity]);
		this.courseName = courseName;
		this.count = 0;
	}
	
	public void setCourseName(String courseName) {
		this.courseName = courseName;
	}
	
	public void setStudents(T[] students) {
		this.students = students;
	}
	
	public String getCourseName() {
		return courseName;
	}
	
	public T[] getStudents() {
		return students;
	}
	
	public int getCount() {
		return count;
	}
	
	public void add(T obj) {
		try {
			if (count == students.length) {
				throw new FullException();
			}
			this.students[count++] = obj;
		}
		catch (CourseException e) {
			System.out.println(e.getMessage());
			e.doExcept(this);
			this.add(obj);
		}
		finally {
			;
		}
	}
}









