package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import com.ifdsgroup.ifast.desktop.web.jrdsp.enums.NotionalDatePeriodType;

public class NotionalBalanceDatePeriodTest {
	private static final String LIFE_TO_DATE = "Life to Date";
	
	@Test
	public void testLifeTimePeriod() {
		String fromDate = "21/12/2006";
		String cycleDate = "20/01/2012";
		String inceptionDate = "02/01/2005";
		NotionalBalanceDatePeriod datePeriod = new NotionalBalanceDatePeriod(fromDate, LIFE_TO_DATE, cycleDate, inceptionDate);
		assertEquals(datePeriod.getToDate(), cycleDate);
		assertEquals(datePeriod.getFromDate(), fromDate);
		assertEquals(datePeriod.getDateType(), NotionalDatePeriodType.LIFE_TIME);
	}
	
	@Test
	public void testAnnualDatePeriod() {
		String fromDate = "21/12/2006";
		String cycleDate = "20/01/2012";
		String inceptionDateBeforeYearOfAnnualEndDate = "02/01/2005";
		NotionalBalanceDatePeriod datePeriod = new NotionalBalanceDatePeriod(fromDate, "Annual - 2018", cycleDate, inceptionDateBeforeYearOfAnnualEndDate);
		assertEquals(datePeriod.getFromDate(), "01/01/2018");
		assertEquals(datePeriod.getToDate(), "31/12/2018");
		assertEquals(datePeriod.getDateType(), NotionalDatePeriodType.ANNUAL);
		
		String inceptionDateWithinAnnualDate = "02/03/2018";
		
		datePeriod = new NotionalBalanceDatePeriod(fromDate, "Annual - 2018", cycleDate, inceptionDateWithinAnnualDate);
		assertEquals(datePeriod.getFromDate(), inceptionDateWithinAnnualDate);
		assertEquals(datePeriod.getToDate(), "31/12/2018");
		assertEquals(datePeriod.getDateType(), NotionalDatePeriodType.ANNUAL);
	}
	
	@Test
	public void testAsOfDatePeriod() {
		String fromDate = "21/12/2006";
		String cycleDate = "20/01/2012";
		String inceptionDate = "02/01/2005";
		String asOfDate = "09/08/2019";
		
		NotionalBalanceDatePeriod datePeriod = new NotionalBalanceDatePeriod(fromDate, asOfDate, cycleDate, inceptionDate);
		assertEquals(datePeriod.getFromDate(), fromDate);
		assertEquals(datePeriod.getToDate(), asOfDate);
		assertEquals(datePeriod.getDateType(), NotionalDatePeriodType.AS_OF);
	}
}
