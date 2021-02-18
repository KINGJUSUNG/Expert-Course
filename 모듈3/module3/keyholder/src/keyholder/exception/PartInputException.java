package keyholder.exception;

public class PartInputException extends PartException {
	
	private static final long serialVersionUID = 1L;

	public static final String MSG = "�з����� �Է¿� �����Ͽ����ϴ�.";
	
	public PartInputException() {
		this(MSG);
	}
	
	public PartInputException(String message) {
		super(message);
	}
}
