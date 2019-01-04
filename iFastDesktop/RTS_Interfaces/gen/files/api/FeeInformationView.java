
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fee Information Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FeeInformation.doc">FeeInformation.doc</A>.
 * 
 * @author RTS Generated
 */
public class FeeInformationView extends IFastView implements Serializable
{

   /**
    * Client Level Transfer Fee member variable.
    */
   private String _ClientLvlTfr = null;
   
   /**
    * Client Level Exchange Fee member variable.
    */
   private String _ClientLvlExch = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Acquisition Fee Flag member array.
    */
   private Boolean[] _AcqActive = null;
   
   /**
    * Acquisition Rate member array.
    */
   private String[] _AcqRate = null;
   
   /**
    * Acquisition Fee Frequency member array.
    */
   private String[] _AcqFreq = null;
   
   /**
    * Acquisition Fee Frequency Description member array.
    */
   private String[] _AcqFreqDesc = null;
   
   /**
    * Acquisition Fee Type member array.
    */
   private String[] _AcqFeeType = null;
   
   /**
    * Acquisition Fee Type Description member array.
    */
   private String[] _AcqFeeTypeDesc = null;
   
   /**
    * Acquisition How Paid member array.
    */
   private String[] _AcqHowPaid = null;
   
   /**
    * Acquistion How Paid Description member array.
    */
   private String[] _AcqHowPaidDesc = null;
   
   /**
    * Acquisition Based On member array.
    */
   private String[] _AcqBasedOn = null;
   
   /**
    * Acquistion Based On Description member array.
    */
   private String[] _AcqBasedOnDesc = null;
   
   /**
    * With-hold Fee Flag member array.
    */
   private Boolean[] _WHoldActive = null;
   
   /**
    * With-hold Rate member array.
    */
   private String[] _WHoldRate = null;
   
   /**
    * With-hold Fee Frequency member array.
    */
   private String[] _WHoldFreq = null;
   
   /**
    * With-hold Fee Frequency Description member array.
    */
   private String[] _WHoldFreqDesc = null;
   
   /**
    * With-Hold Fee Type member array.
    */
   private String[] _WHoldFeeType = null;
   
   /**
    * With-Hold Fee Type Description member array.
    */
   private String[] _WHoldFeeTypeDesc = null;
   
   /**
    * With-hold How Paid member array.
    */
   private String[] _WHoldHowPaid = null;
   
   /**
    * With-hold How Paid Description member array.
    */
   private String[] _WHoldHowPaidDesc = null;
   
   /**
    * With-hold Based On member array.
    */
   private String[] _WHoldBasedIOn = null;
   
   /**
    * With-hold Based On Description member array.
    */
   private String[] _WHoldBasedOnDesc = null;
   
   /**
    * Back-end Load Fee Flag member array.
    */
   private Boolean[] _BELActive = null;
   
   /**
    * Back-end Load Rate member array.
    */
   private String[] _BELRate = null;
   
   /**
    * Back-end Load Fee member array.
    */
   private String[] _BELFreq = null;
   
   /**
    * Back-end Load Fee Frequency Description member array.
    */
   private String[] _BELFreqDesc = null;
   
   /**
    * Back-end Load Fee Type member array.
    */
   private String[] _BELFeeType = null;
   
   /**
    * Back-end Load Fee Type Description member array.
    */
   private String[] _BELFeeTypeDesc = null;
   
   /**
    * Back-end Load How Paid member array.
    */
   private String[] _BELHowPaid = null;
   
   /**
    * Back-end Load How Paid Description member array.
    */
   private String[] _BELHowPaidDesc = null;
   
   /**
    * Back-end Load Based On member array.
    */
   private String[] _BELBasedOn = null;
   
   /**
    * Back-end Load Based On Description member array.
    */
   private String[] _BELBasedOnDesc = null;
   
   /**
    * Transfer Fee Flag member array.
    */
   private Boolean[] _TfrActive = null;
   
   /**
    * Transfer Rate member array.
    */
   private String[] _TfrRate = null;
   
   /**
    * Transfer Fee Frequency member array.
    */
   private String[] _TfrFreq = null;
   
   /**
    * Transfer Fee Frequency Description member array.
    */
   private String[] _TfrFreqDesc = null;
   
   /**
    * Transfer Fee Type member array.
    */
   private String[] _TfrFeeType = null;
   
   /**
    * Transfer Fee Type Description member array.
    */
   private String[] _TfrFeeTypeDesc = null;
   
   /**
    * Transfer How Paid member array.
    */
   private String[] _TfrHowPaid = null;
   
   /**
    * Transfer How Paid Description member array.
    */
   private String[] _TfrHowPaidDesc = null;
   
   /**
    * Transfer Based On member array.
    */
   private String[] _TfrBasedOn = null;
   
   /**
    * Transfer Based On Description member array.
    */
   private String[] _TfrBasedOnDesc = null;
   
   /**
    * RRSP Trustee Fee Flag member array.
    */
   private Boolean[] _RRSPActive = null;
   
   /**
    * RRSP Trustee Rate member array.
    */
   private String[] _RRSPRate = null;
   
   /**
    * RRSP Trustee Fee Frequency member array.
    */
   private String[] _RRSPFreq = null;
   
   /**
    * RRSP Trustee Fee Frequency Description member array.
    */
   private String[] _RRSPFreqDesc = null;
   
   /**
    * RRSP Trustee Fee Type member array.
    */
   private String[] _RRSPFeeType = null;
   
   /**
    * RRSP Trustee Fee Type Description member array.
    */
   private String[] _RRSPFeeTypeDesc = null;
   
   /**
    * RRSP Trustee How Paid member array.
    */
   private String[] _RRSPHowPaid = null;
   
   /**
    * RRSP Trustee How Paid Description member array.
    */
   private String[] _RRSPHowPaidDesc = null;
   
   /**
    * RRSP Trustee Based On member array.
    */
   private String[] _RRSPBasedOn = null;
   
   /**
    * RRSP Trustee Based On Description member array.
    */
   private String[] _RRSPBasedOnDesc = null;
   
   /**
    * RRIF Admin Fee Flag member array.
    */
   private Boolean[] _RRIFActive = null;
   
   /**
    * RRIF Admin Rate member array.
    */
   private String[] _RRIFRate = null;
   
   /**
    * RRIF Admin Fee Frequency member array.
    */
   private String[] _RRIFFreq = null;
   
   /**
    * RRIF Admin Fee Frequency Description member array.
    */
   private String[] _RRIFFreqDesc = null;
   
   /**
    * RRIF Admin Fee Type member array.
    */
   private String[] _RRIFFeeType = null;
   
   /**
    * RRIF Admin Fee Type Desc member array.
    */
   private String[] _RRIFFeeTypeDesc = null;
   
   /**
    * RRIF Admin How Paid member array.
    */
   private String[] _RRIFHowPaid = null;
   
   /**
    * RRIF Admin How Paid Desc member array.
    */
   private String[] _RRIFHowPaidDesc = null;
   
   /**
    * RRIF Admin Based On member array.
    */
   private String[] _RRIFBasedOn = null;
   
   /**
    * RRIF Admin Based On Description member array.
    */
   private String[] _RRIFBasedOnDesc = null;
   
   /**
    * Incentive Fee Flag member array.
    */
   private Boolean[] _IncvActive = null;
   
   /**
    * Incentive Rate member array.
    */
   private String[] _IncvRate = null;
   
   /**
    * Incentive Fee Frequency member array.
    */
   private String[] _IncvFreq = null;
   
   /**
    * Incentive Fee Frequency Description member array.
    */
   private String[] _IncvFreqDesc = null;
   
   /**
    * Incentive Fee Type member array.
    */
   private String[] _IncvFeeType = null;
   
   /**
    * Incentive Fee Type Description member array.
    */
   private String[] _IncvFeeTypeDesc = null;
   
   /**
    * Incentive How Paid member array.
    */
   private String[] _IncvHowPaid = null;
   
   /**
    * Incentive How Paid Description member array.
    */
   private String[] _IncvHowPaidDesc = null;
   
   /**
    * Incentive Based On member array.
    */
   private String[] _IncvBasedOn = null;
   
   /**
    * Incentive Based On Description member array.
    */
   private String[] _IncvBasedOnDesc = null;
   
   /**
    * Trailer Fee Flag member array.
    */
   private Boolean[] _TrlActive = null;
   
   /**
    * Trailer Rate member array.
    */
   private String[] _TrlRate = null;
   
   /**
    * Trailer Fee Frequency member array.
    */
   private String[] _TrlFreq = null;
   
   /**
    * Trailer Fee Frequency Description member array.
    */
   private String[] _TrlFreqDesc = null;
   
   /**
    * Trailer Fee Type member array.
    */
   private String[] _TrlFeeType = null;
   
   /**
    * Trailer Fee Type Description member array.
    */
   private String[] _TrlFeeTypeDesc = null;
   
   /**
    * Trailer How Paid member array.
    */
   private String[] _TrlHowPaid = null;
   
   /**
    * Trailer How Paid Description member array.
    */
   private String[] _TrlHowPaidDesc = null;
   
   /**
    * Trailer Based On member array.
    */
   private String[] _TrlBasedOn = null;
   
   /**
    * Trailer Based On Description member array.
    */
   private String[] _TrlBasedOnDesc = null;
   
   /**
    * R.O.A. Fee Flag member array.
    */
   private Boolean[] _ROAActive = null;
   
   /**
    * R.O.A. Rate member array.
    */
   private String[] _ROARate = null;
   
   /**
    * R.O.A. Fee Frequency member array.
    */
   private String[] _ROAFreq = null;
   
   /**
    * R.O.A. Fee Frequency Description member array.
    */
   private String[] _ROAFreqDesc = null;
   
   /**
    * R.O.A. Fee Type member array.
    */
   private String[] _ROAFeeType = null;
   
   /**
    * R.O.A. Fee Type Desc member array.
    */
   private String[] _ROAFeeTypeDesc = null;
   
   /**
    * R.O.A. How Paid member array.
    */
   private String[] _ROAHowPaid = null;
   
   /**
    * R.O.A. How Paid Desc member array.
    */
   private String[] _ROAHowPaidDesc = null;
   
   /**
    * R.O.A. Based On member array.
    */
   private String[] _ROABasedOn = null;
   
   /**
    * R.O.A. Based On Description member array.
    */
   private String[] _ROABasedOnDesc = null;
   
   /**
    * Extra Commission Fee Flag member array.
    */
   private Boolean[] _XtraActive = null;
   
   /**
    * Extra Commission Rate member array.
    */
   private String[] _XtraRate = null;
   
   /**
    * Extra Commission Fee Frequency member array.
    */
   private String[] _XtraFreq = null;
   
   /**
    * Extra Commission Fee Frequency Description member array.
    */
   private String[] _XtraFreqDesc = null;
   
   /**
    * Extra Commission Fee Type member array.
    */
   private String[] _XtraFeeType = null;
   
   /**
    * Extra Commission Fee Type Description member array.
    */
   private String[] _XtraFeeTypeDesc = null;
   
   /**
    * Extra Commission How Paid member array.
    */
   private String[] _XtraHowPaid = null;
   
   /**
    * Extra Commission How Paid Description member array.
    */
   private String[] _XtraHowPaidDesc = null;
   
   /**
    * Extra Commission Based On member array.
    */
   private String[] _XtraBasedOn = null;
   
   /**
    * Extra Commission Based On Description member array.
    */
   private String[] _XtraBasedOnDesc = null;
   
   /**
    * Dist & Maintenance Fee Flag member array.
    */
   private Boolean[] _DistActive = null;
   
   /**
    * Dist & Maintenance Rate member array.
    */
   private String[] _DistRate = null;
   
   /**
    * Dist & Maintenance Fee Frequency member array.
    */
   private String[] _DistFreq = null;
   
   /**
    * Dist & Maintenance Fee Frequency Description member array.
    */
   private String[] _DistFreqDesc = null;
   
   /**
    * Dist & Maintenance Fee Type member array.
    */
   private String[] _DistFeeType = null;
   
   /**
    * Dist & Maintenance Fee Type Description member array.
    */
   private String[] _DistFeeTypeDesc = null;
   
   /**
    * Dist & Maintenance How Paid member array.
    */
   private String[] _DistHowPaid = null;
   
   /**
    * Dist & Maintenance How Paid Description member array.
    */
   private String[] _DistHowPaidDesc = null;
   
   /**
    * Dist & Maintenance Based On Description member array.
    */
   private String[] _DistBasedOn = null;
   
   /**
    * Dist & Maintenance Based On Description member array.
    */
   private String[] _DistBasedOnDesc = null;
   
   /**
    * Max Fee Flag member array.
    */
   private Boolean[] _MaxActive = null;
   
   /**
    * Max Fee Rate member array.
    */
   private String[] _MaxRate = null;
   
   /**
    * Max Fee Frequency member array.
    */
   private String[] _MaxFreq = null;
   
   /**
    * Max Fee Frequency Description member array.
    */
   private String[] _MaxFreqDesc = null;
   
   /**
    * Max Fee Type member array.
    */
   private String[] _MaxFeeType = null;
   
   /**
    * Max Fee Type Description member array.
    */
   private String[] _MaxFeeTypeDesc = null;
   
   /**
    * Max Fee How Paid member array.
    */
   private String[] _MaxHowPaid = null;
   
   /**
    * Max Fee How Paid Description member array.
    */
   private String[] _MaxHowPaidDesc = null;
   
   /**
    * Max Fee Based On member array.
    */
   private String[] _MaxBasedOn = null;
   
   /**
    * Max Fee Based On Description member array.
    */
   private String[] _MaxBasedOnDesc = null;
   
   /**
    * FIFO Management fees for BackEnd loading Funds member array.
    */
   private Boolean[] _FIFOMFFee = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Redemption Fee Default Rate member array.
    */
   private String[] _RedemFee = null;
   
   /**
    * Redemption Fee Type member array.
    */
   private String[] _RedemFeeType = null;
   
   /**
    * Redemption Fee Currency member array.
    */
   private String[] _RedemFeeCurrency = null;
   
   /**
    * Fee on In side of Exchange Default member array.
    */
   private String[] _ExchInFeeDefault = null;
   
   /**
    * Fee on In side of Exchange Default Fee Type member array.
    */
   private String[] _ExchInFeeDefType = null;
   
   /**
    * Fee on In side of Exchange Maximum member array.
    */
   private String[] _ExchInFeeMax = null;
   
   /**
    * Fee on In side of Exchange Minimum member array.
    */
   private String[] _ExchInFeeMin = null;
   

   /**
    * Constructs the FeeInformationView object.
    * 
    */
   public FeeInformationView()
   {
      super ( new FeeInformationRequest() );
   }

   /**
    * Constructs the FeeInformationView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FeeInformationView( String hostEncoding )
   {
      super ( new FeeInformationRequest( hostEncoding ) );
   }

   /**
    * Gets the FeeInformationRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FeeInformationRequest object.
    */
   public final FeeInformationRequest getRequest()
   {
      return (FeeInformationRequest)getIFastRequest();
   }
        
   /**
    * Gets the Client Level Transfer Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Client Level Transfer Fee or null.
    */
   public final String getClientLvlTfr()
   {
      return _ClientLvlTfr;
   }
	
   /**
    * Gets the Client Level Transfer Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Client Level Transfer Fee or the specified default value.
    */
   public final String getClientLvlTfr( String defaultValue )
   {
      return _ClientLvlTfr == null ? defaultValue : _ClientLvlTfr;
   }
                  
   /**
    * Gets the Client Level Exchange Fee field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Client Level Exchange Fee or null.
    */
   public final String getClientLvlExch()
   {
      return _ClientLvlExch;
   }
	
   /**
    * Gets the Client Level Exchange Fee field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Client Level Exchange Fee or the specified default value.
    */
   public final String getClientLvlExch( String defaultValue )
   {
      return _ClientLvlExch == null ? defaultValue : _ClientLvlExch;
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
    * Gets the Acquisition Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition Fee Flag or null.
    */
   public final Boolean getAcqActive( int index )
   {
      return _AcqActive[index];
   }
    
   /**
    * Gets the Acquisition Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Fee Flag or the specified default value.
    */
   public final boolean getAcqActive( int index, boolean defaultValue )
   {
      return _AcqActive[index] == null ? defaultValue : _AcqActive[index].booleanValue();
   }
    
   /**
    * Gets the array of Acquisition Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition Fee Flag values.
    */
   public final Boolean[] getAcqActiveArray()
   {
      return _AcqActive;
   }
    
   /**
    * Gets the Acquisition Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition Rate or null.
    */
   public final String getAcqRate( int index )
   {
      return _AcqRate[index];
   }
    
   /**
    * Gets the Acquisition Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Rate or the specified default value.
    */
   public final String getAcqRate( int index, String defaultValue )
   {
      return _AcqRate[index] == null ? defaultValue : _AcqRate[index];
   }
    
   /**
    * Gets the array of Acquisition Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition Rate values.
    */
   public final String[] getAcqRateArray()
   {
      return _AcqRate;
   }
    
   /**
    * Gets the Acquisition Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition Fee Frequency or null.
    */
   public final String getAcqFreq( int index )
   {
      return _AcqFreq[index];
   }
    
   /**
    * Gets the Acquisition Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Fee Frequency or the specified default value.
    */
   public final String getAcqFreq( int index, String defaultValue )
   {
      return _AcqFreq[index] == null ? defaultValue : _AcqFreq[index];
   }
    
   /**
    * Gets the array of Acquisition Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition Fee Frequency values.
    */
   public final String[] getAcqFreqArray()
   {
      return _AcqFreq;
   }
    
   /**
    * Gets the Acquisition Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition Fee Frequency Description or null.
    */
   public final String getAcqFreqDesc( int index )
   {
      return _AcqFreqDesc[index];
   }
    
   /**
    * Gets the Acquisition Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Fee Frequency Description or the specified default value.
    */
   public final String getAcqFreqDesc( int index, String defaultValue )
   {
      return _AcqFreqDesc[index] == null ? defaultValue : _AcqFreqDesc[index];
   }
    
   /**
    * Gets the array of Acquisition Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition Fee Frequency Description values.
    */
   public final String[] getAcqFreqDescArray()
   {
      return _AcqFreqDesc;
   }
    
   /**
    * Gets the Acquisition Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition Fee Type or null.
    */
   public final String getAcqFeeType( int index )
   {
      return _AcqFeeType[index];
   }
    
   /**
    * Gets the Acquisition Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Fee Type or the specified default value.
    */
   public final String getAcqFeeType( int index, String defaultValue )
   {
      return _AcqFeeType[index] == null ? defaultValue : _AcqFeeType[index];
   }
    
   /**
    * Gets the array of Acquisition Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition Fee Type values.
    */
   public final String[] getAcqFeeTypeArray()
   {
      return _AcqFeeType;
   }
    
   /**
    * Gets the Acquisition Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition Fee Type Description or null.
    */
   public final String getAcqFeeTypeDesc( int index )
   {
      return _AcqFeeTypeDesc[index];
   }
    
   /**
    * Gets the Acquisition Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Fee Type Description or the specified default value.
    */
   public final String getAcqFeeTypeDesc( int index, String defaultValue )
   {
      return _AcqFeeTypeDesc[index] == null ? defaultValue : _AcqFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of Acquisition Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition Fee Type Description values.
    */
   public final String[] getAcqFeeTypeDescArray()
   {
      return _AcqFeeTypeDesc;
   }
    
   /**
    * Gets the Acquisition How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition How Paid or null.
    */
   public final String getAcqHowPaid( int index )
   {
      return _AcqHowPaid[index];
   }
    
   /**
    * Gets the Acquisition How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition How Paid or the specified default value.
    */
   public final String getAcqHowPaid( int index, String defaultValue )
   {
      return _AcqHowPaid[index] == null ? defaultValue : _AcqHowPaid[index];
   }
    
   /**
    * Gets the array of Acquisition How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition How Paid values.
    */
   public final String[] getAcqHowPaidArray()
   {
      return _AcqHowPaid;
   }
    
   /**
    * Gets the Acquistion How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquistion How Paid Description or null.
    */
   public final String getAcqHowPaidDesc( int index )
   {
      return _AcqHowPaidDesc[index];
   }
    
   /**
    * Gets the Acquistion How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquistion How Paid Description or the specified default value.
    */
   public final String getAcqHowPaidDesc( int index, String defaultValue )
   {
      return _AcqHowPaidDesc[index] == null ? defaultValue : _AcqHowPaidDesc[index];
   }
    
   /**
    * Gets the array of Acquistion How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquistion How Paid Description values.
    */
   public final String[] getAcqHowPaidDescArray()
   {
      return _AcqHowPaidDesc;
   }
    
   /**
    * Gets the Acquisition Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquisition Based On or null.
    */
   public final String getAcqBasedOn( int index )
   {
      return _AcqBasedOn[index];
   }
    
   /**
    * Gets the Acquisition Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquisition Based On or the specified default value.
    */
   public final String getAcqBasedOn( int index, String defaultValue )
   {
      return _AcqBasedOn[index] == null ? defaultValue : _AcqBasedOn[index];
   }
    
   /**
    * Gets the array of Acquisition Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquisition Based On values.
    */
   public final String[] getAcqBasedOnArray()
   {
      return _AcqBasedOn;
   }
    
   /**
    * Gets the Acquistion Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Acquistion Based On Description or null.
    */
   public final String getAcqBasedOnDesc( int index )
   {
      return _AcqBasedOnDesc[index];
   }
    
   /**
    * Gets the Acquistion Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Acquistion Based On Description or the specified default value.
    */
   public final String getAcqBasedOnDesc( int index, String defaultValue )
   {
      return _AcqBasedOnDesc[index] == null ? defaultValue : _AcqBasedOnDesc[index];
   }
    
   /**
    * Gets the array of Acquistion Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Acquistion Based On Description values.
    */
   public final String[] getAcqBasedOnDescArray()
   {
      return _AcqBasedOnDesc;
   }
    
   /**
    * Gets the With-hold Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-hold Fee Flag or null.
    */
   public final Boolean getWHoldActive( int index )
   {
      return _WHoldActive[index];
   }
    
   /**
    * Gets the With-hold Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-hold Fee Flag or the specified default value.
    */
   public final boolean getWHoldActive( int index, boolean defaultValue )
   {
      return _WHoldActive[index] == null ? defaultValue : _WHoldActive[index].booleanValue();
   }
    
   /**
    * Gets the array of With-hold Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-hold Fee Flag values.
    */
   public final Boolean[] getWHoldActiveArray()
   {
      return _WHoldActive;
   }
    
   /**
    * Gets the With-hold Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-hold Rate or null.
    */
   public final String getWHoldRate( int index )
   {
      return _WHoldRate[index];
   }
    
   /**
    * Gets the With-hold Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-hold Rate or the specified default value.
    */
   public final String getWHoldRate( int index, String defaultValue )
   {
      return _WHoldRate[index] == null ? defaultValue : _WHoldRate[index];
   }
    
   /**
    * Gets the array of With-hold Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-hold Rate values.
    */
   public final String[] getWHoldRateArray()
   {
      return _WHoldRate;
   }
    
   /**
    * Gets the With-hold Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-hold Fee Frequency or null.
    */
   public final String getWHoldFreq( int index )
   {
      return _WHoldFreq[index];
   }
    
   /**
    * Gets the With-hold Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-hold Fee Frequency or the specified default value.
    */
   public final String getWHoldFreq( int index, String defaultValue )
   {
      return _WHoldFreq[index] == null ? defaultValue : _WHoldFreq[index];
   }
    
   /**
    * Gets the array of With-hold Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-hold Fee Frequency values.
    */
   public final String[] getWHoldFreqArray()
   {
      return _WHoldFreq;
   }
    
   /**
    * Gets the With-hold Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-hold Fee Frequency Description or null.
    */
   public final String getWHoldFreqDesc( int index )
   {
      return _WHoldFreqDesc[index];
   }
    
   /**
    * Gets the With-hold Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-hold Fee Frequency Description or the specified default value.
    */
   public final String getWHoldFreqDesc( int index, String defaultValue )
   {
      return _WHoldFreqDesc[index] == null ? defaultValue : _WHoldFreqDesc[index];
   }
    
   /**
    * Gets the array of With-hold Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-hold Fee Frequency Description values.
    */
   public final String[] getWHoldFreqDescArray()
   {
      return _WHoldFreqDesc;
   }
    
   /**
    * Gets the With-Hold Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-Hold Fee Type or null.
    */
   public final String getWHoldFeeType( int index )
   {
      return _WHoldFeeType[index];
   }
    
   /**
    * Gets the With-Hold Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-Hold Fee Type or the specified default value.
    */
   public final String getWHoldFeeType( int index, String defaultValue )
   {
      return _WHoldFeeType[index] == null ? defaultValue : _WHoldFeeType[index];
   }
    
   /**
    * Gets the array of With-Hold Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-Hold Fee Type values.
    */
   public final String[] getWHoldFeeTypeArray()
   {
      return _WHoldFeeType;
   }
    
   /**
    * Gets the With-Hold Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-Hold Fee Type Description or null.
    */
   public final String getWHoldFeeTypeDesc( int index )
   {
      return _WHoldFeeTypeDesc[index];
   }
    
   /**
    * Gets the With-Hold Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-Hold Fee Type Description or the specified default value.
    */
   public final String getWHoldFeeTypeDesc( int index, String defaultValue )
   {
      return _WHoldFeeTypeDesc[index] == null ? defaultValue : _WHoldFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of With-Hold Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-Hold Fee Type Description values.
    */
   public final String[] getWHoldFeeTypeDescArray()
   {
      return _WHoldFeeTypeDesc;
   }
    
   /**
    * Gets the With-hold How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-hold How Paid or null.
    */
   public final String getWHoldHowPaid( int index )
   {
      return _WHoldHowPaid[index];
   }
    
   /**
    * Gets the With-hold How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-hold How Paid or the specified default value.
    */
   public final String getWHoldHowPaid( int index, String defaultValue )
   {
      return _WHoldHowPaid[index] == null ? defaultValue : _WHoldHowPaid[index];
   }
    
   /**
    * Gets the array of With-hold How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-hold How Paid values.
    */
   public final String[] getWHoldHowPaidArray()
   {
      return _WHoldHowPaid;
   }
    
   /**
    * Gets the With-hold How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-hold How Paid Description or null.
    */
   public final String getWHoldHowPaidDesc( int index )
   {
      return _WHoldHowPaidDesc[index];
   }
    
   /**
    * Gets the With-hold How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-hold How Paid Description or the specified default value.
    */
   public final String getWHoldHowPaidDesc( int index, String defaultValue )
   {
      return _WHoldHowPaidDesc[index] == null ? defaultValue : _WHoldHowPaidDesc[index];
   }
    
   /**
    * Gets the array of With-hold How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-hold How Paid Description values.
    */
   public final String[] getWHoldHowPaidDescArray()
   {
      return _WHoldHowPaidDesc;
   }
    
   /**
    * Gets the With-hold Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-hold Based On or null.
    */
   public final String getWHoldBasedIOn( int index )
   {
      return _WHoldBasedIOn[index];
   }
    
   /**
    * Gets the With-hold Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-hold Based On or the specified default value.
    */
   public final String getWHoldBasedIOn( int index, String defaultValue )
   {
      return _WHoldBasedIOn[index] == null ? defaultValue : _WHoldBasedIOn[index];
   }
    
   /**
    * Gets the array of With-hold Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-hold Based On values.
    */
   public final String[] getWHoldBasedIOnArray()
   {
      return _WHoldBasedIOn;
   }
    
   /**
    * Gets the With-hold Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the With-hold Based On Description or null.
    */
   public final String getWHoldBasedOnDesc( int index )
   {
      return _WHoldBasedOnDesc[index];
   }
    
   /**
    * Gets the With-hold Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the With-hold Based On Description or the specified default value.
    */
   public final String getWHoldBasedOnDesc( int index, String defaultValue )
   {
      return _WHoldBasedOnDesc[index] == null ? defaultValue : _WHoldBasedOnDesc[index];
   }
    
   /**
    * Gets the array of With-hold Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of With-hold Based On Description values.
    */
   public final String[] getWHoldBasedOnDescArray()
   {
      return _WHoldBasedOnDesc;
   }
    
   /**
    * Gets the Back-end Load Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load Fee Flag or null.
    */
   public final Boolean getBELActive( int index )
   {
      return _BELActive[index];
   }
    
   /**
    * Gets the Back-end Load Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load Fee Flag or the specified default value.
    */
   public final boolean getBELActive( int index, boolean defaultValue )
   {
      return _BELActive[index] == null ? defaultValue : _BELActive[index].booleanValue();
   }
    
   /**
    * Gets the array of Back-end Load Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load Fee Flag values.
    */
   public final Boolean[] getBELActiveArray()
   {
      return _BELActive;
   }
    
   /**
    * Gets the Back-end Load Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load Rate or null.
    */
   public final String getBELRate( int index )
   {
      return _BELRate[index];
   }
    
   /**
    * Gets the Back-end Load Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load Rate or the specified default value.
    */
   public final String getBELRate( int index, String defaultValue )
   {
      return _BELRate[index] == null ? defaultValue : _BELRate[index];
   }
    
   /**
    * Gets the array of Back-end Load Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load Rate values.
    */
   public final String[] getBELRateArray()
   {
      return _BELRate;
   }
    
   /**
    * Gets the Back-end Load Fee field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load Fee or null.
    */
   public final String getBELFreq( int index )
   {
      return _BELFreq[index];
   }
    
   /**
    * Gets the Back-end Load Fee field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load Fee or the specified default value.
    */
   public final String getBELFreq( int index, String defaultValue )
   {
      return _BELFreq[index] == null ? defaultValue : _BELFreq[index];
   }
    
   /**
    * Gets the array of Back-end Load Fee fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load Fee values.
    */
   public final String[] getBELFreqArray()
   {
      return _BELFreq;
   }
    
   /**
    * Gets the Back-end Load Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load Fee Frequency Description or null.
    */
   public final String getBELFreqDesc( int index )
   {
      return _BELFreqDesc[index];
   }
    
   /**
    * Gets the Back-end Load Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load Fee Frequency Description or the specified default value.
    */
   public final String getBELFreqDesc( int index, String defaultValue )
   {
      return _BELFreqDesc[index] == null ? defaultValue : _BELFreqDesc[index];
   }
    
   /**
    * Gets the array of Back-end Load Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load Fee Frequency Description values.
    */
   public final String[] getBELFreqDescArray()
   {
      return _BELFreqDesc;
   }
    
   /**
    * Gets the Back-end Load Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load Fee Type or null.
    */
   public final String getBELFeeType( int index )
   {
      return _BELFeeType[index];
   }
    
   /**
    * Gets the Back-end Load Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load Fee Type or the specified default value.
    */
   public final String getBELFeeType( int index, String defaultValue )
   {
      return _BELFeeType[index] == null ? defaultValue : _BELFeeType[index];
   }
    
   /**
    * Gets the array of Back-end Load Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load Fee Type values.
    */
   public final String[] getBELFeeTypeArray()
   {
      return _BELFeeType;
   }
    
   /**
    * Gets the Back-end Load Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load Fee Type Description or null.
    */
   public final String getBELFeeTypeDesc( int index )
   {
      return _BELFeeTypeDesc[index];
   }
    
   /**
    * Gets the Back-end Load Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load Fee Type Description or the specified default value.
    */
   public final String getBELFeeTypeDesc( int index, String defaultValue )
   {
      return _BELFeeTypeDesc[index] == null ? defaultValue : _BELFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of Back-end Load Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load Fee Type Description values.
    */
   public final String[] getBELFeeTypeDescArray()
   {
      return _BELFeeTypeDesc;
   }
    
   /**
    * Gets the Back-end Load How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load How Paid or null.
    */
   public final String getBELHowPaid( int index )
   {
      return _BELHowPaid[index];
   }
    
   /**
    * Gets the Back-end Load How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load How Paid or the specified default value.
    */
   public final String getBELHowPaid( int index, String defaultValue )
   {
      return _BELHowPaid[index] == null ? defaultValue : _BELHowPaid[index];
   }
    
   /**
    * Gets the array of Back-end Load How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load How Paid values.
    */
   public final String[] getBELHowPaidArray()
   {
      return _BELHowPaid;
   }
    
   /**
    * Gets the Back-end Load How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load How Paid Description or null.
    */
   public final String getBELHowPaidDesc( int index )
   {
      return _BELHowPaidDesc[index];
   }
    
   /**
    * Gets the Back-end Load How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load How Paid Description or the specified default value.
    */
   public final String getBELHowPaidDesc( int index, String defaultValue )
   {
      return _BELHowPaidDesc[index] == null ? defaultValue : _BELHowPaidDesc[index];
   }
    
   /**
    * Gets the array of Back-end Load How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load How Paid Description values.
    */
   public final String[] getBELHowPaidDescArray()
   {
      return _BELHowPaidDesc;
   }
    
   /**
    * Gets the Back-end Load Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load Based On or null.
    */
   public final String getBELBasedOn( int index )
   {
      return _BELBasedOn[index];
   }
    
   /**
    * Gets the Back-end Load Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load Based On or the specified default value.
    */
   public final String getBELBasedOn( int index, String defaultValue )
   {
      return _BELBasedOn[index] == null ? defaultValue : _BELBasedOn[index];
   }
    
   /**
    * Gets the array of Back-end Load Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load Based On values.
    */
   public final String[] getBELBasedOnArray()
   {
      return _BELBasedOn;
   }
    
   /**
    * Gets the Back-end Load Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Back-end Load Based On Description or null.
    */
   public final String getBELBasedOnDesc( int index )
   {
      return _BELBasedOnDesc[index];
   }
    
   /**
    * Gets the Back-end Load Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Back-end Load Based On Description or the specified default value.
    */
   public final String getBELBasedOnDesc( int index, String defaultValue )
   {
      return _BELBasedOnDesc[index] == null ? defaultValue : _BELBasedOnDesc[index];
   }
    
   /**
    * Gets the array of Back-end Load Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Back-end Load Based On Description values.
    */
   public final String[] getBELBasedOnDescArray()
   {
      return _BELBasedOnDesc;
   }
    
   /**
    * Gets the Transfer Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Fee Flag or null.
    */
   public final Boolean getTfrActive( int index )
   {
      return _TfrActive[index];
   }
    
   /**
    * Gets the Transfer Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Fee Flag or the specified default value.
    */
   public final boolean getTfrActive( int index, boolean defaultValue )
   {
      return _TfrActive[index] == null ? defaultValue : _TfrActive[index].booleanValue();
   }
    
   /**
    * Gets the array of Transfer Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Fee Flag values.
    */
   public final Boolean[] getTfrActiveArray()
   {
      return _TfrActive;
   }
    
   /**
    * Gets the Transfer Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Rate or null.
    */
   public final String getTfrRate( int index )
   {
      return _TfrRate[index];
   }
    
   /**
    * Gets the Transfer Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Rate or the specified default value.
    */
   public final String getTfrRate( int index, String defaultValue )
   {
      return _TfrRate[index] == null ? defaultValue : _TfrRate[index];
   }
    
   /**
    * Gets the array of Transfer Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Rate values.
    */
   public final String[] getTfrRateArray()
   {
      return _TfrRate;
   }
    
   /**
    * Gets the Transfer Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Fee Frequency or null.
    */
   public final String getTfrFreq( int index )
   {
      return _TfrFreq[index];
   }
    
   /**
    * Gets the Transfer Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Fee Frequency or the specified default value.
    */
   public final String getTfrFreq( int index, String defaultValue )
   {
      return _TfrFreq[index] == null ? defaultValue : _TfrFreq[index];
   }
    
   /**
    * Gets the array of Transfer Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Fee Frequency values.
    */
   public final String[] getTfrFreqArray()
   {
      return _TfrFreq;
   }
    
   /**
    * Gets the Transfer Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Fee Frequency Description or null.
    */
   public final String getTfrFreqDesc( int index )
   {
      return _TfrFreqDesc[index];
   }
    
   /**
    * Gets the Transfer Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Fee Frequency Description or the specified default value.
    */
   public final String getTfrFreqDesc( int index, String defaultValue )
   {
      return _TfrFreqDesc[index] == null ? defaultValue : _TfrFreqDesc[index];
   }
    
   /**
    * Gets the array of Transfer Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Fee Frequency Description values.
    */
   public final String[] getTfrFreqDescArray()
   {
      return _TfrFreqDesc;
   }
    
   /**
    * Gets the Transfer Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Fee Type or null.
    */
   public final String getTfrFeeType( int index )
   {
      return _TfrFeeType[index];
   }
    
   /**
    * Gets the Transfer Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Fee Type or the specified default value.
    */
   public final String getTfrFeeType( int index, String defaultValue )
   {
      return _TfrFeeType[index] == null ? defaultValue : _TfrFeeType[index];
   }
    
   /**
    * Gets the array of Transfer Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Fee Type values.
    */
   public final String[] getTfrFeeTypeArray()
   {
      return _TfrFeeType;
   }
    
   /**
    * Gets the Transfer Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Fee Type Description or null.
    */
   public final String getTfrFeeTypeDesc( int index )
   {
      return _TfrFeeTypeDesc[index];
   }
    
   /**
    * Gets the Transfer Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Fee Type Description or the specified default value.
    */
   public final String getTfrFeeTypeDesc( int index, String defaultValue )
   {
      return _TfrFeeTypeDesc[index] == null ? defaultValue : _TfrFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of Transfer Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Fee Type Description values.
    */
   public final String[] getTfrFeeTypeDescArray()
   {
      return _TfrFeeTypeDesc;
   }
    
   /**
    * Gets the Transfer How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer How Paid or null.
    */
   public final String getTfrHowPaid( int index )
   {
      return _TfrHowPaid[index];
   }
    
   /**
    * Gets the Transfer How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer How Paid or the specified default value.
    */
   public final String getTfrHowPaid( int index, String defaultValue )
   {
      return _TfrHowPaid[index] == null ? defaultValue : _TfrHowPaid[index];
   }
    
   /**
    * Gets the array of Transfer How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer How Paid values.
    */
   public final String[] getTfrHowPaidArray()
   {
      return _TfrHowPaid;
   }
    
   /**
    * Gets the Transfer How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer How Paid Description or null.
    */
   public final String getTfrHowPaidDesc( int index )
   {
      return _TfrHowPaidDesc[index];
   }
    
   /**
    * Gets the Transfer How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer How Paid Description or the specified default value.
    */
   public final String getTfrHowPaidDesc( int index, String defaultValue )
   {
      return _TfrHowPaidDesc[index] == null ? defaultValue : _TfrHowPaidDesc[index];
   }
    
   /**
    * Gets the array of Transfer How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer How Paid Description values.
    */
   public final String[] getTfrHowPaidDescArray()
   {
      return _TfrHowPaidDesc;
   }
    
   /**
    * Gets the Transfer Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Based On or null.
    */
   public final String getTfrBasedOn( int index )
   {
      return _TfrBasedOn[index];
   }
    
   /**
    * Gets the Transfer Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Based On or the specified default value.
    */
   public final String getTfrBasedOn( int index, String defaultValue )
   {
      return _TfrBasedOn[index] == null ? defaultValue : _TfrBasedOn[index];
   }
    
   /**
    * Gets the array of Transfer Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Based On values.
    */
   public final String[] getTfrBasedOnArray()
   {
      return _TfrBasedOn;
   }
    
   /**
    * Gets the Transfer Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Transfer Based On Description or null.
    */
   public final String getTfrBasedOnDesc( int index )
   {
      return _TfrBasedOnDesc[index];
   }
    
   /**
    * Gets the Transfer Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Transfer Based On Description or the specified default value.
    */
   public final String getTfrBasedOnDesc( int index, String defaultValue )
   {
      return _TfrBasedOnDesc[index] == null ? defaultValue : _TfrBasedOnDesc[index];
   }
    
   /**
    * Gets the array of Transfer Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Transfer Based On Description values.
    */
   public final String[] getTfrBasedOnDescArray()
   {
      return _TfrBasedOnDesc;
   }
    
   /**
    * Gets the RRSP Trustee Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee Fee Flag or null.
    */
   public final Boolean getRRSPActive( int index )
   {
      return _RRSPActive[index];
   }
    
   /**
    * Gets the RRSP Trustee Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee Fee Flag or the specified default value.
    */
   public final boolean getRRSPActive( int index, boolean defaultValue )
   {
      return _RRSPActive[index] == null ? defaultValue : _RRSPActive[index].booleanValue();
   }
    
   /**
    * Gets the array of RRSP Trustee Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee Fee Flag values.
    */
   public final Boolean[] getRRSPActiveArray()
   {
      return _RRSPActive;
   }
    
   /**
    * Gets the RRSP Trustee Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee Rate or null.
    */
   public final String getRRSPRate( int index )
   {
      return _RRSPRate[index];
   }
    
   /**
    * Gets the RRSP Trustee Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee Rate or the specified default value.
    */
   public final String getRRSPRate( int index, String defaultValue )
   {
      return _RRSPRate[index] == null ? defaultValue : _RRSPRate[index];
   }
    
   /**
    * Gets the array of RRSP Trustee Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee Rate values.
    */
   public final String[] getRRSPRateArray()
   {
      return _RRSPRate;
   }
    
   /**
    * Gets the RRSP Trustee Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee Fee Frequency or null.
    */
   public final String getRRSPFreq( int index )
   {
      return _RRSPFreq[index];
   }
    
   /**
    * Gets the RRSP Trustee Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee Fee Frequency or the specified default value.
    */
   public final String getRRSPFreq( int index, String defaultValue )
   {
      return _RRSPFreq[index] == null ? defaultValue : _RRSPFreq[index];
   }
    
   /**
    * Gets the array of RRSP Trustee Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee Fee Frequency values.
    */
   public final String[] getRRSPFreqArray()
   {
      return _RRSPFreq;
   }
    
   /**
    * Gets the RRSP Trustee Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee Fee Frequency Description or null.
    */
   public final String getRRSPFreqDesc( int index )
   {
      return _RRSPFreqDesc[index];
   }
    
   /**
    * Gets the RRSP Trustee Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee Fee Frequency Description or the specified default value.
    */
   public final String getRRSPFreqDesc( int index, String defaultValue )
   {
      return _RRSPFreqDesc[index] == null ? defaultValue : _RRSPFreqDesc[index];
   }
    
   /**
    * Gets the array of RRSP Trustee Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee Fee Frequency Description values.
    */
   public final String[] getRRSPFreqDescArray()
   {
      return _RRSPFreqDesc;
   }
    
   /**
    * Gets the RRSP Trustee Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee Fee Type or null.
    */
   public final String getRRSPFeeType( int index )
   {
      return _RRSPFeeType[index];
   }
    
   /**
    * Gets the RRSP Trustee Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee Fee Type or the specified default value.
    */
   public final String getRRSPFeeType( int index, String defaultValue )
   {
      return _RRSPFeeType[index] == null ? defaultValue : _RRSPFeeType[index];
   }
    
   /**
    * Gets the array of RRSP Trustee Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee Fee Type values.
    */
   public final String[] getRRSPFeeTypeArray()
   {
      return _RRSPFeeType;
   }
    
   /**
    * Gets the RRSP Trustee Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee Fee Type Description or null.
    */
   public final String getRRSPFeeTypeDesc( int index )
   {
      return _RRSPFeeTypeDesc[index];
   }
    
   /**
    * Gets the RRSP Trustee Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee Fee Type Description or the specified default value.
    */
   public final String getRRSPFeeTypeDesc( int index, String defaultValue )
   {
      return _RRSPFeeTypeDesc[index] == null ? defaultValue : _RRSPFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of RRSP Trustee Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee Fee Type Description values.
    */
   public final String[] getRRSPFeeTypeDescArray()
   {
      return _RRSPFeeTypeDesc;
   }
    
   /**
    * Gets the RRSP Trustee How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee How Paid or null.
    */
   public final String getRRSPHowPaid( int index )
   {
      return _RRSPHowPaid[index];
   }
    
   /**
    * Gets the RRSP Trustee How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee How Paid or the specified default value.
    */
   public final String getRRSPHowPaid( int index, String defaultValue )
   {
      return _RRSPHowPaid[index] == null ? defaultValue : _RRSPHowPaid[index];
   }
    
   /**
    * Gets the array of RRSP Trustee How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee How Paid values.
    */
   public final String[] getRRSPHowPaidArray()
   {
      return _RRSPHowPaid;
   }
    
   /**
    * Gets the RRSP Trustee How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee How Paid Description or null.
    */
   public final String getRRSPHowPaidDesc( int index )
   {
      return _RRSPHowPaidDesc[index];
   }
    
   /**
    * Gets the RRSP Trustee How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee How Paid Description or the specified default value.
    */
   public final String getRRSPHowPaidDesc( int index, String defaultValue )
   {
      return _RRSPHowPaidDesc[index] == null ? defaultValue : _RRSPHowPaidDesc[index];
   }
    
   /**
    * Gets the array of RRSP Trustee How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee How Paid Description values.
    */
   public final String[] getRRSPHowPaidDescArray()
   {
      return _RRSPHowPaidDesc;
   }
    
   /**
    * Gets the RRSP Trustee Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee Based On or null.
    */
   public final String getRRSPBasedOn( int index )
   {
      return _RRSPBasedOn[index];
   }
    
   /**
    * Gets the RRSP Trustee Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee Based On or the specified default value.
    */
   public final String getRRSPBasedOn( int index, String defaultValue )
   {
      return _RRSPBasedOn[index] == null ? defaultValue : _RRSPBasedOn[index];
   }
    
   /**
    * Gets the array of RRSP Trustee Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee Based On values.
    */
   public final String[] getRRSPBasedOnArray()
   {
      return _RRSPBasedOn;
   }
    
   /**
    * Gets the RRSP Trustee Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRSP Trustee Based On Description or null.
    */
   public final String getRRSPBasedOnDesc( int index )
   {
      return _RRSPBasedOnDesc[index];
   }
    
   /**
    * Gets the RRSP Trustee Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRSP Trustee Based On Description or the specified default value.
    */
   public final String getRRSPBasedOnDesc( int index, String defaultValue )
   {
      return _RRSPBasedOnDesc[index] == null ? defaultValue : _RRSPBasedOnDesc[index];
   }
    
   /**
    * Gets the array of RRSP Trustee Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRSP Trustee Based On Description values.
    */
   public final String[] getRRSPBasedOnDescArray()
   {
      return _RRSPBasedOnDesc;
   }
    
   /**
    * Gets the RRIF Admin Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin Fee Flag or null.
    */
   public final Boolean getRRIFActive( int index )
   {
      return _RRIFActive[index];
   }
    
   /**
    * Gets the RRIF Admin Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin Fee Flag or the specified default value.
    */
   public final boolean getRRIFActive( int index, boolean defaultValue )
   {
      return _RRIFActive[index] == null ? defaultValue : _RRIFActive[index].booleanValue();
   }
    
   /**
    * Gets the array of RRIF Admin Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin Fee Flag values.
    */
   public final Boolean[] getRRIFActiveArray()
   {
      return _RRIFActive;
   }
    
   /**
    * Gets the RRIF Admin Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin Rate or null.
    */
   public final String getRRIFRate( int index )
   {
      return _RRIFRate[index];
   }
    
   /**
    * Gets the RRIF Admin Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin Rate or the specified default value.
    */
   public final String getRRIFRate( int index, String defaultValue )
   {
      return _RRIFRate[index] == null ? defaultValue : _RRIFRate[index];
   }
    
   /**
    * Gets the array of RRIF Admin Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin Rate values.
    */
   public final String[] getRRIFRateArray()
   {
      return _RRIFRate;
   }
    
   /**
    * Gets the RRIF Admin Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin Fee Frequency or null.
    */
   public final String getRRIFFreq( int index )
   {
      return _RRIFFreq[index];
   }
    
   /**
    * Gets the RRIF Admin Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin Fee Frequency or the specified default value.
    */
   public final String getRRIFFreq( int index, String defaultValue )
   {
      return _RRIFFreq[index] == null ? defaultValue : _RRIFFreq[index];
   }
    
   /**
    * Gets the array of RRIF Admin Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin Fee Frequency values.
    */
   public final String[] getRRIFFreqArray()
   {
      return _RRIFFreq;
   }
    
   /**
    * Gets the RRIF Admin Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin Fee Frequency Description or null.
    */
   public final String getRRIFFreqDesc( int index )
   {
      return _RRIFFreqDesc[index];
   }
    
   /**
    * Gets the RRIF Admin Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin Fee Frequency Description or the specified default value.
    */
   public final String getRRIFFreqDesc( int index, String defaultValue )
   {
      return _RRIFFreqDesc[index] == null ? defaultValue : _RRIFFreqDesc[index];
   }
    
   /**
    * Gets the array of RRIF Admin Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin Fee Frequency Description values.
    */
   public final String[] getRRIFFreqDescArray()
   {
      return _RRIFFreqDesc;
   }
    
   /**
    * Gets the RRIF Admin Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin Fee Type or null.
    */
   public final String getRRIFFeeType( int index )
   {
      return _RRIFFeeType[index];
   }
    
   /**
    * Gets the RRIF Admin Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin Fee Type or the specified default value.
    */
   public final String getRRIFFeeType( int index, String defaultValue )
   {
      return _RRIFFeeType[index] == null ? defaultValue : _RRIFFeeType[index];
   }
    
   /**
    * Gets the array of RRIF Admin Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin Fee Type values.
    */
   public final String[] getRRIFFeeTypeArray()
   {
      return _RRIFFeeType;
   }
    
   /**
    * Gets the RRIF Admin Fee Type Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin Fee Type Desc or null.
    */
   public final String getRRIFFeeTypeDesc( int index )
   {
      return _RRIFFeeTypeDesc[index];
   }
    
   /**
    * Gets the RRIF Admin Fee Type Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin Fee Type Desc or the specified default value.
    */
   public final String getRRIFFeeTypeDesc( int index, String defaultValue )
   {
      return _RRIFFeeTypeDesc[index] == null ? defaultValue : _RRIFFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of RRIF Admin Fee Type Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin Fee Type Desc values.
    */
   public final String[] getRRIFFeeTypeDescArray()
   {
      return _RRIFFeeTypeDesc;
   }
    
   /**
    * Gets the RRIF Admin How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin How Paid or null.
    */
   public final String getRRIFHowPaid( int index )
   {
      return _RRIFHowPaid[index];
   }
    
   /**
    * Gets the RRIF Admin How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin How Paid or the specified default value.
    */
   public final String getRRIFHowPaid( int index, String defaultValue )
   {
      return _RRIFHowPaid[index] == null ? defaultValue : _RRIFHowPaid[index];
   }
    
   /**
    * Gets the array of RRIF Admin How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin How Paid values.
    */
   public final String[] getRRIFHowPaidArray()
   {
      return _RRIFHowPaid;
   }
    
   /**
    * Gets the RRIF Admin How Paid Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin How Paid Desc or null.
    */
   public final String getRRIFHowPaidDesc( int index )
   {
      return _RRIFHowPaidDesc[index];
   }
    
   /**
    * Gets the RRIF Admin How Paid Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin How Paid Desc or the specified default value.
    */
   public final String getRRIFHowPaidDesc( int index, String defaultValue )
   {
      return _RRIFHowPaidDesc[index] == null ? defaultValue : _RRIFHowPaidDesc[index];
   }
    
   /**
    * Gets the array of RRIF Admin How Paid Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin How Paid Desc values.
    */
   public final String[] getRRIFHowPaidDescArray()
   {
      return _RRIFHowPaidDesc;
   }
    
   /**
    * Gets the RRIF Admin Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin Based On or null.
    */
   public final String getRRIFBasedOn( int index )
   {
      return _RRIFBasedOn[index];
   }
    
   /**
    * Gets the RRIF Admin Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin Based On or the specified default value.
    */
   public final String getRRIFBasedOn( int index, String defaultValue )
   {
      return _RRIFBasedOn[index] == null ? defaultValue : _RRIFBasedOn[index];
   }
    
   /**
    * Gets the array of RRIF Admin Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin Based On values.
    */
   public final String[] getRRIFBasedOnArray()
   {
      return _RRIFBasedOn;
   }
    
   /**
    * Gets the RRIF Admin Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RRIF Admin Based On Description or null.
    */
   public final String getRRIFBasedOnDesc( int index )
   {
      return _RRIFBasedOnDesc[index];
   }
    
   /**
    * Gets the RRIF Admin Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RRIF Admin Based On Description or the specified default value.
    */
   public final String getRRIFBasedOnDesc( int index, String defaultValue )
   {
      return _RRIFBasedOnDesc[index] == null ? defaultValue : _RRIFBasedOnDesc[index];
   }
    
   /**
    * Gets the array of RRIF Admin Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RRIF Admin Based On Description values.
    */
   public final String[] getRRIFBasedOnDescArray()
   {
      return _RRIFBasedOnDesc;
   }
    
   /**
    * Gets the Incentive Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive Fee Flag or null.
    */
   public final Boolean getIncvActive( int index )
   {
      return _IncvActive[index];
   }
    
   /**
    * Gets the Incentive Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive Fee Flag or the specified default value.
    */
   public final boolean getIncvActive( int index, boolean defaultValue )
   {
      return _IncvActive[index] == null ? defaultValue : _IncvActive[index].booleanValue();
   }
    
   /**
    * Gets the array of Incentive Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive Fee Flag values.
    */
   public final Boolean[] getIncvActiveArray()
   {
      return _IncvActive;
   }
    
   /**
    * Gets the Incentive Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive Rate or null.
    */
   public final String getIncvRate( int index )
   {
      return _IncvRate[index];
   }
    
   /**
    * Gets the Incentive Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive Rate or the specified default value.
    */
   public final String getIncvRate( int index, String defaultValue )
   {
      return _IncvRate[index] == null ? defaultValue : _IncvRate[index];
   }
    
   /**
    * Gets the array of Incentive Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive Rate values.
    */
   public final String[] getIncvRateArray()
   {
      return _IncvRate;
   }
    
   /**
    * Gets the Incentive Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive Fee Frequency or null.
    */
   public final String getIncvFreq( int index )
   {
      return _IncvFreq[index];
   }
    
   /**
    * Gets the Incentive Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive Fee Frequency or the specified default value.
    */
   public final String getIncvFreq( int index, String defaultValue )
   {
      return _IncvFreq[index] == null ? defaultValue : _IncvFreq[index];
   }
    
   /**
    * Gets the array of Incentive Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive Fee Frequency values.
    */
   public final String[] getIncvFreqArray()
   {
      return _IncvFreq;
   }
    
   /**
    * Gets the Incentive Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive Fee Frequency Description or null.
    */
   public final String getIncvFreqDesc( int index )
   {
      return _IncvFreqDesc[index];
   }
    
   /**
    * Gets the Incentive Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive Fee Frequency Description or the specified default value.
    */
   public final String getIncvFreqDesc( int index, String defaultValue )
   {
      return _IncvFreqDesc[index] == null ? defaultValue : _IncvFreqDesc[index];
   }
    
   /**
    * Gets the array of Incentive Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive Fee Frequency Description values.
    */
   public final String[] getIncvFreqDescArray()
   {
      return _IncvFreqDesc;
   }
    
   /**
    * Gets the Incentive Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive Fee Type or null.
    */
   public final String getIncvFeeType( int index )
   {
      return _IncvFeeType[index];
   }
    
   /**
    * Gets the Incentive Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive Fee Type or the specified default value.
    */
   public final String getIncvFeeType( int index, String defaultValue )
   {
      return _IncvFeeType[index] == null ? defaultValue : _IncvFeeType[index];
   }
    
   /**
    * Gets the array of Incentive Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive Fee Type values.
    */
   public final String[] getIncvFeeTypeArray()
   {
      return _IncvFeeType;
   }
    
   /**
    * Gets the Incentive Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive Fee Type Description or null.
    */
   public final String getIncvFeeTypeDesc( int index )
   {
      return _IncvFeeTypeDesc[index];
   }
    
   /**
    * Gets the Incentive Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive Fee Type Description or the specified default value.
    */
   public final String getIncvFeeTypeDesc( int index, String defaultValue )
   {
      return _IncvFeeTypeDesc[index] == null ? defaultValue : _IncvFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of Incentive Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive Fee Type Description values.
    */
   public final String[] getIncvFeeTypeDescArray()
   {
      return _IncvFeeTypeDesc;
   }
    
   /**
    * Gets the Incentive How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive How Paid or null.
    */
   public final String getIncvHowPaid( int index )
   {
      return _IncvHowPaid[index];
   }
    
   /**
    * Gets the Incentive How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive How Paid or the specified default value.
    */
   public final String getIncvHowPaid( int index, String defaultValue )
   {
      return _IncvHowPaid[index] == null ? defaultValue : _IncvHowPaid[index];
   }
    
   /**
    * Gets the array of Incentive How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive How Paid values.
    */
   public final String[] getIncvHowPaidArray()
   {
      return _IncvHowPaid;
   }
    
   /**
    * Gets the Incentive How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive How Paid Description or null.
    */
   public final String getIncvHowPaidDesc( int index )
   {
      return _IncvHowPaidDesc[index];
   }
    
   /**
    * Gets the Incentive How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive How Paid Description or the specified default value.
    */
   public final String getIncvHowPaidDesc( int index, String defaultValue )
   {
      return _IncvHowPaidDesc[index] == null ? defaultValue : _IncvHowPaidDesc[index];
   }
    
   /**
    * Gets the array of Incentive How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive How Paid Description values.
    */
   public final String[] getIncvHowPaidDescArray()
   {
      return _IncvHowPaidDesc;
   }
    
   /**
    * Gets the Incentive Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive Based On or null.
    */
   public final String getIncvBasedOn( int index )
   {
      return _IncvBasedOn[index];
   }
    
   /**
    * Gets the Incentive Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive Based On or the specified default value.
    */
   public final String getIncvBasedOn( int index, String defaultValue )
   {
      return _IncvBasedOn[index] == null ? defaultValue : _IncvBasedOn[index];
   }
    
   /**
    * Gets the array of Incentive Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive Based On values.
    */
   public final String[] getIncvBasedOnArray()
   {
      return _IncvBasedOn;
   }
    
   /**
    * Gets the Incentive Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Incentive Based On Description or null.
    */
   public final String getIncvBasedOnDesc( int index )
   {
      return _IncvBasedOnDesc[index];
   }
    
   /**
    * Gets the Incentive Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Incentive Based On Description or the specified default value.
    */
   public final String getIncvBasedOnDesc( int index, String defaultValue )
   {
      return _IncvBasedOnDesc[index] == null ? defaultValue : _IncvBasedOnDesc[index];
   }
    
   /**
    * Gets the array of Incentive Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Incentive Based On Description values.
    */
   public final String[] getIncvBasedOnDescArray()
   {
      return _IncvBasedOnDesc;
   }
    
   /**
    * Gets the Trailer Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer Fee Flag or null.
    */
   public final Boolean getTrlActive( int index )
   {
      return _TrlActive[index];
   }
    
   /**
    * Gets the Trailer Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer Fee Flag or the specified default value.
    */
   public final boolean getTrlActive( int index, boolean defaultValue )
   {
      return _TrlActive[index] == null ? defaultValue : _TrlActive[index].booleanValue();
   }
    
   /**
    * Gets the array of Trailer Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer Fee Flag values.
    */
   public final Boolean[] getTrlActiveArray()
   {
      return _TrlActive;
   }
    
   /**
    * Gets the Trailer Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer Rate or null.
    */
   public final String getTrlRate( int index )
   {
      return _TrlRate[index];
   }
    
   /**
    * Gets the Trailer Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer Rate or the specified default value.
    */
   public final String getTrlRate( int index, String defaultValue )
   {
      return _TrlRate[index] == null ? defaultValue : _TrlRate[index];
   }
    
   /**
    * Gets the array of Trailer Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer Rate values.
    */
   public final String[] getTrlRateArray()
   {
      return _TrlRate;
   }
    
   /**
    * Gets the Trailer Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer Fee Frequency or null.
    */
   public final String getTrlFreq( int index )
   {
      return _TrlFreq[index];
   }
    
   /**
    * Gets the Trailer Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer Fee Frequency or the specified default value.
    */
   public final String getTrlFreq( int index, String defaultValue )
   {
      return _TrlFreq[index] == null ? defaultValue : _TrlFreq[index];
   }
    
   /**
    * Gets the array of Trailer Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer Fee Frequency values.
    */
   public final String[] getTrlFreqArray()
   {
      return _TrlFreq;
   }
    
   /**
    * Gets the Trailer Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer Fee Frequency Description or null.
    */
   public final String getTrlFreqDesc( int index )
   {
      return _TrlFreqDesc[index];
   }
    
   /**
    * Gets the Trailer Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer Fee Frequency Description or the specified default value.
    */
   public final String getTrlFreqDesc( int index, String defaultValue )
   {
      return _TrlFreqDesc[index] == null ? defaultValue : _TrlFreqDesc[index];
   }
    
   /**
    * Gets the array of Trailer Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer Fee Frequency Description values.
    */
   public final String[] getTrlFreqDescArray()
   {
      return _TrlFreqDesc;
   }
    
   /**
    * Gets the Trailer Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer Fee Type or null.
    */
   public final String getTrlFeeType( int index )
   {
      return _TrlFeeType[index];
   }
    
   /**
    * Gets the Trailer Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer Fee Type or the specified default value.
    */
   public final String getTrlFeeType( int index, String defaultValue )
   {
      return _TrlFeeType[index] == null ? defaultValue : _TrlFeeType[index];
   }
    
   /**
    * Gets the array of Trailer Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer Fee Type values.
    */
   public final String[] getTrlFeeTypeArray()
   {
      return _TrlFeeType;
   }
    
   /**
    * Gets the Trailer Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer Fee Type Description or null.
    */
   public final String getTrlFeeTypeDesc( int index )
   {
      return _TrlFeeTypeDesc[index];
   }
    
   /**
    * Gets the Trailer Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer Fee Type Description or the specified default value.
    */
   public final String getTrlFeeTypeDesc( int index, String defaultValue )
   {
      return _TrlFeeTypeDesc[index] == null ? defaultValue : _TrlFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of Trailer Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer Fee Type Description values.
    */
   public final String[] getTrlFeeTypeDescArray()
   {
      return _TrlFeeTypeDesc;
   }
    
   /**
    * Gets the Trailer How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer How Paid or null.
    */
   public final String getTrlHowPaid( int index )
   {
      return _TrlHowPaid[index];
   }
    
   /**
    * Gets the Trailer How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer How Paid or the specified default value.
    */
   public final String getTrlHowPaid( int index, String defaultValue )
   {
      return _TrlHowPaid[index] == null ? defaultValue : _TrlHowPaid[index];
   }
    
   /**
    * Gets the array of Trailer How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer How Paid values.
    */
   public final String[] getTrlHowPaidArray()
   {
      return _TrlHowPaid;
   }
    
   /**
    * Gets the Trailer How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer How Paid Description or null.
    */
   public final String getTrlHowPaidDesc( int index )
   {
      return _TrlHowPaidDesc[index];
   }
    
   /**
    * Gets the Trailer How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer How Paid Description or the specified default value.
    */
   public final String getTrlHowPaidDesc( int index, String defaultValue )
   {
      return _TrlHowPaidDesc[index] == null ? defaultValue : _TrlHowPaidDesc[index];
   }
    
   /**
    * Gets the array of Trailer How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer How Paid Description values.
    */
   public final String[] getTrlHowPaidDescArray()
   {
      return _TrlHowPaidDesc;
   }
    
   /**
    * Gets the Trailer Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer Based On or null.
    */
   public final String getTrlBasedOn( int index )
   {
      return _TrlBasedOn[index];
   }
    
   /**
    * Gets the Trailer Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer Based On or the specified default value.
    */
   public final String getTrlBasedOn( int index, String defaultValue )
   {
      return _TrlBasedOn[index] == null ? defaultValue : _TrlBasedOn[index];
   }
    
   /**
    * Gets the array of Trailer Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer Based On values.
    */
   public final String[] getTrlBasedOnArray()
   {
      return _TrlBasedOn;
   }
    
   /**
    * Gets the Trailer Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Trailer Based On Description or null.
    */
   public final String getTrlBasedOnDesc( int index )
   {
      return _TrlBasedOnDesc[index];
   }
    
   /**
    * Gets the Trailer Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Trailer Based On Description or the specified default value.
    */
   public final String getTrlBasedOnDesc( int index, String defaultValue )
   {
      return _TrlBasedOnDesc[index] == null ? defaultValue : _TrlBasedOnDesc[index];
   }
    
   /**
    * Gets the array of Trailer Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Trailer Based On Description values.
    */
   public final String[] getTrlBasedOnDescArray()
   {
      return _TrlBasedOnDesc;
   }
    
   /**
    * Gets the R.O.A. Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. Fee Flag or null.
    */
   public final Boolean getROAActive( int index )
   {
      return _ROAActive[index];
   }
    
   /**
    * Gets the R.O.A. Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. Fee Flag or the specified default value.
    */
   public final boolean getROAActive( int index, boolean defaultValue )
   {
      return _ROAActive[index] == null ? defaultValue : _ROAActive[index].booleanValue();
   }
    
   /**
    * Gets the array of R.O.A. Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. Fee Flag values.
    */
   public final Boolean[] getROAActiveArray()
   {
      return _ROAActive;
   }
    
   /**
    * Gets the R.O.A. Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. Rate or null.
    */
   public final String getROARate( int index )
   {
      return _ROARate[index];
   }
    
   /**
    * Gets the R.O.A. Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. Rate or the specified default value.
    */
   public final String getROARate( int index, String defaultValue )
   {
      return _ROARate[index] == null ? defaultValue : _ROARate[index];
   }
    
   /**
    * Gets the array of R.O.A. Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. Rate values.
    */
   public final String[] getROARateArray()
   {
      return _ROARate;
   }
    
   /**
    * Gets the R.O.A. Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. Fee Frequency or null.
    */
   public final String getROAFreq( int index )
   {
      return _ROAFreq[index];
   }
    
   /**
    * Gets the R.O.A. Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. Fee Frequency or the specified default value.
    */
   public final String getROAFreq( int index, String defaultValue )
   {
      return _ROAFreq[index] == null ? defaultValue : _ROAFreq[index];
   }
    
   /**
    * Gets the array of R.O.A. Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. Fee Frequency values.
    */
   public final String[] getROAFreqArray()
   {
      return _ROAFreq;
   }
    
   /**
    * Gets the R.O.A. Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. Fee Frequency Description or null.
    */
   public final String getROAFreqDesc( int index )
   {
      return _ROAFreqDesc[index];
   }
    
   /**
    * Gets the R.O.A. Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. Fee Frequency Description or the specified default value.
    */
   public final String getROAFreqDesc( int index, String defaultValue )
   {
      return _ROAFreqDesc[index] == null ? defaultValue : _ROAFreqDesc[index];
   }
    
   /**
    * Gets the array of R.O.A. Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. Fee Frequency Description values.
    */
   public final String[] getROAFreqDescArray()
   {
      return _ROAFreqDesc;
   }
    
   /**
    * Gets the R.O.A. Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. Fee Type or null.
    */
   public final String getROAFeeType( int index )
   {
      return _ROAFeeType[index];
   }
    
   /**
    * Gets the R.O.A. Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. Fee Type or the specified default value.
    */
   public final String getROAFeeType( int index, String defaultValue )
   {
      return _ROAFeeType[index] == null ? defaultValue : _ROAFeeType[index];
   }
    
   /**
    * Gets the array of R.O.A. Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. Fee Type values.
    */
   public final String[] getROAFeeTypeArray()
   {
      return _ROAFeeType;
   }
    
   /**
    * Gets the R.O.A. Fee Type Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. Fee Type Desc or null.
    */
   public final String getROAFeeTypeDesc( int index )
   {
      return _ROAFeeTypeDesc[index];
   }
    
   /**
    * Gets the R.O.A. Fee Type Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. Fee Type Desc or the specified default value.
    */
   public final String getROAFeeTypeDesc( int index, String defaultValue )
   {
      return _ROAFeeTypeDesc[index] == null ? defaultValue : _ROAFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of R.O.A. Fee Type Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. Fee Type Desc values.
    */
   public final String[] getROAFeeTypeDescArray()
   {
      return _ROAFeeTypeDesc;
   }
    
   /**
    * Gets the R.O.A. How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. How Paid or null.
    */
   public final String getROAHowPaid( int index )
   {
      return _ROAHowPaid[index];
   }
    
   /**
    * Gets the R.O.A. How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. How Paid or the specified default value.
    */
   public final String getROAHowPaid( int index, String defaultValue )
   {
      return _ROAHowPaid[index] == null ? defaultValue : _ROAHowPaid[index];
   }
    
   /**
    * Gets the array of R.O.A. How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. How Paid values.
    */
   public final String[] getROAHowPaidArray()
   {
      return _ROAHowPaid;
   }
    
   /**
    * Gets the R.O.A. How Paid Desc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. How Paid Desc or null.
    */
   public final String getROAHowPaidDesc( int index )
   {
      return _ROAHowPaidDesc[index];
   }
    
   /**
    * Gets the R.O.A. How Paid Desc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. How Paid Desc or the specified default value.
    */
   public final String getROAHowPaidDesc( int index, String defaultValue )
   {
      return _ROAHowPaidDesc[index] == null ? defaultValue : _ROAHowPaidDesc[index];
   }
    
   /**
    * Gets the array of R.O.A. How Paid Desc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. How Paid Desc values.
    */
   public final String[] getROAHowPaidDescArray()
   {
      return _ROAHowPaidDesc;
   }
    
   /**
    * Gets the R.O.A. Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. Based On or null.
    */
   public final String getROABasedOn( int index )
   {
      return _ROABasedOn[index];
   }
    
   /**
    * Gets the R.O.A. Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. Based On or the specified default value.
    */
   public final String getROABasedOn( int index, String defaultValue )
   {
      return _ROABasedOn[index] == null ? defaultValue : _ROABasedOn[index];
   }
    
   /**
    * Gets the array of R.O.A. Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. Based On values.
    */
   public final String[] getROABasedOnArray()
   {
      return _ROABasedOn;
   }
    
   /**
    * Gets the R.O.A. Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the R.O.A. Based On Description or null.
    */
   public final String getROABasedOnDesc( int index )
   {
      return _ROABasedOnDesc[index];
   }
    
   /**
    * Gets the R.O.A. Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the R.O.A. Based On Description or the specified default value.
    */
   public final String getROABasedOnDesc( int index, String defaultValue )
   {
      return _ROABasedOnDesc[index] == null ? defaultValue : _ROABasedOnDesc[index];
   }
    
   /**
    * Gets the array of R.O.A. Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of R.O.A. Based On Description values.
    */
   public final String[] getROABasedOnDescArray()
   {
      return _ROABasedOnDesc;
   }
    
   /**
    * Gets the Extra Commission Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission Fee Flag or null.
    */
   public final Boolean getXtraActive( int index )
   {
      return _XtraActive[index];
   }
    
   /**
    * Gets the Extra Commission Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission Fee Flag or the specified default value.
    */
   public final boolean getXtraActive( int index, boolean defaultValue )
   {
      return _XtraActive[index] == null ? defaultValue : _XtraActive[index].booleanValue();
   }
    
   /**
    * Gets the array of Extra Commission Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission Fee Flag values.
    */
   public final Boolean[] getXtraActiveArray()
   {
      return _XtraActive;
   }
    
   /**
    * Gets the Extra Commission Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission Rate or null.
    */
   public final String getXtraRate( int index )
   {
      return _XtraRate[index];
   }
    
   /**
    * Gets the Extra Commission Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission Rate or the specified default value.
    */
   public final String getXtraRate( int index, String defaultValue )
   {
      return _XtraRate[index] == null ? defaultValue : _XtraRate[index];
   }
    
   /**
    * Gets the array of Extra Commission Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission Rate values.
    */
   public final String[] getXtraRateArray()
   {
      return _XtraRate;
   }
    
   /**
    * Gets the Extra Commission Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission Fee Frequency or null.
    */
   public final String getXtraFreq( int index )
   {
      return _XtraFreq[index];
   }
    
   /**
    * Gets the Extra Commission Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission Fee Frequency or the specified default value.
    */
   public final String getXtraFreq( int index, String defaultValue )
   {
      return _XtraFreq[index] == null ? defaultValue : _XtraFreq[index];
   }
    
   /**
    * Gets the array of Extra Commission Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission Fee Frequency values.
    */
   public final String[] getXtraFreqArray()
   {
      return _XtraFreq;
   }
    
   /**
    * Gets the Extra Commission Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission Fee Frequency Description or null.
    */
   public final String getXtraFreqDesc( int index )
   {
      return _XtraFreqDesc[index];
   }
    
   /**
    * Gets the Extra Commission Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission Fee Frequency Description or the specified default value.
    */
   public final String getXtraFreqDesc( int index, String defaultValue )
   {
      return _XtraFreqDesc[index] == null ? defaultValue : _XtraFreqDesc[index];
   }
    
   /**
    * Gets the array of Extra Commission Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission Fee Frequency Description values.
    */
   public final String[] getXtraFreqDescArray()
   {
      return _XtraFreqDesc;
   }
    
   /**
    * Gets the Extra Commission Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission Fee Type or null.
    */
   public final String getXtraFeeType( int index )
   {
      return _XtraFeeType[index];
   }
    
   /**
    * Gets the Extra Commission Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission Fee Type or the specified default value.
    */
   public final String getXtraFeeType( int index, String defaultValue )
   {
      return _XtraFeeType[index] == null ? defaultValue : _XtraFeeType[index];
   }
    
   /**
    * Gets the array of Extra Commission Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission Fee Type values.
    */
   public final String[] getXtraFeeTypeArray()
   {
      return _XtraFeeType;
   }
    
   /**
    * Gets the Extra Commission Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission Fee Type Description or null.
    */
   public final String getXtraFeeTypeDesc( int index )
   {
      return _XtraFeeTypeDesc[index];
   }
    
   /**
    * Gets the Extra Commission Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission Fee Type Description or the specified default value.
    */
   public final String getXtraFeeTypeDesc( int index, String defaultValue )
   {
      return _XtraFeeTypeDesc[index] == null ? defaultValue : _XtraFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of Extra Commission Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission Fee Type Description values.
    */
   public final String[] getXtraFeeTypeDescArray()
   {
      return _XtraFeeTypeDesc;
   }
    
   /**
    * Gets the Extra Commission How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission How Paid or null.
    */
   public final String getXtraHowPaid( int index )
   {
      return _XtraHowPaid[index];
   }
    
   /**
    * Gets the Extra Commission How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission How Paid or the specified default value.
    */
   public final String getXtraHowPaid( int index, String defaultValue )
   {
      return _XtraHowPaid[index] == null ? defaultValue : _XtraHowPaid[index];
   }
    
   /**
    * Gets the array of Extra Commission How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission How Paid values.
    */
   public final String[] getXtraHowPaidArray()
   {
      return _XtraHowPaid;
   }
    
   /**
    * Gets the Extra Commission How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission How Paid Description or null.
    */
   public final String getXtraHowPaidDesc( int index )
   {
      return _XtraHowPaidDesc[index];
   }
    
   /**
    * Gets the Extra Commission How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission How Paid Description or the specified default value.
    */
   public final String getXtraHowPaidDesc( int index, String defaultValue )
   {
      return _XtraHowPaidDesc[index] == null ? defaultValue : _XtraHowPaidDesc[index];
   }
    
   /**
    * Gets the array of Extra Commission How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission How Paid Description values.
    */
   public final String[] getXtraHowPaidDescArray()
   {
      return _XtraHowPaidDesc;
   }
    
   /**
    * Gets the Extra Commission Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission Based On or null.
    */
   public final String getXtraBasedOn( int index )
   {
      return _XtraBasedOn[index];
   }
    
   /**
    * Gets the Extra Commission Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission Based On or the specified default value.
    */
   public final String getXtraBasedOn( int index, String defaultValue )
   {
      return _XtraBasedOn[index] == null ? defaultValue : _XtraBasedOn[index];
   }
    
   /**
    * Gets the array of Extra Commission Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission Based On values.
    */
   public final String[] getXtraBasedOnArray()
   {
      return _XtraBasedOn;
   }
    
   /**
    * Gets the Extra Commission Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Extra Commission Based On Description or null.
    */
   public final String getXtraBasedOnDesc( int index )
   {
      return _XtraBasedOnDesc[index];
   }
    
   /**
    * Gets the Extra Commission Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Extra Commission Based On Description or the specified default value.
    */
   public final String getXtraBasedOnDesc( int index, String defaultValue )
   {
      return _XtraBasedOnDesc[index] == null ? defaultValue : _XtraBasedOnDesc[index];
   }
    
   /**
    * Gets the array of Extra Commission Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Extra Commission Based On Description values.
    */
   public final String[] getXtraBasedOnDescArray()
   {
      return _XtraBasedOnDesc;
   }
    
   /**
    * Gets the Dist & Maintenance Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance Fee Flag or null.
    */
   public final Boolean getDistActive( int index )
   {
      return _DistActive[index];
   }
    
   /**
    * Gets the Dist & Maintenance Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance Fee Flag or the specified default value.
    */
   public final boolean getDistActive( int index, boolean defaultValue )
   {
      return _DistActive[index] == null ? defaultValue : _DistActive[index].booleanValue();
   }
    
   /**
    * Gets the array of Dist & Maintenance Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance Fee Flag values.
    */
   public final Boolean[] getDistActiveArray()
   {
      return _DistActive;
   }
    
   /**
    * Gets the Dist & Maintenance Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance Rate or null.
    */
   public final String getDistRate( int index )
   {
      return _DistRate[index];
   }
    
   /**
    * Gets the Dist & Maintenance Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance Rate or the specified default value.
    */
   public final String getDistRate( int index, String defaultValue )
   {
      return _DistRate[index] == null ? defaultValue : _DistRate[index];
   }
    
   /**
    * Gets the array of Dist & Maintenance Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance Rate values.
    */
   public final String[] getDistRateArray()
   {
      return _DistRate;
   }
    
   /**
    * Gets the Dist & Maintenance Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance Fee Frequency or null.
    */
   public final String getDistFreq( int index )
   {
      return _DistFreq[index];
   }
    
   /**
    * Gets the Dist & Maintenance Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance Fee Frequency or the specified default value.
    */
   public final String getDistFreq( int index, String defaultValue )
   {
      return _DistFreq[index] == null ? defaultValue : _DistFreq[index];
   }
    
   /**
    * Gets the array of Dist & Maintenance Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance Fee Frequency values.
    */
   public final String[] getDistFreqArray()
   {
      return _DistFreq;
   }
    
   /**
    * Gets the Dist & Maintenance Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance Fee Frequency Description or null.
    */
   public final String getDistFreqDesc( int index )
   {
      return _DistFreqDesc[index];
   }
    
   /**
    * Gets the Dist & Maintenance Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance Fee Frequency Description or the specified default value.
    */
   public final String getDistFreqDesc( int index, String defaultValue )
   {
      return _DistFreqDesc[index] == null ? defaultValue : _DistFreqDesc[index];
   }
    
   /**
    * Gets the array of Dist & Maintenance Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance Fee Frequency Description values.
    */
   public final String[] getDistFreqDescArray()
   {
      return _DistFreqDesc;
   }
    
   /**
    * Gets the Dist & Maintenance Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance Fee Type or null.
    */
   public final String getDistFeeType( int index )
   {
      return _DistFeeType[index];
   }
    
   /**
    * Gets the Dist & Maintenance Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance Fee Type or the specified default value.
    */
   public final String getDistFeeType( int index, String defaultValue )
   {
      return _DistFeeType[index] == null ? defaultValue : _DistFeeType[index];
   }
    
   /**
    * Gets the array of Dist & Maintenance Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance Fee Type values.
    */
   public final String[] getDistFeeTypeArray()
   {
      return _DistFeeType;
   }
    
   /**
    * Gets the Dist & Maintenance Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance Fee Type Description or null.
    */
   public final String getDistFeeTypeDesc( int index )
   {
      return _DistFeeTypeDesc[index];
   }
    
   /**
    * Gets the Dist & Maintenance Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance Fee Type Description or the specified default value.
    */
   public final String getDistFeeTypeDesc( int index, String defaultValue )
   {
      return _DistFeeTypeDesc[index] == null ? defaultValue : _DistFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of Dist & Maintenance Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance Fee Type Description values.
    */
   public final String[] getDistFeeTypeDescArray()
   {
      return _DistFeeTypeDesc;
   }
    
   /**
    * Gets the Dist & Maintenance How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance How Paid or null.
    */
   public final String getDistHowPaid( int index )
   {
      return _DistHowPaid[index];
   }
    
   /**
    * Gets the Dist & Maintenance How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance How Paid or the specified default value.
    */
   public final String getDistHowPaid( int index, String defaultValue )
   {
      return _DistHowPaid[index] == null ? defaultValue : _DistHowPaid[index];
   }
    
   /**
    * Gets the array of Dist & Maintenance How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance How Paid values.
    */
   public final String[] getDistHowPaidArray()
   {
      return _DistHowPaid;
   }
    
   /**
    * Gets the Dist & Maintenance How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance How Paid Description or null.
    */
   public final String getDistHowPaidDesc( int index )
   {
      return _DistHowPaidDesc[index];
   }
    
   /**
    * Gets the Dist & Maintenance How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance How Paid Description or the specified default value.
    */
   public final String getDistHowPaidDesc( int index, String defaultValue )
   {
      return _DistHowPaidDesc[index] == null ? defaultValue : _DistHowPaidDesc[index];
   }
    
   /**
    * Gets the array of Dist & Maintenance How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance How Paid Description values.
    */
   public final String[] getDistHowPaidDescArray()
   {
      return _DistHowPaidDesc;
   }
    
   /**
    * Gets the Dist & Maintenance Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance Based On Description or null.
    */
   public final String getDistBasedOn( int index )
   {
      return _DistBasedOn[index];
   }
    
   /**
    * Gets the Dist & Maintenance Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance Based On Description or the specified default value.
    */
   public final String getDistBasedOn( int index, String defaultValue )
   {
      return _DistBasedOn[index] == null ? defaultValue : _DistBasedOn[index];
   }
    
   /**
    * Gets the array of Dist & Maintenance Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance Based On Description values.
    */
   public final String[] getDistBasedOnArray()
   {
      return _DistBasedOn;
   }
    
   /**
    * Gets the Dist & Maintenance Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Dist & Maintenance Based On Description or null.
    */
   public final String getDistBasedOnDesc( int index )
   {
      return _DistBasedOnDesc[index];
   }
    
   /**
    * Gets the Dist & Maintenance Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Dist & Maintenance Based On Description or the specified default value.
    */
   public final String getDistBasedOnDesc( int index, String defaultValue )
   {
      return _DistBasedOnDesc[index] == null ? defaultValue : _DistBasedOnDesc[index];
   }
    
   /**
    * Gets the array of Dist & Maintenance Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Dist & Maintenance Based On Description values.
    */
   public final String[] getDistBasedOnDescArray()
   {
      return _DistBasedOnDesc;
   }
    
   /**
    * Gets the Max Fee Flag field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee Flag or null.
    */
   public final Boolean getMaxActive( int index )
   {
      return _MaxActive[index];
   }
    
   /**
    * Gets the Max Fee Flag field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee Flag or the specified default value.
    */
   public final boolean getMaxActive( int index, boolean defaultValue )
   {
      return _MaxActive[index] == null ? defaultValue : _MaxActive[index].booleanValue();
   }
    
   /**
    * Gets the array of Max Fee Flag fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee Flag values.
    */
   public final Boolean[] getMaxActiveArray()
   {
      return _MaxActive;
   }
    
   /**
    * Gets the Max Fee Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee Rate or null.
    */
   public final String getMaxRate( int index )
   {
      return _MaxRate[index];
   }
    
   /**
    * Gets the Max Fee Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee Rate or the specified default value.
    */
   public final String getMaxRate( int index, String defaultValue )
   {
      return _MaxRate[index] == null ? defaultValue : _MaxRate[index];
   }
    
   /**
    * Gets the array of Max Fee Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee Rate values.
    */
   public final String[] getMaxRateArray()
   {
      return _MaxRate;
   }
    
   /**
    * Gets the Max Fee Frequency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee Frequency or null.
    */
   public final String getMaxFreq( int index )
   {
      return _MaxFreq[index];
   }
    
   /**
    * Gets the Max Fee Frequency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee Frequency or the specified default value.
    */
   public final String getMaxFreq( int index, String defaultValue )
   {
      return _MaxFreq[index] == null ? defaultValue : _MaxFreq[index];
   }
    
   /**
    * Gets the array of Max Fee Frequency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee Frequency values.
    */
   public final String[] getMaxFreqArray()
   {
      return _MaxFreq;
   }
    
   /**
    * Gets the Max Fee Frequency Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee Frequency Description or null.
    */
   public final String getMaxFreqDesc( int index )
   {
      return _MaxFreqDesc[index];
   }
    
   /**
    * Gets the Max Fee Frequency Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee Frequency Description or the specified default value.
    */
   public final String getMaxFreqDesc( int index, String defaultValue )
   {
      return _MaxFreqDesc[index] == null ? defaultValue : _MaxFreqDesc[index];
   }
    
   /**
    * Gets the array of Max Fee Frequency Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee Frequency Description values.
    */
   public final String[] getMaxFreqDescArray()
   {
      return _MaxFreqDesc;
   }
    
   /**
    * Gets the Max Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee Type or null.
    */
   public final String getMaxFeeType( int index )
   {
      return _MaxFeeType[index];
   }
    
   /**
    * Gets the Max Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee Type or the specified default value.
    */
   public final String getMaxFeeType( int index, String defaultValue )
   {
      return _MaxFeeType[index] == null ? defaultValue : _MaxFeeType[index];
   }
    
   /**
    * Gets the array of Max Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee Type values.
    */
   public final String[] getMaxFeeTypeArray()
   {
      return _MaxFeeType;
   }
    
   /**
    * Gets the Max Fee Type Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee Type Description or null.
    */
   public final String getMaxFeeTypeDesc( int index )
   {
      return _MaxFeeTypeDesc[index];
   }
    
   /**
    * Gets the Max Fee Type Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee Type Description or the specified default value.
    */
   public final String getMaxFeeTypeDesc( int index, String defaultValue )
   {
      return _MaxFeeTypeDesc[index] == null ? defaultValue : _MaxFeeTypeDesc[index];
   }
    
   /**
    * Gets the array of Max Fee Type Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee Type Description values.
    */
   public final String[] getMaxFeeTypeDescArray()
   {
      return _MaxFeeTypeDesc;
   }
    
   /**
    * Gets the Max Fee How Paid field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee How Paid or null.
    */
   public final String getMaxHowPaid( int index )
   {
      return _MaxHowPaid[index];
   }
    
   /**
    * Gets the Max Fee How Paid field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee How Paid or the specified default value.
    */
   public final String getMaxHowPaid( int index, String defaultValue )
   {
      return _MaxHowPaid[index] == null ? defaultValue : _MaxHowPaid[index];
   }
    
   /**
    * Gets the array of Max Fee How Paid fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee How Paid values.
    */
   public final String[] getMaxHowPaidArray()
   {
      return _MaxHowPaid;
   }
    
   /**
    * Gets the Max Fee How Paid Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee How Paid Description or null.
    */
   public final String getMaxHowPaidDesc( int index )
   {
      return _MaxHowPaidDesc[index];
   }
    
   /**
    * Gets the Max Fee How Paid Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee How Paid Description or the specified default value.
    */
   public final String getMaxHowPaidDesc( int index, String defaultValue )
   {
      return _MaxHowPaidDesc[index] == null ? defaultValue : _MaxHowPaidDesc[index];
   }
    
   /**
    * Gets the array of Max Fee How Paid Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee How Paid Description values.
    */
   public final String[] getMaxHowPaidDescArray()
   {
      return _MaxHowPaidDesc;
   }
    
   /**
    * Gets the Max Fee Based On field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee Based On or null.
    */
   public final String getMaxBasedOn( int index )
   {
      return _MaxBasedOn[index];
   }
    
   /**
    * Gets the Max Fee Based On field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee Based On or the specified default value.
    */
   public final String getMaxBasedOn( int index, String defaultValue )
   {
      return _MaxBasedOn[index] == null ? defaultValue : _MaxBasedOn[index];
   }
    
   /**
    * Gets the array of Max Fee Based On fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee Based On values.
    */
   public final String[] getMaxBasedOnArray()
   {
      return _MaxBasedOn;
   }
    
   /**
    * Gets the Max Fee Based On Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Max Fee Based On Description or null.
    */
   public final String getMaxBasedOnDesc( int index )
   {
      return _MaxBasedOnDesc[index];
   }
    
   /**
    * Gets the Max Fee Based On Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Max Fee Based On Description or the specified default value.
    */
   public final String getMaxBasedOnDesc( int index, String defaultValue )
   {
      return _MaxBasedOnDesc[index] == null ? defaultValue : _MaxBasedOnDesc[index];
   }
    
   /**
    * Gets the array of Max Fee Based On Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Max Fee Based On Description values.
    */
   public final String[] getMaxBasedOnDescArray()
   {
      return _MaxBasedOnDesc;
   }
    
   /**
    * Gets the FIFO Management fees for BackEnd loading Funds field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FIFO Management fees for BackEnd loading Funds or null.
    */
   public final Boolean getFIFOMFFee( int index )
   {
      return _FIFOMFFee[index];
   }
    
   /**
    * Gets the FIFO Management fees for BackEnd loading Funds field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FIFO Management fees for BackEnd loading Funds or the specified default value.
    */
   public final boolean getFIFOMFFee( int index, boolean defaultValue )
   {
      return _FIFOMFFee[index] == null ? defaultValue : _FIFOMFFee[index].booleanValue();
   }
    
   /**
    * Gets the array of FIFO Management fees for BackEnd loading Funds fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FIFO Management fees for BackEnd loading Funds values.
    */
   public final Boolean[] getFIFOMFFeeArray()
   {
      return _FIFOMFFee;
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getrxFundCode( int index )
   {
      return _rxFundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getrxFundCode( int index, String defaultValue )
   {
      return _rxFundCode[index] == null ? defaultValue : _rxFundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getrxFundCodeArray()
   {
      return _rxFundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getrxClassCode( int index )
   {
      return _rxClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getrxClassCode( int index, String defaultValue )
   {
      return _rxClassCode[index] == null ? defaultValue : _rxClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getrxClassCodeArray()
   {
      return _rxClassCode;
   }
    
   /**
    * Gets the Redemption Fee Default Rate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Fee Default Rate or null.
    */
   public final String getRedemFee( int index )
   {
      return _RedemFee[index];
   }
    
   /**
    * Gets the Redemption Fee Default Rate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Fee Default Rate or the specified default value.
    */
   public final String getRedemFee( int index, String defaultValue )
   {
      return _RedemFee[index] == null ? defaultValue : _RedemFee[index];
   }
    
   /**
    * Gets the array of Redemption Fee Default Rate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Fee Default Rate values.
    */
   public final String[] getRedemFeeArray()
   {
      return _RedemFee;
   }
    
   /**
    * Gets the Redemption Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Fee Type or null.
    */
   public final String getRedemFeeType( int index )
   {
      return _RedemFeeType[index];
   }
    
   /**
    * Gets the Redemption Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Fee Type or the specified default value.
    */
   public final String getRedemFeeType( int index, String defaultValue )
   {
      return _RedemFeeType[index] == null ? defaultValue : _RedemFeeType[index];
   }
    
   /**
    * Gets the array of Redemption Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Fee Type values.
    */
   public final String[] getRedemFeeTypeArray()
   {
      return _RedemFeeType;
   }
    
   /**
    * Gets the Redemption Fee Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Redemption Fee Currency or null.
    */
   public final String getRedemFeeCurrency( int index )
   {
      return _RedemFeeCurrency[index];
   }
    
   /**
    * Gets the Redemption Fee Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Redemption Fee Currency or the specified default value.
    */
   public final String getRedemFeeCurrency( int index, String defaultValue )
   {
      return _RedemFeeCurrency[index] == null ? defaultValue : _RedemFeeCurrency[index];
   }
    
   /**
    * Gets the array of Redemption Fee Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Redemption Fee Currency values.
    */
   public final String[] getRedemFeeCurrencyArray()
   {
      return _RedemFeeCurrency;
   }
    
   /**
    * Gets the Fee on In side of Exchange Default field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee on In side of Exchange Default or null.
    */
   public final String getExchInFeeDefault( int index )
   {
      return _ExchInFeeDefault[index];
   }
    
   /**
    * Gets the Fee on In side of Exchange Default field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee on In side of Exchange Default or the specified default value.
    */
   public final String getExchInFeeDefault( int index, String defaultValue )
   {
      return _ExchInFeeDefault[index] == null ? defaultValue : _ExchInFeeDefault[index];
   }
    
   /**
    * Gets the array of Fee on In side of Exchange Default fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee on In side of Exchange Default values.
    */
   public final String[] getExchInFeeDefaultArray()
   {
      return _ExchInFeeDefault;
   }
    
   /**
    * Gets the Fee on In side of Exchange Default Fee Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee on In side of Exchange Default Fee Type or null.
    */
   public final String getExchInFeeDefType( int index )
   {
      return _ExchInFeeDefType[index];
   }
    
   /**
    * Gets the Fee on In side of Exchange Default Fee Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee on In side of Exchange Default Fee Type or the specified default value.
    */
   public final String getExchInFeeDefType( int index, String defaultValue )
   {
      return _ExchInFeeDefType[index] == null ? defaultValue : _ExchInFeeDefType[index];
   }
    
   /**
    * Gets the array of Fee on In side of Exchange Default Fee Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee on In side of Exchange Default Fee Type values.
    */
   public final String[] getExchInFeeDefTypeArray()
   {
      return _ExchInFeeDefType;
   }
    
   /**
    * Gets the Fee on In side of Exchange Maximum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee on In side of Exchange Maximum or null.
    */
   public final String getExchInFeeMax( int index )
   {
      return _ExchInFeeMax[index];
   }
    
   /**
    * Gets the Fee on In side of Exchange Maximum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee on In side of Exchange Maximum or the specified default value.
    */
   public final String getExchInFeeMax( int index, String defaultValue )
   {
      return _ExchInFeeMax[index] == null ? defaultValue : _ExchInFeeMax[index];
   }
    
   /**
    * Gets the array of Fee on In side of Exchange Maximum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee on In side of Exchange Maximum values.
    */
   public final String[] getExchInFeeMaxArray()
   {
      return _ExchInFeeMax;
   }
    
   /**
    * Gets the Fee on In side of Exchange Minimum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fee on In side of Exchange Minimum or null.
    */
   public final String getExchInFeeMin( int index )
   {
      return _ExchInFeeMin[index];
   }
    
   /**
    * Gets the Fee on In side of Exchange Minimum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fee on In side of Exchange Minimum or the specified default value.
    */
   public final String getExchInFeeMin( int index, String defaultValue )
   {
      return _ExchInFeeMin[index] == null ? defaultValue : _ExchInFeeMin[index];
   }
    
   /**
    * Gets the array of Fee on In side of Exchange Minimum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fee on In side of Exchange Minimum values.
    */
   public final String[] getExchInFeeMinArray()
   {
      return _ExchInFeeMin;
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
      _ClientLvlTfr = responseBuffer.decodeString(responseBuffer.getNextField());
      _ClientLvlExch = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _AcqActive = resizeArray( _AcqActive, _RepeatCount );
      _AcqRate = resizeArray( _AcqRate, _RepeatCount );
      _AcqFreq = resizeArray( _AcqFreq, _RepeatCount );
      _AcqFreqDesc = resizeArray( _AcqFreqDesc, _RepeatCount );
      _AcqFeeType = resizeArray( _AcqFeeType, _RepeatCount );
      _AcqFeeTypeDesc = resizeArray( _AcqFeeTypeDesc, _RepeatCount );
      _AcqHowPaid = resizeArray( _AcqHowPaid, _RepeatCount );
      _AcqHowPaidDesc = resizeArray( _AcqHowPaidDesc, _RepeatCount );
      _AcqBasedOn = resizeArray( _AcqBasedOn, _RepeatCount );
      _AcqBasedOnDesc = resizeArray( _AcqBasedOnDesc, _RepeatCount );
      _WHoldActive = resizeArray( _WHoldActive, _RepeatCount );
      _WHoldRate = resizeArray( _WHoldRate, _RepeatCount );
      _WHoldFreq = resizeArray( _WHoldFreq, _RepeatCount );
      _WHoldFreqDesc = resizeArray( _WHoldFreqDesc, _RepeatCount );
      _WHoldFeeType = resizeArray( _WHoldFeeType, _RepeatCount );
      _WHoldFeeTypeDesc = resizeArray( _WHoldFeeTypeDesc, _RepeatCount );
      _WHoldHowPaid = resizeArray( _WHoldHowPaid, _RepeatCount );
      _WHoldHowPaidDesc = resizeArray( _WHoldHowPaidDesc, _RepeatCount );
      _WHoldBasedIOn = resizeArray( _WHoldBasedIOn, _RepeatCount );
      _WHoldBasedOnDesc = resizeArray( _WHoldBasedOnDesc, _RepeatCount );
      _BELActive = resizeArray( _BELActive, _RepeatCount );
      _BELRate = resizeArray( _BELRate, _RepeatCount );
      _BELFreq = resizeArray( _BELFreq, _RepeatCount );
      _BELFreqDesc = resizeArray( _BELFreqDesc, _RepeatCount );
      _BELFeeType = resizeArray( _BELFeeType, _RepeatCount );
      _BELFeeTypeDesc = resizeArray( _BELFeeTypeDesc, _RepeatCount );
      _BELHowPaid = resizeArray( _BELHowPaid, _RepeatCount );
      _BELHowPaidDesc = resizeArray( _BELHowPaidDesc, _RepeatCount );
      _BELBasedOn = resizeArray( _BELBasedOn, _RepeatCount );
      _BELBasedOnDesc = resizeArray( _BELBasedOnDesc, _RepeatCount );
      _TfrActive = resizeArray( _TfrActive, _RepeatCount );
      _TfrRate = resizeArray( _TfrRate, _RepeatCount );
      _TfrFreq = resizeArray( _TfrFreq, _RepeatCount );
      _TfrFreqDesc = resizeArray( _TfrFreqDesc, _RepeatCount );
      _TfrFeeType = resizeArray( _TfrFeeType, _RepeatCount );
      _TfrFeeTypeDesc = resizeArray( _TfrFeeTypeDesc, _RepeatCount );
      _TfrHowPaid = resizeArray( _TfrHowPaid, _RepeatCount );
      _TfrHowPaidDesc = resizeArray( _TfrHowPaidDesc, _RepeatCount );
      _TfrBasedOn = resizeArray( _TfrBasedOn, _RepeatCount );
      _TfrBasedOnDesc = resizeArray( _TfrBasedOnDesc, _RepeatCount );
      _RRSPActive = resizeArray( _RRSPActive, _RepeatCount );
      _RRSPRate = resizeArray( _RRSPRate, _RepeatCount );
      _RRSPFreq = resizeArray( _RRSPFreq, _RepeatCount );
      _RRSPFreqDesc = resizeArray( _RRSPFreqDesc, _RepeatCount );
      _RRSPFeeType = resizeArray( _RRSPFeeType, _RepeatCount );
      _RRSPFeeTypeDesc = resizeArray( _RRSPFeeTypeDesc, _RepeatCount );
      _RRSPHowPaid = resizeArray( _RRSPHowPaid, _RepeatCount );
      _RRSPHowPaidDesc = resizeArray( _RRSPHowPaidDesc, _RepeatCount );
      _RRSPBasedOn = resizeArray( _RRSPBasedOn, _RepeatCount );
      _RRSPBasedOnDesc = resizeArray( _RRSPBasedOnDesc, _RepeatCount );
      _RRIFActive = resizeArray( _RRIFActive, _RepeatCount );
      _RRIFRate = resizeArray( _RRIFRate, _RepeatCount );
      _RRIFFreq = resizeArray( _RRIFFreq, _RepeatCount );
      _RRIFFreqDesc = resizeArray( _RRIFFreqDesc, _RepeatCount );
      _RRIFFeeType = resizeArray( _RRIFFeeType, _RepeatCount );
      _RRIFFeeTypeDesc = resizeArray( _RRIFFeeTypeDesc, _RepeatCount );
      _RRIFHowPaid = resizeArray( _RRIFHowPaid, _RepeatCount );
      _RRIFHowPaidDesc = resizeArray( _RRIFHowPaidDesc, _RepeatCount );
      _RRIFBasedOn = resizeArray( _RRIFBasedOn, _RepeatCount );
      _RRIFBasedOnDesc = resizeArray( _RRIFBasedOnDesc, _RepeatCount );
      _IncvActive = resizeArray( _IncvActive, _RepeatCount );
      _IncvRate = resizeArray( _IncvRate, _RepeatCount );
      _IncvFreq = resizeArray( _IncvFreq, _RepeatCount );
      _IncvFreqDesc = resizeArray( _IncvFreqDesc, _RepeatCount );
      _IncvFeeType = resizeArray( _IncvFeeType, _RepeatCount );
      _IncvFeeTypeDesc = resizeArray( _IncvFeeTypeDesc, _RepeatCount );
      _IncvHowPaid = resizeArray( _IncvHowPaid, _RepeatCount );
      _IncvHowPaidDesc = resizeArray( _IncvHowPaidDesc, _RepeatCount );
      _IncvBasedOn = resizeArray( _IncvBasedOn, _RepeatCount );
      _IncvBasedOnDesc = resizeArray( _IncvBasedOnDesc, _RepeatCount );
      _TrlActive = resizeArray( _TrlActive, _RepeatCount );
      _TrlRate = resizeArray( _TrlRate, _RepeatCount );
      _TrlFreq = resizeArray( _TrlFreq, _RepeatCount );
      _TrlFreqDesc = resizeArray( _TrlFreqDesc, _RepeatCount );
      _TrlFeeType = resizeArray( _TrlFeeType, _RepeatCount );
      _TrlFeeTypeDesc = resizeArray( _TrlFeeTypeDesc, _RepeatCount );
      _TrlHowPaid = resizeArray( _TrlHowPaid, _RepeatCount );
      _TrlHowPaidDesc = resizeArray( _TrlHowPaidDesc, _RepeatCount );
      _TrlBasedOn = resizeArray( _TrlBasedOn, _RepeatCount );
      _TrlBasedOnDesc = resizeArray( _TrlBasedOnDesc, _RepeatCount );
      _ROAActive = resizeArray( _ROAActive, _RepeatCount );
      _ROARate = resizeArray( _ROARate, _RepeatCount );
      _ROAFreq = resizeArray( _ROAFreq, _RepeatCount );
      _ROAFreqDesc = resizeArray( _ROAFreqDesc, _RepeatCount );
      _ROAFeeType = resizeArray( _ROAFeeType, _RepeatCount );
      _ROAFeeTypeDesc = resizeArray( _ROAFeeTypeDesc, _RepeatCount );
      _ROAHowPaid = resizeArray( _ROAHowPaid, _RepeatCount );
      _ROAHowPaidDesc = resizeArray( _ROAHowPaidDesc, _RepeatCount );
      _ROABasedOn = resizeArray( _ROABasedOn, _RepeatCount );
      _ROABasedOnDesc = resizeArray( _ROABasedOnDesc, _RepeatCount );
      _XtraActive = resizeArray( _XtraActive, _RepeatCount );
      _XtraRate = resizeArray( _XtraRate, _RepeatCount );
      _XtraFreq = resizeArray( _XtraFreq, _RepeatCount );
      _XtraFreqDesc = resizeArray( _XtraFreqDesc, _RepeatCount );
      _XtraFeeType = resizeArray( _XtraFeeType, _RepeatCount );
      _XtraFeeTypeDesc = resizeArray( _XtraFeeTypeDesc, _RepeatCount );
      _XtraHowPaid = resizeArray( _XtraHowPaid, _RepeatCount );
      _XtraHowPaidDesc = resizeArray( _XtraHowPaidDesc, _RepeatCount );
      _XtraBasedOn = resizeArray( _XtraBasedOn, _RepeatCount );
      _XtraBasedOnDesc = resizeArray( _XtraBasedOnDesc, _RepeatCount );
      _DistActive = resizeArray( _DistActive, _RepeatCount );
      _DistRate = resizeArray( _DistRate, _RepeatCount );
      _DistFreq = resizeArray( _DistFreq, _RepeatCount );
      _DistFreqDesc = resizeArray( _DistFreqDesc, _RepeatCount );
      _DistFeeType = resizeArray( _DistFeeType, _RepeatCount );
      _DistFeeTypeDesc = resizeArray( _DistFeeTypeDesc, _RepeatCount );
      _DistHowPaid = resizeArray( _DistHowPaid, _RepeatCount );
      _DistHowPaidDesc = resizeArray( _DistHowPaidDesc, _RepeatCount );
      _DistBasedOn = resizeArray( _DistBasedOn, _RepeatCount );
      _DistBasedOnDesc = resizeArray( _DistBasedOnDesc, _RepeatCount );
      _MaxActive = resizeArray( _MaxActive, _RepeatCount );
      _MaxRate = resizeArray( _MaxRate, _RepeatCount );
      _MaxFreq = resizeArray( _MaxFreq, _RepeatCount );
      _MaxFreqDesc = resizeArray( _MaxFreqDesc, _RepeatCount );
      _MaxFeeType = resizeArray( _MaxFeeType, _RepeatCount );
      _MaxFeeTypeDesc = resizeArray( _MaxFeeTypeDesc, _RepeatCount );
      _MaxHowPaid = resizeArray( _MaxHowPaid, _RepeatCount );
      _MaxHowPaidDesc = resizeArray( _MaxHowPaidDesc, _RepeatCount );
      _MaxBasedOn = resizeArray( _MaxBasedOn, _RepeatCount );
      _MaxBasedOnDesc = resizeArray( _MaxBasedOnDesc, _RepeatCount );
      _FIFOMFFee = resizeArray( _FIFOMFFee, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _RedemFee = resizeArray( _RedemFee, _RepeatCount );
      _RedemFeeType = resizeArray( _RedemFeeType, _RepeatCount );
      _RedemFeeCurrency = resizeArray( _RedemFeeCurrency, _RepeatCount );
      _ExchInFeeDefault = resizeArray( _ExchInFeeDefault, _RepeatCount );
      _ExchInFeeDefType = resizeArray( _ExchInFeeDefType, _RepeatCount );
      _ExchInFeeMax = resizeArray( _ExchInFeeMax, _RepeatCount );
      _ExchInFeeMin = resizeArray( _ExchInFeeMin, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _AcqActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _AcqRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcqBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WHoldActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _WHoldRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WHoldFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WHoldFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WHoldFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WHoldFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WHoldHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WHoldHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WHoldBasedIOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WHoldBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _BELRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BELBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TfrRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TfrBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RRSPRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRSPBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _RRIFRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RRIFBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncvActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _IncvRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncvFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncvFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncvFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncvFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncvHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncvHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncvBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IncvBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrlActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _TrlRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrlFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrlFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrlFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrlFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrlHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrlHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrlBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TrlBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROAActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ROARate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROAFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROAFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROAFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROAFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROAHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROAHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROABasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ROABasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XtraActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _XtraRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XtraFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XtraFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XtraFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XtraFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XtraHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XtraHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XtraBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XtraBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _DistRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxActive[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _MaxRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxFreqDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxFeeTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxHowPaid[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxHowPaidDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxBasedOn[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _MaxBasedOnDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FIFOMFFee[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedemFee[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedemFeeType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RedemFeeCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchInFeeDefault[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchInFeeDefType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchInFeeMax[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExchInFeeMin[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
