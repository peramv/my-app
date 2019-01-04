package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;


import java.math.BigDecimal;
import java.util.Objects;

public class NotionalLotUsage {
    private String type;
    private String period;
    private BigDecimal usage;

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getPeriod() {
        return period;
    }

    public void setPeriod(String period) {
        this.period = period;
    }

    public BigDecimal getUsage() {
        return usage;
    }

    public void setUsage(BigDecimal usage) {
        this.usage = usage;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        NotionalLotUsage that = (NotionalLotUsage) o;
        return Objects.equals(type, that.type) &&
            Objects.equals(period, that.period) &&
            Objects.equals(usage, that.usage);
    }

    @Override
    public int hashCode() {

        return Objects.hash(type, period, usage);
    }

    @Override
    public String toString() {
        return "NotionalLotUsage{" +
            "\ntype='" + type + '\'' +
            "\n, period='" + period + '\'' +
            "\n, usage=" + usage +
            '}';
    }
}
