// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Protected Fund Set-Up Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/ProtFundMaint.doc">ProtFundMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class ProtFundMaintRequest extends IFastRequest implements Serializable
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
    * RunMode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Protected Fund Recid member array.
    */
   private Integer[] _ProtectFundRId = new Integer[25];
            
   /**
    * Fund member array.
    */
   private String[] _FundCode = new String[25];
            
   /**
    * Class member array.
    */
   private String[] _ClassCode = new String[25];
            
   /**
    * Start Date member array.
    */
   private Date[] _StartDate = new Date[25];
            
   /**
    * End Date member array.
    */
   private Date[] _EndDate = new Date[25];
            
   /**
    * Insurance Provider Code member array.
    */
   private String[] _InsurCode = new String[25];
            
   /**
    * Insurance Cost member array.
    */
   private String[] _InsurCost = new String[25];
            
   /**
    * Contract Gap Type 01, 02, 03 member array.
    */
   private Integer[] _ContractGapType = new Integer[25];
            
   /**
    * Number of resets allowed member array.
    */
   private Integer[] _NumResets = new Integer[25];
            
   /**
    * Maturity Years member array.
    */
   private Integer[] _MaturityYears = new Integer[25];
            
   /**
    * Version Number member array.
    */
   private Integer[] _VersionNum = new Integer[25];
            

   /**
    * Constructs the ProtFundMaintRequest object.
    * 
    */
   ProtFundMaintRequest()
   {
      super ( 238 );
   }

   /**
    * Constructs the ProtFundMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   ProtFundMaintRequest( String hostEncoding )
   {
      super ( 238, hostEncoding );
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
    * Sets the Protected Fund Recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Protected Fund Recid will be set to.
    */
   public final void setProtectFundRId( int index, Integer value )
   {
      assertUnsent();
      _ProtectFundRId[index] = value;
   }
	
   /**
    * Sets the Fund field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund will be set to.
    */
   public final void setFundCode( int index, String value )
   {
      assertUnsent();
      _FundCode[index] = value;
   }
	
   /**
    * Sets the Class field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Class will be set to.
    */
   public final void setClassCode( int index, String value )
   {
      assertUnsent();
      _ClassCode[index] = value;
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
    * Sets the Insurance Provider Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Insurance Provider Code will be set to.
    */
   public final void setInsurCode( int index, String value )
   {
      assertUnsent();
      _InsurCode[index] = value;
   }
	
   /**
    * Sets the Insurance Cost field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Insurance Cost will be set to.
    */
   public final void setInsurCost( int index, String value )
   {
      assertUnsent();
      _InsurCost[index] = value;
   }
	
   /**
    * Sets the Contract Gap Type 01, 02, 03 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Contract Gap Type 01, 02, 03 will be set to.
    */
   public final void setContractGapType( int index, Integer value )
   {
      assertUnsent();
      _ContractGapType[index] = value;
   }
	
   /**
    * Sets the Number of resets allowed field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Number of resets allowed will be set to.
    */
   public final void setNumResets( int index, Integer value )
   {
      assertUnsent();
      _NumResets[index] = value;
   }
	
   /**
    * Sets the Maturity Years field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Maturity Years will be set to.
    */
   public final void setMaturityYears( int index, Integer value )
   {
      assertUnsent();
      _MaturityYears[index] = value;
   }
	
   /**
    * Sets the Version Number field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version Number will be set to.
    */
   public final void setVersionNum( int index, Integer value )
   {
      assertUnsent();
      _VersionNum[index] = value;
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
         requestBuffer.appendField( _ProtectFundRId[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
         requestBuffer.appendField( _StartDate[x] );
         requestBuffer.appendField( _EndDate[x] );
         requestBuffer.appendField( _InsurCode[x] );
         requestBuffer.appendField( _InsurCost[x] );
         requestBuffer.appendField( _ContractGapType[x] );
         requestBuffer.appendField( _NumResets[x] );
         requestBuffer.appendField( _MaturityYears[x] );
         requestBuffer.appendField( _VersionNum[x] );
      }
   }

}

