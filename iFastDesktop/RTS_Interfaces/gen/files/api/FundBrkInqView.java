
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Fund Broker Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/FundBrkInq.doc">FundBrkInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundBrkInqView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Fund Broker Code member array.
    */
   private String[] _rxFundBrokerCode = null;
   
   /**
    * Remarks member array.
    */
   private String[] _Remarks = null;
   
   /**
    * Price Type member array.
    */
   private String[] _PriceType = null;
   
   /**
    * Routing Type member array.
    */
   private String[] _RoutingType = null;
   
   /**
    * PUEV Capable member array.
    */
   private Boolean[] _PUEVCapable = null;
   
   /**
    * Clearing Method member array.
    */
   private String[] _ClearingMethod = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * User Name member array.
    */
   private String[] _UserName = null;
   
   /**
    * Mod Date member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Mod User member array.
    */
   private String[] _ModUser = null;
   
   /**
    * Fund Broker Version member array.
    */
   private Integer[] _FundBrokerVersion = null;
   
   /**
    * Fund Broker Record ID member array.
    */
   private Integer[] _FundBrokerRId = null;
   
   /**
    * Fund Broker Entity ID member array.
    */
   private String[] _FundBrokerEntityId = null;
   
   /**
    * Where Use Fund Broker Record ID member array.
    */
   private Integer[] _WhereUseFundBrokerRId = null;
   
   /**
    * Where Use Fund Broker Version member array.
    */
   private Integer[] _WhereUseFundBrokerVersion = null;
   
   /**
    * Fund Broker Last Name member array.
    */
   private String[] _rxFundBrokerLastName = null;
   
   /**
    * Fund Broker First Name member array.
    */
   private String[] _rxFundBrokerFirstName = null;
   
   /**
    * Addr ID member array.
    */
   private String[] _AddrID = null;
   
   /**
    * Entity Addr Version member array.
    */
   private Integer[] _EntityAddrVersion = null;
   
   /**
    * Entity Addr Xref Record ID member array.
    */
   private Integer[] _EntityAddrXrefRId = null;
   
   /**
    * Entity Addr Xref Version member array.
    */
   private Integer[] _EntityAddrXrefVer = null;
   
   /**
    * Addr Line 1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Addr Line 2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Addr Line 3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Addr Line 4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Province member array.
    */
   private String[] _Province = null;
   
   /**
    * Country member array.
    */
   private String[] _Country = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Where Use Primary Contact Record ID member array.
    */
   private Integer[] _WhereUseContact1RId = null;
   
   /**
    * Where Use Primary Contact Version member array.
    */
   private Integer[] _WhereUseContact1Version = null;
   
   /**
    * Primary Contact Entity ID member array.
    */
   private String[] _Contact1EntityId = null;
   
   /**
    * Where Use Secondary Contact Record ID member array.
    */
   private Integer[] _WhereUseContact2RId = null;
   
   /**
    * Where Use Secondary Contact Version member array.
    */
   private Integer[] _WhereUseContact2Version = null;
   
   /**
    * Secondary Contact Entity ID member array.
    */
   private String[] _Contact2EntityId = null;
   
   /**
    * Flag Decribing Wheather There Are Pending Trades With The Fund Broker member array.
    */
   private Boolean[] _HasPendingTrades = null;
   
   /**
    * Effective Date of Latest Pending Trade with the Fund Broker member array.
    */
   private Date[] _LatestPendingTradeDeff = null;
   
   /**
    * Fund Broker Offset Time member array.
    */
   private Integer[] _FundBrokerOffsetTime = null;
   
   /**
    * Fund Broker Portfolio member array.
    */
   private String[] _FbPortfolio = null;
   
   /**
    * Fund Broker Branch member array.
    */
   private String[] _FbBranch = null;
   
   /**
    * Account Servicer member array.
    */
   private String[] _AcctServicer = null;
   
   /**
    * Fund Broker Settle Type member array.
    */
   private String[] _FbSettleType = null;
   
   /**
    * Fund Broker Account Designation member array.
    */
   private String[] _FbAcctDesig = null;
   
   /**
    * Fund Broker Agent member array.
    */
   private String[] _FbAgent = null;
   
   /**
    * Reg Account member array.
    */
   private String[] _RegAcct = null;
   
   /**
    * Fund Broker Dealer member array.
    */
   private String[] _FbDealer = null;
   
   /**
    * Reg Name member array.
    */
   private String[] _RegName = null;
   
   /**
    * Fund Broker Template member array.
    */
   private String[] _FbTemplate = null;
   
   /**
    * Reg AddrID member array.
    */
   private String[] _RegAddrID = null;
   
   /**
    * Reg Entity Addr Version member array.
    */
   private Integer[] _RegEntityAddrVersion = null;
   
   /**
    * Reg Entity Addr Xref RId member array.
    */
   private Integer[] _RegEntityAddrXrefRId = null;
   
   /**
    * Reg Entity Addr Xref Ver member array.
    */
   private Integer[] _RegEntityAddrXrefVer = null;
   
   /**
    * Reg Addr Line 1 member array.
    */
   private String[] _RegAddrLine1 = null;
   
   /**
    * Reg Addr Line 2 member array.
    */
   private String[] _RegAddrLine2 = null;
   
   /**
    * Reg Addr Line 3 member array.
    */
   private String[] _RegAddrLine3 = null;
   
   /**
    * Reg Addr Line 4 member array.
    */
   private String[] _RegAddrLine4 = null;
   
   /**
    * Reg Province member array.
    */
   private String[] _RegProvince = null;
   
   /**
    * Reg Country member array.
    */
   private String[] _RegCountry = null;
   
   /**
    * Reg Postal Code member array.
    */
   private String[] _RegPostalCode = null;
   

   /**
    * Constructs the FundBrkInqView object.
    * 
    */
   public FundBrkInqView()
   {
      super ( new FundBrkInqRequest() );
   }

   /**
    * Constructs the FundBrkInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public FundBrkInqView( String hostEncoding )
   {
      super ( new FundBrkInqRequest( hostEncoding ) );
   }

   /**
    * Gets the FundBrkInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The FundBrkInqRequest object.
    */
   public final FundBrkInqRequest getRequest()
   {
      return (FundBrkInqRequest)getIFastRequest();
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
    * Gets the Fund Broker Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Code or null.
    */
   public final String getrxFundBrokerCode( int index )
   {
      return _rxFundBrokerCode[index];
   }
    
   /**
    * Gets the Fund Broker Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Code or the specified default value.
    */
   public final String getrxFundBrokerCode( int index, String defaultValue )
   {
      return _rxFundBrokerCode[index] == null ? defaultValue : _rxFundBrokerCode[index];
   }
    
   /**
    * Gets the array of Fund Broker Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Code values.
    */
   public final String[] getrxFundBrokerCodeArray()
   {
      return _rxFundBrokerCode;
   }
    
   /**
    * Gets the Remarks field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Remarks or null.
    */
   public final String getRemarks( int index )
   {
      return _Remarks[index];
   }
    
   /**
    * Gets the Remarks field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Remarks or the specified default value.
    */
   public final String getRemarks( int index, String defaultValue )
   {
      return _Remarks[index] == null ? defaultValue : _Remarks[index];
   }
    
   /**
    * Gets the array of Remarks fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Remarks values.
    */
   public final String[] getRemarksArray()
   {
      return _Remarks;
   }
    
   /**
    * Gets the Price Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Price Type or null.
    */
   public final String getPriceType( int index )
   {
      return _PriceType[index];
   }
    
   /**
    * Gets the Price Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Price Type or the specified default value.
    */
   public final String getPriceType( int index, String defaultValue )
   {
      return _PriceType[index] == null ? defaultValue : _PriceType[index];
   }
    
   /**
    * Gets the array of Price Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Price Type values.
    */
   public final String[] getPriceTypeArray()
   {
      return _PriceType;
   }
    
   /**
    * Gets the Routing Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Routing Type or null.
    */
   public final String getRoutingType( int index )
   {
      return _RoutingType[index];
   }
    
   /**
    * Gets the Routing Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Routing Type or the specified default value.
    */
   public final String getRoutingType( int index, String defaultValue )
   {
      return _RoutingType[index] == null ? defaultValue : _RoutingType[index];
   }
    
   /**
    * Gets the array of Routing Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Routing Type values.
    */
   public final String[] getRoutingTypeArray()
   {
      return _RoutingType;
   }
    
   /**
    * Gets the PUEV Capable field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the PUEV Capable or null.
    */
   public final Boolean getPUEVCapable( int index )
   {
      return _PUEVCapable[index];
   }
    
   /**
    * Gets the PUEV Capable field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the PUEV Capable or the specified default value.
    */
   public final boolean getPUEVCapable( int index, boolean defaultValue )
   {
      return _PUEVCapable[index] == null ? defaultValue : _PUEVCapable[index].booleanValue();
   }
    
   /**
    * Gets the array of PUEV Capable fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of PUEV Capable values.
    */
   public final Boolean[] getPUEVCapableArray()
   {
      return _PUEVCapable;
   }
    
   /**
    * Gets the Clearing Method field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Clearing Method or null.
    */
   public final String getClearingMethod( int index )
   {
      return _ClearingMethod[index];
   }
    
   /**
    * Gets the Clearing Method field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Clearing Method or the specified default value.
    */
   public final String getClearingMethod( int index, String defaultValue )
   {
      return _ClearingMethod[index] == null ? defaultValue : _ClearingMethod[index];
   }
    
   /**
    * Gets the array of Clearing Method fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Clearing Method values.
    */
   public final String[] getClearingMethodArray()
   {
      return _ClearingMethod;
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Stop Date or null.
    */
   public final Date getStopDate( int index )
   {
      return _StopDate[index];
   }
    
   /**
    * Gets the Stop Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Stop Date or the specified default value.
    */
   public final Date getStopDate( int index, Date defaultValue )
   {
      return _StopDate[index] == null ? defaultValue : _StopDate[index];
   }
    
   /**
    * Gets the array of Stop Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Stop Date values.
    */
   public final Date[] getStopDateArray()
   {
      return _StopDate;
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date or null.
    */
   public final Date getEffectiveDate( int index )
   {
      return _EffectiveDate[index];
   }
    
   /**
    * Gets the Effective Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date or the specified default value.
    */
   public final Date getEffectiveDate( int index, Date defaultValue )
   {
      return _EffectiveDate[index] == null ? defaultValue : _EffectiveDate[index];
   }
    
   /**
    * Gets the array of Effective Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date values.
    */
   public final Date[] getEffectiveDateArray()
   {
      return _EffectiveDate;
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Process Date or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the Process Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Process Date or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of Process Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Process Date values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the User Name or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the User Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the User Name or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of User Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of User Name values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod Date or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the Mod Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod Date or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of Mod Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod Date values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Mod User or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the Mod User field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Mod User or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of Mod User fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Mod User values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the Fund Broker Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Version or null.
    */
   public final Integer getFundBrokerVersion( int index )
   {
      return _FundBrokerVersion[index];
   }
    
   /**
    * Gets the Fund Broker Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Version or the specified default value.
    */
   public final int getFundBrokerVersion( int index, int defaultValue )
   {
      return _FundBrokerVersion[index] == null ? defaultValue : _FundBrokerVersion[index].intValue();
   }
    
   /**
    * Gets the array of Fund Broker Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Version values.
    */
   public final Integer[] getFundBrokerVersionArray()
   {
      return _FundBrokerVersion;
   }
    
   /**
    * Gets the Fund Broker Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Record ID or null.
    */
   public final Integer getFundBrokerRId( int index )
   {
      return _FundBrokerRId[index];
   }
    
   /**
    * Gets the Fund Broker Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Record ID or the specified default value.
    */
   public final int getFundBrokerRId( int index, int defaultValue )
   {
      return _FundBrokerRId[index] == null ? defaultValue : _FundBrokerRId[index].intValue();
   }
    
   /**
    * Gets the array of Fund Broker Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Record ID values.
    */
   public final Integer[] getFundBrokerRIdArray()
   {
      return _FundBrokerRId;
   }
    
   /**
    * Gets the Fund Broker Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Entity ID or null.
    */
   public final String getFundBrokerEntityId( int index )
   {
      return _FundBrokerEntityId[index];
   }
    
   /**
    * Gets the Fund Broker Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Entity ID or the specified default value.
    */
   public final String getFundBrokerEntityId( int index, String defaultValue )
   {
      return _FundBrokerEntityId[index] == null ? defaultValue : _FundBrokerEntityId[index];
   }
    
   /**
    * Gets the array of Fund Broker Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Entity ID values.
    */
   public final String[] getFundBrokerEntityIdArray()
   {
      return _FundBrokerEntityId;
   }
    
   /**
    * Gets the Where Use Fund Broker Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where Use Fund Broker Record ID or null.
    */
   public final Integer getWhereUseFundBrokerRId( int index )
   {
      return _WhereUseFundBrokerRId[index];
   }
    
   /**
    * Gets the Where Use Fund Broker Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Use Fund Broker Record ID or the specified default value.
    */
   public final int getWhereUseFundBrokerRId( int index, int defaultValue )
   {
      return _WhereUseFundBrokerRId[index] == null ? defaultValue : _WhereUseFundBrokerRId[index].intValue();
   }
    
   /**
    * Gets the array of Where Use Fund Broker Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where Use Fund Broker Record ID values.
    */
   public final Integer[] getWhereUseFundBrokerRIdArray()
   {
      return _WhereUseFundBrokerRId;
   }
    
   /**
    * Gets the Where Use Fund Broker Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where Use Fund Broker Version or null.
    */
   public final Integer getWhereUseFundBrokerVersion( int index )
   {
      return _WhereUseFundBrokerVersion[index];
   }
    
   /**
    * Gets the Where Use Fund Broker Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Use Fund Broker Version or the specified default value.
    */
   public final int getWhereUseFundBrokerVersion( int index, int defaultValue )
   {
      return _WhereUseFundBrokerVersion[index] == null ? defaultValue : _WhereUseFundBrokerVersion[index].intValue();
   }
    
   /**
    * Gets the array of Where Use Fund Broker Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where Use Fund Broker Version values.
    */
   public final Integer[] getWhereUseFundBrokerVersionArray()
   {
      return _WhereUseFundBrokerVersion;
   }
    
   /**
    * Gets the Fund Broker Last Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Last Name or null.
    */
   public final String getrxFundBrokerLastName( int index )
   {
      return _rxFundBrokerLastName[index];
   }
    
   /**
    * Gets the Fund Broker Last Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Last Name or the specified default value.
    */
   public final String getrxFundBrokerLastName( int index, String defaultValue )
   {
      return _rxFundBrokerLastName[index] == null ? defaultValue : _rxFundBrokerLastName[index];
   }
    
   /**
    * Gets the array of Fund Broker Last Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Last Name values.
    */
   public final String[] getrxFundBrokerLastNameArray()
   {
      return _rxFundBrokerLastName;
   }
    
   /**
    * Gets the Fund Broker First Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker First Name or null.
    */
   public final String getrxFundBrokerFirstName( int index )
   {
      return _rxFundBrokerFirstName[index];
   }
    
   /**
    * Gets the Fund Broker First Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker First Name or the specified default value.
    */
   public final String getrxFundBrokerFirstName( int index, String defaultValue )
   {
      return _rxFundBrokerFirstName[index] == null ? defaultValue : _rxFundBrokerFirstName[index];
   }
    
   /**
    * Gets the array of Fund Broker First Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker First Name values.
    */
   public final String[] getrxFundBrokerFirstNameArray()
   {
      return _rxFundBrokerFirstName;
   }
    
   /**
    * Gets the Addr ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Addr ID or null.
    */
   public final String getAddrID( int index )
   {
      return _AddrID[index];
   }
    
   /**
    * Gets the Addr ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Addr ID or the specified default value.
    */
   public final String getAddrID( int index, String defaultValue )
   {
      return _AddrID[index] == null ? defaultValue : _AddrID[index];
   }
    
   /**
    * Gets the array of Addr ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Addr ID values.
    */
   public final String[] getAddrIDArray()
   {
      return _AddrID;
   }
    
   /**
    * Gets the Entity Addr Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Addr Version or null.
    */
   public final Integer getEntityAddrVersion( int index )
   {
      return _EntityAddrVersion[index];
   }
    
   /**
    * Gets the Entity Addr Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Addr Version or the specified default value.
    */
   public final int getEntityAddrVersion( int index, int defaultValue )
   {
      return _EntityAddrVersion[index] == null ? defaultValue : _EntityAddrVersion[index].intValue();
   }
    
   /**
    * Gets the array of Entity Addr Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Addr Version values.
    */
   public final Integer[] getEntityAddrVersionArray()
   {
      return _EntityAddrVersion;
   }
    
   /**
    * Gets the Entity Addr Xref Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Addr Xref Record ID or null.
    */
   public final Integer getEntityAddrXrefRId( int index )
   {
      return _EntityAddrXrefRId[index];
   }
    
   /**
    * Gets the Entity Addr Xref Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Addr Xref Record ID or the specified default value.
    */
   public final int getEntityAddrXrefRId( int index, int defaultValue )
   {
      return _EntityAddrXrefRId[index] == null ? defaultValue : _EntityAddrXrefRId[index].intValue();
   }
    
   /**
    * Gets the array of Entity Addr Xref Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Addr Xref Record ID values.
    */
   public final Integer[] getEntityAddrXrefRIdArray()
   {
      return _EntityAddrXrefRId;
   }
    
   /**
    * Gets the Entity Addr Xref Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity Addr Xref Version or null.
    */
   public final Integer getEntityAddrXrefVer( int index )
   {
      return _EntityAddrXrefVer[index];
   }
    
   /**
    * Gets the Entity Addr Xref Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity Addr Xref Version or the specified default value.
    */
   public final int getEntityAddrXrefVer( int index, int defaultValue )
   {
      return _EntityAddrXrefVer[index] == null ? defaultValue : _EntityAddrXrefVer[index].intValue();
   }
    
   /**
    * Gets the array of Entity Addr Xref Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity Addr Xref Version values.
    */
   public final Integer[] getEntityAddrXrefVerArray()
   {
      return _EntityAddrXrefVer;
   }
    
   /**
    * Gets the Addr Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Addr Line 1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Addr Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Addr Line 1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Addr Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Addr Line 1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Addr Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Addr Line 2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Addr Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Addr Line 2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Addr Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Addr Line 2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Addr Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Addr Line 3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Addr Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Addr Line 3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Addr Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Addr Line 3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Addr Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Addr Line 4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Addr Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Addr Line 4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Addr Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Addr Line 4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Province field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Province or null.
    */
   public final String getProvince( int index )
   {
      return _Province[index];
   }
    
   /**
    * Gets the Province field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Province or the specified default value.
    */
   public final String getProvince( int index, String defaultValue )
   {
      return _Province[index] == null ? defaultValue : _Province[index];
   }
    
   /**
    * Gets the array of Province fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Province values.
    */
   public final String[] getProvinceArray()
   {
      return _Province;
   }
    
   /**
    * Gets the Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country or null.
    */
   public final String getCountry( int index )
   {
      return _Country[index];
   }
    
   /**
    * Gets the Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country or the specified default value.
    */
   public final String getCountry( int index, String defaultValue )
   {
      return _Country[index] == null ? defaultValue : _Country[index];
   }
    
   /**
    * Gets the array of Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country values.
    */
   public final String[] getCountryArray()
   {
      return _Country;
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Postal Code or null.
    */
   public final String getPostalCode( int index )
   {
      return _PostalCode[index];
   }
    
   /**
    * Gets the Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Postal Code or the specified default value.
    */
   public final String getPostalCode( int index, String defaultValue )
   {
      return _PostalCode[index] == null ? defaultValue : _PostalCode[index];
   }
    
   /**
    * Gets the array of Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Postal Code values.
    */
   public final String[] getPostalCodeArray()
   {
      return _PostalCode;
   }
    
   /**
    * Gets the Where Use Primary Contact Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where Use Primary Contact Record ID or null.
    */
   public final Integer getWhereUseContact1RId( int index )
   {
      return _WhereUseContact1RId[index];
   }
    
   /**
    * Gets the Where Use Primary Contact Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Use Primary Contact Record ID or the specified default value.
    */
   public final int getWhereUseContact1RId( int index, int defaultValue )
   {
      return _WhereUseContact1RId[index] == null ? defaultValue : _WhereUseContact1RId[index].intValue();
   }
    
   /**
    * Gets the array of Where Use Primary Contact Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where Use Primary Contact Record ID values.
    */
   public final Integer[] getWhereUseContact1RIdArray()
   {
      return _WhereUseContact1RId;
   }
    
   /**
    * Gets the Where Use Primary Contact Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where Use Primary Contact Version or null.
    */
   public final Integer getWhereUseContact1Version( int index )
   {
      return _WhereUseContact1Version[index];
   }
    
   /**
    * Gets the Where Use Primary Contact Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Use Primary Contact Version or the specified default value.
    */
   public final int getWhereUseContact1Version( int index, int defaultValue )
   {
      return _WhereUseContact1Version[index] == null ? defaultValue : _WhereUseContact1Version[index].intValue();
   }
    
   /**
    * Gets the array of Where Use Primary Contact Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where Use Primary Contact Version values.
    */
   public final Integer[] getWhereUseContact1VersionArray()
   {
      return _WhereUseContact1Version;
   }
    
   /**
    * Gets the Primary Contact Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Primary Contact Entity ID or null.
    */
   public final String getContact1EntityId( int index )
   {
      return _Contact1EntityId[index];
   }
    
   /**
    * Gets the Primary Contact Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Primary Contact Entity ID or the specified default value.
    */
   public final String getContact1EntityId( int index, String defaultValue )
   {
      return _Contact1EntityId[index] == null ? defaultValue : _Contact1EntityId[index];
   }
    
   /**
    * Gets the array of Primary Contact Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Primary Contact Entity ID values.
    */
   public final String[] getContact1EntityIdArray()
   {
      return _Contact1EntityId;
   }
    
   /**
    * Gets the Where Use Secondary Contact Record ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where Use Secondary Contact Record ID or null.
    */
   public final Integer getWhereUseContact2RId( int index )
   {
      return _WhereUseContact2RId[index];
   }
    
   /**
    * Gets the Where Use Secondary Contact Record ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Use Secondary Contact Record ID or the specified default value.
    */
   public final int getWhereUseContact2RId( int index, int defaultValue )
   {
      return _WhereUseContact2RId[index] == null ? defaultValue : _WhereUseContact2RId[index].intValue();
   }
    
   /**
    * Gets the array of Where Use Secondary Contact Record ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where Use Secondary Contact Record ID values.
    */
   public final Integer[] getWhereUseContact2RIdArray()
   {
      return _WhereUseContact2RId;
   }
    
   /**
    * Gets the Where Use Secondary Contact Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Where Use Secondary Contact Version or null.
    */
   public final Integer getWhereUseContact2Version( int index )
   {
      return _WhereUseContact2Version[index];
   }
    
   /**
    * Gets the Where Use Secondary Contact Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Where Use Secondary Contact Version or the specified default value.
    */
   public final int getWhereUseContact2Version( int index, int defaultValue )
   {
      return _WhereUseContact2Version[index] == null ? defaultValue : _WhereUseContact2Version[index].intValue();
   }
    
   /**
    * Gets the array of Where Use Secondary Contact Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Where Use Secondary Contact Version values.
    */
   public final Integer[] getWhereUseContact2VersionArray()
   {
      return _WhereUseContact2Version;
   }
    
   /**
    * Gets the Secondary Contact Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Secondary Contact Entity ID or null.
    */
   public final String getContact2EntityId( int index )
   {
      return _Contact2EntityId[index];
   }
    
   /**
    * Gets the Secondary Contact Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Secondary Contact Entity ID or the specified default value.
    */
   public final String getContact2EntityId( int index, String defaultValue )
   {
      return _Contact2EntityId[index] == null ? defaultValue : _Contact2EntityId[index];
   }
    
   /**
    * Gets the array of Secondary Contact Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Secondary Contact Entity ID values.
    */
   public final String[] getContact2EntityIdArray()
   {
      return _Contact2EntityId;
   }
    
   /**
    * Gets the Flag Decribing Wheather There Are Pending Trades With The Fund Broker field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Flag Decribing Wheather There Are Pending Trades With The Fund Broker or null.
    */
   public final Boolean getHasPendingTrades( int index )
   {
      return _HasPendingTrades[index];
   }
    
   /**
    * Gets the Flag Decribing Wheather There Are Pending Trades With The Fund Broker field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Flag Decribing Wheather There Are Pending Trades With The Fund Broker or the specified default value.
    */
   public final boolean getHasPendingTrades( int index, boolean defaultValue )
   {
      return _HasPendingTrades[index] == null ? defaultValue : _HasPendingTrades[index].booleanValue();
   }
    
   /**
    * Gets the array of Flag Decribing Wheather There Are Pending Trades With The Fund Broker fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Flag Decribing Wheather There Are Pending Trades With The Fund Broker values.
    */
   public final Boolean[] getHasPendingTradesArray()
   {
      return _HasPendingTrades;
   }
    
   /**
    * Gets the Effective Date of Latest Pending Trade with the Fund Broker field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Effective Date of Latest Pending Trade with the Fund Broker or null.
    */
   public final Date getLatestPendingTradeDeff( int index )
   {
      return _LatestPendingTradeDeff[index];
   }
    
   /**
    * Gets the Effective Date of Latest Pending Trade with the Fund Broker field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Effective Date of Latest Pending Trade with the Fund Broker or the specified default value.
    */
   public final Date getLatestPendingTradeDeff( int index, Date defaultValue )
   {
      return _LatestPendingTradeDeff[index] == null ? defaultValue : _LatestPendingTradeDeff[index];
   }
    
   /**
    * Gets the array of Effective Date of Latest Pending Trade with the Fund Broker fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Effective Date of Latest Pending Trade with the Fund Broker values.
    */
   public final Date[] getLatestPendingTradeDeffArray()
   {
      return _LatestPendingTradeDeff;
   }
    
   /**
    * Gets the Fund Broker Offset Time field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Offset Time or null.
    */
   public final Integer getFundBrokerOffsetTime( int index )
   {
      return _FundBrokerOffsetTime[index];
   }
    
   /**
    * Gets the Fund Broker Offset Time field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Offset Time or the specified default value.
    */
   public final int getFundBrokerOffsetTime( int index, int defaultValue )
   {
      return _FundBrokerOffsetTime[index] == null ? defaultValue : _FundBrokerOffsetTime[index].intValue();
   }
    
   /**
    * Gets the array of Fund Broker Offset Time fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Offset Time values.
    */
   public final Integer[] getFundBrokerOffsetTimeArray()
   {
      return _FundBrokerOffsetTime;
   }
    
   /**
    * Gets the Fund Broker Portfolio field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Portfolio or null.
    */
   public final String getFbPortfolio( int index )
   {
      return _FbPortfolio[index];
   }
    
   /**
    * Gets the Fund Broker Portfolio field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Portfolio or the specified default value.
    */
   public final String getFbPortfolio( int index, String defaultValue )
   {
      return _FbPortfolio[index] == null ? defaultValue : _FbPortfolio[index];
   }
    
   /**
    * Gets the array of Fund Broker Portfolio fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Portfolio values.
    */
   public final String[] getFbPortfolioArray()
   {
      return _FbPortfolio;
   }
    
   /**
    * Gets the Fund Broker Branch field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Branch or null.
    */
   public final String getFbBranch( int index )
   {
      return _FbBranch[index];
   }
    
   /**
    * Gets the Fund Broker Branch field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Branch or the specified default value.
    */
   public final String getFbBranch( int index, String defaultValue )
   {
      return _FbBranch[index] == null ? defaultValue : _FbBranch[index];
   }
    
   /**
    * Gets the array of Fund Broker Branch fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Branch values.
    */
   public final String[] getFbBranchArray()
   {
      return _FbBranch;
   }
    
   /**
    * Gets the Account Servicer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Servicer or null.
    */
   public final String getAcctServicer( int index )
   {
      return _AcctServicer[index];
   }
    
   /**
    * Gets the Account Servicer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Servicer or the specified default value.
    */
   public final String getAcctServicer( int index, String defaultValue )
   {
      return _AcctServicer[index] == null ? defaultValue : _AcctServicer[index];
   }
    
   /**
    * Gets the array of Account Servicer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Servicer values.
    */
   public final String[] getAcctServicerArray()
   {
      return _AcctServicer;
   }
    
   /**
    * Gets the Fund Broker Settle Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Settle Type or null.
    */
   public final String getFbSettleType( int index )
   {
      return _FbSettleType[index];
   }
    
   /**
    * Gets the Fund Broker Settle Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Settle Type or the specified default value.
    */
   public final String getFbSettleType( int index, String defaultValue )
   {
      return _FbSettleType[index] == null ? defaultValue : _FbSettleType[index];
   }
    
   /**
    * Gets the array of Fund Broker Settle Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Settle Type values.
    */
   public final String[] getFbSettleTypeArray()
   {
      return _FbSettleType;
   }
    
   /**
    * Gets the Fund Broker Account Designation field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Account Designation or null.
    */
   public final String getFbAcctDesig( int index )
   {
      return _FbAcctDesig[index];
   }
    
   /**
    * Gets the Fund Broker Account Designation field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Account Designation or the specified default value.
    */
   public final String getFbAcctDesig( int index, String defaultValue )
   {
      return _FbAcctDesig[index] == null ? defaultValue : _FbAcctDesig[index];
   }
    
   /**
    * Gets the array of Fund Broker Account Designation fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Account Designation values.
    */
   public final String[] getFbAcctDesigArray()
   {
      return _FbAcctDesig;
   }
    
   /**
    * Gets the Fund Broker Agent field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Agent or null.
    */
   public final String getFbAgent( int index )
   {
      return _FbAgent[index];
   }
    
   /**
    * Gets the Fund Broker Agent field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Agent or the specified default value.
    */
   public final String getFbAgent( int index, String defaultValue )
   {
      return _FbAgent[index] == null ? defaultValue : _FbAgent[index];
   }
    
   /**
    * Gets the array of Fund Broker Agent fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Agent values.
    */
   public final String[] getFbAgentArray()
   {
      return _FbAgent;
   }
    
   /**
    * Gets the Reg Account field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Account or null.
    */
   public final String getRegAcct( int index )
   {
      return _RegAcct[index];
   }
    
   /**
    * Gets the Reg Account field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Account or the specified default value.
    */
   public final String getRegAcct( int index, String defaultValue )
   {
      return _RegAcct[index] == null ? defaultValue : _RegAcct[index];
   }
    
   /**
    * Gets the array of Reg Account fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Account values.
    */
   public final String[] getRegAcctArray()
   {
      return _RegAcct;
   }
    
   /**
    * Gets the Fund Broker Dealer field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Dealer or null.
    */
   public final String getFbDealer( int index )
   {
      return _FbDealer[index];
   }
    
   /**
    * Gets the Fund Broker Dealer field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Dealer or the specified default value.
    */
   public final String getFbDealer( int index, String defaultValue )
   {
      return _FbDealer[index] == null ? defaultValue : _FbDealer[index];
   }
    
   /**
    * Gets the array of Fund Broker Dealer fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Dealer values.
    */
   public final String[] getFbDealerArray()
   {
      return _FbDealer;
   }
    
   /**
    * Gets the Reg Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Name or null.
    */
   public final String getRegName( int index )
   {
      return _RegName[index];
   }
    
   /**
    * Gets the Reg Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Name or the specified default value.
    */
   public final String getRegName( int index, String defaultValue )
   {
      return _RegName[index] == null ? defaultValue : _RegName[index];
   }
    
   /**
    * Gets the array of Reg Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Name values.
    */
   public final String[] getRegNameArray()
   {
      return _RegName;
   }
    
   /**
    * Gets the Fund Broker Template field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Broker Template or null.
    */
   public final String getFbTemplate( int index )
   {
      return _FbTemplate[index];
   }
    
   /**
    * Gets the Fund Broker Template field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Broker Template or the specified default value.
    */
   public final String getFbTemplate( int index, String defaultValue )
   {
      return _FbTemplate[index] == null ? defaultValue : _FbTemplate[index];
   }
    
   /**
    * Gets the array of Fund Broker Template fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Broker Template values.
    */
   public final String[] getFbTemplateArray()
   {
      return _FbTemplate;
   }
    
   /**
    * Gets the Reg AddrID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg AddrID or null.
    */
   public final String getRegAddrID( int index )
   {
      return _RegAddrID[index];
   }
    
   /**
    * Gets the Reg AddrID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg AddrID or the specified default value.
    */
   public final String getRegAddrID( int index, String defaultValue )
   {
      return _RegAddrID[index] == null ? defaultValue : _RegAddrID[index];
   }
    
   /**
    * Gets the array of Reg AddrID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg AddrID values.
    */
   public final String[] getRegAddrIDArray()
   {
      return _RegAddrID;
   }
    
   /**
    * Gets the Reg Entity Addr Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Entity Addr Version or null.
    */
   public final Integer getRegEntityAddrVersion( int index )
   {
      return _RegEntityAddrVersion[index];
   }
    
   /**
    * Gets the Reg Entity Addr Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Entity Addr Version or the specified default value.
    */
   public final int getRegEntityAddrVersion( int index, int defaultValue )
   {
      return _RegEntityAddrVersion[index] == null ? defaultValue : _RegEntityAddrVersion[index].intValue();
   }
    
   /**
    * Gets the array of Reg Entity Addr Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Entity Addr Version values.
    */
   public final Integer[] getRegEntityAddrVersionArray()
   {
      return _RegEntityAddrVersion;
   }
    
   /**
    * Gets the Reg Entity Addr Xref RId field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Entity Addr Xref RId or null.
    */
   public final Integer getRegEntityAddrXrefRId( int index )
   {
      return _RegEntityAddrXrefRId[index];
   }
    
   /**
    * Gets the Reg Entity Addr Xref RId field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Entity Addr Xref RId or the specified default value.
    */
   public final int getRegEntityAddrXrefRId( int index, int defaultValue )
   {
      return _RegEntityAddrXrefRId[index] == null ? defaultValue : _RegEntityAddrXrefRId[index].intValue();
   }
    
   /**
    * Gets the array of Reg Entity Addr Xref RId fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Entity Addr Xref RId values.
    */
   public final Integer[] getRegEntityAddrXrefRIdArray()
   {
      return _RegEntityAddrXrefRId;
   }
    
   /**
    * Gets the Reg Entity Addr Xref Ver field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Entity Addr Xref Ver or null.
    */
   public final Integer getRegEntityAddrXrefVer( int index )
   {
      return _RegEntityAddrXrefVer[index];
   }
    
   /**
    * Gets the Reg Entity Addr Xref Ver field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Entity Addr Xref Ver or the specified default value.
    */
   public final int getRegEntityAddrXrefVer( int index, int defaultValue )
   {
      return _RegEntityAddrXrefVer[index] == null ? defaultValue : _RegEntityAddrXrefVer[index].intValue();
   }
    
   /**
    * Gets the array of Reg Entity Addr Xref Ver fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Entity Addr Xref Ver values.
    */
   public final Integer[] getRegEntityAddrXrefVerArray()
   {
      return _RegEntityAddrXrefVer;
   }
    
   /**
    * Gets the Reg Addr Line 1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Addr Line 1 or null.
    */
   public final String getRegAddrLine1( int index )
   {
      return _RegAddrLine1[index];
   }
    
   /**
    * Gets the Reg Addr Line 1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Addr Line 1 or the specified default value.
    */
   public final String getRegAddrLine1( int index, String defaultValue )
   {
      return _RegAddrLine1[index] == null ? defaultValue : _RegAddrLine1[index];
   }
    
   /**
    * Gets the array of Reg Addr Line 1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Addr Line 1 values.
    */
   public final String[] getRegAddrLine1Array()
   {
      return _RegAddrLine1;
   }
    
   /**
    * Gets the Reg Addr Line 2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Addr Line 2 or null.
    */
   public final String getRegAddrLine2( int index )
   {
      return _RegAddrLine2[index];
   }
    
   /**
    * Gets the Reg Addr Line 2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Addr Line 2 or the specified default value.
    */
   public final String getRegAddrLine2( int index, String defaultValue )
   {
      return _RegAddrLine2[index] == null ? defaultValue : _RegAddrLine2[index];
   }
    
   /**
    * Gets the array of Reg Addr Line 2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Addr Line 2 values.
    */
   public final String[] getRegAddrLine2Array()
   {
      return _RegAddrLine2;
   }
    
   /**
    * Gets the Reg Addr Line 3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Addr Line 3 or null.
    */
   public final String getRegAddrLine3( int index )
   {
      return _RegAddrLine3[index];
   }
    
   /**
    * Gets the Reg Addr Line 3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Addr Line 3 or the specified default value.
    */
   public final String getRegAddrLine3( int index, String defaultValue )
   {
      return _RegAddrLine3[index] == null ? defaultValue : _RegAddrLine3[index];
   }
    
   /**
    * Gets the array of Reg Addr Line 3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Addr Line 3 values.
    */
   public final String[] getRegAddrLine3Array()
   {
      return _RegAddrLine3;
   }
    
   /**
    * Gets the Reg Addr Line 4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Addr Line 4 or null.
    */
   public final String getRegAddrLine4( int index )
   {
      return _RegAddrLine4[index];
   }
    
   /**
    * Gets the Reg Addr Line 4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Addr Line 4 or the specified default value.
    */
   public final String getRegAddrLine4( int index, String defaultValue )
   {
      return _RegAddrLine4[index] == null ? defaultValue : _RegAddrLine4[index];
   }
    
   /**
    * Gets the array of Reg Addr Line 4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Addr Line 4 values.
    */
   public final String[] getRegAddrLine4Array()
   {
      return _RegAddrLine4;
   }
    
   /**
    * Gets the Reg Province field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Province or null.
    */
   public final String getRegProvince( int index )
   {
      return _RegProvince[index];
   }
    
   /**
    * Gets the Reg Province field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Province or the specified default value.
    */
   public final String getRegProvince( int index, String defaultValue )
   {
      return _RegProvince[index] == null ? defaultValue : _RegProvince[index];
   }
    
   /**
    * Gets the array of Reg Province fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Province values.
    */
   public final String[] getRegProvinceArray()
   {
      return _RegProvince;
   }
    
   /**
    * Gets the Reg Country field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Country or null.
    */
   public final String getRegCountry( int index )
   {
      return _RegCountry[index];
   }
    
   /**
    * Gets the Reg Country field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Country or the specified default value.
    */
   public final String getRegCountry( int index, String defaultValue )
   {
      return _RegCountry[index] == null ? defaultValue : _RegCountry[index];
   }
    
   /**
    * Gets the array of Reg Country fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Country values.
    */
   public final String[] getRegCountryArray()
   {
      return _RegCountry;
   }
    
   /**
    * Gets the Reg Postal Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reg Postal Code or null.
    */
   public final String getRegPostalCode( int index )
   {
      return _RegPostalCode[index];
   }
    
   /**
    * Gets the Reg Postal Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reg Postal Code or the specified default value.
    */
   public final String getRegPostalCode( int index, String defaultValue )
   {
      return _RegPostalCode[index] == null ? defaultValue : _RegPostalCode[index];
   }
    
   /**
    * Gets the array of Reg Postal Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reg Postal Code values.
    */
   public final String[] getRegPostalCodeArray()
   {
      return _RegPostalCode;
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
      
      _rxFundBrokerCode = resizeArray( _rxFundBrokerCode, _RepeatCount );
      _Remarks = resizeArray( _Remarks, _RepeatCount );
      _PriceType = resizeArray( _PriceType, _RepeatCount );
      _RoutingType = resizeArray( _RoutingType, _RepeatCount );
      _PUEVCapable = resizeArray( _PUEVCapable, _RepeatCount );
      _ClearingMethod = resizeArray( _ClearingMethod, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _EffectiveDate = resizeArray( _EffectiveDate, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _FundBrokerVersion = resizeArray( _FundBrokerVersion, _RepeatCount );
      _FundBrokerRId = resizeArray( _FundBrokerRId, _RepeatCount );
      _FundBrokerEntityId = resizeArray( _FundBrokerEntityId, _RepeatCount );
      _WhereUseFundBrokerRId = resizeArray( _WhereUseFundBrokerRId, _RepeatCount );
      _WhereUseFundBrokerVersion = resizeArray( _WhereUseFundBrokerVersion, _RepeatCount );
      _rxFundBrokerLastName = resizeArray( _rxFundBrokerLastName, _RepeatCount );
      _rxFundBrokerFirstName = resizeArray( _rxFundBrokerFirstName, _RepeatCount );
      _AddrID = resizeArray( _AddrID, _RepeatCount );
      _EntityAddrVersion = resizeArray( _EntityAddrVersion, _RepeatCount );
      _EntityAddrXrefRId = resizeArray( _EntityAddrXrefRId, _RepeatCount );
      _EntityAddrXrefVer = resizeArray( _EntityAddrXrefVer, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _Province = resizeArray( _Province, _RepeatCount );
      _Country = resizeArray( _Country, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _WhereUseContact1RId = resizeArray( _WhereUseContact1RId, _RepeatCount );
      _WhereUseContact1Version = resizeArray( _WhereUseContact1Version, _RepeatCount );
      _Contact1EntityId = resizeArray( _Contact1EntityId, _RepeatCount );
      _WhereUseContact2RId = resizeArray( _WhereUseContact2RId, _RepeatCount );
      _WhereUseContact2Version = resizeArray( _WhereUseContact2Version, _RepeatCount );
      _Contact2EntityId = resizeArray( _Contact2EntityId, _RepeatCount );
      _HasPendingTrades = resizeArray( _HasPendingTrades, _RepeatCount );
      _LatestPendingTradeDeff = resizeArray( _LatestPendingTradeDeff, _RepeatCount );
      _FundBrokerOffsetTime = resizeArray( _FundBrokerOffsetTime, _RepeatCount );
      _FbPortfolio = resizeArray( _FbPortfolio, _RepeatCount );
      _FbBranch = resizeArray( _FbBranch, _RepeatCount );
      _AcctServicer = resizeArray( _AcctServicer, _RepeatCount );
      _FbSettleType = resizeArray( _FbSettleType, _RepeatCount );
      _FbAcctDesig = resizeArray( _FbAcctDesig, _RepeatCount );
      _FbAgent = resizeArray( _FbAgent, _RepeatCount );
      _RegAcct = resizeArray( _RegAcct, _RepeatCount );
      _FbDealer = resizeArray( _FbDealer, _RepeatCount );
      _RegName = resizeArray( _RegName, _RepeatCount );
      _FbTemplate = resizeArray( _FbTemplate, _RepeatCount );
      _RegAddrID = resizeArray( _RegAddrID, _RepeatCount );
      _RegEntityAddrVersion = resizeArray( _RegEntityAddrVersion, _RepeatCount );
      _RegEntityAddrXrefRId = resizeArray( _RegEntityAddrXrefRId, _RepeatCount );
      _RegEntityAddrXrefVer = resizeArray( _RegEntityAddrXrefVer, _RepeatCount );
      _RegAddrLine1 = resizeArray( _RegAddrLine1, _RepeatCount );
      _RegAddrLine2 = resizeArray( _RegAddrLine2, _RepeatCount );
      _RegAddrLine3 = resizeArray( _RegAddrLine3, _RepeatCount );
      _RegAddrLine4 = resizeArray( _RegAddrLine4, _RepeatCount );
      _RegProvince = resizeArray( _RegProvince, _RepeatCount );
      _RegCountry = resizeArray( _RegCountry, _RepeatCount );
      _RegPostalCode = resizeArray( _RegPostalCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxFundBrokerCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Remarks[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PriceType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RoutingType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PUEVCapable[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _ClearingMethod[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _EffectiveDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundBrokerVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundBrokerRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FundBrokerEntityId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WhereUseFundBrokerRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _WhereUseFundBrokerVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _rxFundBrokerLastName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundBrokerFirstName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _EntityAddrVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EntityAddrXrefRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EntityAddrXrefVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Province[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Country[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WhereUseContact1RId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _WhereUseContact1Version[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Contact1EntityId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _WhereUseContact2RId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _WhereUseContact2Version[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _Contact2EntityId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _HasPendingTrades[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _LatestPendingTradeDeff[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _FundBrokerOffsetTime[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _FbPortfolio[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FbBranch[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AcctServicer[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FbSettleType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FbAcctDesig[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FbAgent[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegAcct[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FbDealer[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FbTemplate[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegAddrID[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegEntityAddrVersion[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RegEntityAddrXrefRId[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RegEntityAddrXrefVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _RegAddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegAddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegAddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegAddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegProvince[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegCountry[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _RegPostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
