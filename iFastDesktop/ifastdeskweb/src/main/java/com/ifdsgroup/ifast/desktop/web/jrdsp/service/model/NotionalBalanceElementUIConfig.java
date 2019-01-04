package com.ifdsgroup.ifast.desktop.web.jrdsp.service.model;

import java.util.Arrays;

public enum NotionalBalanceElementUIConfig {
    BOND("01", "Bond", 51, true),
    GRANT("02", "Grant", 50, true),
    REGULAR_CONTRIBUTION("03", "Regular_Contributions", 2, true),
    RETIREMENT_SAVINGS_ROLLOVER("04", "Retirement_Savings_Rollovers", 4, true),
    REGULAR_EDUCATION_SAVINGS_ROLLOVER("05", "Reg_Education_Savings_Rollovers", 5, true),
    TOTAL_CONTRIBUTIONS_ROLLOVERS("06", "Total_Rollovers", 3, false),
    TOTAL_ROLLOVERS("07", "Total_Contributions_Rollovers", 1, false),
    INCOME("08", "Income", 6, false);

    public static NotionalBalanceElementUIConfig getConfigByCode(String code) {
        return Arrays.stream(values()).filter(config -> code.equals(config.getCode()))
            .findFirst().orElseThrow(() -> new RuntimeException("Bad code " + code));
    }
    
    private final String code;
    private final String uiKey;
    private Integer uiListPosition;
    private boolean displayAsHyperlink;

    NotionalBalanceElementUIConfig(String code, String uiKey, int uiListPosition, boolean displayAsHyperlink) {
        this.code = code;
        this.uiKey = uiKey;
        this.uiListPosition = uiListPosition;
        this.displayAsHyperlink = displayAsHyperlink;
    }

    public String getCode() {
        return code;
    }

    public String getUiKey() {
        return uiKey;
    }

    public Integer getUiListPosition() {
        return uiListPosition;
    }

    public boolean isDisplayAsHyperlink() {
        return displayAsHyperlink;
    }
}
