// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Update Default Allocations request.
 * For additional view information see <A HREF="../../../../viewspecs/UpDefAllocations.doc">UpDefAllocations.doc</A>.
 * 
 * @author RTS Generated
 */
public class UpDefAllocationsRequest extends IFastRequest implements Serializable
{

   /**
    * Shareholder Number member variable.
    */
   private String _ShrNum = "0";
            
   /**
    * Session ID member variable.
    */
   private String _SessionId = "";
            
   /**
    * User ID member variable.
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
    * UpdateAMSPAC flag member variable.
    */
   private Boolean _UpdateAMSPAC = new Boolean(false);
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[50];
            
   /**
    * TransType member array.
    */
   private String[] _TransType = new String[50];
            
   /**
    * Level member array.
    */
   private Integer[] _Level = new Integer[50];
            
   /**
    * AccountNum member array.
    */
   private String[] _AccountNum = new String[50];
            
   /**
    * FundCode member array.
    */
   private String[] _FundCode = new String[50];
            
   /**
    * ClassCode member array.
    */
   private String[] _ClassCode = new String[50];
            
   /**
    * Distrib-Detl recid member array.
    */
   private Integer[] _DistribDetlRid = new Integer[50];
            
   /**
    * Version Number member array.
    */
   private Integer[] _VersionNum = new Integer[50];
            
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[50];
            
   /**
    * Percentage member array.
    */
   private String[] _Percentage = new String[50];
            
   /**
    * Fund Group member array.
    */
   private String[] _FundGroup = new String[50];
            
   /**
    * Rebalance Percent member array.
    */
   private String[] _RebalPrcnt = new String[50];
            
   /**
    * Currency for AMS member array.
    */
   private String[] _AMSCurrency = new String[50];
            
   /**
    * Commission amount if Commission Type is flat OR commission percentage if commission type is percent member array.
    */
   private String[] _FELComm = new String[50];
            
   /**
    * Commission Type (Flat or Percent) member array.
    */
   private Boolean[] _FELCommType = new Boolean[50];
            

   /**
    * Constructs the UpDefAllocationsRequest object.
    * 
    */
   UpDefAllocationsRequest()
   {
      super ( 89 );
   }

   /**
    * Constructs the UpDefAllocationsRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   UpDefAllocationsRequest( String hostEncoding )
   {
      super ( 89, hostEncoding );
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
    * Sets the User ID field for the request.
    * 
    * @param value  Value that the User ID will be set to.
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
    * Sets the UpdateAMSPAC flag field for the request.
    * 
    * @param value  Value that the UpdateAMSPAC flag will be set to.
    */
   public final void setUpdateAMSPAC( Boolean value )
   {
      assertUnsent();
      _UpdateAMSPAC = value;
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
    * Sets the TransType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the TransType will be set to.
    */
   public final void setTransType( int index, String value )
   {
      assertUnsent();
      _TransType[index] = value;
   }
	
   /**
    * Sets the Level field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Level will be set to.
    */
   public final void setLevel( int index, Integer value )
   {
      assertUnsent();
      _Level[index] = value;
   }
	
   /**
    * Sets the AccountNum field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AccountNum will be set to.
    */
   public final void setAccountNum( int index, String value )
   {
      assertUnsent();
      _AccountNum[index] = value;
   }
	
   /**
    * Sets the FundCode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FundCode will be set to.
    */
   public final void setFundCode( int index, String value )
   {
      assertUnsent();
      _FundCode[index] = value;
   }
	
   /**
    * Sets the ClassCode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ClassCode will be set to.
    */
   public final void setClassCode( int index, String value )
   {
      assertUnsent();
      _ClassCode[index] = value;
   }
	
   /**
    * Sets the Distrib-Detl recid field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Distrib-Detl recid will be set to.
    */
   public final void setDistribDetlRid( int index, Integer value )
   {
      assertUnsent();
      _DistribDetlRid[index] = value;
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
    * Sets the Percentage field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Percentage will be set to.
    */
   public final void setPercentage( int index, String value )
   {
      assertUnsent();
      _Percentage[index] = value;
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
    * Sets the Rebalance Percent field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Rebalance Percent will be set to.
    */
   public final void setRebalPrcnt( int index, String value )
   {
      assertUnsent();
      _RebalPrcnt[index] = value;
   }
	
   /**
    * Sets the Currency for AMS field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Currency for AMS will be set to.
    */
   public final void setAMSCurrency( int index, String value )
   {
      assertUnsent();
      _AMSCurrency[index] = value;
   }
	
   /**
    * Sets the Commission amount if Commission Type is flat OR commission percentage if commission type is percent field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission amount if Commission Type is flat OR commission percentage if commission type is percent will be set to.
    */
   public final void setFELComm( int index, String value )
   {
      assertUnsent();
      _FELComm[index] = value;
   }
	
   /**
    * Sets the Commission Type (Flat or Percent) field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Commission Type (Flat or Percent) will be set to.
    */
   public final void setFELCommType( int index, Boolean value )
   {
      assertUnsent();
      _FELCommType[index] = value;
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
      requestBuffer.appendField( _ShrNum );
      requestBuffer.appendField( _SessionId );
      requestBuffer.appendField( _User_Id );
      encodeLanguageCodeField( _LanguageCode, requestBuffer );
      requestBuffer.appendField( _CompanyId );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( _UpdateAMSPAC );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _TransType[x] );
         requestBuffer.appendField( _Level[x] );
         requestBuffer.appendField( _AccountNum[x] );
         requestBuffer.appendField( _FundCode[x] );
         requestBuffer.appendField( _ClassCode[x] );
         requestBuffer.appendField( _DistribDetlRid[x] );
         requestBuffer.appendField( _VersionNum[x] );
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _Percentage[x] );
         requestBuffer.appendField( _FundGroup[x] );
         requestBuffer.appendField( _RebalPrcnt[x] );
         requestBuffer.appendField( _AMSCurrency[x] );
         requestBuffer.appendField( _FELComm[x] );
         requestBuffer.appendField( _FELCommType[x] );
      }
   }

}

