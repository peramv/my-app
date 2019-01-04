// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Broker Remarks Update request.
 * For additional view information see <A HREF="../../../../viewspecs/BrkrRemarksUpd.doc">BrkrRemarksUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class BrkrRemarksUpdRequest extends IFastRequest implements Serializable
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
    * Agency Code member variable.
    */
   private String _AgencyCode = "";
            
   /**
    * Branch Code member variable.
    */
   private String _BranchCode = "";
            
   /**
    * Agent Code member variable.
    */
   private String _AgentCode = "";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Remarks Line 1 member array.
    */
   private String[] _Remarks1 = new String[25];
            
   /**
    * Remarks Line 2 member array.
    */
   private String[] _Remarks2 = new String[25];
            
   /**
    * Remarks Line 3 member array.
    */
   private String[] _Remarks3 = new String[25];
            
   /**
    * Remarks Line 4 member array.
    */
   private String[] _Remarks4 = new String[25];
            
   /**
    * Remarks Line 5 member array.
    */
   private String[] _Remarks5 = new String[25];
            
   /**
    * Remarks Line 6 member array.
    */
   private String[] _Remarks6 = new String[25];
            
   /**
    * Remarks Line 7 member array.
    */
   private String[] _Remarks7 = new String[25];
            
   /**
    * Remarks Line 8 member array.
    */
   private String[] _Remarks8 = new String[25];
            
   /**
    * Remarks Line 9 member array.
    */
   private String[] _Remarks9 = new String[25];
            
   /**
    * Remarks Line 10 member array.
    */
   private String[] _Remarks10 = new String[25];
            
   /**
    * Remarks recid member array.
    */
   private Integer[] _RemarksRId = new Integer[25];
            

   /**
    * Constructs the BrkrRemarksUpdRequest object.
    * 
    */
   BrkrRemarksUpdRequest()
   {
      super ( 316 );
   }

   /**
    * Constructs the BrkrRemarksUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   BrkrRemarksUpdRequest( String hostEncoding )
   {
      super ( 316, hostEncoding );
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
    * Sets the Agency Code field for the request.
    * 
    * @param value  Value that the Agency Code will be set to.
    */
   public final void setAgencyCode( String value )
   {
      assertUnsent();
      _AgencyCode = value;
   }
	
   /**
    * Sets the Branch Code field for the request.
    * 
    * @param value  Value that the Branch Code will be set to.
    */
   public final void setBranchCode( String value )
   {
      assertUnsent();
      _BranchCode = value;
   }
	
   /**
    * Sets the Agent Code field for the request.
    * 
    * @param value  Value that the Agent Code will be set to.
    */
   public final void setAgentCode( String value )
   {
      assertUnsent();
      _AgentCode = value;
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
    * Sets the Remarks Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 1 will be set to.
    */
   public final void setRemarks1( int index, String value )
   {
      assertUnsent();
      _Remarks1[index] = value;
   }
	
   /**
    * Sets the Remarks Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 2 will be set to.
    */
   public final void setRemarks2( int index, String value )
   {
      assertUnsent();
      _Remarks2[index] = value;
   }
	
   /**
    * Sets the Remarks Line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 3 will be set to.
    */
   public final void setRemarks3( int index, String value )
   {
      assertUnsent();
      _Remarks3[index] = value;
   }
	
   /**
    * Sets the Remarks Line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 4 will be set to.
    */
   public final void setRemarks4( int index, String value )
   {
      assertUnsent();
      _Remarks4[index] = value;
   }
	
   /**
    * Sets the Remarks Line 5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 5 will be set to.
    */
   public final void setRemarks5( int index, String value )
   {
      assertUnsent();
      _Remarks5[index] = value;
   }
	
   /**
    * Sets the Remarks Line 6 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 6 will be set to.
    */
   public final void setRemarks6( int index, String value )
   {
      assertUnsent();
      _Remarks6[index] = value;
   }
	
   /**
    * Sets the Remarks Line 7 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 7 will be set to.
    */
   public final void setRemarks7( int index, String value )
   {
      assertUnsent();
      _Remarks7[index] = value;
   }
	
   /**
    * Sets the Remarks Line 8 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 8 will be set to.
    */
   public final void setRemarks8( int index, String value )
   {
      assertUnsent();
      _Remarks8[index] = value;
   }
	
   /**
    * Sets the Remarks Line 9 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 9 will be set to.
    */
   public final void setRemarks9( int index, String value )
   {
      assertUnsent();
      _Remarks9[index] = value;
   }
	
   /**
    * Sets the Remarks Line 10 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks Line 10 will be set to.
    */
   public final void setRemarks10( int index, String value )
   {
      assertUnsent();
      _Remarks10[index] = value;
   }
	
   /**
    * Sets the Remarks recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks recid will be set to.
    */
   public final void setRemarksRId( int index, Integer value )
   {
      assertUnsent();
      _RemarksRId[index] = value;
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
      requestBuffer.appendField( _AgencyCode );
      requestBuffer.appendField( _BranchCode );
      requestBuffer.appendField( _AgentCode );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _Remarks1[x] );
         requestBuffer.appendField( _Remarks2[x] );
         requestBuffer.appendField( _Remarks3[x] );
         requestBuffer.appendField( _Remarks4[x] );
         requestBuffer.appendField( _Remarks5[x] );
         requestBuffer.appendField( _Remarks6[x] );
         requestBuffer.appendField( _Remarks7[x] );
         requestBuffer.appendField( _Remarks8[x] );
         requestBuffer.appendField( _Remarks9[x] );
         requestBuffer.appendField( _Remarks10[x] );
         requestBuffer.appendField( _RemarksRId[x] );
      }
   }

}

