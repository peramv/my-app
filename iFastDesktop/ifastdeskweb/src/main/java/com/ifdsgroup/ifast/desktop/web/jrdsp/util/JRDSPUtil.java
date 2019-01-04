package com.ifdsgroup.ifast.desktop.web.jrdsp.util;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.UUID;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.BaseResponse;


public class JRDSPUtil {
	
	private static final Logger LOG = LogManager.getLogger(JRDSPUtil.class);
	
	
	public static String booleanToString(boolean bool)
	{
		return (bool) ? "Yes":  "No";

	}
	
	public static boolean stringToBoolean(String boolString)
	{
		return ("Yes".equalsIgnoreCase(boolString)) ? true:false;

	}

	public static String getElectionType(String electionCode) {
		
		//TODO Move elections to Enum
		if(electionCode != null)
		{
			if("1".equalsIgnoreCase(electionCode))
				return "DTC Election";
			if("2".equalsIgnoreCase(electionCode))
				return "SDSP Election";
			if("3".equalsIgnoreCase(electionCode))
				return "Specified Year";
		}
		return "";
	}
	
	public static String getElectionCode(String electionType) {

		//TODO Move elections to Enum
		if(electionType != null)
		{
			if("DTC Election".equalsIgnoreCase(electionType))
				return "1";
			if("SDSP Election".equalsIgnoreCase(electionType))
				return "2";
			if("Specified Year".equalsIgnoreCase(electionType))
				return "3";
		}
		return null;
	}

	public static MultiValueMap<String, String> addHeaders(String httpPath,String method, String acceptType,String apiVersion,String traceId){
		MultiValueMap<String, String> headers = new LinkedMultiValueMap<String, String>();
		if(checkNotNull(httpPath,method,acceptType,apiVersion,traceId))
		{
			headers.add("HTTP_Path", httpPath);
			headers.add("HTTP_Method", method);
			headers.add("accept", acceptType);
			headers.add("x-api-version", apiVersion);
		}
		
		return headers;
		
	}
	
	public static boolean checkNotNull(String ...strings  ) {
		
		for(String s:strings)
		{
			if(s!=null && !s.isEmpty() )
				continue;
			else
				return false;
		}
		
		return true;
	}
	
	public static String generateTraceId()
	{
		UUID uuid = UUID.randomUUID();
		return uuid.toString();
 
	}
	
	public static Date convertStringToDate(String stringDate) throws ParseException {
		
		Date date=null;
		if(stringDate!=null) {
			DateFormat format = new SimpleDateFormat("d/M/y", Locale.ENGLISH);
			date = format.parse(stringDate);
			System.out.println(date); 
			
		}
		
		return date;
	}
	
	
	public static void printObject(Object obj) {
		
		ObjectMapper mapper = new ObjectMapper();
		
		try {
			LOG.debug(mapper.writeValueAsString(obj));
		} catch (JsonProcessingException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
	public static BaseResponse buildErrorResponse(int errorCode, String errorText) {
		BaseResponse error=new BaseResponse();
		error.setStatusCodeValue(errorCode);
		error.setStatusCodeText(errorText);
		return error;
	}
	

}
