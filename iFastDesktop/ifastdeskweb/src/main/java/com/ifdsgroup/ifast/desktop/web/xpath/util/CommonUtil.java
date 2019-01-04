package com.ifdsgroup.ifast.desktop.web.xpath.util;

import java.util.Enumeration;

import javax.servlet.http.HttpServletRequest;

/**
 * Utility class
 * 
 * @author if993762
 */
public class CommonUtil {

	/**
	 * This method returns the request header details
	 * 
	 * @param servletRequest The HttpServletRequest Object
	 * @return concatenated string of key value pair of header information
	 */
	public static String getHeaderInfo(HttpServletRequest servletRequest) {

		StringBuilder strBuilder = new StringBuilder();
		Enumeration<String> headerNames = servletRequest.getHeaderNames();
		if (headerNames != null) {
			while (headerNames.hasMoreElements()) {
				String headerName = headerNames.nextElement();
				String headerValue = servletRequest.getHeader(headerName);
				strBuilder.append(headerName).append("=").append(headerValue).append("\n");
			}
		}

		return strBuilder.toString();
	}

}
