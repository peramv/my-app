package com.ifdsgroup.ifast.desktop.web.core.config;


/**
 * This class contains constants used by the application
 * 
 * @author if993762
 *
 */
public class DesktopWebConstants {

    // Header Node
    public static final String REQUEST_HEADER = "RequestHeader";
    public static final String SESSION_ID = "sessionId";
    public static final String SLOT_NAME = "envName";
    public static final String CLIENT_CODE = "companyCode";
    public static final String USER_ID = "ruserId";
    
    public static final String IFAST_SESSION_TOKEN = "IFAST_SESSION_TOKEN";
    public static final String IFAST_SLOT_NAME = "IFAST_SLOT_NAME";

    // Retrieve Cache Response Header Node
    public static final String RETRIEVE_CACHE_RESPONSE_HEADER = "RetrieveCacheResponse";

    // Smart View Response Header Node
    public static final String SMART_VIEW_RESPONSE_HEADER = "SmartviewResponse";

    // Sonic Response constants
    public static final String SONIC_RESPONSE_SUCCESS = "Accepted";
    public static final String SONIC_RESPONSE_REJECTED = "Rejected";

    // Retrieve Cache Header Node
    public static final String KEY = "cacheKey";

    // Cache Key Node
    public static final String INITIAL_DATA = "InitData";
    public static final String SCREEN_TAB_LIST = "ScreenDefList";
    public static final String EXISTING_CLASS_DATA = "ExistingClassData";
    public static final String UPDATED_CLASS_DATA = "UpdatedClassData";

    // Update Cache Request Header Node
    public static final String UPDATE_CACHE_REQUEST_HEADER = "UpdateCacheRequest";
    public static final String TO_BE_CACHED = "ToBeCached";
    public static final String TO_BE_CACHED_ATTRIBUTE = "cacheKey";
    public static final String TO_BE_CACHED_HEADER = "/" + UPDATE_CACHE_REQUEST_HEADER + "/" + TO_BE_CACHED;

    // Delete Cache Request Header Node
    public static final String DELETE_CACHE_REQUEST_HEADER = "DeleteCacheRequest";

    // XML Data
    public static final String PAY_LOAD_DATA_TYPE_XML = "XML";
    public static final String SUCCESS_RESPONSE = "success";
    public static final String SUCCESS_MSG = "success";
    public static final String FAILURE_RESPONSE = "failed";

    // Externalization data
    public static final String PROP_PATH = System.getProperty("config.path");

    // Added for OE
	public static final String API_DEFAULT_LANGUAGE = "en";
    public static final String ACCTBALASOF_API = "gnAcctBalAsOf";
    public static final String ACCTBALASOF_INTERFACE = "ifds.gnAPI.AcctBalAsOf";
    public static final String API_DATE_FORMAT = "yyyymmdd";
    public static final String API_DOWNLOAD_MODE = "no";
	public static final String API_DATA_MODE = "inquire";

    private DesktopWebConstants() {
    }

}