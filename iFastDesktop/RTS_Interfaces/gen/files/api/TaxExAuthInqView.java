
// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import java.text.ParseException;
import com.ifds.rts.*;

/**
 * Tax Exemption Authorization Inquiry view.
 * For additional view information see <A HREF="../../../../viewspecs/TaxExAuthInq.doc">TaxExAuthInq.doc</A>.
 * 
 * @author RTS Generated
 */
public class TaxExAuthInqView extends IFastView implements Serializable
{

   /**
    * Deregistration Amount Year-to-Date member variable.
    */
   private String _DeregAmtYrToDate = null;
   
   private int _RepeatCount = 0;
   
   /**
    * Tax Exempt ID member array.
    */
   private Integer[] _TaxExID = null;
   
   /**
    * Tax Jurisdiction member array.
    */
   private String[] _TaxJuris = null;
   
   /**
    * Tax Exemption Type member array.
    */
   private String[] _TaxExType = null;
   
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = null;
   
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = null;
   
   /**
    * Exempt Amount Orig member array.
    */
   private String[] _ExemptAmtOrig = null;
   
   /**
    * Exempt Amount Used member array.
    */
   private String[] _ExemptAmountUsed = null;
   
   /**
    * Process Date member array.
    */
   private Date[] _ProcessDate = null;
   
   /**
    * UserName member array.
    */
   private String[] _UserName = null;
   
   /**
    * ModUser member array.
    */
   private String[] _ModUser = null;
   
   /**
    * ModDate member array.
    */
   private Date[] _ModDate = null;
   
   /**
    * Tax Exempt Version member array.
    */
   private Integer[] _TaxExempVer = null;
   
   /**
    * Entity ID member array.
    */
   private String[] _EntityId = null;
   
   /**
    * Certificate Number member array.
    */
   private String[] _CertificateNum = null;
   
   /**
    * Exemption Scope member array.
    */
   private String[] _ExemptionScope = null;
   
   /**
    * Reason for exemption member array.
    */
   private String[] _ReasonCode = null;
   
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = null;
   
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = null;
   

   /**
    * Constructs the TaxExAuthInqView object.
    * 
    */
   public TaxExAuthInqView()
   {
      super ( new TaxExAuthInqRequest() );
   }

   /**
    * Constructs the TaxExAuthInqView object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   public TaxExAuthInqView( String hostEncoding )
   {
      super ( new TaxExAuthInqRequest( hostEncoding ) );
   }

   /**
    * Gets the TaxExAuthInqRequest object associated with this view. Data is set
    * into this object before calling any of this view's recieve
    * methods. An attempt to set request fields after the first receive will
    * result in a runtime exception.
    * 
    * @return The TaxExAuthInqRequest object.
    */
   public final TaxExAuthInqRequest getRequest()
   {
      return (TaxExAuthInqRequest)getIFastRequest();
   }
        
   /**
    * Gets the Deregistration Amount Year-to-Date field for the response. If the field has
    * no value, null is returned. 
    * 
    * @return The value of the Deregistration Amount Year-to-Date or null.
    */
   public final String getDeregAmtYrToDate()
   {
      return _DeregAmtYrToDate;
   }
	
   /**
    * Gets the Deregistration Amount Year-to-Date field for the response. If the field has
    * no value, the specified default value is returned.
    * 
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Deregistration Amount Year-to-Date or the specified default value.
    */
   public final String getDeregAmtYrToDate( String defaultValue )
   {
      return _DeregAmtYrToDate == null ? defaultValue : _DeregAmtYrToDate;
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
    * Gets the Tax Exempt ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Exempt ID or null.
    */
   public final Integer getTaxExID( int index )
   {
      return _TaxExID[index];
   }
    
   /**
    * Gets the Tax Exempt ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Exempt ID or the specified default value.
    */
   public final int getTaxExID( int index, int defaultValue )
   {
      return _TaxExID[index] == null ? defaultValue : _TaxExID[index].intValue();
   }
    
   /**
    * Gets the array of Tax Exempt ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Exempt ID values.
    */
   public final Integer[] getTaxExIDArray()
   {
      return _TaxExID;
   }
    
   /**
    * Gets the Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Jurisdiction or null.
    */
   public final String getTaxJuris( int index )
   {
      return _TaxJuris[index];
   }
    
   /**
    * Gets the Tax Jurisdiction field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Jurisdiction or the specified default value.
    */
   public final String getTaxJuris( int index, String defaultValue )
   {
      return _TaxJuris[index] == null ? defaultValue : _TaxJuris[index];
   }
    
   /**
    * Gets the array of Tax Jurisdiction fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Jurisdiction values.
    */
   public final String[] getTaxJurisArray()
   {
      return _TaxJuris;
   }
    
   /**
    * Gets the Tax Exemption Type field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Exemption Type or null.
    */
   public final String getTaxExType( int index )
   {
      return _TaxExType[index];
   }
    
   /**
    * Gets the Tax Exemption Type field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Exemption Type or the specified default value.
    */
   public final String getTaxExType( int index, String defaultValue )
   {
      return _TaxExType[index] == null ? defaultValue : _TaxExType[index];
   }
    
   /**
    * Gets the array of Tax Exemption Type fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Exemption Type values.
    */
   public final String[] getTaxExTypeArray()
   {
      return _TaxExType;
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Start Date or null.
    */
   public final Date getStartDate( int index )
   {
      return _StartDate[index];
   }
    
   /**
    * Gets the Start Date field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Start Date or the specified default value.
    */
   public final Date getStartDate( int index, Date defaultValue )
   {
      return _StartDate[index] == null ? defaultValue : _StartDate[index];
   }
    
   /**
    * Gets the array of Start Date fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Start Date values.
    */
   public final Date[] getStartDateArray()
   {
      return _StartDate;
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
    * Gets the Exempt Amount Orig field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exempt Amount Orig or null.
    */
   public final String getExemptAmtOrig( int index )
   {
      return _ExemptAmtOrig[index];
   }
    
   /**
    * Gets the Exempt Amount Orig field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exempt Amount Orig or the specified default value.
    */
   public final String getExemptAmtOrig( int index, String defaultValue )
   {
      return _ExemptAmtOrig[index] == null ? defaultValue : _ExemptAmtOrig[index];
   }
    
   /**
    * Gets the array of Exempt Amount Orig fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exempt Amount Orig values.
    */
   public final String[] getExemptAmtOrigArray()
   {
      return _ExemptAmtOrig;
   }
    
   /**
    * Gets the Exempt Amount Used field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exempt Amount Used or null.
    */
   public final String getExemptAmountUsed( int index )
   {
      return _ExemptAmountUsed[index];
   }
    
   /**
    * Gets the Exempt Amount Used field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exempt Amount Used or the specified default value.
    */
   public final String getExemptAmountUsed( int index, String defaultValue )
   {
      return _ExemptAmountUsed[index] == null ? defaultValue : _ExemptAmountUsed[index];
   }
    
   /**
    * Gets the array of Exempt Amount Used fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exempt Amount Used values.
    */
   public final String[] getExemptAmountUsedArray()
   {
      return _ExemptAmountUsed;
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
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the UserName or null.
    */
   public final String getUserName( int index )
   {
      return _UserName[index];
   }
    
   /**
    * Gets the UserName field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the UserName or the specified default value.
    */
   public final String getUserName( int index, String defaultValue )
   {
      return _UserName[index] == null ? defaultValue : _UserName[index];
   }
    
   /**
    * Gets the array of UserName fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of UserName values.
    */
   public final String[] getUserNameArray()
   {
      return _UserName;
   }
    
   /**
    * Gets the ModUser field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModUser or null.
    */
   public final String getModUser( int index )
   {
      return _ModUser[index];
   }
    
   /**
    * Gets the ModUser field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModUser or the specified default value.
    */
   public final String getModUser( int index, String defaultValue )
   {
      return _ModUser[index] == null ? defaultValue : _ModUser[index];
   }
    
   /**
    * Gets the array of ModUser fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModUser values.
    */
   public final String[] getModUserArray()
   {
      return _ModUser;
   }
    
   /**
    * Gets the ModDate field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the ModDate or null.
    */
   public final Date getModDate( int index )
   {
      return _ModDate[index];
   }
    
   /**
    * Gets the ModDate field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the ModDate or the specified default value.
    */
   public final Date getModDate( int index, Date defaultValue )
   {
      return _ModDate[index] == null ? defaultValue : _ModDate[index];
   }
    
   /**
    * Gets the array of ModDate fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of ModDate values.
    */
   public final Date[] getModDateArray()
   {
      return _ModDate;
   }
    
   /**
    * Gets the Tax Exempt Version field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Tax Exempt Version or null.
    */
   public final Integer getTaxExempVer( int index )
   {
      return _TaxExempVer[index];
   }
    
   /**
    * Gets the Tax Exempt Version field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Tax Exempt Version or the specified default value.
    */
   public final int getTaxExempVer( int index, int defaultValue )
   {
      return _TaxExempVer[index] == null ? defaultValue : _TaxExempVer[index].intValue();
   }
    
   /**
    * Gets the array of Tax Exempt Version fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Tax Exempt Version values.
    */
   public final Integer[] getTaxExempVerArray()
   {
      return _TaxExempVer;
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Entity ID or null.
    */
   public final String getEntityId( int index )
   {
      return _EntityId[index];
   }
    
   /**
    * Gets the Entity ID field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Entity ID or the specified default value.
    */
   public final String getEntityId( int index, String defaultValue )
   {
      return _EntityId[index] == null ? defaultValue : _EntityId[index];
   }
    
   /**
    * Gets the array of Entity ID fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Entity ID values.
    */
   public final String[] getEntityIdArray()
   {
      return _EntityId;
   }
    
   /**
    * Gets the Certificate Number field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Certificate Number or null.
    */
   public final String getCertificateNum( int index )
   {
      return _CertificateNum[index];
   }
    
   /**
    * Gets the Certificate Number field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Certificate Number or the specified default value.
    */
   public final String getCertificateNum( int index, String defaultValue )
   {
      return _CertificateNum[index] == null ? defaultValue : _CertificateNum[index];
   }
    
   /**
    * Gets the array of Certificate Number fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Certificate Number values.
    */
   public final String[] getCertificateNumArray()
   {
      return _CertificateNum;
   }
    
   /**
    * Gets the Exemption Scope field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Exemption Scope or null.
    */
   public final String getExemptionScope( int index )
   {
      return _ExemptionScope[index];
   }
    
   /**
    * Gets the Exemption Scope field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Exemption Scope or the specified default value.
    */
   public final String getExemptionScope( int index, String defaultValue )
   {
      return _ExemptionScope[index] == null ? defaultValue : _ExemptionScope[index];
   }
    
   /**
    * Gets the array of Exemption Scope fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Exemption Scope values.
    */
   public final String[] getExemptionScopeArray()
   {
      return _ExemptionScope;
   }
    
   /**
    * Gets the Reason for exemption field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Reason for exemption or null.
    */
   public final String getReasonCode( int index )
   {
      return _ReasonCode[index];
   }
    
   /**
    * Gets the Reason for exemption field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Reason for exemption or the specified default value.
    */
   public final String getReasonCode( int index, String defaultValue )
   {
      return _ReasonCode[index] == null ? defaultValue : _ReasonCode[index];
   }
    
   /**
    * Gets the array of Reason for exemption fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Reason for exemption values.
    */
   public final String[] getReasonCodeArray()
   {
      return _ReasonCode;
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Fund Code or null.
    */
   public final String getFundCode( int index )
   {
      return _FundCode[index];
   }
    
   /**
    * Gets the Fund Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Fund Code or the specified default value.
    */
   public final String getFundCode( int index, String defaultValue )
   {
      return _FundCode[index] == null ? defaultValue : _FundCode[index];
   }
    
   /**
    * Gets the array of Fund Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Fund Code values.
    */
   public final String[] getFundCodeArray()
   {
      return _FundCode;
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, null is returned. 
    * 
    * @param index  Zero based index of the repeat for which the value will be retrieved.
    * @return The value of the Class Code or null.
    */
   public final String getClassCode( int index )
   {
      return _ClassCode[index];
   }
    
   /**
    * Gets the Class Code field for the response and the 
    * given index. If the field has no value, the specified default value is returned.
    * 
    * @param index         Zero based index of the repeat for which the value will be retrieved.
    * @param defaultValue  The value to return if the field has no value.
    * @return The value of the Class Code or the specified default value.
    */
   public final String getClassCode( int index, String defaultValue )
   {
      return _ClassCode[index] == null ? defaultValue : _ClassCode[index];
   }
    
   /**
    * Gets the array of Class Code fields for the response that
    * have been retrieved so far. Fields from records that have not yet been received,
    * will not present.
    * 
    * @return The array of Class Code values.
    */
   public final String[] getClassCodeArray()
   {
      return _ClassCode;
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
      _DeregAmtYrToDate = responseBuffer.decodeString(responseBuffer.getNextField());
                  
      // multi-record section
      int oldRepeatCount = _RepeatCount;
      decodeRepeatCount( responseBuffer );
      
      _TaxExID = resizeArray( _TaxExID, _RepeatCount );
      _TaxJuris = resizeArray( _TaxJuris, _RepeatCount );
      _TaxExType = resizeArray( _TaxExType, _RepeatCount );
      _StartDate = resizeArray( _StartDate, _RepeatCount );
      _StopDate = resizeArray( _StopDate, _RepeatCount );
      _ExemptAmtOrig = resizeArray( _ExemptAmtOrig, _RepeatCount );
      _ExemptAmountUsed = resizeArray( _ExemptAmountUsed, _RepeatCount );
      _ProcessDate = resizeArray( _ProcessDate, _RepeatCount );
      _UserName = resizeArray( _UserName, _RepeatCount );
      _ModUser = resizeArray( _ModUser, _RepeatCount );
      _ModDate = resizeArray( _ModDate, _RepeatCount );
      _TaxExempVer = resizeArray( _TaxExempVer, _RepeatCount );
      _EntityId = resizeArray( _EntityId, _RepeatCount );
      _CertificateNum = resizeArray( _CertificateNum, _RepeatCount );
      _ExemptionScope = resizeArray( _ExemptionScope, _RepeatCount );
      _ReasonCode = resizeArray( _ReasonCode, _RepeatCount );
      _FundCode = resizeArray( _FundCode, _RepeatCount );
      _ClassCode = resizeArray( _ClassCode, _RepeatCount );
        
      for (int x = oldRepeatCount ; x < _RepeatCount; x++)
      {
         _TaxExID[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _TaxJuris[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _TaxExType[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _StartDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _StopDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _ExemptAmtOrig[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExemptAmountUsed[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ProcessDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _UserName[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModUser[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ModDate[x] = responseBuffer.decodeDate(responseBuffer.getNextField());
         _TaxExempVer[x] = responseBuffer.decodeInteger(responseBuffer.getNextField());
         _EntityId[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _CertificateNum[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ExemptionScope[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ReasonCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _FundCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
         _ClassCode[x] = responseBuffer.decodeString(responseBuffer.getNextField());
      }
      

   }

}
      
