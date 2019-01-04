// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Review Detail Update request.
 * For additional view information see <A HREF="../../../../viewspecs/ReviewDetlUpd.doc">ReviewDetlUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class ReviewDetlUpdRequest extends IFastRequest implements Serializable
{

   /**
    * Session ID member variable.
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
    * Account Nuimber member variable.
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
    * Acct Review Recid member array.
    */
   private Integer[] _AcctReviewRId = new Integer[25];
            
   /**
    * Scheduled Review Date member array.
    */
   private Date[] _SchedReviewDate = new Date[25];
            
   /**
    * Actual Review Date member array.
    */
   private Date[] _ActualReviewDate = new Date[25];
            
   /**
    * Comments Line 1 member array.
    */
   private String[] _Comments1 = new String[25];
            
   /**
    * Comments Line 2 member array.
    */
   private String[] _Comments2 = new String[25];
            
   /**
    * Comments Line 3 member array.
    */
   private String[] _Comments3 = new String[25];
            

   /**
    * Constructs the ReviewDetlUpdRequest object.
    * 
    */
   ReviewDetlUpdRequest()
   {
      super ( 205 );
   }

   /**
    * Constructs the ReviewDetlUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ReviewDetlUpdRequest( String hostEncoding )
   {
      super ( 205, hostEncoding );
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
    * Sets the Account Nuimber field for the request.
    * 
    * @param value  Value that the Account Nuimber will be set to.
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
    * Sets the Acct Review Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Acct Review Recid will be set to.
    */
   public final void setAcctReviewRId( int index, Integer value )
   {
      assertUnsent();
      _AcctReviewRId[index] = value;
   }
	
   /**
    * Sets the Scheduled Review Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Scheduled Review Date will be set to.
    */
   public final void setSchedReviewDate( int index, Date value )
   {
      assertUnsent();
      _SchedReviewDate[index] = value;
   }
	
   /**
    * Sets the Actual Review Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Actual Review Date will be set to.
    */
   public final void setActualReviewDate( int index, Date value )
   {
      assertUnsent();
      _ActualReviewDate[index] = value;
   }
	
   /**
    * Sets the Comments Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Comments Line 1 will be set to.
    */
   public final void setComments1( int index, String value )
   {
      assertUnsent();
      _Comments1[index] = value;
   }
	
   /**
    * Sets the Comments Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Comments Line 2 will be set to.
    */
   public final void setComments2( int index, String value )
   {
      assertUnsent();
      _Comments2[index] = value;
   }
	
   /**
    * Sets the Comments Line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Comments Line 3 will be set to.
    */
   public final void setComments3( int index, String value )
   {
      assertUnsent();
      _Comments3[index] = value;
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
      requestBuffer.appendField( _AccountNum );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _AcctReviewRId[x] );
         requestBuffer.appendField( _SchedReviewDate[x] );
         requestBuffer.appendField( _ActualReviewDate[x] );
         requestBuffer.appendField( _Comments1[x] );
         requestBuffer.appendField( _Comments2[x] );
         requestBuffer.appendField( _Comments3[x] );
      }
   }

}

