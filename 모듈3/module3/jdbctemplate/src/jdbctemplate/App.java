package jdbctemplate;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.AbstractApplicationContext;
import org.springframework.context.support.GenericXmlApplicationContext;

public class App {

	public static void main(String[] args) throws Exception {
		ApplicationContext ctx = new GenericXmlApplicationContext("AppContext.xml");
		((AbstractApplicationContext)ctx).registerShutdownHook();
	}
}
