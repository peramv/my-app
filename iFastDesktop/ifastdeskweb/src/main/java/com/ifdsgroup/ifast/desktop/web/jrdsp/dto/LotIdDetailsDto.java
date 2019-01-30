package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;
import java.util.Objects;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name = "lotIdDetailsDto")
public class LotIdDetailsDto {
    private Integer lotId;
    private BigDecimal purchase;
    private BigDecimal redemption;
    private BigDecimal balance;

    public Integer getLotId() {
        return lotId;
    }

    public void setLotId(Integer lotId) {
        this.lotId = lotId;
    }

    public BigDecimal getPurchase() {
        return purchase;
    }

    public void setPurchase(BigDecimal purchase) {
        this.purchase = purchase;
    }

    public BigDecimal getRedemption() {
        return redemption;
    }

    public void setRedemption(BigDecimal redemption) {
        this.redemption = redemption;
    }

    public BigDecimal getBalance() {
        return balance;
    }

    public void setBalance(BigDecimal balance) {
        this.balance = balance;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        LotIdDetailsDto that = (LotIdDetailsDto) o;
        return Objects.equals(lotId, that.lotId) &&
                Objects.equals(purchase, that.purchase) &&
                Objects.equals(redemption, that.redemption) &&
                Objects.equals(balance, that.balance);
    }

    @Override
    public int hashCode() {
        return Objects.hash(lotId, purchase, redemption, balance);
    }

    @Override
    public String toString() {
        return "LotDetailsResponse{" +
                "lotId=" + lotId +
                ", purchase=" + purchase +
                ", redemption=" + redemption +
                ", balance=" + balance +
                '}';
    }
}
