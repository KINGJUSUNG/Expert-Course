
public final class Worker extends Person {
	public final static String TYPE = "직장인";
	private String job;
	
	public Worker(String name, String job) {
		super(name);
		this.job = job;
	}
	
	public void setJob(String job) {
		this.job = job;
	}
	
	public String getJob() {
		return this.job;
	}
	
	public String toString() {
		return super.toString() + " : " + job;
	}
}
