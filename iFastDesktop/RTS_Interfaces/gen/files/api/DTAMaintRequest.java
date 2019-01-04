// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * DTA Update request.
 * For additional view information see <A HREF="../../../../viewspecs/DTAMaint.doc">DTAMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class DTAMaintRequest extends IFastRequest implements Serializable
{

   /**
    * SessionId member variable.
    */
   private String _SessionId = "";
            
   /**
    * User_Id member variable.
    */
   private String _MaxRepeatCount = "";
            
   /**
    * LanguageCode member variable.
    */
   private String _LanguageCode = "";
            
   /**
    * CompanyId member variable.
    */
   private String _CompanyId = "";
            
            
            
   /**
    * Account member variable.
    */
   private String _Account = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * DTAType member array.
    */
   private String[] _DTAType = new String[25];
            
   /**
    * EffectiveDate member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * StopDate member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * TransitNo member array.
    */
   private Integer[] _TransitNo = new Integer[25];
            
   /**
    * ModDate member array.
    */
   private Date[] _ModDate = new Date[25];
            
   /**
    * ModUser member array.
    */
   private String[] _ModUser = new String[25];
            
   /**
    * UserName member array.
    */
   private String[] _UserName = new String[25];
            
   /**
    * ProcessDate member array.
    */
   private Date[] _ProcessDate = new Date[25];
            
   /**
    * Version member array.
    */
   private Integer[] _Version = new Integer[25];
            
   /**
    * DTARecid member array.
    */
   private Integer[] _DTARecid = new Integer[25];
            

   /**
    * Constructs the DTAMaintRequest object.
    * 
    */
   DTAMaintRequest()
   {
      super ( 266 );
   }

   /**
    * Constructs the DTAMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   DTAMaintRequest( String hostEncoding )
   {
      super ( 266, hostEncoding );
   }

   /**
    * Sets the SessionId field for the request.
    * 
    * @param value  Value that the SessionId will be set to.
    */
   public final void setSessionId( String value )
   {
      assertUnsent();
      _SessionId = value;
   }
	
   /**
    * Sets the User_Id field for the request.
    * 
    * @param value  Value that the User_Id will be set to.
    */
   public final void setMaxRepeatCount( String value )
   {
      assertUnsent();
      _MaxRepeatCount = value;
   }
	
   /**
    * Sets the LanguageCode field for the request.
    * 
    * @param value  Value that the LanguageCode will be set to.
    */
   public final void setLanguageCode( String value )
   {
      assertUnsent();
      _LanguageCode = value;
   }
	
   /**
    * Sets the CompanyId field for the request.
    * 
    * @param value  Value that the CompanyId will be set to.
    */
   public final void setCompanyId( String value )
   {
      assertUnsent();
      _CompanyId = value;
   }
	
   /**
    * Sets the Account field for the request.
    * 
    * @param value  Value that the Account will be set to.
    */
   public final void setAccount( String value )
   {
      assertUnsent();
      _Account = value;
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
    * Sets the DTAType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the DTAType will be set to.
    */
   public final void setDTAType( int index, String value )
   {
      assertUnsent();
      _DTAType[index] = value;
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
    * Sets the TransitNo field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the TransitNo will be set to.
    */
   public final void setTransitNo( int index, Integer value )
   {
      assertUnsent();
      _TransitNo[index] = value;
   }
	
   /**
    * Sets the ModDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ModDate will be set to.
    */
   public final void setModDate( int index, Date value )
   {
      assertUnsent();
      _ModDate[index] = value;
   }
	
   /**
    * Sets the ModUser field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ModUser will be set to.
    */
   public final void setModUser( int index, String value )
   {
      assertUnsent();
      _ModUser[index] = value;
   }
	
   /**
    * Sets the UserName field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the UserName will be set to.
    */
   public final void setUserName( int index, String value )
   {
      assertUnsent();
      _UserName[index] = value;
   }
	
   /**
    * Sets the ProcessDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ProcessDate will be set to.
    */
   public final void setProcessDate( int index, Date value )
   {
      assertUnsent();
      _ProcessDate[index] = value;
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
    * Sets the DTARecid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the DTARecid will be set to.
    */
   public final void setDTARecid( int index, Integer value )
   {
      assertUnsent();
      _DTARecid[index] = value;
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
      requestBuffer.appendField( _MaxRepeatCount );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _Account );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _DTAType[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _TransitNo[x] );
         requestBuffer.appendField( _ModDate[x] );
         requestBuffer.appendField( _ModUser[x] );
         requestBuffer.appendField( _UserName[x] );
         requestBuffer.appendField( _ProcessDate[x] );
         requestBuffer.appendField( _Version[x] );
         requestBuffer.appendField( _DTARecid[x] );
      }
   }

}

