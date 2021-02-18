package jdbc.vo;

public class PartVO {
	private int partId;
	private String partName;

	public PartVO() {}
	public PartVO(int partId, String partName) {
		super();
		this.partId = partId;
		this.partName = partName;
	}
	public int getPartId() { return partId; }
	public void setPartId(int partId) { this.partId = partId; }
	public String getPartName() { return partName; }
	public void setPartName(String partName) { this.partName = partName;}

	public String toString() {
		return String.format("분류번호: %d, 분류명: %s", partId, partName);
	}
}
