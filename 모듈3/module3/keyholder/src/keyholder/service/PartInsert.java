package keyholder.service;

import keyholder.exception.PartException;

public interface PartInsert {
	void execute(String partName) throws PartException; 
}
