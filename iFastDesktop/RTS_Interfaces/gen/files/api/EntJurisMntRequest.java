// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Entity Regulatory Jurisdiction Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/EntJurisMnt.doc">EntJurisMnt.doc</A>.
 * 
 * @author RTS Generated
 */
public class EntJurisMntRequest extends IFastRequest implements Serializable
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
    * Account Number member variable.
    */
   private String _AccountNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * EntRegJurisDetlUUID member array.
    */
   private String[] _EntRegJurisDetlUUID = new String[25];
            
   /**
    * Entity ID member array.
    */
   private String[] _EntityId = new String[25];
            
   /**
    * Regulation member array.
    */
   private String[] _Regulation = new String[25];
            
   /**
    * Tax Jurisdiction member array.
    */
   private String[] _TaxJuris = new String[25];
            
   /**
    * Tax Payer Status member array.
    */
   private String[] _TaxPayerStatus = new String[25];
            
   /**
    * Auto Reset Tax Payer member array.
    */
   private Boolean[] _AutoResetTaxPayrStat = new Boolean[25];
            
   /**
    * Consented member array.
    */
   private String[] _Consented = new String[25];
            
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = new Date[25];
            
   /**
    * End Date member array.
    */
   private Date[] _EndDate = new Date[25];
            
   /**
    * Version member array.
    */
   private Integer[] _Version = new Integer[25];
            
   /**
    * ReasonCode member array.
    */
   private String[] _ReasonCode = new String[25];
            

   /**
    * Constructs the EntJurisMntRequest object.
    * 
    */
   EntJurisMntRequest()
   {
      super ( 459 );
   }

   /**
    * Constructs the EntJurisMntRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   EntJurisMntRequest( String hostEncoding )
   {
      super ( 459, hostEncoding );
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
    * Sets the EntRegJurisDetlUUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the EntRegJurisDetlUUID will be set to.
    */
   public final void setEntRegJurisDetlUUID( int index, String value )
   {
      assertUnsent();
      _EntRegJurisDetlUUID[index] = value;
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
    * Sets the Regulation field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Regulation will be set to.
    */
   public final void setRegulation( int index, String value )
   {
      assertUnsent();
      _Regulation[index] = value;
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
    * Sets the Tax Payer Status field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Tax Payer Status will be set to.
    */
   public final void setTaxPayerStatus( int index, String value )
   {
      assertUnsent();
      _TaxPayerStatus[index] = value;
   }
	
   /**
    * Sets the Auto Reset Tax Payer field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Auto Reset Tax Payer will be set to.
    */
   public final void setAutoResetTaxPayrStat( int index, Boolean value )
   {
      assertUnsent();
      _AutoResetTaxPayrStat[index] = value;
   }
	
   /**
    * Sets the Consented field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Consented will be set to.
    */
   public final void setConsented( int index, String value )
   {
      assertUnsent();
      _Consented[index] = value;
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
    * Sets the End Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the End Date will be set to.
    */
   public final void setEndDate( int index, Date value )
   {
      assertUnsent();
      _EndDate[index] = value;
   }
	
   /**
    * Sets the Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version will be set to.
    */
   public final void setVersion( int index, Integer value )
   {
      assertUnsent();
      _Version[index] = value;
   }
	
   /**
    * Sets the ReasonCode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ReasonCode will be set to.
    */
   public final void setReasonCode( int index, String value )
   {
      assertUnsent();
      _ReasonCode[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EntRegJurisDetlUUID[x] );
         requestBuffer.appendField( _EntityId[x] );
         requestBuffer.appendField( _Regulation[x] );
         requestBuffer.appendField( _TaxJuris[x] );
         requestBuffer.appendField( _TaxPayerStatus[x] );
         requestBuffer.appendField( _AutoResetTaxPayrStat[x] );
         requestBuffer.appendField( _Consented[x] );
         requestBuffer.appendField( _StartDate[x] );
         requestBuffer.appendField( _EndDate[x] );
         requestBuffer.appendField( _Version[x] );
         requestBuffer.appendField( _ReasonCode[x] );
      }
   }

}

