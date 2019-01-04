package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

public class AccountRdspPutRequest extends BaseRequest {
    private AccountRdspDto accountRdsp;

    public AccountRdspDto getAccountRdsp() {
        return accountRdsp;
    }

    public void setAccountRdsp(AccountRdspDto accountRdsp) {
        this.accountRdsp = accountRdsp;
    }
}
