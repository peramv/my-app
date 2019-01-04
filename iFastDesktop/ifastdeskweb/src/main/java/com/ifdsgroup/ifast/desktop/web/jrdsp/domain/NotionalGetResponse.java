package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import javax.xml.bind.annotation.XmlRootElement;

import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AssociatedGrantDto;

@XmlRootElement(name="NotionalGetResponse")
public class NotionalGetResponse extends BaseResponse{
	
	private long contributionAmount;
	private long grantAmount;
	private long bondAmount;
	
	private AssociatedGrantDto associatedGrant;
	
	
	public long getContributionAmount() {
		return contributionAmount;
	}
	public void setContributionAmount(long contributionAmount) {
		contributionAmount = contributionAmount;
	}
	public long getGrantAmount() {
		return grantAmount;
	}
	public void setGrantAmount(long grantAmount) {
		grantAmount = grantAmount;
	}
	public long getBondAmount() {
		return bondAmount;
	}
	public void setBondAmount(long bondAmount) {
		bondAmount = bondAmount;
	}
	public AssociatedGrantDto getAssociatedGrant() {
		return associatedGrant;
	}
	public void setAssociatedGrant(AssociatedGrantDto associatedGrant) {
		this.associatedGrant = associatedGrant;
	}
	
	

}
