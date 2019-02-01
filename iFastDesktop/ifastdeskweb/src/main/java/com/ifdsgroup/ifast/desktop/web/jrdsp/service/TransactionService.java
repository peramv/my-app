package com.ifdsgroup.ifast.desktop.web.jrdsp.service;

import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.HttpEntity;
import org.springframework.http.HttpMethod;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.util.UriComponentsBuilder;

import com.ifdsgroup.ifast.desktop.web.api.dto.GnAcctBalAsOfRequest;
import com.ifdsgroup.ifast.desktop.web.api.dto.GnAcctBalAsOfResponse;
import com.ifdsgroup.ifast.desktop.web.api.dto.RequestHeader;
import com.ifdsgroup.ifast.desktop.web.core.config.DesktopWebConstants;
import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.CommonConstants;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AnnualAmounts;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Contributions;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Element;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ElementList;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.GrantsBonds;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.Limits;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalAnnualAmounts;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalBalanceResponse;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalLotUsage;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.NotionalSummary;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.UsageSummary;
import com.ifdsgroup.ifast.desktop.web.jrdsp.service.model.NotionalBalanceElementUIConfig;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.DateUtil;
import com.ifdsgroup.ifast.desktop.web.jrdsp.util.JRDSPUtil;
import com.ifdsgroup.ifast.desktop.web.service.ApiService;

@Service
public class TransactionService {
	private static final String ANNUAL = "Annual - ";
	private static final String SEPARATOR = "-";
	private static final String EXCLUDE_UNSETTLE_UNITS = "No";
	private static final String NOTIONAL_SUMMARY_PATH = "/account/rdsp%s/notionalBalance";
	private static final String LIMIT_PATH = "/account/rdsp%s/notionalUsage";
	private static final String NOTIONAL_ANNUAL_AMOUNTS_PATH = "/account/rdsp%s/notionalAnnualAmounts";
	
	private static final BigDecimal MAX_LIFE_TIME_CONTRIBUTION = new BigDecimal("200000.00");
	private static final BigDecimal MAX_LIFE_TIME_GRANT = new BigDecimal("70000.00");
	private static final BigDecimal MAX_LIFE_TIME_BOND = new BigDecimal("20000.00");
	private static final BigDecimal MAX_ANNUAL_GRANT = new BigDecimal("3500.00");
	private static final BigDecimal MAX_ANNUAL_BOND = new BigDecimal("1000.00");
	
	private static final String LIFE_TIME_PERIOD = "lifetime";
	private static final String ANNUAL_PERIOD = "annual";
	
	private static final String ERROR_NO_GRANT_USAGE = "No Grant usage info!";
	private static final String ERROR_NO_BOND_USAGE = "No Bond usage info!";

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
		String inceptionDate = accountService.getInceptionDate(String.valueOf(accountNumber));		
		String fromDateStr = inceptionDate;
		
		NotionalBalanceDatePeriod datePeriod = new NotionalBalanceDatePeriod(fromDateStr, toDate, cycleDate, inceptionDate);
		NotionalBalanceResponse response = new NotionalBalanceResponse();

		response.setAccountNumber(accountNumber);
		response.setBeneName(accountService.getBeneName(accountNumber));
		response.setInceptionDate(inceptionDate);
		
		buildNotionalSummary(userId, accountNumber, datePeriod, response);
		
		buildAnnualAmounts(userId, accountNumber, datePeriod, response);
		
		response.setLimitsList(buildLimits(userId, accountNumber, datePeriod));
		
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
			contribution -> {
				contribution.setContCategory(getCategoryText(contribution.getContCategory()));
			});
		
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

	private void buildNotionalSummary(String userId, long accountNumber, NotionalBalanceDatePeriod datePeriod, NotionalBalanceResponse response) {
		NotionalSummary notionalSummary = queryNotionalSummary(accountNumber, datePeriod, userId);
		
		List<Contributions> contributionsList = notionalSummary.getContributionList();
		List<GrantsBonds> grantBondList = notionalSummary.getGrantsBondsList();
		
		buildTotal(contributionsList);
		
		contributionsList.add(createIncomeCategoryContribution(notionalSummary.getAccountIncome()));

		response.setContributionsList(contributionsList);
		response.setGrantsBondsList(grantBondList);

		BigDecimal marketValue = getMarketValue(userId, accountNumber, datePeriod);
		response.setMarketValue(marketValue);
		response.setIncome(buildIncome(contributionsList, grantBondList, marketValue, datePeriod));
	}

	private Contributions createIncomeCategoryContribution(BigDecimal incomeRedemptions) {
		Contributions contributions = new Contributions();
		contributions.setContCategory(NotionalBalanceElementUIConfig.INCOME.getCode());
		contributions.setPurchases(null);
		contributions.setRedemptions(incomeRedemptions);
		
		return contributions;
	}
	
	private void buildTotal(List<Contributions> contributionsList) {
		contributionsList.add(new Contributions(NotionalBalanceElementUIConfig.TOTAL_CONTRIBUTIONS_ROLLOVERS.getCode(), 
				contributionsList.stream().filter(cont -> isContributionRollovers(cont.getContCategory())).map(Contributions::getPurchases).reduce(BigDecimal.ZERO, BigDecimal::add), 
				contributionsList.stream().filter(cont -> isContributionRollovers(cont.getContCategory())).map(Contributions::getRedemptions).reduce(BigDecimal.ZERO, BigDecimal::add), 
				contributionsList.stream().filter(cont -> isContributionRollovers(cont.getContCategory())).map(Contributions::getContBalance).reduce(BigDecimal.ZERO, BigDecimal::add)));
		contributionsList.add(new Contributions(NotionalBalanceElementUIConfig.TOTAL_ROLLOVERS.getCode(), 
				contributionsList.stream().filter(cont -> isTotalRollovers(cont.getContCategory())).map(Contributions::getPurchases).reduce(BigDecimal.ZERO, BigDecimal::add), 
				contributionsList.stream().filter(cont -> isTotalRollovers(cont.getContCategory())).map(Contributions::getRedemptions).reduce(BigDecimal.ZERO, BigDecimal::add), 
				contributionsList.stream().filter(cont -> isTotalRollovers(cont.getContCategory())).map(Contributions::getContBalance).reduce(BigDecimal.ZERO, BigDecimal::add)));		
	}

	private List<Limits> buildLimits(String userId, long accountNumber, NotionalBalanceDatePeriod datePeriod) {
		List<NotionalLotUsage> usages = queryNotionalLotUsage(datePeriod, accountNumber, userId);
		
		List<Limits> limitsList = new ArrayList<>();
		
		if(!datePeriod.isAnnual()) {
			BigDecimal lifetimeContribution = BigDecimal.valueOf(
				usages.stream().filter(
					usage -> (NotionalBalanceElementUIConfig.REGULAR_CONTRIBUTION.getCode().equals(usage.getType()) || 
							NotionalBalanceElementUIConfig.RETIREMENT_SAVINGS_ROLLOVER.getCode().equals(usage.getType()) || 
							NotionalBalanceElementUIConfig.REGULAR_EDUCATION_SAVINGS_ROLLOVER.getCode().equals(usage.getType()))
							&& LIFE_TIME_PERIOD.equals(usage.getPeriod())
				).mapToDouble(usage -> usage.getUsage().doubleValue()).sum()
			);
			
			BigDecimal lifetimeGrant = usages.stream().filter(
				usage -> (NotionalBalanceElementUIConfig.GRANT.getCode().equals(usage.getType()) && LIFE_TIME_PERIOD.equals(usage.getPeriod()))
			).findFirst().orElseThrow(() -> new RuntimeException(ERROR_NO_GRANT_USAGE)).getUsage();
			
			BigDecimal lifetimeBond = usages.stream().filter(
				usage -> (NotionalBalanceElementUIConfig.BOND.getCode().equals(usage.getType()) && LIFE_TIME_PERIOD.equals(usage.getPeriod()))
			).findFirst().orElseThrow(() -> new RuntimeException(ERROR_NO_BOND_USAGE)).getUsage();
			
			
			BigDecimal remainingContribution = MAX_LIFE_TIME_CONTRIBUTION.subtract(lifetimeContribution);
			
			BigDecimal remainingGrant = MAX_LIFE_TIME_GRANT.subtract(lifetimeGrant);
			
			BigDecimal remainingBond = MAX_LIFE_TIME_BOND.subtract(lifetimeBond);
			
			limitsList.add(
				new Limits("Lifetime", MAX_LIFE_TIME_CONTRIBUTION, lifetimeContribution, remainingContribution, MAX_LIFE_TIME_GRANT,
					lifetimeGrant, remainingGrant, MAX_LIFE_TIME_BOND, lifetimeBond , remainingBond));
		} else {
			limitsList.add(new Limits("Lifetime"));
		}
		
		BigDecimal annualGrant = usages.stream().filter(
			usage -> (NotionalBalanceElementUIConfig.GRANT.getCode().equals(usage.getType()) && ANNUAL_PERIOD.equals(usage.getPeriod()))
		).findFirst().orElseThrow(() -> new RuntimeException(ERROR_NO_GRANT_USAGE)).getUsage();
		
		BigDecimal annualBond = usages.stream().filter(
			usage -> (NotionalBalanceElementUIConfig.BOND.getCode().equals(usage.getType()) && ANNUAL_PERIOD.equals(usage.getPeriod()))
		).findFirst().orElseThrow(() -> new RuntimeException(ERROR_NO_BOND_USAGE)).getUsage();
		
		BigDecimal remainingAnnualGrant = MAX_ANNUAL_GRANT.subtract(annualGrant);
		
		BigDecimal remainingAnnualBond = MAX_ANNUAL_BOND.subtract(annualBond);
		
		limitsList.add(
			new Limits("Annual", null, null, null, MAX_ANNUAL_GRANT, annualGrant,
				remainingAnnualGrant, MAX_ANNUAL_BOND, annualBond, remainingAnnualBond));

		return limitsList;
	}

	private BigDecimal buildIncome(List<Contributions> contributionsList, List<GrantsBonds> grantBondList, 
									BigDecimal marketValue, NotionalBalanceDatePeriod datePeriod) {
		BigDecimal income = BigDecimal.ZERO;
		
		if(!datePeriod.isAnnual()) {
			BigDecimal contributionBalance = BigDecimal.ZERO;
			BigDecimal grantBalance = BigDecimal.ZERO;
			BigDecimal bondBalance = BigDecimal.ZERO;

			if (contributionsList != null) {
				contributionBalance = contributionsList.stream()
					.filter(cont -> cont.getContCategory().equals(NotionalBalanceElementUIConfig.REGULAR_CONTRIBUTION.getCode()))
					.findAny().get().getContBalance();
			}
			
			if (grantBondList != null) {
				bondBalance = grantBondList.stream()
					.filter(grantBond -> grantBond.getCategory().equals(NotionalBalanceElementUIConfig.BOND.getCode()))
					.findAny().get().getBalance();
				grantBalance = grantBondList.stream()
					.filter(grantBond -> grantBond.getCategory().equals(NotionalBalanceElementUIConfig.GRANT.getCode()))
					.findAny().get().getBalance();
			}
			
			income = getIncomeBalance(contributionBalance, grantBalance, bondBalance, marketValue);
		} else {
			income = null;
		}
		return income;
	}

	private BigDecimal getIncomeBalance(BigDecimal totalContributions, BigDecimal totalGrant, BigDecimal totalBonds, BigDecimal marketValue) {
		BigDecimal total = totalContributions.add(totalBonds).add(totalGrant);
		return marketValue.compareTo(total) > 0 ? marketValue.subtract(total) : BigDecimal.ZERO;
	}

	private BigDecimal getMarketValue(String userId, long accountNumber, NotionalBalanceDatePeriod datePeriod) {
		BigDecimal marketValue = BigDecimal.ZERO;
		
		if(!datePeriod.isAnnual()) {
			
			GnAcctBalAsOfRequest request = new GnAcctBalAsOfRequest();
			
			request.setAsOfDate(datePeriod.getToDate());
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
				marketValue = response.getAcctBalList().getAcctFundBals().stream().map(acctFundBal -> {
					BigDecimal nav = acctFundBal.getNav() != null ? acctFundBal.getNav() : BigDecimal.ZERO;
					BigDecimal settledUnits = acctFundBal.getSettUnits() != null ? acctFundBal.getSettUnits()
							: BigDecimal.ZERO;
					return nav.multiply(settledUnits);
				}).reduce(BigDecimal.ZERO, BigDecimal::add);
			}
		} else {
			marketValue = null;
		}
		
		return marketValue;
	}
	
	protected void buildAnnualAmounts(String userId, long accountNumber, NotionalBalanceDatePeriod datePeriod, NotionalBalanceResponse response) {
		NotionalAnnualAmounts responseEntity = queryNotionalAnnualAmounts(accountNumber, datePeriod, userId);
		
		if(datePeriod.isAnnual()) {
			response.setAssistanceHoldBack(null);
		} else {
			response.setAssistanceHoldBack(responseEntity.getAhaAmount());
		}
		
		AnnualAmounts annualAmounts = responseEntity.getAnnualAmounts();
		
		if(responseEntity.isEndDateSameYearAsInception()) {
			annualAmounts.setPgap(null);
			annualAmounts.setPgapMax(BigDecimal.ZERO);
			annualAmounts.setLdapMax(BigDecimal.ZERO);
			annualAmounts.setJan1Fmv(BigDecimal.ZERO);
			annualAmounts.setSdspMaxTaxablePortion(BigDecimal.ZERO);
		} else {
			if(null == annualAmounts.getPgap() || annualAmounts.getPgap() == Boolean.FALSE) {
				annualAmounts.setPgapMax(BigDecimal.ZERO);
			}
			if(responseEntity.isSdspAccount()) {
				annualAmounts.setLdapMax(BigDecimal.ZERO);
				if(!datePeriod.isAnnual()) {
					response.setAssistanceHoldBack(BigDecimal.ZERO);
				}
			} else {
				annualAmounts.setSdspMaxTaxablePortion(BigDecimal.ZERO);
			}
		}
		response.setAnnualAmounts(annualAmounts);
	}
	
	private NotionalAnnualAmounts queryNotionalAnnualAmounts(long accountNumber, NotionalBalanceDatePeriod datePeriod, String userId) {
		return ((ResponseEntity<NotionalAnnualAmounts>)(sendNotionalRequest(NOTIONAL_ANNUAL_AMOUNTS_PATH, accountNumber, datePeriod, NotionalAnnualAmounts.class, userId))).getBody();
	}
	
	private List<NotionalLotUsage> queryNotionalLotUsage(NotionalBalanceDatePeriod datePeriod, long accountNumber, String userId) {
		UsageSummary usageSummary = ((ResponseEntity<UsageSummary>)(sendNotionalRequest(LIMIT_PATH, accountNumber, datePeriod, UsageSummary.class, userId))).getBody();
		return usageSummary.getNotionalLotUsages();
	}
	
	private NotionalSummary queryNotionalSummary(long accountNumber, NotionalBalanceDatePeriod datePeriod, String userId) {
		return ((ResponseEntity<NotionalSummary>)(sendNotionalRequest(NOTIONAL_SUMMARY_PATH, accountNumber, datePeriod, NotionalSummary.class, userId))).getBody();
	}
	
	private ResponseEntity<?> sendNotionalRequest(String requestUri, long accountNumber, NotionalBalanceDatePeriod datePeriod, Class<?> x, String userId) {
		MultiValueMap<String, String> headers = JRDSPUtil.addHeaders(String.format(requestUri, ""),
				HttpMethod.GET.name(), "application/json", "1.0", JRDSPUtil.generateTraceId(), userId);
		HttpEntity<?> httpEntity = new HttpEntity<>(headers);

		UriComponentsBuilder builder = UriComponentsBuilder
			.fromUriString(jrdspServiceURL + String.format(NOTIONAL_SUMMARY_PATH, "/" + accountNumber))
			.queryParam("fromDate", datePeriod.getFromDate())
			.queryParam("toDate", datePeriod.getToDate());
		
		String url = builder.build().toUriString();
		
		return  restTemplate.exchange(url, HttpMethod.GET, httpEntity, x);
	}

	private boolean isContributionRollovers(String value) {
		return value.contains(NotionalBalanceElementUIConfig.RETIREMENT_SAVINGS_ROLLOVER.getCode()) ||
				value.contains(NotionalBalanceElementUIConfig.REGULAR_EDUCATION_SAVINGS_ROLLOVER.getCode());
	}
	
	private boolean isTotalRollovers(String value) {
		return value.contains(NotionalBalanceElementUIConfig.TOTAL_CONTRIBUTIONS_ROLLOVERS.getCode()) ||
				value.contains(NotionalBalanceElementUIConfig.REGULAR_CONTRIBUTION.getCode());
	}
}
