// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fee Model Update request.
 * For additional view information see <A HREF="../../../../viewspecs/FeeModelUpd.doc">FeeModelUpd.doc</A>.
 * 
 * @author RTS Generated
 */
public class FeeModelUpdRequest extends IFastRequest implements Serializable
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
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode A, M, D member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Rec ID of the fee model record to be updated member array.
    */
   private Integer[] _FeeModelRecID = new Integer[25];
            
   /**
    * Version of the record to be updated member array.
    */
   private Integer[] _FeeModelVer = new Integer[25];
            
   /**
    * Fee model code member array.
    */
   private String[] _FeeModelCode = new String[25];
            
   /**
    * Fee model description member array.
    */
   private String[] _FeeModelDesc = new String[25];
            
   /**
    * Start date of fee model member array.
    */
   private Date[] _StartDate = new Date[25];
            
   /**
    * Stop date of fee model member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Fee model type member array.
    */
   private String[] _FeeModelType = new String[25];
            
   /**
    * Holding Company Code member array.
    */
   private String[] _HoldCoCode = new String[25];
            
   /**
    * Calculation Currency member array.
    */
   private String[] _CalCurrency = new String[25];
            
   /**
    * Calculation Rate Type member array.
    */
   private String[] _CalRateType = new String[25];
            
   /**
    * Eligible Fund By member array.
    */
   private String[] _FundGrpType = new String[25];
            
   /**
    * Model Aggregation Method member array.
    */
   private String[] _ModelAggrMethod = new String[25];
            
   /**
    * Fee Model Option member array.
    */
   private String[] _Program = new String[25];
            
   /**
    * Schedule member array.
    */
   private Integer[] _ScheduleFreqID = new Integer[25];
            
   /**
    * Fund Group member array.
    */
   private String[] _FundGroup = new String[25];
            
   /**
    * Fund Sponsor recid member array.
    */
   private Integer[] _FundSponsorRID = new Integer[25];
            
   /**
    * Fee Aggregation recid member array.
    */
   private Integer[] _FeeAggregationRID = new Integer[25];
            
   /**
    * Fund Sponsor Fee Model Version member array.
    */
   private Integer[] _FundSponsorVer = new Integer[25];
            
   /**
    * FeeOnFMO member array.
    */
   private Integer[] _FeeOnFMO = new Integer[25];
            

   /**
    * Constructs the FeeModelUpdRequest object.
    * 
    */
   FeeModelUpdRequest()
   {
      super ( 306 );
   }

   /**
    * Constructs the FeeModelUpdRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FeeModelUpdRequest( String hostEncoding )
   {
      super ( 306, hostEncoding );
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
    * Sets the Record Count for the repeatable request.
    * 
    * @param value    Value that the Record Count will be set to.
    */
   public final void setRepeatCount( int value )
   {
      _RepeatCount = value;
   }
         
   /**
    * Sets the Run Mode A, M, D field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Run Mode A, M, D will be set to.
    */
   public final void setRunMode( int index, String value )
   {
      assertUnsent();
      _RunMode[index] = value;
   }
	
   /**
    * Sets the Rec ID of the fee model record to be updated field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Rec ID of the fee model record to be updated will be set to.
    */
   public final void setFeeModelRecID( int index, Integer value )
   {
      assertUnsent();
      _FeeModelRecID[index] = value;
   }
	
   /**
    * Sets the Version of the record to be updated field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Version of the record to be updated will be set to.
    */
   public final void setFeeModelVer( int index, Integer value )
   {
      assertUnsent();
      _FeeModelVer[index] = value;
   }
	
   /**
    * Sets the Fee model code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fee model code will be set to.
    */
   public final void setFeeModelCode( int index, String value )
   {
      assertUnsent();
      _FeeModelCode[index] = value;
   }
	
   /**
    * Sets the Fee model description field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fee model description will be set to.
    */
   public final void setFeeModelDesc( int index, String value )
   {
      assertUnsent();
      _FeeModelDesc[index] = value;
   }
	
   /**
    * Sets the Start date of fee model field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Start date of fee model will be set to.
    */
   public final void setStartDate( int index, Date value )
   {
      assertUnsent();
      _StartDate[index] = value;
   }
	
   /**
    * Sets the Stop date of fee model field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop date of fee model will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
   }
	
   /**
    * Sets the Fee model type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fee model type will be set to.
    */
   public final void setFeeModelType( int index, String value )
   {
      assertUnsent();
      _FeeModelType[index] = value;
   }
	
   /**
    * Sets the Holding Company Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Holding Company Code will be set to.
    */
   public final void setHoldCoCode( int index, String value )
   {
      assertUnsent();
      _HoldCoCode[index] = value;
   }
	
   /**
    * Sets the Calculation Currency field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Calculation Currency will be set to.
    */
   public final void setCalCurrency( int index, String value )
   {
      assertUnsent();
      _CalCurrency[index] = value;
   }
	
   /**
    * Sets the Calculation Rate Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Calculation Rate Type will be set to.
    */
   public final void setCalRateType( int index, String value )
   {
      assertUnsent();
      _CalRateType[index] = value;
   }
	
   /**
    * Sets the Eligible Fund By field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Eligible Fund By will be set to.
    */
   public final void setFundGrpType( int index, String value )
   {
      assertUnsent();
      _FundGrpType[index] = value;
   }
	
   /**
    * Sets the Model Aggregation Method field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Model Aggregation Method will be set to.
    */
   public final void setModelAggrMethod( int index, String value )
   {
      assertUnsent();
      _ModelAggrMethod[index] = value;
   }
	
   /**
    * Sets the Fee Model Option field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fee Model Option will be set to.
    */
   public final void setProgram( int index, String value )
   {
      assertUnsent();
      _Program[index] = value;
   }
	
   /**
    * Sets the Schedule field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Schedule will be set to.
    */
   public final void setScheduleFreqID( int index, Integer value )
   {
      assertUnsent();
      _ScheduleFreqID[index] = value;
   }
	
   /**
    * Sets the Fund Group field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Group will be set to.
    */
   public final void setFundGroup( int index, String value )
   {
      assertUnsent();
      _FundGroup[index] = value;
   }
	
   /**
    * Sets the Fund Sponsor recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Sponsor recid will be set to.
    */
   public final void setFundSponsorRID( int index, Integer value )
   {
      assertUnsent();
      _FundSponsorRID[index] = value;
   }
	
   /**
    * Sets the Fee Aggregation recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fee Aggregation recid will be set to.
    */
   public final void setFeeAggregationRID( int index, Integer value )
   {
      assertUnsent();
      _FeeAggregationRID[index] = value;
   }
	
   /**
    * Sets the Fund Sponsor Fee Model Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Sponsor Fee Model Version will be set to.
    */
   public final void setFundSponsorVer( int index, Integer value )
   {
      assertUnsent();
      _FundSponsorVer[index] = value;
   }
	
   /**
    * Sets the FeeOnFMO field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FeeOnFMO will be set to.
    */
   public final void setFeeOnFMO( int index, Integer value )
   {
      assertUnsent();
      _FeeOnFMO[index] = value;
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
      encodeOverrideRepeatsField( requestBuffer );
      encodeNextKeyField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _FeeModelRecID[x] );
         requestBuffer.appendField( _FeeModelVer[x] );
         requestBuffer.appendField( _FeeModelCode[x] );
         requestBuffer.appendField( _FeeModelDesc[x] );
         requestBuffer.appendField( _StartDate[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _FeeModelType[x] );
         requestBuffer.appendField( _HoldCoCode[x] );
         requestBuffer.appendField( _CalCurrency[x] );
         requestBuffer.appendField( _CalRateType[x] );
         requestBuffer.appendField( _FundGrpType[x] );
         requestBuffer.appendField( _ModelAggrMethod[x] );
         requestBuffer.appendField( _Program[x] );
         requestBuffer.appendField( _ScheduleFreqID[x] );
         requestBuffer.appendField( _FundGroup[x] );
         requestBuffer.appendField( _FundSponsorRID[x] );
         requestBuffer.appendField( _FeeAggregationRID[x] );
         requestBuffer.appendField( _FundSponsorVer[x] );
         requestBuffer.appendField( _FeeOnFMO[x] );
      }
   }

}

