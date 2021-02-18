package keyholder.vo;

public class PartVo {
	private int partId;
	private String partName;
	
	public PartVo() {}
	public PartVo(int partId, String partName) {
		this.partId = partId;
		this.partName = partName;
	}

	public int getPartId() { return partId; }
	public void setPartId(int partId) { this.partId = partId; }
	public String getPartName() { return partName; }
	public void setPartName(String partName) { this.partName = partName; }
	
	public String toString() {
		return String.format("%d %s", partId, partName);
	}
}
