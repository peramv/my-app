package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

import org.apache.commons.lang3.StringUtils;

import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.CommonConstants;
import com.ifdsgroup.ifast.desktop.web.jrdsp.enums.NotionalDatePeriodType;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.DateUtil;

public class NotionalBalanceDatePeriod {
	private static final String LIFE_TO_DATE = "Life to Date";
	private static final String ANNUAL = "Annual - ";
	private static final String LAST_DAY_MONTH = "31/12/";
	private static final String FIRST_DAY_MONTH = "01/01/";

	private String fromDate;
	private String toDate;
	private String inceptionDate;
	private String cycleDate;
	private NotionalDatePeriodType dateType;

	public NotionalBalanceDatePeriod(String fromDate, String toDate, String cycleDate, String inceptionDate) {
		setFromDate(fromDate);
		setToDate(toDate);
		setCycleDate(cycleDate);
		setInceptionDate(inceptionDate);
		setDateType(NotionalDatePeriodType.LIFE_TIME);

		if (StringUtils.isNotEmpty(toDate)) {
			if (LIFE_TO_DATE.equals(toDate)) {
				setDateType(NotionalDatePeriodType.LIFE_TIME);
				LocalDate cycleDateLocal = LocalDate.parse(cycleDate,
						DateTimeFormatter.ofPattern(CommonConstants.DATE_FORMAT));
				setToDate(DateUtil.getCurrentDateStr(cycleDateLocal, CommonConstants.DATE_FORMAT));
			} else if (toDate.startsWith(ANNUAL)) {
				setDateType(NotionalDatePeriodType.ANNUAL);
				String selectedYear = toDate.length() < 4 ? toDate : toDate.trim().substring(toDate.length() - 4);
				setToDate(LAST_DAY_MONTH + selectedYear);

				if (DateUtil.getYear(inceptionDate, CommonConstants.DATE_FORMAT) < Integer.parseInt(selectedYear)) {
					setFromDate(FIRST_DAY_MONTH + selectedYear);
				} else {
					setFromDate(inceptionDate);
				}
			} else {
				setDateType(NotionalDatePeriodType.AS_OF);
				setToDate(toDate);
			}
		}
	}

	public boolean isEndDateSameYearAsInception() {
		return getYear(getToDate()).equalsIgnoreCase(getInceptionDate());
	}
	
	protected String getYear(String date) {
		return date.length() < 4 ? date : date.trim().substring(date.length() - 4);
	}

	boolean isAnnual() {
		return getDateType() == NotionalDatePeriodType.ANNUAL;
	}
	
	public String getFromDate() {
		return fromDate;
	}

	public void setFromDate(String fromDate) {
		this.fromDate = fromDate;
	}

	public String getToDate() {
		return toDate;
	}

	public void setToDate(String toDate) {
		this.toDate = toDate;
	}

	public String getInceptionDate() {
		return inceptionDate;
	}

	public void setInceptionDate(String inceptionDate) {
		this.inceptionDate = inceptionDate;
	}

	public String getCycleDate() {
		return cycleDate;
	}

	public void setCycleDate(String cycleDate) {
		this.cycleDate = cycleDate;
	}

	public NotionalDatePeriodType getDateType() {
		return dateType;
	}

	public void setDateType(NotionalDatePeriodType dateType) {
		this.dateType = dateType;
	}

}
