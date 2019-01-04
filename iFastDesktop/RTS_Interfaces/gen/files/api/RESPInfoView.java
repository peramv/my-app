
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * RESP Information Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/RESPInfo.doc">RESPInfo.doc</A>.
 * 
 * @author RTS Generated
 */
public class RESPInfoView extends IFastView implements Serializable
{

   /**
    * Termination Date for Contribution member variable.
    */
   private Date _TerminateDate = null;
   
   /**
    * Termination Date of the Plan member variable.
    */
   private Date _MaturityDate = null;
   
   /**
    * To-Date Contribution member variable.
    */
   private String _ToDateContr = null;
   
   /**
    * Plan Number member variable.
    */
   private String _PlanNum = null;
   
   /**
    * Grant Repayable member variable.
    */
   private String _GrantRepayable = null;
   
   /**
    * CESG Eligible member variable.
    */
   private Boolean _CESGEligible = null;
   
   /**
    * To-Date Earnings Redemption member variable.
    */
   private String _TDRedEarning = null;
   
   /**
    * GrandFathered member variable.
    */
   private Boolean _GFathered = null;
   
   /**
    * Curent Earnings member variable.
    */
   private String _CurrEarning = null;
   
   /**
    * RESP Status member variable.
    */
   private String _RESPStatus = null;
   
   /**
    * RESP Status Description member variable.
    */
   private String _RESPStatDesc = null;
   
   /**
    * Redemption Life Time Contribution member variable.
    */
   private String _RedLifeContr = null;
   
   /**
    * Redemption Un-Assisted Amount member variable.
    */
   private String _RedUCAmt = null;
   
   /**
    * Redemption Assisted Amount member variable.
    */
   private String _RedACAmt = null;
   
   /**
    * Redemption Net Grant member variable.
    */
   private String _RedNetGrant = null;
   
   /**
    * Account Life Time Contribution member variable.
    */
   private String _AcctLifeContr = null;
   
   /**
    * Account Un-Assisted Amount member variable.
    */
   private String _AcctUCAmt = null;
   
   /**
    * Account  Assisted Amount member variable.
    */
   private String _AcctACAmt = null;
   
   /**
    * Account Net Grant member variable.
    */
   private String _AcctNetGrant = null;
   
   /**
    * Account Educational Adjustment Payment member variable.
    */
   private String _AcctEAP = null;
   
   /**
    * RESP Beneficiary Specify Flag member variable.
    */
   private String _RESPBenefSpecify = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Beneficiary Name member array.
    */
   private String[] _BeneName = null;
   
   /**
    * Year To Date Contribution member array.
    */
   private String[] _YTDContr = null;
   
   /**
    * Life Contribution member array.
    */
   private String[] _LifeContr = null;
   
   /**
    * Un-Assisted member array.
    */
   private String[] _UnAssisted = null;
   
   /**
    * Assisted member array.
    */
   private String[] _Assisted = null;
   
   /**
    * Net Government Grant member array.
    */
   private String[] _NetGrant = null;
   
   /**
    * Educational Adjustment Payment member array.
    */
   private String[] _EAPayment = null;
   

   /**
    * Constructs the RESPInfoView object.
    * 
    */
   public RESPInfoView()
   {
      super ( new RESPInfoRequest() );
   }

   /**
    * Constructs the RESPInfoView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public RESPInfoView( String hostEncoding )
   {
      super ( new RESPInfoRequest( hostEncoding ) );
   }

   /**
    * Gets the RESPInfoRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The RESPInfoRequest object.
    */
   public final RESPInfoRequest getRequest()
   {
      return (RESPInfoRequest)getIFastRequest();
   }
        
   /**
    * Gets the Termination Date for Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Termination Date for Contribution or null.
    */
   public final Date getTerminateDate()
   {
      return _TerminateDate;
   }
	
   /**
    * Gets the Termination Date for Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Termination Date for Contribution or the specified default value.
    */
   public final Date getTerminateDate( Date defaultValue )
   {
      return _TerminateDate == null ? defaultValue : _TerminateDate;
   }
                  
   /**
    * Gets the Termination Date of the Plan field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Termination Date of the Plan or null.
    */
   public final Date getMaturityDate()
   {
      return _MaturityDate;
   }
	
   /**
    * Gets the Termination Date of the Plan field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Termination Date of the Plan or the specified default value.
    */
   public final Date getMaturityDate( Date defaultValue )
   {
      return _MaturityDate == null ? defaultValue : _MaturityDate;
   }
                  
   /**
    * Gets the To-Date Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the To-Date Contribution or null.
    */
   public final String getToDateContr()
   {
      return _ToDateContr;
   }
	
   /**
    * Gets the To-Date Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To-Date Contribution or the specified default value.
    */
   public final String getToDateContr( String defaultValue )
   {
      return _ToDateContr == null ? defaultValue : _ToDateContr;
   }
                  
   /**
    * Gets the Plan Number field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Plan Number or null.
    */
   public final String getPlanNum()
   {
      return _PlanNum;
   }
	
   /**
    * Gets the Plan Number field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Plan Number or the specified default value.
    */
   public final String getPlanNum( String defaultValue )
   {
      return _PlanNum == null ? defaultValue : _PlanNum;
   }
                  
   /**
    * Gets the Grant Repayable field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Grant Repayable or null.
    */
   public final String getGrantRepayable()
   {
      return _GrantRepayable;
   }
	
   /**
    * Gets the Grant Repayable field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Grant Repayable or the specified default value.
    */
   public final String getGrantRepayable( String defaultValue )
   {
      return _GrantRepayable == null ? defaultValue : _GrantRepayable;
   }
                  
   /**
    * Gets the CESG Eligible field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the CESG Eligible or null.
    */
   public final Boolean getCESGEligible()
   {
      return _CESGEligible;
   }
	
   /**
    * Gets the CESG Eligible field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CESG Eligible or the specified default value.
    */
   public final boolean getCESGEligible( boolean defaultValue )
   {
      return _CESGEligible == null ? defaultValue : _CESGEligible.booleanValue();
   }
                  
   /**
    * Gets the To-Date Earnings Redemption field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the To-Date Earnings Redemption or null.
    */
   public final String getTDRedEarning()
   {
      return _TDRedEarning;
   }
	
   /**
    * Gets the To-Date Earnings Redemption field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the To-Date Earnings Redemption or the specified default value.
    */
   public final String getTDRedEarning( String defaultValue )
   {
      return _TDRedEarning == null ? defaultValue : _TDRedEarning;
   }
                  
   /**
    * Gets the GrandFathered field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the GrandFathered or null.
    */
   public final Boolean getGFathered()
   {
      return _GFathered;
   }
	
   /**
    * Gets the GrandFathered field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the GrandFathered or the specified default value.
    */
   public final boolean getGFathered( boolean defaultValue )
   {
      return _GFathered == null ? defaultValue : _GFathered.booleanValue();
   }
                  
   /**
    * Gets the Curent Earnings field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Curent Earnings or null.
    */
   public final String getCurrEarning()
   {
      return _CurrEarning;
   }
	
   /**
    * Gets the Curent Earnings field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Curent Earnings or the specified default value.
    */
   public final String getCurrEarning( String defaultValue )
   {
      return _CurrEarning == null ? defaultValue : _CurrEarning;
   }
                  
   /**
    * Gets the RESP Status field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Status or null.
    */
   public final String getRESPStatus()
   {
      return _RESPStatus;
   }
	
   /**
    * Gets the RESP Status field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Status or the specified default value.
    */
   public final String getRESPStatus( String defaultValue )
   {
      return _RESPStatus == null ? defaultValue : _RESPStatus;
   }
                  
   /**
    * Gets the RESP Status Description field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Status Description or null.
    */
   public final String getRESPStatDesc()
   {
      return _RESPStatDesc;
   }
	
   /**
    * Gets the RESP Status Description field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Status Description or the specified default value.
    */
   public final String getRESPStatDesc( String defaultValue )
   {
      return _RESPStatDesc == null ? defaultValue : _RESPStatDesc;
   }
                  
   /**
    * Gets the Redemption Life Time Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemption Life Time Contribution or null.
    */
   public final String getRedLifeContr()
   {
      return _RedLifeContr;
   }
	
   /**
    * Gets the Redemption Life Time Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Life Time Contribution or the specified default value.
    */
   public final String getRedLifeContr( String defaultValue )
   {
      return _RedLifeContr == null ? defaultValue : _RedLifeContr;
   }
                  
   /**
    * Gets the Redemption Un-Assisted Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemption Un-Assisted Amount or null.
    */
   public final String getRedUCAmt()
   {
      return _RedUCAmt;
   }
	
   /**
    * Gets the Redemption Un-Assisted Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Un-Assisted Amount or the specified default value.
    */
   public final String getRedUCAmt( String defaultValue )
   {
      return _RedUCAmt == null ? defaultValue : _RedUCAmt;
   }
                  
   /**
    * Gets the Redemption Assisted Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemption Assisted Amount or null.
    */
   public final String getRedACAmt()
   {
      return _RedACAmt;
   }
	
   /**
    * Gets the Redemption Assisted Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Assisted Amount or the specified default value.
    */
   public final String getRedACAmt( String defaultValue )
   {
      return _RedACAmt == null ? defaultValue : _RedACAmt;
   }
                  
   /**
    * Gets the Redemption Net Grant field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Redemption Net Grant or null.
    */
   public final String getRedNetGrant()
   {
      return _RedNetGrant;
   }
	
   /**
    * Gets the Redemption Net Grant field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Net Grant or the specified default value.
    */
   public final String getRedNetGrant( String defaultValue )
   {
      return _RedNetGrant == null ? defaultValue : _RedNetGrant;
   }
                  
   /**
    * Gets the Account Life Time Contribution field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Life Time Contribution or null.
    */
   public final String getAcctLifeContr()
   {
      return _AcctLifeContr;
   }
	
   /**
    * Gets the Account Life Time Contribution field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Life Time Contribution or the specified default value.
    */
   public final String getAcctLifeContr( String defaultValue )
   {
      return _AcctLifeContr == null ? defaultValue : _AcctLifeContr;
   }
                  
   /**
    * Gets the Account Un-Assisted Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Un-Assisted Amount or null.
    */
   public final String getAcctUCAmt()
   {
      return _AcctUCAmt;
   }
	
   /**
    * Gets the Account Un-Assisted Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Un-Assisted Amount or the specified default value.
    */
   public final String getAcctUCAmt( String defaultValue )
   {
      return _AcctUCAmt == null ? defaultValue : _AcctUCAmt;
   }
                  
   /**
    * Gets the Account  Assisted Amount field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account  Assisted Amount or null.
    */
   public final String getAcctACAmt()
   {
      return _AcctACAmt;
   }
	
   /**
    * Gets the Account  Assisted Amount field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account  Assisted Amount or the specified default value.
    */
   public final String getAcctACAmt( String defaultValue )
   {
      return _AcctACAmt == null ? defaultValue : _AcctACAmt;
   }
                  
   /**
    * Gets the Account Net Grant field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Net Grant or null.
    */
   public final String getAcctNetGrant()
   {
      return _AcctNetGrant;
   }
	
   /**
    * Gets the Account Net Grant field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Net Grant or the specified default value.
    */
   public final String getAcctNetGrant( String defaultValue )
   {
      return _AcctNetGrant == null ? defaultValue : _AcctNetGrant;
   }
                  
   /**
    * Gets the Account Educational Adjustment Payment field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Account Educational Adjustment Payment or null.
    */
   public final String getAcctEAP()
   {
      return _AcctEAP;
   }
	
   /**
    * Gets the Account Educational Adjustment Payment field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Educational Adjustment Payment or the specified default value.
    */
   public final String getAcctEAP( String defaultValue )
   {
      return _AcctEAP == null ? defaultValue : _AcctEAP;
   }
                  
   /**
    * Gets the RESP Beneficiary Specify Flag field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the RESP Beneficiary Specify Flag or null.
    */
   public final String getRESPBenefSpecify()
   {
      return _RESPBenefSpecify;
   }
	
   /**
    * Gets the RESP Beneficiary Specify Flag field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RESP Beneficiary Specify Flag or the specified default value.
    */
   public final String getRESPBenefSpecify( String defaultValue )
   {
      return _RESPBenefSpecify == null ? defaultValue : _RESPBenefSpecify;
   }
                  
   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public int getRecordCount()
   {
      return _RepeatCount;
   }

   /**
    * Gets the Record Count for the repeatable response.
    * 
    * @return The number of records in the repeating fields.
    */
   public final int getRepeatCount()
   {
      return _RepeatCount;
   }

   /**
    * Decodes the repeat count value from the host 
    * respones.
    * 
    * @param response Host formatted response object.
    * @exception ParseException
    */
   private final void decodeRepeatCount( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, UnsupportedEncodingException
   {
      int receivedRecordCount = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _RepeatCount += receivedRecordCount;
   }

   /**
    * Gets the Beneficiary Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Beneficiary Name or null.
    */
   public final String getBeneName( int index )
   {
      return _BeneName[index];
   }
    
   /**
    * Gets the Beneficiary Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Beneficiary Name or the specified default value.
    */
   public final String getBeneName( int index, String defaultValue )
   {
      return _BeneName[index] == null ? defaultValue : _BeneName[index];
   }
    
   /**
    * Gets the array of Beneficiary Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Beneficiary Name values.
    */
   public final String[] getBeneNameArray()
   {
      return _BeneName;
   }
    
   /**
    * Gets the Year To Date Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Year To Date Contribution or null.
    */
   public final String getYTDContr( int index )
   {
      return _YTDContr[index];
   }
    
   /**
    * Gets the Year To Date Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Year To Date Contribution or the specified default value.
    */
   public final String getYTDContr( int index, String defaultValue )
   {
      return _YTDContr[index] == null ? defaultValue : _YTDContr[index];
   }
    
   /**
    * Gets the array of Year To Date Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Year To Date Contribution values.
    */
   public final String[] getYTDContrArray()
   {
      return _YTDContr;
   }
    
   /**
    * Gets the Life Contribution field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Life Contribution or null.
    */
   public final String getLifeContr( int index )
   {
      return _LifeContr[index];
   }
    
   /**
    * Gets the Life Contribution field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Life Contribution or the specified default value.
    */
   public final String getLifeContr( int index, String defaultValue )
   {
      return _LifeContr[index] == null ? defaultValue : _LifeContr[index];
   }
    
   /**
    * Gets the array of Life Contribution fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Life Contribution values.
    */
   public final String[] getLifeContrArray()
   {
      return _LifeContr;
   }
    
   /**
    * Gets the Un-Assisted field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Un-Assisted or null.
    */
   public final String getUnAssisted( int index )
   {
      return _UnAssisted[index];
   }
    
   /**
    * Gets the Un-Assisted field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Un-Assisted or the specified default value.
    */
   public final String getUnAssisted( int index, String defaultValue )
   {
      return _UnAssisted[index] == null ? defaultValue : _UnAssisted[index];
   }
    
   /**
    * Gets the array of Un-Assisted fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Un-Assisted values.
    */
   public final String[] getUnAssistedArray()
   {
      return _UnAssisted;
   }
    
   /**
    * Gets the Assisted field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Assisted or null.
    */
   public final String getAssisted( int index )
   {
      return _Assisted[index];
   }
    
   /**
    * Gets the Assisted field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Assisted or the specified default value.
    */
   public final String getAssisted( int index, String defaultValue )
   {
      return _Assisted[index] == null ? defaultValue : _Assisted[index];
   }
    
   /**
    * Gets the array of Assisted fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Assisted values.
    */
   public final String[] getAssistedArray()
   {
      return _Assisted;
   }
    
   /**
    * Gets the Net Government Grant field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Net Government Grant or null.
    */
   public final String getNetGrant( int index )
   {
      return _NetGrant[index];
   }
    
   /**
    * Gets the Net Government Grant field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Net Government Grant or the specified default value.
    */
   public final String getNetGrant( int index, String defaultValue )
   {
      return _NetGrant[index] == null ? defaultValue : _NetGrant[index];
   }
    
   /**
    * Gets the array of Net Government Grant fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Net Government Grant values.
    */
   public final String[] getNetGrantArray()
   {
      return _NetGrant;
   }
    
   /**
    * Gets the Educational Adjustment Payment field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Educational Adjustment Payment or null.
    */
   public final String getEAPayment( int index )
   {
      return _EAPayment[index];
   }
    
   /**
    * Gets the Educational Adjustment Payment field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Educational Adjustment Payment or the specified default value.
    */
   public final String getEAPayment( int index, String defaultValue )
   {
      return _EAPayment[index] == null ? defaultValue : _EAPayment[index];
   }
    
   /**
    * Gets the array of Educational Adjustment Payment fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Educational Adjustment Payment values.
    */
   public final String[] getEAPaymentArray()
   {
      return _EAPayment;
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
      decodeMoreAvailableField( responseBuffer );
      decodeNextKeyField( responseBuffer );
      _TerminateDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _MaturityDate = responseBuffer.decodeDate(responseBuffer.getNextField());
      _ToDateContr = responseBuffer.decodeString(responseBuffer.getNextField());
      _PlanNum = responseBuffer.decodeString(responseBuffer.getNextField());
      _GrantRepayable = responseBuffer.decodeString(responseBuffer.getNextField());
      _CESGEligible = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _TDRedEarning = responseBuffer.decodeString(responseBuffer.getNextField());
      _GFathered = responseBuffer.decodeBoolean(responseBuffer.getNextField());
      _CurrEarning = responseBuffer.decodeString(responseBuffer.getNextField());
      _RESPStatus = responseBuffer.decodeString(responseBuffer.getNextField());
      _RESPStatDesc = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedLifeContr = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedUCAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedACAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _RedNetGrant = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctLifeContr = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctUCAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctACAmt = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctNetGrant = responseBuffer.decodeString(responseBuffer.getNextField());
      _AcctEAP = responseBuffer.decodeString(responseBuffer.getNextField());
      _RESPBenefSpecify = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _BeneName = resizeArray( _BeneName, _RepeatCount );
      _YTDContr = resizeArray( _YTDContr, _RepeatCount );
      _LifeContr = resizeArray( _LifeContr, _RepeatCount );
      _UnAssisted = resizeArray( _UnAssisted, _RepeatCount );
      _Assisted = resizeArray( _Assisted, _RepeatCount );
      _NetGrant = resizeArray( _NetGrant, _RepeatCount );
      _EAPayment = resizeArray( _EAPayment, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _BeneName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _YTDContr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LifeContr[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnAssisted[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Assisted[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _NetGrant[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EAPayment[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
