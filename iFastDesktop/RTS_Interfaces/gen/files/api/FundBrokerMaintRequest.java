// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Fund Broker Maintenance request.
 * For additional view information see <A HREF="../../../../viewspecs/FundBrokerMaint.doc">FundBrokerMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class FundBrokerMaintRequest extends IFastRequest implements Serializable
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
   private String _CompanyID = "";
            
            
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * Fund Broker Code member array.
    */
   private String[] _FundBrokerCode = new String[25];
            
   /**
    * Remarks member array.
    */
   private String[] _Remarks = new String[25];
            
   /**
    * Price Type member array.
    */
   private String[] _PriceType = new String[25];
            
   /**
    * Routing Type member array.
    */
   private String[] _RoutingType = new String[25];
            
   /**
    * PUEV Capable member array.
    */
   private Boolean[] _PUEVCapable = new Boolean[25];
            
   /**
    * Clearing Method member array.
    */
   private String[] _ClearingMethod = new String[25];
            
   /**
    * Stop Date member array.
    */
   private Date[] _StopDate = new Date[25];
            
   /**
    * Effective Date member array.
    */
   private Date[] _EffectiveDate = new Date[25];
            
   /**
    * Fund Broker Version member array.
    */
   private Integer[] _FundBrokerVersion = new Integer[25];
            
   /**
    * Fund Broker Record ID member array.
    */
   private Integer[] _FundBrokerRId = new Integer[25];
            
   /**
    * Fund Broker Entity ID member array.
    */
   private String[] _FundBrokerEntityID = new String[25];
            
   /**
    * Where Use Fund Broker Record ID member array.
    */
   private Integer[] _WhereUseFundBrokerRId = new Integer[25];
            
   /**
    * Where Use Fund Broker Version member array.
    */
   private Integer[] _WhereUseFundBrokerVersion = new Integer[25];
            
   /**
    * Addr ID member array.
    */
   private String[] _AddrID = new String[25];
            
   /**
    * Entity Addr Version member array.
    */
   private Integer[] _EntityAddrVersion = new Integer[25];
            
   /**
    * Entity Addr Xref Record ID member array.
    */
   private Integer[] _EntityAddrXrefRId = new Integer[25];
            
   /**
    * Entity Addr Xref Version member array.
    */
   private Integer[] _EntityAddrXrefVer = new Integer[25];
            
   /**
    * Addr Line 1 member array.
    */
   private String[] _AddrLine1 = new String[25];
            
   /**
    * Addr Line 2 member array.
    */
   private String[] _AddrLine2 = new String[25];
            
   /**
    * Addr Line 3 member array.
    */
   private String[] _AddrLine3 = new String[25];
            
   /**
    * Addr Line 4 member array.
    */
   private String[] _AddrLine4 = new String[25];
            
   /**
    * Province member array.
    */
   private String[] _Province = new String[25];
            
   /**
    * Country member array.
    */
   private String[] _Country = new String[25];
            
   /**
    * Postal Code member array.
    */
   private String[] _PostalCode = new String[25];
            
   /**
    * Where Use Primary Contact Record ID member array.
    */
   private Integer[] _WhereUseContact1RId = new Integer[25];
            
   /**
    * Where Use Primary Contact Version member array.
    */
   private Integer[] _WhereUsecontact1Version = new Integer[25];
            
   /**
    * Primary Contact Entity ID member array.
    */
   private String[] _Contact1EntityID = new String[25];
            
   /**
    * Where Use Secondary Contact Record ID member array.
    */
   private Integer[] _WhereUseContact2RId = new Integer[25];
            
   /**
    * Where Use Secondary Contact Version member array.
    */
   private Integer[] _WhereUseContact2Version = new Integer[25];
            
   /**
    * Secondary Contact Entity ID member array.
    */
   private String[] _Contact2EntityId = new String[25];
            
   /**
    * Set All Funds Investro Capable Indicator member array.
    */
   private Boolean[] _SetFundToInvestr = new Boolean[25];
            
   /**
    * Fund Broker Offset Time member array.
    */
   private Integer[] _FundBrokerOffsetTime = new Integer[25];
            
   /**
    * Fund Broker Portfolio member array.
    */
   private String[] _FbPortfolio = new String[25];
            
   /**
    * Fund Broker Branch member array.
    */
   private String[] _FbBranch = new String[25];
            
   /**
    * Account Servicer member array.
    */
   private String[] _AcctServicer = new String[25];
            
   /**
    * Fund Broker SettleType member array.
    */
   private String[] _FbSettleType = new String[25];
            
   /**
    * Fund Broker AcctDesig member array.
    */
   private String[] _FbAcctDesig = new String[25];
            
   /**
    * Fund Broker Agent member array.
    */
   private String[] _FbAgent = new String[25];
            
   /**
    * Reg Account member array.
    */
   private String[] _RegAcct = new String[25];
            
   /**
    * Fund Broker Dealer member array.
    */
   private String[] _FbDealer = new String[25];
            
   /**
    * Reg Name member array.
    */
   private String[] _RegName = new String[25];
            
   /**
    * Fund Broker Template member array.
    */
   private String[] _FbTemplate = new String[25];
            
   /**
    * Reg AddrID member array.
    */
   private String[] _RegAddrID = new String[25];
            
   /**
    * Reg Entity Addr Version member array.
    */
   private Integer[] _RegEntityAddrVersion = new Integer[25];
            
   /**
    * Reg Entity Addr Xref RId member array.
    */
   private Integer[] _RegEntityAddrXrefRId = new Integer[25];
            
   /**
    * Reg Entity Addr Xref Ver member array.
    */
   private Integer[] _RegEntityAddrXrefVer = new Integer[25];
            
   /**
    * Reg Addr Line 1 member array.
    */
   private String[] _RegAddrLine1 = new String[25];
            
   /**
    * Reg Addr Line 2 member array.
    */
   private String[] _RegAddrLine2 = new String[25];
            
   /**
    * Reg Addr Line 3 member array.
    */
   private String[] _RegAddrLine3 = new String[25];
            
   /**
    * Reg Addr Line 4 member array.
    */
   private String[] _RegAddrLine4 = new String[25];
            
   /**
    * Reg Province member array.
    */
   private String[] _RegProvince = new String[25];
            
   /**
    * Reg Country member array.
    */
   private String[] _RegCountry = new String[25];
            
   /**
    * Reg Postal Code member array.
    */
   private String[] _RegPostalCode = new String[25];
            

   /**
    * Constructs the FundBrokerMaintRequest object.
    * 
    */
   FundBrokerMaintRequest()
   {
      super ( 320 );
   }

   /**
    * Constructs the FundBrokerMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   FundBrokerMaintRequest( String hostEncoding )
   {
      super ( 320, hostEncoding );
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
   public final void setCompanyID( String value )
   {
      assertUnsent();
      _CompanyID = value;
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
    * Sets the Fund Broker Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Code will be set to.
    */
   public final void setFundBrokerCode( int index, String value )
   {
      assertUnsent();
      _FundBrokerCode[index] = value;
   }
	
   /**
    * Sets the Remarks field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remarks will be set to.
    */
   public final void setRemarks( int index, String value )
   {
      assertUnsent();
      _Remarks[index] = value;
   }
	
   /**
    * Sets the Price Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Price Type will be set to.
    */
   public final void setPriceType( int index, String value )
   {
      assertUnsent();
      _PriceType[index] = value;
   }
	
   /**
    * Sets the Routing Type field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Routing Type will be set to.
    */
   public final void setRoutingType( int index, String value )
   {
      assertUnsent();
      _RoutingType[index] = value;
   }
	
   /**
    * Sets the PUEV Capable field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the PUEV Capable will be set to.
    */
   public final void setPUEVCapable( int index, Boolean value )
   {
      assertUnsent();
      _PUEVCapable[index] = value;
   }
	
   /**
    * Sets the Clearing Method field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Clearing Method will be set to.
    */
   public final void setClearingMethod( int index, String value )
   {
      assertUnsent();
      _ClearingMethod[index] = value;
   }
	
   /**
    * Sets the Stop Date field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Stop Date will be set to.
    */
   public final void setStopDate( int index, Date value )
   {
      assertUnsent();
      _StopDate[index] = value;
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
    * Sets the Fund Broker Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Version will be set to.
    */
   public final void setFundBrokerVersion( int index, Integer value )
   {
      assertUnsent();
      _FundBrokerVersion[index] = value;
   }
	
   /**
    * Sets the Fund Broker Record ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Record ID will be set to.
    */
   public final void setFundBrokerRId( int index, Integer value )
   {
      assertUnsent();
      _FundBrokerRId[index] = value;
   }
	
   /**
    * Sets the Fund Broker Entity ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Entity ID will be set to.
    */
   public final void setFundBrokerEntityID( int index, String value )
   {
      assertUnsent();
      _FundBrokerEntityID[index] = value;
   }
	
   /**
    * Sets the Where Use Fund Broker Record ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Where Use Fund Broker Record ID will be set to.
    */
   public final void setWhereUseFundBrokerRId( int index, Integer value )
   {
      assertUnsent();
      _WhereUseFundBrokerRId[index] = value;
   }
	
   /**
    * Sets the Where Use Fund Broker Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Where Use Fund Broker Version will be set to.
    */
   public final void setWhereUseFundBrokerVersion( int index, Integer value )
   {
      assertUnsent();
      _WhereUseFundBrokerVersion[index] = value;
   }
	
   /**
    * Sets the Addr ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Addr ID will be set to.
    */
   public final void setAddrID( int index, String value )
   {
      assertUnsent();
      _AddrID[index] = value;
   }
	
   /**
    * Sets the Entity Addr Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Addr Version will be set to.
    */
   public final void setEntityAddrVersion( int index, Integer value )
   {
      assertUnsent();
      _EntityAddrVersion[index] = value;
   }
	
   /**
    * Sets the Entity Addr Xref Record ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Addr Xref Record ID will be set to.
    */
   public final void setEntityAddrXrefRId( int index, Integer value )
   {
      assertUnsent();
      _EntityAddrXrefRId[index] = value;
   }
	
   /**
    * Sets the Entity Addr Xref Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Entity Addr Xref Version will be set to.
    */
   public final void setEntityAddrXrefVer( int index, Integer value )
   {
      assertUnsent();
      _EntityAddrXrefVer[index] = value;
   }
	
   /**
    * Sets the Addr Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Addr Line 1 will be set to.
    */
   public final void setAddrLine1( int index, String value )
   {
      assertUnsent();
      _AddrLine1[index] = value;
   }
	
   /**
    * Sets the Addr Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Addr Line 2 will be set to.
    */
   public final void setAddrLine2( int index, String value )
   {
      assertUnsent();
      _AddrLine2[index] = value;
   }
	
   /**
    * Sets the Addr Line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Addr Line 3 will be set to.
    */
   public final void setAddrLine3( int index, String value )
   {
      assertUnsent();
      _AddrLine3[index] = value;
   }
	
   /**
    * Sets the Addr Line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Addr Line 4 will be set to.
    */
   public final void setAddrLine4( int index, String value )
   {
      assertUnsent();
      _AddrLine4[index] = value;
   }
	
   /**
    * Sets the Province field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Province will be set to.
    */
   public final void setProvince( int index, String value )
   {
      assertUnsent();
      _Province[index] = value;
   }
	
   /**
    * Sets the Country field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Country will be set to.
    */
   public final void setCountry( int index, String value )
   {
      assertUnsent();
      _Country[index] = value;
   }
	
   /**
    * Sets the Postal Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Postal Code will be set to.
    */
   public final void setPostalCode( int index, String value )
   {
      assertUnsent();
      _PostalCode[index] = value;
   }
	
   /**
    * Sets the Where Use Primary Contact Record ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Where Use Primary Contact Record ID will be set to.
    */
   public final void setWhereUseContact1RId( int index, Integer value )
   {
      assertUnsent();
      _WhereUseContact1RId[index] = value;
   }
	
   /**
    * Sets the Where Use Primary Contact Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Where Use Primary Contact Version will be set to.
    */
   public final void setWhereUsecontact1Version( int index, Integer value )
   {
      assertUnsent();
      _WhereUsecontact1Version[index] = value;
   }
	
   /**
    * Sets the Primary Contact Entity ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Primary Contact Entity ID will be set to.
    */
   public final void setContact1EntityID( int index, String value )
   {
      assertUnsent();
      _Contact1EntityID[index] = value;
   }
	
   /**
    * Sets the Where Use Secondary Contact Record ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Where Use Secondary Contact Record ID will be set to.
    */
   public final void setWhereUseContact2RId( int index, Integer value )
   {
      assertUnsent();
      _WhereUseContact2RId[index] = value;
   }
	
   /**
    * Sets the Where Use Secondary Contact Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Where Use Secondary Contact Version will be set to.
    */
   public final void setWhereUseContact2Version( int index, Integer value )
   {
      assertUnsent();
      _WhereUseContact2Version[index] = value;
   }
	
   /**
    * Sets the Secondary Contact Entity ID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Secondary Contact Entity ID will be set to.
    */
   public final void setContact2EntityId( int index, String value )
   {
      assertUnsent();
      _Contact2EntityId[index] = value;
   }
	
   /**
    * Sets the Set All Funds Investro Capable Indicator field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Set All Funds Investro Capable Indicator will be set to.
    */
   public final void setSetFundToInvestr( int index, Boolean value )
   {
      assertUnsent();
      _SetFundToInvestr[index] = value;
   }
	
   /**
    * Sets the Fund Broker Offset Time field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Offset Time will be set to.
    */
   public final void setFundBrokerOffsetTime( int index, Integer value )
   {
      assertUnsent();
      _FundBrokerOffsetTime[index] = value;
   }
	
   /**
    * Sets the Fund Broker Portfolio field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Portfolio will be set to.
    */
   public final void setFbPortfolio( int index, String value )
   {
      assertUnsent();
      _FbPortfolio[index] = value;
   }
	
   /**
    * Sets the Fund Broker Branch field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Branch will be set to.
    */
   public final void setFbBranch( int index, String value )
   {
      assertUnsent();
      _FbBranch[index] = value;
   }
	
   /**
    * Sets the Account Servicer field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Account Servicer will be set to.
    */
   public final void setAcctServicer( int index, String value )
   {
      assertUnsent();
      _AcctServicer[index] = value;
   }
	
   /**
    * Sets the Fund Broker SettleType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker SettleType will be set to.
    */
   public final void setFbSettleType( int index, String value )
   {
      assertUnsent();
      _FbSettleType[index] = value;
   }
	
   /**
    * Sets the Fund Broker AcctDesig field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker AcctDesig will be set to.
    */
   public final void setFbAcctDesig( int index, String value )
   {
      assertUnsent();
      _FbAcctDesig[index] = value;
   }
	
   /**
    * Sets the Fund Broker Agent field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Agent will be set to.
    */
   public final void setFbAgent( int index, String value )
   {
      assertUnsent();
      _FbAgent[index] = value;
   }
	
   /**
    * Sets the Reg Account field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Account will be set to.
    */
   public final void setRegAcct( int index, String value )
   {
      assertUnsent();
      _RegAcct[index] = value;
   }
	
   /**
    * Sets the Fund Broker Dealer field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Dealer will be set to.
    */
   public final void setFbDealer( int index, String value )
   {
      assertUnsent();
      _FbDealer[index] = value;
   }
	
   /**
    * Sets the Reg Name field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Name will be set to.
    */
   public final void setRegName( int index, String value )
   {
      assertUnsent();
      _RegName[index] = value;
   }
	
   /**
    * Sets the Fund Broker Template field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Fund Broker Template will be set to.
    */
   public final void setFbTemplate( int index, String value )
   {
      assertUnsent();
      _FbTemplate[index] = value;
   }
	
   /**
    * Sets the Reg AddrID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg AddrID will be set to.
    */
   public final void setRegAddrID( int index, String value )
   {
      assertUnsent();
      _RegAddrID[index] = value;
   }
	
   /**
    * Sets the Reg Entity Addr Version field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Entity Addr Version will be set to.
    */
   public final void setRegEntityAddrVersion( int index, Integer value )
   {
      assertUnsent();
      _RegEntityAddrVersion[index] = value;
   }
	
   /**
    * Sets the Reg Entity Addr Xref RId field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Entity Addr Xref RId will be set to.
    */
   public final void setRegEntityAddrXrefRId( int index, Integer value )
   {
      assertUnsent();
      _RegEntityAddrXrefRId[index] = value;
   }
	
   /**
    * Sets the Reg Entity Addr Xref Ver field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Entity Addr Xref Ver will be set to.
    */
   public final void setRegEntityAddrXrefVer( int index, Integer value )
   {
      assertUnsent();
      _RegEntityAddrXrefVer[index] = value;
   }
	
   /**
    * Sets the Reg Addr Line 1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Addr Line 1 will be set to.
    */
   public final void setRegAddrLine1( int index, String value )
   {
      assertUnsent();
      _RegAddrLine1[index] = value;
   }
	
   /**
    * Sets the Reg Addr Line 2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Addr Line 2 will be set to.
    */
   public final void setRegAddrLine2( int index, String value )
   {
      assertUnsent();
      _RegAddrLine2[index] = value;
   }
	
   /**
    * Sets the Reg Addr Line 3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Addr Line 3 will be set to.
    */
   public final void setRegAddrLine3( int index, String value )
   {
      assertUnsent();
      _RegAddrLine3[index] = value;
   }
	
   /**
    * Sets the Reg Addr Line 4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Addr Line 4 will be set to.
    */
   public final void setRegAddrLine4( int index, String value )
   {
      assertUnsent();
      _RegAddrLine4[index] = value;
   }
	
   /**
    * Sets the Reg Province field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Province will be set to.
    */
   public final void setRegProvince( int index, String value )
   {
      assertUnsent();
      _RegProvince[index] = value;
   }
	
   /**
    * Sets the Reg Country field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Country will be set to.
    */
   public final void setRegCountry( int index, String value )
   {
      assertUnsent();
      _RegCountry[index] = value;
   }
	
   /**
    * Sets the Reg Postal Code field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Reg Postal Code will be set to.
    */
   public final void setRegPostalCode( int index, String value )
   {
      assertUnsent();
      _RegPostalCode[index] = value;
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
      requestBuffer.appendField( _CompanyID );
      encodeTrackField( requestBuffer );
      encodeActivityField( requestBuffer );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _FundBrokerCode[x] );
         requestBuffer.appendField( _Remarks[x] );
         requestBuffer.appendField( _PriceType[x] );
         requestBuffer.appendField( _RoutingType[x] );
         requestBuffer.appendField( _PUEVCapable[x] );
         requestBuffer.appendField( _ClearingMethod[x] );
         requestBuffer.appendField( _StopDate[x] );
         requestBuffer.appendField( _EffectiveDate[x] );
         requestBuffer.appendField( _FundBrokerVersion[x] );
         requestBuffer.appendField( _FundBrokerRId[x] );
         requestBuffer.appendField( _FundBrokerEntityID[x] );
         requestBuffer.appendField( _WhereUseFundBrokerRId[x] );
         requestBuffer.appendField( _WhereUseFundBrokerVersion[x] );
         requestBuffer.appendField( _AddrID[x] );
         requestBuffer.appendField( _EntityAddrVersion[x] );
         requestBuffer.appendField( _EntityAddrXrefRId[x] );
         requestBuffer.appendField( _EntityAddrXrefVer[x] );
         requestBuffer.appendField( _AddrLine1[x] );
         requestBuffer.appendField( _AddrLine2[x] );
         requestBuffer.appendField( _AddrLine3[x] );
         requestBuffer.appendField( _AddrLine4[x] );
         requestBuffer.appendField( _Province[x] );
         requestBuffer.appendField( _Country[x] );
         requestBuffer.appendField( _PostalCode[x] );
         requestBuffer.appendField( _WhereUseContact1RId[x] );
         requestBuffer.appendField( _WhereUsecontact1Version[x] );
         requestBuffer.appendField( _Contact1EntityID[x] );
         requestBuffer.appendField( _WhereUseContact2RId[x] );
         requestBuffer.appendField( _WhereUseContact2Version[x] );
         requestBuffer.appendField( _Contact2EntityId[x] );
         requestBuffer.appendField( _SetFundToInvestr[x] );
         requestBuffer.appendField( _FundBrokerOffsetTime[x] );
         requestBuffer.appendField( _FbPortfolio[x] );
         requestBuffer.appendField( _FbBranch[x] );
         requestBuffer.appendField( _AcctServicer[x] );
         requestBuffer.appendField( _FbSettleType[x] );
         requestBuffer.appendField( _FbAcctDesig[x] );
         requestBuffer.appendField( _FbAgent[x] );
         requestBuffer.appendField( _RegAcct[x] );
         requestBuffer.appendField( _FbDealer[x] );
         requestBuffer.appendField( _RegName[x] );
         requestBuffer.appendField( _FbTemplate[x] );
         requestBuffer.appendField( _RegAddrID[x] );
         requestBuffer.appendField( _RegEntityAddrVersion[x] );
         requestBuffer.appendField( _RegEntityAddrXrefRId[x] );
         requestBuffer.appendField( _RegEntityAddrXrefVer[x] );
         requestBuffer.appendField( _RegAddrLine1[x] );
         requestBuffer.appendField( _RegAddrLine2[x] );
         requestBuffer.appendField( _RegAddrLine3[x] );
         requestBuffer.appendField( _RegAddrLine4[x] );
         requestBuffer.appendField( _RegProvince[x] );
         requestBuffer.appendField( _RegCountry[x] );
         requestBuffer.appendField( _RegPostalCode[x] );
      }
   }

}

