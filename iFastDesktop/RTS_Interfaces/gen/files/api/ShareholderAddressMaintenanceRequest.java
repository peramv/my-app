// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shareholder address Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/ShareholderAddressMaintenance.doc">ShareholderAddressMaintenance.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShareholderAddressMaintenanceRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionId = "";
            
   /**
    * User Id member variable.
    */
   private String _User_Id = "";
            
   /**
    * Language Code member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * Company Id member variable.
    */
   private String _CompanyId = "";
            
   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Shareholder Name 2 member variable.
    */
   private String _ShrName2 = "";
            
            
            
   /**
    * Update Shareholder Info of account with same CIF member variable.
    */
   private Boolean _UpdSameCIFInfo = new Boolean(false);
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = new String[25];
            
   /**
    * Name Line 1 member array.
    */
   private String[] _Name1 = new String[25];
            
   /**
    * Name Line 2 member array.
    */
   private String[] _Name2 = new String[25];
            
   /**
    * Address Line 1 member array.
    */
   private String[] _AddrLine1 = new String[25];
            
   /**
    * Address Line 2 member array.
    */
   private String[] _AddrLine2 = new String[25];
            
   /**
    * Address Line 3 member array.
    */
   private String[] _AddrLine3 = new String[25];
            
   /**
    * Address Line 4 member array.
    */
   private String[] _AddrLine4 = new String[25];
            
   /**
    * Address Line 5 member array.
    */
   private String[] _AddrLine5 = new String[25];
            
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = new String[25];
            
   /**
    * Country Code member array.
    */
   private String[] _CountryCode = new String[25];
            
   /**
    * Address Change Confirmation member array.
    */
   private Boolean[] _Confirm = new Boolean[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * StopDate member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * City member array.
    */
   private String[] _City = new String[25];
            
   /**
    * Address File Version Number member array.
    */
   private Integer[] _AddrFileVer = new Integer[25];
            
   /**
    * Recid ID for Address File Record member array.
    */
   private Integer[] _AddrFileRid = new Integer[25];
            
   /**
    * Salutation member array.
    */
   private String[] _Salutation = new String[25];
            
   /**
    * Registered Address Code member array.
    */
   private String[] _RegAddrCode = new String[25];
            
   /**
    * Province member array.
    */
   private String[] _Province = new String[25];
            
   /**
    * Returned Mail Date member array.
    */
   private Date[] _RetMailDate = new Date[25];
            
   /**
    * Returned Mail Flag member array.
    */
   private Boolean[] _RetMailFlag = new Boolean[25];
            
   /**
    * Reason of returned mail member array.
    */
   private String[] _RetMailReasonCode = new String[25];
            
   /**
    * Stage of returned mail member array.
    */
   private String[] _UnclmStage = new String[25];
            
   /**
    * Date that government report is generated member array.
    */
   private Date[] _UnclmStmtDate = new Date[25];
            
   /**
    * Date that property is remitted to the government member array.
    */
   private Date[] _UnclmRemitDate = new Date[25];
            
   /**
    * Date that stage is changed to unclaimed member array.
    */
   private Date[] _StageDate = new Date[25];
            
   /**
    * Free format comment member array.
    */
   private String[] _Comments = new String[25];
            
   /**
    * Flag indicates Tax Jurisdiction should get sync up with Address-file.addr-cntry member array.
    */
   private Boolean[] _UpdShrTaxJuris = new Boolean[25];
            
   /**
    * Flag indicates Province of Resident should get sync up with Address-file.addr-cntry member array.
    */
   private Boolean[] _UpdShrProvRes = new Boolean[25];
            
   /**
    * Indicates if stage was overridden member array.
    */
   private String[] _StageAssignBy = new String[25];
            
   /**
    * Skips Address Validation member array.
    */
   private String[] _SkipValidate = new String[25];
            
   /**
    * Verify Status member array.
    */
   private String[] _VerifyStat = new String[25];
            

   /**
    * Constructs the ShareholderAddressMaintenanceRequest object.
    * 
    */
   ShareholderAddressMaintenanceRequest()
   {
      super ( 72 );
   }

   /**
    * Constructs the ShareholderAddressMaintenanceRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShareholderAddressMaintenanceRequest( String hostEncoding )
   {
      super ( 72, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User Id field for the request.
    * 
    * @param value  Value that the User Id will be set to.
    */
   public final void setUser_Id( String value )
   {
      assertUnsent();
      _User_Id = value;
   }
	
   /**
    * Sets the Language Code field for the request.
    * 
    * @param value  Value that the Language Code will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the Company Id field for the request.
    * 
    * @param value  Value that the Company Id will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Shareholder Number field for the request.
    * 
    * @param value  Value that the Shareholder Number will be set to.
    */
   public final void setShrNum( String value )
   {
      assertUnsent();
      _ShrNum = value;
   }
	
   /**
    * Sets the Shareholder Name 2 field for the request.
    * 
    * @param value  Value that the Shareholder Name 2 will be set to.
    */
   public final void setShrName2( String value )
   {
      assertUnsent();
      _ShrName2 = value;
   }
	
   /**
    * Sets the Update Shareholder Info of account with same CIF field for the request.
    * 
    * @param value  Value that the Update Shareholder Info of account with same CIF will be set to.
    */
   public final void setUpdSameCIFInfo( Boolean value )
   {
      assertUnsent();
      _UpdSameCIFInfo = value;
   }
	
   /**
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Run Mode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Address Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Code will be set to.
    */
   public final void setAddrCode( int index, String value )
   {
      assertUnsent();
      _AddrCode[index] = value;
   }
	
   /**
    * Sets the Name Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Name Line 1 will be set to.
    */
   public final void setName1( int index, String value )
   {
      assertUnsent();
      _Name1[index] = value;
   }
	
   /**
    * Sets the Name Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Name Line 2 will be set to.
    */
   public final void setName2( int index, String value )
   {
      assertUnsent();
      _Name2[index] = value;
   }
	
   /**
    * Sets the Address Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 1 will be set to.
    */
   public final void setAddrLine1( int index, String value )
   {
      assertUnsent();
      _AddrLine1[index] = value;
   }
	
   /**
    * Sets the Address Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 2 will be set to.
    */
   public final void setAddrLine2( int index, String value )
   {
      assertUnsent();
      _AddrLine2[index] = value;
   }
	
   /**
    * Sets the Address Line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 3 will be set to.
    */
   public final void setAddrLine3( int index, String value )
   {
      assertUnsent();
      _AddrLine3[index] = value;
   }
	
   /**
    * Sets the Address Line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 4 will be set to.
    */
   public final void setAddrLine4( int index, String value )
   {
      assertUnsent();
      _AddrLine4[index] = value;
   }
	
   /**
    * Sets the Address Line 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Line 5 will be set to.
    */
   public final void setAddrLine5( int index, String value )
   {
      assertUnsent();
      _AddrLine5[index] = value;
   }
	
   /**
    * Sets the Postal Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Postal Code will be set to.
    */
   public final void setPostalCode( int index, String value )
   {
      assertUnsent();
      _PostalCode[index] = value;
   }
	
   /**
    * Sets the Country Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Country Code will be set to.
    */
   public final void setCountryCode( int index, String value )
   {
      assertUnsent();
      _CountryCode[index] = value;
   }
	
   /**
    * Sets the Address Change Confirmation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Change Confirmation will be set to.
    */
   public final void setConfirm( int index, Boolean value )
   {
      assertUnsent();
      _Confirm[index] = value;
   }
	
   /**
    * Sets the Effective Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Effective Date will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
   }
	
   /**
    * Sets the StopDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the StopDate will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the City field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the City will be set to.
    */
   public final void setCity( int index, String value )
   {
      assertUnsent();
      _City[index] = value;
   }
	
   /**
    * Sets the Address File Version Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address File Version Number will be set to.
    */
   public final void setAddrFileVer( int index, Integer value )
   {
      assertUnsent();
      _AddrFileVer[index] = value;
   }
	
   /**
    * Sets the Recid ID for Address File Record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Recid ID for Address File Record will be set to.
    */
   public final void setAddrFileRid( int index, Integer value )
   {
      assertUnsent();
      _AddrFileRid[index] = value;
   }
	
   /**
    * Sets the Salutation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Salutation will be set to.
    */
   public final void setSalutation( int index, String value )
   {
      assertUnsent();
      _Salutation[index] = value;
   }
	
   /**
    * Sets the Registered Address Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Registered Address Code will be set to.
    */
   public final void setRegAddrCode( int index, String value )
   {
      assertUnsent();
      _RegAddrCode[index] = value;
   }
	
   /**
    * Sets the Province field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Province will be set to.
    */
   public final void setProvince( int index, String value )
   {
      assertUnsent();
      _Province[index] = value;
   }
	
   /**
    * Sets the Returned Mail Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Returned Mail Date will be set to.
    */
   public final void setRetMailDate( int index, Date value )
   {
      assertUnsent();
      _RetMailDate[index] = value;
   }
	
   /**
    * Sets the Returned Mail Flag field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Returned Mail Flag will be set to.
    */
   public final void setRetMailFlag( int index, Boolean value )
   {
      assertUnsent();
      _RetMailFlag[index] = value;
   }
	
   /**
    * Sets the Reason of returned mail field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reason of returned mail will be set to.
    */
   public final void setRetMailReasonCode( int index, String value )
   {
      assertUnsent();
      _RetMailReasonCode[index] = value;
   }
	
   /**
    * Sets the Stage of returned mail field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stage of returned mail will be set to.
    */
   public final void setUnclmStage( int index, String value )
   {
      assertUnsent();
      _UnclmStage[index] = value;
   }
	
   /**
    * Sets the Date that government report is generated field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Date that government report is generated will be set to.
    */
   public final void setUnclmStmtDate( int index, Date value )
   {
      assertUnsent();
      _UnclmStmtDate[index] = value;
   }
	
   /**
    * Sets the Date that property is remitted to the government field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Date that property is remitted to the government will be set to.
    */
   public final void setUnclmRemitDate( int index, Date value )
   {
      assertUnsent();
      _UnclmRemitDate[index] = value;
   }
	
   /**
    * Sets the Date that stage is changed to unclaimed field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Date that stage is changed to unclaimed will be set to.
    */
   public final void setStageDate( int index, Date value )
   {
      assertUnsent();
      _StageDate[index] = value;
   }
	
   /**
    * Sets the Free format comment field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Free format comment will be set to.
    */
   public final void setComments( int index, String value )
   {
      assertUnsent();
      _Comments[index] = value;
   }
	
   /**
    * Sets the Flag indicates Tax Jurisdiction should get sync up with Address-file.addr-cntry field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Flag indicates Tax Jurisdiction should get sync up with Address-file.addr-cntry will be set to.
    */
   public final void setUpdShrTaxJuris( int index, Boolean value )
   {
      assertUnsent();
      _UpdShrTaxJuris[index] = value;
   }
	
   /**
    * Sets the Flag indicates Province of Resident should get sync up with Address-file.addr-cntry field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Flag indicates Province of Resident should get sync up with Address-file.addr-cntry will be set to.
    */
   public final void setUpdShrProvRes( int index, Boolean value )
   {
      assertUnsent();
      _UpdShrProvRes[index] = value;
   }
	
   /**
    * Sets the Indicates if stage was overridden field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Indicates if stage was overridden will be set to.
    */
   public final void setStageAssignBy( int index, String value )
   {
      assertUnsent();
      _StageAssignBy[index] = value;
   }
	
   /**
    * Sets the Skips Address Validation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Skips Address Validation will be set to.
    */
   public final void setSkipValidate( int index, String value )
   {
      assertUnsent();
      _SkipValidate[index] = value;
   }
	
   /**
    * Sets the Verify Status field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Verify Status will be set to.
    */
   public final void setVerifyStat( int index, String value )
   {
      assertUnsent();
      _VerifyStat[index] = value;
   }
	
   /**
    * Implements the abstract base method to encode
    * the host formatted request.
    * 
    * @param transaction
    *               Host formatted request object.
    */
   protected final void encodeFields( RTSRequestEncodeBuffer requestBuffer ) throws UnsupportedEncodingException
   {
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( _ShrName2 );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _UpdSameCIFInfo );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _AddrCode[x] );
         requestBuffer.appendField( _Name1[x] );
         requestBuffer.appendField( _Name2[x] );
         requestBuffer.appendField( _AddrLine1[x] );
         requestBuffer.appendField( _AddrLine2[x] );
         requestBuffer.appendField( _AddrLine3[x] );
         requestBuffer.appendField( _AddrLine4[x] );
         requestBuffer.appendField( _AddrLine5[x] );
         requestBuffer.appendField( _PostalCode[x] );
         requestBuffer.appendField( _CountryCode[x] );
         requestBuffer.appendField( _Confirm[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _City[x] );
         requestBuffer.appendField( _AddrFileVer[x] );
         requestBuffer.appendField( _AddrFileRid[x] );
         requestBuffer.appendField( _Salutation[x] );
         requestBuffer.appendField( _RegAddrCode[x] );
         requestBuffer.appendField( _Province[x] );
         requestBuffer.appendField( _RetMailDate[x] );
         requestBuffer.appendField( _RetMailFlag[x] );
         requestBuffer.appendField( _RetMailReasonCode[x] );
         requestBuffer.appendField( _UnclmStage[x] );
         requestBuffer.appendField( _UnclmStmtDate[x] );
         requestBuffer.appendField( _UnclmRemitDate[x] );
         requestBuffer.appendField( _StageDate[x] );
         requestBuffer.appendField( _Comments[x] );
         requestBuffer.appendField( _UpdShrTaxJuris[x] );
         requestBuffer.appendField( _UpdShrProvRes[x] );
         requestBuffer.appendField( _StageAssignBy[x] );
         requestBuffer.appendField( _SkipValidate[x] );
         requestBuffer.appendField( _VerifyStat[x] );
      }
   }

}

