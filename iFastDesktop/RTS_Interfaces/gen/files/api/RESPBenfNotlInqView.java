
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Beneficiary Notional Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RESPBenfNotlInq.doc">RESPBenfNotlInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPBenfNotlInqView extends IFastView implements Serializable
{

   /**
    * Record Level member variable.
    */
   private String _RecordLevel = null;
   
   /**
    * YTD Contribution member variable.
    */
   private String _YTDContribution = null;
   
   /**
    * TD Contribution member variable.
    */
   private String _TDContribution = null;
   
   /**
    * Grant Amount member variable.
    */
   private String _GrantAmount = null;
   
   /**
    * Additional Grant member variable.
    */
   private String _AdditionalGrant = null;
   
   /**
    * CLB Amount member variable.
    */
   private String _CLBAmount = null;
   
   /**
    * PGrant Amount member variable.
    */
   private String _PGrantAmount = null;
   
   /**
    * TD Redemption Contribution member variable.
    */
   private String _TDRedContrib = null;
   
   /**
    * TD Redemption Earnings member variable.
    */
   private String _TDRedEarnings = null;
   
   /**
    * Redemption CESG member variable.
    */
   private String _RedCESG = null;
   
   /**
    * Redemtion CLB member variable.
    */
   private String _RedCLB = null;
   
   /**
    * Redemption PGrant member variable.
    */
   private String _RedPGrant = null;
   
   /**
    * UC Amount member variable.
    */
   private String _UCAmount = null;
   
   /**
    * AC Amount member variable.
    */
   private String _ACAmount = null;
   
   /**
    * Pre98 Contribution member variable.
    */
   private String _Pre98Contrib = null;
   
   /**
    * Pre98 Redemption Contribution member variable.
    */
   private String _Pre98RedContrib = null;
   
   /**
    * RESP Beneficiary ID member variable.
    */
   private String _RESPBenefID = null;
   
   /**
    * Entity Type member variable.
    */
   private String _EntityType = null;
   
   /**
    * Entity Type Sequnce member variable.
    */
   private Integer _EntityTypeSeq = null;
   
   /**
    * RESP Beneficiary ID To member variable.
    */
   private String _RESPBenefIDTo = null;
   
   /**
    * Entity Type To member variable.
    */
   private String _EntityTypeTo = null;
   
   /**
    * Entity Type Sequnce To member variable.
    */
   private Integer _EntityTypeSeqTo = null;
   
   /**
    * RESP Allocation Percent member variable.
    */
   private String _RESPAllocPrcnt = null;
   
   /**
    * Beneficiary Tainted member variable.
    */
   private Boolean _Tainted = null;
   
   /**
    * End date of beneficiary being tained member variable.
    */
   private Date _TaintEndDate = null;
   
   /**
    * Flag if contributions should be report to HRDC member variable.
    */
   private Boolean _GrantRequest = null;
   
   /**
    * Beneficiary Date of Birth member variable.
    */
   private Date _BenefDofB = null;
   
   /**
    * Tax Jurisdiction member variable.
    */
   private String _TaxJuris = null;
   
   /**
    * Relation member variable.
    */
   private String _Relation = null;
   
   /**
    * Beneficiary Effective Date member variable.
    */
   private Date _BenefEffectiveDate = null;
   
   /**
    * Transfer Percent member variable.
    */
   private String _TransferPercent = null;
   
   /**
    * Account Level Override member variable.
    */
   private Boolean _AcctLvlOverride = null;
   
   /**
    * QESI UC Amount member variable.
    */
   private String _QESIUCAmount = null;
   
   /**
    * QESI AC Amount member variable.
    */
   private String _QESIACAmount = null;
   
   /**
    * QESI YTD Contribution member variable.
    */
   private String _QESIYTDContribution = null;
   
   /**
    * QESI Basic Grant member variable.
    */
   private String _QESIBasicGrant = null;
   
   /**
    * QESI Increase Amount member variable.
    */
   private String _QESIIncreaseAmt = null;
   
   /**
    * Pre98 QESI Contribution member variable.
    */
   private String _Pre98QESIContrib = null;
   
   /**
    * Pre2007 QESI Contribution member variable.
    */
   private String _Pre2007QESIContrib = null;
   
   /**
    * RESP External Transaction Detail UUID member variable.
    */
   private String _RESPExtTrDetlUUID = null;
   
   /**
    * RESP External Transaction Detel Version member variable.
    */
   private Integer _RESPExtTrDetlVer = null;
   
   /**
    * RESP Contribution Detail UUID member variable.
    */
   private String _RESPContrDetlUUID = null;
   
   /**
    * RESP Contribution Detail Version member variable.
    */
   private Integer _RESPContrDetlVer = null;
   
   /**
    * EligibleTransfer member variable.
    */
   private Boolean _EligTransfer = null;
   
   /**
    * CESG Paid member variable.
    */
   private String _CESGPaid = null;
   
   /**
    * QESI Paid member variable.
    */
   private String _QESIPaid = null;
   
   /**
    * IsResidualCESG member variable.
    */
   private Boolean _IsResidualCESG = null;
   
   /**
    * SAGES Grant member variable.
    */
   private String _SAGESGrant = null;
   
   /**
    * SAGES UC Amount member variable.
    */
   private String _SAGESUCAmount = null;
   
   /**
    * SAGES AC Amount member variable.
    */
   private String _SAGESACAmount = null;
   

   /**
    * Constructs the RESPBenfNotlInqView object.
    * 
    */
   public RESPBenfNotlInqView()
   {
      super ( new RESPBenfNotlInqRequest() );
   }

   /**
    * Constructs the RESPBenfNotlInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESPBenfNotlInqView( String hostEncoding )
   {
      super ( new RESPBenfNotlInqRequest( hostEncoding ) );
   }

   /**
    * Gets the RESPBenfNotlInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESPBenfNotlInqRequest object.
    */
   public final RESPBenfNotlInqRequest getRequest()
   {
      return (RESPBenfNotlInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Record Level field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Record Level or null.
    */
   public final String getRecordLevel()
   {
      return _RecordLevel;
   }
	
   /**
    * Gets the Record Level field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Record Level or the specified default value.
    */
   public final String getRecordLevel( String defaultValue )
   {
      return _RecordLevel == null ? defaultValue : _RecordLevel;
   }
                  
   /**
    * Gets the YTD Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the YTD Contribution or null.
    */
   public final String getYTDContribution()
   {
      return _YTDContribution;
   }
	
   /**
    * Gets the YTD Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the YTD Contribution or the specified default value.
    */
   public final String getYTDContribution( String defaultValue )
   {
      return _YTDContribution == null ? defaultValue : _YTDContribution;
   }
                  
   /**
    * Gets the TD Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TD Contribution or null.
    */
   public final String getTDContribution()
   {
      return _TDContribution;
   }
	
   /**
    * Gets the TD Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TD Contribution or the specified default value.
    */
   public final String getTDContribution( String defaultValue )
   {
      return _TDContribution == null ? defaultValue : _TDContribution;
   }
                  
   /**
    * Gets the Grant Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Grant Amount or null.
    */
   public final String getGrantAmount()
   {
      return _GrantAmount;
   }
	
   /**
    * Gets the Grant Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Grant Amount or the specified default value.
    */
   public final String getGrantAmount( String defaultValue )
   {
      return _GrantAmount == null ? defaultValue : _GrantAmount;
   }
                  
   /**
    * Gets the Additional Grant field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Additional Grant or null.
    */
   public final String getAdditionalGrant()
   {
      return _AdditionalGrant;
   }
	
   /**
    * Gets the Additional Grant field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Additional Grant or the specified default value.
    */
   public final String getAdditionalGrant( String defaultValue )
   {
      return _AdditionalGrant == null ? defaultValue : _AdditionalGrant;
   }
                  
   /**
    * Gets the CLB Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CLB Amount or null.
    */
   public final String getCLBAmount()
   {
      return _CLBAmount;
   }
	
   /**
    * Gets the CLB Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CLB Amount or the specified default value.
    */
   public final String getCLBAmount( String defaultValue )
   {
      return _CLBAmount == null ? defaultValue : _CLBAmount;
   }
                  
   /**
    * Gets the PGrant Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the PGrant Amount or null.
    */
   public final String getPGrantAmount()
   {
      return _PGrantAmount;
   }
	
   /**
    * Gets the PGrant Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PGrant Amount or the specified default value.
    */
   public final String getPGrantAmount( String defaultValue )
   {
      return _PGrantAmount == null ? defaultValue : _PGrantAmount;
   }
                  
   /**
    * Gets the TD Redemption Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TD Redemption Contribution or null.
    */
   public final String getTDRedContrib()
   {
      return _TDRedContrib;
   }
	
   /**
    * Gets the TD Redemption Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TD Redemption Contribution or the specified default value.
    */
   public final String getTDRedContrib( String defaultValue )
   {
      return _TDRedContrib == null ? defaultValue : _TDRedContrib;
   }
                  
   /**
    * Gets the TD Redemption Earnings field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the TD Redemption Earnings or null.
    */
   public final String getTDRedEarnings()
   {
      return _TDRedEarnings;
   }
	
   /**
    * Gets the TD Redemption Earnings field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the TD Redemption Earnings or the specified default value.
    */
   public final String getTDRedEarnings( String defaultValue )
   {
      return _TDRedEarnings == null ? defaultValue : _TDRedEarnings;
   }
                  
   /**
    * Gets the Redemption CESG field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemption CESG or null.
    */
   public final String getRedCESG()
   {
      return _RedCESG;
   }
	
   /**
    * Gets the Redemption CESG field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption CESG or the specified default value.
    */
   public final String getRedCESG( String defaultValue )
   {
      return _RedCESG == null ? defaultValue : _RedCESG;
   }
                  
   /**
    * Gets the Redemtion CLB field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemtion CLB or null.
    */
   public final String getRedCLB()
   {
      return _RedCLB;
   }
	
   /**
    * Gets the Redemtion CLB field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemtion CLB or the specified default value.
    */
   public final String getRedCLB( String defaultValue )
   {
      return _RedCLB == null ? defaultValue : _RedCLB;
   }
                  
   /**
    * Gets the Redemption PGrant field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemption PGrant or null.
    */
   public final String getRedPGrant()
   {
      return _RedPGrant;
   }
	
   /**
    * Gets the Redemption PGrant field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption PGrant or the specified default value.
    */
   public final String getRedPGrant( String defaultValue )
   {
      return _RedPGrant == null ? defaultValue : _RedPGrant;
   }
                  
   /**
    * Gets the UC Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the UC Amount or null.
    */
   public final String getUCAmount()
   {
      return _UCAmount;
   }
	
   /**
    * Gets the UC Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UC Amount or the specified default value.
    */
   public final String getUCAmount( String defaultValue )
   {
      return _UCAmount == null ? defaultValue : _UCAmount;
   }
                  
   /**
    * Gets the AC Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the AC Amount or null.
    */
   public final String getACAmount()
   {
      return _ACAmount;
   }
	
   /**
    * Gets the AC Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AC Amount or the specified default value.
    */
   public final String getACAmount( String defaultValue )
   {
      return _ACAmount == null ? defaultValue : _ACAmount;
   }
                  
   /**
    * Gets the Pre98 Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pre98 Contribution or null.
    */
   public final String getPre98Contrib()
   {
      return _Pre98Contrib;
   }
	
   /**
    * Gets the Pre98 Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pre98 Contribution or the specified default value.
    */
   public final String getPre98Contrib( String defaultValue )
   {
      return _Pre98Contrib == null ? defaultValue : _Pre98Contrib;
   }
                  
   /**
    * Gets the Pre98 Redemption Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pre98 Redemption Contribution or null.
    */
   public final String getPre98RedContrib()
   {
      return _Pre98RedContrib;
   }
	
   /**
    * Gets the Pre98 Redemption Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pre98 Redemption Contribution or the specified default value.
    */
   public final String getPre98RedContrib( String defaultValue )
   {
      return _Pre98RedContrib == null ? defaultValue : _Pre98RedContrib;
   }
                  
   /**
    * Gets the RESP Beneficiary ID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Beneficiary ID or null.
    */
   public final String getRESPBenefID()
   {
      return _RESPBenefID;
   }
	
   /**
    * Gets the RESP Beneficiary ID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Beneficiary ID or the specified default value.
    */
   public final String getRESPBenefID( String defaultValue )
   {
      return _RESPBenefID == null ? defaultValue : _RESPBenefID;
   }
                  
   /**
    * Gets the Entity Type field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity Type or null.
    */
   public final String getEntityType()
   {
      return _EntityType;
   }
	
   /**
    * Gets the Entity Type field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type or the specified default value.
    */
   public final String getEntityType( String defaultValue )
   {
      return _EntityType == null ? defaultValue : _EntityType;
   }
                  
   /**
    * Gets the Entity Type Sequnce field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity Type Sequnce or null.
    */
   public final Integer getEntityTypeSeq()
   {
      return _EntityTypeSeq;
   }
	
   /**
    * Gets the Entity Type Sequnce field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Sequnce or the specified default value.
    */
   public final int getEntityTypeSeq( int defaultValue )
   {
      return _EntityTypeSeq == null ? defaultValue : _EntityTypeSeq.intValue();
   }
                  
   /**
    * Gets the RESP Beneficiary ID To field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Beneficiary ID To or null.
    */
   public final String getRESPBenefIDTo()
   {
      return _RESPBenefIDTo;
   }
	
   /**
    * Gets the RESP Beneficiary ID To field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Beneficiary ID To or the specified default value.
    */
   public final String getRESPBenefIDTo( String defaultValue )
   {
      return _RESPBenefIDTo == null ? defaultValue : _RESPBenefIDTo;
   }
                  
   /**
    * Gets the Entity Type To field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity Type To or null.
    */
   public final String getEntityTypeTo()
   {
      return _EntityTypeTo;
   }
	
   /**
    * Gets the Entity Type To field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type To or the specified default value.
    */
   public final String getEntityTypeTo( String defaultValue )
   {
      return _EntityTypeTo == null ? defaultValue : _EntityTypeTo;
   }
                  
   /**
    * Gets the Entity Type Sequnce To field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Entity Type Sequnce To or null.
    */
   public final Integer getEntityTypeSeqTo()
   {
      return _EntityTypeSeqTo;
   }
	
   /**
    * Gets the Entity Type Sequnce To field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Type Sequnce To or the specified default value.
    */
   public final int getEntityTypeSeqTo( int defaultValue )
   {
      return _EntityTypeSeqTo == null ? defaultValue : _EntityTypeSeqTo.intValue();
   }
                  
   /**
    * Gets the RESP Allocation Percent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Allocation Percent or null.
    */
   public final String getRESPAllocPrcnt()
   {
      return _RESPAllocPrcnt;
   }
	
   /**
    * Gets the RESP Allocation Percent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Allocation Percent or the specified default value.
    */
   public final String getRESPAllocPrcnt( String defaultValue )
   {
      return _RESPAllocPrcnt == null ? defaultValue : _RESPAllocPrcnt;
   }
                  
   /**
    * Gets the Beneficiary Tainted field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Beneficiary Tainted or null.
    */
   public final Boolean getTainted()
   {
      return _Tainted;
   }
	
   /**
    * Gets the Beneficiary Tainted field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Tainted or the specified default value.
    */
   public final boolean getTainted( boolean defaultValue )
   {
      return _Tainted == null ? defaultValue : _Tainted.booleanValue();
   }
                  
   /**
    * Gets the End date of beneficiary being tained field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the End date of beneficiary being tained or null.
    */
   public final Date getTaintEndDate()
   {
      return _TaintEndDate;
   }
	
   /**
    * Gets the End date of beneficiary being tained field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the End date of beneficiary being tained or the specified default value.
    */
   public final Date getTaintEndDate( Date defaultValue )
   {
      return _TaintEndDate == null ? defaultValue : _TaintEndDate;
   }
                  
   /**
    * Gets the Flag if contributions should be report to HRDC field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Flag if contributions should be report to HRDC or null.
    */
   public final Boolean getGrantRequest()
   {
      return _GrantRequest;
   }
	
   /**
    * Gets the Flag if contributions should be report to HRDC field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag if contributions should be report to HRDC or the specified default value.
    */
   public final boolean getGrantRequest( boolean defaultValue )
   {
      return _GrantRequest == null ? defaultValue : _GrantRequest.booleanValue();
   }
                  
   /**
    * Gets the Beneficiary Date of Birth field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Beneficiary Date of Birth or null.
    */
   public final Date getBenefDofB()
   {
      return _BenefDofB;
   }
	
   /**
    * Gets the Beneficiary Date of Birth field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Date of Birth or the specified default value.
    */
   public final Date getBenefDofB( Date defaultValue )
   {
      return _BenefDofB == null ? defaultValue : _BenefDofB;
   }
                  
   /**
    * Gets the Tax Jurisdiction field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Tax Jurisdiction or null.
    */
   public final String getTaxJuris()
   {
      return _TaxJuris;
   }
	
   /**
    * Gets the Tax Jurisdiction field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction or the specified default value.
    */
   public final String getTaxJuris( String defaultValue )
   {
      return _TaxJuris == null ? defaultValue : _TaxJuris;
   }
                  
   /**
    * Gets the Relation field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Relation or null.
    */
   public final String getRelation()
   {
      return _Relation;
   }
	
   /**
    * Gets the Relation field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Relation or the specified default value.
    */
   public final String getRelation( String defaultValue )
   {
      return _Relation == null ? defaultValue : _Relation;
   }
                  
   /**
    * Gets the Beneficiary Effective Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Beneficiary Effective Date or null.
    */
   public final Date getBenefEffectiveDate()
   {
      return _BenefEffectiveDate;
   }
	
   /**
    * Gets the Beneficiary Effective Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Effective Date or the specified default value.
    */
   public final Date getBenefEffectiveDate( Date defaultValue )
   {
      return _BenefEffectiveDate == null ? defaultValue : _BenefEffectiveDate;
   }
                  
   /**
    * Gets the Transfer Percent field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Transfer Percent or null.
    */
   public final String getTransferPercent()
   {
      return _TransferPercent;
   }
	
   /**
    * Gets the Transfer Percent field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Percent or the specified default value.
    */
   public final String getTransferPercent( String defaultValue )
   {
      return _TransferPercent == null ? defaultValue : _TransferPercent;
   }
                  
   /**
    * Gets the Account Level Override field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Level Override or null.
    */
   public final Boolean getAcctLvlOverride()
   {
      return _AcctLvlOverride;
   }
	
   /**
    * Gets the Account Level Override field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Level Override or the specified default value.
    */
   public final boolean getAcctLvlOverride( boolean defaultValue )
   {
      return _AcctLvlOverride == null ? defaultValue : _AcctLvlOverride.booleanValue();
   }
                  
   /**
    * Gets the QESI UC Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the QESI UC Amount or null.
    */
   public final String getQESIUCAmount()
   {
      return _QESIUCAmount;
   }
	
   /**
    * Gets the QESI UC Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the QESI UC Amount or the specified default value.
    */
   public final String getQESIUCAmount( String defaultValue )
   {
      return _QESIUCAmount == null ? defaultValue : _QESIUCAmount;
   }
                  
   /**
    * Gets the QESI AC Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the QESI AC Amount or null.
    */
   public final String getQESIACAmount()
   {
      return _QESIACAmount;
   }
	
   /**
    * Gets the QESI AC Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the QESI AC Amount or the specified default value.
    */
   public final String getQESIACAmount( String defaultValue )
   {
      return _QESIACAmount == null ? defaultValue : _QESIACAmount;
   }
                  
   /**
    * Gets the QESI YTD Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the QESI YTD Contribution or null.
    */
   public final String getQESIYTDContribution()
   {
      return _QESIYTDContribution;
   }
	
   /**
    * Gets the QESI YTD Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the QESI YTD Contribution or the specified default value.
    */
   public final String getQESIYTDContribution( String defaultValue )
   {
      return _QESIYTDContribution == null ? defaultValue : _QESIYTDContribution;
   }
                  
   /**
    * Gets the QESI Basic Grant field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the QESI Basic Grant or null.
    */
   public final String getQESIBasicGrant()
   {
      return _QESIBasicGrant;
   }
	
   /**
    * Gets the QESI Basic Grant field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the QESI Basic Grant or the specified default value.
    */
   public final String getQESIBasicGrant( String defaultValue )
   {
      return _QESIBasicGrant == null ? defaultValue : _QESIBasicGrant;
   }
                  
   /**
    * Gets the QESI Increase Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the QESI Increase Amount or null.
    */
   public final String getQESIIncreaseAmt()
   {
      return _QESIIncreaseAmt;
   }
	
   /**
    * Gets the QESI Increase Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the QESI Increase Amount or the specified default value.
    */
   public final String getQESIIncreaseAmt( String defaultValue )
   {
      return _QESIIncreaseAmt == null ? defaultValue : _QESIIncreaseAmt;
   }
                  
   /**
    * Gets the Pre98 QESI Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pre98 QESI Contribution or null.
    */
   public final String getPre98QESIContrib()
   {
      return _Pre98QESIContrib;
   }
	
   /**
    * Gets the Pre98 QESI Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pre98 QESI Contribution or the specified default value.
    */
   public final String getPre98QESIContrib( String defaultValue )
   {
      return _Pre98QESIContrib == null ? defaultValue : _Pre98QESIContrib;
   }
                  
   /**
    * Gets the Pre2007 QESI Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Pre2007 QESI Contribution or null.
    */
   public final String getPre2007QESIContrib()
   {
      return _Pre2007QESIContrib;
   }
	
   /**
    * Gets the Pre2007 QESI Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Pre2007 QESI Contribution or the specified default value.
    */
   public final String getPre2007QESIContrib( String defaultValue )
   {
      return _Pre2007QESIContrib == null ? defaultValue : _Pre2007QESIContrib;
   }
                  
   /**
    * Gets the RESP External Transaction Detail UUID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP External Transaction Detail UUID or null.
    */
   public final String getRESPExtTrDetlUUID()
   {
      return _RESPExtTrDetlUUID;
   }
	
   /**
    * Gets the RESP External Transaction Detail UUID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP External Transaction Detail UUID or the specified default value.
    */
   public final String getRESPExtTrDetlUUID( String defaultValue )
   {
      return _RESPExtTrDetlUUID == null ? defaultValue : _RESPExtTrDetlUUID;
   }
                  
   /**
    * Gets the RESP External Transaction Detel Version field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP External Transaction Detel Version or null.
    */
   public final Integer getRESPExtTrDetlVer()
   {
      return _RESPExtTrDetlVer;
   }
	
   /**
    * Gets the RESP External Transaction Detel Version field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP External Transaction Detel Version or the specified default value.
    */
   public final int getRESPExtTrDetlVer( int defaultValue )
   {
      return _RESPExtTrDetlVer == null ? defaultValue : _RESPExtTrDetlVer.intValue();
   }
                  
   /**
    * Gets the RESP Contribution Detail UUID field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Contribution Detail UUID or null.
    */
   public final String getRESPContrDetlUUID()
   {
      return _RESPContrDetlUUID;
   }
	
   /**
    * Gets the RESP Contribution Detail UUID field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Contribution Detail UUID or the specified default value.
    */
   public final String getRESPContrDetlUUID( String defaultValue )
   {
      return _RESPContrDetlUUID == null ? defaultValue : _RESPContrDetlUUID;
   }
                  
   /**
    * Gets the RESP Contribution Detail Version field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Contribution Detail Version or null.
    */
   public final Integer getRESPContrDetlVer()
   {
      return _RESPContrDetlVer;
   }
	
   /**
    * Gets the RESP Contribution Detail Version field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Contribution Detail Version or the specified default value.
    */
   public final int getRESPContrDetlVer( int defaultValue )
   {
      return _RESPContrDetlVer == null ? defaultValue : _RESPContrDetlVer.intValue();
   }
                  
   /**
    * Gets the EligibleTransfer field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the EligibleTransfer or null.
    */
   public final Boolean getEligTransfer()
   {
      return _EligTransfer;
   }
	
   /**
    * Gets the EligibleTransfer field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the EligibleTransfer or the specified default value.
    */
   public final boolean getEligTransfer( boolean defaultValue )
   {
      return _EligTransfer == null ? defaultValue : _EligTransfer.booleanValue();
   }
                  
   /**
    * Gets the CESG Paid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CESG Paid or null.
    */
   public final String getCESGPaid()
   {
      return _CESGPaid;
   }
	
   /**
    * Gets the CESG Paid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CESG Paid or the specified default value.
    */
   public final String getCESGPaid( String defaultValue )
   {
      return _CESGPaid == null ? defaultValue : _CESGPaid;
   }
                  
   /**
    * Gets the QESI Paid field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the QESI Paid or null.
    */
   public final String getQESIPaid()
   {
      return _QESIPaid;
   }
	
   /**
    * Gets the QESI Paid field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the QESI Paid or the specified default value.
    */
   public final String getQESIPaid( String defaultValue )
   {
      return _QESIPaid == null ? defaultValue : _QESIPaid;
   }
                  
   /**
    * Gets the IsResidualCESG field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the IsResidualCESG or null.
    */
   public final Boolean getIsResidualCESG()
   {
      return _IsResidualCESG;
   }
	
   /**
    * Gets the IsResidualCESG field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IsResidualCESG or the specified default value.
    */
   public final boolean getIsResidualCESG( boolean defaultValue )
   {
      return _IsResidualCESG == null ? defaultValue : _IsResidualCESG.booleanValue();
   }
                  
   /**
    * Gets the SAGES Grant field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SAGES Grant or null.
    */
   public final String getSAGESGrant()
   {
      return _SAGESGrant;
   }
	
   /**
    * Gets the SAGES Grant field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES Grant or the specified default value.
    */
   public final String getSAGESGrant( String defaultValue )
   {
      return _SAGESGrant == null ? defaultValue : _SAGESGrant;
   }
                  
   /**
    * Gets the SAGES UC Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SAGES UC Amount or null.
    */
   public final String getSAGESUCAmount()
   {
      return _SAGESUCAmount;
   }
	
   /**
    * Gets the SAGES UC Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES UC Amount or the specified default value.
    */
   public final String getSAGESUCAmount( String defaultValue )
   {
      return _SAGESUCAmount == null ? defaultValue : _SAGESUCAmount;
   }
                  
   /**
    * Gets the SAGES AC Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the SAGES AC Amount or null.
    */
   public final String getSAGESACAmount()
   {
      return _SAGESACAmount;
   }
	
   /**
    * Gets the SAGES AC Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SAGES AC Amount or the specified default value.
    */
   public final String getSAGESACAmount( String defaultValue )
   {
      return _SAGESACAmount == null ? defaultValue : _SAGESACAmount;
   }
                  
   /**
    * Implements the abstract base method to decode
    * the host formatted response.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   protected void decodeFields( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      
      // single-record section
      _RecordLevel = responseBuffer.decodeString(responseBuffer.getNextField());
      _YTDContribution = responseBuffer.decodeString(responseBuffer.getNextField());
      _TDContribution = responseBuffer.decodeString(responseBuffer.getNextField());
      _GrantAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _AdditionalGrant = responseBuffer.decodeString(responseBuffer.getNextField());
      _CLBAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _PGrantAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _TDRedContrib = responseBuffer.decodeString(responseBuffer.getNextField());
      _TDRedEarnings = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedCESG = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedCLB = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedPGrant = responseBuffer.decodeString(responseBuffer.getNextField());
      _UCAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _ACAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _Pre98Contrib = responseBuffer.decodeString(responseBuffer.getNextField());
      _Pre98RedContrib = responseBuffer.decodeString(responseBuffer.getNextField());
      _RESPBenefID = responseBuffer.decodeString(responseBuffer.getNextField());
      _EntityType = responseBuffer.decodeString(responseBuffer.getNextField());
      _EntityTypeSeq = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _RESPBenefIDTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _EntityTypeTo = responseBuffer.decodeString(responseBuffer.getNextField());
      _EntityTypeSeqTo = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _RESPAllocPrcnt = responseBuffer.decodeString(responseBuffer.getNextField());
      _Tainted = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TaintEndDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _GrantRequest = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _BenefDofB = responseBuffer.decodeDate(responseBuffer.getNextField());
      _TaxJuris = responseBuffer.decodeString(responseBuffer.getNextField());
      _Relation = responseBuffer.decodeString(responseBuffer.getNextField());
      _BenefEffectiveDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _TransferPercent = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctLvlOverride = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _QESIUCAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _QESIACAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _QESIYTDContribution = responseBuffer.decodeString(responseBuffer.getNextField());
      _QESIBasicGrant = responseBuffer.decodeString(responseBuffer.getNextField());
      _QESIIncreaseAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _Pre98QESIContrib = responseBuffer.decodeString(responseBuffer.getNextField());
      _Pre2007QESIContrib = responseBuffer.decodeString(responseBuffer.getNextField());
      _RESPExtTrDetlUUID = responseBuffer.decodeString(responseBuffer.getNextField());
      _RESPExtTrDetlVer = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _RESPContrDetlUUID = responseBuffer.decodeString(responseBuffer.getNextField());
      _RESPContrDetlVer = responseBuffer.decodeInteger(responseBuffer.getNextField());
      _EligTransfer = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CESGPaid = responseBuffer.decodeString(responseBuffer.getNextField());
      _QESIPaid = responseBuffer.decodeString(responseBuffer.getNextField());
      _IsResidualCESG = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _SAGESGrant = responseBuffer.decodeString(responseBuffer.getNextField());
      _SAGESUCAmount = responseBuffer.decodeString(responseBuffer.getNextField());
      _SAGESACAmount = responseBuffer.decodeString(responseBuffer.getNextField());
                  

   }

}
      
