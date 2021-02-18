package keyholder.exception;

public abstract class PartException extends RuntimeException {

	private static final long serialVersionUID = 1L;
	
	public PartException(String message) {
		super(message);
	}
}
