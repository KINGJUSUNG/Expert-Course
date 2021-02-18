
public class Employee {
	private String code;
	private String name;
	private String deptCode;
	private String typeCode;
	private String dutieCode;
	private String seniorCode;
	private int income;
	private int worktime;
	private Depart depart;
	private Dutie dutie;
	private Type type;
	
	public Employee() {}

	public Employee(String code, String name, String deptCode, String typeCode, String dutieCode, String seniorCode,
			int income, int worktime) {
		this.code = code;
		this.name = name;
		this.deptCode = deptCode;
		this.typeCode = typeCode;
		this.dutieCode = dutieCode;
		this.seniorCode = seniorCode;
		this.income = income;
		this.worktime = worktime;
	}

	public String getCode() {
		return code;
	}

	public void setCode(String code) {
		this.code = code;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDeptCode() {
		return deptCode;
	}

	public void setDeptCode(String deptCode) {
		this.deptCode = deptCode;
	}

	public String getTypeCode() {
		return typeCode;
	}

	public void setTypeCode(String typeCode) {
		this.typeCode = typeCode;
	}

	public String getDutieCode() {
		return dutieCode;
	}

	public void setDutieCode(String dutieCode) {
		this.dutieCode = dutieCode;
	}

	public String getSeniorCode() {
		return seniorCode;
	}

	public void setSeniorCode(String seniorCode) {
		this.seniorCode = seniorCode;
	}

	public int getIncome() {
		return income;
	}

	public void setIncome(int income) {
		this.income = income;
	}

	public int getWorktime() {
		return worktime;
	}

	public void setWorktime(int worktime) {
		this.worktime = worktime;
	}
	
	public Depart getDepart() {
		return depart;
	}
	
	public void setDepart(Depart depart) {
		this.depart = depart;
	}
	
	public Dutie getDutie() {
		return dutie;
	}
	
	public void setDutie(Dutie dutie) {
		this.dutie = dutie;
	}
	
	public Type getType() {
		return type;
	}
	
	public void setType(Type type) {
		this.type = type;
	}
	
}
