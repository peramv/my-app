// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Shareholder - Fund Sponsor Agreement Update request.
 * For additional view information see <A HREF="../../../../viewspecs/ShrFndSpAgrUpd.doc">ShrFndSpAgrUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class ShrFndSpAgrUpdRequest extends IFastRequest implements Serializable
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
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Record ID member array.
    */
   private Integer[] _ShrFndSpnRId = new Integer[25];
            
   /**
    * Version Number member array.
    */
   private Integer[] _ShrFndSpnVer = new Integer[25];
            
   /**
    * Fund Sponsor / Group member array.
    */
   private String[] _FundGroup = new String[25];
            
   /**
    * Distribution Cooperation Agreement member array.
    */
   private String[] _DistCoopAgrmnt = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            

   /**
    * Constructs the ShrFndSpAgrUpdRequest object.
    * 
    */
   ShrFndSpAgrUpdRequest()
   {
      super ( 300 );
   }

   /**
    * Constructs the ShrFndSpAgrUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ShrFndSpAgrUpdRequest( String hostEncoding )
   {
      super ( 300, hostEncoding );
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
    * Sets the Record ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Record ID will be set to.
    */
   public final void setShrFndSpnRId( int index, Integer value )
   {
      assertUnsent();
      _ShrFndSpnRId[index] = value;
   }
	
   /**
    * Sets the Version Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version Number will be set to.
    */
   public final void setShrFndSpnVer( int index, Integer value )
   {
      assertUnsent();
      _ShrFndSpnVer[index] = value;
   }
	
   /**
    * Sets the Fund Sponsor / Group field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Sponsor / Group will be set to.
    */
   public final void setFundGroup( int index, String value )
   {
      assertUnsent();
      _FundGroup[index] = value;
   }
	
   /**
    * Sets the Distribution Cooperation Agreement field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distribution Cooperation Agreement will be set to.
    */
   public final void setDistCoopAgrmnt( int index, String value )
   {
      assertUnsent();
      _DistCoopAgrmnt[index] = value;
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
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _ShrFndSpnRId[x] );
         requestBuffer.appendField( _ShrFndSpnVer[x] );
         requestBuffer.appendField( _FundGroup[x] );
         requestBuffer.appendField( _DistCoopAgrmnt[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
      }
   }

}

