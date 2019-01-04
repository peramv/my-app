// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Tax Exempt Authorization Update request.
 * For additional view information see <A HREF="../../../../viewspecs/TaxExAuthUpd.doc">TaxExAuthUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class TaxExAuthUpdRequest extends IFastRequest implements Serializable
{

   /**
    * Session Id member variable.
    */
   private String _SessionID = "";
            
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * TaxExID member array.
    */
   private Integer[] _TaxExID = new Integer[25];
            
   /**
    * Tax Jurisdiction member array.
    */
   private String[] _TaxJuris = new String[25];
            
   /**
    * TaxExType member array.
    */
   private String[] _TaxExType = new String[25];
            
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = new Date[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * ExemptAmtOrig member array.
    */
   private String[] _ExemptAmtOrig = new String[25];
            
   /**
    * TaxExempt Version member array.
    */
   private Integer[] _TaxExempVer = new Integer[25];
            
   /**
    * Entity ID member array.
    */
   private String[] _EntityId = new String[25];
            
   /**
    * Certificate Number member array.
    */
   private String[] _CertificateNum = new String[25];
            
   /**
    * Exemption Scope member array.
    */
   private String[] _ExemptionScope = new String[25];
            
   /**
    * Reason for exemption member array.
    */
   private String[] _ReasonCode = new String[25];
            
   /**
    * Fund Code member array.
    */
   private String[] _FundCode = new String[25];
            
   /**
    * Class Code member array.
    */
   private String[] _ClassCode = new String[25];
            

   /**
    * Constructs the TaxExAuthUpdRequest object.
    * 
    */
   TaxExAuthUpdRequest()
   {
      super ( 302 );
   }

   /**
    * Constructs the TaxExAuthUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   TaxExAuthUpdRequest( String hostEncoding )
   {
      super ( 302, hostEncoding );
   }

   /**
    * Sets the Session Id field for the request.
    * 
    * @param value  Value that the Session Id will be set to.
    */
   public final void setSessionID( String value )
   {
      assertUnsent();
      _SessionID = value;
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
    * Sets the Account Number field for the request.
    * 
    * @param value  Value that the Account Number will be set to.
    */
   public final void setAccountNum( String value )
   {
      assertUnsent();
      _AccountNum = value;
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
    * Sets the RunMode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RunMode will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the TaxExID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the TaxExID will be set to.
    */
   public final void setTaxExID( int index, Integer value )
   {
      assertUnsent();
      _TaxExID[index] = value;
   }
	
   /**
    * Sets the Tax Jurisdiction field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Tax Jurisdiction will be set to.
    */
   public final void setTaxJuris( int index, String value )
   {
      assertUnsent();
      _TaxJuris[index] = value;
   }
	
   /**
    * Sets the TaxExType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the TaxExType will be set to.
    */
   public final void setTaxExType( int index, String value )
   {
      assertUnsent();
      _TaxExType[index] = value;
   }
	
   /**
    * Sets the Start Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Start Date will be set to.
    */
   public final void setStartDate( int index, Date value )
   {
      assertUnsent();
      _StartDate[index] = value;
   }
	
   /**
    * Sets the Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the ExemptAmtOrig field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ExemptAmtOrig will be set to.
    */
   public final void setExemptAmtOrig( int index, String value )
   {
      assertUnsent();
      _ExemptAmtOrig[index] = value;
   }
	
   /**
    * Sets the TaxExempt Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the TaxExempt Version will be set to.
    */
   public final void setTaxExempVer( int index, Integer value )
   {
      assertUnsent();
      _TaxExempVer[index] = value;
   }
	
   /**
    * Sets the Entity ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity ID will be set to.
    */
   public final void setEntityId( int index, String value )
   {
      assertUnsent();
      _EntityId[index] = value;
   }
	
   /**
    * Sets the Certificate Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Certificate Number will be set to.
    */
   public final void setCertificateNum( int index, String value )
   {
      assertUnsent();
      _CertificateNum[index] = value;
   }
	
   /**
    * Sets the Exemption Scope field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Exemption Scope will be set to.
    */
   public final void setExemptionScope( int index, String value )
   {
      assertUnsent();
      _ExemptionScope[index] = value;
   }
	
   /**
    * Sets the Reason for exemption field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reason for exemption will be set to.
    */
   public final void setReasonCode( int index, String value )
   {
      assertUnsent();
      _ReasonCode[index] = value;
   }
	
   /**
    * Sets the Fund Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Code will be set to.
    */
   public final void setFundCode( int index, String value )
   {
      assertUnsent();
      _FundCode[index] = value;
   }
	
   /**
    * Sets the Class Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Class Code will be set to.
    */
   public final void setClassCode( int index, String value )
   {
      assertUnsent();
      _ClassCode[index] = value;
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
      requestBuffer.appendField( _SessionID );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _TaxExID[x] );
         requestBuffer.appendField( _TaxJuris[x] );
         requestBuffer.appendField( _TaxExType[x] );
         requestBuffer.appendField( _StartDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _ExemptAmtOrig[x] );
         requestBuffer.appendField( _TaxExempVer[x] );
         requestBuffer.appendField( _EntityId[x] );
         requestBuffer.appendField( _CertificateNum[x] );
         requestBuffer.appendField( _ExemptionScope[x] );
         requestBuffer.appendField( _ReasonCode[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
      }
   }

}

