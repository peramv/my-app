// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Entity Address Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/UpdEntAddr.doc">UpdEntAddr.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpdEntAddrRequest extends IFastRequest implements Serializable
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
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * EntityId member array.
    */
   private String[] _EntityId = new String[25];
            
   /**
    * Address Code member array.
    */
   private String[] _AddrCode = new String[25];
            
   /**
    * Address Description member array.
    */
   private String[] _AddrDesc = new String[25];
            
   /**
    * Address ID member array.
    */
   private String[] _AddrId = new String[25];
            
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
    * City member array.
    */
   private String[] _City = new String[25];
            
   /**
    * Province member array.
    */
   private String[] _Province = new String[25];
            
   /**
    * Country member array.
    */
   private String[] _Country = new String[25];
            
   /**
    * PostalCode member array.
    */
   private String[] _PostalCode = new String[25];
            
   /**
    * Hold Mail member array.
    */
   private Boolean[] _HoldMail = new Boolean[25];
            
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Addr Xref Recid member array.
    */
   private Integer[] _EntityAddrXrefRid = new Integer[25];
            
   /**
    * Addr Xref Version member array.
    */
   private Integer[] _EntityAddrXrefVer = new Integer[25];
            
   /**
    * Addr Version member array.
    */
   private Integer[] _EntityAddrVer = new Integer[25];
            
   /**
    * RetMailFlag member array.
    */
   private Boolean[] _RetMailFlag = new Boolean[25];
            
   /**
    * RetMailDate member array.
    */
   private Date[] _RetMailDate = new Date[25];
            
   /**
    * RetMailReasonCode member array.
    */
   private String[] _RetMailReasonCode = new String[25];
            
   /**
    * RetMailComment member array.
    */
   private String[] _RetMailComment = new String[25];
            

   /**
    * Constructs the UpdEntAddrRequest object.
    * 
    */
   UpdEntAddrRequest()
   {
      super ( 80 );
   }

   /**
    * Constructs the UpdEntAddrRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   UpdEntAddrRequest( String hostEncoding )
   {
      super ( 80, hostEncoding );
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
    * Sets the EntityId field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EntityId will be set to.
    */
   public final void setEntityId( int index, String value )
   {
      assertUnsent();
      _EntityId[index] = value;
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
    * Sets the Address Description field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address Description will be set to.
    */
   public final void setAddrDesc( int index, String value )
   {
      assertUnsent();
      _AddrDesc[index] = value;
   }
	
   /**
    * Sets the Address ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Address ID will be set to.
    */
   public final void setAddrId( int index, String value )
   {
      assertUnsent();
      _AddrId[index] = value;
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
    * Sets the Country field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Country will be set to.
    */
   public final void setCountry( int index, String value )
   {
      assertUnsent();
      _Country[index] = value;
   }
	
   /**
    * Sets the PostalCode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the PostalCode will be set to.
    */
   public final void setPostalCode( int index, String value )
   {
      assertUnsent();
      _PostalCode[index] = value;
   }
	
   /**
    * Sets the Hold Mail field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Hold Mail will be set to.
    */
   public final void setHoldMail( int index, Boolean value )
   {
      assertUnsent();
      _HoldMail[index] = value;
   }
	
   /**
    * Sets the EffectiveDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EffectiveDate will be set to.
    */
   public final void setEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _EffectiveDate[index] = value;
   }
	
   /**
    * Sets the Addr Xref Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Addr Xref Recid will be set to.
    */
   public final void setEntityAddrXrefRid( int index, Integer value )
   {
      assertUnsent();
      _EntityAddrXrefRid[index] = value;
   }
	
   /**
    * Sets the Addr Xref Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Addr Xref Version will be set to.
    */
   public final void setEntityAddrXrefVer( int index, Integer value )
   {
      assertUnsent();
      _EntityAddrXrefVer[index] = value;
   }
	
   /**
    * Sets the Addr Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Addr Version will be set to.
    */
   public final void setEntityAddrVer( int index, Integer value )
   {
      assertUnsent();
      _EntityAddrVer[index] = value;
   }
	
   /**
    * Sets the RetMailFlag field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RetMailFlag will be set to.
    */
   public final void setRetMailFlag( int index, Boolean value )
   {
      assertUnsent();
      _RetMailFlag[index] = value;
   }
	
   /**
    * Sets the RetMailDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RetMailDate will be set to.
    */
   public final void setRetMailDate( int index, Date value )
   {
      assertUnsent();
      _RetMailDate[index] = value;
   }
	
   /**
    * Sets the RetMailReasonCode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RetMailReasonCode will be set to.
    */
   public final void setRetMailReasonCode( int index, String value )
   {
      assertUnsent();
      _RetMailReasonCode[index] = value;
   }
	
   /**
    * Sets the RetMailComment field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RetMailComment will be set to.
    */
   public final void setRetMailComment( int index, String value )
   {
      assertUnsent();
      _RetMailComment[index] = value;
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
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EntityId[x] );
         requestBuffer.appendField( _AddrCode[x] );
         requestBuffer.appendField( _AddrDesc[x] );
         requestBuffer.appendField( _AddrId[x] );
         requestBuffer.appendField( _AddrLine1[x] );
         requestBuffer.appendField( _AddrLine2[x] );
         requestBuffer.appendField( _AddrLine3[x] );
         requestBuffer.appendField( _City[x] );
         requestBuffer.appendField( _Province[x] );
         requestBuffer.appendField( _Country[x] );
         requestBuffer.appendField( _PostalCode[x] );
         requestBuffer.appendField( _HoldMail[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _EntityAddrXrefRid[x] );
         requestBuffer.appendField( _EntityAddrXrefVer[x] );
         requestBuffer.appendField( _EntityAddrVer[x] );
         requestBuffer.appendField( _RetMailFlag[x] );
         requestBuffer.appendField( _RetMailDate[x] );
         requestBuffer.appendField( _RetMailReasonCode[x] );
         requestBuffer.appendField( _RetMailComment[x] );
      }
   }

}

