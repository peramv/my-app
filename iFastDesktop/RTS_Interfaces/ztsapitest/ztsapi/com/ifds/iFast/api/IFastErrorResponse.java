package com.ifds.iFast.api;

import java.text.ParseException;
import java.io.IOException;
import java.util.*;
import java.io.Serializable;
import com.ifds.rts.RTSResponseDecodeBuffer;

/**
 * An object of this type is returned by 
 * IFastView.getErrorResponse() if a call to
 * IFastView.receive() or IFastView.ReceiveAll()
 * resulted in a host error response. 
 * 
 * Typically this will be as a result of data not
 * being found for the given request, or inappropriate
 * field data in the request.
 */
public class IFastErrorResponse implements Serializable  
{

   /**
    * (1) Data not found
    */
   public static final int DATA_NOT_FOUND = 1;

   /**
    * (2) Access denied - After mandatory logoff time
    */
   public static final int AD_AFTER_MANDATORY_LOGOFF_TIME = 2;

   /**
    * (3) Access denied - Before allowable logon time
    */
   public static final int AD_BEFORE_ALLOWABLE_LOGON_TIME = 3;

   /**
    * (4) Access denied - invalid password
    */
   public static final int AD_INVALID_PASSWORD = 4;

   /**
    * (5) Access denied - Invalid profile
    */
   public static final int AD_INVALID_PROFILE = 5;

   /**
    * (6) Access denied - Maximum sessions already running
    */
   public static final int AD_MAXIMUM_SESSIONS_ALREADY_RUNNING = 6;

   /**
    * (7) Access denied - No company access
    */
   public static final int AD_NO_COMPANY_ACCESS = 7;

   /**
    * (8) Access denied - Past password grace period
    */
   public static final int AD_PAST_PASSWORD_GRACE_PERIOD = 8;

   /**
    * (9) Access denied - Profile has no access today
    */
   public static final int AD_PROFILE_HAS_NO_ACCESS_TODAY = 9;

   /**
    * (10) Access denied - Shareholder does not exist
    */
   public static final int AD_SHAREHOLDER_DOES_NOT_EXIST = 10;

   /**
    * (11) Access denied - Too many failed logons
    */
   public static final int AD_TOO_MANY_FAILED_LOGONS = 11;

   /**
    * (13) Access denied - unknown user
    */
   public static final int AD_UNKNOWN_USER = 13;

   /**
    * (14) Access denied - User account not active
    */
   public static final int AD_USER_ACCOUNT_NOT_ACTIVE = 14;

   /**
    * (15) Access denied - user has no company access
    */
   public static final int AD_USER_HAS_NO_COMPANY_ACCESS = 15;

   /**
    * (34) Unknown Account
    */
   public static final int UNKNOWN_ACCOUNT = 34;

   /**
    * (35) Unknown Start Date
    */
   public static final int UNKNOWN_START_DATE = 35;

   /**
    * (41) Entity not found
    */
   public static final int ENTITY_NOT_FOUND = 41;

   /**
    * (42) Registered Address Default not found
    */
   public static final int REGISTERED_ADDRESS_DEFAULT_NOT_FOUND = 42;

   /**
    * (43) Broker not found
    */
   public static final int BROKER_NOT_FOUND = 43;

   /**
    * (44) Intermediary not found
    */
   public static final int INTERMEDIARY_NOT_FOUND = 44;

   /**
    * (46) Account Number is invalid
    */
   public static final int ACCOUNT_NUMBER_INVALID = 46;

   /**
    * (48) User cannot access this account
    */
   public static final int USER_CANNOT_ACCESS_ACCOUNT = 48;

   /**
    * (49) Please send again as last record was deleted
    */
   public static final int SEND_AGAIN_LAST_RECORD_DELETED = 49;

   /**
    * (50) Invalid Fund Code
    */
   public static final int INVALID_FUND_CODE = 50;

   /**
    * (51) Next Key did not match expected  format 
    */
   public static final int NEXT_KEY_NOT_PROPERLY_FORMAT  = 51;

   /**
    * (54) Invalid Class Code
    */
   public static final int INVALID_CLASS_CODE = 54;

   /**
    * (55) No Address Record Available
    */
   public static final int NO_ADDRESS_RECORD_AVAILABLE = 55;

   /**
    * (56) Invalid CHUIReln setup. 'Function' not found in 'Company'.Menu-Detl. 
    */
   public static final int INVALID_CHUIRELN_SETUP = 56;

   /**
    * (58) No related CHUI functions available
    */
   public static final int CHUI_FUNCTIONS_NOT_AVAILABLE = 58;

   /**
    * (82) Invalid Shareholder
    */
   public static final int INVALID_SHAREHOLDER = 82;

   /**
    * (96) User-access record  not found for this user-id.
    */
   public static final int USER_ACCESS_RECORD_NOT_FOUND = 96;

   /**
    * (97) User status is inactive in Company Database
    */
   public static final int USER_STATUS_INACTIVE = 97;

   /**
    * (102) Sales Rep not found.
    */
   public static final int SALES_REP_NOT_FOUND = 102;

   /**
    * (103) Branch not found
    */
   public static final int BRANCH_NOT_FOUND = 103;

   /**
    * (111) "Cash" is not a valid fund.
    */
   public static final int CASH_NOT_VALID_FUND_CODE = 111;

   /**
    * (114) User-id does not have access to this Broker/Branch/Sales Rep
    */
   public static final int USER_ID_CANNOT_ACCESS_BROKER_BRANCH_SALESREP = 114;

   /**
    * (117) Controls record CloseAcctCode not found
    */
   public static final int CONTROL_RECORD_CLOSEACCTCODE_NOT_FOUND = 117;

   /**
    * (118) Close A/C redemption code entered without full redemption
    */
   public static final int REDEMPTION_CODE_ENTERED_WITHOUT_REDEMPTION = 118;

   /**
    * (119) No Account holdings exist at this date
    */
   public static final int NO_ACCOUNT_HOLDINGS_AT_DATE = 119;

   /**
    * (120) Units not allowed for Net Redemptions
    */
   public static final int UNITS_NOT_ALLOWED_FOR_NET_REDEMPTION = 120;

   /**
    * (121) Full Redemption is not allowed for Net Redemptions
    */
   public static final int FULL_REDEMPTION_NOT_ALLOWED_FOR_NET_REDEMPTION = 121;

   /**
    * (122) Redemption code not available for this Tax Type
    */
   public static final int NO_REDEMPTION_CODE_FOR_TAX_TYPE = 122;

   /**
    * (123) Invalid Fund and Class entered for this account
    */
   public static final int INVALID_FUND_CLASS_FOR_ACCOUNT = 123;

   /**
    * (124) Amount entered greater than that available on Fund
    */
   public static final int AMOUNT_GREATER_THAN_AVAILABLE_FOR_FUND = 124;

   /**
    * (132) Sorting request code is not valid
    */
   public static final int SORTING_REQUEST_CODE_IS_NOT_VALID = 132;

   /**
    * (133) Invalid Request Type
    */
   public static final int INVALID_REQUEST_TYPE = 133;

   /**
    * (150) Database unavailable.
    */
   public static final int DATABASE_UNAVAILABLE = 150;

   /**
    * (151) Access denied - database not connected.
    */
   public static final int AD_DATABASE_NOT_CONNECTED = 151;

   /**
    * (152) Access denied - no company record.
    */
   public static final int AD_NO_COMPANY_RECORD = 152;

   /**
    * (153) Access denied - Unknown response type: <Response Type>
    */
   public static final int AD_UNKNOWN_RESPONSE_TYPE = 153;

   /**
    * (154) Access denied - no session record.
    */
   public static final int AD_NO_SESSION_RECORD = 154;

   /**
    * (155) Access denied - Password must be reset.
    */
   public static final int AD_PASSWORD_MUST_BE_RESET = 155;

   /**
    * (156) Access denied - Past logoff time.
    */
   public static final int AD_PAST_LOGOFF_TIME = 156;

   /**
    * (184) Search for Sales Rep by Broker Code only not supported
    */
   public static final int CANNOT_SEARCH_BY_BROKER_CODE_ALONE = 184;

   /**
    * (194) Amount is mandatory, should be greater than 0
    */
   public static final int AMOUNT_IS_MANDATORY = 194;

   /**
    * (223) Unit-Detl record not found
    */
   public static final int UNIT_DETAIL_NOT_FOUND = 223;

   /**
    * (237) Back Office Time Zone is invalid
    */
   public static final int BACK_OFFICE_TIME_ZONE_INVALID = 237;

   /**
    * (238) Financial Institution Time Zone is invalid
    */
   public static final int FINANCIAL_INSTITUTION_TIME_ZONE_INVALID = 238;

   /**
    * (239) Amount cannot be greater than 100 for AmountType P
    */
   public static final int AMOUNT_GREATER_THAN_100_FOR_AMOUNT_TYPE_P = 239;

   /**
    * (246) UserType does not have access to this view
    */
   public static final int USER_TYPE_CANNOT_ACCESS_VIEW = 246;

   /**
    * (247) SecurityProfileId does not have access to this view
    */
   public static final int SECURITY_PROFILE_ID_CANNOT_ACCESS_VIEW = 247;

   /**
    * (249) Banking Entity must either be 01, 02, 03, 04, 10 or 11
    */
   public static final int BANKING_ENTITY_MUST_BE_01_02_03_04_10_11 = 249;

   /**
    * (250) Broker must be entered
    */
   public static final int BROKER_MUST_BE_ENTERED = 250;

   /**
    * (251) Broker and Branch must be entered
    */
   public static final int BROKER_BRANCH_MUST_BE_ENTERED = 251;

   /**
    * (252) Broker, Branch and Sales Rep must be entered
    */
   public static final int BROKER_BRANCH_SALES_REP_MUST_BE_ENTERED = 252;

   /**
    * (253) Broker and Sales Rep must be entered
    */
   public static final int BROKER_SALES_REP_MUST_BE_ENTERED = 253;

   /**
    * (317) User cannot access this account
    */
   public static final int USER_CANNOT_ACCESS_ACCOUNT_2 = 317;

   /**
    * (341) Invalid AmountType
    */
   public static final int INVALID_AMOUNT_TYPE = 341;

   /**
    * (342) Invalid Baycom
    */
   public static final int INVALID_BAYCOM = 342;

   /**
    * (344) Amount must be 0 for AmountType T
    */
   public static final int AMOUNT_MUST_BE_0_FOR_AMOUNT_TYPE_T = 344;

   /**
    * (345) Not Applicable for this Fund/Class
    */
   public static final int NOT_APPLICABLE_FOR_FUND_CLASS = 345;
   
   /**
    * (351) FundCode cannot be blank for BankingEntity 11
    */
   public static final int FUND_CODE_NOT_BLANK_FOR_BANKING_ENTITY_11 = 351;

   /*
    * Error code member variable.
    */
   private final int _code;
   /**
    * Message member variable.
    */
   private final String _message;

   /**
    * Constructs the IFastErrorResponse object.<br><br>
    * 
    * @param response Host encoded error response.
    * @exception ParseException
    */
   IFastErrorResponse( RTSResponseDecodeBuffer responseBuffer ) throws ParseException, IOException
   {
      _code = responseBuffer.decodeInteger(responseBuffer.getNextField()).intValue();
      _message = responseBuffer.decodeString(responseBuffer.getNextField());
   }

   /**
    * Gets the code for the error response.<br><br>
    * 
    * @return The the error code.
    */
   public int getCode()
   {
      return _code;
   }

   /**
    * Gets the message for the error response.<br><br>
    * 
    * @return The message texxt.
    */
   public String getMessage()
   {
      return _message;
   }

   /**
    * To String method of Object.<br><br>
    * 
    * @return The message text.
    */
   public String toString()
   {
      return "   IFastErrorResponse:   code: " + getCode() + "   message: " + getMessage();
   }

}
