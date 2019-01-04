// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Update Shareholder Remarks request.
 * For additional view information see <A HREF="../../../../viewspecs/UpShrRemarks.doc">UpShrRemarks.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpShrRemarksRequest extends IFastRequest implements Serializable
{

   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Session ID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
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
    * Update Remarks with same CIF member variable.
    */
   private Boolean _UpdSameCIFInfo = new Boolean(false);
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Remarks line 1 member array.
    */
   private String[] _Remark1 = new String[50];
            
   /**
    * Remarks line 2 member array.
    */
   private String[] _Remark2 = new String[50];
            
   /**
    * Remarks line 3 member array.
    */
   private String[] _Remark3 = new String[50];
            
   /**
    * Remarks line 4 member array.
    */
   private String[] _Remark4 = new String[50];
            
   /**
    * Remarks line 5 member array.
    */
   private String[] _Remark5 = new String[50];
            
   /**
    * Remarks line 6 member array.
    */
   private String[] _Remark6 = new String[50];
            
   /**
    * Remarks line 7 member array.
    */
   private String[] _Remark7 = new String[50];
            
   /**
    * Remarks line 8 member array.
    */
   private String[] _Remark8 = new String[50];
            
   /**
    * Remarks line 9 member array.
    */
   private String[] _Remark9 = new String[50];
            
   /**
    * Remarks line 10 member array.
    */
   private String[] _Remark10 = new String[50];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[50];
            
   /**
    * Remark is about a transaction member array.
    */
   private Boolean[] _TransNote = new Boolean[50];
            
   /**
    * Remarks is Active member array.
    */
   private Boolean[] _Active = new Boolean[50];
            
   /**
    * Recid of Remarks record member array.
    */
   private Integer[] _RemarksDetlRid = new Integer[50];
            
   /**
    * Version Number member array.
    */
   private Integer[] _RemarksDetlVer = new Integer[50];
            
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[50];
            
   /**
    * Remark Type member array.
    */
   private String[] _RemarkType = new String[50];
            
   /**
    * Account Number member array.
    */
   private String[] _AccountNum = new String[50];
            
   /**
    * Alert member variable.
    */
   private String[] _Alert = new String[50];

   /**
    * Constructs the UpShrRemarksRequest object.
    * 
    */
   UpShrRemarksRequest()
   {
      super ( 85 );
   }

   /**
    * Constructs the UpShrRemarksRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   UpShrRemarksRequest( String hostEncoding )
   {
      super ( 85, hostEncoding );
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
    * Sets the Session ID field for the request.
    * 
    * @param value  Value that the Session ID will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the Update Remarks with same CIF field for the request.
    * 
    * @param value  Value that the Update Remarks with same CIF will be set to.
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
    * Sets the Remarks line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 1 will be set to.
    */
   public final void setRemark1( int index, String value )
   {
      assertUnsent();
      _Remark1[index] = value;
   }
	
   /**
    * Sets the Remarks line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 2 will be set to.
    */
   public final void setRemark2( int index, String value )
   {
      assertUnsent();
      _Remark2[index] = value;
   }
	
   /**
    * Sets the Remarks line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 3 will be set to.
    */
   public final void setRemark3( int index, String value )
   {
      assertUnsent();
      _Remark3[index] = value;
   }
	
   /**
    * Sets the Remarks line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 4 will be set to.
    */
   public final void setRemark4( int index, String value )
   {
      assertUnsent();
      _Remark4[index] = value;
   }
	
   /**
    * Sets the Remarks line 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 5 will be set to.
    */
   public final void setRemark5( int index, String value )
   {
      assertUnsent();
      _Remark5[index] = value;
   }
	
   /**
    * Sets the Remarks line 6 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 6 will be set to.
    */
   public final void setRemark6( int index, String value )
   {
      assertUnsent();
      _Remark6[index] = value;
   }
	
   /**
    * Sets the Remarks line 7 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 7 will be set to.
    */
   public final void setRemark7( int index, String value )
   {
      assertUnsent();
      _Remark7[index] = value;
   }
	
   /**
    * Sets the Remarks line 8 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 8 will be set to.
    */
   public final void setRemark8( int index, String value )
   {
      assertUnsent();
      _Remark8[index] = value;
   }
	
   /**
    * Sets the Remarks line 9 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 9 will be set to.
    */
   public final void setRemark9( int index, String value )
   {
      assertUnsent();
      _Remark9[index] = value;
   }
	
   /**
    * Sets the Remarks line 10 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks line 10 will be set to.
    */
   public final void setRemark10( int index, String value )
   {
      assertUnsent();
      _Remark10[index] = value;
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
    * Sets the Remark is about a transaction field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remark is about a transaction will be set to.
    */
   public final void setTransNote( int index, Boolean value )
   {
      assertUnsent();
      _TransNote[index] = value;
   }
	
   /**
    * Sets the Remarks is Active field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks is Active will be set to.
    */
   public final void setActive( int index, Boolean value )
   {
      assertUnsent();
      _Active[index] = value;
   }
	
   /**
    * Sets the Recid of Remarks record field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Recid of Remarks record will be set to.
    */
   public final void setRemarksDetlRid( int index, Integer value )
   {
      assertUnsent();
      _RemarksDetlRid[index] = value;
   }
	
   /**
    * Sets the Version Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version Number will be set to.
    */
   public final void setRemarksDetlVer( int index, Integer value )
   {
      assertUnsent();
      _RemarksDetlVer[index] = value;
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
    * Sets the Remark Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remark Type will be set to.
    */
   public final void setRemarkType( int index, String value )
   {
      assertUnsent();
      _RemarkType[index] = value;
   }
	
   /**
    * Sets the Account Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( int index, String value )
   {
      assertUnsent();
      _AccountNum[index] = value;
   }

   /**
    * Sets the Alert field for the request.
    * 
    * @param value  Value that the Alert will be set to.
    */
   public final void setAlert( int index, String value )
   {
      assertUnsent();
      _Alert[index] = value;
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
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _UpdSameCIFInfo );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _Remark1[x] );
         requestBuffer.appendField( _Remark2[x] );
         requestBuffer.appendField( _Remark3[x] );
         requestBuffer.appendField( _Remark4[x] );
         requestBuffer.appendField( _Remark5[x] );
         requestBuffer.appendField( _Remark6[x] );
         requestBuffer.appendField( _Remark7[x] );
         requestBuffer.appendField( _Remark8[x] );
         requestBuffer.appendField( _Remark9[x] );
         requestBuffer.appendField( _Remark10[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _TransNote[x] );
         requestBuffer.appendField( _Active[x] );
         requestBuffer.appendField( _RemarksDetlRid[x] );
         requestBuffer.appendField( _RemarksDetlVer[x] );
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _RemarkType[x] );
         requestBuffer.appendField( _AccountNum[x] );
         requestBuffer.appendField( _Alert[x] );
      }
   }

}

