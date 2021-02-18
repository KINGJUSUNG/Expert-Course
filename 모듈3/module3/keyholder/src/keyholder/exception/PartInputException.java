package keyholder.exception;

public class PartInputException extends PartException {
	
	private static final long serialVersionUID = 1L;

	public static final String MSG = "분류정보 입력에 실패하였습니다.";
	
	public PartInputException() {
		this(MSG);
	}
	
	public PartInputException(String message) {
		super(message);
	}
}
