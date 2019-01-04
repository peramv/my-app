package com.ifds.iFast.api;

public class SonicConfigException extends Exception {
	public SonicConfigException(String msg) {
		super(msg);
	}

	public SonicConfigException() {
		this("Sonic configuration file is missing or invalid.");
	}

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

}
