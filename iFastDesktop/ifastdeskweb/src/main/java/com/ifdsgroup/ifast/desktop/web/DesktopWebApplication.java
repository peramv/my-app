package com.ifdsgroup.ifast.desktop.web;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

/**
 * This class is the main class for Spring Boot application
 * 
 * @author if993762
 *
 */
@SpringBootApplication
public class DesktopWebApplication { // This is a false positive on sonar.
										// Adding a private constructor will
										// break the spring boot application

	/**
	 * This is the main function that starts the Spring Boot application and
	 * deploys the code base onto embedded default Tomcat server
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		SpringApplication.run(DesktopWebApplication.class, args);
	}
}