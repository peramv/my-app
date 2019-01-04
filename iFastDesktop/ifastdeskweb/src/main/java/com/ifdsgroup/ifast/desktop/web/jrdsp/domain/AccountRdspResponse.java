package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import com.fasterxml.jackson.annotation.JsonInclude;

import java.util.Objects;

@JsonInclude(JsonInclude.Include.NON_NULL)
public class AccountRdspResponse extends BaseResponse {
    private AccountRdspDto accountRdsp;

    public AccountRdspDto getAccountRdsp() {
        return accountRdsp;
    }

    public void setAccountRdsp(AccountRdspDto accountRdsp) {
        this.accountRdsp = accountRdsp;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AccountRdspResponse that = (AccountRdspResponse) o;
        return Objects.equals(accountRdsp, that.accountRdsp);
    }

    @Override
    public int hashCode() {

        return Objects.hash(accountRdsp);
    }

    @Override
    public String toString() {
        return "AccountRdspResponse{" +
                "accountRdsp=" + accountRdsp +
                '}';
    }
}

