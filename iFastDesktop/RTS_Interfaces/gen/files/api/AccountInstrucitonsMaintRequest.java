// **** GENERATED FILE, PLEASE DO NOT MODIFY ******
package com.ifds.iFast.api;

import java.util.Date;
import java.io.Serializable;
import java.io.UnsupportedEncodingException;
import com.ifds.rts.*;

/**
 * Account MAT/INT/CSW Maint request.
 * For additional view information see <A HREF="../../../../viewspecs/AccountInstrucitonsMaint.doc">AccountInstrucitonsMaint.doc</A>.
 * 
 * @author RTS Generated
 */
public class AccountInstrucitonsMaintRequest extends IFastRequest implements Serializable
{

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
    * InstructionType member variable.
    */
   private String _InstructionType = "";
            
   /**
    * Account member variable.
    */
   private String _Account = "0";
            
   /**
    * Fund member variable.
    */
   private String _Fund = "";
            
   /**
    * Class member variable.
    */
   private String _Class = "";
            
   /**
    * SplitType member variable.
    */
   private String _SplitType = "";
            
   /**
    * EffectiveDate member variable.
    */
   private Date _EffectiveDate = null;
            
   /**
    * TransNum member variable.
    */
   private String _TransNum = "0";
            
   /**
    * CashSweepBal member variable.
    */
   private String _CashSweepBal = "";
            
   /**
    * SelectedAmt member variable.
    */
   private String _SelectedAmt = "0";
            
   /**
    * GBCD member variable.
    */
   private Boolean _GBCD = new Boolean(false);
            
   /**
    * TransSeq member variable.
    */
   private Integer _TransSeq = null;
            
   /**
    * ProcType member variable.
    */
   private String _ProcType = "";
            
   /**
    * TransId member variable.
    */
   private String _TransId = "0";
            
   /**
    * OrigIntInvestId member variable.
    */
   private String _OrigIntInvestId = "0";
            
   /**
    * Record count member variable.
    */
   private int _RepeatCount = 0;
   
   /**
    * Run Mode member array.
    */
   private String[] _RunMode = new String[25];
            
   /**
    * DistribDetlUUID member array.
    */
   private String[] _DistribDetlUUID = new String[25];
            
   /**
    * IntInvestId member array.
    */
   private String[] _IntInvestId = new String[25];
            
   /**
    * RollOverType member array.
    */
   private String[] _RollOverType = new String[25];
            
   /**
    * AccountTo member array.
    */
   private String[] _AccountTo = new String[25];
            
   /**
    * FundTo member array.
    */
   private String[] _FundTo = new String[25];
            
   /**
    * ClassTo member array.
    */
   private String[] _ClassTo = new String[25];
            
   /**
    * Remaining member array.
    */
   private String[] _Remaining = new String[25];
            
   /**
    * Currency member array.
    */
   private String[] _Currency = new String[25];
            
   /**
    * Percent member array.
    */
   private String[] _Percent = new String[25];
            
   /**
    * PayType member array.
    */
   private String[] _PayType = new String[25];
            
   /**
    * PayTypeDesc member array.
    */
   private String[] _PayTypeDesc = new String[25];
            
   /**
    * CommReduction member array.
    */
   private String[] _CommReduction = new String[25];
            
   /**
    * IntInvestType member array.
    */
   private String[] _IntInvestType = new String[25];
            
   /**
    * FELAmt member array.
    */
   private String[] _FELAmt = new String[25];
            
   /**
    * IntInvestTerm member array.
    */
   private Integer[] _IntInvestTerm = new Integer[25];
            
   /**
    * IntCalcMthd member array.
    */
   private String[] _IntCalcMthd = new String[25];
            
   /**
    * IntRateType member array.
    */
   private String[] _IntRateType = new String[25];
            
   /**
    * ForcedRate member array.
    */
   private String[] _ForcedRate = new String[25];
            
   /**
    * IntCredFreq member array.
    */
   private String[] _IntCredFreq = new String[25];
            
   /**
    * SourceOfFund member array.
    */
   private String[] _SourceOfFund = new String[25];
            
   /**
    * RefNum member array.
    */
   private String[] _RefNum = new String[25];
            
   /**
    * AddlAmt member array.
    */
   private String[] _AddlAmt = new String[25];
            
   /**
    * BankAcctId member array.
    */
   private String[] _BankAcctId = new String[25];
            
   /**
    * BankAcctUse member array.
    */
   private String[] _BankAcctUse = new String[25];
            
   /**
    * BankIdType member array.
    */
   private String[] _BankIdType = new String[25];
            
   /**
    * BankIdValue member array.
    */
   private Integer[] _BankIdValue = new Integer[25];
            
   /**
    * BankTransitNo member array.
    */
   private Integer[] _BankTransitNo = new Integer[25];
            
   /**
    * BankSwiftCode member array.
    */
   private Integer[] _BankSwiftCode = new Integer[25];
            
   /**
    * BankRefNumber member array.
    */
   private Integer[] _BankRefNumber = new Integer[25];
            
   /**
    * BankInstName member array.
    */
   private String[] _BankInstName = new String[25];
            
   /**
    * BankAddr1 member array.
    */
   private String[] _BankAddr1 = new String[25];
            
   /**
    * BankAddr2 member array.
    */
   private String[] _BankAddr2 = new String[25];
            
   /**
    * BankAddr3 member array.
    */
   private String[] _BankAddr3 = new String[25];
            
   /**
    * BankAddr4 member array.
    */
   private String[] _BankAddr4 = new String[25];
            
   /**
    * BankAddr5 member array.
    */
   private String[] _BankAddr5 = new String[25];
            
   /**
    * BankPostal member array.
    */
   private String[] _BankPostal = new String[25];
            
   /**
    * BankCountry member array.
    */
   private String[] _BankCountry = new String[25];
            
   /**
    * BankAcctType member array.
    */
   private String[] _BankAcctType = new String[25];
            
   /**
    * BankAcctCurrency member array.
    */
   private String[] _BankAcctCurrency = new String[25];
            
   /**
    * BankEffectiveDate member array.
    */
   private Date[] _BankEffectiveDate = new Date[25];
            
   /**
    * BankStopDate member array.
    */
   private Date[] _BankStopDate = new Date[25];
            
   /**
    * BankPayMethod member array.
    */
   private String[] _BankPayMethod = new String[25];
            
   /**
    * BankACHProcessor member array.
    */
   private String[] _BankACHProcessor = new String[25];
            
   /**
    * BankContact member array.
    */
   private String[] _BankContact = new String[25];
            
   /**
    * BankCorrespondent member array.
    */
   private String[] _BankCorrespondent = new String[25];
            
   /**
    * AddrCode member array.
    */
   private String[] _AddrCode = new String[25];
            
   /**
    * BankId member array.
    */
   private String[] _BankId = new String[25];
            
   /**
    * BankAcctNum member array.
    */
   private String[] _BankAcctNum = new String[25];
            
   /**
    * BankAcctName member array.
    */
   private String[] _BankAcctName = new String[25];
            
   /**
    * IntInvestUUID member array.
    */
   private String[] _IntInvestUUID = new String[25];
            
   /**
    * DistribDetlVer member array.
    */
   private Integer[] _DistribDetlVer = new Integer[25];
            
   /**
    * BankAcctVer member array.
    */
   private Integer[] _BankAcctVer = new Integer[25];
            
   /**
    * IntInvestVer member array.
    */
   private Integer[] _IntInvestVer = new Integer[25];
            

   /**
    * Constructs the AccountInstrucitonsMaintRequest object.
    * 
    */
   AccountInstrucitonsMaintRequest()
   {
      super ( 429 );
   }

   /**
    * Constructs the AccountInstrucitonsMaintRequest object with the given host encoding.
    * 
    * @param hostEncoding
    *               character encoding for sending/receiving host data
    */
   AccountInstrucitonsMaintRequest( String hostEncoding )
   {
      super ( 429, hostEncoding );
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
    * Sets the InstructionType field for the request.
    * 
    * @param value  Value that the InstructionType will be set to.
    */
   public final void setInstructionType( String value )
   {
      assertUnsent();
      _InstructionType = value;
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
    * Sets the Fund field for the request.
    * 
    * @param value  Value that the Fund will be set to.
    */
   public final void setFund( String value )
   {
      assertUnsent();
      _Fund = value;
   }
	
   /**
    * Sets the Class field for the request.
    * 
    * @param value  Value that the Class will be set to.
    */
   public final void setClass( String value )
   {
      assertUnsent();
      _Class = value;
   }
	
   /**
    * Sets the SplitType field for the request.
    * 
    * @param value  Value that the SplitType will be set to.
    */
   public final void setSplitType( String value )
   {
      assertUnsent();
      _SplitType = value;
   }
	
   /**
    * Sets the EffectiveDate field for the request.
    * 
    * @param value  Value that the EffectiveDate will be set to.
    */
   public final void setEffectiveDate( Date value )
   {
      assertUnsent();
      _EffectiveDate = value;
   }
	
   /**
    * Sets the TransNum field for the request.
    * 
    * @param value  Value that the TransNum will be set to.
    */
   public final void setTransNum( String value )
   {
      assertUnsent();
      _TransNum = value;
   }
	
   /**
    * Sets the CashSweepBal field for the request.
    * 
    * @param value  Value that the CashSweepBal will be set to.
    */
   public final void setCashSweepBal( String value )
   {
      assertUnsent();
      _CashSweepBal = value;
   }
	
   /**
    * Sets the SelectedAmt field for the request.
    * 
    * @param value  Value that the SelectedAmt will be set to.
    */
   public final void setSelectedAmt( String value )
   {
      assertUnsent();
      _SelectedAmt = value;
   }
	
   /**
    * Sets the GBCD field for the request.
    * 
    * @param value  Value that the GBCD will be set to.
    */
   public final void setGBCD( Boolean value )
   {
      assertUnsent();
      _GBCD = value;
   }
	
   /**
    * Sets the TransSeq field for the request.
    * 
    * @param value  Value that the TransSeq will be set to.
    */
   public final void setTransSeq( Integer value )
   {
      assertUnsent();
      _TransSeq = value;
   }
	
   /**
    * Sets the ProcType field for the request.
    * 
    * @param value  Value that the ProcType will be set to.
    */
   public final void setProcType( String value )
   {
      assertUnsent();
      _ProcType = value;
   }
	
   /**
    * Sets the TransId field for the request.
    * 
    * @param value  Value that the TransId will be set to.
    */
   public final void setTransId( String value )
   {
      assertUnsent();
      _TransId = value;
   }
	
   /**
    * Sets the OrigIntInvestId field for the request.
    * 
    * @param value  Value that the OrigIntInvestId will be set to.
    */
   public final void setOrigIntInvestId( String value )
   {
      assertUnsent();
      _OrigIntInvestId = value;
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
    * Sets the DistribDetlUUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the DistribDetlUUID will be set to.
    */
   public final void setDistribDetlUUID( int index, String value )
   {
      assertUnsent();
      _DistribDetlUUID[index] = value;
   }
	
   /**
    * Sets the IntInvestId field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IntInvestId will be set to.
    */
   public final void setIntInvestId( int index, String value )
   {
      assertUnsent();
      _IntInvestId[index] = value;
   }
	
   /**
    * Sets the RollOverType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RollOverType will be set to.
    */
   public final void setRollOverType( int index, String value )
   {
      assertUnsent();
      _RollOverType[index] = value;
   }
	
   /**
    * Sets the AccountTo field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AccountTo will be set to.
    */
   public final void setAccountTo( int index, String value )
   {
      assertUnsent();
      _AccountTo[index] = value;
   }
	
   /**
    * Sets the FundTo field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FundTo will be set to.
    */
   public final void setFundTo( int index, String value )
   {
      assertUnsent();
      _FundTo[index] = value;
   }
	
   /**
    * Sets the ClassTo field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ClassTo will be set to.
    */
   public final void setClassTo( int index, String value )
   {
      assertUnsent();
      _ClassTo[index] = value;
   }
	
   /**
    * Sets the Remaining field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Remaining will be set to.
    */
   public final void setRemaining( int index, String value )
   {
      assertUnsent();
      _Remaining[index] = value;
   }
	
   /**
    * Sets the Currency field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Currency will be set to.
    */
   public final void setCurrency( int index, String value )
   {
      assertUnsent();
      _Currency[index] = value;
   }
	
   /**
    * Sets the Percent field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the Percent will be set to.
    */
   public final void setPercent( int index, String value )
   {
      assertUnsent();
      _Percent[index] = value;
   }
	
   /**
    * Sets the PayType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the PayType will be set to.
    */
   public final void setPayType( int index, String value )
   {
      assertUnsent();
      _PayType[index] = value;
   }
	
   /**
    * Sets the PayTypeDesc field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the PayTypeDesc will be set to.
    */
   public final void setPayTypeDesc( int index, String value )
   {
      assertUnsent();
      _PayTypeDesc[index] = value;
   }
	
   /**
    * Sets the CommReduction field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the CommReduction will be set to.
    */
   public final void setCommReduction( int index, String value )
   {
      assertUnsent();
      _CommReduction[index] = value;
   }
	
   /**
    * Sets the IntInvestType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IntInvestType will be set to.
    */
   public final void setIntInvestType( int index, String value )
   {
      assertUnsent();
      _IntInvestType[index] = value;
   }
	
   /**
    * Sets the FELAmt field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the FELAmt will be set to.
    */
   public final void setFELAmt( int index, String value )
   {
      assertUnsent();
      _FELAmt[index] = value;
   }
	
   /**
    * Sets the IntInvestTerm field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IntInvestTerm will be set to.
    */
   public final void setIntInvestTerm( int index, Integer value )
   {
      assertUnsent();
      _IntInvestTerm[index] = value;
   }
	
   /**
    * Sets the IntCalcMthd field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IntCalcMthd will be set to.
    */
   public final void setIntCalcMthd( int index, String value )
   {
      assertUnsent();
      _IntCalcMthd[index] = value;
   }
	
   /**
    * Sets the IntRateType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IntRateType will be set to.
    */
   public final void setIntRateType( int index, String value )
   {
      assertUnsent();
      _IntRateType[index] = value;
   }
	
   /**
    * Sets the ForcedRate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the ForcedRate will be set to.
    */
   public final void setForcedRate( int index, String value )
   {
      assertUnsent();
      _ForcedRate[index] = value;
   }
	
   /**
    * Sets the IntCredFreq field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IntCredFreq will be set to.
    */
   public final void setIntCredFreq( int index, String value )
   {
      assertUnsent();
      _IntCredFreq[index] = value;
   }
	
   /**
    * Sets the SourceOfFund field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the SourceOfFund will be set to.
    */
   public final void setSourceOfFund( int index, String value )
   {
      assertUnsent();
      _SourceOfFund[index] = value;
   }
	
   /**
    * Sets the RefNum field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the RefNum will be set to.
    */
   public final void setRefNum( int index, String value )
   {
      assertUnsent();
      _RefNum[index] = value;
   }
	
   /**
    * Sets the AddlAmt field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AddlAmt will be set to.
    */
   public final void setAddlAmt( int index, String value )
   {
      assertUnsent();
      _AddlAmt[index] = value;
   }
	
   /**
    * Sets the BankAcctId field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAcctId will be set to.
    */
   public final void setBankAcctId( int index, String value )
   {
      assertUnsent();
      _BankAcctId[index] = value;
   }
	
   /**
    * Sets the BankAcctUse field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAcctUse will be set to.
    */
   public final void setBankAcctUse( int index, String value )
   {
      assertUnsent();
      _BankAcctUse[index] = value;
   }
	
   /**
    * Sets the BankIdType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankIdType will be set to.
    */
   public final void setBankIdType( int index, String value )
   {
      assertUnsent();
      _BankIdType[index] = value;
   }
	
   /**
    * Sets the BankIdValue field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankIdValue will be set to.
    */
   public final void setBankIdValue( int index, Integer value )
   {
      assertUnsent();
      _BankIdValue[index] = value;
   }
	
   /**
    * Sets the BankTransitNo field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankTransitNo will be set to.
    */
   public final void setBankTransitNo( int index, Integer value )
   {
      assertUnsent();
      _BankTransitNo[index] = value;
   }
	
   /**
    * Sets the BankSwiftCode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankSwiftCode will be set to.
    */
   public final void setBankSwiftCode( int index, Integer value )
   {
      assertUnsent();
      _BankSwiftCode[index] = value;
   }
	
   /**
    * Sets the BankRefNumber field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankRefNumber will be set to.
    */
   public final void setBankRefNumber( int index, Integer value )
   {
      assertUnsent();
      _BankRefNumber[index] = value;
   }
	
   /**
    * Sets the BankInstName field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankInstName will be set to.
    */
   public final void setBankInstName( int index, String value )
   {
      assertUnsent();
      _BankInstName[index] = value;
   }
	
   /**
    * Sets the BankAddr1 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAddr1 will be set to.
    */
   public final void setBankAddr1( int index, String value )
   {
      assertUnsent();
      _BankAddr1[index] = value;
   }
	
   /**
    * Sets the BankAddr2 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAddr2 will be set to.
    */
   public final void setBankAddr2( int index, String value )
   {
      assertUnsent();
      _BankAddr2[index] = value;
   }
	
   /**
    * Sets the BankAddr3 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAddr3 will be set to.
    */
   public final void setBankAddr3( int index, String value )
   {
      assertUnsent();
      _BankAddr3[index] = value;
   }
	
   /**
    * Sets the BankAddr4 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAddr4 will be set to.
    */
   public final void setBankAddr4( int index, String value )
   {
      assertUnsent();
      _BankAddr4[index] = value;
   }
	
   /**
    * Sets the BankAddr5 field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAddr5 will be set to.
    */
   public final void setBankAddr5( int index, String value )
   {
      assertUnsent();
      _BankAddr5[index] = value;
   }
	
   /**
    * Sets the BankPostal field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankPostal will be set to.
    */
   public final void setBankPostal( int index, String value )
   {
      assertUnsent();
      _BankPostal[index] = value;
   }
	
   /**
    * Sets the BankCountry field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankCountry will be set to.
    */
   public final void setBankCountry( int index, String value )
   {
      assertUnsent();
      _BankCountry[index] = value;
   }
	
   /**
    * Sets the BankAcctType field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAcctType will be set to.
    */
   public final void setBankAcctType( int index, String value )
   {
      assertUnsent();
      _BankAcctType[index] = value;
   }
	
   /**
    * Sets the BankAcctCurrency field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAcctCurrency will be set to.
    */
   public final void setBankAcctCurrency( int index, String value )
   {
      assertUnsent();
      _BankAcctCurrency[index] = value;
   }
	
   /**
    * Sets the BankEffectiveDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankEffectiveDate will be set to.
    */
   public final void setBankEffectiveDate( int index, Date value )
   {
      assertUnsent();
      _BankEffectiveDate[index] = value;
   }
	
   /**
    * Sets the BankStopDate field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankStopDate will be set to.
    */
   public final void setBankStopDate( int index, Date value )
   {
      assertUnsent();
      _BankStopDate[index] = value;
   }
	
   /**
    * Sets the BankPayMethod field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankPayMethod will be set to.
    */
   public final void setBankPayMethod( int index, String value )
   {
      assertUnsent();
      _BankPayMethod[index] = value;
   }
	
   /**
    * Sets the BankACHProcessor field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankACHProcessor will be set to.
    */
   public final void setBankACHProcessor( int index, String value )
   {
      assertUnsent();
      _BankACHProcessor[index] = value;
   }
	
   /**
    * Sets the BankContact field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankContact will be set to.
    */
   public final void setBankContact( int index, String value )
   {
      assertUnsent();
      _BankContact[index] = value;
   }
	
   /**
    * Sets the BankCorrespondent field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankCorrespondent will be set to.
    */
   public final void setBankCorrespondent( int index, String value )
   {
      assertUnsent();
      _BankCorrespondent[index] = value;
   }
	
   /**
    * Sets the AddrCode field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the AddrCode will be set to.
    */
   public final void setAddrCode( int index, String value )
   {
      assertUnsent();
      _AddrCode[index] = value;
   }
	
   /**
    * Sets the BankId field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankId will be set to.
    */
   public final void setBankId( int index, String value )
   {
      assertUnsent();
      _BankId[index] = value;
   }
	
   /**
    * Sets the BankAcctNum field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAcctNum will be set to.
    */
   public final void setBankAcctNum( int index, String value )
   {
      assertUnsent();
      _BankAcctNum[index] = value;
   }
	
   /**
    * Sets the BankAcctName field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAcctName will be set to.
    */
   public final void setBankAcctName( int index, String value )
   {
      assertUnsent();
      _BankAcctName[index] = value;
   }
	
   /**
    * Sets the IntInvestUUID field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IntInvestUUID will be set to.
    */
   public final void setIntInvestUUID( int index, String value )
   {
      assertUnsent();
      _IntInvestUUID[index] = value;
   }
	
   /**
    * Sets the DistribDetlVer field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the DistribDetlVer will be set to.
    */
   public final void setDistribDetlVer( int index, Integer value )
   {
      assertUnsent();
      _DistribDetlVer[index] = value;
   }
	
   /**
    * Sets the BankAcctVer field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the BankAcctVer will be set to.
    */
   public final void setBankAcctVer( int index, Integer value )
   {
      assertUnsent();
      _BankAcctVer[index] = value;
   }
	
   /**
    * Sets the IntInvestVer field for the request and the given index.
    * 
    * @param index  Zero based index of the repeat for which the value will be set.
    * @param value  Value that the IntInvestVer will be set to.
    */
   public final void setIntInvestVer( int index, Integer value )
   {
      assertUnsent();
      _IntInvestVer[index] = value;
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
      requestBuffer.appendField( _InstructionType );
      requestBuffer.appendField( _Account );
      requestBuffer.appendField( _Fund );
      requestBuffer.appendField( _Class );
      requestBuffer.appendField( _SplitType );
      requestBuffer.appendField( _EffectiveDate );
      requestBuffer.appendField( _TransNum );
      requestBuffer.appendField( _CashSweepBal );
      requestBuffer.appendField( _SelectedAmt );
      requestBuffer.appendField( _GBCD );
      requestBuffer.appendField( _TransSeq );
      requestBuffer.appendField( _ProcType );
      requestBuffer.appendField( _TransId );
      requestBuffer.appendField( _OrigIntInvestId );
      requestBuffer.appendField( new Integer(_RepeatCount) );  // add record count
      for ( int x = 0; x < _RepeatCount; x++ )
      {
         requestBuffer.appendField( _RunMode[x] );
         requestBuffer.appendField( _DistribDetlUUID[x] );
         requestBuffer.appendField( _IntInvestId[x] );
         requestBuffer.appendField( _RollOverType[x] );
         requestBuffer.appendField( _AccountTo[x] );
         requestBuffer.appendField( _FundTo[x] );
         requestBuffer.appendField( _ClassTo[x] );
         requestBuffer.appendField( _Remaining[x] );
         requestBuffer.appendField( _Currency[x] );
         requestBuffer.appendField( _Percent[x] );
         requestBuffer.appendField( _PayType[x] );
         requestBuffer.appendField( _PayTypeDesc[x] );
         requestBuffer.appendField( _CommReduction[x] );
         requestBuffer.appendField( _IntInvestType[x] );
         requestBuffer.appendField( _FELAmt[x] );
         requestBuffer.appendField( _IntInvestTerm[x] );
         requestBuffer.appendField( _IntCalcMthd[x] );
         requestBuffer.appendField( _IntRateType[x] );
         requestBuffer.appendField( _ForcedRate[x] );
         requestBuffer.appendField( _IntCredFreq[x] );
         requestBuffer.appendField( _SourceOfFund[x] );
         requestBuffer.appendField( _RefNum[x] );
         requestBuffer.appendField( _AddlAmt[x] );
         requestBuffer.appendField( _BankAcctId[x] );
         requestBuffer.appendField( _BankAcctUse[x] );
         requestBuffer.appendField( _BankIdType[x] );
         requestBuffer.appendField( _BankIdValue[x] );
         requestBuffer.appendField( _BankTransitNo[x] );
         requestBuffer.appendField( _BankSwiftCode[x] );
         requestBuffer.appendField( _BankRefNumber[x] );
         requestBuffer.appendField( _BankInstName[x] );
         requestBuffer.appendField( _BankAddr1[x] );
         requestBuffer.appendField( _BankAddr2[x] );
         requestBuffer.appendField( _BankAddr3[x] );
         requestBuffer.appendField( _BankAddr4[x] );
         requestBuffer.appendField( _BankAddr5[x] );
         requestBuffer.appendField( _BankPostal[x] );
         requestBuffer.appendField( _BankCountry[x] );
         requestBuffer.appendField( _BankAcctType[x] );
         requestBuffer.appendField( _BankAcctCurrency[x] );
         requestBuffer.appendField( _BankEffectiveDate[x] );
         requestBuffer.appendField( _BankStopDate[x] );
         requestBuffer.appendField( _BankPayMethod[x] );
         requestBuffer.appendField( _BankACHProcessor[x] );
         requestBuffer.appendField( _BankContact[x] );
         requestBuffer.appendField( _BankCorrespondent[x] );
         requestBuffer.appendField( _AddrCode[x] );
         requestBuffer.appendField( _BankId[x] );
         requestBuffer.appendField( _BankAcctNum[x] );
         requestBuffer.appendField( _BankAcctName[x] );
         requestBuffer.appendField( _IntInvestUUID[x] );
         requestBuffer.appendField( _DistribDetlVer[x] );
         requestBuffer.appendField( _BankAcctVer[x] );
         requestBuffer.appendField( _IntInvestVer[x] );
      }
   }

}

