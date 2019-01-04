package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import com.ifdsgroup.ifast.desktop.web.api.dto.GnAcctBalAsOfRequest;
import com.ifdsgroup.ifast.desktop.web.api.dto.GnAcctBalAsOfResponse;
import com.ifdsgroup.ifast.desktop.web.api.dto.RequestHeader;
import com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.CommonConstants;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Contributions;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Element;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ElementList;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.GrantsBonds;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalLotUsage;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.UsageSummary;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Limits;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalBalanceResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalSummary;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.model.NotionalBalanceElementUIConfig;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.DateUtil;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.JRDSPUtil;
import com.ifdsgroup.ifast.desktop.web.service.ApiService;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.util.UriComponentsBuilder;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class TransactionService {

	private static final String LIFE_TO_DATE = "Life to Date";
	private static final String ANNUAL = "Annual - ";
	private static final String LAST_DAY_MONTH = "31/12/";
	private static final String SEPARATOR = "-";
	private static final String FIRST_DAY_MONTH = "01/01/";
	private static final String EXCLUDE_UNSETTLE_UNITS = "No";
	private static final String NOTIONAL_SUMMARY_PATH = "/account/rdsp%s/notionalBalance";
	private static final String ROLLOVER = "Rollover";
	private static final String LIMIT_PATH = "/account/rdsp%s/notionalUsage";

	@Autowired
	RestTemplate restTemplate;

	@Autowired
	ApiService apiService;

	@Autowired
	AccountService accountService;

	@Value("${ifast.clientCode}")
	String clientCode;

	@Value("${jrdsp.services.url}")
	private String jrdspServiceURL;

	public NotionalBalanceResponse getNotionalBalance(String userId, long accountNumber, String toDate,String cycleDate) {
		String toDateStr = null;
		String inceptionDate = accountService.getInceptionDate(String.valueOf(accountNumber));
		String fromDateStr = inceptionDate;
		if (StringUtils.isNotEmpty(toDate)) {
			if (LIFE_TO_DATE.equals(toDate)) {
				LocalDate cycleDateLocal =  LocalDate.parse(cycleDate, DateTimeFormatter.ofPattern(CommonConstants.DATE_FORMAT));
				toDateStr = DateUtil.getCurrentDateStr(cycleDateLocal,CommonConstants.DATE_FORMAT);
			} else if (toDate.startsWith(ANNUAL)) {
				String selectedYear = toDate.length() < 4 ? toDate : toDate.trim().substring(toDate.length() - 4);
				toDateStr = LAST_DAY_MONTH + selectedYear;
				if (DateUtil.getYear(inceptionDate, CommonConstants.DATE_FORMAT) < Integer.parseInt(selectedYear)) {
					fromDateStr = FIRST_DAY_MONTH + selectedYear;
				} else {
					fromDateStr = inceptionDate;
				}
			} else {
				toDateStr = toDate;
			}
		}
		NotionalBalanceResponse response = new NotionalBalanceResponse();
		response.setAccountNumber(accountNumber);
		response.setBeneName(accountService.getBeneName(accountNumber));

		response.setInceptionDate(inceptionDate);
		buildNotionalSummary(userId, accountNumber, fromDateStr, toDateStr, response);
		buildLimits(accountNumber, fromDateStr, toDateStr, response);
		response.setList(createElementList(inceptionDate,cycleDate));

		response.setContributionsList(response.getContributionsList().stream()
			.sorted(Comparator.comparing(
				contribution -> NotionalBalanceElementUIConfig.getConfigByCode(
					contribution.getContCategory()).getUiListPosition())
			)
			.collect(Collectors.toList()));

		response.setGrantsBondsList(response.getGrantsBondsList().stream()
			.sorted(Comparator.comparing(
				grantOrBond -> NotionalBalanceElementUIConfig.getConfigByCode(
					grantOrBond.getCategory()).getUiListPosition())
			)
			.collect(Collectors.toList()));

		response.getContributionsList().forEach(
			contribution -> contribution.setContCategory(getCategoryText(contribution.getContCategory())));
		response.getGrantsBondsList().forEach(
			grantBond -> grantBond.setCategory(getCategoryText(grantBond.getCategory())));

		return response;
	}

	private String getCategoryText(String category) {
		NotionalBalanceElementUIConfig categoryConfig = NotionalBalanceElementUIConfig.getConfigByCode(category);
		return categoryConfig.isDisplayAsHyperlink() + SEPARATOR + categoryConfig.getUiKey();
	}

	private ElementList createElementList(String inceptionDate,String cycleDate) {
		int inceptionYear = DateUtil.getYear(inceptionDate, CommonConstants.DATE_FORMAT);
		int currentYear = DateUtil.getYear(cycleDate, CommonConstants.DATE_FORMAT);
		List<Element> elementList = new ArrayList<>();
		elementList.add(new Element("Life to Date", "Life to Date"));
		for (int i = currentYear; i >= inceptionYear; i--) {
			elementList.add(new Element(ANNUAL + i, ANNUAL + i));
		}
		com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ElementList list = new com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ElementList();
		list.setListName("periodList");
		list.setElements(elementList);
		return list;
	}

	private void buildNotionalSummary(String userId, long accountNumber, String fromDate, String toDate,
									  NotionalBalanceResponse response) {
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(String.format(NOTIONAL_SUMMARY_PATH, ""),
				HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId());
		HttpEntity<?> httpEntity = new HttpEntity<>(headers);

		UriComponentsBuilder builder = UriComponentsBuilder
			.fromUriString(jrdspServiceURL + String.format(NOTIONAL_SUMMARY_PATH, "/" + accountNumber))
			.queryParam("fromDate", fromDate)
			.queryParam("toDate", toDate);
		String url = builder.build().toUriString();
		ResponseEntity<NotionalSummary> responseEntity = restTemplate.exchange(
			url, HttpMethod.GET, httpEntity, NotionalSummary.class);

		List<Contributions> contributionsList = responseEntity.getBody().getContributionList();
		List<GrantsBonds> grantBondList = responseEntity.getBody().getGrantsBondsList();
		buildTotal(contributionsList);
		contributionsList.add(buildIncome(userId, contributionsList, grantBondList, accountNumber, toDate));
		response.setContributionsList(contributionsList);
		response.setGrantsBondsList(responseEntity.getBody().getGrantsBondsList());
	}

	private void buildTotal(List<Contributions> contributionsList) {
		contributionsList.add(new Contributions("06", contributionsList.stream().filter(cont -> cont.getContCategory().contains("04") || cont.getContCategory().contains("05")).map(Contributions::getPurchases).reduce(BigDecimal.ZERO, BigDecimal::add), 
				contributionsList.stream().filter(cont -> cont.getContCategory().contains("04") || cont.getContCategory().contains("05")).map(Contributions::getRedemptions).reduce(BigDecimal.ZERO, BigDecimal::add), 
				contributionsList.stream().filter(cont -> cont.getContCategory().contains("04") || cont.getContCategory().contains("05")).map(Contributions::getContBalance).reduce(BigDecimal.ZERO, BigDecimal::add)));
		contributionsList.add(new Contributions("07", contributionsList.stream().filter(cont -> cont.getContCategory().contains("06") || cont.getContCategory().contains("03")).map(Contributions::getPurchases).reduce(BigDecimal.ZERO, BigDecimal::add), 
				contributionsList.stream().filter(cont -> cont.getContCategory().contains("06") || cont.getContCategory().contains("03")).map(Contributions::getRedemptions).reduce(BigDecimal.ZERO, BigDecimal::add), 
				contributionsList.stream().filter(cont -> cont.getContCategory().contains("06") || cont.getContCategory().contains("03")).map(Contributions::getContBalance).reduce(BigDecimal.ZERO, BigDecimal::add)));		
	}

	private void buildLimits(long accountNumber, String fromDate, String toDate,
			NotionalBalanceResponse response) {
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(String.format(LIMIT_PATH, ""),
				HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId());
		HttpEntity<?> httpEntity = new HttpEntity<>(headers);
		UriComponentsBuilder builder = UriComponentsBuilder
			.fromUriString(jrdspServiceURL + String.format(LIMIT_PATH, "/" + accountNumber))
			.queryParam("fromDate", fromDate)
			.queryParam("toDate", toDate);
		String url = builder.build().toUriString();
		ResponseEntity<UsageSummary> responseEntity = restTemplate.exchange(url, HttpMethod.GET, httpEntity, UsageSummary.class);
		List<NotionalLotUsage> usages = responseEntity.getBody().getNotionalLotUsages();

		// TODO Replace the "max" hardcoded values below to configurable values
		List<Limits> limitsList = new ArrayList<>();
		BigDecimal lifetimeContribution = BigDecimal.valueOf(
			usages.stream().filter(
				usage -> ("03".equals(usage.getType()) || "04".equals(usage.getType()) || "05".equals(usage.getType()))
						&& "lifetime".equals(usage.getPeriod())
			).mapToDouble(usage -> usage.getUsage().doubleValue()).sum()
		);
		BigDecimal lifetimeGrant = usages.stream().filter(
			usage -> ("02".equals(usage.getType()) && "lifetime".equals(usage.getPeriod()))
		).findFirst().orElseThrow(() -> new RuntimeException("No Grant usage info!")).getUsage();
		BigDecimal lifetimeBond = usages.stream().filter(
			usage -> ("01".equals(usage.getType()) && "lifetime".equals(usage.getPeriod()))
		).findFirst().orElseThrow(() -> new RuntimeException("No Bond usage info!")).getUsage();
		BigDecimal maxLifetimeContribution = new BigDecimal("200000.00");
		BigDecimal remainingContribution = maxLifetimeContribution.subtract(lifetimeContribution);
		BigDecimal maxLifetimeGrant = new BigDecimal("70000.00");
		BigDecimal remainingGrant = maxLifetimeGrant.subtract(lifetimeGrant);
		BigDecimal maxLifetimeBond = new BigDecimal("20000.00");
		BigDecimal remainingBond = maxLifetimeBond.subtract(lifetimeBond);
		limitsList.add(
			new Limits("Lifetime", maxLifetimeContribution, lifetimeContribution, remainingContribution, maxLifetimeGrant,
				lifetimeGrant, remainingGrant, maxLifetimeBond, lifetimeBond,remainingBond));

		BigDecimal annualGrant = usages.stream().filter(
			usage -> ("02".equals(usage.getType()) && "annual".equals(usage.getPeriod()))
		).findFirst().orElseThrow(() -> new RuntimeException("No Grant usage info!")).getUsage();
		BigDecimal annualBond = usages.stream().filter(
			usage -> ("01".equals(usage.getType()) && "annual".equals(usage.getPeriod()))
		).findFirst().orElseThrow(() -> new RuntimeException("No Bond usage info!")).getUsage();
		BigDecimal maxAnnualGrant = new BigDecimal("3500.00");
		BigDecimal remainingAnnualGrant = maxAnnualGrant.subtract(annualGrant);
		BigDecimal maxAnnualBond = new BigDecimal("1000.00");
		BigDecimal remainingAnnualBond = maxAnnualBond.subtract(annualBond);
		limitsList.add(
			new Limits("Annual", null, null, null, maxAnnualGrant, annualGrant,
				remainingAnnualGrant, maxAnnualBond, annualBond, remainingAnnualBond));

		response.setLimitsList(limitsList);
	}

	private Contributions buildIncome(String userId, List<Contributions> contributionsList, List<GrantsBonds> grantBondList,
									  long accountNumber, String toDate) {
		Contributions contributions = new Contributions();
		contributions.setContCategory("08");
		contributions.setPurchases(null);
		contributions.setRedemptions(new BigDecimal("0"));
		BigDecimal contributionBalance = new BigDecimal(0);
		if (contributionsList != null) {
			contributionBalance = contributionsList.stream()
				.filter(cont -> cont.getContCategory().equals("03")).findAny().get()
				.getContBalance();
		}
		BigDecimal grantBalance = new BigDecimal(0);
		BigDecimal bondBalance = new BigDecimal(0);
		if (grantBondList != null) {
			bondBalance = grantBondList.stream().filter(grantBond -> grantBond.getCategory().equals("01"))
				.findAny().get().getBalance();
			grantBalance = grantBondList.stream().filter(grantBond -> grantBond.getCategory().equals("02"))
				.findAny().get().getBalance();
		}
		contributions.setContBalance(getIncomeBalance(contributionBalance, grantBalance, bondBalance,
				getMarketValue(userId, accountNumber, toDate)));
		return contributions;
	}

	private BigDecimal getIncomeBalance(BigDecimal totContributions, BigDecimal totGrant, BigDecimal totBonds,
			BigDecimal marketValue) {
		BigDecimal total = totContributions.add(totBonds).add(totGrant);
		return marketValue.compareTo(total) > 0 ? marketValue.subtract(total) : BigDecimal.ZERO;
	}

	private BigDecimal getMarketValue(String userId, long accountNumber, String asOfDate) {
		GnAcctBalAsOfRequest request = new GnAcctBalAsOfRequest();
		request.setAsOfDate(asOfDate);
		request.setAcct(accountNumber);
		request.setInclUnsettled(EXCLUDE_UNSETTLE_UNITS);
		RequestHeader requestHeader = new RequestHeader();
		requestHeader.setApiName(DesktopWebConstants.ACCTBALASOF_API);
		requestHeader.setRuserid(userId);
		requestHeader.setClientCode(clientCode);
		requestHeader.setInterfaceName(DesktopWebConstants.ACCTBALASOF_INTERFACE);
		requestHeader.setDataMode(DesktopWebConstants.API_DATA_MODE);
		requestHeader.setDownLoadMode(DesktopWebConstants.API_DOWNLOAD_MODE);
		requestHeader.setDateFormat(DesktopWebConstants.API_DATE_FORMAT);
		
		//Since marketValue is number language doesn't matter
		requestHeader.setLocale(DesktopWebConstants.API_DEFAULT_LANGUAGE); 
		request.setRequestHeader(requestHeader);
		GnAcctBalAsOfResponse response = apiService.inquireApi(request, GnAcctBalAsOfResponse.class);
		if (response != null && response.getAcctBalList() != null
				&& response.getAcctBalList().getAcctFundBals() != null) {
			return response.getAcctBalList().getAcctFundBals().stream().map(acctFundBal -> {
				BigDecimal nav = acctFundBal.getNav() != null ? acctFundBal.getNav() : BigDecimal.ZERO;
				BigDecimal settledUnits = acctFundBal.getSettUnits() != null ? acctFundBal.getSettUnits()
						: BigDecimal.ZERO;
				return nav.multiply(settledUnits);
			}).reduce(BigDecimal.ZERO, BigDecimal::add);
		}
		return new BigDecimal(0);
	}

}
