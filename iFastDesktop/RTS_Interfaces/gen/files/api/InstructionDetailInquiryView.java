
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * MAT/INT/CSW Instruction Detail Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/InstructionDetailInquiry.doc">InstructionDetailInquiry.doc</A>.
 * 
 * @author RTS Generated
 */
public class InstructionDetailInquiryView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * DistribDetlUUID member array.
    */
   private String[] _DistribDetlUUID = null;
   
   /**
    * IntInvestId member array.
    */
   private String[] _IntInvestId = null;
   
   /**
    * RollOverType member array.
    */
   private String[] _RollOverType = null;
   
   /**
    * AccountTo member array.
    */
   private String[] _AccountTo = null;
   
   /**
    * FundTo member array.
    */
   private String[] _FundTo = null;
   
   /**
    * ClassTo member array.
    */
   private String[] _ClassTo = null;
   
   /**
    * Remaining member array.
    */
   private String[] _Remaining = null;
   
   /**
    * Currency member array.
    */
   private String[] _Currency = null;
   
   /**
    * Percent member array.
    */
   private String[] _Percent = null;
   
   /**
    * PayType member array.
    */
   private String[] _PayType = null;
   
   /**
    * PayTypeDesc member array.
    */
   private String[] _PayTypeDesc = null;
   
   /**
    * CommReduction member array.
    */
   private String[] _CommReduction = null;
   
   /**
    * IntInvestType member array.
    */
   private String[] _IntInvestType = null;
   
   /**
    * FELAmt member array.
    */
   private String[] _FELAmt = null;
   
   /**
    * IntInvestTerm member array.
    */
   private Integer[] _IntInvestTerm = null;
   
   /**
    * IntCalcMthd member array.
    */
   private String[] _IntCalcMthd = null;
   
   /**
    * IntRateType member array.
    */
   private String[] _IntRateType = null;
   
   /**
    * ForcedRate member array.
    */
   private String[] _ForcedRate = null;
   
   /**
    * IntCredFreq member array.
    */
   private String[] _IntCredFreq = null;
   
   /**
    * SourceOfFund member array.
    */
   private String[] _SourceOfFund = null;
   
   /**
    * RefNum member array.
    */
   private String[] _RefNum = null;
   
   /**
    * AddlAmt member array.
    */
   private String[] _AddlAmt = null;
   
   /**
    * BankAcctId member array.
    */
   private String[] _BankAcctId = null;
   
   /**
    * BankAcctUse member array.
    */
   private String[] _BankAcctUse = null;
   
   /**
    * BankIdType member array.
    */
   private String[] _BankIdType = null;
   
   /**
    * BankIdValue member array.
    */
   private Integer[] _BankIdValue = null;
   
   /**
    * BankTransitNo member array.
    */
   private Integer[] _BankTransitNo = null;
   
   /**
    * BankSwiftCode member array.
    */
   private Integer[] _BankSwiftCode = null;
   
   /**
    * BankRefNumber member array.
    */
   private Integer[] _BankRefNumber = null;
   
   /**
    * BankInstName member array.
    */
   private String[] _BankInstName = null;
   
   /**
    * BankAddr1 member array.
    */
   private String[] _BankAddr1 = null;
   
   /**
    * BankAddr2 member array.
    */
   private String[] _BankAddr2 = null;
   
   /**
    * BankAddr3 member array.
    */
   private String[] _BankAddr3 = null;
   
   /**
    * BankAddr4 member array.
    */
   private String[] _BankAddr4 = null;
   
   /**
    * BankAddr5 member array.
    */
   private String[] _BankAddr5 = null;
   
   /**
    * BankPostal member array.
    */
   private String[] _BankPostal = null;
   
   /**
    * BankCountry member array.
    */
   private String[] _BankCountry = null;
   
   /**
    * BankAcctType member array.
    */
   private String[] _BankAcctType = null;
   
   /**
    * BankAcctTypeDesc member array.
    */
   private String[] _BankAcctTypeDesc = null;
   
   /**
    * BankAcctCurrency member array.
    */
   private String[] _BankAcctCurrency = null;
   
   /**
    * BankCurrDesc member array.
    */
   private String[] _BankCurrDesc = null;
   
   /**
    * BankEffectiveDate member array.
    */
   private Date[] _BankEffectiveDate = null;
   
   /**
    * BankStopDate member array.
    */
   private Date[] _BankStopDate = null;
   
   /**
    * BankPayMethod member array.
    */
   private String[] _BankPayMethod = null;
   
   /**
    * BankACHProcessor member array.
    */
   private String[] _BankACHProcessor = null;
   
   /**
    * BankContact member array.
    */
   private String[] _BankContact = null;
   
   /**
    * BankCorrespondent member array.
    */
   private String[] _BankCorrespondent = null;
   
   /**
    * AddrCode member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * BankId member array.
    */
   private String[] _BankId = null;
   
   /**
    * BankAcctNum member array.
    */
   private String[] _BankAcctNum = null;
   
   /**
    * BankAcctName member array.
    */
   private String[] _BankAcctName = null;
   
   /**
    * IntInvestUUID member array.
    */
   private String[] _IntInvestUUID = null;
   
   /**
    * DistribDetlVer member array.
    */
   private Integer[] _DistribDetlVer = null;
   
   /**
    * BankAcctVer member array.
    */
   private Integer[] _BankAcctVer = null;
   
   /**
    * IntInvestVer member array.
    */
   private Integer[] _IntInvestVer = null;
   

   /**
    * Constructs the InstructionDetailInquiryView object.
    * 
    */
   public InstructionDetailInquiryView()
   {
      super ( new InstructionDetailInquiryRequest() );
   }

   /**
    * Constructs the InstructionDetailInquiryView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public InstructionDetailInquiryView( String hostEncoding )
   {
      super ( new InstructionDetailInquiryRequest( hostEncoding ) );
   }

   /**
    * Gets the InstructionDetailInquiryRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The InstructionDetailInquiryRequest object.
    */
   public final InstructionDetailInquiryRequest getRequest()
   {
      return (InstructionDetailInquiryRequest)getIFastRequest();
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
    * Gets the DistribDetlUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DistribDetlUUID or null.
    */
   public final String getDistribDetlUUID( int index )
   {
      return _DistribDetlUUID[index];
   }
    
   /**
    * Gets the DistribDetlUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DistribDetlUUID or the specified default value.
    */
   public final String getDistribDetlUUID( int index, String defaultValue )
   {
      return _DistribDetlUUID[index] == null ? defaultValue : _DistribDetlUUID[index];
   }
    
   /**
    * Gets the array of DistribDetlUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DistribDetlUUID values.
    */
   public final String[] getDistribDetlUUIDArray()
   {
      return _DistribDetlUUID;
   }
    
   /**
    * Gets the IntInvestId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestId or null.
    */
   public final String getIntInvestId( int index )
   {
      return _IntInvestId[index];
   }
    
   /**
    * Gets the IntInvestId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestId or the specified default value.
    */
   public final String getIntInvestId( int index, String defaultValue )
   {
      return _IntInvestId[index] == null ? defaultValue : _IntInvestId[index];
   }
    
   /**
    * Gets the array of IntInvestId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestId values.
    */
   public final String[] getIntInvestIdArray()
   {
      return _IntInvestId;
   }
    
   /**
    * Gets the RollOverType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RollOverType or null.
    */
   public final String getRollOverType( int index )
   {
      return _RollOverType[index];
   }
    
   /**
    * Gets the RollOverType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RollOverType or the specified default value.
    */
   public final String getRollOverType( int index, String defaultValue )
   {
      return _RollOverType[index] == null ? defaultValue : _RollOverType[index];
   }
    
   /**
    * Gets the array of RollOverType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RollOverType values.
    */
   public final String[] getRollOverTypeArray()
   {
      return _RollOverType;
   }
    
   /**
    * Gets the AccountTo field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AccountTo or null.
    */
   public final String getAccountTo( int index )
   {
      return _AccountTo[index];
   }
    
   /**
    * Gets the AccountTo field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AccountTo or the specified default value.
    */
   public final String getAccountTo( int index, String defaultValue )
   {
      return _AccountTo[index] == null ? defaultValue : _AccountTo[index];
   }
    
   /**
    * Gets the array of AccountTo fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AccountTo values.
    */
   public final String[] getAccountToArray()
   {
      return _AccountTo;
   }
    
   /**
    * Gets the FundTo field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FundTo or null.
    */
   public final String getFundTo( int index )
   {
      return _FundTo[index];
   }
    
   /**
    * Gets the FundTo field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FundTo or the specified default value.
    */
   public final String getFundTo( int index, String defaultValue )
   {
      return _FundTo[index] == null ? defaultValue : _FundTo[index];
   }
    
   /**
    * Gets the array of FundTo fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FundTo values.
    */
   public final String[] getFundToArray()
   {
      return _FundTo;
   }
    
   /**
    * Gets the ClassTo field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ClassTo or null.
    */
   public final String getClassTo( int index )
   {
      return _ClassTo[index];
   }
    
   /**
    * Gets the ClassTo field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ClassTo or the specified default value.
    */
   public final String getClassTo( int index, String defaultValue )
   {
      return _ClassTo[index] == null ? defaultValue : _ClassTo[index];
   }
    
   /**
    * Gets the array of ClassTo fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ClassTo values.
    */
   public final String[] getClassToArray()
   {
      return _ClassTo;
   }
    
   /**
    * Gets the Remaining field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remaining or null.
    */
   public final String getRemaining( int index )
   {
      return _Remaining[index];
   }
    
   /**
    * Gets the Remaining field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remaining or the specified default value.
    */
   public final String getRemaining( int index, String defaultValue )
   {
      return _Remaining[index] == null ? defaultValue : _Remaining[index];
   }
    
   /**
    * Gets the array of Remaining fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remaining values.
    */
   public final String[] getRemainingArray()
   {
      return _Remaining;
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Currency or null.
    */
   public final String getCurrency( int index )
   {
      return _Currency[index];
   }
    
   /**
    * Gets the Currency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Currency or the specified default value.
    */
   public final String getCurrency( int index, String defaultValue )
   {
      return _Currency[index] == null ? defaultValue : _Currency[index];
   }
    
   /**
    * Gets the array of Currency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Currency values.
    */
   public final String[] getCurrencyArray()
   {
      return _Currency;
   }
    
   /**
    * Gets the Percent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Percent or null.
    */
   public final String getPercent( int index )
   {
      return _Percent[index];
   }
    
   /**
    * Gets the Percent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Percent or the specified default value.
    */
   public final String getPercent( int index, String defaultValue )
   {
      return _Percent[index] == null ? defaultValue : _Percent[index];
   }
    
   /**
    * Gets the array of Percent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Percent values.
    */
   public final String[] getPercentArray()
   {
      return _Percent;
   }
    
   /**
    * Gets the PayType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PayType or null.
    */
   public final String getPayType( int index )
   {
      return _PayType[index];
   }
    
   /**
    * Gets the PayType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PayType or the specified default value.
    */
   public final String getPayType( int index, String defaultValue )
   {
      return _PayType[index] == null ? defaultValue : _PayType[index];
   }
    
   /**
    * Gets the array of PayType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PayType values.
    */
   public final String[] getPayTypeArray()
   {
      return _PayType;
   }
    
   /**
    * Gets the PayTypeDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PayTypeDesc or null.
    */
   public final String getPayTypeDesc( int index )
   {
      return _PayTypeDesc[index];
   }
    
   /**
    * Gets the PayTypeDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PayTypeDesc or the specified default value.
    */
   public final String getPayTypeDesc( int index, String defaultValue )
   {
      return _PayTypeDesc[index] == null ? defaultValue : _PayTypeDesc[index];
   }
    
   /**
    * Gets the array of PayTypeDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PayTypeDesc values.
    */
   public final String[] getPayTypeDescArray()
   {
      return _PayTypeDesc;
   }
    
   /**
    * Gets the CommReduction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CommReduction or null.
    */
   public final String getCommReduction( int index )
   {
      return _CommReduction[index];
   }
    
   /**
    * Gets the CommReduction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CommReduction or the specified default value.
    */
   public final String getCommReduction( int index, String defaultValue )
   {
      return _CommReduction[index] == null ? defaultValue : _CommReduction[index];
   }
    
   /**
    * Gets the array of CommReduction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CommReduction values.
    */
   public final String[] getCommReductionArray()
   {
      return _CommReduction;
   }
    
   /**
    * Gets the IntInvestType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestType or null.
    */
   public final String getIntInvestType( int index )
   {
      return _IntInvestType[index];
   }
    
   /**
    * Gets the IntInvestType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestType or the specified default value.
    */
   public final String getIntInvestType( int index, String defaultValue )
   {
      return _IntInvestType[index] == null ? defaultValue : _IntInvestType[index];
   }
    
   /**
    * Gets the array of IntInvestType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestType values.
    */
   public final String[] getIntInvestTypeArray()
   {
      return _IntInvestType;
   }
    
   /**
    * Gets the FELAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the FELAmt or null.
    */
   public final String getFELAmt( int index )
   {
      return _FELAmt[index];
   }
    
   /**
    * Gets the FELAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the FELAmt or the specified default value.
    */
   public final String getFELAmt( int index, String defaultValue )
   {
      return _FELAmt[index] == null ? defaultValue : _FELAmt[index];
   }
    
   /**
    * Gets the array of FELAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of FELAmt values.
    */
   public final String[] getFELAmtArray()
   {
      return _FELAmt;
   }
    
   /**
    * Gets the IntInvestTerm field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestTerm or null.
    */
   public final Integer getIntInvestTerm( int index )
   {
      return _IntInvestTerm[index];
   }
    
   /**
    * Gets the IntInvestTerm field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestTerm or the specified default value.
    */
   public final int getIntInvestTerm( int index, int defaultValue )
   {
      return _IntInvestTerm[index] == null ? defaultValue : _IntInvestTerm[index].intValue();
   }
    
   /**
    * Gets the array of IntInvestTerm fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestTerm values.
    */
   public final Integer[] getIntInvestTermArray()
   {
      return _IntInvestTerm;
   }
    
   /**
    * Gets the IntCalcMthd field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntCalcMthd or null.
    */
   public final String getIntCalcMthd( int index )
   {
      return _IntCalcMthd[index];
   }
    
   /**
    * Gets the IntCalcMthd field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntCalcMthd or the specified default value.
    */
   public final String getIntCalcMthd( int index, String defaultValue )
   {
      return _IntCalcMthd[index] == null ? defaultValue : _IntCalcMthd[index];
   }
    
   /**
    * Gets the array of IntCalcMthd fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntCalcMthd values.
    */
   public final String[] getIntCalcMthdArray()
   {
      return _IntCalcMthd;
   }
    
   /**
    * Gets the IntRateType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntRateType or null.
    */
   public final String getIntRateType( int index )
   {
      return _IntRateType[index];
   }
    
   /**
    * Gets the IntRateType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntRateType or the specified default value.
    */
   public final String getIntRateType( int index, String defaultValue )
   {
      return _IntRateType[index] == null ? defaultValue : _IntRateType[index];
   }
    
   /**
    * Gets the array of IntRateType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntRateType values.
    */
   public final String[] getIntRateTypeArray()
   {
      return _IntRateType;
   }
    
   /**
    * Gets the ForcedRate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ForcedRate or null.
    */
   public final String getForcedRate( int index )
   {
      return _ForcedRate[index];
   }
    
   /**
    * Gets the ForcedRate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ForcedRate or the specified default value.
    */
   public final String getForcedRate( int index, String defaultValue )
   {
      return _ForcedRate[index] == null ? defaultValue : _ForcedRate[index];
   }
    
   /**
    * Gets the array of ForcedRate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ForcedRate values.
    */
   public final String[] getForcedRateArray()
   {
      return _ForcedRate;
   }
    
   /**
    * Gets the IntCredFreq field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntCredFreq or null.
    */
   public final String getIntCredFreq( int index )
   {
      return _IntCredFreq[index];
   }
    
   /**
    * Gets the IntCredFreq field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntCredFreq or the specified default value.
    */
   public final String getIntCredFreq( int index, String defaultValue )
   {
      return _IntCredFreq[index] == null ? defaultValue : _IntCredFreq[index];
   }
    
   /**
    * Gets the array of IntCredFreq fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntCredFreq values.
    */
   public final String[] getIntCredFreqArray()
   {
      return _IntCredFreq;
   }
    
   /**
    * Gets the SourceOfFund field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the SourceOfFund or null.
    */
   public final String getSourceOfFund( int index )
   {
      return _SourceOfFund[index];
   }
    
   /**
    * Gets the SourceOfFund field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the SourceOfFund or the specified default value.
    */
   public final String getSourceOfFund( int index, String defaultValue )
   {
      return _SourceOfFund[index] == null ? defaultValue : _SourceOfFund[index];
   }
    
   /**
    * Gets the array of SourceOfFund fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of SourceOfFund values.
    */
   public final String[] getSourceOfFundArray()
   {
      return _SourceOfFund;
   }
    
   /**
    * Gets the RefNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the RefNum or null.
    */
   public final String getRefNum( int index )
   {
      return _RefNum[index];
   }
    
   /**
    * Gets the RefNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the RefNum or the specified default value.
    */
   public final String getRefNum( int index, String defaultValue )
   {
      return _RefNum[index] == null ? defaultValue : _RefNum[index];
   }
    
   /**
    * Gets the array of RefNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of RefNum values.
    */
   public final String[] getRefNumArray()
   {
      return _RefNum;
   }
    
   /**
    * Gets the AddlAmt field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddlAmt or null.
    */
   public final String getAddlAmt( int index )
   {
      return _AddlAmt[index];
   }
    
   /**
    * Gets the AddlAmt field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddlAmt or the specified default value.
    */
   public final String getAddlAmt( int index, String defaultValue )
   {
      return _AddlAmt[index] == null ? defaultValue : _AddlAmt[index];
   }
    
   /**
    * Gets the array of AddlAmt fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddlAmt values.
    */
   public final String[] getAddlAmtArray()
   {
      return _AddlAmt;
   }
    
   /**
    * Gets the BankAcctId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAcctId or null.
    */
   public final String getBankAcctId( int index )
   {
      return _BankAcctId[index];
   }
    
   /**
    * Gets the BankAcctId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAcctId or the specified default value.
    */
   public final String getBankAcctId( int index, String defaultValue )
   {
      return _BankAcctId[index] == null ? defaultValue : _BankAcctId[index];
   }
    
   /**
    * Gets the array of BankAcctId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAcctId values.
    */
   public final String[] getBankAcctIdArray()
   {
      return _BankAcctId;
   }
    
   /**
    * Gets the BankAcctUse field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAcctUse or null.
    */
   public final String getBankAcctUse( int index )
   {
      return _BankAcctUse[index];
   }
    
   /**
    * Gets the BankAcctUse field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAcctUse or the specified default value.
    */
   public final String getBankAcctUse( int index, String defaultValue )
   {
      return _BankAcctUse[index] == null ? defaultValue : _BankAcctUse[index];
   }
    
   /**
    * Gets the array of BankAcctUse fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAcctUse values.
    */
   public final String[] getBankAcctUseArray()
   {
      return _BankAcctUse;
   }
    
   /**
    * Gets the BankIdType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankIdType or null.
    */
   public final String getBankIdType( int index )
   {
      return _BankIdType[index];
   }
    
   /**
    * Gets the BankIdType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankIdType or the specified default value.
    */
   public final String getBankIdType( int index, String defaultValue )
   {
      return _BankIdType[index] == null ? defaultValue : _BankIdType[index];
   }
    
   /**
    * Gets the array of BankIdType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankIdType values.
    */
   public final String[] getBankIdTypeArray()
   {
      return _BankIdType;
   }
    
   /**
    * Gets the BankIdValue field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankIdValue or null.
    */
   public final Integer getBankIdValue( int index )
   {
      return _BankIdValue[index];
   }
    
   /**
    * Gets the BankIdValue field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankIdValue or the specified default value.
    */
   public final int getBankIdValue( int index, int defaultValue )
   {
      return _BankIdValue[index] == null ? defaultValue : _BankIdValue[index].intValue();
   }
    
   /**
    * Gets the array of BankIdValue fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankIdValue values.
    */
   public final Integer[] getBankIdValueArray()
   {
      return _BankIdValue;
   }
    
   /**
    * Gets the BankTransitNo field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankTransitNo or null.
    */
   public final Integer getBankTransitNo( int index )
   {
      return _BankTransitNo[index];
   }
    
   /**
    * Gets the BankTransitNo field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankTransitNo or the specified default value.
    */
   public final int getBankTransitNo( int index, int defaultValue )
   {
      return _BankTransitNo[index] == null ? defaultValue : _BankTransitNo[index].intValue();
   }
    
   /**
    * Gets the array of BankTransitNo fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankTransitNo values.
    */
   public final Integer[] getBankTransitNoArray()
   {
      return _BankTransitNo;
   }
    
   /**
    * Gets the BankSwiftCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankSwiftCode or null.
    */
   public final Integer getBankSwiftCode( int index )
   {
      return _BankSwiftCode[index];
   }
    
   /**
    * Gets the BankSwiftCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankSwiftCode or the specified default value.
    */
   public final int getBankSwiftCode( int index, int defaultValue )
   {
      return _BankSwiftCode[index] == null ? defaultValue : _BankSwiftCode[index].intValue();
   }
    
   /**
    * Gets the array of BankSwiftCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankSwiftCode values.
    */
   public final Integer[] getBankSwiftCodeArray()
   {
      return _BankSwiftCode;
   }
    
   /**
    * Gets the BankRefNumber field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankRefNumber or null.
    */
   public final Integer getBankRefNumber( int index )
   {
      return _BankRefNumber[index];
   }
    
   /**
    * Gets the BankRefNumber field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankRefNumber or the specified default value.
    */
   public final int getBankRefNumber( int index, int defaultValue )
   {
      return _BankRefNumber[index] == null ? defaultValue : _BankRefNumber[index].intValue();
   }
    
   /**
    * Gets the array of BankRefNumber fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankRefNumber values.
    */
   public final Integer[] getBankRefNumberArray()
   {
      return _BankRefNumber;
   }
    
   /**
    * Gets the BankInstName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankInstName or null.
    */
   public final String getBankInstName( int index )
   {
      return _BankInstName[index];
   }
    
   /**
    * Gets the BankInstName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankInstName or the specified default value.
    */
   public final String getBankInstName( int index, String defaultValue )
   {
      return _BankInstName[index] == null ? defaultValue : _BankInstName[index];
   }
    
   /**
    * Gets the array of BankInstName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankInstName values.
    */
   public final String[] getBankInstNameArray()
   {
      return _BankInstName;
   }
    
   /**
    * Gets the BankAddr1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAddr1 or null.
    */
   public final String getBankAddr1( int index )
   {
      return _BankAddr1[index];
   }
    
   /**
    * Gets the BankAddr1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAddr1 or the specified default value.
    */
   public final String getBankAddr1( int index, String defaultValue )
   {
      return _BankAddr1[index] == null ? defaultValue : _BankAddr1[index];
   }
    
   /**
    * Gets the array of BankAddr1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAddr1 values.
    */
   public final String[] getBankAddr1Array()
   {
      return _BankAddr1;
   }
    
   /**
    * Gets the BankAddr2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAddr2 or null.
    */
   public final String getBankAddr2( int index )
   {
      return _BankAddr2[index];
   }
    
   /**
    * Gets the BankAddr2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAddr2 or the specified default value.
    */
   public final String getBankAddr2( int index, String defaultValue )
   {
      return _BankAddr2[index] == null ? defaultValue : _BankAddr2[index];
   }
    
   /**
    * Gets the array of BankAddr2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAddr2 values.
    */
   public final String[] getBankAddr2Array()
   {
      return _BankAddr2;
   }
    
   /**
    * Gets the BankAddr3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAddr3 or null.
    */
   public final String getBankAddr3( int index )
   {
      return _BankAddr3[index];
   }
    
   /**
    * Gets the BankAddr3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAddr3 or the specified default value.
    */
   public final String getBankAddr3( int index, String defaultValue )
   {
      return _BankAddr3[index] == null ? defaultValue : _BankAddr3[index];
   }
    
   /**
    * Gets the array of BankAddr3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAddr3 values.
    */
   public final String[] getBankAddr3Array()
   {
      return _BankAddr3;
   }
    
   /**
    * Gets the BankAddr4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAddr4 or null.
    */
   public final String getBankAddr4( int index )
   {
      return _BankAddr4[index];
   }
    
   /**
    * Gets the BankAddr4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAddr4 or the specified default value.
    */
   public final String getBankAddr4( int index, String defaultValue )
   {
      return _BankAddr4[index] == null ? defaultValue : _BankAddr4[index];
   }
    
   /**
    * Gets the array of BankAddr4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAddr4 values.
    */
   public final String[] getBankAddr4Array()
   {
      return _BankAddr4;
   }
    
   /**
    * Gets the BankAddr5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAddr5 or null.
    */
   public final String getBankAddr5( int index )
   {
      return _BankAddr5[index];
   }
    
   /**
    * Gets the BankAddr5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAddr5 or the specified default value.
    */
   public final String getBankAddr5( int index, String defaultValue )
   {
      return _BankAddr5[index] == null ? defaultValue : _BankAddr5[index];
   }
    
   /**
    * Gets the array of BankAddr5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAddr5 values.
    */
   public final String[] getBankAddr5Array()
   {
      return _BankAddr5;
   }
    
   /**
    * Gets the BankPostal field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankPostal or null.
    */
   public final String getBankPostal( int index )
   {
      return _BankPostal[index];
   }
    
   /**
    * Gets the BankPostal field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankPostal or the specified default value.
    */
   public final String getBankPostal( int index, String defaultValue )
   {
      return _BankPostal[index] == null ? defaultValue : _BankPostal[index];
   }
    
   /**
    * Gets the array of BankPostal fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankPostal values.
    */
   public final String[] getBankPostalArray()
   {
      return _BankPostal;
   }
    
   /**
    * Gets the BankCountry field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankCountry or null.
    */
   public final String getBankCountry( int index )
   {
      return _BankCountry[index];
   }
    
   /**
    * Gets the BankCountry field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankCountry or the specified default value.
    */
   public final String getBankCountry( int index, String defaultValue )
   {
      return _BankCountry[index] == null ? defaultValue : _BankCountry[index];
   }
    
   /**
    * Gets the array of BankCountry fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankCountry values.
    */
   public final String[] getBankCountryArray()
   {
      return _BankCountry;
   }
    
   /**
    * Gets the BankAcctType field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAcctType or null.
    */
   public final String getBankAcctType( int index )
   {
      return _BankAcctType[index];
   }
    
   /**
    * Gets the BankAcctType field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAcctType or the specified default value.
    */
   public final String getBankAcctType( int index, String defaultValue )
   {
      return _BankAcctType[index] == null ? defaultValue : _BankAcctType[index];
   }
    
   /**
    * Gets the array of BankAcctType fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAcctType values.
    */
   public final String[] getBankAcctTypeArray()
   {
      return _BankAcctType;
   }
    
   /**
    * Gets the BankAcctTypeDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAcctTypeDesc or null.
    */
   public final String getBankAcctTypeDesc( int index )
   {
      return _BankAcctTypeDesc[index];
   }
    
   /**
    * Gets the BankAcctTypeDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAcctTypeDesc or the specified default value.
    */
   public final String getBankAcctTypeDesc( int index, String defaultValue )
   {
      return _BankAcctTypeDesc[index] == null ? defaultValue : _BankAcctTypeDesc[index];
   }
    
   /**
    * Gets the array of BankAcctTypeDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAcctTypeDesc values.
    */
   public final String[] getBankAcctTypeDescArray()
   {
      return _BankAcctTypeDesc;
   }
    
   /**
    * Gets the BankAcctCurrency field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAcctCurrency or null.
    */
   public final String getBankAcctCurrency( int index )
   {
      return _BankAcctCurrency[index];
   }
    
   /**
    * Gets the BankAcctCurrency field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAcctCurrency or the specified default value.
    */
   public final String getBankAcctCurrency( int index, String defaultValue )
   {
      return _BankAcctCurrency[index] == null ? defaultValue : _BankAcctCurrency[index];
   }
    
   /**
    * Gets the array of BankAcctCurrency fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAcctCurrency values.
    */
   public final String[] getBankAcctCurrencyArray()
   {
      return _BankAcctCurrency;
   }
    
   /**
    * Gets the BankCurrDesc field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankCurrDesc or null.
    */
   public final String getBankCurrDesc( int index )
   {
      return _BankCurrDesc[index];
   }
    
   /**
    * Gets the BankCurrDesc field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankCurrDesc or the specified default value.
    */
   public final String getBankCurrDesc( int index, String defaultValue )
   {
      return _BankCurrDesc[index] == null ? defaultValue : _BankCurrDesc[index];
   }
    
   /**
    * Gets the array of BankCurrDesc fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankCurrDesc values.
    */
   public final String[] getBankCurrDescArray()
   {
      return _BankCurrDesc;
   }
    
   /**
    * Gets the BankEffectiveDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankEffectiveDate or null.
    */
   public final Date getBankEffectiveDate( int index )
   {
      return _BankEffectiveDate[index];
   }
    
   /**
    * Gets the BankEffectiveDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankEffectiveDate or the specified default value.
    */
   public final Date getBankEffectiveDate( int index, Date defaultValue )
   {
      return _BankEffectiveDate[index] == null ? defaultValue : _BankEffectiveDate[index];
   }
    
   /**
    * Gets the array of BankEffectiveDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankEffectiveDate values.
    */
   public final Date[] getBankEffectiveDateArray()
   {
      return _BankEffectiveDate;
   }
    
   /**
    * Gets the BankStopDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankStopDate or null.
    */
   public final Date getBankStopDate( int index )
   {
      return _BankStopDate[index];
   }
    
   /**
    * Gets the BankStopDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankStopDate or the specified default value.
    */
   public final Date getBankStopDate( int index, Date defaultValue )
   {
      return _BankStopDate[index] == null ? defaultValue : _BankStopDate[index];
   }
    
   /**
    * Gets the array of BankStopDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankStopDate values.
    */
   public final Date[] getBankStopDateArray()
   {
      return _BankStopDate;
   }
    
   /**
    * Gets the BankPayMethod field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankPayMethod or null.
    */
   public final String getBankPayMethod( int index )
   {
      return _BankPayMethod[index];
   }
    
   /**
    * Gets the BankPayMethod field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankPayMethod or the specified default value.
    */
   public final String getBankPayMethod( int index, String defaultValue )
   {
      return _BankPayMethod[index] == null ? defaultValue : _BankPayMethod[index];
   }
    
   /**
    * Gets the array of BankPayMethod fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankPayMethod values.
    */
   public final String[] getBankPayMethodArray()
   {
      return _BankPayMethod;
   }
    
   /**
    * Gets the BankACHProcessor field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankACHProcessor or null.
    */
   public final String getBankACHProcessor( int index )
   {
      return _BankACHProcessor[index];
   }
    
   /**
    * Gets the BankACHProcessor field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankACHProcessor or the specified default value.
    */
   public final String getBankACHProcessor( int index, String defaultValue )
   {
      return _BankACHProcessor[index] == null ? defaultValue : _BankACHProcessor[index];
   }
    
   /**
    * Gets the array of BankACHProcessor fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankACHProcessor values.
    */
   public final String[] getBankACHProcessorArray()
   {
      return _BankACHProcessor;
   }
    
   /**
    * Gets the BankContact field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankContact or null.
    */
   public final String getBankContact( int index )
   {
      return _BankContact[index];
   }
    
   /**
    * Gets the BankContact field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankContact or the specified default value.
    */
   public final String getBankContact( int index, String defaultValue )
   {
      return _BankContact[index] == null ? defaultValue : _BankContact[index];
   }
    
   /**
    * Gets the array of BankContact fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankContact values.
    */
   public final String[] getBankContactArray()
   {
      return _BankContact;
   }
    
   /**
    * Gets the BankCorrespondent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankCorrespondent or null.
    */
   public final String getBankCorrespondent( int index )
   {
      return _BankCorrespondent[index];
   }
    
   /**
    * Gets the BankCorrespondent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankCorrespondent or the specified default value.
    */
   public final String getBankCorrespondent( int index, String defaultValue )
   {
      return _BankCorrespondent[index] == null ? defaultValue : _BankCorrespondent[index];
   }
    
   /**
    * Gets the array of BankCorrespondent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankCorrespondent values.
    */
   public final String[] getBankCorrespondentArray()
   {
      return _BankCorrespondent;
   }
    
   /**
    * Gets the AddrCode field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the AddrCode or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the AddrCode field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the AddrCode or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of AddrCode fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of AddrCode values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the BankId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankId or null.
    */
   public final String getBankId( int index )
   {
      return _BankId[index];
   }
    
   /**
    * Gets the BankId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankId or the specified default value.
    */
   public final String getBankId( int index, String defaultValue )
   {
      return _BankId[index] == null ? defaultValue : _BankId[index];
   }
    
   /**
    * Gets the array of BankId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankId values.
    */
   public final String[] getBankIdArray()
   {
      return _BankId;
   }
    
   /**
    * Gets the BankAcctNum field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAcctNum or null.
    */
   public final String getBankAcctNum( int index )
   {
      return _BankAcctNum[index];
   }
    
   /**
    * Gets the BankAcctNum field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAcctNum or the specified default value.
    */
   public final String getBankAcctNum( int index, String defaultValue )
   {
      return _BankAcctNum[index] == null ? defaultValue : _BankAcctNum[index];
   }
    
   /**
    * Gets the array of BankAcctNum fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAcctNum values.
    */
   public final String[] getBankAcctNumArray()
   {
      return _BankAcctNum;
   }
    
   /**
    * Gets the BankAcctName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAcctName or null.
    */
   public final String getBankAcctName( int index )
   {
      return _BankAcctName[index];
   }
    
   /**
    * Gets the BankAcctName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAcctName or the specified default value.
    */
   public final String getBankAcctName( int index, String defaultValue )
   {
      return _BankAcctName[index] == null ? defaultValue : _BankAcctName[index];
   }
    
   /**
    * Gets the array of BankAcctName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAcctName values.
    */
   public final String[] getBankAcctNameArray()
   {
      return _BankAcctName;
   }
    
   /**
    * Gets the IntInvestUUID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestUUID or null.
    */
   public final String getIntInvestUUID( int index )
   {
      return _IntInvestUUID[index];
   }
    
   /**
    * Gets the IntInvestUUID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestUUID or the specified default value.
    */
   public final String getIntInvestUUID( int index, String defaultValue )
   {
      return _IntInvestUUID[index] == null ? defaultValue : _IntInvestUUID[index];
   }
    
   /**
    * Gets the array of IntInvestUUID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestUUID values.
    */
   public final String[] getIntInvestUUIDArray()
   {
      return _IntInvestUUID;
   }
    
   /**
    * Gets the DistribDetlVer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the DistribDetlVer or null.
    */
   public final Integer getDistribDetlVer( int index )
   {
      return _DistribDetlVer[index];
   }
    
   /**
    * Gets the DistribDetlVer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the DistribDetlVer or the specified default value.
    */
   public final int getDistribDetlVer( int index, int defaultValue )
   {
      return _DistribDetlVer[index] == null ? defaultValue : _DistribDetlVer[index].intValue();
   }
    
   /**
    * Gets the array of DistribDetlVer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of DistribDetlVer values.
    */
   public final Integer[] getDistribDetlVerArray()
   {
      return _DistribDetlVer;
   }
    
   /**
    * Gets the BankAcctVer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the BankAcctVer or null.
    */
   public final Integer getBankAcctVer( int index )
   {
      return _BankAcctVer[index];
   }
    
   /**
    * Gets the BankAcctVer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the BankAcctVer or the specified default value.
    */
   public final int getBankAcctVer( int index, int defaultValue )
   {
      return _BankAcctVer[index] == null ? defaultValue : _BankAcctVer[index].intValue();
   }
    
   /**
    * Gets the array of BankAcctVer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of BankAcctVer values.
    */
   public final Integer[] getBankAcctVerArray()
   {
      return _BankAcctVer;
   }
    
   /**
    * Gets the IntInvestVer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the IntInvestVer or null.
    */
   public final Integer getIntInvestVer( int index )
   {
      return _IntInvestVer[index];
   }
    
   /**
    * Gets the IntInvestVer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the IntInvestVer or the specified default value.
    */
   public final int getIntInvestVer( int index, int defaultValue )
   {
      return _IntInvestVer[index] == null ? defaultValue : _IntInvestVer[index].intValue();
   }
    
   /**
    * Gets the array of IntInvestVer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of IntInvestVer values.
    */
   public final Integer[] getIntInvestVerArray()
   {
      return _IntInvestVer;
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
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _DistribDetlUUID = resizeArray( _DistribDetlUUID, _RepeatCount );
      _IntInvestId = resizeArray( _IntInvestId, _RepeatCount );
      _RollOverType = resizeArray( _RollOverType, _RepeatCount );
      _AccountTo = resizeArray( _AccountTo, _RepeatCount );
      _FundTo = resizeArray( _FundTo, _RepeatCount );
      _ClassTo = resizeArray( _ClassTo, _RepeatCount );
      _Remaining = resizeArray( _Remaining, _RepeatCount );
      _Currency = resizeArray( _Currency, _RepeatCount );
      _Percent = resizeArray( _Percent, _RepeatCount );
      _PayType = resizeArray( _PayType, _RepeatCount );
      _PayTypeDesc = resizeArray( _PayTypeDesc, _RepeatCount );
      _CommReduction = resizeArray( _CommReduction, _RepeatCount );
      _IntInvestType = resizeArray( _IntInvestType, _RepeatCount );
      _FELAmt = resizeArray( _FELAmt, _RepeatCount );
      _IntInvestTerm = resizeArray( _IntInvestTerm, _RepeatCount );
      _IntCalcMthd = resizeArray( _IntCalcMthd, _RepeatCount );
      _IntRateType = resizeArray( _IntRateType, _RepeatCount );
      _ForcedRate = resizeArray( _ForcedRate, _RepeatCount );
      _IntCredFreq = resizeArray( _IntCredFreq, _RepeatCount );
      _SourceOfFund = resizeArray( _SourceOfFund, _RepeatCount );
      _RefNum = resizeArray( _RefNum, _RepeatCount );
      _AddlAmt = resizeArray( _AddlAmt, _RepeatCount );
      _BankAcctId = resizeArray( _BankAcctId, _RepeatCount );
      _BankAcctUse = resizeArray( _BankAcctUse, _RepeatCount );
      _BankIdType = resizeArray( _BankIdType, _RepeatCount );
      _BankIdValue = resizeArray( _BankIdValue, _RepeatCount );
      _BankTransitNo = resizeArray( _BankTransitNo, _RepeatCount );
      _BankSwiftCode = resizeArray( _BankSwiftCode, _RepeatCount );
      _BankRefNumber = resizeArray( _BankRefNumber, _RepeatCount );
      _BankInstName = resizeArray( _BankInstName, _RepeatCount );
      _BankAddr1 = resizeArray( _BankAddr1, _RepeatCount );
      _BankAddr2 = resizeArray( _BankAddr2, _RepeatCount );
      _BankAddr3 = resizeArray( _BankAddr3, _RepeatCount );
      _BankAddr4 = resizeArray( _BankAddr4, _RepeatCount );
      _BankAddr5 = resizeArray( _BankAddr5, _RepeatCount );
      _BankPostal = resizeArray( _BankPostal, _RepeatCount );
      _BankCountry = resizeArray( _BankCountry, _RepeatCount );
      _BankAcctType = resizeArray( _BankAcctType, _RepeatCount );
      _BankAcctTypeDesc = resizeArray( _BankAcctTypeDesc, _RepeatCount );
      _BankAcctCurrency = resizeArray( _BankAcctCurrency, _RepeatCount );
      _BankCurrDesc = resizeArray( _BankCurrDesc, _RepeatCount );
      _BankEffectiveDate = resizeArray( _BankEffectiveDate, _RepeatCount );
      _BankStopDate = resizeArray( _BankStopDate, _RepeatCount );
      _BankPayMethod = resizeArray( _BankPayMethod, _RepeatCount );
      _BankACHProcessor = resizeArray( _BankACHProcessor, _RepeatCount );
      _BankContact = resizeArray( _BankContact, _RepeatCount );
      _BankCorrespondent = resizeArray( _BankCorrespondent, _RepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _BankId = resizeArray( _BankId, _RepeatCount );
      _BankAcctNum = resizeArray( _BankAcctNum, _RepeatCount );
      _BankAcctName = resizeArray( _BankAcctName, _RepeatCount );
      _IntInvestUUID = resizeArray( _IntInvestUUID, _RepeatCount );
      _DistribDetlVer = resizeArray( _DistribDetlVer, _RepeatCount );
      _BankAcctVer = resizeArray( _BankAcctVer, _RepeatCount );
      _IntInvestVer = resizeArray( _IntInvestVer, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _DistribDetlUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntInvestId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RollOverType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AccountTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassTo[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remaining[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Currency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Percent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PayTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CommReduction[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntInvestType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FELAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntInvestTerm[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _IntCalcMthd[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntRateType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ForcedRate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntCredFreq[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _SourceOfFund[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RefNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddlAmt[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctUse[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankIdType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankIdValue[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankTransitNo[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankSwiftCode[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankRefNumber[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankInstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAddr5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankPostal[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCountry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctTypeDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctCurrency[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCurrDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankEffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BankStopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _BankPayMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankACHProcessor[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankContact[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankCorrespondent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _BankAcctName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IntInvestUUID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _DistribDetlVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _BankAcctVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _IntInvestVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
      }
      

   }

}
      
