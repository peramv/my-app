// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Cheque Detail Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/ChqDetlMain.doc">ChqDetlMain.doc</A>.
 * 
 * @author RTS Generated
 */
public class ChqDetlMainRequest extends IFastRequest implements Serializable
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
    * ChqDetlUUID member array.
    */
   private String[] _ChqDetlUUID = new String[25];
            
   /**
    * Cheque Status member array.
    */
   private String[] _ChqStat = new String[25];
            
   /**
    * Unclaim Stage member array.
    */
   private String[] _UnclmStage = new String[25];
            
   /**
    * StageDate member array.
    */
   private Date[] _StageDate = new Date[25];
            
   /**
    * Unclaim Remit Date member array.
    */
   private Date[] _UnclmRemitDate = new Date[25];
            
   /**
    * Comments member array.
    */
   private String[] _Comments = new String[25];
            
   /**
    * Version member array.
    */
   private Integer[] _Version = new Integer[25];
            
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Indicates if stage was overridden member array.
    */
   private String[] _StageAssignBy = new String[25];
            

   /**
    * Constructs the ChqDetlMainRequest object.
    * 
    */
   ChqDetlMainRequest()
   {
      super ( 391 );
   }

   /**
    * Constructs the ChqDetlMainRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ChqDetlMainRequest( String hostEncoding )
   {
      super ( 391, hostEncoding );
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
    * Sets the ChqDetlUUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ChqDetlUUID will be set to.
    */
   public final void setChqDetlUUID( int index, String value )
   {
      assertUnsent();
      _ChqDetlUUID[index] = value;
   }
	
   /**
    * Sets the Cheque Status field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Cheque Status will be set to.
    */
   public final void setChqStat( int index, String value )
   {
      assertUnsent();
      _ChqStat[index] = value;
   }
	
   /**
    * Sets the Unclaim Stage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Unclaim Stage will be set to.
    */
   public final void setUnclmStage( int index, String value )
   {
      assertUnsent();
      _UnclmStage[index] = value;
   }
	
   /**
    * Sets the StageDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the StageDate will be set to.
    */
   public final void setStageDate( int index, Date value )
   {
      assertUnsent();
      _StageDate[index] = value;
   }
	
   /**
    * Sets the Unclaim Remit Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Unclaim Remit Date will be set to.
    */
   public final void setUnclmRemitDate( int index, Date value )
   {
      assertUnsent();
      _UnclmRemitDate[index] = value;
   }
	
   /**
    * Sets the Comments field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Comments will be set to.
    */
   public final void setComments( int index, String value )
   {
      assertUnsent();
      _Comments[index] = value;
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
         requestBuffer.appendField( _ChqDetlUUID[x] );
         requestBuffer.appendField( _ChqStat[x] );
         requestBuffer.appendField( _UnclmStage[x] );
         requestBuffer.appendField( _StageDate[x] );
         requestBuffer.appendField( _UnclmRemitDate[x] );
         requestBuffer.appendField( _Comments[x] );
         requestBuffer.appendField( _Version[x] );
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _StageAssignBy[x] );
      }
   }

}

