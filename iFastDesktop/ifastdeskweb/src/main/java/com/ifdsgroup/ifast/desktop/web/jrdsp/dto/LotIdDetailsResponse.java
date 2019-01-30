package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.Objects;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name = "lotIdDetailsResponse")
public class LotIdDetailsResponse extends BaseResponse {
    private LotIdDetailsDto lotIdDetailsDto;

    public LotIdDetailsDto getLotIdDetailsDto() {
        return lotIdDetailsDto;
    }

    public void setLotIdDetailsDto(LotIdDetailsDto lotIdDetailsDto) {
        this.lotIdDetailsDto = lotIdDetailsDto;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        LotIdDetailsResponse that = (LotIdDetailsResponse) o;
        return Objects.equals(lotIdDetailsDto, that.lotIdDetailsDto);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), lotIdDetailsDto);
    }

    @Override
    public String toString() {
        return "LotIdDetailsResponse{" +
                "lotIdDetailsDto=" + lotIdDetailsDto +
                '}';
    }
}
