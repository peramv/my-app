// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Market Index Details Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/MktIdxDetUpd.doc">MktIdxDetUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class MktIdxDetUpdRequest extends IFastRequest implements Serializable
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
    * LanguageCode member variable.
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
    * Market Index Detail Version member array.
    */
   private Integer[] _MktIdxDetlVer = new Integer[25];
            
   /**
    * Market Index Detail Recid member array.
    */
   private Integer[] _MktIdxDetlRid = new Integer[25];
            
   /**
    * Index Code member array.
    */
   private String[] _IndexCode = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Closing Value member array.
    */
   private String[] _ClosingValue = new String[25];
            
   /**
    * Hurdle Rate member array.
    */
   private String[] _HurdleRate = new String[25];
            

   /**
    * Constructs the MktIdxDetUpdRequest object.
    * 
    */
   MktIdxDetUpdRequest()
   {
      super ( 248 );
   }

   /**
    * Constructs the MktIdxDetUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   MktIdxDetUpdRequest( String hostEncoding )
   {
      super ( 248, hostEncoding );
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
    * Sets the Market Index Detail Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Market Index Detail Version will be set to.
    */
   public final void setMktIdxDetlVer( int index, Integer value )
   {
      assertUnsent();
      _MktIdxDetlVer[index] = value;
   }
	
   /**
    * Sets the Market Index Detail Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Market Index Detail Recid will be set to.
    */
   public final void setMktIdxDetlRid( int index, Integer value )
   {
      assertUnsent();
      _MktIdxDetlRid[index] = value;
   }
	
   /**
    * Sets the Index Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Index Code will be set to.
    */
   public final void setIndexCode( int index, String value )
   {
      assertUnsent();
      _IndexCode[index] = value;
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
    * Sets the Closing Value field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Closing Value will be set to.
    */
   public final void setClosingValue( int index, String value )
   {
      assertUnsent();
      _ClosingValue[index] = value;
   }
	
   /**
    * Sets the Hurdle Rate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Hurdle Rate will be set to.
    */
   public final void setHurdleRate( int index, String value )
   {
      assertUnsent();
      _HurdleRate[index] = value;
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
         requestBuffer.appendField( _MktIdxDetlVer[x] );
         requestBuffer.appendField( _MktIdxDetlRid[x] );
         requestBuffer.appendField( _IndexCode[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _ClosingValue[x] );
         requestBuffer.appendField( _HurdleRate[x] );
      }
   }

}

