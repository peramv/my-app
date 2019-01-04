
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Account/fund certificates view.
 * For additional view information see <A HREF="../../../../viewspecs/AcctCertificates.doc">AcctCertificates.doc</A>.
 * 
 * @author RTS Generated
 */
public class AcctCertificatesView extends IFastView implements Serializable
{

   private int _RepeatCount = 0;
   
   /**
    * Account Number member array.
    */
   private String[] _rxAcctNum = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _rxFundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _rxClassCode = null;
   
   /**
    * Certificate Number member array.
    */
   private String[] _CertNumber = null;
   
   /**
    * Cross Reference Number member array.
    */
   private String[] _XrefNumber = null;
   
   /**
    * Status Code member array.
    */
   private String[] _StatusCode = null;
   
   /**
    * Status Code Description member array.
    */
   private String[] _StatusDesc = null;
   
   /**
    * Units member array.
    */
   private String[] _Units = null;
   
   /**
    * Certificate Issued member array.
    */
   private Boolean[] _Issued = null;
   
   /**
    * Cert Issue Date member array.
    */
   private Date[] _IssueDate = null;
   
   /**
    * Settle Units Balance member array.
    */
   private String[] _AcctUnits = null;
   
   /**
    * Issued Units member array.
    */
   private String[] _IssuedUnits = null;
   
   /**
    * UnIssued Units member array.
    */
   private String[] _UnIssuedUnits = null;
   
   /**
    * Last Status Code member array.
    */
   private String[] _LastStatusCode = null;
   
   /**
    * Last Status Description member array.
    */
   private String[] _LastStatusDesc = null;
   
   /**
    * Reported member array.
    */
   private Boolean[] _Reported = null;
   
   /**
    * Last Report Date member array.
    */
   private Date[] _LastRptDate = null;
   
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = null;
   
   /**
    * Address Line1 member array.
    */
   private String[] _AddrLine1 = null;
   
   /**
    * Address Line2 member array.
    */
   private String[] _AddrLine2 = null;
   
   /**
    * Address Line3 member array.
    */
   private String[] _AddrLine3 = null;
   
   /**
    * Address Line4 member array.
    */
   private String[] _AddrLine4 = null;
   
   /**
    * Address Line5 member array.
    */
   private String[] _AddrLine5 = null;
   
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = null;
   
   /**
    * Comments member array.
    */
   private String[] _Comments = null;
   
   /**
    * CreatedBy member array.
    */
   private String[] _Username = null;
   
   /**
    * CreatedOn member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * ModifiedBy member array.
    */
   private String[] _ModUser = null;
   
   /**
    * ModifiedOn member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Country Code member array.
    */
   private String[] _CountryCode = null;
   
   /**
    * Country Name member array.
    */
   private String[] _CountryName = null;
   

   /**
    * Constructs the AcctCertificatesView object.
    * 
    */
   public AcctCertificatesView()
   {
      super ( new AcctCertificatesRequest() );
   }

   /**
    * Constructs the AcctCertificatesView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public AcctCertificatesView( String hostEncoding )
   {
      super ( new AcctCertificatesRequest( hostEncoding ) );
   }

   /**
    * Gets the AcctCertificatesRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The AcctCertificatesRequest object.
    */
   public final AcctCertificatesRequest getRequest()
   {
      return (AcctCertificatesRequest)getIFastRequest();
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
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Account Number or null.
    */
   public final String getrxAcctNum( int index )
   {
      return _rxAcctNum[index];
   }
    
   /**
    * Gets the Account Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Account Number or the specified default value.
    */
   public final String getrxAcctNum( int index, String defaultValue )
   {
      return _rxAcctNum[index] == null ? defaultValue : _rxAcctNum[index];
   }
    
   /**
    * Gets the array of Account Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Account Number values.
    */
   public final String[] getrxAcctNumArray()
   {
      return _rxAcctNum;
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
    * Gets the Certificate Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Certificate Number or null.
    */
   public final String getCertNumber( int index )
   {
      return _CertNumber[index];
   }
    
   /**
    * Gets the Certificate Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Certificate Number or the specified default value.
    */
   public final String getCertNumber( int index, String defaultValue )
   {
      return _CertNumber[index] == null ? defaultValue : _CertNumber[index];
   }
    
   /**
    * Gets the array of Certificate Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Certificate Number values.
    */
   public final String[] getCertNumberArray()
   {
      return _CertNumber;
   }
    
   /**
    * Gets the Cross Reference Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cross Reference Number or null.
    */
   public final String getXrefNumber( int index )
   {
      return _XrefNumber[index];
   }
    
   /**
    * Gets the Cross Reference Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cross Reference Number or the specified default value.
    */
   public final String getXrefNumber( int index, String defaultValue )
   {
      return _XrefNumber[index] == null ? defaultValue : _XrefNumber[index];
   }
    
   /**
    * Gets the array of Cross Reference Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cross Reference Number values.
    */
   public final String[] getXrefNumberArray()
   {
      return _XrefNumber;
   }
    
   /**
    * Gets the Status Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status Code or null.
    */
   public final String getStatusCode( int index )
   {
      return _StatusCode[index];
   }
    
   /**
    * Gets the Status Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status Code or the specified default value.
    */
   public final String getStatusCode( int index, String defaultValue )
   {
      return _StatusCode[index] == null ? defaultValue : _StatusCode[index];
   }
    
   /**
    * Gets the array of Status Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status Code values.
    */
   public final String[] getStatusCodeArray()
   {
      return _StatusCode;
   }
    
   /**
    * Gets the Status Code Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Status Code Description or null.
    */
   public final String getStatusDesc( int index )
   {
      return _StatusDesc[index];
   }
    
   /**
    * Gets the Status Code Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Status Code Description or the specified default value.
    */
   public final String getStatusDesc( int index, String defaultValue )
   {
      return _StatusDesc[index] == null ? defaultValue : _StatusDesc[index];
   }
    
   /**
    * Gets the array of Status Code Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Status Code Description values.
    */
   public final String[] getStatusDescArray()
   {
      return _StatusDesc;
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Units or null.
    */
   public final String getUnits( int index )
   {
      return _Units[index];
   }
    
   /**
    * Gets the Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Units or the specified default value.
    */
   public final String getUnits( int index, String defaultValue )
   {
      return _Units[index] == null ? defaultValue : _Units[index];
   }
    
   /**
    * Gets the array of Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Units values.
    */
   public final String[] getUnitsArray()
   {
      return _Units;
   }
    
   /**
    * Gets the Certificate Issued field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Certificate Issued or null.
    */
   public final Boolean getIssued( int index )
   {
      return _Issued[index];
   }
    
   /**
    * Gets the Certificate Issued field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Certificate Issued or the specified default value.
    */
   public final boolean getIssued( int index, boolean defaultValue )
   {
      return _Issued[index] == null ? defaultValue : _Issued[index].booleanValue();
   }
    
   /**
    * Gets the array of Certificate Issued fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Certificate Issued values.
    */
   public final Boolean[] getIssuedArray()
   {
      return _Issued;
   }
    
   /**
    * Gets the Cert Issue Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Cert Issue Date or null.
    */
   public final Date getIssueDate( int index )
   {
      return _IssueDate[index];
   }
    
   /**
    * Gets the Cert Issue Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Cert Issue Date or the specified default value.
    */
   public final Date getIssueDate( int index, Date defaultValue )
   {
      return _IssueDate[index] == null ? defaultValue : _IssueDate[index];
   }
    
   /**
    * Gets the array of Cert Issue Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Cert Issue Date values.
    */
   public final Date[] getIssueDateArray()
   {
      return _IssueDate;
   }
    
   /**
    * Gets the Settle Units Balance field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Settle Units Balance or null.
    */
   public final String getAcctUnits( int index )
   {
      return _AcctUnits[index];
   }
    
   /**
    * Gets the Settle Units Balance field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Settle Units Balance or the specified default value.
    */
   public final String getAcctUnits( int index, String defaultValue )
   {
      return _AcctUnits[index] == null ? defaultValue : _AcctUnits[index];
   }
    
   /**
    * Gets the array of Settle Units Balance fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Settle Units Balance values.
    */
   public final String[] getAcctUnitsArray()
   {
      return _AcctUnits;
   }
    
   /**
    * Gets the Issued Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Issued Units or null.
    */
   public final String getIssuedUnits( int index )
   {
      return _IssuedUnits[index];
   }
    
   /**
    * Gets the Issued Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Issued Units or the specified default value.
    */
   public final String getIssuedUnits( int index, String defaultValue )
   {
      return _IssuedUnits[index] == null ? defaultValue : _IssuedUnits[index];
   }
    
   /**
    * Gets the array of Issued Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Issued Units values.
    */
   public final String[] getIssuedUnitsArray()
   {
      return _IssuedUnits;
   }
    
   /**
    * Gets the UnIssued Units field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UnIssued Units or null.
    */
   public final String getUnIssuedUnits( int index )
   {
      return _UnIssuedUnits[index];
   }
    
   /**
    * Gets the UnIssued Units field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UnIssued Units or the specified default value.
    */
   public final String getUnIssuedUnits( int index, String defaultValue )
   {
      return _UnIssuedUnits[index] == null ? defaultValue : _UnIssuedUnits[index];
   }
    
   /**
    * Gets the array of UnIssued Units fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UnIssued Units values.
    */
   public final String[] getUnIssuedUnitsArray()
   {
      return _UnIssuedUnits;
   }
    
   /**
    * Gets the Last Status Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Status Code or null.
    */
   public final String getLastStatusCode( int index )
   {
      return _LastStatusCode[index];
   }
    
   /**
    * Gets the Last Status Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Status Code or the specified default value.
    */
   public final String getLastStatusCode( int index, String defaultValue )
   {
      return _LastStatusCode[index] == null ? defaultValue : _LastStatusCode[index];
   }
    
   /**
    * Gets the array of Last Status Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Status Code values.
    */
   public final String[] getLastStatusCodeArray()
   {
      return _LastStatusCode;
   }
    
   /**
    * Gets the Last Status Description field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Status Description or null.
    */
   public final String getLastStatusDesc( int index )
   {
      return _LastStatusDesc[index];
   }
    
   /**
    * Gets the Last Status Description field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Status Description or the specified default value.
    */
   public final String getLastStatusDesc( int index, String defaultValue )
   {
      return _LastStatusDesc[index] == null ? defaultValue : _LastStatusDesc[index];
   }
    
   /**
    * Gets the array of Last Status Description fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Status Description values.
    */
   public final String[] getLastStatusDescArray()
   {
      return _LastStatusDesc;
   }
    
   /**
    * Gets the Reported field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reported or null.
    */
   public final Boolean getReported( int index )
   {
      return _Reported[index];
   }
    
   /**
    * Gets the Reported field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reported or the specified default value.
    */
   public final boolean getReported( int index, boolean defaultValue )
   {
      return _Reported[index] == null ? defaultValue : _Reported[index].booleanValue();
   }
    
   /**
    * Gets the array of Reported fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reported values.
    */
   public final Boolean[] getReportedArray()
   {
      return _Reported;
   }
    
   /**
    * Gets the Last Report Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Last Report Date or null.
    */
   public final Date getLastRptDate( int index )
   {
      return _LastRptDate[index];
   }
    
   /**
    * Gets the Last Report Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Last Report Date or the specified default value.
    */
   public final Date getLastRptDate( int index, Date defaultValue )
   {
      return _LastRptDate[index] == null ? defaultValue : _LastRptDate[index];
   }
    
   /**
    * Gets the array of Last Report Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Last Report Date values.
    */
   public final Date[] getLastRptDateArray()
   {
      return _LastRptDate;
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Code or null.
    */
   public final String getAddrCode( int index )
   {
      return _AddrCode[index];
   }
    
   /**
    * Gets the Address Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Code or the specified default value.
    */
   public final String getAddrCode( int index, String defaultValue )
   {
      return _AddrCode[index] == null ? defaultValue : _AddrCode[index];
   }
    
   /**
    * Gets the array of Address Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Code values.
    */
   public final String[] getAddrCodeArray()
   {
      return _AddrCode;
   }
    
   /**
    * Gets the Address Line1 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line1 or null.
    */
   public final String getAddrLine1( int index )
   {
      return _AddrLine1[index];
   }
    
   /**
    * Gets the Address Line1 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line1 or the specified default value.
    */
   public final String getAddrLine1( int index, String defaultValue )
   {
      return _AddrLine1[index] == null ? defaultValue : _AddrLine1[index];
   }
    
   /**
    * Gets the array of Address Line1 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line1 values.
    */
   public final String[] getAddrLine1Array()
   {
      return _AddrLine1;
   }
    
   /**
    * Gets the Address Line2 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line2 or null.
    */
   public final String getAddrLine2( int index )
   {
      return _AddrLine2[index];
   }
    
   /**
    * Gets the Address Line2 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line2 or the specified default value.
    */
   public final String getAddrLine2( int index, String defaultValue )
   {
      return _AddrLine2[index] == null ? defaultValue : _AddrLine2[index];
   }
    
   /**
    * Gets the array of Address Line2 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line2 values.
    */
   public final String[] getAddrLine2Array()
   {
      return _AddrLine2;
   }
    
   /**
    * Gets the Address Line3 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line3 or null.
    */
   public final String getAddrLine3( int index )
   {
      return _AddrLine3[index];
   }
    
   /**
    * Gets the Address Line3 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line3 or the specified default value.
    */
   public final String getAddrLine3( int index, String defaultValue )
   {
      return _AddrLine3[index] == null ? defaultValue : _AddrLine3[index];
   }
    
   /**
    * Gets the array of Address Line3 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line3 values.
    */
   public final String[] getAddrLine3Array()
   {
      return _AddrLine3;
   }
    
   /**
    * Gets the Address Line4 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line4 or null.
    */
   public final String getAddrLine4( int index )
   {
      return _AddrLine4[index];
   }
    
   /**
    * Gets the Address Line4 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line4 or the specified default value.
    */
   public final String getAddrLine4( int index, String defaultValue )
   {
      return _AddrLine4[index] == null ? defaultValue : _AddrLine4[index];
   }
    
   /**
    * Gets the array of Address Line4 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line4 values.
    */
   public final String[] getAddrLine4Array()
   {
      return _AddrLine4;
   }
    
   /**
    * Gets the Address Line5 field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Address Line5 or null.
    */
   public final String getAddrLine5( int index )
   {
      return _AddrLine5[index];
   }
    
   /**
    * Gets the Address Line5 field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Address Line5 or the specified default value.
    */
   public final String getAddrLine5( int index, String defaultValue )
   {
      return _AddrLine5[index] == null ? defaultValue : _AddrLine5[index];
   }
    
   /**
    * Gets the array of Address Line5 fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Address Line5 values.
    */
   public final String[] getAddrLine5Array()
   {
      return _AddrLine5;
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
    * Gets the Comments field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Comments or null.
    */
   public final String getComments( int index )
   {
      return _Comments[index];
   }
    
   /**
    * Gets the Comments field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Comments or the specified default value.
    */
   public final String getComments( int index, String defaultValue )
   {
      return _Comments[index] == null ? defaultValue : _Comments[index];
   }
    
   /**
    * Gets the array of Comments fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Comments values.
    */
   public final String[] getCommentsArray()
   {
      return _Comments;
   }
    
   /**
    * Gets the CreatedBy field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CreatedBy or null.
    */
   public final String getUsername( int index )
   {
      return _Username[index];
   }
    
   /**
    * Gets the CreatedBy field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CreatedBy or the specified default value.
    */
   public final String getUsername( int index, String defaultValue )
   {
      return _Username[index] == null ? defaultValue : _Username[index];
   }
    
   /**
    * Gets the array of CreatedBy fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CreatedBy values.
    */
   public final String[] getUsernameArray()
   {
      return _Username;
   }
    
   /**
    * Gets the CreatedOn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the CreatedOn or null.
    */
   public final Date getProcessDate( int index )
   {
      return _ProcessDate[index];
   }
    
   /**
    * Gets the CreatedOn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the CreatedOn or the specified default value.
    */
   public final Date getProcessDate( int index, Date defaultValue )
   {
      return _ProcessDate[index] == null ? defaultValue : _ProcessDate[index];
   }
    
   /**
    * Gets the array of CreatedOn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of CreatedOn values.
    */
   public final Date[] getProcessDateArray()
   {
      return _ProcessDate;
   }
    
   /**
    * Gets the ModifiedBy field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModifiedBy or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the ModifiedBy field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModifiedBy or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of ModifiedBy fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModifiedBy values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the ModifiedOn field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModifiedOn or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the ModifiedOn field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModifiedOn or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of ModifiedOn fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModifiedOn values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Code or null.
    */
   public final String getCountryCode( int index )
   {
      return _CountryCode[index];
   }
    
   /**
    * Gets the Country Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Code or the specified default value.
    */
   public final String getCountryCode( int index, String defaultValue )
   {
      return _CountryCode[index] == null ? defaultValue : _CountryCode[index];
   }
    
   /**
    * Gets the array of Country Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Code values.
    */
   public final String[] getCountryCodeArray()
   {
      return _CountryCode;
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Country Name or null.
    */
   public final String getCountryName( int index )
   {
      return _CountryName[index];
   }
    
   /**
    * Gets the Country Name field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Country Name or the specified default value.
    */
   public final String getCountryName( int index, String defaultValue )
   {
      return _CountryName[index] == null ? defaultValue : _CountryName[index];
   }
    
   /**
    * Gets the array of Country Name fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Country Name values.
    */
   public final String[] getCountryNameArray()
   {
      return _CountryName;
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
      
      _rxAcctNum = resizeArray( _rxAcctNum, _RepeatCount );
      _rxFundCode = resizeArray( _rxFundCode, _RepeatCount );
      _rxClassCode = resizeArray( _rxClassCode, _RepeatCount );
      _CertNumber = resizeArray( _CertNumber, _RepeatCount );
      _XrefNumber = resizeArray( _XrefNumber, _RepeatCount );
      _StatusCode = resizeArray( _StatusCode, _RepeatCount );
      _StatusDesc = resizeArray( _StatusDesc, _RepeatCount );
      _Units = resizeArray( _Units, _RepeatCount );
      _Issued = resizeArray( _Issued, _RepeatCount );
      _IssueDate = resizeArray( _IssueDate, _RepeatCount );
      _AcctUnits = resizeArray( _AcctUnits, _RepeatCount );
      _IssuedUnits = resizeArray( _IssuedUnits, _RepeatCount );
      _UnIssuedUnits = resizeArray( _UnIssuedUnits, _RepeatCount );
      _LastStatusCode = resizeArray( _LastStatusCode, _RepeatCount );
      _LastStatusDesc = resizeArray( _LastStatusDesc, _RepeatCount );
      _Reported = resizeArray( _Reported, _RepeatCount );
      _LastRptDate = resizeArray( _LastRptDate, _RepeatCount );
      _AddrCode = resizeArray( _AddrCode, _RepeatCount );
      _AddrLine1 = resizeArray( _AddrLine1, _RepeatCount );
      _AddrLine2 = resizeArray( _AddrLine2, _RepeatCount );
      _AddrLine3 = resizeArray( _AddrLine3, _RepeatCount );
      _AddrLine4 = resizeArray( _AddrLine4, _RepeatCount );
      _AddrLine5 = resizeArray( _AddrLine5, _RepeatCount );
      _PostalCode = resizeArray( _PostalCode, _RepeatCount );
      _Comments = resizeArray( _Comments, _RepeatCount );
      _Username = resizeArray( _Username, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _CountryCode = resizeArray( _CountryCode, _RepeatCount );
      _CountryName = resizeArray( _CountryName, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _rxAcctNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxFundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _rxClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _XrefNumber[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatusCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StatusDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Units[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Issued[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _IssueDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AcctUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _IssuedUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _UnIssuedUnits[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastStatusCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _LastStatusDesc[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Reported[x] = responseBuffer.decodeBoolean(responseBuffer.getNextField());
         _LastRptDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _AddrCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine1[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine2[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine3[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine4[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _AddrLine5[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _PostalCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Comments[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _Username[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _CountryCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CountryName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
