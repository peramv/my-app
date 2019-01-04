package com.ifdsgroup.ifast.desktop.web.jrdsp.util;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.Calendar;
import java.util.Date;

public class DateUtil {
	public static final int getCurrentYear() {
		return  Calendar.getInstance().get(Calendar.YEAR);
	}
	
	public static final int getYear(Date date) {
		 return date.toInstant().atZone(ZoneId.systemDefault()).toLocalDate().getYear();
	}

	public static String getCurrentDateStr(LocalDate cycleDate,String dateFormat) {
	    return cycleDate.format(DateTimeFormatter.ofPattern(dateFormat));
	}
	
	public static final int getYear(String dateStr, String dateFormat) {
		DateTimeFormatter formatter = DateTimeFormatter.ofPattern(dateFormat);
		LocalDate dateTime = LocalDate.parse(dateStr, formatter);
		return dateTime.getYear();
	}
}
