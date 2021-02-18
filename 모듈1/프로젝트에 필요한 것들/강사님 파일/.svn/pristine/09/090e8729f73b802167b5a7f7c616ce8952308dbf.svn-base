
public class SQLManager {
	public static class Insert {
		public static final String EMPLOYEE = "INSERT INTO employees VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
		public static final String DEPART = "INSERT INTO depart VALUES (?, ?)";
		public static final String DUTIES = "INSERT INTO duties VALUES (?, ?)";
		public static final String TYPE = "INSERT INTO types VALUES (?, ?)";
	}
	
	public static class Delete {
		public static final String EMPLOYEE = "DELETE FROM employees WHERE emp_code = ?";
		public static final String EMPLOYEE_FROM_DEPART = "DELETE FROM employees WHERE dept_code = ?";
		public static final String EMPLOYEE_FROM_DUTIES = "DELETE FROM employees WHERE duties_code = ?";
		public static final String EMPLOYEE_FROM_TYPE = "DELETE FROM employees WHERE type_code = ?";
		public static final String DEPART = "DELETE FROM depart WHERE dept_code = ?";
		public static final String DUTIES = "DELETE FROM duties WHERE duties_code = ?";
		public static final String TYPE = "DELETE FROM types WHERE type_code = ?";
		public static final String EMPLOYEES_CODE_ALL = "DELETE FROM employees WHERE dept_code = '%s'";				
	}

	public static class Update {
		public static final String EMPLOYEE = "UPDATE employees SET emp_name = ?, dept_code = ?, duties_code = ?, type_code = ?, senior_code = ?, income = ?, worktime = ?";
		public static final String DEPART = "UPDATE depart SET dept_name = ? WHERE dept_code = ?";
		public static final String DUTIES = "UPDATE duties SET duties_name = ? WHERE duties_code = ?";
		public static final String TYPE = "UPDATE types SET type_name = ? WHERE type_code = ?";
	}
	
	public static class Select {
		
		public static final String TYPE_ALL = "SELECT * FROM types";
		public static final String TYPE = "SELECT * FROM types WHERE type_code = ?";
		public static final String TYPE_CODE_COUNT = "SELECT COUNT(*) AS cnt FROM type WHERE type_code = ?";
	}
}
