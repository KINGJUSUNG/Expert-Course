import java.text.DecimalFormat;

public class Common {	
	public static final char STX = '\u0002';
	public static final char ETX = '\u0003';
	public static final char EOT = '\u0004';
	public static final int CODE_LEN = 10;
	public static final int COUNT_LEN = 4;
	public static final int PRICE_LEN = 10;
	
	public static boolean isEOT(StringBuffer buffer) {
		return (buffer.indexOf("" + EOT) == 0);
	}
	
	public static boolean isValidatePacket(StringBuffer packet) {
		return (packet.indexOf("" + STX) >= 0 && packet.indexOf("" + ETX) >= 0);
	}
	
	public static String currency(String number) {
		DecimalFormat df = new DecimalFormat("#,###");
		return df.format(Integer.parseInt(number.trim()));
	}
}
